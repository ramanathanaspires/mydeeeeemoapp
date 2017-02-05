#include "gadgets.h"
#include "ui_gadgets.h"
#include<QKeyEvent>
#include<QMessageBox>
#include<QDebug>
#include <QProcess>
#include <GlobalClass.h>
#include <csettingsfiles.h>
using namespace Globalclass ;

GADGETS::GADGETS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GADGETS)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("UsbGadgets");
    setFocusPolicy(Qt::NoFocus);
    setWindowFlags(Qt::FramelessWindowHint);
    g_ccmainObj->serverMethod()->GadgetConfiguration(Gadeget,MassStorage);
    ui->pushButtonUsbIp->hide();
    ui->pushButtonUsbIp->setAutoDefault(true);
    ui->pushButtonOk->setAutoDefault(true);
    ui->pushButtonOk->setText("Ok");
    ui->pushButtonOk->setShortcut(Qt::Key_F2);
    ui->pushButton->setShortcut(Qt::Key_F2);
    ui->pushButtonusbExit->setShortcut(Qt::Key_F4);
    ui->label->setAlignment(Qt::AlignCenter);


    g_ccmainObj->EnableExternalUSB(true);//Testing

    if( g_ccmainObj->serverMethod()->getUSBON_OFF())
    {
        busbFlag = false;
        ui->pushButtonUSBONOFF->setText("ON");
        ui->pushButtonUSBONOFF->setStyleSheet("background-color:green");
        ui->groupBoxUsb_2->setEnabled(true);
    }
    else
    {
        busbFlag = true;
        ui->pushButtonUSBONOFF->setText("OFF");
        ui->pushButtonUSBONOFF->setStyleSheet("background-color:red");
        ui->groupBoxUsb_2->setEnabled(false);
    }
    switch(Gadeget)
    {
    case 0:
        ui->radioButtonSerial->setFocus();
        ui->radioButtonSerial->setChecked(true);
        break;
    case 1:
        ui->radioButtonUSB->setFocus();
        ui->radioButtonUSB->setChecked(true);
        ui->pushButtonUsbIp->show();
        ui->pushButtonUsbIp->setFocus();
        break;
    case 2:
//        if(MassStorage==1)
//        {
//            ui->radioButtonPendrive->setFocus();
//            ui->radioButtonPendrive->setChecked(true);
//            break;
//        }
        if(MassStorage==2)
        {
            ui->radioButtonSDCard->setFocus();
            ui->radioButtonSDCard->setChecked(true);
            break;
        }
    case 3:
        ui->radioButtonnormal->setFocus();
        ui->radioButtonnormal->setChecked(true);
        break;
    default:
        ui->radioButtonSerial->setFocus();
        ui->radioButtonSerial->setChecked(true);
        break;
    }
    ui->groupBoxUsb->hide();
    ui->groupBoxUsb_2->show();
    ui->pushButtonUSBONOFF->setFocus();
}

GADGETS::~GADGETS()
{
    delete ui;
}
void GADGETS::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key()== Qt::Key_Escape)
    {
        if(ui->groupBoxUsb->isVisible() == true)
        {
            ui->groupBoxUsb->setVisible(false);
            ui->groupBoxUsb_2->setVisible(true);
        }
        else
        {
            g_ccmainObj->EnableExternalUSB(false);//Testing
            this->close();
        }
    }
    if(keyevent->key()==Qt::Key_Down)
    {
        if(ui->radioButtonnormal->isChecked())
        {
            ui->radioButtonSerial->setFocus();
            ui->radioButtonSerial->setChecked(true);
        }
    }
    if(keyevent->key()==Qt::Key_Up)
    {
        if(ui->radioButtonSerial->isChecked())
        {
            ui->radioButtonnormal->setFocus();
            ui->radioButtonnormal->setChecked(true);
        }
    }
}


