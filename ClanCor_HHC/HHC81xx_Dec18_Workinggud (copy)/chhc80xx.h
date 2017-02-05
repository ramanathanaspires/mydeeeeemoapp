/**
 * \file "chhc80xx.h"
 * \brief it provides an interface for communicate with HHC80xx pheripherals.
 *
 * This file is used to communicate co-processor & gsm module.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CHHC80XX_H
#define CHHC80XX_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <CHHC80xxServer>

namespace ClanCor
{
/**
     * \class CHHC80xx
     * \brief The CHHC80xx class provides the methods for communicate with co-processor & gsm module.
     *
     *  you can use this class perform various operations.
     */
class CHHC80xx : public QObject
{
    Q_OBJECT
    /*****************************************************************************
                                PUBLIC
******************************************************************************/
public:
    /**
         * The enum describes the message state
         */
    enum E_MessageState
    {
        eMessageState_UNREAD = 1,       /**< unread messages */
        eMessageState_READ = 2,         /**< read messages */
        eMessageState_STORED_UNSENT = 3,/**< stored unsent messages */
        eMessageState_STORED_SENT = 4,  /**< stored sent messages */
        eMessageState_ALL = 5           /**< all messages */
    };

    /**
         * \struct SSmsDetail
         * \brief It provides the interface for read sms details.
         *
         * It stores the sms details of the gsm network.
         */
    struct SSmsDetail
    {
        int m_MessageIndex;         /** gives the message index */
        E_MessageState m_eState;    /** gives the message state */
        QString m_strFrom;          /** gives the message from address */
        QString m_strMessage;       /** gives the message data */
        QDateTime m_dateTime;       /** gives the message received date & time */
    };

    /**
         * \struct SMagneticCardRead
         * \brief This structure used as an interface to read magnetic card tracks.
         *
         * Its members stores the track informations read from the magnetic card.
         */
    struct SMagneticCardRead
    {
        QString m_strTrack1;          /** stores the track1 info */
        QString m_strTrack2;          /** stores the track2 info */
        QString m_strTrack3;          /** stores the track3 info */
    };

    /**
         * \fn CHHC80xx()
         * A constructor.
         * \brief Creates a new HHC80xx object for send & receive the data from co-processor & gsm module .
         */
    CHHC80xx();

    /**
         * \fn ~CHHC80xx()
         * A destructor.
         * \brief Destroys the HHC80xx object and frees any allocated resources.
         */
    ~CHHC80xx();

    /**
         * \fn static void version(QString &r_strVer,QString &r_strDateTime)
         * \brief This function is used to get the HHC80xx library version & date time.
         * it gives the version & date time of the ClanCor HHC80xx SDK library.
         * \param[out] r_strVer used to get the version.
         * \param[out] r_strDateTime used to get the date & time.
         */
    static void version(QString &r_strVer,QString &r_strDateTime);

    /**
         * \fn oid coProcessorVersion(QString &r_strVer,QString &r_strDateTime)
         * \brief This function is used to get the co-processor version & date time.
         * it gives the version & date time of the co-processor.
         * \param[out] r_strVer used to get the version.
         * \param[out] r_strDateTime used to get the date & time.
         */
    void coProcessorVersion(QString &r_strVer,QString &r_strDateTime);

    /**
         * \fn QString deviceModel() const
         * \brief This function is used to get the device model name.
         * it will return the Device model like HHC-80xx ,HHC70xx,..,etc.
         * \return It returns the device model name.
         */
    QString deviceModel() const;

    /**
         * \fn QString lastError() const
         * \brief This function is used to get the error information about the last error (if any) that occurred with this class function.
         * if any function of this class returns false, use this function to get the error information.
         * \return It returns the last error information.
         */
    QString lastError() const;

    /**
         * \fn QString machineId() const
         * \brief This function is used to get the device machine id.
         * it will return the Device unique machine id.
         * \return It returns the device machine id.
         */
    QString machineId() const;

    /**
           * \fn bool initializeGSMModule() const
           * \brief This Function is used to initialise the GSM module
           * \return It returns true if it module is initiated successfully else False
           */
    bool initializeGSMModule() const;

