#include "SmartCard.h"
#include "ui_SmartCard.h"
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include "GlobalClass.h"

using namespace Globalclass;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define TIMEOUT 1000	/* 1 second timeout */

/* command used to parse (on screen) the ATR */
#define ATR_PARSER "ATR_analysis"

#ifndef SCARD_E_NO_READERS_AVAILABLE
#define SCARD_E_NO_READERS_AVAILABLE 0x8010002E
#endif

//#define TIME_BEFORE_SUICIDE 30

#define CHECK(f, rv) \
    do \
{ \
    if (rv != SCARD_S_SUCCESS ) \
{ \
    LastErr = QString(f) + " " + QString(pcsc_stringify_error(rv)); \
    (void)SCardReleaseContext(hContext); \
    return false; \
    } \
    } while(0);

#define CHECK_C(f , rv, hContext) \
    do { \
    if (SCARD_S_SUCCESS != rv) \
{ \
    if (SCARD_E_CANCELLED != rv) \
{ \
    LastError =  QString(f) + " " + QString(pcsc_stringify_error(rv)); \
    isError = true; \
    goto release_resource; \
    } \
    } \
    } while(0)

/********************************************************************************
                        Contactless Smartcard
To communicate with smart card readers from source code PC/SC lite API calls are
used, for more information on pc/sc lite API reference visit,
            -http://pcsclite.alioth.debian.org/pcsc-lite/
            -http://pcsclite.alioth.debian.org/api/group__API.html
********************************************************************************/
SmartCard::SmartCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmartCard)
{
    ui->setupUi(this);
    setParent(MdiArea);
    isError = false;
    strUserID_old = "";
    strUserName_old = "";
    strMobileNo_old = "";
    strCity_old = "";
    ui->labelCardMode->setText("SAM");
    ui->lblCardstat->hide();
    ui->name_lblCardstat->hide();
    ui->btn_Read->setVisible(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    move(0,0);
    ui->pushButtonSam->setAutoDefault(true);
    ui->pushButtonSmartcard1->setAutoDefault(true);
    ui->pushButtonSmartcard2->setAutoDefault(true);
    ui->lblATR->setWordWrap(true);
    ui->lblCardstat->setWordWrap(true);
    obj_thrd = new SC_thread;
    if(obj_thrd->connected)
    {
        connect(obj_thrd, SIGNAL(state_changed(int)), this, SLOT(slot_stateChanged(int)));
        connect(obj_thrd, SIGNAL(error_close()), this, SLOT(slotclose()));
        obj_thrd->start();
    }
    else
    {
        QMessageBox::critical(0, "SAM/Smartcard", obj_thrd->LastError);
        isError = true;
    }
    QRegExp re( "^[0-9]{10}$" );
    QRegExpValidator *validator = new QRegExpValidator( re, 0 );

    ui->txt_MobileNo->setValidator( validator );

    ui->grpBx_data->setVisible(false);
    ui->grpBx_main->setVisible(true);
    ui->btn_Read->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->cmb_ReaderName->setFocus();
}

SmartCard::~SmartCard()
{
    delete ui;
}

void SmartCard::slot_stateChanged(int index)
{
    QMutex mutex;
    mutex.lock();
    if(ui->grpBx_data->isVisible())
    {
        on_btnClose_clicked();
    }
    ui->cmb_ReaderName->clear();
    if(-1 != index)
    {
        ui->cmb_ReaderName->addItems(obj_thrd->strlstReaders);
        ui->lblATR->setText(obj_thrd->strlstATR.at(index));
        ui->lblCardstat->setText(obj_thrd->strlstCardstat.at(index));
        ui->cmb_ReaderName->setCurrentIndex(index);
        if(obj_thrd->strlstCardPresent.size() > 0)
        {
            ui->btn_Read->setEnabled(true);
            ui->btn_Read->setFocus();
        }
        else
            ui->btn_Read->setEnabled(false);
    }
    else
    {
        ui->cmb_ReaderName->addItem("No Reader found..");
        ui->lblATR->setText("");
        ui->lblCardstat->setText("");
        ui->btn_Read->setEnabled(false);
    }
    mutex.unlock();
}

void SmartCard::on_btn_Read_clicked()
{
    setEnabled(false);
    if(Read_SmartCard(ui->cmb_ReaderName->currentText()))
    {
        connect(ui->txt_UserID, SIGNAL(textChanged(QString)), this, SLOT(txt_UserID_textChanged(QString)));
        connect(ui->txt_UserName, SIGNAL(textChanged(QString)), this, SLOT(txt_UserName_textChanged(QString)));
        connect(ui->txt_MobileNo, SIGNAL(textChanged(QString)), this, SLOT(txt_MobileNo_textChanged(QString)));
        connect(ui->txtCity, SIGNAL(textChanged(QString)), this, SLOT(txtCity_textChanged(QString)));
        ui->grpBx_data->setVisible(true);
        ui->grpBx_main->setVisible(false);
        setEnabled(true);
        ui->btnClose->setFocus();
    }else
    {
        setEnabled(true);
        ui->btn_Read->setFocus();
        QMessageBox::critical(0, "Read/Write", LastErr);
    }
    qApp->processEvents();
}

void SmartCard::on_cmb_ReaderName_currentIndexChanged(int index)
{
    setEnabled(false);
    if(index >= 0 && index < obj_thrd->strlstATR.size())
    {
        if(prevIndex != index)
        {
            on_btnClose_clicked();
            ui->lblATR->setText(obj_thrd->strlstATR.at(index));
            ui->lblCardstat->setText(obj_thrd->strlstCardstat.at(index));
        }
        prevIndex = index;
    }
    setEnabled(true);
    if(ui->btn_Read->isEnabled())
        ui->btn_Read->setFocus();
    else
        ui->cmb_ReaderName->setFocus();
}

void SmartCard::on_btnSave_clicked()
{
    setEnabled(false);
    if(ui->txt_UserID->text() == "")
    {
        QMessageBox::critical(0, "SAM/SmartCard","Please enter user id before Save");
        setEnabled(true);
        ui->txt_UserID->setFocus();
        return;
    }
    else if(ui->txt_UserName->text() == "")
    {
        QMessageBox::critical(0, "SAM/SmartCard","Please enter user name before Save");
        setEnabled(true);
        ui->txt_UserName->setFocus();
        return;
    }
    else if(ui->txt_MobileNo->text() == "")
    {
        QMessageBox::critical(0, "SAM/SmartCard","Please enter mobile no before Save");
        setEnabled(true);
        ui->txt_MobileNo->setFocus();
        return;
    }
    else if(ui->txtCity->text() == "")
    {
        QMessageBox::critical(0, "SAM/SmartCard","Please enter city before Save");
        setEnabled(true);
        ui->txtCity->setFocus();
        return;
    }

    if(Write_SmartCard(ui->cmb_ReaderName->currentText()))
    {
        QMessageBox::information(0, "SAM/SmartCard", "Write success...");
        ui->txt_UserID->clear();
        ui->txt_UserName->clear();
        ui->txt_MobileNo->clear();
        ui->txtCity->clear();
        strUserID_old.clear();
        strUserName_old.clear();
        strMobileNo_old.clear();
        strCity_old.clear();
        ui->btnSave->setEnabled(false);

        ui->grpBx_data->setVisible(false);
        ui->grpBx_main->setVisible(true);
        setEnabled(true);
        ui->btn_Read->setFocus();

    }else
    {
        QMessageBox::critical(0, "Read/Write ", LastErr);
        setEnabled(true);
        ui->btnSave->setFocus();
    }
}

void SmartCard::on_btnClose_clicked()
{
    setEnabled(false);
    disconnect(ui->txt_UserID, SIGNAL(textChanged(QString)), 0, 0);
    disconnect(ui->txt_UserName, SIGNAL(textChanged(QString)), 0, 0);
    disconnect(ui->txt_MobileNo, SIGNAL(textChanged(QString)), 0, 0);
    disconnect(ui->txtCity, SIGNAL(textChanged(QString)), 0, 0);
    ui->grpBx_data->setVisible(false);
    ui->grpBx_main->setVisible(true);
    ui->txt_UserID->clear();
    ui->txt_UserName->clear();
    ui->txt_MobileNo->clear();
    ui->txtCity->clear();
    strUserID_old.clear();
    strUserName_old.clear();
    strMobileNo_old.clear();
    strCity_old.clear();
    ui->btnSave->setEnabled(false);
    setEnabled(true);
    ui->btn_Read->setFocus();
}

void SmartCard::txt_UserID_textChanged(QString textchanged)
{
    if(textchanged != strUserID_old)
    {
        if(!ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(true);
        }
    }
    else
    {
        if(ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(false);
        }
    }
}

void SmartCard::txt_UserName_textChanged(QString textchanged)
{
    if(textchanged != strUserName_old)
    {
        if(!ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(true);
        }
    }
    else
    {
        if(ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(false);
        }
    }
}

void SmartCard::txt_MobileNo_textChanged(QString textchanged)
{
    if(textchanged != strMobileNo_old)
    {
        if(!ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(true);
        }
    }
    else
    {
        if(ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(false);
        }
    }
}

void SmartCard::txtCity_textChanged(QString textchanged)
{
    if(textchanged != strCity_old)
    {
        if(!ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(true);
        }
    }
    else
    {
        if(ui->btnSave->isEnabled())
        {
            ui->btnSave->setEnabled(false);
        }
    }
}

void SmartCard::slotclose()
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

void SmartCard::keyPressEvent(QKeyEvent *e)
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

bool SmartCard::Read_SmartCard(QString Reader)
{
    QMutex mut_connect;
    mut_connect.lock();

    LONG rv;
    SCARDCONTEXT hContext;
    SCARDHANDLE hCard;
    SCARD_IO_REQUEST pioSendPci;
    LPTSTR mszReaders = NULL;
    DWORD dwActiveProtocol;

    BYTE cmd1[] = { 0x80, 0x20, 0x07, 0x00, 0x08, 0x41,         //issuer code of card
                    0x43, 0x4F, 0x53, 0x54, 0x45, 0x53, 0x54 };

    /*SCardEstablishContext -> Creates an Application Context to the PC/SC Resource Manager. */

    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, 0, 0, &hContext);
    CHECK("SCardEstablishContext", rv)

            if (mszReaders != NULL)
    {
        free(mszReaders);
        mszReaders = NULL;
    }

    mszReaders = (char*) malloc(sizeof(char)*Reader.size());
    if (mszReaders == NULL)
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);

        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }

    strcpy(mszReaders, Reader.toLocal8Bit().data());
    qDebug("reader name: %s\n", mszReaders);

    /* SCardConnect -> Establishes a connection to the reader specified in * mszReaders. */
    rv = SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED,
                      SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
    CHECK("SCardConnect", rv)

            switch(dwActiveProtocol)
    {
        case SCARD_PROTOCOL_T0:
            pioSendPci = *SCARD_PCI_T0;
            break;

        case SCARD_PROTOCOL_T1:
            pioSendPci = *SCARD_PCI_T1;
            break;
    }

    if(!PerformTransmitAPDU(hCard, &pioSendPci, cmd1, sizeof(cmd1)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);
        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }

    // Select file Hi address & Low address

    BYTE Data[7];
    Data[0] = 0x080;        // CLA
    Data[1] = 0x0A4;        // INS
    Data[2] = 0x00;         // P1
    Data[3] = 0x00;         // P2
    Data[4] = 0x02;         // P3

    Data[5] = 0xAA;         // Value of High Byte
    Data[6] = 0x90;         // Value of Low Byte

    if(!PerformTransmitAPDU(hCard, &pioSendPci, Data, sizeof(Data)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);
        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }

    BYTE Data1[5];
    Data1[0] = 0x80;         // CLA
    Data1[1] = 0xB2;         // INS
    Data1[2] = 0x00;         // Record No
    Data1[3] = 0x00;         // P2
    Data1[4] = 0xFA;         // Length of Data

    if(!PerformTransmitAPDU(hCard, &pioSendPci, Data1, sizeof(Data1)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);
        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }
    if(RxedData != "")
    {

        QStringList strlstTemp = RxedData.simplified().split("!&");
        if(strlstTemp.size() == 4 )
        {
            ui->txt_UserID->setText(strlstTemp.at(0));
            ui->txt_UserName->setText(strlstTemp.at(1));
            ui->txt_MobileNo->setText(strlstTemp.at(2));
            ui->txtCity->setText(QString(strlstTemp.at(3)));
            strUserID_old = strlstTemp.at(0);
            strUserName_old = strlstTemp.at(1);
            strMobileNo_old = strlstTemp.at(2);
            strCity_old = strlstTemp.at(3);
        }
        else
        {
            QMessageBox::information(0, "SAM/SmartCard ", "No data available on the card...");
        }
        strlstTemp.clear();
        RxedData.clear();
    }
    else
    {
        QMessageBox::information(0, "SAM/SmartCard", "No data available on the card...");
    }

    SCardDisconnect(hCard, 0);

    /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
    free(mszReaders);

    rv = SCardReleaseContext(hContext);
    if(SCARD_S_SUCCESS != rv)
    {
        qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        isError = true;
    }

    mut_connect.unlock();
    return true;
}

