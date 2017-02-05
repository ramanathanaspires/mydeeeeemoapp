#include "wifi_conf.h"
#include "ui_wifi_conf.h"
#include "GlobalClass.h"
using namespace Globalclass;
#include <QScrollArea>
#include <QFile>
#include <QBuffer>
#include <QMessageBox>

WIFI_Conf::WIFI_Conf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WIFI_Conf)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("WIFI Settings");
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    Prev_enc = CHHC80xxServer::eSecurityMode_NONE;
    Prev_key = "";
    QScrollArea *scr = new QScrollArea(this);
    scr->setWidget(ui->groupBox_Main);
    scr->setFixedSize(320,480);
    scr->setFocusPolicy(Qt::NoFocus);

    ui->cmbAdhoc->addItem("OFF");
    ui->cmbAdhoc->addItem("ON");

    ui->cmbEncryption->addItem("None");
    ui->cmbEncryption->addItem("WPA2 Personal");
    ui->cmbEncryption->addItem("WEP");

    ui->txtIPaddress->setValidator(new QIntValidator(ui->txtIPaddress));
    ui->txtIPaddress->setInputMask("000.000.000.000");
    ui->txtSubnet->setValidator(new QIntValidator(ui->txtSubnet));
    ui->txtSubnet->setInputMask("000.000.000.000");
    ui->txtGateway->setValidator(new QIntValidator(ui->txtGateway));
    ui->txtGateway->setInputMask("000.000.000.000");

    ui->txtKey->setEchoMode(QLineEdit::Password);
    g_ccmainObj->setKeypadMode(ClanCor::eKeypadMode_NUMERIC);
////    E_GadgetMode Gadeget;
////    E_MassStorage MassStorage;
//    g_ccmainObj->serverMethod()->GadgetConfiguration(Gadeget,MassStorage);
//    if(Gadeget == 3)
//    {

//    }

//    else
//    {
//        QMessageBox::information(0,"WIFI CONFIGURATION","Please set Normal mode in GADGET");
//        bWifiONOFFflag = true;
//        ui->BtnON_OFF->setText("OFF");
//        ui->BtnON_OFF->setStyleSheet("background-color:red");
//        ui->groupBox_Settings->setEnabled(true);
//    }
    CHHC80xxServer::SWifiNetwork wifiConfig;
    if(g_ccmainObj->serverMethod()->wifiConfig(wifiConfig))
    {
        qDebug()<<"\r serverMethod() if ";
        ui->txtIPaddress->setText(wifiConfig.m_strIpAddress);
        ui->txtSubnet->setText(wifiConfig.m_strSubnetMask);
        ui->txtGateway->setText(wifiConfig.m_strGateway);
        ui->txtSSID->setText(wifiConfig.m_strEssid);
        if( wifiConfig.m_bAdhoc == true) {
            qDebug()<<"\r serverMethod() if if ";
            ui->cmbAdhoc->setCurrentIndex(1);
        }
        if ( wifiConfig.m_eSecurity != CHHC80xxServer::eSecurityMode_NONE )
        {
            qDebug()<<"\r  if != none ";
            ui->cmbEncryption->setCurrentIndex((int) wifiConfig.m_eSecurity);
            Prev_enc = wifiConfig.m_eSecurity;
            Prev_key = wifiConfig.m_strKey;
            ui->txtKey->setText(wifiConfig.m_strKey);
        }
    }
    ui->groupBox_Settings->setEnabled(false);

    if(g_ccmainObj->serverMethod()->getWIFION_OFF())
    {
        qDebug()<<"\r serverMethod() get WIFI off() ifff ";
        bWifiONOFFflag = false;
        ui->BtnON_OFF->setText("ON");
        ui->BtnON_OFF->setStyleSheet("background-color:green");
        ui->groupBox_Settings->setEnabled(true);
    }
    else
    {
        qDebug()<<"\r serverMethod() get WIFI off() elseeee ";
        bWifiONOFFflag = true;
        ui->BtnON_OFF->setText("OFF");
        ui->BtnON_OFF->setStyleSheet("background-color:red");
        ui->groupBox_Settings->setEnabled(true);
    }

    connect(ui->txtIPaddress, SIGNAL(textChanged(QString)), this, SLOT(makeEnable()));
    connect(ui->txtSubnet, SIGNAL(textChanged(QString)), this, SLOT(makeEnable()));
    connect(ui->txtGateway, SIGNAL(textChanged(QString)), this, SLOT(makeEnable()));
    connect(ui->txtSSID, SIGNAL(textChanged(QString)), this, SLOT(makeEnable()));
    connect(ui->txtKey, SIGNAL(textChanged(QString)), this, SLOT(makeEnable()));
    connect(ui->cmbAdhoc, SIGNAL(currentIndexChanged(int)), this, SLOT(makeEnable()));

    ui->BtnOk->setEnabled(false);
    ui->txtKey->setEnabled(false);
    ui->BtnON_OFF->setAutoDefault(true);
    ui->BtnON_OFF->setFocus();
}
WIFI_Conf::~WIFI_Conf()
{
    delete ui;
}