    /**
           * \fn void setAutoboot(bool enable) const
           * \param[in] enable used to set Auto boot enable true or false for secondary Application.
           * \brief This Function is used to setAutoboot for Secondary Application.
           */
    void setAutoboot(bool enable) const;

    /**
           * \fn bool getAutoboot() const
           * \brief This Function is used to getAutoboot enbaled for Secondary Application.
           * \return It Returns true if the Autoboot is enabled else return false.
           */
    bool getAutoboot() const;

    /**
           * \fn bool setGPRSAPN() const
           * \param[in] APNName used to set APN name for the Sim Inserted.
           * \brief This Function is used to setAPNName to GSM module
           * \return It Returns true if the APN has been set successfully
           */
    bool setGPRSAPN(QString APNName) const;

    /**
           * \fn bool getGPRSAPN() const
           * \param[in] APNName used to get APN name form the module.
           * \brief This Function is used to getAPNName form GSM module
           */
    void getGPRSAPN(QString &APNName) const;

    /**
         * \fn QString getLog(E_FirwareLog eFirmwareLog) const
         * \brief This function is used to retrieve log data's stored by firmware.
         * it will return the log data's in text format.
         * \param[in] eFirmwareLog used to pass enum values to select log type.
         * \return It returns log data's as QString if available. otherwise returns NULL string if no log available (or) if error occured.
         *
         * \sa see also E_FirwareLog.
         */
    QString getLog(E_FirmwareLog eFirmwareLog) const;

    /**
         * \fn CHHC80xxServer* serverMethod() const
         * \brief This function is used to get the current server object for accessing server functions.
         * it will return CHHC80xxServer object.
         * \return It returns server object.
         *
         * \note Note that this function return null if your application not running as a main application.
         */
    CHHC80xxServer* serverMethod() const;

    /**
         * \fn void setServerMethod(CHHC80xxServer *objServer)
         * \brief This function is used to set the custom server object for receive the all ClanCor HHC80xx server events & customize the own HHC80xx panel.
         *
         * To implement a custom server method, derive from the CHHC80xxServer class, and use
         * the server's setServerMethod() function to install it.
         * When subclassing CHHC80xxServer, you can reimplement the all virtual functions to cutomize the flash messages,
         * popup messages, HHC80xPanel,..,etc.
         * \param[in] objServer used to set current server object.
         *
         * \note Note that this function can only be used in the server process.
         * which means your applciation should run the main application instead of ClanCor_HHC application
         */
    void setServerMethod(CHHC80xxServer *objServer);

    /**
         * \fn void shutDown()
         * \brief This function is used to shutdown the device.
         */
    void shutDown();

//    /**
//         * \fn void restart()
//         * \brief This function is used to restart the device.
//         */
//    void restart();

    /**
         * \fn bool keypadMode(E_KeypadMode &r_eKeypadMode)
         * \brief This function is used to get the current keypad mode.
         * \param[out] r_eKeypadMode used to get current keypad mode. possible enumeration values for charging status are numeric/ Alphabets
         * \return It returns true, if current keypad mode retrieved successfully, otherwise return false.
         *
         * \sa see also E_KeypadMode.
         */
    bool keypadMode(E_KeypadMode &r_eKeypadMode) const;

    /**
         * \fn bool setKeypadMode(E_KeypadMode eMode) const
         * \brief This function is used to set the keypad mode.
         * \param[in] eMode used to set mode as numeric/Alphabets.
         * \return It returns true, if keypad mode changed successfully; otherwise returns false.
         *
         * \sa see also E_KeypadMode.
         */
    bool setKeypadMode(E_KeypadMode eMode) const;

    /**
         * \fn bool capsLockStatus(bool &r_bCapsLock)
         * \brief This function is used to get the current Caps Lock status of keypad.
         * \param[out] r_bCapsLock used to get current Caps Lock status of keypad. true if Caps lock enabled, otherwise false.
         * \return It returns true, if Caps Lock status retrieved successfully, otherwise return false.
         *
         * \sa see also E_KeypadMode.
         */
    bool capsLockStatus(bool &r_bCapsLock) const;