bool SmartCard::Write_SmartCard(QString Reader)
{
    QMutex mut_connect;
    mut_connect.lock();

    LONG rv;
    SCARDCONTEXT hContext;
    SCARDHANDLE hCard;
    SCARD_IO_REQUEST pioSendPci;
    LPTSTR mszReaders = NULL;
    DWORD dwActiveProtocol;
    int i = 0;

    BYTE cmd1[] = { 0x80, 0x20, 0x07, 0x00, 0x08, 0x41,         //issuer code of card
                    0x43, 0x4F, 0x53, 0x54, 0x45, 0x53, 0x54 };


    /*SCardEstablishContext -> Creates an Application Context to the PC/SC Resource Manager. */

    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, 0, 0, &hContext);
    CHECK("SCardEstablishContext", rv)

            if (mszReaders != NULL)
    {
        free(mszReaders);
        mszReaders = NULL;
    }

    mszReaders = (char*) malloc(sizeof(char)*Reader.size());
    if (mszReaders == NULL)
    {
        qDebug("malloc: not enough memory\n");
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);
        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }

    strcpy(mszReaders, Reader.toLocal8Bit().data());

    /* SCardConnect -> Establishes a connection to the reader specified in * mszReaders. */
    rv = SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED,
                      SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
    CHECK("SCardConnect", rv)

            switch(dwActiveProtocol)
    {
        case SCARD_PROTOCOL_T0:
            pioSendPci = *SCARD_PCI_T0;
            break;

        case SCARD_PROTOCOL_T1:
            pioSendPci = *SCARD_PCI_T1;
            break;
    }

    if(!PerformTransmitAPDU(hCard, &pioSendPci, cmd1, sizeof(cmd1)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);

        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        return false;
    }

    BYTE Data1[7];
    Data1[0] = 0x080;        // CLA
    Data1[1] = 0x0A4;        // INS
    Data1[2] = 0x00;         // P1
    Data1[3] = 0x00;         // P2
    Data1[4] = 0x02;         // P3

    Data1[5] = 0xAA;         // Value of High Byte
    Data1[6] = 0x90;         // Value of Low Byte

    if(!PerformTransmitAPDU(hCard, &pioSendPci, Data1, sizeof(Data1)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);
        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        mut_connect.unlock();
        return false;
    }

    QByteArray ApduIn1;
    ApduIn1.append(ui->txt_UserID->text().simplified() + "!&" + ui->txt_UserName->text().simplified() + "!&" + ui->txt_MobileNo->text().simplified() + "!&" + ui->txtCity->text().simplified());
    int caseType;
    unsigned char RecNo, maxLen, DataLen;
    caseType = 0x00;
    RecNo = 0x00;
    maxLen = 0xFA;
    DataLen = 0xFA;
    BYTE Data[5 + maxLen];
    if (caseType == 1)    // If card data is to be erased before writing new data. Re-initialize card values to $00
    {

        Data[0] = 0x80;         // CLA
        Data[1] = 0xD2;         // INS
        Data[2] = RecNo;        // Record No
        Data[3] = 0x00;         // P2
        Data[4] = maxLen;       // Length of Data

        for (i = 0; i < maxLen; i++)
            Data[i+5] = ApduIn1.at(i);

        if(!PerformTransmitAPDU(hCard, &pioSendPci, Data, sizeof(Data)))
        {
            SCardDisconnect(hCard, 0);

            /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
            free(mszReaders);

            rv = SCardReleaseContext(hContext);
            if(SCARD_S_SUCCESS != rv)
            {
                qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
            }
            mut_connect.unlock();
            return false;
        }
    }

    //Write data to card
    Data[0] = 0x80;         // CLA
    Data[1] = 0xD2;         // INS
    Data[2] = RecNo;        // Record No
    Data[3] = 0x00;         // P2
    Data[4] = DataLen;     // Length of Data

    for (i = 0; i < maxLen; i++)
    {
        if(ApduIn1.size() > i )
        {
            Data[i + 5] = ApduIn1.at(i);
        }
        else
        {
            Data[i + 5] = 0x20;
        }
    }

    if(!PerformTransmitAPDU(hCard, &pioSendPci, Data, sizeof(Data)))
    {
        SCardDisconnect(hCard, 0);

        /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
        free(mszReaders);

        rv = SCardReleaseContext(hContext);
        if(SCARD_S_SUCCESS != rv)
        {
            qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
        }
        return false;
    }
    ApduIn1.clear();
    SCardDisconnect(hCard, 0);

    /*SCardReleaseContext -> Destroys a communication context to the PC/SC Resource Manager. */
    free(mszReaders);

    rv = SCardReleaseContext(hContext);
    if(SCARD_S_SUCCESS != rv)
    {
        qDebug()<<QString("SCardReleaseContext ") + QString(pcsc_stringify_error(rv));
    }
    mut_connect.unlock();
    return true;
}

