/**
 * \file "cgsmmodule.h"
 * \brief it provides an various function for communicate with gsm module.
 *
 * This file is used to process various gsm related functions.
 * For more details about AT commands you can refer "SIM900_AT_Command_Manual_V1.03" document.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CGSMMODULE_H
#define CGSMMODULE_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QThread>
#include <QString>
#include <QList>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include "qextserialport.h"
#include "chhc80xx.h"

namespace ClanCor
{
/**
     * \class CGsmModule
     * \brief The CGsmModule class provides the methods for communicate with gsm module.
     *
     * It inherits QThread class for get signal strenght in threading.
     */
class CGsmModule : public QThread
{
    Q_OBJECT

public:
    /**
         * \fn CGsmModule(const QString &r_const_strPORTNAME)
         * A constructor.
         * \brief class used to send & receive the AT commands to/from gsm module. Also used to enable / disable gprs.
         * \arg[in] r_const_strPORTNAME used to set the gsm port name.
         */
    CGsmModule(const QString &r_const_strPORTNAME);

    /**
         * \fn ~CGsmModule()
         * A destructor.
         * \brief Stop the thread and destroys the allocated resources.
         */
    ~CGsmModule();


    //Testing

   bool getGPSPosition(QString &r_strLatitude, QString &r_strLongitude);


    /**
         * \fn bool isInitiated()
         * \brief This function is used to check whether gsm module is initiated succesfully or not.
         * \return It returns true, if module initiated successfully; otherwise returns false.
         */
    bool isInitiated() const { return m_bModuleInitiated; }

    /**
         * \fn QString getLastError()
         * \brief This function is used to get the error information about the last error (if any) that occurred with this class function.
         * if any function of this class returns false, use this function to get the error information.
         * \return It returns the last error information.
         */

     QString myvariable; //edit ram 24feb14

    QString getLastError() const { return m_strError; }

    /**
         * \fn bool initModule()
         * \brief This function is used to initialize the gsm module.
         * \return It returns true, if module initiated successfully; otherwise returns false.
         */
    bool initModule();

    /**
         * \fn bool initiatedModule()
         * \brief This function is used to initiate the default command for second application call.
         * \return It returns true, if module initiated successfully; otherwise returns false.
         */
    bool initiatedModule();

    /**
         * \fn bool getNetwork(QString &r_NetworkName)
         * \brief This function is used to get the current operator name.
         * \param[out] r_OperatorName used to get the current operator name.
         * \return It returns true, if operation executed successfully; otherwise returns false.
         */
    bool getNetwork(QString &r_NetworkName);

    /**
         * \fn bool getOperatorList(QList<QString> &r_listOperators)
         * \brief This function is used to get list of network operators available.
         * \param[out] r_listOperators used to get the available operators.
         * \return It returns true, if operation executed successfully; otherwise returns false.
         */
    bool getOperatorList(QList<QString> &r_listOperators);

    /**
         * \fn  bool checkNetwork()
         * \brief This function is used Check network Registration Status.
         * \return It returns true, if Network Registred successfully; otherwise returns false.
         */
    bool checkNetwork();
    /**
         * \fn bool setGprsApn(const QString &r_const_strAPNNAME)
         * \brief This function is used to set the apn name for the current network.
         * \param[in] r_const_strAPNNAME used to set the Apn address of the current network.
         * \return It returns true, if the apn send successfully; otherwise returns false.
         */
    bool setGprsApn(const QString &r_const_strAPNNAME);

    /**
         * \fn bool setGprsNetwork(const QString &r_const_strAPNNAME,const E_NetworkMode &r_const_eNetworkMode)
         * \brief This function is used to set the Network operator Manually or Auto.
         * \param[in] r_const_strNetworkID used to set the NetworkId for the Modual.
         * \param[in] r_const_eNetworkMode used to set the NetworkMode (Manual/Auto) for the Modual.
         * \return It returns true, if the apn send successfully; otherwise returns false.
         */

