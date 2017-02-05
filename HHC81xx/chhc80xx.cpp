#include "chhc80xx.h"
#include "cpheripherals.h"
#include "cglobal.h"
#include "cfiletransfer.h"
#include <sys/vfs.h>
#include <sys/statfs.h>
#include "cinputmethod.h"
#include "cnetworkstatus.h"
#include "cvolume.h"
#include "csignature.h"
#include "caudiomodule.h"
#include "csymboldialog.h"
#include <csettingsfile.h>
#include <virtual.h>
#include <gps_data.h>

const int const_nDEFAULT_KEPAD_LOCK_TIME = 30;
const int const_nDEFAULT_IDLE_TIME = 60;
const int const_nDEFAULT_STANDBY_TIME = 180;

using namespace ClanCor;
using namespace Global;

/**
 * \var CVolume *VolumeGUI
 * \brief used to call increase or decrease the speaker volume.
 */
CVolume *VolumeGUI;
/**
 * \var QTimer timerVolume
 * \brief used for close the dialog volume gui timeout.
 */
QTimer timerVolume;
/**
 * \var QString strError
 * \brief used to store the error information.
 */
QString strError;
/**
 * \var bool bResponse
 * \brief used to store response of the functions.
 */
bool bResponse;
/**
 * \var QString strLanIp
 * \brief used to store the lan ip address.
 */
QString strLanIp = "";
/**
 * \var QString strSubnetMask
 * \brief used to store the subnet mask address.
 */
QString strSubnetMask = "";
/**
 * \var QString strGateway
 * \brief used to store the gateway address.
 */
QString strGateway = "";
/**
 * \var QString strGprsIpAddress
 * \brief used to store the gprs ip address.
 */
QString strGprsIpAddress = "";

