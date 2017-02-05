/**
 * \file "cpheripherals.h"
 * \brief it provides an interface for communicate with co-processor.
 *
 * This file is used to communicate co-processor for control the pheripherals and printing.
 * For more details about Protocol you can refer "Communication Protocol in HHTP8xxx project(New frm 25th June)" document.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CPHERIPHERALS_H
#define CPHERIPHERALS_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QThread>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QDialog>
#include <QSlider>
#include <QMutex>
#include "qextserialport.h"
#include "cprinter.h"
#include "chhc80xxserver.h"
#include "chhc80xxtypes.h"


const int  const_nSIZE_OF_NO_OF_BYTES               = 4;
const char const_cSTART_BYTE                        = '^';
const char const_cEND_BYTE                          = '!';

const char const_cPHERIPHERAL_MACHINE               = 'M';
const char const_cPHERIPHERAL_HID                   = 'H';
const char const_cPHERIPHERAL_IO_CONTROL            = 'I';
const char const_cPHERIPHERAL_PRINTER               = 'P';
const char const_cPHERIPHERAL_BARCODE               = 'B';
const char const_cPHERIPHERAL_RTC                   = 'R';
const char const_cPHERIPHERAL_MAGNETICCARD_READER   = 'C';

const char const_cPACKETID_SUCCESS_ACK              = 'K';
const char const_cPACKETID_NEGATIVE_ACK             = 'N';
const char const_cPACKETID_HANDSHAKING              = 'H';
const char const_cPACKETID_GET_MACHINE_ID           = 'G';
const char const_cPACKETID_ACK_MACHINE_ID           = 'I';
const char const_cPACKETID_GET_VERSION              = 'V';
const char const_cPACKETID_SHUTDOWN                 = 'O';
const char const_cPACKETID_RESET_CO_PROCESSOR       = 'R';
const char const_cPACKETID_RESET_REPROGRAM          = 'U';
const char const_cPACKETID_SUPPLY_STATUS            = 'S';
const char const_cPACKETID_KEYPAD_STATUS            = 'G';
const char const_cPACKETID_ACK_KEYPAD_STATUS        = 'S';
const char const_cPACKETID_KEYPAD_BEEP              = 'B';
const char const_cPACKETID_POWER_CONTROL            = 'P';
const char const_cPACKETID_SET_KEYPAD_MODE          = 'S';
const char const_cPACKETID_SET_KEYPADMODE_LOCK      = 'L';
const char const_cPACKETID_SET_KEYPADMODE_UNLOCK    = 'U';
const char const_cPACKETID_BEEP                     = 'B';
const char const_cPACKETID_TEST_RTC                 = 'T';
const char const_cPACKETID_GET_RTC                  = 'G';
const char const_cPACKETID_SET_RTC                  = 'S';
const char const_cPACKETID_TFT_BACKLIGHT            = 'L';
const char const_cPACKETID_AUDIO_CONTROL            = 'A';
const char const_cPACKETID_PRINT_DATA               = 'D';
const char const_cPACKETID_PRINT_LANGUAGE           = 'S';
const char const_cPACKETID_LOAD_IMAGE_DATA          = 'P';
const char const_cPACKETID_PRINT_BARCODE            = 'B';
const char const_cPACKETID_PRINT_HEADER_FOOTER      = 'I';
const char const_cPACKETID_PRINT_IMAGE              = 'I';
const char const_cPACKETID_PRINT_NUMBER             = 'N';
const char const_cPACKETID_LOAD_HEADER_IMAGE        = 'C';
const char const_cPACKETID_LOAD_FOOTER_IMAGE        = 'A';
const char const_cPACKETID_ENABLE_DISABLE_MODULE    = 'E';
const char const_cPACKETID_DRAW_LINE                = 'L';
const char const_cPACKETID_PAPER_FEED               = 'F';
const char const_cPACKETID_PAPER_STATUS             = 'G';
const char const_cPACKETID_PRINTER_STATUS           = 'S';
const char const_cPACKETID_TEST_PRINT               = 'T';
const char const_cPACKETID_LAST_PRINT_RESPONSE      = 'R';
const char const_cPACKETID_LOG                      = 'L';
const char const_cPACKETID_BOOT_PSW                 = 'B';
const char const_cPACKETID_READ_MAGNETICCARD        = 'R';
const char const_cPACKETID_READ_TERMINATE_MC	    = 'T';
const char const_cPACKETID_ACK_READ_MAGNETICCARD    = 'S';
//const QString const_StringNativeData_EOP            = "^N";

const char const_cPRINT_PHOTO                       = 'P';
const char const_cPOWER_STANDBY                     = '1';
const char const_cPOWER_IDLE                        = '2';
const char const_cPOWER_WAKEUP                      = '3';
const char const_cKEYPAD_BEEP_ON                    = 'A';
const char const_cKEYPAD_BEEP_OFF                   = 'S';
const char const_cHEADER_IMAGE_DATA                 = 'H';
const char const_cFOOTER_IMAGE_DATA                 = 'F';
const char const_cBARCODE_CODE128                   = '0';
const char const_cBARCODE_CODEA                     = '0'; //not implemented
const char const_cBARCODE_CODEB                     = '1';
const char const_cBARCODE_CODEC                     = '2'; //not implemented
const char const_cGET_POWER_LOG                     = '1';
const char const_cGET_PROCESS_LOG                   = '2';
const char const_cERASE_LOG                         = '3';
const char const_cSTORE_BOOT_PSW                    = '1';
const char const_cGET_BOOT_PSW                      = '2';

namespace ClanCor
{
    /**
     * \class CPheripherals
     * \brief The CPheripherals class provides the methods for control pheripherals & printing.
     *
     *  you can use this class to perform various operations.
     */
    class CPheripherals : public QThread
    {
        Q_OBJECT

    public:
        /**
         * The enum describes the list of module controlled by co-processor
         */
        enum E_Module
        {
            emodule_GPRS = 1, /**< Gprs module */
            emodule_GPS = 2, /**< Gps module */
            emodule_AUDIO = 3, /**< audio module */
            emodule_HEADPHONE = 4, /**< headphone module */
            emodule_FlashLight = 5, /**< FlashLight module */
            emodule_RFID = 6 ,/**< RFID module */
            emodule_SAM = 7,  /** <SAM module */
            emodule_BARCODE = 8,  /** <Barcode module */
            emodule_PRINTER = 9,   /** <Printer module */
            emodule_KEYPAD = 10,    /** <KeyPad> */
            emodule_SMARTCARD=11,   /** <Samrt Card> */
            emodule_Hub = 12,       /** <Hub >*/
            emodule_WIFI = 13,    /** <WIFI module> */
            emodule_EXTERNALUSB=14,   /** <External USB> */
            emodule_BLUETOOTH = 15  /** <Bluetoth module> */
        };

        /**
         * \fn CPheripherals(const QString r_const_strPORTNAME)
         * A constructor.
         * \brief Creates an object for send & receive the data to/from co-processor.
         * \arg[in] r_const_strPORTNAME used to set the co-processor port name.
         */
        CPheripherals(const QString r_const_strPORTNAME);

        /**
         * \fn ~CPheripherals()
         * A destructor.
         * \brief Stop the thread and destroys the allocated resources.
         */
        ~CPheripherals();

        /**
         * \fn QString version()
         * \brief This function returns the co-processor program version.
         * \return It returns the program version name.
         */
        QString version() const { return m_strPicVersion; }

        /**
         * \fn QString dateTime()
         * \brief This function returns the co-processor program date & time.
         * \return It returns the program date & time.
         */
        QString dateTime() const { return m_strPicDateTime; }

        /**
         * \fn QString machineId()
         * \brief This function returns the unique machine id of the Device.
         * \return It returns the device machine id.
         */
        QString machineId() const { return m_strMachineId; }

        /**
         * \fn QString deviceModel()
         * \brief This function returns the device model name like HHC-80xx ,HHC70xx,..,etc..
         * \return It returns the device model name.
         */
        QString deviceModel() const { return m_strDeviceModel; }

        /**
         * \fn bool enableSmartCardSlot(E_SmartcardSlot r_eSmartCard)
         * \brief This function return true if Slot is Enabled.
         */
        bool enableSmartCardSlot(E_SmartcardSlot r_eSmartCard);

        /**
         * \fn  bool setMachineId(QString machineId,QString deviceModel,QString ModuleId);
         * \brief This Function is used to set the Device Machine Id,devicemodel,GPRS module type through Software
         * \return It returns true if it sets machineid else False.
         */
        bool setMachineId(QString machineId,QString deviceModel,QString ModuleId);
        /**
         * \fn bool isBootloader()
         * \brief This function is used to check the device is switch on with Bootloader mode.
         * press fn + switch on to run the booloader mode.
         * \return It returns true, if it is bootloader mode; otherwise return false.
         */
        bool isBootloader();

        /**
         * \fn float fbatteryvalue()
         * \brief This function is used to check the device is switch on with Bootloader mode.
         * press fn + switch on to run the booloader mode.
         * \return It returns true, if it is bootloader mode; otherwise return false.
         */
        float fbatteryvalue();

        /**
         * \fn programCoProcessor(const QString &r_const_FILENAME);
         * \brief This function is used to reprogram the coprocessor.
         * Device will be shutdown once the reprogramming is successful or failed.
         * \param[in] r_const_FILENAME used to pass the path of the program filename.
         */
        bool programCoProcessor(const QString &r_const_FILENAME);

        /**
         * \fn bool handShaking()
         * \brief This function is used to send the handshaking command to co-processor.
         * \return It returns true, if successfully handshaking with co-processor; otherwise return false.
         */
        bool handShaking();

        /**
         * \fn bool handShaking()
         * \brief This function is used to reset the co-processor.
         * it has been used when reboot the device.
         * \return It returns true, if successfully reset the co-processor; otherwise return false.
         */
        bool resetCoProcessor();

        /**
         * \fn bool gotoIdle()
         * \brief This function is used to goto idlemode for power management.
         * \return It returns true, if the co-processor went to idle mode successfully; otherwise return false.
         */
        bool gotoIdle();
        /**
         * \fn bool wakeUpFromIdle()
         * \brief This function is used to wakeup from idle mode.
         * it will also detach all usb devices.
         * use to press On key, touch in the screen to wakeup from idle mode.
         * \return It returns true, if the co-processor is wakeuped successfully; otherwise return false.
         */
        bool wakeUpFromIdle();
        /**
         * \fn bool gotoStandby()
         * \brief This function is used to standby the co-processor.
         * use to press On key wakeup from standby mode.
         * \return It returns true, if co-processor went to standby mode; otherwise return false.
         */
        bool gotoStandby();

        /**
         * \fn bool currentKeypadMode(E_KeypadMode &r_eKeypadMode)
         * \brief This function is used to get the current keypad mode.
         * \param[out] r_eKeypadMode used to get current keypad mode. possible enumeration values for charging status are
         * numeric/ Alphabets/ Alphabets Capslock.
         * \return It returns true, if current keypad mode retrieved successfully, otherwise return false.
         *
         * \sa see also E_KeypadMode.
         */
        bool currentKeypadMode(E_KeypadMode &r_eKeypadMode);

        /**
         * \fn bool setKeypad(E_KeypadMode eMode)
         * \brief This function is used to set the keypad mode.
         * \param[in] eMode used to set mode as numeric/Alphabets.
         * \return It returns true, if keypad mode changed successfully; otherwise returns false.
         *
         * \sa see also E_KeypadMode.
         */
        bool setKeypadMode(E_KeypadMode eMode);

        /**
         * \fn bool setKeypadModeLock(bool bModeLockON)
         * \brief This function is used to Lock the keypad mode. It will lock the HW & SW keypad mode change.
         * \param[in] bModeLockON used to lock or unlock Keypad mode. if true passed as argument, keypad mode will be locked.
         * if false passed as argument keypad mode will be unlocked. that is hardware or software keypad mode change will never work.
         * Until unlocking the Keypad mode lock resetting the device.
         * \return It returns true, if keypad mode locked / unlocked successfully; returns false if any error.
         *
         */
        bool setKeypadModeLock(bool bModeLockON);

        /**
         * \fn bool capsLockStatus(bool &r_bCapsLock)
         * \brief This function is used to get the current Caps Lock status of keypad.
         * \param[out] r_bCapsLock used to get current Caps Lock status of keypad. true if Caps lock enabled, otherwise false.
         * \return It returns true, if Caps Lock status retrieved successfully, otherwise return false.
         *
         * \sa see also E_KeypadMode.
         */
        bool capsLockStatus(bool &r_bCapsLock);

        /**
         * \fn bool setKeypadBeep(bool bOn)
         * \brief This function is used to set Enable/Disable the keypad beep.
         * \param[in] bOn used to set the keypad beep should be On/Off.
         * \return It returns true, if keypad beep enable/disable successfully; otherwise returns false.
         */
        bool setKeypadBeep(bool bKeypadBeepON);

        /**
         * \fn bool setBeep(E_BeepType eBeep)
         * \brief This function is used to set the beep for intimate user for some events.
         * \param[in] eBeep used to set the beep type.
         * \return It returns true, if the beep set successfully; otherwise returns false.
         *
         * \sa see also E_BeepType.
         */
        bool setBeep(E_BeepType eBeep);

        /**
         * \fn bool setBacklight(int nValue)
         * \brief This function is used to control the display backlight level.
         * \param[in] nLevel used to set the backlight level. it must be 0 to 5.
         * \return It returns true, if level updated successfully; otherwise returns false.
         */
        bool setBacklight(int nValue);
        /**
         * \fn bool setAudioControl(int nValue)
         * \brief This function is used to control the display Audio level.
         * \param[in] nLevel used to set the backlight level. it must be 0 to 5.
         * \return It returns true, if level updated successfully; otherwise returns false.
         */
        bool setAudioControl(int nValue);

        /**
         * \fn bool ChargeStatus(E_ChargeStatus &r_eChargeStatus);
         * \brief This function is used to get battery charging status.
         * \param[out] r_eChargeStatus used to get charging status. possible enumeration values for charging status as Connected/Removed/Completed/Invalid
         * \return It returns true, if the charge status retrieved successfully; otherwise returns false.
         *
         * \sa see also E_ChargeStatus.
         */
        bool ChargeStatus(E_ChargeStatus &r_eChargeStatus);

        /**
         * \fn bool setDateTime(const QDateTime &r_const_dateTimeDT)
         * \brief This function is used to set the current date & time.
         * \param[in] r_const_dateTimeDT used to set new date & time.
         * \return It returns true, if given date & time is updated successfully; otherwise returns false.
         */
        bool setDateTime(const QDateTime &r_const_dateTimeDT);

        /**
         * \fn bool dateTime(QDateTime &r_dateTimeDT)
         * \brief This function is used to get the current date & time from co-processor.
         * \param[out] r_dateTimeDT used to get the date & time.
         * \return It returns true, if the date & time received successfully; otherwise returns false.
         */
        bool dateTime(QDateTime &r_dateTimeDT);

        /**
         * \fn bool readMageneticCard(E_MagneticCard &r_eMagneticCard, QString &r_strMCTrackInfo)
         * \brief This function is used to read track informations from magnetic card using the magnetic card reader assembled with HHC-80xx/70xx or HHC-81xx/71xx series handheld computers.
         * \param[in] r_eMagneticCard used to select the track to be read from the magnetic card.
         * \param[out] r_strMCTrackInfo used to store the read track informations from the magnetic card.
         * \param[in] nTimeout_Sec used to set the time out value in seconds.
         * \return It returns true, if magnetic card read operation was successfull; otherwise returns false.
         */
        bool readMageneticCard(const E_MagneticCard &r_eMagneticCard, QString &r_strMCTrackInfo, unsigned int unTimeout_Sec);

        /**
         * \fn bool enableModule(CPheripherals::E_Module eModule, bool bState)
         * \brief This function is used to Enable/Disable the modules.
         * \param[in] eModule used to set the module which want to enable/disable.
         * \param[in] bState used to set the Enable/Disable the given module.
         * \return It returns true, if the command executed successfully; otherwise returns false.
         */
        bool enableModule(CPheripherals::E_Module eModule, bool bState,bool bEnable_or_Statuscheck = false);

        /**
         * \fn bool loadHeaderImage(const QImage &r_const_imageHEADER)
         * \brief This function is used load the header image in the printer.
         * The maximum image width and hight should be 384*50.
         * loaded header image will be cleared after shutdown or restart the device.
         * \param[in] r_const_imageHEADER used to specify the image which is to be loaded in printer header.
         * \return It returns true, if the header image loaded successfully; otherwise returns false.
         */
        bool loadHeaderImage(const QImage &r_const_imageHEADER);

        /**
         * \fn bool loadFooterImage(const QImage &r_const_imageFOOTER)
         * \brief This function is used load the footer image in the printer.
         * The maximum image width and hight should be 384*50.
         * loaded footer image will be cleared after shutdown or restart the device.
         * \param[in] r_const_imageFOOTER used to specify the image which is to be loaded in printer footer.
         * \return It returns true, if the footer image loaded successfully; otherwise returns false.
         */
        bool loadFooterImage(const QImage &r_const_imageFOOTER);

        /**
         * \fn bool printData(const QList<QString> &listDatas, const QList<QString> &listImages)
         * \brief This function is used to print the data & images from the passed list arguments.
         * \param[in] listDatas used to pass the list of data to be printed.
         * \param[in] listImages used to pass the list of images to be printed.
         * \return It returns true, if all the given data printed successfully; otherwise returns false.
         */
        bool printData(const QList<QString> &listDatas, const QList<QImage> &listImages);

        /**
         * \fn bool sendPrintData(const QString &r_const_strPrintData, const bool &r_const_bNativeLanguage)
         * \brief This function is used to pass the print data to the printer, By checking whether the given data is native language or not.
         * If the given data is native language then the packet will be formed with const_cPACKETID_PRINT_LANGUAGE, otherwise const_cPACKETID_PRINT_DATA
         * \param[in] cPheripheralId used to set the pheripheral id.
         * \param[in] cPacketId used to set the packet id.
         * \param[in] r_const_strDATA used to set the data.
         * \param[in] nWait used to set the time out in milliseconds.
         * \return It returns true, if the command executed successfully; otherwise returns false.
         */
        bool sendPrintData(const QString &r_const_strPrintData, const bool &r_const_bNativeLanguage);
        /**
         * \fn bool imagePrinting(const QImage &r_const_imagePRINT)
         * \brief This function is used print the image.
         * The maximum image width should be 132.
         * \param[in] r_const_imagePRINT used to specify the image which is to be printed.
         * \return It returns true, if the image is printed successfully; otherwise returns false.
         */
        bool imagePrinting(const QImage &r_const_imagePRINT);

        /**
         * \fn bool grayScalePrinting(const QImage &r_const_imageGRAYSCALE)
         * \brief This function is used print the 3-bit grayscale image.
         * now it has been removed in the co-processor.
         * The maximum image width should be 132.
         * \param[in] r_const_imageGRAYSCALE used to specify the image which is to be printed.
         * \return It returns true, if the image is printed successfully; otherwise returns false.
         */
        bool grayScalePrinting(const QImage &r_const_imageGRAYSCALE);

        /**
         * \fn bool shutDown()
         * \brief This function is used to shutdown the co-processor.
         * intimate the co-processor before shutdown the device.
         * \return It returns true, if the command sent successfully; otherwise returns false.
         */
        bool shutDown();

        /**
         * \fn bool testRTC()
         * \brief This function is used to test the RTC.
         * \return It returns true, if the RTC test is succeeded; otherwise returns false.
         */
        bool testRTC();

        /**
         * \fn bool checkPrinterStatus()
         * \brief This function is used to check the printer status like printer ready status to print, printer door status & printer paper status.
         * \return It returns true, if the printer status check command was successfull; otherwise returns false.
         */
        bool checkPrinterStatus();

        /**
         * \fn bool paperStatus()
         * \brief This function is used to check the printer paper status.
         * \param[in] r_const_bPaperAvailable used to store paper sense result, true if paper is available on printer else false value will be stored.
         * \return It returns true, if the paper status command successfull; otherwise returns false.
         */
        bool checkPaperStatus(bool &r_bPaperAvailable);

        /**
         * \fn bool testPrinter()
         * \brief This function is used to test the printer.
         * now it has been removed in the co-processor.
         * \return It returns true, if the printer test is succeeded; otherwise returns false.
         */
        bool testPrinter();
        /**
         * \fn bool batteryvoltage(float &r_value)
         * \brief This function is used to get battery voltage.
         * \return It returns true, if the battery voltage get succeeded; otherwise returns false.
         */
        bool batteryvoltage(float &r_value);

        /**
         * \fn bool getPowerLog(QString &r_strData)
         * \brief This function is used to get the powerlog.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool getPowerLog(QString &r_strData);

        /**
         * \fn bool getProcessLog(QString &r_strData)
         * \brief This function is used to get the process log.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool getProcessLog(QString &r_strData);

        /**
         * \fn bool getLog(QString &r_strData)
         * \brief This function is used to show the dialog when reading power/process log.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool getLog(QString &r_strData);

        /**
         * \fn bool setBootPassword(const QString &r_const_strPSW)
         * \brief This function is used to set the boot password.
         * \return It returns true, if the command sent successfully; otherwise returns false.
         */
        bool setBootPassword(const QString &r_const_strPSW);

        /**
         * \fn bool bootPassword(QString &r_strPsw)
         * \brief This function is used to get the boot password.
         * \return It returns true, if the command sent successfully; otherwise returns false.
         */
        bool bootPassword(QString &r_strPsw);

        /**
         * \fn QString formPacket(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA)
         * \brief This function is used to form the packet by given data.
         * \param[in] cPheripheralId used to set the pheripheral id.
         * \param[in] cPacketId used to set the packet id.
         * \param[in] r_const_strDATA used to set the data.
         * \return It returns the data which is to be sent to co-processor.
         */
        static QString formPacket(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA);

//        /**
//         * \var bool m_bCapsLock
//         * \brief used store Caps lock status of Keypad.
//         */
//        bool m_bCapsLock;

    private:

        /**
         * \var QextSerialPort *m_serialportCoProcessor
         * \brief used to connect the co-processor via serialport.
         */
        QextSerialPort *m_serialportCoProcessor;
        /**
         * \var QMutex mutex
         * \brief used to lock and unlock the code for serialise the process.
         */
        QMutex m_mutex;
        /**
         * \var QString m_strLastkeypadMode
         * \brief used to store the last keypad mode string for verify the mode is changed.
         */
        QString m_strLastkeypadMode;
        /**
         * \var QString m_strRootPassword
         * \brief used to store the received boot password.
         */
        QString m_strRootPassword;
        /**
         * \var QDialog *m_dialogPrint
         * \brief used to show the dialog when paper is not available when printing.
         */
        QDialog *m_dialogPrint;
        /**
         * \var extern float fADCValue
         * \brief used to store ADCValue.
         */
        float fADCValue;
        /**
         * \var QLabel *m_labelPrinterStatus
         * \brief used to display the status of the printer.
         */
        QLabel *m_labelPrinterStatus;
        /**
         * \var QString m_strPreviousData
         * \brief used to store last received data from the co-processor or incomplete response data.
         */
        QString m_strPreviousData;
        /**
         * \var QString m_strMachineId
         * \brief used to store the received Machine id .
         */
        QString m_strMachineId;
        /**
         * \var QString m_strPicVersion
         * \brief used to store the received co-processor version.
         */
        QString m_strPicVersion;
        /**
         * \var QString m_strPicDateTime
         * \brief used to store the received co-processor date & time.
         */
        QString m_strPicDateTime;
        /**
         * \var QString m_strDeviceModel
         * \brief used to store the received device model name.
         */
        QString m_strDeviceModel;
        /**
         * \var QString m_strRtc
         * \brief used to store the received RTC data when testRtc().
         */
        QString m_strRtc;
        /**
         * \var QString m_strLogData
         * \brief used to store the received power/process log data.
         */
        QString m_strLogData;
	    /**
         * \var QString m_strMCRData
         * \brief used to store the received MCR data.
         */
        QString m_strMCRData;
        /**
         * \var QDateTime m_dateTimeSystem
         * \brief used to store the received datetime.
         */
        QDateTime m_dateTimeSystem;
        /**
         * \var QPushButton *m_pushButtonPrint
         * \brief used to display print button in dialog.
         */
        QPushButton *m_pushButtonPrint;
        /**
         * \var QPushButton *m_pushButtonCancel
         * \brief used to display cancel button in dialog.
         */
        QPushButton *m_pushButtonCancel;
        /**
         * \var QLabel *m_labelImage
         * \brief used to display grayscale image.
         */
        QLabel *m_labelImage;
        /**
         * \var QSlider *m_sliderBrightness
         * \brief used to set the brightness value of the grayscale image.
         */
        QSlider *m_sliderBrightness;
        /**
         * \var QImage m_imageGrayScale
         * \brief used to store the graysacle printing image.
         */
        QImage m_imageGrayScale;
        /**
         * \var QDialog *m_dialogGrayScale
         * \brief used to show the dialog when grayscale printing.
         */
        QDialog *m_dialogGrayScale;
        /**
         * \var E_ChargeStatus geChargeStatus
         * \brief used to store charging status.
         */
        E_ChargeStatus m_eChargeStatus;
        /**
         * \var bool m_bResponse
         * \brief used to store the response from the co-processor of last sent command.
         */
        bool m_bResponse;
        /**
         * \var bool m_bHandshakePIC
         * \brief used to store the handshake status of the co-processor.
         */
        bool m_bHandshakePIC;
        /**
         * \var bool m_bThreadRunning
         * \brief used to store the thread is running or not.
         */
        bool m_bThreadRunning;
        /**
         * \var bool m_bThreadPause
         * \brief used to store the thread is paused or not.
         */
        bool m_bThreadPause;
        /**
         * \var bool bIdleMode
         * \brief used to store the co-processor is in idle or not.
         */
        bool m_bIdleMode;
        /**
         * \var bool m_bPrintClicked
         * \brief used to store print button is clicked in print dialog.
         */
        bool m_bPrintClicked;
        /**
         * \var bool m_bPrintCanceled
         * \brief used to store cancel button is clicked in print dialog.
         */
        bool m_bPrintCanceled;
        /**
         * \var bool m_bNegativeAck
         * \brief used to store co-process has given the negative acknowledgement.
         */
        bool m_bNegativeAck;
        /**
         * \var bool m_bDoorClosed
         * \brief used to store door is closed or opened when printing.
         */
        bool m_bDoorClosed;
        /**
         * \var bool m_bPrinterReady
         * \brief used to store printer is ready or not.
         */
        bool m_bPrinterReady;
        /**
         * \var bool m_bPrinterReady
         * \brief used to store paper is avaliable or not for printing.
         */
        bool m_bPaperAvailable;
        /**
         * \var bool m_bBatteryCharging
         * \brief used to store battery is charging or not.
         */
        bool m_bBatteryCharging;
        /**
         * \var bool m_bInvalidCharger
         * \brief used to set invalid charger status.
         */
        bool m_bInvalidCharger;
        /**
         * \var bool m_bCapsLock
         * \brief used store Caps lock status of Keypad.
         */
        bool m_bCapsLock;
        /**
         * \var bool m_bKeypadModeLocked
         * \brief used store Keypad lock status.
         */
        bool m_bKeypadModeLocked;
        /**
         * \var int m_nCount
         * \brief used to check 5 times to avg ADC value of the battery.
         */
        int m_nCount;
        /**
         * \var int nADCValue
         * \brief used to store ADC value.
         */
        int nADCValue;
        /**
         * \var int m_nADCTotal
         * \brief used to store the sum of last 5 ADC value.
         */
        int m_nADCTotal;
        /**
         * \var int m_nADCMaxValue
         * \brief used to check store the maximum ADC value.
         */
        int m_nADCMaxValue;
        /**
         * \var int m_nADC_VALUE_SHUTDOWN
         * \brief used to store the ADC value for shutdown.
         */
        int m_nADC_VALUE_SHUTDOWN;
        /**
         * \var int m_nPrevBatt
         * \brief used to store the previous battery percentage.
         */
        int m_nPrevBatt;

        /**
         * \fn virtual void run()
         * \brief The starting point for the thread. this function is remplemented of thread class.
         * it performs to get the battery status & keypad mode.
         */
        virtual void run();

        /**
         * \fn bool portInitialize(const QString &r_const_strPORTNAME)
         * \brief This function is used to intialize the co-processor port.
         * \param[in] r_const_strPORTNAME used to set the port name.
         * \return It returns true, if port opened successfully; otherwise returns false.
         */
        bool portInitialize(const QString &r_const_strPORTNAME);

        /**
         * \fn bool sendData(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA, long nWait)
         * \brief This function is used to format & transmit the data to co-processor.
         * \param[in] cPheripheralId used to set the pheripheral id.
         * \param[in] cPacketId used to set the packet id.
         * \param[in] r_const_strDATA used to set the data.
         * \param[in] nWait used to set the time out in milliseconds.
         * \return It returns true, if the command executed successfully; otherwise returns false.
         */
        bool sendData(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA, long nWait);

        /**
         * \fn bool sendImage(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA, long nWait)
         * \brief This function is used to format & transmit the image data to co-processor for printing.
         * \param[in] cPheripheralId used to set the pheripheral id.
         * \param[in] cPacketId used to set the packet id.
         * \param[in] r_const_strDATA used to set the data.
         * \param[in] nWait used to set the time out in milliseconds.
         * \return It returns true, if the command executed successfully; otherwise returns false.
         */
        bool sendImage(QChar cPheripheralId, QChar cPacketId, const QByteArray &bytearrayImage, long nWait);
        /**
         * \fn bool sendData(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA, long nWait)
         * \brief This function is used to transmit the formatted data to co-processor.
         * \param[in] r_const_strDATA used to set the data.
         * \param[in] nWait used to set the time out in milliseconds.
         * \return It returns true, if the command executed successfully; otherwise returns false.
         */
        bool sendData(const QString &r_const_strDATA, long nWait);

        /**
         * \fn bool waitForPrinting()
         * \brief This function is used to wait for reprint or cancel the print when paper is not available.
         * \return It returns true, if the reprint is needed; otherwise returns false.
         */
        bool waitForPrinting();

        /**
         * \fn bool loadImage(const QImage &r_const_imageLOAD,QChar cPacketId, int nMaxHeight, int nMaxWidth)
         * \brief This function is used load the header/footer image to co-processor for printing.
         * The maximum image width and hight should be 384*50.
         * \param[in] r_const_imageLOAD used to specify the image which is to be loaded.
         * \param[in] cPacketId used to set the packet id for header/footer image.
         * \param[in] nMaxHeight used to set the image height need to be sent. co-processor maximum height is 50.
         * \param[in] nMaxWidth used to set the width need to be sent. co-processor maximum width is 384.
         * \return It returns true, if the header/footer image loaded successfully; otherwise returns false.
         */
        bool loadImage(const QImage &r_const_imageLOAD,QChar cPacketId, int nMaxHeight, int nMaxWidth);

        /**
         * \fn int getBatteryLevel(int nPercentage)
         * \brief This function is used to calculate the battery level given by battery percentage.
         * \param[in] nPercentage used to set battery percentage. it should be 0 to 100.
         * \return It returns the battery level. the value should be 0 to 5.
         */
        int getBatteryLevel(int nPercentage);

        /**
         * \fn void arrivedData()
         * \brief This function is used to read the available data from the port.
         */
        void arrivedData();

        /**
         * \fn void handleMessage(const QString &r_const_strDATA)
         * \brief This function is used to handle for process the received data.
         * \param[in] r_const_strDATA used to set the received data.
         */
        void handleMessage(const QString &r_const_strDATA);

        /**
         * \fn bool grayscalePrint(const QImage &r_const_imageGRAYSCALE)
         * \brief This function is used to process the image into the grayscale and transmit the data.
         * now it has been removed in the co-processor.
         * The maximum image width should be 132 which is fixed in the co-processor.
         * \param[in] r_const_imageGRAYSCALE used to specify the image which is to be printed.
         * \return It returns true, if the image is printed successfully; otherwise returns false.
         */
        bool grayscalePrint(const QImage &r_const_imageGRAYSCALE);

        /**
         * \fn QString checkSum(const QString &r_const_strDATA)
         * \brief This function is used to calculate the checksum value.
         * \param[in] r_const_strDATA used to set the data for calculate checksum.
         * \return the checksum value in 2 byte hex string.
         */
        static QString checkSum(const QString &r_const_strDATA);

        /**
         * \fn QString ImagecheckSum(const QString &r_const_strHDRDATA, const QString &r_const_strIMGDATA)
         * \brief This function is used to calculate the checksum value.
         * \param[in] r_const_strHDRDATA used to set the print header data for calculate checksum.
         * \param[in] r_const_strIMGDATA used to set the hex converted image data for calculate checksum.
         * \return the checksum value in 2 byte hex string.
         */
        QString ImagecheckSum(const QString &r_const_strHDRDATA, const QByteArray &r_const_strIMGDATA);

    signals:    /** Signals */
        /*\@{*/
        /**
         * \fn void batteryLevel(int nLevel,int nPercentage,float nValue)
         * \brief This signal is emitted whenever batter level & percentage value is changed.
         * \param[in] nLevel it gives the battery level. It would be 0 to 5.
         * \param[in] nPercentage it gives the battery percentage. It would be 0 to 100.
         */
        void batteryLevel(int nLevel,int nPercentage);
//        /**
//         * \fn void batteryLevel(int nLevel,int nPercentage,float nValue)
//         * \brief This signal is emitted whenever batter level & percentage value is changed.
//         * \param[in] nLevel it gives the battery level. It would be 0 to 5.
//         * \param[in] nPercentage it gives the battery percentage. It would be 0 to 100.
//         */
//        void batteryValue(float fvalue);
        /**
         * \fn void batteryChargeStatus(E_ChargeStatus eStatus)
         * \brief This signal is emitted whenever battery charge status is changed.
         * \param[in] eStatus it gives the charging status as Connected/Removed/Completed/Invalid.
         *
         * \sa see also E_ChargeStatus.
         */
        void batteryChargeStatus(E_ChargeStatus eStatus);

        /**
         * \fn keypadMode(E_KeypadMode eMode,bool CapsLockOn)
         * \brief This signal is emitted whenever keypad mode is changed.
         * \param[in] eMode it gives the keypad mode whether Numeric/Alphabets
         * \param[in] bCapsOn it gives the CapsLock is ON/OFF.
         *
         * \sa see also E_KeypadMode.
         */
        void keypadMode(E_KeypadMode eMode,bool bCapsOn);

        /**
         * \fn void keypadModeLocked( bool bModeLocked )
         * \brief This signal is emitted whenever keypad mode is locked / unlocked.
         * \param[in] bModeLocked it gives the keypad mode is LOCKED/UNLOCKED.
         *
         */
        void keypadModeLocked( bool bModeLocked );

        /**
         * \fn void shutdown(bool bMessage)
         * \brief This signal is emitted whenever shutdown is called by co-processor
         * \param[in] bMessage it gives the shutdown or shutdown dialod need to be shown.
         */
        void shutdown(bool bMessage);

        /**
         * \fn void volumeIncrease(bool bIncrease)
         * \brief This signal is emitted whenever speaker volume should be increased/decreased by using function key.
         * \param[in] bState used to set value as Increase/Decrease.
         */
        void volumeIncrease(bool bState);

        /**
         * \fn wakeup(bool bflagStandby)
         * \brief This signal is emitted for intimate wakeup from idle or standby mode.
         * \param[in] bflagStandby it gives the wakeup is standby or not.
         */
        void wakeup(bool bflagStandby);

        /**
         * \fn void resetTimer()
         * \brief This signal is emitted for reset the timer of keypadlock,idle,and standby.
         */
        void resetTimer();

        /**
         * \fn void showDesktop()
         * \brief This signal is emitted for intimate the first application when the staus changed in shared memory.
         */
        void showDesktop();

        /*\@}*/

    public slots:
        /**
         * \fn void startThread()
         * \brief This function is used to start the thread for get the battery status and keypad mode.
         */
        void startThread();

        /**
         * \fn void pauseThread()
         * \brief This function is used to pause the thread.
         */
        void pauseThread();

        /**
         * \fn void stopThread()
         * \brief This function is used to stop the thread.
         */
        void stopThread();

    private slots:
        /**
         * \fn void updateBrightness()
         * \brief This function is used to update the brightness level in grayscale image.
         */
        void updateBrightness();
        /**
         * \fn void on_pushButtonPrint_clicked()
         * \brief This function is used to intimate reprint.
         */
        void on_pushButtonPrint_clicked();
        /**
         * \fn void on_pushButtonCancel_clicked()
         * \brief This function is used to intimate cancel the print.
         */
        void on_pushButtonCancel_clicked();
    };
}

#endif // CPHERIPHERALS_H
