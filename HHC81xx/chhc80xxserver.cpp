#include "chhc80xxserver.h"
#include <sys/vfs.h>
#include <sys/statfs.h>
#include <QtCore/QMetaType>
#include "ctouchcalibrate.h"
#include "cglobal.h"
#include "cvolume.h"
#include <csettingsfile.h>
#include <QVariant>
#include <gps_data.h>
extern "C"
{
#include<uart.h>
}
using namespace ClanCor;
using namespace Global;

CHHC80xxServer::CHHC80xxServer()
{
    m_nCurrent = 1;
    m_nBatteryPer = 0;
    m_nBatteryVal = 6;
    gpsiconflag = false;

    myProcess = new QProcess;

    m_labelMessage = new QLabel("Keypad Locked..");
    m_labelMessage->setStyleSheet("border-width: 4px;border-color:#174763; border-style: solid;background-color:#c1d7ee;color:black");
    m_labelMessage->setFont(QFont("sans serif",14,1,false));
    m_labelMessage->setAlignment(Qt::AlignCenter);
    m_labelMessage->setWordWrap(true);
    m_labelMessage->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_labelMessage->setWindowModality(Qt::ApplicationModal);
    m_labelMessage->setGeometry(30,60,260,120);
    m_labelMessage->setFocusPolicy(Qt::NoFocus);

    connect(&m_timerFlash,SIGNAL(timeout()), this, SLOT(timerFlash_timeout()));

    m_labelBaloon = new QLabel;
    m_labelBaloon->setFocusPolicy(Qt::NoFocus);
    m_labelBaloon->setFont(QFont("sans serif",12,1,false));
    m_labelBaloon->setWindowFlags(Qt::ToolTip);
    m_labelBaloon->setStyleSheet("border-width: 2px;border-color:#2b396a; border-style: solid; background-color:#ffffc8;");
    m_labelBaloon->setAlignment(Qt::AlignRight);
    connect(&m_timerToolTip,SIGNAL(timeout()), this, SLOT(closeBaloon()));

    m_widgetPanel = new QWidget;

    m_calendarWidget = new QCalendarWidget(m_widgetPanel);
    m_calendarWidget->setFixedSize(240,160);
    m_calendarWidget->hide();
    m_calendarWidget->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint);

    QPushButton *pushButtonLogo = new QPushButton(m_widgetPanel);
    pushButtonLogo->setIcon(QIcon(":/icons-png/logo.png"));
    pushButtonLogo->setFocusPolicy(Qt::NoFocus);
    pushButtonLogo->setStyleSheet("border:0");
    //    pushButtonLogo->setIconSize(QSize(40,20));
    pushButtonLogo->setIconSize(QSize(30,20));
    //    pushButtonLogo->setGeometry(0,0,20,20);
    pushButtonLogo->setGeometry(0,0,30,20);
    connect(pushButtonLogo,SIGNAL(clicked()), this, SLOT(showDesktop()));

    m_labelTower = new QLabel(m_widgetPanel);
    m_labelTower->setGeometry(25,0,30,20);
    m_labelTower->setPixmap(QPixmap(":/icons-png/t0.png"));

    //Add GPS ICON
    if(objGps != NULL)
    {
        m_labelGps = new QLabel(m_widgetPanel);
        //        m_labelGps->setGeometry(55,-3,20,25);
        m_labelGps->setGeometry(55,-3,30,20);
        //        m_labelGps->setPixmap(QPixmap(":/icons-png/GPSy.png"));
        m_labelGps->setPixmap(QPixmap(" "));
        connect(objGps,SIGNAL(showgpsicon(bool)),this,SLOT(showgps(bool)));
    }

    m_labelPencil = new QLabel(m_widgetPanel);
    m_labelPencil->setGeometry(75,0,20,20);
    m_labelPencil->setPixmap(QPixmap(":/icons-png/pencil.png"));

    m_labelkeypad = new QLabel(m_widgetPanel);
    //    m_labelkeypad->setGeometry(95,0,25,20);
    //    m_labelkeypad->setFont(QFont("sans serif",9,QFont::Bold));
    m_labelkeypad->setGeometry(95,0,30,20);
    m_labelkeypad->setFont(QFont("sans serif",12,QFont::Bold));
    m_labelkeypad->setText("abc");


    m_pushButtonLocked = new QPushButton(m_widgetPanel);
    //    m_pushButtonLocked->setGeometry(120,0,30,20);
    //    m_pushButtonLocked->setGeometry(110,0,30,20);
    m_pushButtonLocked->setGeometry(120,0,20,20);
    m_pushButtonLocked->setFocusPolicy(Qt::NoFocus);
    m_pushButtonLocked->setStyleSheet("border:0");
    //    m_pushButtonLocked->setIconSize(QSize(30,20));
    m_pushButtonLocked->setIconSize(QSize(20,20));

    m_pushButtonDate = new QPushButton(m_widgetPanel);
    m_pushButtonDate->setFlat(true);
    m_pushButtonDate->setFocusPolicy(Qt::NoFocus);
    m_pushButtonDate->setStyleSheet("border:0");
    //    m_pushButtonDate->setGeometry(150,0,110,20);
    m_pushButtonDate->setGeometry(130,0,130,20);
    //    m_pushButtonDate->setFont(QFont("sans serif",9,QFont::Normal));
    m_pushButtonDate->setFont(QFont("sans serif",13,QFont::Bold));
    connect(m_pushButtonDate,SIGNAL(clicked()),this,SLOT(dateTime_clicked()));

    m_pushButtonNetworkIcon = new QPushButton(m_widgetPanel);
    m_pushButtonNetworkIcon->setFocusPolicy(Qt::NoFocus);
    m_pushButtonNetworkIcon->setStyleSheet("border:0");
    //    m_pushButtonNetworkIcon->setIconSize(QSize(20,20));
    //    m_pushButtonNetworkIcon->setGeometry(260,0,20,20);
    m_pushButtonNetworkIcon->setIconSize(QSize(30,20));
    m_pushButtonNetworkIcon->setGeometry(255,0,30,20);


    m_pushuttonBattery = new QPushButton(m_widgetPanel);
    m_pushuttonBattery->setFocusPolicy(Qt::NoFocus);
    m_pushuttonBattery->setStyleSheet("border:0");
    //    m_pushuttonBattery->setIconSize(QSize(30,15));
    //    m_pushuttonBattery->setGeometry(285,0,30,15);
    m_pushuttonBattery->setIconSize(QSize(35,20));
    m_pushuttonBattery->setGeometry(280,0,35,20);
    connect(m_pushuttonBattery, SIGNAL(clicked()), this, SLOT(showPercentage()));

    /* To get current battery charge status from library */
    E_ChargeStatus eChargeStatus;
    if(gpheripheralsPIC->ChargeStatus(eChargeStatus))
    {
        if(eChargeStatus == ClanCor::eChargeStatus_NONE)
        {
            m_pushuttonBattery->setIcon(QIcon(":/icons-png/b0.png"));
        }
        else
        {
            batteryChargeStatus(eChargeStatus);
        }
    }
    else
    {
        m_pushuttonBattery->setIcon(QIcon(":/icons-png/b0.png"));
    }

    m_toolbarPanel = new QToolBar("Top bar");
    m_toolbarPanel->setFocusPolicy(Qt::NoFocus);
    m_toolbarPanel->setFocus(Qt::NoFocusReason);
    m_toolbarPanel->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    m_toolbarPanel->setMovable(false);
    //    m_toolbarPanel->setFixedSize(320,20);
    m_toolbarPanel->setFixedSize(320,25);
    //    m_toolbarPanel->setGeometry(0,0,320,25);

    //    m_toolbarPanel->setFixedSize(320,25);
    m_toolbarPanel->addWidget(m_widgetPanel);

    m_toolbarPanel->layout()->setMargin(0);
    m_toolbarPanel->layout()->setSpacing(0);
    m_widgetPanel->setFocusPolicy(Qt::NoFocus);
    m_widgetPanel->setFocus(Qt::NoFocusReason);
    m_widgetPanel->setWindowFlags(Qt::FramelessWindowHint);
    m_widgetPanel->setFixedSize(320,240);
    //    m_widgetPanel->setFixedSize(320,480);

    qRegisterMetaType<E_ChargeStatus>("E_ChargeStatus");
    qRegisterMetaType<E_KeypadMode>("E_KeypadMode");
    qRegisterMetaType<E_NetworkStatus>("E_NetworkStatus");

    /* connect signals & slots */
    connect(gpheripheralsPIC, SIGNAL(batteryLevel(int,int)), this, SLOT(batteryLevel(int,int)));
    connect(gpheripheralsPIC, SIGNAL(batteryChargeStatus(E_ChargeStatus)), this, SLOT(batteryChargeStatus(E_ChargeStatus)));
    connect(gpheripheralsPIC, SIGNAL(keypadMode(E_KeypadMode,bool)), this, SLOT(keypadMode(E_KeypadMode,bool)));
    connect(gpheripheralsPIC, SIGNAL(keypadModeLocked(bool)), this, SLOT(keypadModeLocked(bool)));
    connect(gpheripheralsPIC, SIGNAL(shutdown(bool)), this, SLOT(shutDown(bool)));
    connect(gpheripheralsPIC, SIGNAL(showDesktop()), this, SLOT(showDesktop()));


    //    connect(gpheripheralsPIC, SIGNAL(batteryLevel(int,int)), this, SLOT(batteryLevel(int,int)));
    //    connect(gpheripheralsPIC, SIGNAL(batteryChargeStatus(E_ChargeStatus)), this, SLOT(batteryChargeStatus(E_ChargeStatus)));
    //    connect(gpheripheralsPIC, SIGNAL(shutdown(bool)), this, SLOT(shutDown(bool)));
    //    connect(gpheripheralsPIC, SIGNAL(showDesktop()), this, SLOT(showDesktop()));
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        connect(ggsmModuleSimCom, SIGNAL(gsmNetworkSignal(int)), this, SLOT(gsmNetworkSignal(int)));
        connect(ggsmModuleSimCom, SIGNAL(modReady()), this, SLOT(setNetworkApn()));
    }

    connect(&m_timerCharging, SIGNAL(timeout () ), this, SLOT(updateCharging()));


    if ( gnetworkActive != NULL ) {
        connect(gnetworkActive, SIGNAL(activeNetwork(E_NetworkStatus,int)), this, SLOT(activeNetwork(E_NetworkStatus,int)));
        connect(gnetworkActive, SIGNAL(popUpMessage(QString)), this, SLOT(popUpMessage(QString)));
    }

    if ( ginputMethodObj != NULL )
    {
        connect(ginputMethodObj, SIGNAL(keypadLockStatus(bool)), this, SLOT(keypadLockStatus(bool)));
        connect(ginputMethodObj, SIGNAL(wakeupFromIdleMode()), this, SLOT(wakeupFromIdleMode()));
        connect(ginputMethodObj, SIGNAL(wakeupFromStandbyMode()), this, SLOT(wakeupFromStandbyMode()));
        connect(ginputMethodObj, SIGNAL(standbyTimeout()), this, SLOT(standby_click()));
        connect(ginputMethodObj, SIGNAL(idleModeTimeout()), this, SLOT(idleMode_timeout()));

        //        connect(ginputMethodObj, SIGNAL(keypadLockStatus(bool)), this, SLOT(keypadLockStatus(bool)));
        //        connect(ginputMethodObj, SIGNAL(wakeupFromIdleMode()), this, SLOT(wakeupFromIdleMode()));
        //        connect(ginputMethodObj, SIGNAL(wakeupFromStandbyMode()), this, SLOT(wakeupFromStandbyMode()));
        //        connect(ginputMethodObj, SIGNAL(keypadMode(E_KeypadMode,bool)), this, SLOT(keypadMode(E_KeypadMode,bool)));
        //        connect(ginputMethodObj, SIGNAL(standbyTimeout()), this, SLOT(standby_click()));
        //        connect(ginputMethodObj, SIGNAL(idleModeTimeout()), this, SLOT(idleMode_timeout()));
        //        connect(ginputMethodObj, SIGNAL(keypadModeLocked(bool)), this, SLOT(keypadModeLocked(bool)));
    }

    connect(&m_timerDT,SIGNAL(timeout()), this, SLOT(updateDateTime()));

    m_timerDT.start(1000);
    updateDateTime();
}