CHHC80xx::CHHC80xx()
{
    Q_INIT_RESOURCE(icons);
#ifdef Q_WS_QWS
    gserverObj = QWSServer::instance();
    gserverObj->setCursorVisible(false);
    if ( gserverObj != NULL )
    {
        /* remove the shared memory if exist*/
        system("rm /tmp/qipc_sharedmemory_HHCxx*");
        system("rm /tmp/qipc_systemsem_HHCxx*");
        gFreeCacheMemory();
        /* update logo in the display */
        QBrush brush;
        /* Load Logo for initial Screen from usr/share/logo dynamic as per user required image */
        brush.setTextureImage(QImage("/usr/share/logo/logo.png"));
        brush.setColor(Qt::yellow);
        gserverObj->setBackground(brush);
        gserverObj->refresh();
    }
#endif
    /* initialize gsm and co-processor modules */
    gInitialize();
    gstrDeviceModel = gpheripheralsPIC->deviceModel();
    //#if SERIAL_DEBUG_FLAG
    //    gserialportDebug->close();
    //    gserialportDebug->open();
    //#endif
#ifdef Q_WS_X11
    ghhc80xxServerObj = new CHHC80xxServer;
#endif

#ifdef Q_WS_QWS
    gnetworkActive = new CNetwork;
    if ( gbFirsCall )
    {
        E_GadgetMode GadgetType=eSerial_USBMode;
        E_MassStorage MassStorage =eNone;
        /* do the below process, first api call */
        int nKeypadLock, nIdleMode, nStandby; /* store the automatic timeout value of keypad lock, idle mode and standby */
        /* Load Logo for initial Screen from usr/share/logo dynamic as per user required image */
        gsplash = new QSplashScreen(QPixmap("/usr/share/logo/logo.png"));
        qApp->setActiveWindow(gsplash);
        gsplash->setDisabled(true);
        gsplash->setWindowModality(Qt::ApplicationModal);
        gsplash->setFont(QFont("sans serif",14,QFont::Bold));

        ginputMethodObj = new CInputMethod;
        ghhc80xxServerObj = new CHHC80xxServer;
        VolumeGUI = new CVolume;

        CSettingsFile settings;
        /* Check if default configuration details have already been available or not */
        if(!settings.contains("NetworkApnNames"))
        {
            /* Initalize the default values in config files when it creates */

            /* to save values for APN  in settings file */
            ghhc80xxServerObj->setGprsApn("");

            /* Retrieve LAN IP address values from OS */
            lanIpAddress();
            if ( strLanIp !="" ) {
                /* Save LAN IP values into settings file */
                ghhc80xxServerObj->setEthernetConfig(strLanIp,strSubnetMask,strGateway);
            }
            /* Set the defualt power save time intervals */
            nKeypadLock = const_nDEFAULT_KEPAD_LOCK_TIME;
            nIdleMode = const_nDEFAULT_IDLE_TIME;
            nStandby = const_nDEFAULT_STANDBY_TIME;
        }
        else
        {
            /* Read the power save timer values from configuration file */
            nKeypadLock = ghhc80xxServerObj->keypadLockTimeout();
            nIdleMode = ghhc80xxServerObj->idleModeTimeout();
            nStandby = ghhc80xxServerObj->standbyModeTimeout();

        }
        /* Set power save timer values for devices */
        ghhc80xxServerObj->setKeypadLockTimeout(nKeypadLock);
        ghhc80xxServerObj->setIdleModeTimeout(nIdleMode);
        ghhc80xxServerObj->setStandbyModeTimeout(nStandby);

        if(settings.contains("GADGETCONFIGURATION"))
        {
            /* Retrive gadget configuration which was saved in file */
            ghhc80xxServerObj->GadgetConfiguration(GadgetType,MassStorage);
        }
        else
        {
            /* Set gadget configuration by default setting as serial mode */
            ghhc80xxServerObj->setGadgetConfiguration(GadgetType,MassStorage);
        }
        if(GadgetType!=3)
        {
            /* If gadget is not in normal mode not enable wifi */
            ghhc80xxServerObj->setWIFION_OFF(false);
        }
        CSettingsFile settings1("ClanCor", "HHC80xxSDK1.xml");
        if(!settings1.contains("AutoBoot"))
        {
            /* Set autoboot to false if not have autoboot name in file */
            setAutoboot(false);
        }
        if(!settings1.contains("GPRSSettings"))
        {
            /* Set always ON or OFF, if the name does not contain gprssettings name in file */
            ghhc80xxServerObj->setgprsAlwaysON_OFF(false);
        }
        if(!settings1.contains("USBSettings"))
        {
            CSettingsFile settings2("ClanCor", "HHC80xxSDK1.xml");
            settings2.beginSettingsGroup("USBSettings");
            if(settings2.contains("USBSettings"))
                settings2.setValue("EnableUSB","False");
        }

        /* connect signal & slots */
        //        connect(gbarCodeObj,SIGNAL(barcodeData(QString)), ginputMethodObj, SLOT(sendBarcodeData(QString)));
        connect(&timerVolume, SIGNAL(timeout()), this, SLOT(volumeGui_timeout()));
        connect(gpheripheralsPIC, SIGNAL(wakeup(bool)), ginputMethodObj, SLOT(wakeup(bool)));
        connect(gpheripheralsPIC, SIGNAL(resetTimer()), ginputMethodObj, SLOT(resetTimer()));
        connect(gpheripheralsPIC, SIGNAL(volumeIncrease(bool)), this, SLOT(volumeIncrease(bool)));

        /* Check if the device model is 7 series to activate mobile keypad */
        if ( gstrDeviceModel.contains("HHC-7") )
        {
            /* set mobile keypad active */
            //            qDebug()<<"ACTIVE MOBILE KEYPAD";
            ginputMethodObj->setActiveMobileKeypad(true);
        }
        else
        {
            //            qDebug()<<"ACTIVE QWERTY KEYPAD";
        }

        /* get display backlight voltage value level from configuration file */
        int nBrightness = ghhc80xxServerObj->backlight();

        if ( nBrightness != 0 )
        {
            /* Set display backlight voltage value level to device */
            gpheripheralsPIC->setBacklight(nBrightness);
        }
        //Normally enable by PIC Iteself
        /* Set keypad beep sound enabled */
        //        gpheripheralsPIC->setKeypadBeep(true);

        /*To unlock keypad if it has locked already */
        //        gpheripheralsPIC->setKeypadModeLock(false);

        /* Power ON GPRS module through controller, If not powered on already */
        //        gpheripheralsPIC->enableModule(CPheripherals::emodule_GPRS, true);

        /* Set instance of reimplemented QImputMethod class to QWSServer */
        gserverObj->setCurrentInputMethod(ginputMethodObj);

        /*Check device booted in bootloader mode */
        if ( gpheripheralsPIC->isBootloader() && QFile::exists("/mnt/Programfile.hex") )
        {
            /* If device booted in bootloader mode, then start programming Co-Processor */
            gbIdleStatus = true;
            gpheripheralsPIC->programCoProcessor("/mnt/Programfile.hex");
            gbIdleStatus = false;
        }

        gLoadIntoSharedPIC(const_strRUNNING);
        //  gLoadIntoSharedKey(const_strKEYPAD_ALPHABETS);
        gLoadIntoSharedNetwork(const_strRUNNING);
        /* start PIC thread after 1500 mSecs delay*/
        QTimer::singleShot(1500,gpheripheralsPIC, SLOT(startThread()));
        /* start network thread after 2000 mSecs delay*/
        QTimer::singleShot(2000,gnetworkActive, SLOT(startThread()));
        /* Create Symbol dialog instance */
        CSymbolDialog::Instance();
    }
    else
    {
        /* initiate if it is not first api call */
        QString strData;
        if(gstrCheckGPRSConfiguration.toLower() == "yes")
        {
            if ( gLoadFromSharedGSM(strData) )
            {
                if ( ! strData.contains(const_strERROR) )
                {
                    if(!(gbGprsAlwaysOn = ghhc80xxServerObj->getgprsAlwaysON_OFF()))
                        ggsmModuleSimCom->initiatedModule();
                    gLoadIntoSharedGSM(const_strCOMPLETED);
                }
            }
        }
        gLoadIntoSharedPIC(const_strCOMPLETED);
        gLoadIntoSharedNetwork(const_strCOMPLETED);
    }
#endif
    /* Free cache memory */
    gFreeCacheMemory();
}

CHHC80xx::~CHHC80xx()
{
    /* destroy the allocated resources */
#ifdef Q_WS_QWS
    delete gnetworkActive;
    if ( gbFirsCall ) {
        delete ginputMethodObj;
        delete ghhc80xxServerObj;
        //        delete gbarCodeObj;
        delete VolumeGUI;
    }
#endif
#ifdef Q_WS_X11
    delete ghhc80xxServerObj;
#endif
    QString strGsmData;
    gLoadFromSharedGSM(strGsmData);
    gTerminate();
}