bool SmartCard::PerformTransmitAPDU(SCARDHANDLE hCard,LPCSCARD_IO_REQUEST pioSendPci, BYTE cmd1[], unsigned long size)
{
    QMutexLocker locker(&mutex);
    BYTE pbRecvBuffer[256];
    DWORD dwRecvLength = sizeof(pbRecvBuffer);


    /*SCardTransmit -> Sends an APDU to the smart card contained in the reader connected to by SCardConnect(). */

    LONG rv = SCardTransmit(hCard, pioSendPci, cmd1, size,
                            0, pbRecvBuffer, &dwRecvLength);
    if (SCARD_S_SUCCESS != rv)
    {
        isError = true;
        QMessageBox::critical(0, "Read/Write ","SCardTransmit: "+ QString(pcsc_stringify_error(rv)));
        return false;
    }
    RxedData.clear();

    for(unsigned int i=0; i<dwRecvLength-2; i++)
        RxedData.append(QString(1, QChar(pbRecvBuffer[i])));
    return true;
}



/********************************************************************************/
//                         Contact less Smartcard thread
//in this class thread concept is used to check the reader status repetedly, if the
// status changed it will updated on the form
/********************************************************************************/

SC_thread::SC_thread()
{
    connected = false;
    isError = false;
    connect(this, SIGNAL(finished()), this, SLOT(thread_terminate()));

    connected = true;
}