CHHC80xxServer::~CHHC80xxServer()
{
    /* destroy the allocated resources */
    delete m_toolbarPanel;
    delete m_labelMessage;
    delete m_labelBaloon;
}

bool CHHC80xxServer::setEthernetConfig(const QString &r_const_strIPADDRESS, const QString &r_const_strSUBNET, const QString &r_const_strGATEWAY) const
{
    QStringList strListResult;
    QString strNetwork;
    QString broadcast;
    int a;

    for ( int nIndex = 0; nIndex < 4; nIndex ++ ) {
        if ( r_const_strIPADDRESS.section(".",nIndex,nIndex).simplified() == "" ) {
            QMessageBox::critical(0, "Ethernet", "Invalid IP Address");
            return false;
        }
        if ( r_const_strSUBNET.section(".",nIndex,nIndex).simplified() == "" ) {
            QMessageBox::critical(0, "Ethernet", "Invalid Subnet mask");
            return false;
        }
        if ( r_const_strGATEWAY.section(".",nIndex,nIndex).simplified() == "" ) {
            QMessageBox::critical(0,"Ethernet","Invalid Gateway Address");
            return false;
        }
        a = r_const_strIPADDRESS.section(".",nIndex,nIndex).simplified().toInt()
                & r_const_strSUBNET.section(".",nIndex,nIndex).simplified().toInt();
        strListResult.append(QString::number(a));
        strNetwork += QString::number(a) + ".";
    }
    strNetwork = strNetwork.left(strNetwork.length()-1);
    for ( int nIndex = 0; nIndex < 3; nIndex ++ ) {
        broadcast += strListResult.at(nIndex) + ".";
    }
    broadcast += "255";

    QByteArray byteArraySource, byteArrayDest;
    QFile fileNetwork("/etc/network/interfaces");
    if ( fileNetwork.open(QFile::ReadOnly) ) {
        byteArraySource = fileNetwork.readAll();
        fileNetwork.close();
        QBuffer bufferSource(&byteArraySource);
        bufferSource.open(QIODevice::ReadWrite);
        bool bStartEthernet = false, bEndEthernet = false;

        if ( bufferSource.atEnd() ) {
            QString strTemp;
            byteArrayDest.append("# This file describes the network interfaces available on your system + \n");
            byteArrayDest.append("# and how to activate them. For more information, see interfaces(5).\n\n");
            byteArrayDest.append("# The loopback network interface\nauto lo\niface lo inet loopback\n\n");
            byteArrayDest.append("# The primary network interface\nauto eth0\niface eth0 inet static\n");

            strTemp = "address " + r_const_strIPADDRESS + "\n" + "netmask " + r_const_strSUBNET + "\n" +
                    "network " + strNetwork + "\nbroadcast " + broadcast + "\ngateway " + r_const_strGATEWAY + "\n";
            byteArrayDest.append(strTemp);
            byteArrayDest.append("# End primary network interface\n\n");
        }
        else {
            QString strTemp;
            while ( ! bufferSource.atEnd() ) {
                strTemp = bufferSource.readLine(0);
                if ( strTemp.trimmed() == "# The primary network interface" ) {
                    if( ! bStartEthernet ) {
                        bStartEthernet = true;
                    }
                    byteArrayDest.append(strTemp);
                    byteArrayDest.append("auto eth0\niface eth0 inet static\n");
                    strTemp = "address " + r_const_strIPADDRESS + "\n" + "netmask " + r_const_strSUBNET + "\n" +
                            "network " + strNetwork + "\nbroadcast " + broadcast + "\ngateway " + r_const_strGATEWAY + "\n";
                    byteArrayDest.append(strTemp);
                    bufferSource.seek(bufferSource.pos());
                    while ( ! bufferSource.atEnd() ) {
                        strTemp = bufferSource.readLine(0);
                        if ( strTemp.trimmed() == "# End primary network interface" ) {
                            bEndEthernet = true;
                            byteArrayDest.append(strTemp + "\n");
                            break;
                        }
                    }
                }
                else {
                    if(bEndEthernet == true)
                    {
                        if(strTemp != "\n")
                        {
                            byteArrayDest.append(strTemp);
                        }
                    }
                    else
                    {
                        byteArrayDest.append(strTemp);
                    }
                }
            }
            if ( ! bStartEthernet ) {
                byteArrayDest.append("# The primary network interface\nauto eth0\niface eth0 inet static\n");
                strTemp = "address " + r_const_strIPADDRESS + "\n" + "netmask " + r_const_strSUBNET + "\n" +
                        "network " + strNetwork + "\nbroadcast " + broadcast + "\ngateway " + r_const_strGATEWAY + "\n";
                byteArrayDest.append(strTemp);
            }
            if ( ! bEndEthernet ) {
                byteArrayDest.append("# End primary network interface\n\n");
            }
        }
        bufferSource.close();
    }

    if ( fileNetwork.open(QFile::WriteOnly) ) {
        fileNetwork.write(byteArrayDest);
        fileNetwork.close();
    }
    byteArraySource.clear();
    byteArrayDest.clear();
    strListResult.clear();
    strNetwork.clear();
    sleep(1);
    if ( system(QString("ifdown eth0").toLatin1()) ) {
        QMessageBox::critical(0,"Network Setting","network link down failed..");
        return false;
    }
    if(gnetworkActive->isWifi())
    {
        qDebug()<<"WIFI is Active";
    }
    else
    {
        sleep(3);
        if ( system(QString("ifup eth0").toLatin1()) ) {
            QMessageBox::critical(0,"Network Setting","network link up failed..");
            return false;
        }
    }
    CSettingsFile settings;
    settings.beginSettingsGroup("NetworkEthernetConfiguration");
    settings.setValue("EthIpAddress", r_const_strIPADDRESS);
    settings.setValue("EthSubnet", r_const_strSUBNET);
    settings.setValue("EthGateway", r_const_strGATEWAY);
    return true;
}