    bool setGprsNetwork(const QString &r_const_strNetworkID,const E_NetworkMode &r_const_eNetworkMode);

    /**
         * \fn int writeSms(const QString &r_const_strDESTINATION, const QString &r_const_strMESSAGE)
         * \brief This function is used to send the SMS message.
         * \param[in] r_const_strDESTINATION used to set the Destination.
         * \param[in] r_const_strMESSAGE used to set Message information.
         * \return It returns, index value returned from GSM module, if write operation executed successfully; otherwise returns -1.
         */
    int writeSms(const QString &r_const_strDESTINATION, const QString &r_const_strMESSAGE);

    /**
         * \fn bool readSms(QList<CHHC80xx::SSmsDetail> &r_listMessages, CHHC80xx::E_MessageState eState)
         * \brief This function is used to read the SMS message.
         * \param[out] r_listMessages used to receive the messages.
         * \param[in] eState used to set Message state.
         * \return It returns true, if read operation executed successfully send to the network; otherwise returns false.
         *
         * \sa see also CHHC80xx::SSmsDetail and CHHC80xx::E_MessageState.
         */
    bool readSms(QList<CHHC80xx::SSmsDetail> &r_listMessages, CHHC80xx::E_MessageState eState);

    /**
         * \fn deleteSms(int nIndex)
         * \brief This function is used to delete message from preferred message location.
         * \param[in] nIndex used to set associated memory location.
         * \return It returns true, if message deleted successfully; otherwise returns false.
         */
    bool deleteSms(int nIndex);

    /**
         * \fn bool smsDeliveryStatus(const int const_nSMSIndex);
         * \brief This function is used to retrieve SMS Delivery status from the internal SMS delivery queue,
         * \ that is, it will check the delivery status of SMS index passed as argument.
         * \param[in] const_nSMSIndex used to pass Delivered SMS index value.
         * \return It returns true, if message delivered successfully; otherwise returns false.
         */
    bool smsDeliveryStatus(const int const_nSMSIndex);

    bool testGPS();

    /**
         * \fn bool enableGprs()
         * \brief This function is used to enable the gprs connectivity.
         * \return It returns true, if gprs enabled successfully; otherwise returns false.
         */
    bool enableGprs();

    /**
         * \fn bool disableGprs()
         * \brief This function is used to disable the gprs connectivity.
         * \return It returns true, if gprs disabled successfully; otherwise returns false.
         */
    bool disableGprs();

    /**
         * \fn bool gsmATCommand(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec)
         * \brief This function is used to send command to gsm module, and stores the response into the passed reference argument.
         * It will wait for response from module until timeout. It wont decode or process the response like sendCommand() member function.
         * \param[in] const_strCOMMAND used to pass the AT commands to be executed.
         * \param[out] r_const_strRESPONSE used to set the response text from GSM module, for the given AT commands.
         * \param[in] nTimeout_mSec used to set the time out in milliseconds.
         * \return It returns true, if executed successfully; otherwise returns false.
         */
    bool gsmATCommand(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec);

    /**
         * \fn bool testModule()
         * \brief This function is used to test the Gprs module.
         * It will show messagebox with information like Tower lelel, operator and gprs connectivity status,..,etc.
         * \return It returns true, if test is succeeded; otherwise returns false.
         */
    bool testModule();

