#include "smartcard_contactless.h"
#include "ui_smartcard_contactless.h"
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>

#include "GlobalClass.h"

using namespace Globalclass;

//#define TIME_BEFORE_SUICIDE 30

#define CHECK_CL(f, rv) \
 if (SCARD_S_SUCCESS != rv) \
 { \
   if (SCARD_E_CANCELLED != rv) \
   { \
     LastError =  QString(f) + " " + QString(pcsc_stringify_error(rv)); \
     qDebug()<<"\r"<<LastError; \
     isError = true; \
     return; \
   }\
 }

 #define TIMEOUT 1000	/* 1 second timeout */

/********************************************************************************
                        Contactless Smartcard
To communicate with smart card readers from source code PC/SC lite API calls are
used, for more information on pc/sc lite API reference visit,
            -http://pcsclite.alioth.debian.org/pcsc-lite/
            -http://pcsclite.alioth.debian.org/api/group__API.html
********************************************************************************/
smartcard_contactless::smartcard_contactless(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smartcard_contactless)
{
    ui->setupUi(this);
    setParent(MdiArea);
    isError = false;

    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    move(0,0);

    ui->lblATR->setWordWrap(true);
    ui->lblCardstat->setWordWrap(true);
    ui->lblReader->setWordWrap(true);
    ui->lblUID->setWordWrap(true);
    obj_thrd = new SC_CLthread;
    if(obj_thrd->connected)
    {
        connect(obj_thrd, SIGNAL(state_changed(bool)), this, SLOT(slot_stateChanged(bool)));
        connect(obj_thrd, SIGNAL(error_close()), this, SLOT(slotclose()));
        obj_thrd->start();
    }
    else
    {
        QMessageBox::critical(0, "Error - Smartcard utility", obj_thrd->LastError);
        isError = true;
    }
    ui->groupBox->setFocus();
}

smartcard_contactless::~smartcard_contactless()
{
    delete ui;
}

void smartcard_contactless::slot_stateChanged(bool readerState)
{
    if(readerState)
    {
        ui->lblATR->setText(obj_thrd->ATR);
        ui->lblCardstat->setText(obj_thrd->Cardstat);
        ui->lblUID->setText(obj_thrd->UID);
        ui->lblReader->setText(obj_thrd->Reader);
    }
    else
    {
        ui->lblReader->setText("No Reader Found..");
        ui->lblATR->setText("");
        ui->lblCardstat->setText("");
        ui->lblUID->setText("");
    }
}


void smartcard_contactless::slotclose()
{
    if(obj_thrd->isError)
    {
        QMessageBox::critical(0, "Error - Smartcard utility", obj_thrd->LastError);
    }
    if(obj_thrd->isRunning())
    {
        obj_thrd->thread_terminate();
    }
    obj_thrd->deleteLater();
    reject();
}

void smartcard_contactless::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape || e->key() == Qt::Key_F4)
    {
        slotclose();
    }

    else
    {
        QDialog::keyPressEvent(e);
    }
}


/********************************************************************************/
//                         Contact less Smartcard thread
//in this class thread concept is used to check the reader status repetedly, if the
// status changed it will updated on the form
/********************************************************************************/
SC_CLthread::SC_CLthread()
{
    connected = false;
    isError = false;
    readers = NULL;
    connect(this, SIGNAL(finished()), this, SLOT(thread_terminate()));

    /*SCardEstablishContext ->This function creates a communication context to the PC/SC Resource Manager.
        This must be the first function called in a PC/SC application */

    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, 0, 0, &hContext);
    CHECK_CL("SCardEstablishContext ", rv)

    connected = true;
}