bool CHHC80xxServer::ethernetConfig(QString &r_IpAddress, QString &r_SubnetMask, QString &r_Gateway) const
{
    bool bResponse = false;
    CSettingsFile settings;
    settings.beginSettingsGroup("NetworkEthernetConfiguration");

    if ( settings.contains("EthIpAddress") ) {
        r_IpAddress = settings.value("EthIpAddress");
        r_SubnetMask = settings.value("EthSubnet");
        r_Gateway = settings.value("EthGateway");
        bResponse = true;
    }

    return bResponse;
}

void CHHC80xxServer::setGadgetConfiguration(E_GadgetMode &r_Gadget_Mode,E_MassStorage &r_Mass_Storage_Type) const
{
    CSettingsFile settings;
    settings.beginSettingsGroup("GADGETCONFIGURATION");
    settings.setValue("GadgetOption", QString::number(r_Gadget_Mode));
    settings.setValue("MassStorage", QString::number(r_Mass_Storage_Type));
}

bool CHHC80xxServer::GadgetConfiguration( E_GadgetMode &r_Gadget_Mode,E_MassStorage &r_Mass_Storage_Type) const
{
    bool bResponse = false;
    CSettingsFile settings;
    settings.beginSettingsGroup("GADGETCONFIGURATION");
    if(settings.contains("GadgetOption"))
    {
        r_Gadget_Mode = (E_GadgetMode) settings.value("GadgetOption").toInt();
        r_Mass_Storage_Type = (E_MassStorage) settings.value("MassStorage").toInt();
        bResponse = true;
    }
    return bResponse;
}