    /**
         * \fn bool setKeypadModeLock(bool bModeLockON) const
         * \brief This function is used to Lock the keypad mode. It will lock the HW & SW keypad mode change, user cannot change keypad
         * mode using mode key.
         * \param[in] bModeLockON used to pass boolean value to lock or unlock Keypad mode. if true passed as argument, keypad mode will
         * be locked. if false passed as argument keypad mode will be unlocked. that is hardware or software keypad mode change wont
         * work if locked. Until unlocking the Keypad mode lock resetting the device.
         * \return It returns true, if keypad mode locked / unlocked successfully; returns false if any error.
         */
    bool setKeypadModeLock(bool bModeLockON) const;

    /**
         * \fn bool setKeypadBeep(bool bOn) const
         * \brief This function is used to set Enable/Disable the keypad beep.
         * \param[in] bOn used to set the keypad beep should be On/Off.
         * \return It returns true, if keypad beep enable/disable successfully; otherwise returns false.
         */
    bool setKeypadBeep(bool bOn) const;

    /**
         * \fn bool setBacklight(int nLevel) const
         * \brief This function is used to control the display backlight level.
         * \param[in] nLevel used to set the backlight level. it must be 0 to 5.
         * \return It returns true, if level updated successfully; otherwise returns false.
         */
    bool setBacklight(int nLevel) const;

    /**
         * \fn bool setAudioControl(int nLevel) const
         * \brief This function is used to control the display audio level.
         * \param[in] nLevel used to set the audio level. it must be 0 to 5.
         * \return It returns true, if level updated successfully; otherwise returns false.
         */
    bool setAudioControl(int nLevel) const;
    /**
         * \fn bool setGPRS(bool bSwitchOn) const
         * \brief This function is used to switch ON or OFF GPRS.
         * \param[in] bEnable used to store pass values to switch ON or OFF RFID reader.
         * \return It returns true, if this function executed successfully; otherwise returns false.
         */
    bool EnableGPRSModule(bool bSwitchOn) const;
    /**
         * \fn bool setRFID(bool bSwitchOn) const
         * \brief This function is used to switch ON or OFF RFID reader.
         * \param[in] bEnable used to store pass values to switch ON or OFF RFID reader.
         * \return It returns true, if this function executed successfully; otherwise returns false.
         */

    bool EnableRFIDModule(bool bSwitchOn) const;

    /**
         * \fn bool setGPS(bool bSwitchOn) const
         * \brief This function is used to switch ON or OFF GPS receiver.
         * \param[in] bEnable used to store pass values to switch ON or OFF GPS receiver.
         * \return It returns true, if this function executed successfully; otherwise returns false.
         */
    bool EnableGPSModule(bool bSwitchOn) const;
    /**
         * \fn bool setSAM(bool bSwitchOn) const
         * \brief This function is used to switch ON or OFF SAM CARD.
         * \param[in] bEnable used to store pass values to switch ON or OFF SAM CARD.
         * \return It returns true, if this function executed successfully; otherwise returns false.
         */
    bool EnableSAMModule(bool bSwitchOn) const;
    /**
         * \fn bool setCAMERA(bool bSwitchOn) const
         * \brief This function is used to switch ON or OFF CAMERA.
         * \param[in] bEnable used to store pass values to switch ON or OFF CAMERA.
         * \return It returns true, if this function executed successfully; otherwise returns false.
         */
    bool EnableCAMERAModule(bool bSwitchOn) const;
    /**
         * \fn bool setBARCODE(bool bSwitchOn) const
         * \brief This function is used to switch ON ot OFF BARCODE.
         * \param[in] bEnable used to store pass values to switch ON or OFF BARCODE .
         * \return It returns true,  if this function executed successfully; otherwise returns false.
         */
    bool EnableBARCODEModule(bool bSwitchOn) const;
    /**
         * \fn bool setPRINTER(bool bSwitchOn) const
         * \brief This function is used to switch ON ot OFF PRINTER.
         * \param[in] bEnable used to store pass values to switch ON or OFF PRINTER.
         * \return It returns true,  if this function executed successfully; otherwise returns false.
         */
    bool EnablePRINTERModule(bool bSwitchOn) const;