void SC_CLthread::run()
{
    unsigned int i, l_i_readcount;
    DWORD timeout,dwActiveProtocol;
    char atr[MAX_ATR_SIZE*3+1];	/* ATR in ASCII */
    rgReaderStates_t = NULL;
    SCARD_READERSTATE rgReaderStates[1];
    BYTE cmd1[] = {0xFF, 0xCA, 0x00, 0x00, 0x00};
    bool CardPresent = false, l_bool_result = false;
    QString cardStatus, curr_atr;
    int pnp = TRUE;
    mszReaders = NULL;

    rgReaderStates[0].szReader = "\\\\?PnP?\\Notification";
    rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;

    rv = SCardGetStatusChange(hContext, 0, rgReaderStates, 1);
    if (rgReaderStates[0].dwEventState && SCARD_STATE_UNKNOWN)
    {
        qDebug("PnP reader name not supported. Using polling.\n");
        pnp = FALSE;
    }
    get_readers:
    /* free memory possibly allocated in a previous loop */
    if (NULL != readers)
    {
        free(readers);
        readers = NULL;
    }

    if (NULL != rgReaderStates_t)
    {
        free(rgReaderStates_t);
        rgReaderStates_t = NULL;
    }

#ifdef SCARD_AUTOALLOCATE

    if (mszReaders)
    {
        rv = SCardFreeMemory(hContext, mszReaders);
        CHECK_CL("SCardFreeMemory ", rv)
        mszReaders = NULL;
    }

    dwReaders = SCARD_AUTOALLOCATE;

    /* SCardListReaders -> This function returns a list of currently available readers on the system. */

    rv = SCardListReaders(hContext, 0, (LPTSTR)&mszReaders, &dwReaders);
    if (rv != SCARD_E_NO_READERS_AVAILABLE)
            CHECK_CL("SCardListReaders ", rv)
#else
    rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
    CHECK_CL("SCardListReaders ", rv)

    mszReaders = calloc(dwReaders, sizeof(char));
    rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);
    CHECK_CL("SCardListReaders ", rv)
#endif

    dwReadersOld = dwReaders;

    NoofReaders = 0;
    if(rv != SCARD_E_NO_READERS_AVAILABLE)
    {
        ptr = mszReaders;
        while (*ptr != '\0')
        {
            ptr += strlen(ptr)+1;
            NoofReaders++;
        }
    }
    if (SCARD_E_NO_READERS_AVAILABLE == rv || 0 == NoofReaders)
    {
        qDebug("Waiting for the first reader...");

        emit state_changed(false);
        if (pnp)
        {
            rgReaderStates[0].szReader = "\\\\?PnP?\\Notification";
            rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;

            rv = SCardGetStatusChange(hContext, INFINITE, rgReaderStates, 1);
//            usleep(1);
            CHECK_CL("SCardGetStatusChange ", rv);
        }
        else
        {
            rv = SCARD_S_SUCCESS;
            while ((SCARD_S_SUCCESS == rv) && (dwReaders == dwReadersOld))
            {
                rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
                if (SCARD_E_NO_READERS_AVAILABLE == rv)
                     rv = SCARD_S_SUCCESS;
                sleep(1);
            }
        }
        if(!connected)
            return;
        qDebug("found one\n");
        goto get_readers;
    }
    else
        CHECK_CL("SCardListReader ", rv);

    readers = (char**) calloc(NoofReaders+1, sizeof(char *));
    if (NULL == readers)
    {
        qDebug("Not enough memory for readers table\n");
        return;
    }

    /* fill the readers table */
    NoofReaders = 0;
    ptr = mszReaders;
    while (*ptr != '\0')
    {
        qDebug("%d: %s\n", NoofReaders, ptr);
        readers[NoofReaders] = ptr;
        ptr += strlen(ptr)+1;
        NoofReaders++;
    }

    /* allocate the ReaderStates table */
    rgReaderStates_t = (SCARD_READERSTATE*) calloc(NoofReaders+1, sizeof(* rgReaderStates_t));
    if (NULL == rgReaderStates_t)
    {
        qDebug("Not enough memory for readers states\n");
        return;
    }

 /* Set the initial states to something we do not know
  * The loop below will include this state to the dwCurrentState
  */
    for (i=0; i<NoofReaders; i++)
    {
        rgReaderStates_t[i].szReader = readers[i];
        rgReaderStates_t[i].dwCurrentState = SCARD_STATE_UNAWARE;
    }
     rgReaderStates_t[NoofReaders].szReader = "\\\\?PnP?\\Notification";
     rgReaderStates_t[NoofReaders].dwCurrentState = SCARD_STATE_UNAWARE;

 /* Wait endlessly for all events in the list of readers
  * We only stop in case of an error
  */
    if (pnp)
    {
        timeout = INFINITE;
        NoofReaders++;
    }
    else
        timeout = TIMEOUT;

    rv = SCardGetStatusChange(hContext, timeout, rgReaderStates_t, NoofReaders);