bool CHHC80xxServer::setWifiConfig(const SWifiNetwork &r_const_wifiCONFIG) const
{
    QByteArray byteArraySource, byteArrayDest;
    QFile fileNetwork("/etc/network/interfaces");
    if ( fileNetwork.open(QFile::ReadOnly) ) {
        byteArraySource = fileNetwork.readAll();
        fileNetwork.close();
        QBuffer bufferSource(&byteArraySource);
        bufferSource.open(QIODevice::ReadWrite);
        bool bStartWireless = false, bEndWireless = false;

        if ( bufferSource.atEnd() ) {
            QString strTemp;
            byteArrayDest.append("# This file describes the network interfaces available on your system + \n");
            byteArrayDest.append("# and how to activate them. For more information, see interfaces(5).\n\n");
            byteArrayDest.append("# The loopback network interface\nauto lo\niface lo inet loopback\n\n");
            byteArrayDest.append("# The primary Wireless interface\nauto wlan0\niface wlan0 inet static\n");
            strTemp = "address " + r_const_wifiCONFIG.m_strIpAddress + "\n" +
                    "netmask " + r_const_wifiCONFIG.m_strSubnetMask + "\n" +
                    "gateway " + r_const_wifiCONFIG.m_strGateway + "\n";
            byteArrayDest.append(strTemp);
            byteArrayDest.append("# End primary Wireless interface\n\n");
            strTemp.clear();
        }
        else
        {
            QString strTemp;
            while ( ! bufferSource.atEnd() ) {
                strTemp = bufferSource.readLine(0);
                if ( strTemp.trimmed() == "# The primary Wireless interface" ) {
                    if ( ! bStartWireless ) {
                        bStartWireless = true;
                    }
                    byteArrayDest.append(strTemp);
                    byteArrayDest.append("auto wlan0\niface wlan0 inet static\n");
                    strTemp = "address " + r_const_wifiCONFIG.m_strIpAddress + "\n" + "netmask " + r_const_wifiCONFIG.m_strSubnetMask + "\n" + "gateway " + r_const_wifiCONFIG.m_strGateway + "\n";
                    byteArrayDest.append(strTemp);
                    bufferSource.seek(bufferSource.pos());
                    while ( ! bufferSource.atEnd() ) {
                        strTemp = bufferSource.readLine(0);
                        if ( strTemp.trimmed() == "# End primary Wireless interface" ) {
                            bEndWireless = true;
                            byteArrayDest.append(strTemp + "\n");
                            break;
                        }
                    }
                }
                else {
                    if(bEndWireless == true)
                    {
                        if(strTemp != "\n")
                        {
                            byteArrayDest.append(strTemp);
                        }
                    }
                    else
                    {
                        byteArrayDest.append(strTemp);
                    }
                }
            }
            if ( ! bStartWireless ) {
                byteArrayDest.append("# The primary Wireless interface\nauto wlan0\niface wlan0 inet static\n");
                strTemp = "address " + r_const_wifiCONFIG.m_strIpAddress + "\n"
                        + "netmask " + r_const_wifiCONFIG.m_strSubnetMask + "\n"
                        + "gateway " + r_const_wifiCONFIG.m_strGateway + "\n";
                byteArrayDest.append(strTemp);
            }
            if ( ! bEndWireless ) {
                byteArrayDest.append("# End primary Wireless interface\n\n");
            }
        }
        bufferSource.close();
    }
    else {
        QMessageBox::critical(0, "Wifi Settings", "Unable to open configuration file...");
        return false;
    }

    if ( fileNetwork.open(QFile::WriteOnly) ) {
        fileNetwork.write(byteArrayDest);
        fileNetwork.close();
    }
    else {
        QMessageBox::critical(0,"Wifi Settings","Unable to open configuration file...");
        return false;
    }
    byteArrayDest.clear();
    byteArraySource.clear();

    fileNetwork.setFileName("/etc/wireless_script.sh");
    if ( fileNetwork.open((QFile::WriteOnly)) ) {
        byteArrayDest.append("#!/bin/sh\n");
        byteArrayDest.append("iwconfig wlan0 essid \"" + r_const_wifiCONFIG.m_strEssid.trimmed() + "\" ");
        if ( r_const_wifiCONFIG.m_bAdhoc ) {
            byteArrayDest.append("mode ad-hoc ");
        }
        if ( r_const_wifiCONFIG.m_eSecurity != eSecurityMode_NONE ) {
            byteArrayDest.append("key " + r_const_wifiCONFIG.m_strKey);
        }
        byteArrayDest.append("\nexit 0");
        fileNetwork.write(byteArrayDest);
        fileNetwork.close();
        byteArrayDest.clear();
    }
    else {
        QMessageBox::critical(0, "Wifi Settings", "Unable to open configuration file...");
        return false;
    }

    CSettingsFile settings;
    settings.beginSettingsGroup("NetworkWifiConfiguration");
    settings.setValue("IpAddress",r_const_wifiCONFIG.m_strIpAddress);
    settings.setValue("Subnet",r_const_wifiCONFIG.m_strSubnetMask);
    settings.setValue("Gateway",r_const_wifiCONFIG.m_strGateway);
    settings.setValue("Essid",r_const_wifiCONFIG.m_strEssid);
    settings.setValue("Adhoc",QVariant(r_const_wifiCONFIG.m_bAdhoc).toString());
    settings.setValue("Security",QString::number(r_const_wifiCONFIG.m_eSecurity));
    settings.setValue("key",r_const_wifiCONFIG.m_strKey);

    if ( gnetworkActive != NULL ) {
        gnetworkActive->restart();
    }
    return true;
}