void CHHC80xx::version(QString &r_strVer, QString &r_strDateTime)
{
    r_strVer = BUILDVERSION;
    r_strDateTime = BUILDDATE;
}

void CHHC80xx::coProcessorVersion(QString &r_strVer, QString &r_strDateTime)
{
    r_strVer = gpheripheralsPIC->version();
    r_strDateTime = gpheripheralsPIC->dateTime();
}

QString CHHC80xx::deviceModel() const
{
    return gpheripheralsPIC->deviceModel();
}

QString CHHC80xx::machineId() const
{
    return gpheripheralsPIC->machineId();
}

QString CHHC80xx::getLog(E_FirmwareLog eFirmwareLog) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    QString stringLog = "";
    switch (eFirmwareLog)
    {
    case eFirmwareLog_Process:      // Get Process log
        if(!gpheripheralsPIC->getProcessLog(stringLog))
        {
            stringLog = "";
        }
        break;
    case eFirmwareLog_Power:        // Get Power log
        if(!gpheripheralsPIC->getPowerLog(stringLog))
        {
            stringLog = "";
        }
        break;
    }
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return stringLog;
}

QString CHHC80xx::lastError() const
{
    return strError;
}

CHHC80xxServer * CHHC80xx::serverMethod() const
{
    return ghhc80xxServerObj;
}

void CHHC80xx::setServerMethod(CHHC80xxServer *objServer)
{
    if ( NULL == objServer )
    {
        return;
    }
#ifdef Q_WS_QWS
    if ( gserverObj != NULL )
    {
        delete ghhc80xxServerObj;
        ghhc80xxServerObj = NULL;
        ghhc80xxServerObj = objServer;
        if(gstrCheckGPRSConfiguration.toLower() == "yes")
        {
            ggsmModuleSimCom->pauseThread();
            ggsmModuleSimCom->startThread();
        }
    }
#endif
}

bool CHHC80xx::initializeGSMModule() const
{
    system("killall pppd");
    sleep(1);
    /*Initialize GSM Module */
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        qDebug()<<"\r init gsm 1";
        if ( ! ggsmModuleSimCom->initModule() )
        {
            qDebug()<<"\r init gsm 2";
            gLoadIntoSharedGSM(const_strERROR + ggsmModuleSimCom->getLastError());
            qDebug()<<"\r init gsm 3";
            return false;
        }
        else
        {
            qDebug()<<"\r init gsm 4";
            gLoadIntoSharedGSM(const_strRUNNING);
            qDebug()<<"\r init gsm 5";
            sleep(1);
            qDebug()<<"\r init gsm 6";
            ggsmModuleSimCom->startThread();
            qDebug()<<"\r init gsm 7";
            return true;
        }
        qDebug()<<"\r init gsm 8";
    }
    qDebug()<<"\r init gsm 9";
}

void CHHC80xx::shutDown() const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    glabelStatus->setText("Device Shutting Down... ");
    glabelStatus->show();
    gUpdateScreen();
    gpheripheralsPIC->setBeep(eBeepType_LONG_BEEP);
    /* decrease the backlight step by step */
    for ( int nValue = 2; nValue >= 0; nValue -- ) {
        usleep(500000);
        gpheripheralsPIC->setBacklight(nValue);
    }
    /* intimate shutdown to co-processor */
    gpheripheralsPIC->shutDown();
    /* intimate shutdown to os */
    system(QString("poweroff").toLatin1());
}

//void CHHC80xx::restart()
//{
//    /* restart the device */
//    gLoadIntoSharedPIC(const_strSTARTED);
//    glabelStatus->setText("Restarting Device... ");
//    glabelStatus->show();
//    gUpdateScreen();
//    /* decrease the backlight step by step */
//    for ( int nValue = 2; nValue >= 0; nValue -- ) {
//        usleep(500000);
//        gpheripheralsPIC->setBacklight(nValue);
//    }
//    /* intimate reset to co-processor */
//    gpheripheralsPIC->resetCoProcessor();
//    /* intimate reboot to os */
//    system(QString("reboot").toLatin1());
//}

bool CHHC80xx::keypadMode(E_KeypadMode &r_eKeypadMode) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->currentKeypadMode(r_eKeypadMode);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    if(!bResponse)
        strError = "Failed to retrieve keypad mode..";
    return bResponse;
}

bool CHHC80xx::setKeypadMode(E_KeypadMode eMode) const
{
    //    qDebug()<<"\r Setkeypadmode.....>>"<<eMode;
    switch ((int)eMode)
    {
    case eKeypadMode_NUMERIC:
        /* set the keypad to numeric mode */
        gLoadIntoSharedPIC(const_strKEYPAD_NUMERIC);
        break;
    case eKeypadMode_ALPHABETS:
        /* set the keypad to alphabets mode */
        gLoadIntoSharedPIC(const_strKEYPAD_ALPHABETS);
        break;
    case eKeypadMode_ALPHABETS_CAPS:
        /* set the keypad to alphabets capslock mode */
        gLoadIntoSharedPIC(const_strKEYPAD_ALPHABETS_CAPS);
        break;
    }
    return true;
}