void GADGETS::on_pushButtonOk_clicked()
{
    if(QMessageBox::information(0,"USBGadget",
                                "Are you sure to shutdown the device",
                                QMessageBox::Yes |QMessageBox::No
                                )==QMessageBox::Yes)
    {
        if(ui->radioButtonSerial->isChecked())
        {
            Gadeget=eSerial_USBMode;
            MassStorage=eNone;
            g_ccmainObj->serverMethod()->setGadgetConfiguration(Gadeget,MassStorage);
            system(QString("cp /usr/share/gadget/gadgetserial.sh /etc/init.d/S35gadget").toLatin1());
            system(QString("cp /usr/share/gadget/inittab.serial /etc/inittab").toLatin1());
        }
        else if(ui->radioButtonUSB->isChecked())
        {
            Gadeget=eUSB_GadgetMode;
            MassStorage=eNone;
            g_ccmainObj->serverMethod()->setGadgetConfiguration(Gadeget,MassStorage);
            system(QString("cp /usr/share/gadget/gadgetether.sh /etc/init.d/S35gadget").toLatin1());
        }
        else if(ui->radioButtonSDCard->isChecked())
        {
            Gadeget=eMass_StorageMode;
            MassStorage=eSDCard;
            g_ccmainObj->serverMethod()->setGadgetConfiguration(Gadeget,MassStorage);
            system(QString("cp /usr/share/gadget/gadgetmmc.sh /etc/init.d/S35gadget").toLatin1());
        }
        else if(ui->radioButtonnormal->isChecked())
        {
            Gadeget=eNormal_StorageMode;
            MassStorage=eNone;
            g_ccmainObj->serverMethod()->setGadgetConfiguration(Gadeget,MassStorage);
            system(QString("rm /etc/init.d/S35gadget").toLatin1());
            system(QString("cp /usr/share/gadget/inittab.normal /etc/inittab").toLatin1());
        }
        g_ccmainObj->shutDown();
    }
    else
    {
        return;
    }
}


void GADGETS::on_pushButtonUsbIp_clicked()
{
    ui->labelText->setAlignment(Qt::AlignCenter);
    ui->lineEditUsb->setValidator(new QIntValidator(ui->lineEditUsb));
    ui->lineEditUsb->setInputMask("000.000.000.000");
    ui->lineEditHost->setValidator(new QIntValidator(ui->lineEditHost));
    ui->lineEditHost->setInputMask("000.000.000.000");

    ui->pushButton->setAutoDefault(true);
    ui->pushButtonusbExit->setAutoDefault(true);

    ui->lineEditUsb->setFocus();
    ui->groupBoxUsb_2->hide();
    ui->groupBoxUsb->show();
    ui->pushButtonOk->setFocus();
}

void GADGETS::on_pushButton_clicked()
{
    usbip = ui->lineEditUsb->text();
    hostip = ui->lineEditHost->text();
    if(usbip == "...")
    {
        QMessageBox::information(0,"USBGadget","Enter USB ip Configuration");
    }
    else if(hostip == "...")
    {
        QMessageBox::information(0,"USBGadget ","Enter HOST ip Configuration");
    }
    else if(usbip == hostip)
    {
        QMessageBox::information(0,"USBGadget ","Both the IP's are same");
    }
    else
    {
            usbip = "ifconfig usb0 "+usbip;
            system(usbip.toLatin1());
            QString gatewayip="route add default gw ";
            QString copycmd=gatewayip +hostip;
            const char *ch1;
            ch1 = copycmd.toLatin1();
            system(QString(ch1).toLatin1());

            QProcess process;
            process.setProcessChannelMode(QProcess::SeparateChannels);
            process.start("ping -c 2 "+hostip);
            while(process.state() == QProcess::Running || process.state() == QProcess::Starting)
            {
                if(process.waitForFinished(1000))
                {
                    QString strOutput = QString(process.readAllStandardOutput());
                    if(strOutput.contains("100% packet loss"))
                    {

                        QMessageBox::information(0,"USBGadget","Ping process fail");
                    }
                    else
                    {
                        QMessageBox::information(0,"USBGadget","ping process success");
                    }
                }

            }
    }
    ui->groupBoxUsb->hide();
    ui->groupBoxUsb_2->show();
}

void GADGETS::on_pushButtonusbExit_clicked()
{
    ui->groupBoxUsb->hide();
    ui->groupBoxUsb_2->show();
}

void GADGETS::on_lineEditUsb_returnPressed()
{
    if(ui->lineEditUsb->text() != "")
        ui->lineEditHost->setFocus();
    else
        ui->lineEditUsb->setFocus();
}

void GADGETS::on_lineEditHost_returnPressed()
{
    if(ui->lineEditHost->text() != "")
        ui->pushButton->setFocus();
    else
        ui->lineEditHost->setFocus();
}

void GADGETS::on_pushButtonUSBONOFF_clicked()
{
    if(busbFlag)
    {
        busbFlag = false;
        ui->pushButtonUSBONOFF->setText("ON");
        ui->pushButtonUSBONOFF->setStyleSheet("background-color:green");
        ui->groupBoxUsb_2->setEnabled(true);
        g_ccmainObj->EnableHub(true);
    }
    else
    {
        busbFlag = true;
        ui->pushButtonUSBONOFF->setText("OFF");
        ui->pushButtonUSBONOFF->setStyleSheet("background-color:red");
        ui->groupBoxUsb_2->setEnabled(false);
        g_ccmainObj->EnableHub(false);
    }
}