bool CHHC80xxServer::wifiConfig(SWifiNetwork &r_wifiConfig) const
{
    bool bResponse = false;
    CSettingsFile settings;
    settings.beginSettingsGroup("NetworkWifiConfiguration");
    if (settings.contains("Essid")) {
        r_wifiConfig.m_strIpAddress = settings.value("IpAddress");
        r_wifiConfig.m_strSubnetMask = settings.value("Subnet");
        r_wifiConfig.m_strGateway = settings.value("Gateway");
        r_wifiConfig.m_strEssid = settings.value("Essid");
        r_wifiConfig.m_bAdhoc = QVariant(settings.value("Adhoc")).toBool();
        r_wifiConfig.m_eSecurity = (E_SecurityMode) settings.value("Security").toInt();
        r_wifiConfig.m_strKey = settings.value("key");
        bResponse = true;
    }
    return bResponse;
}

bool CHHC80xxServer::setGprsApn(const QString &r_const_strApn) const
{
    qDebug()<<"\r apn 1";
    QString strNetwork;
    bool bResponse = false;
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        qDebug()<<"\r apn 2";
        CSettingsFile settings;
        settings.beginSettingsGroup("NetworkApnNames");
        qDebug()<<"\r apn 3";
        //Modified Boopathi No need to store Network Name
        settings.setValue("APN", r_const_strApn);
        qDebug()<<"\r apn 4";
        if ( ggsmModuleSimCom->getNetwork(strNetwork) == true )
        {
            qDebug()<<"\r apn 5"<<strNetwork;
            bResponse = ggsmModuleSimCom->setGprsApn(r_const_strApn);
                        qDebug()<<"\rAPN NAME"<<r_const_strApn;
        }
    }
    return bResponse;
}

void CHHC80xxServer::setNetworkApn()
{
    QString strApnName;
    strApnName = getgprsApn();
    if ( strApnName != "")
    {
        setGprsApn(strApnName);
    }
    else if(gbEnableMessageBoxGSM)
    {
        QMessageBox::information(0, "GSM-APN","Please configure the APN Name");
    }
}

QString CHHC80xxServer::getgprsApn() const
{
    QString strApnName = "";
    CSettingsFile settings;
    settings.beginSettingsGroup("NetworkApnNames");
    if(settings.contains("NetworkApnNames"))
        strApnName=settings.value("APN");
    return strApnName;
}

