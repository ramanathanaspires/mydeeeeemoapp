#include "smartcard_contactless.h"
#include "ui_smartcard_contactless.h"
#include <QMessageBox>
#include <QDebug>
//#include <QMutex>
#include <QKeyEvent>

#include "GlobalClass.h"
using namespace Globalclass;

#include "nfc_api.h"
using namespace global_NFC;

/********************************************************************************
                        Contactless Smartcard
class to show NFC reader details & to list (NFC) ISO14443A tag details like UID & ATR
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
    ui->lblTarget->setWordWrap(true);
    ui->lblReader->setWordWrap(true);
    ui->lblUID->setWordWrap(true);
    obj_thrd = new SC_CLthread;
    if(obj_thrd->connected)
    {
        connect(obj_thrd, SIGNAL(state_changed()), this, SLOT(slot_stateChanged()));
        connect(obj_thrd, SIGNAL(error_close()), this, SLOT(slotclose()));
        ui->lblReader->setText(obj_thrd->Reader);
        obj_thrd->start();
    }
    else
    {
        QMessageBox::critical(0, "RFID", obj_thrd->LastError);
        isError = true;
    }
    ui->groupBox->setFocus();
}

smartcard_contactless::~smartcard_contactless()
{
    delete ui;
}

void smartcard_contactless::slot_stateChanged()
{
    ui->lblATR->setText(obj_thrd->ATR);
    ui->lblTarget->setText(obj_thrd->Target);
    ui->lblUID->setText(obj_thrd->UID);
    ui->lblReader->setText(obj_thrd->Reader);
}


void smartcard_contactless::slotclose()
{
    if(obj_thrd->isError)
    {
        QMessageBox::critical(0, "RFID Read", obj_thrd->LastError);
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
//                         Contact less NFC reader thread
//in this class, thread concept is used to poll reapeatedly at 1sec interval for
//ISO14443A (MIFARE) tag, if the target found, the public variables Target, ATR & UID
//will be updated with corresponding details
/********************************************************************************/

SC_CLthread::SC_CLthread()
{
    connected = false;
    isError = false;
    connect(this, SIGNAL(finished()), this, SLOT(thread_terminate()));

//----- connect NFC device
    if(connectNFC(&Reader) != EXIT_SUCCESS)
    {
        isError = true;
        LastError = g_str_lastError;
        return;
    }

    qDebug()<<"connection success";
    connected = true;
}

void SC_CLthread::run()
{
    while(connected)
    {
        ATR.clear();
        UID.clear();

//----- Read UID, ATR & Target
        if(!nfcReadUID(&ATR, &UID, &Target))
        {
            isError = true;
            LastError = g_str_lastError;
            break;
        }
        emit state_changed();
        msleep(800);
    }

//----- Disconnect NFC device
    disconnectNFC();
}   

void SC_CLthread::thread_terminate()
{
    connected = false;

    if(!isError)
    {
        disconnect(this, SIGNAL(finished()), 0, 0);
    }

    sleep(2);

    if(isRunning())
    {
        exit();
        wait();
    }

    if(isFinished() && isError)
    {
       emit error_close();
    }
}