    /**
         * \fn bool gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel)
         * \brief This function is used to get the gsm network inforamtions.
         * It will assign the informations like operator name, IMI number, CSQ value and Tower level.
         * \param[in] r_strNetwork is a reference variable, used to assign the network name.
         * \param[in] r_strIMINumber is a reference variable, used to assign the IMI number.
         * \param[in] r_strCSQValue is a reference variable, used to assign the current CSQ value.
         * \param[in] r_strTowerlevel is a reference variable, used to assign the current tower level.
         * \return It returns true, if the gsm module is initialized and working properly; otherwise returns false.
         */
    bool gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel);

    /**
         * \fn void idle()
         * \brief This function is used to detach the network.
         */
    void idle();

    /**
         * \fn void wakeup()
         * \brief This function is used to atatch the network.
         */
    void wakeup();

    /**
         * \fn void startThread()
         * \brief This function is used to start the thread for get the signal strenght.
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

    /**
         * \fn void switchDatamode()
         * \brief This function is used to switch to command mode after disabling GPRS.
         */
    void switchDatamode();

    /**
         * \var int m_nCSQValue
         * \brief used to store last csq value of the signal quality.
         */
    int m_nCSQValue;

    signals:    /** Signals */
        /*\@{*/

        /**
             * \fn void gsmNetworkSignal(int nLevel)
             * \brief This signal is emitted whenever signal level is changed.
             * \param[in] nLevel it gives the signal level. The signal level would be 0 to 5.
             */
        void gsmNetworkSignal(int nLevel);

    /**
         * \fn void modReady()
         * \brief This signal is emitted when sim is registered with network.
         */
    void modReady();

    /*\@}*/

private:
//    /**
//         * \var QTimer *gprsporttimer
//         * \brief used to start the timer and wait for 3 min else retry.
//         */
//    QTimer *gprsporttimer;
    /**
         * \var QextSerialPort *m_serialportSimCom
         * \brief used to connect the gsm module via serialport.
         */
    QextSerialPort *m_serialportSimCom;
    //Testing
    /**
         * \var QextSerialPort *m_serialportCMUX3
         * \brief used to connect the gsm module via serialport.
         */
    QextSerialPort *m_serialportCMUX3;
    /**
         * \var QMutex m_Mutex
         * \brief used to lock and unlock the code for serialise the process.
         */
    QMutex m_Mutex;
    /**
         * \var bool m_bResponse
         * \brief used to store the response from the gsm module.
         */
    bool m_bResponse;

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
         * \var bool m_bModuleInitiated
         * \brief used to store the module is initiated or not.
         */
    bool m_bModuleInitiated;
    //        /**
    //         * \var bool m_bModuleReady
    //         * \brief used to store the module ready status for enable gprs operation.
    //         */
    //        bool m_bModuleReady;
    /**
                 * \var bool m_bOperatorList
                 * \brief used to store the whether the operator List is taken for Alignment.
                 */
    bool m_bOperatorList;
//    /**
//         * \var bool m_bModuleInitiated
//         * \brief used to store the gprs is disabled successfully.
//         */
//    bool m_bGprsDisabled;
    /**
         * \var bool m_bCMEError
         * \brief used to store the error given by module for last transmitted command.
         */
    bool m_bCMEError;

    /**
         * \var bool m_bNetworkMode
         * \brief used to store the Network Mode from the gsm module.
         * \brief 0 Means Automatic Mode 1 Means Manual Mode
         */
    bool m_bNetworkMode;

    /**
         * \var int m_nRegStatus
         * \brief used to store registration status of the current simcard.
         */
    int m_nRegStatus;

    /**
         * \var int m_nCount
         * \brief used to store count value for check the gprs connectivity.
         */
    int m_nCount;
    /**
         * \var int m_nTowerLevel
         * \brief used to store the previous value of the tower level .
         */
    int m_nTowerLevel;
    /**
         * \var int m_nCurrentSmsMode
         * \brief used to store the curent sms mode it will be 0 (PDU Mode) or 1(Text Mode).
         */
    int m_nCurrentSmsMode;
    /**
         * \var int m_nSMSSentIndex
         * \brief used to store the index returned by GSM module for currently sent SMS.
         */
    int m_nSMSSentIndex;
    /**
         * \var int m_nSMSDeliveredIndex
         * \brief used to store the index of SMS delivered returned by GSM module for currently sent SMS.
         */
    int m_nSMSDeliveredIndex;
    /**
         * \var QDialog *m_dialogGprs
         * \brief used to show the dialog when enabling the gprs & searching list of networks.
         */
    QDialog *m_dialogGprs;
    /**
         * \var QLabel *m_labelStatus
         * \brief used to show the status in the gprs dialog.
         */
    QLabel *m_labelStatus;
    /**
         * \var QTimer m_timerGprsConnect
         * \brief used for checking gprs connection.
         */
    QTimer m_timerGprsConnect;