bool CHHC80xx::setGsmNetworkManually(QString &r_OperatorID,E_NetworkMode &r_eNetworkMode) const
{
    bool bResponse = false;
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() )
        {
            /* Power ON GPRS module through controller, If not powered on already */
            if(!initializeGSMModule())
                return false;
        }
        bResponse = ggsmModuleSimCom->setGprsNetwork(r_OperatorID,r_eNetworkMode);
    }
    return bResponse;
}
void CHHC80xxServer::serialPortFlushing(const QString &r_const_strPortName) const
{
    if(r_const_strPortName.contains("ttyS2"))
    {
        serialPortFlush("/dev/ttyS2");
    }
    else if (r_const_strPortName.contains("ttyS3"))
    {
        serialPortFlush("/dev/ttyS3");
    }
    else
    {
        if(gnGPRSModuleType==2)
        {
            serialPortFlush("/dev/cmux1");
        }
        else
        {
            serialPortFlush("/dev/ttyS1");
        }
    }
}
bool CHHC80xxServer::setMachineId(QString machineId, QString deviceModel, QString ModuleId) const
{
    return gpheripheralsPIC->setMachineId(machineId,deviceModel,ModuleId);
}

void CHHC80xxServer::setKeypadLockTimeout(int nSecs)
{
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    settings.setValue("KeypadLock", QString::number(nSecs));

    if ( ginputMethodObj != NULL) {
        ginputMethodObj->setKeypadLockTimeout(nSecs);
    }
}

int CHHC80xxServer::keypadLockTimeout() const
{
    int nScreenLock = 0;
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    if(settings.contains("KeypadLock"))
        nScreenLock = settings.value("KeypadLock").toInt();

    return nScreenLock;
}

void CHHC80xxServer::setIdleModeTimeout(int nSecs)
{
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    settings.setValue("Idletime", QString::number(nSecs));

    if ( ginputMethodObj != NULL) {
        ginputMethodObj->setIdleModeTimeout(nSecs);
    }
}

int CHHC80xxServer::idleModeTimeout() const
{
    int nIdle = 0;
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    if(settings.contains("Idletime"))
        nIdle = settings.value("Idletime").toInt();

    return nIdle;
}

void CHHC80xxServer::setStandbyModeTimeout(int nSecs)
{
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    settings.setValue("Standby", QString::number(nSecs));

    if ( ginputMethodObj != NULL) {
//        qDebug()<<"\r chhcserver. inputmethod."<<nSecs;
        ginputMethodObj->setStandbyModeTimeout(nSecs);
    }
}

int CHHC80xxServer::standbyModeTimeout() const
{
    int nStandby = 0;
    CSettingsFile settings;
    settings.beginSettingsGroup("PowerManagement");
    if(settings.contains("Standby"))
        nStandby = settings.value("Standby").toInt();

    return nStandby;
}

bool CHHC80xxServer::setBacklight(int nLevel) const
{
    bool bResponse = false;
    if ( nLevel > 0 && nLevel <= 5 ) {
        bResponse = gpheripheralsPIC->setBacklight(nLevel);
        CSettingsFile settings;
        settings.beginSettingsGroup("TFTSettings");
        settings.setValue("Brightness", QString::number(nLevel));
    }
    return bResponse;
}

int CHHC80xxServer::backlight() const
{
    int nLevel = 0;
    CSettingsFile settings;
    settings.beginSettingsGroup("TFTSettings");
    if(settings.contains("Brightness"))
        nLevel = settings.value("Brightness").toInt();

    return nLevel;
}

void CHHC80xxServer::setgprsAlwaysON_OFF(bool bflag) const
{
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("GPRSSettings");
    if(settings.contains("GPRSSettings"))
    {
        if(bflag)
        {
            settings.setValue("AlwaysON", "True");
        }
        else
        {
            settings.setValue("AlwaysON", "False");
        }
    }
    else
    {
        qDebug()<<"\r fail to set";
    }
}

bool CHHC80xxServer::getgprsAlwaysON_OFF() const
{
    QString returnvalue;
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("GPRSSettings");
    if(settings.contains("GPRSSettings"))
        returnvalue=settings.value("AlwaysON");
    if(returnvalue=="True")
        return true;
    else
        return false;
}

void CHHC80xxServer::setWIFION_OFF(bool bflag) const
{
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("WIFISettings");
    if(settings.contains("WIFISettings"))
    {
        if(bflag)
        {
            settings.setValue("EnableWIFI", "True");
        }
        else
        {
            settings.setValue("EnableWIFI", "False");
        }
    }
    else
    {
        qDebug()<<"\r fail to set";
    }
}

bool CHHC80xxServer::getWIFION_OFF() const
{
    QString returnvalue;
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("WIFISettings");
    if(settings.contains("WIFISettings"))
        returnvalue=settings.value("EnableWIFI");
    if(returnvalue=="True")
        return true;
    else
        return false;
}

bool CHHC80xxServer::getUSBON_OFF() const
{
    QString returnvalue;
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("USBSettings");
    if(settings.contains("USBSettings"))
    {
        returnvalue=settings.value("EnableUSB");

    }
    if(returnvalue == "True")
        return true;
    else
        return false;
}


bool CHHC80xxServer::touchCalibrateDialog() const
{
    bool bResponse = false;
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    //        QMessageBox::critical(0,"Touch Calibration","Touch Screen - Device not found..!");
    //        return bResponse;
    //    }
    //    else{
    CTouchCalibrate *t = new CTouchCalibrate;
    if ( t->getTouchval() ) {
        QMessageBox::information(0,"Touch Calibration Utility" ,
                                 "Touch Screen has been successfully calibrated.. \n"
                                 "Device will shutdown now.." );
        //        ginputMethodObj->on_pushButtonRestart_clicked();
        ginputMethodObj->on_pushButtonShutDown_clicked();
        bResponse = true;
    }
    delete t;
    //    }
    return bResponse;
}