//    usleep(1);

    while (((rv == SCARD_S_SUCCESS) || (rv == SCARD_E_TIMEOUT)) && connected)
    {
        cardStatus.clear();
        if (pnp)
        {
            if (rgReaderStates_t[NoofReaders-1].dwEventState &
                                    SCARD_STATE_CHANGED)
                goto get_readers;
        }
        else
        {
            /* A new reader appeared? */
            if ((SCardListReaders(hContext, NULL, NULL, &dwReaders)
                                    == SCARD_S_SUCCESS) && (dwReaders != dwReadersOld))
                goto get_readers;
        }

        /* Now we have an event, check all the readers in the list to see what
         * happened */
        for (int current_reader=0; current_reader < NoofReaders; current_reader++)
        {
            time_t t;

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_CHANGED)
            {
                /* If something has changed the new state is now the current
                     * state */
                rgReaderStates_t[current_reader].dwCurrentState =
                           rgReaderStates_t[current_reader].dwEventState;
            }
            else
                /* If nothing changed then skip to the next reader */
                continue;

            /* From here we know that the state for the current reader has
             * changed because we did not pass through the continue statement
             * above.
             */

            /* Timestamp the event as we get notified */
            t = time(NULL);

            /* Specify the current reader's number and name */

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_IGNORE)
                    cardStatus = cardStatus + "Ignore this reader ";

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_UNKNOWN)
            {
                cardStatus = cardStatus + "Reader unknown";
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_UNAVAILABLE)
                    cardStatus = cardStatus + "Status unavailable ";

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_EMPTY)
            {
                cardStatus = cardStatus + "Card removed, ";
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_PRESENT)
            {
                cardStatus = cardStatus + "Card inserted, ";
                CardPresent = true;
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_ATRMATCH)
                    cardStatus = cardStatus + "ATR matches card, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_EXCLUSIVE)
                    cardStatus = cardStatus + "Exclusive Mode, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_INUSE)
                    cardStatus = cardStatus + "Shared Mode, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                                                SCARD_STATE_MUTE)
                    cardStatus = cardStatus + "Unresponsive card, ";

            /* force display */
            fflush(stdout);

            /* Also dump the ATR if available */
            if(rgReaderStates_t[current_reader].cbAtr > 0)
            {
                if(rgReaderStates_t[current_reader].cbAtr)
                {
                    for(i=0; i<rgReaderStates_t[current_reader].cbAtr; i++)
                        sprintf(&atr[i*3], "%02X ", rgReaderStates_t[current_reader].rgbAtr[i]);

                    atr[i*3-1] = '\0';
                }
                else
                    atr[0] = '\0';

                curr_atr = QString(atr);
                /* force display */
            }

            if(CardPresent)
            {
                CardPresent = false;
                Reader = QString(rgReaderStates_t[current_reader].szReader);
                Cardstat = cardStatus;
                ATR = curr_atr;

                /* SCardConnect -> Establishes a connection to the reader specified in * mszReaders. */

                l_i_readcount = 0;
                do
                {
                    msleep(200);
                    rv = SCardConnect(hContext, rgReaderStates_t[current_reader].szReader, SCARD_SHARE_SHARED,
                                                              SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
                    l_i_readcount++;

                }while(SCARD_S_SUCCESS != rv && l_i_readcount != 3);
                if (SCARD_S_SUCCESS == rv)
                {
                    switch(dwActiveProtocol)
                    {
                    case SCARD_PROTOCOL_T0:
                        pioSendPci = *SCARD_PCI_T0;
                        break;

                    case SCARD_PROTOCOL_T1:
                        pioSendPci = *SCARD_PCI_T1;
                        break;
                    }
                    l_i_readcount = 0;
                    do
                    {
                        l_bool_result = PerformTransmitAPDU(cmd1, sizeof(cmd1));
                        if(!l_bool_result)
                        {
//                            qDebug()<<"\rinside read fail";
                            LastError = UID;
                            l_i_readcount++;
                            msleep(200);
                        }
                        else
                        {
                            UID = QByteArray(RxedData.toLatin1()).toHex();
                        }
                    }while(l_i_readcount != 5 && !l_bool_result);

                    /*SCardDisconnect -> Terminates a connection made through SCardConnect().  */
                    rv = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
//                    if(SCARD_S_SUCCESS != rv)
//                    {
//                        UID = "<font color:red>Error: "+ QString(pcsc_stringify_error(rv)) + "</font>";
//                        emit state_changed(true);
//                    }
                }
                else
                {
                    UID = "<font color:red>Error: "+ QString(pcsc_stringify_error(rv)) + "</font>";
                }

                emit state_changed(true);
            }
            else
            {
                Reader = QString(rgReaderStates_t[current_reader].szReader);
                Cardstat = cardStatus;
                ATR = curr_atr;
                UID = "";
                emit state_changed(true);
            }
        } /* for */

        /*SCardGetStatusChange -> Blocks execution until the current availability of the cards in a specific set of readers changes. */
        rv = SCardGetStatusChange(hContext, timeout, rgReaderStates_t, NoofReaders);