//    /**
//         * \var QTimer m_timerGprsDisconnected
//         * \brief used for process after gprs disconnected.
//         */
//    QTimer m_timerGprsDisconnected;
    /**
         * \var QList<QString> m_listOperators
         * \brief used to store the available operator list.
         */
    QList<QString> m_listOperators;
    /**
         * \var QList<CHHC80xx::SSmsDetail> m_listSmsDetails
         * \brief used to store sms data into sms structured list.
         */
    QList<CHHC80xx::SSmsDetail> m_listSmsDetails;

    /**
         * \var QString m_str2SocketIP
         * \brief used to store IP address of second socket.
         */
    QString m_str2SocketIP;
    /**
         * \var QString m_strCellinfo
         * \brief used to store network cell information(means like the adv,location).
         */
    QString m_strCellinfo;
    /**
         * \var QString m_strIMINo
         * \brief used to store the IMI number of the gsm module.
         */
    QString m_strIMINo;
    /**
         * \var QString m_strManufacturer_Name
         * \brief used to store the Manufacturer Name of the gsm module.
         */
    QString m_strManufacturer_Name;
    /**
         * \var QString m_strPreviousData
         * \brief used to store last received data from the module or incomplete response data.
         */
    QString m_strPreviousData;
    /**
         * \var QString m_strNetwork
         * \brief used to store the current network name.
         */
    QString m_strNetwork;
    /**
         * \var QString m_strNetwork
         * \brief used to store the error information.
         */


    QString m_strError;
    /**
         * \var QString m_strNetwork
         * \brief used to store the apn name for after standby to send the module.
         */
    QString m_strApnName;
    /**
         * \var QString m_strNetworkInfo
         * \brief used to store network cell information.
         */
    QString m_strNetworkInfo;
    /**
         * \var QString m_strlistGPS
         * \brief used to store GPS position from the the module.
         */

    QStringList m_strlistGPS;