bool CHHC80xxServer::volumeControlDialog() const
{
    if ( ! QFile::exists("/dev/audio") ) {
        gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,true,false);sleep(1);
        if ( ! QFile::exists("/dev/audio") ) {
            sleep(1);
        }
    }
    if ( QFile::exists("/dev/audio") ) {
        system(QString("alsactl restore").toLatin1());
        gbAudioRunning = true;
        CVolumeSetting *volumeSetting = new CVolumeSetting;
        volumeSetting->exec();
        system(QString("alsactl store").toLatin1());
        delete volumeSetting;
        gbAudioRunning = false;
        gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,false,false);
        return true;
    }
    else {
        return false;
    }
}

bool CHHC80xxServer::programCoProcessor(const QString &r_const_FILENAME) const
{
    QMessageBox msgBoxCoProcessor;
    msgBoxCoProcessor.move(0,30);
    msgBoxCoProcessor.setWindowTitle("HHC: program Co-processor");
    msgBoxCoProcessor.setIconPixmap(QPixmap(":/icons/chip-fing.png"));
    msgBoxCoProcessor.setText("If you want to update CoProcessor program, hold Function (Fn) key then click yes");
    msgBoxCoProcessor.addButton(QMessageBox::Yes);
    msgBoxCoProcessor.addButton(QMessageBox::No);
    int nVal = msgBoxCoProcessor.exec();
    if ( QMessageBox::Yes == nVal ) {
        if ( gpheripheralsPIC->programCoProcessor(r_const_FILENAME) ) {
            return true;
        }
    }
    return false;
}

bool CHHC80xxServer::enableWifiModule()
{
    bool bResponse = false;
    if(gbFirsCall)
    {
        gbProcessRunning = true;
        gnetworkActive->pauseThread();
        bResponse = gnetworkActive->enableWifiModule();
        gnetworkActive->startThread();
        gbProcessRunning = false;
    }
    return bResponse;
}

bool CHHC80xxServer::disableWifiModule()
{
    bool bResponse = false;
    if(gbFirsCall)
    {
        gbProcessRunning = true;
        gnetworkActive->pauseThread();
        bResponse = gnetworkActive->disableWifiModule(false);
        gnetworkActive->startThread();
        gbProcessRunning = false;
    }
    return bResponse;
}

void CHHC80xxServer::shutdownDialog()
{
    ginputMethodObj->shutdownDialog();
}

bool CHHC80xxServer::acceptIdleMode()
{
    return true;
}

bool CHHC80xxServer::acceptStandby()
{
    if ( gbGprsConnected || gbLanConnected ) {
        return false;
    }
    else {
        return true;
    }
}
void CHHC80xxServer::showgps(bool flag)
{
    if(flag)
    {
        m_labelGps->setPixmap(QPixmap(":/icons-png/gpsfinal_new.png"));
    }
    else
    {
        //        m_labelGps->setPixmap(QPixmap(":/icons-lib/GPSy.png"));
        m_labelGps->setPixmap(QPixmap(" "));
    }
}

/******************************* SLOTS ****************************************/

void CHHC80xxServer::flashMessage(const QString &r_const_strDISPLAYTEXT)
{
    m_timerFlash.stop();
    m_labelMessage->setText(r_const_strDISPLAYTEXT);
    m_labelMessage->show();
    m_timerFlash.start(1500);
    gUpdateScreen();
}

void CHHC80xxServer::timerFlash_timeout()
{
    m_timerFlash.stop();
    m_labelMessage->close();
    qApp->processEvents();
}

void CHHC80xxServer::popUpMessage(const QString &r_const_strDISPLAYTEXT)
{
    if ( m_labelBaloon->isVisible() ) {
        closeBaloon();
    }
    m_labelBaloon->setText(r_const_strDISPLAYTEXT);
    m_labelBaloon->show();
    m_labelBaloon->move(315-m_labelBaloon->width(),20);
    m_timerToolTip.start(1500);
}

void CHHC80xxServer::closeBaloon()
{
    m_timerToolTip.stop();
    m_labelBaloon->close();
    qApp->processEvents();
}

void CHHC80xxServer::dateTime_clicked()
{
    if ( m_calendarWidget->isVisible() ) {
        m_pushButtonDate->setStyleSheet("border:0");
        m_calendarWidget->close();
    }
    else {
        m_calendarWidget->setSelectedDate(QDateTime::currentDateTime().date());
        m_calendarWidget->move(QPoint(80,21));
        m_pushButtonDate->setStyleSheet("border-width: 2px;border-color:#174763; border-style: solid; background-color:#eee8aa");
        m_calendarWidget->show();
    }
}


void CHHC80xxServer::showPercentage()
{
    if ( ! m_timerCharging.isActive() ) {
        popUpMessage("Battery: " +QVariant(m_nBatteryPer).toString() +" %");
    }
    else {
        popUpMessage("Charging Battery..!");
    }
}