void WIFI_Conf::on_BtnOk_clicked()
{
    setEnabled(false);
    QString IPaddr, Subnet, Gateway, Security, Ad_hoc;
    IPaddr = ui->txtIPaddress->text();
    Subnet = ui->txtSubnet->text();
    Gateway = ui->txtGateway->text();
    Security = "false";
    Ad_hoc = "false";
    if(IPaddr == "...")
    {
        QMessageBox::information(0,"Wireless Settings","Please enter IP address...");
        this->setEnabled(true);
        ui->txtIPaddress->setFocus();
        return;
    }
    else if(Subnet == "...")
    {
        QMessageBox::information(0,"Wireless Settings","Please enter subnet mask...");
        this->setEnabled(true);
        ui->txtSubnet->setFocus();
        return;
    }
    else if(Gateway == "...")
    {
        QMessageBox::information(0,"Wireless Settings","Please enter gateway...");
        this->setEnabled(true);
        ui->txtGateway->setFocus();
        return;
    }
    else if(ui->txtSSID->text() == "")
    {
        QMessageBox::information(0,"Wireless Settings","Please enter SSID...");
        this->setEnabled(true);
        ui->txtSSID->setFocus();
        return;
    }
    else if(ui->cmbEncryption->currentIndex() > 0)
    {
        Security = "true";
        if(ui->txtKey->text() == "")
        {
            QMessageBox::information(0,"Wireless Settings","Please enter key...");
            this->setEnabled(true);
            ui->txtKey->setFocus();
            return;
        }
        if(ui->cmbEncryption->currentText() == "WPA2 Personal")
        {
            if(ui->txtKey->text().length() < 8)
            {
                QMessageBox::information(0,"Wireless Settings","Key length must be 8 - 63 characters...");
                this->setEnabled(true);
                ui->txtKey->setFocus();
                return;
            }
        }
        else if(ui->cmbEncryption->currentText() == "WEP")
        {
            if(ui->txtKey->text().length() != 10 && ui->txtKey->text().length() != 26 )
            {
                QMessageBox::information(0,"Wireless Settings","Key length must be 10 or 26 characters allowed...");
                this->setEnabled(true);
                ui->txtKey->setFocus();
                return;
            }
        }
    }

    if(ui->cmbAdhoc->currentIndex() > 0)
    {
        Ad_hoc = "true";
    }
    bool Adhoc = false;
    if(Ad_hoc == "true")
        Adhoc = true;

    CHHC80xxServer::E_SecurityMode mode;
    if(ui->cmbEncryption->currentIndex() >= 0)
    {
        mode = ( CHHC80xxServer::E_SecurityMode) ui->cmbEncryption->currentIndex();
    }
    else
    {
        mode = CHHC80xxServer::eSecurityMode_NONE;
    }
    CHHC80xxServer::SWifiNetwork wifiConfig;
    wifiConfig.m_strIpAddress = IPaddr;
    wifiConfig.m_strSubnetMask = Subnet;
    wifiConfig.m_strGateway = Gateway;
    wifiConfig.m_strEssid = ui->txtSSID->text().trimmed();
    wifiConfig.m_bAdhoc = Adhoc;
    wifiConfig.m_eSecurity = mode;
    wifiConfig.m_strKey = ui->txtKey->text().trimmed();
    if(g_ccmainObj->serverMethod()->setWifiConfig(wifiConfig))
    {
        QMessageBox::information(0,"Wifi Settings","Wifi Configured Successfully");
        Prev_key.clear();
        this->done(0);
    }
    else
    {
        this->setEnabled(true);
    }
}

void WIFI_Conf::on_BtnCancel_clicked()
{
    Prev_key.clear();
    this->close();
}

void WIFI_Conf::on_cmbEncryption_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if(ui->cmbEncryption->currentIndex() > 0)
    {
        ui->txtKey->setEnabled(true);
        if(ui->cmbEncryption->currentText() == "WPA2 Personal")
        {
            ui->txtKey->setMaxLength(63);
            if(Prev_enc == CHHC80xxServer::eSecurityMode_WPA2_PERSONAL)
                ui->txtKey->setText(Prev_key);
            else
                ui->txtKey->setText("");
        }
        else if(ui->cmbEncryption->currentText() == "WEP")
        {
            ui->txtKey->setMaxLength(26);
            if(Prev_enc == CHHC80xxServer::eSecurityMode_WEP)
                ui->txtKey->setText(Prev_key);
            else
                ui->txtKey->setText("");
        }
    }
    else
    {
        ui->txtKey->setEnabled(false);
    }
    makeEnable();
}

void WIFI_Conf::makeEnable()
{
    if(!ui->BtnOk->isEnabled())
        ui->BtnOk->setEnabled(true);
}

void WIFI_Conf::on_BtnON_OFF_clicked()
{
//    qDebug()<<"\r Clicked button ON_OFF";
//    g_ccmainObj->serverMethod()->GadgetConfiguration(Gadeget,MassStorage);
//    if(Gadeget == 3)
//    {

        if(bWifiONOFFflag)
        {
            qDebug()<<"\r ON OFF click "<<bWifiONOFFflag;
            bWifiONOFFflag = false;
            g_ccmainObj->serverMethod()->setWIFION_OFF(true);
            g_ccmainObj->serverMethod()->enableWifiModule();
            ui->groupBox_Settings->setEnabled(true);
            ui->BtnON_OFF->setText("ON");
            ui->BtnON_OFF->setStyleSheet("background-color:green");
            ui->BtnON_OFF->setFocus();
        }
        else
        {
            qDebug()<<"\r ON OFF click else "<<bWifiONOFFflag;
            bWifiONOFFflag = true;
            g_ccmainObj->serverMethod()->setWIFION_OFF(false);
            g_ccmainObj->serverMethod()->disableWifiModule();
            ui->groupBox_Settings->setEnabled(false);
            ui->BtnON_OFF->setText("OFF");
            ui->BtnON_OFF->setStyleSheet("background-color:red");
            ui->BtnON_OFF->setFocus();
        }
//    }
//    else
//    {
//        QMessageBox::information(0,"WIFI CONFIGURATION","Please set Normal mode in GADGET");
//        ui->BtnON_OFF->setFocus();
//    }
}