bool CHHC80xx::capsLockStatus(bool &r_bCapsLock) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->capsLockStatus(r_bCapsLock);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    if(!bResponse)
        strError = "Failed to retrieve Caps Lock status..";
    return bResponse;
}

bool CHHC80xx::setKeypadModeLock(bool bModeLockON) const
{
    //     qDebug()<<"\r Setkeypadmodelock.....>>"<<bModeLockON;
    QString strSharedMemData;
    int nCount = 0;
    bool bSharedMemRunning = false;
    do {
        /* read the data after wait 100 milli seconds to check shared memory status paused */
        if(nCount != 0)
        {
            gUpdateScreen(100);
        }
        nCount ++;
        /*Read current data from PIC chared Memory */
        gLoadFromSharedPIC(strSharedMemData);
        //        qDebug()<<"\r keylock"<<strSharedMemData;
        if(strSharedMemData.trimmed() == const_strRUNNING)
        {
            bSharedMemRunning = true;
        }
    } while ( (!bSharedMemRunning) && nCount < 20 );
    //    qDebug()<<"\r keylock if"<<strSharedMemData;
    if(bSharedMemRunning)
    {
        gLoadIntoSharedPIC(const_strSTARTED);
    }
    else
    {
        strError = "Unable to lock KeypadMode..";
        //        qDebug()<<"\r"<<strError ;
        return false;
    }

    bResponse = gpheripheralsPIC->setKeypadModeLock(bModeLockON);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    if(!bResponse)
        strError = "Error while locking KeypadMode..";
    return bResponse;
}

bool CHHC80xx::setKeypadBeep(bool bOn) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->setKeypadBeep(bOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::setBacklight(int nLevel) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->setBacklight(nLevel);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}
bool CHHC80xx::setAudioControl(int nLevel) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->setAudioControl(nLevel);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}
bool CHHC80xx::EnableGPRSModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") )
    //    {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_GPRS, bSwitchOn,false);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return true;
    //    }
    return bResponse;
}

bool CHHC80xx::EnableRFIDModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") )
    //    {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_RFID, bSwitchOn,false);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return true;
    //    }
    return bResponse;
}