//    /**
//         * \var QString m_strGPRSGPSPosition
//         * \brief used to store network cell information.
//         */
//    QString m_strGPRSGPSPosition;
////    /**
////         * \var QString m_strGPRSGPSLatitude
////         * \brief used to store network cell information.
////         */
////    QString m_strGPRSGPSLatitude;
////    /**
////         * \var QString m_strGPRSGPSLongitude
////         * \brief used to store network cell information.
////         */
////    QString m_strGPRSGPSLongitude;

    /**
         * \fn virtual void run()
         * \brief The starting point for the thread. this function is remplemented of thread class.
         * it performs to get the network signal strenght.
         */
    virtual void run();
    /**
         * \fn bool portInitialize(const QString &r_const_strPORTNAME)
         * \brief This function is used to intialize the gsm port.
         * \param[in] r_const_strPORTNAME used to set the port name.
         * \return It returns true, if port opened successfully; otherwise returns false.
         */
    bool portInitialize(const QString &r_const_strPORTNAME);
    //Testing
    /**
         * \fn bool portInitialize(const QString &r_const_strPORTNAME)
         * \brief This function is used to intialize the gsm port.
         * \param[in] r_const_strPORTNAME used to set the port name.
         * \return It returns true, if port opened successfully; otherwise returns false.
         */
    bool portInitializeCmux3(const QString &r_const_strPORTNAME);
    /**
         * \fn int readSerialData(QString &r_const_strReadBuffer)
         * \brief This function is used to read data retrieved from serial port.
         * it will return the size of data read through serial port.
         * \param[out] r_const_strReadBuffer used to set the data retrieved from serail port.
         * \return It returns size of data read from serial port as interger.
         */
    int readSerialData(QString &r_const_strReadBuffer);
    /**
         * \fn int writeSerialData(const QString &r_const_strDataToWrite)
         * \brief This function is used to write the given data into the serial port.
         * it will return the size of data wrote through serial port.
         * \param[in] r_const_strDataToWrite used to pass the data to be written on serail port.
         * \return It returns size of data wrote on serial port as interger.
         */
    int writeSerialData(const QString &r_const_strDataToWrite);
    /**
         * \fn bool sendCommand(const QString &r_const_strCOMMAND ,long nWait)
         * \brief This function is used to send the command to gsm module.
         * it will wait for response from module until timeout.
         * \param[in] r_const_strCOMMAND used to set the AT commands.
         * \param[in] nWait used to set the time out in milliseconds.
         * \return It returns true, if executed successfully; otherwise returns false.
         */
    bool sendCommand(const QString &r_const_strCOMMAND ,long nWait);
    /**
         * \fn void arrivedData()
         * \brief This function is used to read the available data from the port.
         */
    void arrivedData();

    /**
         * \fn void processPrevData()
         * \brief This function is used to process the received prevoius data, this
         * this function is mainly used to process unsolicited results reaceived from GSM module (eg, CDS (SMS Delivery status), CBM (Network information) etc).
         */
    void processPrevData();
    /**
         * \fn void handleMessage(const QString &r_const_strDATA)
         * \brief This function is used to handle for process the received data.
         * \param[in] r_const_strDATA used to set the received data.
         */
    void handleMessage(const QString &r_const_strDATA);
    /**
         * \fn int towerLevel(int nCsqValue,int nBer)
         * \brief This function is used to calculate the tower level using csq value and ber.
         * \param[in] nCsqValue used to set the CSQ value.
         * \param[in] nBer used to set the Ber value.
         * \return It returns the tower level. the value should be 0 to 5.
         */
    int towerLevel(int nCsqValue,int nBer);
    /**
         * \fn void handleOperators(const QList<QString> &r_const_listOperators)
         * \brief This function is used to handle for process the received data.
         * \param[in] r_const_listOperators used to set operator data.
         */
    void handleOperators(const QList<QString> &r_const_listOperators);
    /**
         * \fn void handleSmsDetails(const QList<QString> &r_const_listSMSDATA)
         * \brief This function is used to handle for process the list of sms received data.
         * \param[in] r_const_listOperators used to set operator data.
         */
    void handleSmsDetails(const QList<QString> &r_const_listSMSDATA);
    /**
         * \fn void handleSmsDeliveryStatus(const int const_nSMSIndex)
         * \brief This function is used to handle SMS Delivery status received from GSM module,
         * \ that is, it will update SMS status stored with status SENT to DELIVERED.
         * \param[in] const_nSMSIndex used to pass Delivered SMS index value.
         */
    void handleSmsDeliveryStatus(const int const_nSMSIndex);
    /**
         * \fn void deleteDeliveryStatus();
         * \brief This function is used to delete SMS Delivery status from internal queue,
         * \ that is, delete operation is based on 12 hours after SENT or DELIVER status received.
         */
    void deleteDeliveryStatus();

private slots:
    /**
         * \fn void on_timerClose_timeout()
         * \brief This function is used to close the dialog until gprs is connected or timeout.
         */
    void on_timerClose_timeout();
//    /**
//         * \fn void on_timerGprsPortClose_timeout()
//         * \brief This function is used to close the Port port connected or timeout.
//         */
//    void on_timerGprsPortClose_timeout();
    /**
         * \fn void on_timerGprsDisconnect_timeout()
         * \brief This function is used to open the port after gprs is disabled.
         */
    void on_timerGprsDisconnect_timeout();

};
}
#endif // CGSMMODULE_H