//        usleep(1);
    } /* while */
    /* If we get out the loop, GetStatusChange() was unsuccessful */
    CHECK_CL("SCardGetStatusChange", rv);
}

bool SC_CLthread::PerformTransmitAPDU(BYTE cmd1[], unsigned long size)
{
    DWORD dwRecvLength = sizeof(pbRecvBuffer);

    /*SCardTransmit -> Sends an APDU to the smart card contained in the reader connected to by SCardConnect(). */

    LONG rv = SCardTransmit(hCard, &pioSendPci, cmd1, size,
                                 0, pbRecvBuffer, &dwRecvLength);
    if (SCARD_S_SUCCESS != rv)
    {
        UID = "SCardTransmit: "+ QString(pcsc_stringify_error(rv));
        return false;
    }
    RxedData.clear();

    for(unsigned int i=0; i<dwRecvLength-2; i++)
        RxedData.append(QString(1, QChar(pbRecvBuffer[i])));

    return true;
}

void SC_CLthread::thread_terminate()
{
    connected = false;

    /*SCardCancel -> his function cancels all pending blocking requests on the SCardGetStatusChange() function.  */
    if(!isError)
    {
        disconnect(this, SIGNAL(finished()), 0, 0);
        rv = SCardCancel (hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            LastError =  QString("") + QString(pcsc_stringify_error(rv));
            isError = true;
        }
    }

    if(isRunning())
    {
        exit();
        wait();
    }

    /* free memory possibly allocated */
    if (NULL != readers)
        free(readers);
    if (NULL != rgReaderStates_t)
    {
        free(rgReaderStates_t);
    }

    #ifdef SCARD_AUTOALLOCATE

    /*SCardFreeMemory -> Releases memory that has been returned from the resource manager using the SCARD_AUTOALLOCATE length designator.  */
    if (mszReaders)
    {
        rv = SCardFreeMemory(hContext, mszReaders);
        if(SCARD_S_SUCCESS != rv)
        {
            LastError =  QString("SCardFreeMemory ") + QString(pcsc_stringify_error(rv));
            isError = true;
        }
    }
    else
        rv = SCARD_S_SUCCESS;

    /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
    rv = SCardReleaseContext(hContext);
    if(SCARD_S_SUCCESS != rv)
    {
        LastError =  QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        isError = true;
    }

    system("rm /var/run/pcsc/* -R");

    #else
        free(mszReaders);
    #endif


    if(isFinished() && isError)
    {
       emit error_close();
    }
}