bool CHHC80xx::EnableGPSModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_GPS, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnableSAMModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_SAM, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnableCAMERAModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_FlashLight, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnableBARCODEModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    //    if ( gstrDeviceModel.contains("HHC-8") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_BARCODE, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnablePRINTERModule(bool bSwitchOn) const
{
    //  if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_PRINTER, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    // }
    // else
    //  {
    //  return false;
    // }
    return bResponse;
}
bool CHHC80xx::EnableBlutoothModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_BLUETOOTH, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnableExternalUSB(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    //    if ( gstrDeviceModel.contains("HHC-8") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_EXTERNALUSB, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}
bool CHHC80xx::EnableWIFIModule(bool bSwitchOn) const
{
    //  if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_WIFI, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    // }
    // else
    //  {
    //  return false;
    // }
    return bResponse;
}
bool CHHC80xx::EnableHub(bool bSwitchOn) const
{
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("USBSettings");
    if(settings.contains("USBSettings"))
    {
        if(bSwitchOn)
        {
            settings.setValue("EnableUSB", "True");
        }
        else
        {
            settings.setValue("EnableUSB", "False");
        }
    }
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_Hub, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

void CHHC80xx::EnableGSMMessageBox(bool bEnableMessage) const
{
    gbEnableMessageBoxGSM=bEnableMessage;
}

void CHHC80xx::EnablePrinterMessageBox(bool bEnableMessage) const
{
    gbEnableMessageBoxPrinter=bEnableMessage;
}

bool CHHC80xx::EnableSMARTCARDdModule(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") )
    //    {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_SMARTCARD, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}

bool CHHC80xx::EnableSmartCardSlot(const E_SmartcardSlot r_eSmartCard) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableSmartCardSlot(r_eSmartCard);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::setKEYPAD(bool bSwitchOn) const
{
    //    if ( gstrDeviceModel.contains("HHC-7") ) {
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->enableModule(CPheripherals::emodule_KEYPAD, bSwitchOn);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    //    }
    //    else
    //    {
    //        return false;
    //    }
    return bResponse;
}

bool CHHC80xx::setBeep(E_BeepType eBeep) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->setBeep(eBeep);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::batteryChargeStatus(E_ChargeStatus &r_eChargeStatus)
{
    //    int nCount = 0;
    bResponse = false;
    if(gbFirsCall)
    {
        bResponse = gpheripheralsPIC->ChargeStatus(r_eChargeStatus);
        if(!bResponse)
            strError = "Failed to retrieve battery charge status..";
    }
    else
    {
        gLoadIntoSharedPIC(const_strCHARGESTATUS);
        bResponse = gpheripheralsPIC->ChargeStatus(r_eChargeStatus);
        if(!bResponse)
            strError = "Failed to retrieve battery charge status..";
        gLoadIntoSharedPIC(const_strCHARGESTATUS_CLOSE);
    }
    return bResponse;
}

bool CHHC80xx::setDateTime(const QDateTime &r_const_dateTimeDT) const
{
    bool bResponse;
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->setDateTime(r_const_dateTimeDT);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::dateTime(QDateTime &r_const_dateTimeDT) const
{
    bool bResponse;
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->dateTime(r_const_dateTimeDT);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

void CHHC80xx::switchDesktop()
{
    gLoadIntoSharedPIC(const_strSHOW_DESKTOP);
}

void CHHC80xx::enableIdleMode(bool bEnable)
{
    if ( bEnable ) {
        gLoadIntoSharedPIC(const_strRESUMETIMER);
    }
    else {
        gLoadIntoSharedPIC(const_strPAUSETIMER);
    }
}

bool CHHC80xx::signature(QImage &r_imageSignature) const
{
    gLoadIntoSharedPIC(const_strPAUSE_THREADS);
    CSignature *sign = new CSignature;
    sign->exec();
    bResponse = sign->Saved;
    if ( bResponse ) {
        r_imageSignature = sign->Image;
    }
    gLoadIntoSharedPIC(const_strWAKEUP_THREADS);
    delete sign;
    return bResponse;
}

bool CHHC80xx::readMageneticCard(const E_MagneticCard eMagneticCard, SMagneticCardRead &r_sMagneticCardRead, unsigned int unTimeout_Sec) const
{
    bool bResponse;
    QString strCardTrackInfo;
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->readMageneticCard(eMagneticCard, strCardTrackInfo, unTimeout_Sec);
    if(bResponse)
    {
        QStringList strlstTrackInfo;
        switch (eMagneticCard)
        {
        case eMagneticCard_Read_ALL:
            strlstTrackInfo = strCardTrackInfo.split("?");
            if(strlstTrackInfo.size() > 3)
            {
                r_sMagneticCardRead.m_strTrack1 = strlstTrackInfo.at(0);
                r_sMagneticCardRead.m_strTrack2 = strlstTrackInfo.at(1);
                r_sMagneticCardRead.m_strTrack3 = strlstTrackInfo.at(2);
            }
            strlstTrackInfo.clear();
            break;

        case eMagneticCard_Read_TRACK1:
            r_sMagneticCardRead.m_strTrack1 = strCardTrackInfo.split("?").at(0);
            break;

        case eMagneticCard_Read_TRACK2:
            r_sMagneticCardRead.m_strTrack2 = strCardTrackInfo.split("?").at(0);
            break;

        case eMagneticCard_Read_TRACK3:
            r_sMagneticCardRead.m_strTrack3 = strCardTrackInfo.split("?").at(0);
            break;
        }
    }
    strCardTrackInfo.clear();
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::sendFile(const QString &r_const_strFILENAME) const
{
    CFileTransfer *fileTransfer=new CFileTransfer;
    bResponse = fileTransfer->sendFile(r_const_strFILENAME);
    delete fileTransfer;
    return bResponse;
}

bool CHHC80xx::operatorList(QList<QString> &r_listOperators) const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() )
        {
            return false;
        }
        bResponse = false;
        QString strData;
        if ( gLoadFromSharedGSM(strData) )
        {
            /* read the shared memory data for check if gsm module is ready (GPRS inactive) to communicate from second or first call*/
            if (strData.contains(const_strRUNNING) && (!gbGprsConnected))
            {
                gLoadIntoSharedGSM(const_strSTARTED);
                bResponse = ggsmModuleSimCom->getOperatorList(r_listOperators);
                gLoadIntoSharedGSM(const_strCOMPLETED);
                strError = ggsmModuleSimCom->getLastError();
            }
            else
            {
                strError = "GSM Module busy... GPRS might be active..";
            }
        }
    }
    return bResponse;
}

void CHHC80xx::setAutoboot(bool enable) const
{
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("AutoBoot");
    if(settings.contains("AutoBoot"))
    {
        if(enable)
        {
            settings.setValue("Enable", "True");
        }
        else
        {
            settings.setValue("Enable", "False");
        }
    }
}

bool CHHC80xx::getAutoboot() const
{
    QString returnvalue;
    CSettingsFile settings("ClanCor", "HHC80xxSDK1.xml");
    settings.beginSettingsGroup("AutoBoot");
    if(settings.contains("AutoBoot"))
        returnvalue=settings.value("Enable");
    if(returnvalue=="True")
        return true;
    else
        return false;
}

bool CHHC80xx::setGPRSAPN(QString APNName) const
{
    bResponse = false;
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        bResponse = ghhc80xxServerObj->setGprsApn(APNName);
    }
    return bResponse;
}

void CHHC80xx::getGPRSAPN(QString &APNName) const
{
    APNName = ghhc80xxServerObj->getgprsApn();
}

bool CHHC80xx::gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel) const
{
    // for SIMCOM
    bResponse = false;
    QString strSharedMemData;

    int nCount = 0;
    bool bSharedMemRunning = false;
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        do {
            /* read the data after wait 50 milli seconds to check paused */
            if(nCount != 0)
            {
                gUpdateScreen(100);
            }
            nCount ++;
            /*Read current data from PIC chared Memory */
            gLoadFromSharedGSM(strSharedMemData);
            if(strSharedMemData.trimmed() == const_strRUNNING)
            {
                bSharedMemRunning = true;
            }
        } while ( (!bSharedMemRunning) && nCount < 10 );

        /* read the shared memory data for check if gsm module is ready (GPRS inactive) to communicate from second or first call*/
        if (bSharedMemRunning && (!gbGprsConnected))
        {
            gLoadIntoSharedGSM(const_strSTARTED);
            bResponse = ggsmModuleSimCom->gsmNetworkInfo(r_strNetwork, r_strIMINumber, r_strCSQValue, r_strTowerlevel);

            gLoadIntoSharedGSM(const_strCOMPLETED);
            strError = ggsmModuleSimCom->getLastError();
        }
        else
        {
            strError = "GSM Module busy... GPRS might be active..";
        }
    }
    //    qDebug()<<"\r SDK csq.."<<r_strCSQValue<<"response..>>"<<bResponse;
    return bResponse;
}

