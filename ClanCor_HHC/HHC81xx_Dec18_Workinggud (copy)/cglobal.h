/**
 * \file "cglobal.h"
 * \brief it provides a global variables & function for sharing multiple files
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CGLOBAL_H
#define CGLOBAL_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#ifdef Q_WS_QWS
#include <QWSServer>
#endif
#include <QtGui>
#include <QSharedMemory>
#include "qextserialport.h"
#include "cpheripherals.h"
#include "cgsmmodule.h"
#include "cbarcode.h"
#include "cinputmethod.h"
#include "chhc80xx.h"
#include "cnetwork.h"
#include "cconfig.h"
#include<gps_data.h>
#if DEBUG
#define DEBUGMESSAGE(text) qDebug()<<"\r"<<text
#else
#define DEBUGMESSAGE(text)
#endif

namespace ClanCor
{
/*\@{*/
/* these string are used to write in shared memory to process it */
const QString const_strRUNNING                  = "Running";
const QString const_strSTARTED                  = "Started";
const QString const_strPAUSED                   = "Paused";
const QString const_strCOMPLETED                = "Completed";
const QString const_strIDLESTATUS               = "IdleStatus";
const QString const_strPAUSETIMER               = "PauseTimer";
const QString const_strRESUMETIMER              = "ResumeTimer";
const QString const_strWAIT                     = "Wait";
const QString const_strPAUSE_THREADS            = "PauseThreads";
const QString const_strWAKEUP_THREADS           = "WakeupThreads";
const QString const_strSHOW_DESKTOP             = "ShowDesktop";
const QString const_strKEYPAD_NUMERIC           = "SetKeypadN";
const QString const_strKEYPAD_ALPHABETS         = "SetKeypadA";
const QString const_strKEYPAD_ALPHABETS_CAPS    = "SetKeypadAU";
const QString const_strCHARGESTATUS             = "ChargeStat";
const QString const_strCHARGESTATUS_CLOSE       = "ChargeStatClose";
const QString const_strENABLEWIFI               = "EnableWifi";
const QString const_strDISABLEWIFI              = "DisableWifi";
const QString const_strWIFIPROCESS_FAILED       = "WifiProsFailed";
const QString const_strCHARGESTATUS_CONNECTED   = "ChargerCon";
const QString const_strCHARGESTATUS_REMOVED     = "ChargerRem";
const QString const_strCHARGESTATUS_COMPLETED   = "ChargeFull";
const QString const_strCHARGESTATUS_INVALID     = "ChargerInvld";
const QString const_strGPRS_CONNECTED           = "GPRSConnected";
const QString const_strGPRS_DISCONNECTED        = "GPRSDisConnected";
const QString const_strGPRS_CONNECTEDCMUX       = "GPRSConnectedCMUX";
const QString const_strGSM_MODULE_COMM_ERR      = "GSM Module Communication Failed";
const QString const_strERROR                    = "Error->";



/*\@}*/

/* It defines the maximum character should store in shared memory */
const int const_nSHAREDM_MEMORY_MAXSIZE         = 50;