void SC_thread::run()
{
    QString cardStatus, curr_atr;

    int current_reader;
    SCARDCONTEXT hContext = -1;
    LONG rv;
    SCARD_READERSTATE *rgReaderStates_t = NULL;
    SCARD_READERSTATE rgReaderStates[1];
    DWORD dwReaders = 0, dwReadersOld;
    DWORD timeout;
    LPSTR mszReaders = NULL;
    char *ptr, **readers = NULL;
    int i;
    char atr[MAX_ATR_SIZE*3+1];	/* ATR in ASCII */
    int pnp = TRUE;

    CardPresent = false;

get_readers:
    if(hContext == -1)
    {
        rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
        CHECK_C("SCardEstablishContext", rv, hContext);

        rgReaderStates[0].szReader = "\\\\?PnP?\\Notification";
        rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;

        rv = SCardGetStatusChange(hContext, 0, rgReaderStates, 1);
        if (rgReaderStates[0].dwEventState && SCARD_STATE_UNKNOWN)
        {
            qDebug("PnP reader name not supported. Using polling.\n");
            pnp = FALSE;
        }
    }
    else
    {
        rv = SCardIsValidContext(hContext);
        if(rv == SCARD_S_SUCCESS)
        {
            rv = SCardReleaseContext(hContext);
            hCont = -1;
        }
        else if(rv == SCARD_E_INVALID_HANDLE)
        {
            rv = SCardReleaseContext(hContext);
        }
        else
        {
            CHECK_C("SCardIsValidContext", rv, hContext);
        }
        rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
        CHECK_C("SCardEstablishContext", rv, hContext);
    }
    hCont = hContext;

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

    /* Retrieve the available readers list.
    *
    * 1. Call with a null buffer to get the number of bytes to allocate
    * 2. malloc the necessary storage
    * 3. call with the real allocated buffer
    */
    rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
    if (rv != SCARD_E_NO_READERS_AVAILABLE)
        CHECK_C("SCardListReaders", rv, hContext);

    dwReadersOld = dwReaders;

    /* if non NULL we came back so free first */
    if (mszReaders)
    {
        free(mszReaders);
        mszReaders = NULL;
    }

    mszReaders = (char*) malloc(sizeof(char)*dwReaders);
    if (mszReaders == NULL)
    {
        qDebug("malloc: not enough memory\n");
        isError = true;
        LastError = "malloc: not enough memory\n";
        return;
    }

    *mszReaders = '\0';
    rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);

    /* Extract readers from the null separated string and get the total
    * number of readers */

    NoofReaders = 0;
    ptr = mszReaders;
    while (*ptr != '\0')
    {
        ptr += strlen(ptr)+1;
        NoofReaders++;
    }


    if (SCARD_E_NO_READERS_AVAILABLE == rv || 0 == NoofReaders)
    {
        qDebug("\rWaiting for the first reader...");
        fflush(stdout);
        emit state_changed(-1);
        if (pnp)
        {
            rgReaderStates[0].szReader = "\\\\?PnP?\\Notification";
            rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;

            rv = SCardGetStatusChange(hContext, INFINITE, rgReaderStates, 1);
            CHECK_C("SCardGetStatusChange ", rv, hContext);
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
            goto release_resource;
        qDebug("found one\n");
        goto get_readers;
    }
    else
        CHECK_C("SCardListReader ", rv, hContext);

    readers = (char**) calloc(NoofReaders+1, sizeof(char *));
    if (NULL == readers)
    {
        qDebug("Not enough memory for readers table\n");
        return;
    }

    /* fill the readers table */
    strlstReaders.clear();
    strlstATR.clear();
    strlstCardPresent.clear();
    strlstCardstat.clear();
    NoofReaders = 0;
    ptr = mszReaders;
    while (*ptr != '\0')
    {
        qDebug("%d: %s\n", NoofReaders, ptr);
        readers[NoofReaders] = ptr;

        strlstReaders.append(QString(ptr));
        strlstATR.append(" ");
        strlstCardPresent.append(" ");
        strlstCardstat.append(" ");
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
    while (((rv == SCARD_S_SUCCESS) || (rv == SCARD_E_TIMEOUT)) && connected)
    {
        cardStatus.clear();
        curr_atr.clear();
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
        for (current_reader=0; current_reader < NoofReaders; current_reader++)
        {
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

            //        /* Timestamp the event as we get notified */
            //        t = time(NULL);

            /* Specify the current reader's number and name */

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_IGNORE)
                cardStatus =  cardStatus + "Ignore this reader ";

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_UNKNOWN)
            {
                cardStatus =  cardStatus + "Reader unknown";
                goto get_readers;
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_UNAVAILABLE)
                cardStatus =  cardStatus + "Status unavailable ";

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_EMPTY)
            {
                cardStatus =  cardStatus + "Card removed, ";
                CardPresent = false;
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_PRESENT)
            {
                cardStatus =  cardStatus + "Card inserted, ";
                CardPresent = true;
            }

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_ATRMATCH)
                cardStatus =  cardStatus + "ATR matches card, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_EXCLUSIVE)
                cardStatus =  cardStatus + "Exclusive Mode, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_INUSE)
                cardStatus =  cardStatus + "Shared Mode, ";

            if (rgReaderStates_t[current_reader].dwEventState &
                    SCARD_STATE_MUTE)
                cardStatus =  cardStatus + "Unresponsive card, ";

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
                fflush(stdout);
            }

            strlstCardstat.replace(current_reader, cardStatus);
            strlstATR.replace(current_reader, curr_atr);
            if(CardPresent)
            {
                strlstCardPresent.replace(current_reader, "true");
            }
            else
            {
                strlstCardPresent.replace(current_reader, "false");
            }
            cardStatus.clear();
            curr_atr.clear();
            emit state_changed(current_reader);
        } /* for */

        /*SCardGetStatusChange -> Blocks execution until the current availability of the cards in a specific set of readers changes. */
        rv = SCardGetStatusChange(hContext, timeout, rgReaderStates_t, NoofReaders);
    } /* while */

    /* If we get out the loop, GetStatusChange() was unsuccessful */
    CHECK_C("SCardGetStatusChange", rv, hContext);