bool CHHC80xx::gsmNetwork(QString &r_OperatorName) const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() )
        {
            //Modified Boopathi if Module Not Initialized Try to Initialize
            if(!initializeGSMModule())
                return false;
        }
        bResponse = false;
        bResponse = ggsmModuleSimCom->getNetwork(r_OperatorName);
    }
    return bResponse;
}

int CHHC80xx::writeSms(const QString &r_const_strDESTINATION, const QString &r_const_strMESSAGE) const
{
    int nSMSSentIndex = 0;
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() )
        {
            return false;
        }
        bResponse = false;
        QString strSharedMemData;
        int nCount = 0;
        bool bSharedMemRunning = false;
        do {
            /* read the data after wait 50 milli seconds to check paused */
            if(nCount != 0)
            {
                gUpdateScreen(100);
            }
            nCount ++;
            /*Read current data from PIC shared Memory */
            gLoadFromSharedGSM(strSharedMemData);
            if(strSharedMemData.trimmed() == const_strRUNNING)
            {
                bSharedMemRunning = true;
            }
        } while ( (!bSharedMemRunning) && nCount < 10 );

        /* read the shared memory data for check if gsm module is ready (GPRS inactive) to communicate from second or first call*/
        if (bSharedMemRunning && (!gbGprsConnected))
        {
            gLoadIntoSharedGSM(const_strSTARTED);
            nSMSSentIndex = ggsmModuleSimCom->writeSms(r_const_strDESTINATION, r_const_strMESSAGE);
            strError = ggsmModuleSimCom->getLastError();
            gLoadIntoSharedGSM(const_strCOMPLETED);
            sleep(1);
        }
        else
        {
            strError = "GSM Module busy... GPRS might be active..";
        }
    }
    return nSMSSentIndex;
}

bool CHHC80xx::readSms(QList<SSmsDetail> &r_listMessages, E_MessageState eState) const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() ) {
            return false;
        }
        bResponse = false;
        QString strData;
        if ( gLoadFromSharedGSM(strData) ) {
            /* read the shared memory data for check if gsm module is ready (GPRS inactive) to communicate from second or first call*/
            if (strData.contains(const_strRUNNING) && (!gbGprsConnected))
            {
                gLoadIntoSharedGSM(const_strSTARTED);
                bResponse = ggsmModuleSimCom->readSms(r_listMessages, eState);
                gLoadIntoSharedGSM(const_strCOMPLETED);
                strError = ggsmModuleSimCom->getLastError();
            }
            else
            {
                strError = "GSM Module busy... GPRS might be active..";
            }
        }
    }
    return bResponse;
}

bool CHHC80xx::deleteSms(int nIndex) const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() )
        {
            return false;
        }
        bResponse = false;
        QString strData;
        if ( gLoadFromSharedGSM(strData) )
        {
            /* read the shared memory data for check if gsm module is ready (GPRS inactive) to communicate from second or first call*/
            if (strData.contains(const_strRUNNING) && (!gbGprsConnected))
            {
                gLoadIntoSharedGSM(const_strSTARTED);
                bResponse = ggsmModuleSimCom->deleteSms(nIndex);
                gLoadIntoSharedGSM(const_strCOMPLETED);
                strError = ggsmModuleSimCom->getLastError();
            }
            else
            {
                strError = "GSM Module busy... GPRS might be active..";
            }
        }
    }
    return bResponse;
}

bool CHHC80xx::smsDeliveryStatus(const int const_nSMSIndex) const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        return ggsmModuleSimCom->smsDeliveryStatus(const_nSMSIndex);
    }
}