    /**
             * \fn bool EnableSMARTCARD(bool bSwitchOn) const
             * \brief This function is used to switch ON or OFF SAMRTCARD.
             * \param[in] bEnable used to store pass values to switch ON or OFF SAMRTCARD.
             * \return It returns true, if this function executed successfully; otherwise returns false.
             */
    bool EnableSMARTCARDdModule(bool bSwitchOn) const;
    /**
         * \fn bool enableHub(bool bSwitchOn) const
         * \brief This function is used to switch ON ot OFF Hub.
         * \param[in] bSwitchOn used to store pass values to switch ON or OFF Hub.
         * \return It returns true,  if this function executed successfully; otherwise returns false.
         */
    bool EnableHub(bool bSwitchOn) ;

    /**
             * \fn bool enableSMARTCARDSlot(const E_SmartcardSlot r_eSmartCard) const
             * \brief This function is used to switch SmartCard Slots 1 or 2.
             * \return It returns true, if this function executed successfully; otherwise returns false.
             */
     bool EnableSmartCardSlot(const E_SmartcardSlot r_eSmartCard);

     /**
          * \fn void EnableGSMMessageBox(bool bEnableMessage) const
          * \brief This function is used to Enable Message or Disable Message For GSM Module Class.
          * \param[in] bEnableMessage used to store pass values to Enable  or Disable Message.
          */
     void EnableGSMMessageBox(bool bEnableMessage) const;

     /**
          * \fn void EnablePrinterMessageBox(bool bEnableMessage) const
          * \brief This function is used to Enable Message or Disable Message For Printer Module Class.
          * \param[in] bEnableMessage used to store pass values to Enable  or Disable Message.
          */
     void EnablePrinterMessageBox(bool bEnableMessage) const;

     /**
          * \fn bool EnableWIFIEModule(bool bSwitchOn) const
          * \brief This function is used to switch ON ot OFF internal WIFI.
          * \param[in] bEnable used to store pass values to switch ON or OFF internal WIFI .
          * \return It returns true,  if this function executed successfully; otherwise returns false.
          */
     bool EnableWIFIEModule(bool bSwitchOn) const;
     /**
          * \fn bool EnableBlutoothModule(bool bSwitchOn) const
          * \brief This function is used to switch ON ot OFF internal bluetooth.
          * \param[in] bEnable used to store pass values to switch ON or OFF internal bluetooth.
          * \return It returns true,  if this function executed successfully; otherwise returns false.
          */
     bool EnableBlutoothModule(bool bSwitchOn) const;

     /**
              * \fn bool EnableExternalUSB(bool bSwitchOn) const
              * \brief This function is used to switch ON or OFF External USB.
              * \param[in] bEnable used to store pass values to switch ON or OFF External USB.
              * \return It returns true, if this function executed successfully; otherwise returns false.
              */
     bool EnableExternalUSB(bool bSwitchOn) const;

    /**
         * NOTE : Please Avoid to use this function in your Application.
         * \fn bool setKEYPAD(bool bSwitchOn) const
         * \brief This function is used to set the Keypad For Hardware Functional Test.
         * \return It returns true, if the successfully set; otherwise returns false.
         */
    bool setKEYPAD(bool bSwitchOn) const;
    /**
         * \fn bool setBeep(E_BeepType eBeep) const
         * \brief This function is used to set the beep for intimate user for some events.
         * \param[in] eBeep used to set the beep type.
         * \return It returns true, if the beep set successfully; otherwise returns false.
         * \sa see also E_BeepType.
         */
    bool setBeep(E_BeepType eBeep) const;

    /**
         * \fn bool batteryChargeStatus(E_ChargeStatus &r_eChargeStatus)
         * \brief This function is used to get battery charging status.
         * \param[out] r_eChargeStatus used to get charging status. possible enumeration values for charging status as Connected/Removed/Completed/Invalid
         * \return It returns true, if the charge status retrieved successfully; otherwise returns false.
         *
         * \sa see also E_ChargeStatus.
         */
    bool batteryChargeStatus(E_ChargeStatus &r_eChargeStatus);

    /**
         * \fn bool etDateTime(const QDateTime &r_const_dateTimeDT) const
         * \brief This function is used to set the current date & time.
         * \param[in] r_const_dateTimeDT used to set new date & time.
         * \return It returns true, if given date & time is updated successfully; otherwise returns false.
         */
    bool setDateTime(const QDateTime &r_const_dateTimeDT) const;