release_resource:

    /* We try to leave things as clean as possible */
    rv = SCardReleaseContext(hContext);

    /* free memory possibly allocated */
    if (NULL != readers)
        free(readers);
    if (NULL != rgReaderStates_t)
        free(rgReaderStates_t);
    if(NULL != mszReaders)
        free(mszReaders);
}

void SC_thread::thread_start()
{
    connected = true;
    start();
}

void SC_thread::thread_terminate()
{
    if(connected)
        connected = false;

    if(isRunning())
    {
        if(!isError)
        {
            disconnect(this, SIGNAL(finished()), 0, 0);
            if(SCARD_S_SUCCESS != SCardCancel (hCont))
            {
                LastError =  QString("Error in scard cancel") ;
                isError = true;
            }
        }
        exit();
        wait();
    }
    if(isFinished() && isError)
        emit error_close();
}

//void SmartCard::on_cmb_Module_select_currentIndexChanged(const QString &arg1)
//{
//    if(arg1 == "SAM CARD")
//    {
//        ui->cmb_smartcard_slot->setEnabled(false);
//        g_ccmainObj->EnableSMARTCARDdModule(false);
//        g_ccmainObj->EnableSAMModule(true);
//    }
//    else
//    {
//        g_ccmainObj->EnableSAMModule(false);
//        g_ccmainObj->EnableSMARTCARDdModule(true);
//        g_ccmainObj->enableSmartCardSlot(ClanCor::eSmartCard_slot1);
//        ui->cmb_smartcard_slot->setEnabled(true);
//    }
//}