bool CHHC80xx::enableGprs() const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if(!gbGprsAlwaysOn)
        {
            if ( !isGprsInitiated() )
            {
                //Modified Boopathi if Module Not Initialized Try to Initialize
                if(!initializeGSMModule())
                    return false;
            }
            QString strData;
            if ( gLoadFromSharedGSM(strData) )
            {
                /* read the shared memory data for check it contains any error  when initializing gsm module */
                if (strData == const_strRUNNING )
                {
                    gLoadIntoSharedGSM(const_strSTARTED);
                    bResponse = ggsmModuleSimCom->enableGprs();
                    if ( ! bResponse )
                    {
                        gLoadIntoSharedGSM(const_strCOMPLETED);
                    }
                    else
                    {
                        /* To disable idle mode for HHC81xx */
                        gbIdleStatus = false;
                    }
                    strError = ggsmModuleSimCom->getLastError();
                    return bResponse;
                }
                else
                {
                    strError = "GSM Module not ready..";
                    return false;
                }
            }
            else
            {
                strError = "Failed while loading shared memory..";
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool CHHC80xx::disableGprs() const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if(!gbGprsAlwaysOn)
        {
            if ( ! isGprsInitiated() )
            {
                return false;
            }
            if(gbFirsCall)
            {
                bResponse = ggsmModuleSimCom->disableGprs();
            }
            else
            {
                QString strData;
                if ( gLoadFromSharedGSM(strData) )
                {
                    //                    qDebug()<<"\r Second call "<<strData;
                    /* read the shared memory data for check it contains any error
               when initializing gsm module */
                    if (strData.contains(const_strGPRS_CONNECTED))
                    {
                        bResponse = ggsmModuleSimCom->disableGprs();
                    }
                    else if (strData.contains(const_strGPRS_DISCONNECTED))
                        //if disconnected by first software or by low signal strength
                    {
                        gbGprsConnected = false;
                        bResponse = ggsmModuleSimCom->disableGprs();
                    }
                    else
                    {
                        gbGprsConnected = false;
                    }
                }
                else
                {
                    strError = "Failed while loading shared memory..";
                }
            }

            /* To enable back idle mode */
            gbIdleStatus = true;
            strGprsIpAddress = "";
            if (!bResponse)
            {
                strError = ggsmModuleSimCom->getLastError();
            }
            return bResponse;
        }
    }
    else
    {
        return false;
    }
}
QString CHHC80xx::gsm_ModuleVersion()
{
    QString str_gsmmoduleversion="at+cgmr", str_response;
    if(gsmAT_Command(str_gsmmoduleversion,str_response, 1000))
    {
        return str_response.trimmed();
    }
    else
    {
        return str_response;
    }
}
bool CHHC80xx::gsmAT_Command(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec)
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        bResponse = false;
        bResponse = ggsmModuleSimCom->gsmATCommand(const_strCOMMAND, r_const_strRESPONSE, nTimeout_mSec);
    }
    return bResponse;

}

bool CHHC80xx::isGprsInitiated() const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        strError = ggsmModuleSimCom->getLastError();
        return ggsmModuleSimCom->isInitiated();
    }
    else
    {
        return false;
    }
}

bool CHHC80xx::isGprs() const
{
    bool bResponse;
    if(isGprsConnected())
    { /* direct ioctl() call */
        bResponse = true;
    }
    else
    {
        bResponse = false;
        strError = "GPRS link not active..!";
    }
    return bResponse;
# if 0 /* old method */
    QString strData;
    bool bResponse;
    gSysCommand("ifconfig ppp0","",&strData);
    if (strData.contains("UP") && strData.contains("RUNNING"))
    {
        bResponse = true;
    }else
    {
        bResponse = false;
    }
    strData.clear();
    return bResponse;
#endif      
}

void CHHC80xx::gpsStandby() const
{
    if(gstrCheckgpsConfiguration.toLower() == "yes")
        objGps->setGPSStandby();
}
bool CHHC80xx::getGPRSGPSdata(QString &r_strLatitude, QString &r_strLongitude)
{
    bool bResponse;
    bResponse=ggsmModuleSimCom->getGPSPosition(r_strLatitude,r_strLongitude);
    //    if(ggsmModuleSimCom->getGPSPosition(r_strLatitude,r_strLongitude))
    //    {
    //        r_strLatitude =gm_strGPRSGPSLatitude;
    //        r_strLongitude= gm_strGPRSGPSLongitude;
    //        ggsmModuleSimCom->startThread();
    //    }
    //    qDebug()<<"\r chhcs"<<r_strLatitude<<"\n chhdada"<<r_strLongitude;
    return bResponse;
}

bool CHHC80xx::getGPSdata(QString &r_strLatitude, QString &r_strLongitude, QString &r_strAltitude, QString &r_strNo_of_sat, QString &r_strSpeed, QString &r_strTime)
//bool CHHC80xx::getGPSdata( QString &r_strLatitude,QString &r_strLongitude, QString &r_strAltitude, QString &r_strNo_of_sat, QString &r_strSpeed, QString &r_strT)
{
    if(gstrCheckgpsConfiguration.toLower() == "yes")
        return objGps->getGPSFixedvalues(r_strLatitude,r_strLongitude,r_strAltitude,r_strNo_of_sat,r_strSpeed,r_strTime);
}

void CHHC80xx::gpsWakeup() const
{
    if(gstrCheckgpsConfiguration.toLower() == "yes")
        objGps->wakeupGPS();
}

bool CHHC80xx::agpsDownload() const
{
    if(gstrCheckgpsConfiguration.toLower() == "yes")
        return objGps->writeFile();
}

bool CHHC80xx::isEthernet() const
{
    bool bResponse;
    if(getEthernetLinkStatus()) {
        bResponse = true;
    }
    else {
        bResponse = false;
        strError = "Ethernet link not active..!";
    }
    return bResponse;
}

bool CHHC80xx::isWifi() const
{
    bool bResponse;
    if(APMacAddress() == "") {
        bResponse = false;
        strError = "Wifi link not active..!";
    }
    else {
        bResponse = true;
    }
    return bResponse;
}