namespace Global
{
/**
         * \struct SNetworkIP
         * \brief This structue is used to store IP details of network interface.
         *
         * It stores the IP details of network interface.
         */
struct SNetworkIP
{
    QString m_strInterface; /** Network Interface */
    QString m_strIpAddress; /** IP Address */
    QString m_strSubnetMask; /** Subnet Mask */
    QString m_strGateway; /** Gateway */
};

/**
         * \var extern CPheripherals *gpheripheralsPIC
         * \brief used to access the co-processor functions.
         */
extern CPheripherals *gpheripheralsPIC;
/**
         * \var extern CGsmModule *ggsmModuleSimCom
         * \brief used to access the gsm module functions.
         */
extern CGsmModule *ggsmModuleSimCom;
/**
         * \var extern GPS_data *objGps
         * \brief used to access the GPS functions.
         */
extern GPS_data *objGps;
/**
         * \var extern QextSerialPort *gserialportDebug
         * \brief used to write the debug message to debug port via serialport.
         */

//extern QextSerialPort *gserialportDebug;

#ifdef Q_WS_QWS
/**
         * \var extern QWSServer *gserverObj
         * \brief used to access the qwsserver functions.
         */
extern QWSServer *gserverObj;
#endif
/**
         * \var extern CNetwork *gnetworkActive
         * \brief used to process the active network status.
         */
extern CNetwork *gnetworkActive;
/**
         * \var extern CInputMethod *ginputMethodObj
         * \brief used to access the input method class functions.
         */
extern CInputMethod *ginputMethodObj;
/**
         * \var extern CHHC80xxServer *ghhc80xxServerObj
         * \brief used to access the 80xx server functions.
         */
extern CHHC80xxServer *ghhc80xxServerObj;
/**
         * \var extern E_KeypadMode gekeypadModeCurrent
         * \brief used to store the last keypad mode.
         */
extern E_KeypadMode gekeypadModeCurrent;
/**
         * \var extern QSplashScreen *gsplash
         * \brief used to display splash messages.
         */
extern QSplashScreen *gsplash;
/**
         * \var extern QMutex gmutex
         * \brief used to lock and unlock the code for serialise the process.
         */
extern QMutex gmutex;
/**
         * \var extern QSharedMemory gsharedMemPIC
         * \brief used to create & access the sharedmemory of co-processor for intimate second applicaton call.
         */
extern QSharedMemory gsharedMemPIC;
/**
         * \var extern QSharedMemory gsharedMemGSM
         * \brief used to create & access the sharedmemory of gsm for intimate second applicaton call.
         */
extern QSharedMemory gsharedMemGSM;
///**
//         * \var extern QSharedMemory gsharedMemKey
//         * \brief used to create & access the sharedmemory of gsm for intimate second applicaton call.
//         */
//extern QSharedMemory gsharedMemKey;
/**
         * \var extern QSharedMemory gsharedMemNetwork
         * \brief used to create & access the sharedmemory of Network to share thread status information with second applicaton call.
         */
extern QSharedMemory gsharedMemNetwork;
//Testing
//extern QString gm_strGPRSGPSPosition;

extern QString gm_strGPRSGPSLatitude;

extern QString gm_strGPRSGPSLongitude;



/**
         * \var extern QString gstrDeviceModel
         * \brief used to store device model of ClanCor HHC.
         */
extern QString gstrDeviceModel;
/**
         * \var extern QLabel *glabelStatus
         * \brief used to directly display the status.
         */
extern QLabel *glabelStatus;
/**
         * \var extern bool gbFirsCall
         * \brief used to store the library is called by first time.
         */
extern bool gbFirsCall;
/**
         * \var extern bool gbProcessRunning
         * \brief used to store the process is running or not.
         */
extern bool gbProcessRunning;

/**
         * \var extern bool gbEnableMessageBox
         * \brief used to store whether we should Enable Debug Messages.
         */
extern bool gbEnableMessageBoxGSM;

/**
         * \var extern bool gbEnableMessageBoxPrinter
         * \brief used to store whether we should Enable Debug Messages.
         */
extern bool gbEnableMessageBoxPrinter;

/**
         * \var extern bool gbIdleStatus
         * \brief used to store whether we should allow idle or standby mode.
         */

extern bool gbIdleStatus;
/**
         * \var extern bool gbLanConnected
         * \brief used to store ethernet is connected or not.
         */
extern bool gbLanConnected;
/**
         * \var extern bool gbGprsAlwaysOn
         * \brief used to store gprs is always ON or OFF.
         */
extern bool gbGprsAlwaysOn;
/**
         * \var extern bool gbGprsConnected
         * \brief used to store gprs is connected or not.
         */
extern bool gbGprsConnected;
/**
         * \var extern bool gbAudioRunning
         * \brief used to store audio is running or not.
         */
extern bool gbAudioRunning;
/**
         * \var extern int gnGPRSModuleType
         * \brief used to store which GPRS Module whether SIMCOM or Telit.
         */
extern int gnGPRSModuleType;
/**
         * \var extern QString gstrCheckConfiguration
         * \brief used to check the configuration file.
         */

extern QString gstrCheckgpsConfiguration;
/**
         * \var extern QString gstrCheckGPRSConfiguration
         * \brief used to check the gprsconfiguration.
         */
extern QString gstrCheckGPRSConfiguration;

/**
         * \var extern QString gstrVirtualkey
         * \brief used to store the virtual key value.
         */
extern QString gstrVirtualkey;

/**
         * \fn void gInitialize()
         * \brief This function is used to allocate & initalize the resource for global object for any applciation call.
         */
void gInitialize();

/**
         * \fn void gTerminate()
         * \brief This function is used to destroy the allocated global resources.
         */
void gTerminate();

/**
         * \fn bool gLoadIntoSharedPIC(const QString &r_const_strDATA)
         * \brief This function is used to write the given data into co-processor shared memory .
         * \arg[in] r_const_strDATA used to pass the data to be write into shared memory.
         * \return it returns true, if data is written sucessfully; otherwise return false.
         */
bool gLoadIntoSharedPIC(const QString &r_const_strDATA);

/**
         * \fn bool gLoadFromSharedPIC(QString &r_strData)
         * \brief This function is used to read the data from co-processor shared memory .
         * \arg[in] r_const_strDATA used to get the data from shared memory.
         * \return it returns true, if data is read sucessfully; otherwise return false.
         */
bool gLoadFromSharedPIC(QString &r_strData);

///**
//         * \fn bool gLoadIntoSharedKey(const QString &r_const_strDATA)
//         * \brief This function is used to write the given data into gsm shared memory .
//         * \arg[in] r_const_strDATA used to pass the data to be write into shared memory.
//         * \return it returns true, if data is written sucessfully; otherwise return false.
//         */
//bool gLoadIntoSharedKey(const QString &r_const_strDATA);

///**
//         * \fn bool gLoadFromSharedKey(QString &r_strData)
//         * \brief This function is used to read the data from gsm shared memory .
//         * \arg[in] r_const_strDATA used to get the data from shared memory.
//         * \return it returns true, if data is read sucessfully; otherwise return false.
//         */
//bool gLoadFromSharedKey(QString &r_strData);

/**
         * \fn bool gLoadIntoSharedGSM(const QString &r_const_strDATA)
         * \brief This function is used to write the given data into gsm shared memory .
         * \arg[in] r_const_strDATA used to pass the data to be write into shared memory.
         * \return it returns true, if data is written sucessfully; otherwise return false.
         */
bool gLoadIntoSharedGSM(const QString &r_const_strDATA);

/**
         * \fn bool gLoadFromSharedPIC(QString &r_strData)
         * \brief This function is used to read the data from gsm shared memory .
         * \arg[in] r_const_strDATA used to get the data from shared memory.
         * \return it returns true, if data is read sucessfully; otherwise return false.
         */
bool gLoadFromSharedGSM(QString &r_strData);

/**
         * \fn bool gLoadIntoSharedNetwork(const QString &r_const_strDATA)
         * \brief This function is used to write the given data into Network shared memory .
         * \arg[in] r_const_strDATA used to pass the data to be write into shared memory.
         * \return it returns true, if data is written sucessfully; otherwise return false.
         */
bool gLoadIntoSharedNetwork(const QString &r_const_strDATA);

/**
         * \fn bool gLoadFromSharedNetwork(QString &r_strData)
         * \brief This function is used to read the current data from Network shared memory .
         * \arg[in] r_const_strDATA used to get the current data from shared memory.
         * \return it returns true, if data is read sucessfully; otherwise return false.
         */
bool gLoadFromSharedNetwork(QString &r_strData);


/**
         * \fn void gUpdateScreen(int nMsec = 100)
         * \brief Waits for executing the pending process.Updates the display for showing the window.
         * \param[in] nMsec set the waiting time for pending process.Default is 50 milliseconds.
         */
void gUpdateScreen(int nMsec = 100);

/**
         * \fn bool gNetworkIPDetails(const QString const_stringIface, SNetworkIP &r_NetworkIP) const;
         * \brief This function is used to get the Ip details of the provided network interface.
         * it will give the configuration details of the Wifi network.
         * \param[in] const_stringIface used to pass Network interface name as argument.
         * \param[out] r_NetworkIP passed as reference, used to store IP details of the given network interface.
         * \return It returns true, if configuration for the given network interface exists; otherwise returns false.
         *
         * \sa see also SNetworkIP.
         */
bool gNetworkIPDetails(const QString const_stringIface, SNetworkIP &r_NetworkIP);

/**
         * \fn QString gAlignNumber(qint64 nNumber,int nDigit)
         * \brief Converts the number from string and right justified with 0.
         * \param[in] nNumber given number for convert string.
         * \param[in] nDigit right justify string with number of digits.
         * \return it returns the converted string data.
         */
QString gAlignNumber(qint64 nNumber,int nDigit);

/**
         * \fn QString gConvertToString(const QVariant &r_const_variantDATA)
         * \brief This function is used to convert any datatype into string.
         * \param[in] r_const_variantDATA used to set the data for convert string.
         * \return it returns the converted string data.
         */
QString gConvertToString(const QVariant &r_const_variantDATA);

/**
         * \fn int gConvertToInt(const QString &r_const_strDATA)
         * \brief This function is used to convert text into integer.
         * \param[in] r_const_variantDATA used to set the data for convert integer.
         * \return it returns the converted int data.
         */
int gConvertToInt(const QString &r_const_strDATA);

/**
         * \fn bool gSysCommand(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput)
         * \brief This function is used to execute the system command and return the output.
         * \param[in] r_const_strCOMMAND used to set the system command.
         * \param[in] r_const_strARGS used to set the arguments of the system command.
         * \param[out] r_strOutput used to get the result of the command.
         * \return It returns true if successfully command is executed; otherwise return false.
         */
bool gSysCommand(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput);

bool gSysCommandtimeout(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput);

/**
         * \fn bool gSysCommand(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput)
         * \brief This is overloaded function.
         * This function is used to execute the system command.
         * \param[in] r_const_strCOMMAND used to set the system command.
         * \return It returns true if successfully command is executed; otherwise return false.
         */
bool gSysCommand(const QString &r_const_strCOMMAND);

/**
         * \fn void gPicDebugging(const QString &r_const_strDATA)tring &r_const_strARGS, QString &r_strOutput)
         * \brief This function is display the debug information of the co-processor.
         * \param[in] r_const_strCOMMAND used to set the raw data need to split debug data.
         */
void gPicDebugging(const QString &r_const_strDATA);

/**
         * \fn bool gPlayWav(const QString &r_const_strFILENAME)
         * \brief This function is used to play the wav file using mplayer.
         * \param[in] r_const_strFILENAME used to set the file name.
         * \return It returns true if successfully played; otherwise return false.
         */
bool gPlayWav(const QString &r_const_strFILENAME);

/**
         * \fn bool gPortInitialize(const QString &r_const_strPORTNAME)
         * \brief This function is used to intialize the debug port.
         * \param[in] r_const_strPORTNAME used to set the port name.
         * \return It returns true, if port opened successfully; otherwise returns false.
         */
bool gPortInitialize(const QString &r_const_strPORTNAME);

/**
         * \fn void gWriteDataToComport(const QString &r_const_strDATA)
         * \brief This function is used to write the debug data directly into debug port.
         * \param[in] r_const_strDATA used to set the debug data.
         */
void gWriteDataToComport(const QString &r_const_strDATA);
/**
         * \fn void gFreeCacheMemory()
         * \brief This function is used for force to free the cache memory.
         */
void gFreeCacheMemory();

}
}
#endif // GLOBAL_H