    /**
         * \fn bool dateTime(const QDateTime &r_const_dateTimeDT) const
         * \brief This function is used to get the current date & time from RTC.
         * \param[in] r_const_dateTimeDT used to get the current date & time from RTC.
         * \return It returns true, if the date & time is retrieved successfully; otherwise returns false.
         */
    bool dateTime(QDateTime &r_const_dateTimeDT) const;

    /**
         * \fn void switchDesktop()
         * \brief This function is used to switch to HHC 80xx Desktop from the User application.
         */
    void switchDesktop();

    /**
         * \fn void enableIdleMode(bool bEnable)
         * \brief This function is used to Enable/Disable the idle mode for a moment while accessing some USB devices like smartcard reader.
         * \param[in] bEnable used to set the Enable/Disable the idle mode.
         */
    void enableIdleMode(bool bEnable);

    /**
         * \fn bool signature(QImage &r_imageSignature) const
         * \brief This function is used to show the signature capture dialog to capture the signature.
         * \param[out] r_imageSignature used to get the captured signature image.
         * \return It returns true, if signature captured successfully; otherwise returns false.
         */
    bool signature(QImage &r_imageSignature) const;

    /**
         * \fn bool readMageneticCard(const E_MagneticCard eMagneticCard, SMagneticCardRead &r_sMagneticCardRead, unsigned int unTimeout_Sec = 10) const
         * \brief This function serves as API call to read magnetic card using the magnetic card reader assembled with HHC-80xx/70xx or HHC-81xx/71xx series handheld computers.
         * \param[in] r_eMagneticCard used to select the track to be read from the magnetic card.
         * \param[out] r_sMagneticCardRead used to retrieve the track information read from the magnetic card in different QString variables for each track.
         * \param[in] nTimeout_Sec used to set the time out value in seconds.
         * \return It returns true, if magnetic card read operation was successfull; otherwise returns false.
         */
    bool readMageneticCard(const E_MagneticCard eMagneticCard, SMagneticCardRead &r_sMagneticCardRead, unsigned int unTimeout_Sec = 10) const;

    /**
         * \fn bool sendFile(const QString r_const_strFILENAME) const
         * \brief This function is used to set the file which to be transfered.
         * it will show the filetransfer dialog if file exists only.
         * \param[in] r_const_strFILENAME used to set the file name.
         * \return It returns true, if file exist and transfered successfully; otherwise returns false.
         */
    bool sendFile(const QString &r_const_strFILENAME) const;

    /**
         * \fn bool operatorList(QList<QString> &r_listOperators) const
         * \brief This function is used to get list of network operators available.
         * \param[out] r_listOperators used to get the available operators.
         * \return It returns true, if operation executed successfully; otherwise returns false.
         */
    bool operatorList(QList<QString> &r_listOperators) const;