bool CHHC80xx::enableWifi() const
{
    QString strData;
    bool bResponse = false;
    gLoadFromSharedNetwork(strData);
    if(strData.trimmed() == const_strRUNNING)
    {
        if(gLoadIntoSharedNetwork(const_strENABLEWIFI))
        {
            int nCount = 0;
            do {
                /* read the data after wait 200 milli seconds to check paused */
                usleep(200000);
                nCount ++;
                gLoadFromSharedNetwork(strData);
            } while ( (strData.trimmed() != const_strRUNNING && strData.trimmed() != const_strWIFIPROCESS_FAILED) && nCount < 50 );
        }
        if(strData.trimmed() == const_strRUNNING)
        {
            bResponse = true;
        }
        else if(strData.trimmed() == const_strWIFIPROCESS_FAILED)
        {
            bResponse = false;
            gLoadIntoSharedNetwork(const_strRUNNING);
            strError = gnetworkActive->getLastError();
        }
    }
    return bResponse;
}

bool CHHC80xx::disableWifi() const
{
    QString strData;
    bool bResponse = false;
    gLoadFromSharedNetwork(strData);
    if(strData.trimmed() == const_strRUNNING)
    {
        if(gLoadIntoSharedNetwork(const_strDISABLEWIFI))
        {
            int nCount = 0;
            do {
                /* read the data after wait 200 milli seconds to check paused */
                usleep(200000);
                nCount ++;
                gLoadFromSharedNetwork(strData);
            } while ( (strData.trimmed() != const_strRUNNING && strData.trimmed() != const_strWIFIPROCESS_FAILED) && nCount < 50 );
        }
        if(strData.trimmed() == const_strRUNNING)
        {
            bResponse = true;
        }
        else if(strData.trimmed() == const_strWIFIPROCESS_FAILED)
        {
            bResponse = false;
            gLoadIntoSharedNetwork(const_strRUNNING);
            strError = gnetworkActive->getLastError();
        }
    }
    return bResponse;
}

bool CHHC80xx::wifiStatus(int &nLevel) const
{
    bool bResponse = false;
    if(getWifiStatus(nLevel))
        bResponse = true;
    else
    {
        bResponse = false;
        strError = gnetworkActive->getLastError();
    }
    return bResponse;
}

QString CHHC80xx::lanIpAddress() const
{
    SNetworkIP sNetworkIPLan;
    if(gNetworkIPDetails("eth0", sNetworkIPLan))
    {
        strLanIp = sNetworkIPLan.m_strIpAddress;
        strSubnetMask = sNetworkIPLan.m_strSubnetMask;
        strGateway = sNetworkIPLan.m_strGateway;
    }
    else
    {
        return "";
    }
    return strLanIp;
}

QString CHHC80xx::gprsIpAddress() const
{
    //     qDebug()<<"\r strGprsIpAddress...>>"<<gbGprsConnected;
    /* get the gprs ip address */
    if ( gbGprsConnected ) {
        strGprsIpAddress = ipAddress("ppp0");
        //        qDebug()<<"\r strGprsIpAddress...>>"<<strGprsIpAddress;
    }
    return strGprsIpAddress;
}

bool CHHC80xx::testRtc() const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->testRTC();
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

QString CHHC80xx::VirtualKeypad() const
{
    //    qDebug()<<"Going to launch keypad";
    gLoadIntoSharedPIC(const_strPAUSE_THREADS);
    Virtual *v = new Virtual;
    v->exec();
    gLoadIntoSharedPIC(const_strWAKEUP_THREADS);
    delete v;
    return gstrVirtualkey;
}

bool CHHC80xx::testEthernet() const
{
    QString strMessage;
    strLanIp = "";
    lanIpAddress();
    strMessage = "IP Address      : " + strLanIp + "\n";
    strMessage += "Subnet Mask  : " + strSubnetMask + "\n";
    strMessage += "Gateway        : " + strGateway + "\n";
    if ( isEthernet() ) {
        strMessage = "Ethernet Connected \n\n" + strMessage;
        QMessageBox::information(0, "Ethernet", strMessage);
        return true;
    }
    else {
        strMessage = "Ethernet Disconnected \n\n" + strMessage;
        QMessageBox::critical(0, "Ethernet", strMessage);
        return false;
    }
}

bool CHHC80xx::batteryVoltage(float &r_value) const
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->batteryvoltage(r_value);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CHHC80xx::testGprsModule() const
{
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ! isGprsInitiated() ) {
            return false;
        }
        gLoadIntoSharedGSM(const_strSTARTED);
        bResponse = ggsmModuleSimCom->testModule();
        strError = ggsmModuleSimCom->getLastError();
        return bResponse;
    }
    else
    {
        return false;
    }
}

void CHHC80xx::volumeIncrease(bool bState)
{
    timerVolume.stop();
    if ( CAudioModule::enableAudio() ) {
        if ( ! VolumeGUI->isVisible() ) {
            VolumeGUI->show();
            system(QString("alsactl restore").toLatin1());
        }
        ginputMethodObj->resetTimer();
        timerVolume.stop();
        if ( ! VolumeGUI->isVisible() ) {
            VolumeGUI->show();
        }
        timerVolume.start(2500);
        if ( bState ) {
            VolumeGUI->increaseVolume();
        }
        else {
            VolumeGUI->decreaseVolume();
        }
    }
}

void CHHC80xx::volumeGui_timeout()
{
    timerVolume.stop();
    system(QString("alsactl store").toLatin1());
    VolumeGUI->close();
    gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO, false);
}