void CHHC80xxServer::activeNetwork(E_NetworkStatus eStatus, int nLevel)
{    
    switch ((int)eStatus) {
    case eNetworkStatus_ETHERNET:
        m_pushButtonNetworkIcon->setIcon(QIcon(":/icons-png/lan-connected.png"));
        break;
    case eNetworkStatus_GPRS:
        m_pushButtonNetworkIcon->setIcon(QIcon(":/icons-png/gprs-connected.png"));
        break;
    case eNetworkStatus_WIFI:
        if ( nLevel < 0 ) {
            if(nLevel == -1)
            {
                m_pushButtonNetworkIcon->setIcon(QIcon(":/icons-png/wirelessfailed.png"));
            }
            else if(nLevel == -2)
            {
                m_pushButtonNetworkIcon->setIcon(QIcon(":/icons-png/wirelessConnect.png"));
            }
        }
        else {
            m_pushButtonNetworkIcon->setIcon(QIcon(":/icons-png/wireless" + QVariant(nLevel).toString() + ".png"));
        }
        break;
    default:
        m_pushButtonNetworkIcon->setIcon(QIcon(":/none.png"));
    }
}

void CHHC80xxServer::batteryChargeStatus(E_ChargeStatus eStatus)
{    
    switch ((int)eStatus) {
    case eChargeStatus_CONNECTED:
        flashMessage("Charger Connected");
        m_nCurrent = 1;
        m_timerCharging.start(500);
        break;
    case eChargeStatus_REMOVED:
        flashMessage("Charger Removed");
        m_nCurrent = 1;
        m_timerCharging.stop();
        break;
    case eChargeStatus_COMPLETED:
        flashMessage("Charge Full");
        m_timerCharging.stop();
        break;
    case eChargeStatus_INVALID:
        m_timerCharging.stop();
        m_pushuttonBattery->setIcon(QIcon(":/icons-png/b-1.png"));
        flashMessage("Invalid Charger\nor\n Battery not available..!");
        break;
    }
    m_nBatteryVal = 6;
}

void CHHC80xxServer::batteryLevel(int nLevel, int nPercentage)
{
    if ( nLevel == 0 ) {
        flashMessage("Battery Low..!");
        gpheripheralsPIC->setBeep(eBeepType_ERROR_BEEP);
    }

    if ( m_nBatteryVal != nLevel ) {
        m_nBatteryVal = nLevel;
        m_pushuttonBattery->setIcon(QIcon(":/icons-png/b"+ QString::number(nLevel) +".png"));
    }
    m_nBatteryPer = nPercentage;
}

void CHHC80xxServer::updateCharging()
{
    m_pushuttonBattery->setIcon(QIcon(":/icons-png/b"+ QString::number(m_nCurrent) +".png"));
    if ( m_nCurrent < 5 ) {
        m_nCurrent++;
    }
    else {
        m_nCurrent=1;
    }
}

void CHHC80xxServer::keypadMode(E_KeypadMode eMode, bool bCapsOn)
{
    if ( eKeypadMode_NUMERIC == eMode ) {
        m_labelkeypad->setText("123");
    }
    else {
        if ( bCapsOn ) {
            m_labelkeypad->setText("ABC");
        }
        else {
            m_labelkeypad->setText("abc");
        }
    }
}

void CHHC80xxServer::keypadModeLocked( bool bModeLocked )
{
    if(bModeLocked)
    {

        m_labelPencil->setPixmap(QPixmap(":/icons-png/pencil_locked.png"));
    }
    else
    {
        m_labelPencil->setPixmap(QPixmap(":/icons-png/pencil.png"));
    }
}

void CHHC80xxServer::gsmNetworkSignal(int nLevel)
{
    m_labelTower->setPixmap(QPixmap(":/icons-png/t"+ QString::number(nLevel) +".png"));
}

void CHHC80xxServer::keypadLockStatus(bool bLocked)
{
    if ( bLocked == true ) {
        m_pushButtonLocked->setIcon(QPixmap(":/icons-png/lockedkey.png"));
        flashMessage("Keypad Locked..!");
    }
    else {
        m_pushButtonLocked->setIcon(QIcon(":/none.png"));
        flashMessage("Keypad Active..!");
    }
}

void CHHC80xxServer::showDesktop()
{
    //    myProcess->start("/root/eHT71ENV2.3.1");
    //    myProcess->waitForStarted();
    //    if(myProcess->state()==QProcess::Running)
    //    {

    //    }
}

void CHHC80xxServer::wakeupFromIdleMode()
{

}

void CHHC80xxServer::wakeupFromStandbyMode()
{

}

void CHHC80xxServer::updateDateTime()
{
    QString strCurrentDT = QDateTime::currentDateTime().toString("MMM dd, hh:mm AP");
    if ( m_pushButtonDate->text() != strCurrentDT ) {
        m_pushButtonDate->setText(strCurrentDT);
        gFreeCacheMemory();
        struct statfs stfs;
        float tfree,used,total,base, block;
        if ( ::statfs("/root",&stfs) == -1 ) {
            return;
        }
        base = stfs.f_bsize;
        block = stfs.f_blocks;
        tfree = stfs.f_bfree * ( base/  1024 )/1024;
        used = (block * ( base / 1024 ))/1024 - tfree;
        total = (block * ( base / 1024 ))/1024 ;
        int nPer;
        nPer=(int)used*100.0/total;
        if ( nPer > 85 ) {
            flashMessage(QVariant(nPer).toString() +" % Disk Full...!");
        }
    }
}

void CHHC80xxServer::shutDown(bool bMessage)
{
    if ( bMessage ) {
        ginputMethodObj->shutdownDialog();
    }
    else {
        ginputMethodObj->on_pushButtonShutDown_clicked();
    }
}

void CHHC80xxServer::standby_click()
{
    if ( acceptStandby() == true ) {
        ginputMethodObj->standbyMode();
    }
}

void CHHC80xxServer::idleMode_timeout()
{
    if ( acceptIdleMode() == true ) {
        ginputMethodObj->idleMode();
    }
}