    /**
         * \fn bool gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel) const
         * \brief This function is used to get the gsm network inforamtions.
         * It will assign the informations like operator name, IMI number, CSQ value and Tower level.
         * \param[in] r_strNetwork is a reference variable, used to assign the network name.
         * \param[in] r_strIMINumber is a reference variable, used to assign the IMI number.
         * \param[in] r_strCSQValue is a reference variable, used to assign the current CSQ value.
         * \param[in] r_strTowerlevel is a reference variable, used to assign the current tower level.
         * \return It returns true, if the gsm module is initialized and working properly; otherwise returns false.
         */
    bool gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel) const;

    /**
         * \fn bool gsmNetwork(QString &r_OperatorName) const
         * \brief This function is used to get the current operator name.
         * \param[out] r_OperatorName used to get the current operator name.
         * \return It returns true, if operation executed successfully; otherwise returns false.
         */
    bool gsmNetwork(QString &r_OperatorName) const;

    /**
         * \fn bool setGsmNetworkManually(QString &r_OperatorID,E_NetworkMode &r_eNetworkMode) const
         * \brief This function is used to set the current operator name.
         * \param[out] r_OperatorID used to set the current operator ID.
         * \param[out] r_eNetworkMode used to set the NetworkMode (Auto/Manual) .
         * \return It returns true, if operation executed successfully; otherwise returns false.
         */
    bool setGsmNetworkManually(QString &r_OperatorID,E_NetworkMode &r_eNetworkMode) const;

    /**
         * \fn int writeSms(const QString &r_const_strDESTINATION,const QString &r_const_strMESSAGE) const
         * \brief This function is used to send the SMS message.
         * \param[in] r_const_strDESTINATION used to set the Destination.
         * \param[in] r_const_strMESSAGE used to set Message information.
         * \return It returns, index value returned from GSM module, if write operation executed successfully; otherwise returns -1.
         */
    int writeSms(const QString &r_const_strDESTINATION,const QString &r_const_strMESSAGE) const;

    /**
         * \fn bool readSms(QList<SSmsDetail> &r_listMessages,E_MessageState eState) const
         * \brief This function is used to read the SMS message.
         * \param[out] r_listMessages used to receive the messages.
         * \param[in] eState used to set Message state.
         * \return It returns true, if read operation executed successfully send to the network; otherwise returns false.
         *
         * \sa see also SSmsDetail and E_MessageState.
         */
    bool readSms(QList<SSmsDetail> &r_listMessages, E_MessageState eState) const;

    /**
         * \fn bool deleteSms(int nIndex) const
         * \brief This function is used to delete message from preferred message location.
         * \param[in] nIndex used to set associated memory location.
         * \return It returns true, if message deleted successfully; otherwise returns false.
         */
    bool deleteSms(int nIndex) const;

    /**
         * \fn bool smsDeliveryStatus(const int const_nSMSIndex) const;
         * \brief This function is used to retrieve SMS Delivery status from the internal SMS delivery queue,
         * \ that is, it will check the delivery status of SMS index passed as argument.
         * \param[in] const_nSMSIndex used to pass Delivered SMS index value.
         * \return It returns true, if message delivered successfully; otherwise returns false.
         */
    bool smsDeliveryStatus(const int const_nSMSIndex) const;

    /**
         * \fn bool enableGprs() const
         * \brief This function is used to enable the gprs connectivity.
         * \return It returns true, if gprs enabled successfully; otherwise returns false.
         */
    bool enableGprs() const;

    /**
         * \fn bool disableGprs() const
         * \brief This function is used to disable the gprs connectivity.
         * \return It returns true, if gprs disabled successfully; otherwise returns false.
         */
    bool disableGprs() const;

    /**
         * \fn bool gsmAT_Command(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec)
         * \brief This function is used to send command to gsm module, and stores the response into the passed reference argument.
         * It will wait for response from module until timeout. AT commands sent through this function wont reflect on SDK GUI.
         * \param[in] const_strCOMMAND used to pass the AT commands to be executed.
         * \param[out] r_const_strRESPONSE used to set the response text from GSM module, for the given AT commands.
         * \param[in] nTimeout_mSec used to set the time out in milliseconds.
         * \return It returns true, if executed successfully; otherwise returns false.
         */
    bool gsmAT_Command(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec);

    /**
         * \fn bool isGprsInitiated() const
         * \brief This function is used to check whether gsm module is initiated successfully or not.
         * \return It returns true, if gsm module is initiated successfully; otherwise returns false.
         */
    bool isGprsInitiated() const;

    /**
         * \fn bool isGprs() const
         * \brief This function is used to check whether gprs connectivity is available or not.
         * \return It returns true, if gprs connectivity is available; otherwise returns false.
         */
    bool isGprs() const;

    /**
                * \fn void gpsStandby() const
                * \brief This function is used to switch GPS to Standby Mode.
                */
    void gpsStandby() const;
    /**
                * \fn bool getGPSdata(QString &r_strLatitude,QString &r_strLongitude,QString &r_strAltitude,QString &r_strNo_of_sat,QString &r_strSpeed)
                * \brief This function is used to get GPS Data.
                * \param[1] Return Latitude Value
                * \param[2] Return Longitude Value
                * \param[3] Return Altitude Value
                * \param[4] Return No Of Satellite
                * \param[5] Return Speed
                * \param[6] Return Time
                * \return It returns true, if data available; otherwise returns false.
                */
    bool getGPSdata(QString &r_strLatitude,QString &r_strLongitude,QString &r_strAltitude,QString &r_strNo_of_sat,QString &r_strSpeed,QString &r_strTime);

    //Testing
    /**
                * \fn bool getGPRSGPSdata(QString &r_strLatitude,QString &r_strLongitude)
                * \brief This function is used to get GPS Data from the gsm module ( GPRS) ,
                * \param[1] Return Latitude Value
                * \param[2] Return Longitude Value
                * \return It returns true, if data available; otherwise returns false.
                */
    bool getGPRSGPSdata(QString &r_strLatitude,QString &r_strLongitude);



    /**
               * \fn void gpsWakeup() const
               * \brief This function is used to go GPS Wakeup Mode.
               */
    void gpsWakeup() const;
    /**
                * \fn bool agpsDownload() const
                * \brief This function is used to get GPS Data Download throug AGPS.
                * \return It returns true, if this function executed successfully; otherwise returns false.
                */
    bool agpsDownload() const;

    /**
         * \fn bool isEthernet() const
         * \brief This function is used to check whether ethernet connectivity is available or not.
         * \return It returns true, if ethernet connectivity is available; otherwise returns false.
         */
    bool isEthernet() const;

    /**
         * \fn bool isWifi() const
         * \brief This function is used to check whether Wifi link is active or not.
         * \return It returns true, if Wifi link is active; otherwise returns false.
         */
    bool isWifi() const;

    /**
         * \fn bool enableWifi()
         * \brief This function is used to enable the wifi module.
         * \return It returns true, if wifi module is enabled successfully; otherwise returns false.
         */
    bool enableWifi() const;

    /**
         * \fn bool disableWifi()
         * \brief This function is used to disable the wifi module.
         * \return It returns true, if wifi module is disabled successfully; otherwise returns false.
         */
    bool disableWifi() const;

    /**
         * \fn bool wifiStatus(int &nLevel) const
         * \brief This function is used to get the status of the wifi network.
         * \param[out] nLevel it gives the Level of the wifi signal. signal Level would be 0 to 5.
         * If level is -1, router might be switched off or invalid configuration.
         * \return It returns true, if wifi module is switched on; otherwise returns false.
         */
    bool wifiStatus(int &nLevel) const;

    /**
         * \fn QString lanIpAddress() const
         * \brief This function is used to return the lan ip address.
         * \return It returns the ip address of the lan.
         */
    QString lanIpAddress() const;

    /**
         * \fn QString gprsIpAddress() const
         * \brief This function is used to return the gprs ip address.
         * it will return empty string if gprs connectivity is not available.
         * \return It returns the ip address of the gprs connectivity.
         */
    QString gprsIpAddress() const;

    /**
         * \fn bool testRtc() const
         * \brief This function is used to test the RTC.
         * \return It returns true, if the RTC test is succeeded; otherwise returns false.
         */
    bool testRtc() const;

    /**
         * \fn bool testGprsModule() const
         * \brief This function is used to test the Gprs module.
         * It will show messagebox with information like Tower lelel, operator and gprs connectivity status,..,etc.
         * \return It returns true, if test is succeeded; otherwise returns false.
         */

    bool testGprsModule() const;

    /**
         * \fn bool testEthernet() const
         * \brief This function is used to test the ethernet network.
         * It will show messagbox with Ip Address, subnetmask and gateway.
         * \return It returns true, if test is succeeded; otherwise returns false.
         */
    bool testEthernet() const;
    /**
         * \fn bool batteryVoltage(float &r_value) const
         * \brief This function is used to get batteryvoltage Value.
         * \return It returns value.
         */
    bool batteryVoltage(float &r_value) const;
    /**
         * \fn  QString VirtualKeypad() const
         * \brief This function is used to show virtualkeypad.
         * \return It returns val.
         */
    QString VirtualKeypad() const;

private slots:
    /**
         * \fn void volumeIncrease(bool bState)
         * \brief This function is used to increase/decrease the speaker volume using function key.
         * func + Up -> Increase the speaker volume.
         * func + Down -> Decrease the speaker volume.
         * if audio deivce is fond it show the audio dialog for 3 minutes.
         * \param[in] bState used to set value as Increase/Decrease.
         */
    void volumeIncrease(bool bState);
    /**
         * \fn void volumeGui_timeout()
         * \brief This function is used to test the ethernet network.
         * It will close the audio dialog and disable the audio module.
         * \return It returns true, if test is succeeded; otherwise returns false.
         */
    void volumeGui_timeout();
};
}
#endif // CHHC80XX_H