//void SmartCard::on_cmb_smartcard_slot_currentIndexChanged(const QString &arg1)
//{
//    if(arg1 == "SlotNo 1")
//    {
//        g_ccmainObj->enableSmartCardSlot(ClanCor::eSmartCard_slot1);
//    }
//    else
//    {
//        g_ccmainObj->enableSmartCardSlot(ClanCor::eSmartCard_slot2);
//    }
//}

void SmartCard::on_pushButtonSam_clicked()
{
    ui->lblATR->clear();
    g_ccmainObj->EnableSMARTCARDdModule(false);
    g_ccmainObj->EnableSAMModule(true);
     ui->labelCardMode->setText("SAM");
}

void SmartCard::on_pushButtonSmartcard1_clicked()
{
    ui->lblATR->clear();
    g_ccmainObj->EnableSmartCardSlot(ClanCor::eSmartCard_slot1);
    g_ccmainObj->EnableSMARTCARDdModule(true);
     ui->labelCardMode->setText("SMARTCARD1");
}

void SmartCard::on_pushButtonSmartcard2_clicked()
{
    ui->lblATR->clear();
    g_ccmainObj->EnableSmartCardSlot(ClanCor::eSmartCard_slot2);
    g_ccmainObj->EnableSMARTCARDdModule(true);
    ui->labelCardMode->setText("SMARTCARD2");
}
