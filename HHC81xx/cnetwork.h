/**
 * \file "cnetwork.h"
 * \brief it provides an interface for check an active network as ethernet, gprs or wifi.
 *
 * This file is used to communicate with the network interfaces.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CNETWORK_H
#define CNETWORK_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QThread>
#include <QDir>
#include "cnetworkstatus.h"
#include "chhc80xxserver.h"

namespace ClanCor
{
    /**
     * \class CNetwork
     * \brief The CNetwork class provides the methods for control the wifi device and emit the active network interface.
     *
     *  you can use this class to perform various operations.
     */
    class CNetwork : public QThread
    {
        Q_OBJECT
    public:
        /**
         * \fn CNetwork()
         * A constructor.
         * \brief intialize the socket & check the ethernet device is found or not.
         */
        CNetwork();

        /**
         * \fn ~CNetwork()
         * A destructor.
         * \brief Stop the thread and close the sockets.
         */
        ~CNetwork();

        /**
         * \fn QString getLastError()
         * \brief This function is used to get the error information about the last error (if any) that occurred with this class function.
         * if any function of this class returns false, use this function to get the error information.
         * \return It returns the last error information.
         */
        QString getLastError() const { return m_strError; }

        /**
         * \fn bool isWifi()
         * \brief This function returns the wifi is connected with network or not .
         * \return It returns true, if wifi is connected with network; otherwise return false.
         */
        bool isWifi() const { return m_bWifiConnectedNetwork; }

        /**
         * \fn bool isWifiFound()
         * \brief This function returns the wifi device is found with the device or not.
         * \return It returns true, if wifi device is found; otherwise return false.
         */
        bool isWifiFound() const { return m_bWifiDeviceFound; }
        /**
         * \fn void CheckWIFI()
         * \brief This function is used to Check wifi module.
         */
        void CheckWIFI();
        /**
         * \fn bool enableWifiModule()
         * \brief This function is used to enable the wifi module.
         * \return It returns true, if wifi module is enabled successfully; otherwise returns false.
         */
        bool enableWifiModule();
        /**
         * \fn bool disableWifiModule()
         * \brief This function is used to disable the wifi module.
         * \return It returns true, if wifi module is disabled successfully; otherwise returns false.
         */
        bool disableWifiModule(bool bIdleStanby);

        /**
         * \fn void restart()
         * \brief This function is used to restart to connect the wifi network again.
         * use this function when the wifi config details are changed.
         * \return It returns true, if wifi restarted successfully; otherwise returns false.
         */
        bool restart();

    public slots:
        /**
         * \fn void startThread()
         * \brief This function is used to start the thread for check the active network status.
         */
        void startThread();

        /**
         * \fn void startThreadWakeUp()
         * \brief This function is used to start the thread while wake up from idle or standby, to check the active network status.
         */
        void startThreadWakeUp();

        /**
         * \fn void pauseThread()
         * \brief This function is used to pause the thread.
         */
        void pauseThread();

        /**
         * \fn void suspendNWThread()
         * \brief This function is used to pause the thread & disable WIFI.
         */
        void suspendNWThread();

        /**
         * \fn void stopThread()
         * \brief This function is used to stop the thread.
         */
        void stopThread();

    signals:    /** Signals */
        /*\@{*/

        /**
         * \fn void popUpMessage(const QString &r_const_strDISPLAYTEXT)
         * \brief This signal is emitted whenever we need to show the popup messages.
         * \param[in] r_const_strDISPLAYTEXT it gives the network status as Connected/Removed for Wifi/ Ethernet/ GPRS.
         */
        void popUpMessage(const QString &r_const_strDISPLAYTEXT);

        /**
         * \fn void activeNetwork(E_NetworkStatus nStatus, int nLevel)
         * \brief This signal is emitted whenever active network is changed.
         * \param[in] eStatus it gives active network is Ethernet/GPRS/WIFI/NONE.
         * \param[in] nLevel it gives the Level of the wifi signal. signal Level would be 0 to 5.
         * If level is -1, router might be switched off or invalid configuration.
         *
         * \sa see also E_NetworkStatus.
         */
        void activeNetwork(E_NetworkStatus nStatus, int nLevel);

        /*\@}*/

    private:

        /**
         * \var QString m_strNetwork
         * \brief used to store the error information.
         */
        QString m_strError;
        /**
         * \var bool m_bThreadRunning
         * \brief used to store the thread is running or not.
         */
        bool m_bThreadRunning;
        /**
         * \var bool m_bDefaultGprs
         * \brief used to store the active network is gprs or not.
         */
        bool m_bDefaultGprs;
        /**
         * \var bool m_bDefaultEthernet
         * \brief used to store the active network is ethernet or not.
         */
        bool m_bDefaultEthernet;
        /**
         * \var bool m_bWifiConnected
         * \brief used to store the wifi device is connected or not.
         */
        bool m_bWifiConnected;
        /**
         * \var bool m_bWifiConnectedNetwork
         * \brief used to store the wifi is connected with network or not.
         */
        bool m_bWifiConnectedNetwork;
        /**
         * \var bool m_bWifiDeviceFound
         * \brief used to store the wifi device is found or not.
         */
        bool m_bWifiDeviceFound;
        /**
         * \var bool m_bWifiDisabled
         * \brief used to store the wifi is disabled or not.
         */
        bool m_bWifiDisabled;
        /**
         * \var int m_nWifiLevel
         * \brief used to store the wifi signal level.
         */
        int m_nWifiLevel;
        /**
         * \var int m_nWifiEnableTryCount
         * \brief used to store the Wifi Enable try count.
         */
        int m_nWifiEnableTryCount;
        /**
         * \var int m_nWifiDevSearchCount
         * \brief used to store the Wifi Device search count.
         */
        int m_nWifiDevSearchCount ;
        /**
         * \var int m_nWifiConnectionTimeoutCount
         * \brief used to store the count value for WIFI connectivity fail.
         */
        int m_nWifiConnectionTimeoutCount;

        /**
         * \fn virtual void run()
         * \brief The starting point for the thread. this function is remplemented of thread class.
         * it performs to check the active network status.
         */
        virtual void run();

        /**
         * \fn bool isEthernet()
         * \brief This function is used to check the active network is ethernet or not.
         * \return It returns true, if ethernet is connected; otherwise returns false.
         */
        bool isEthernet();

        /**
         * \fn bool connectWifi()
         * \brief This function is used to connect the wifi with network.
         * \return It returns true, if wifi is connected with network; otherwise returns false.
         */
        bool connectWifi();

        /**
         * \fn void processWifi()
         * \brief This function is used to process the wifi network.
         * if wifi is connected, it get the wifi level; otherwise try to connect with wifi network.
         */
        void processWifi();

        /**
         * \fn void processNoNetwork()
         * \brief This function is used to process no active network is available.
         * try to connect wifi,if wifi is device is already found and disconnected.
         */
        void processNoNetwork();

//        /**
//         * \fn bool ping(const QString &r_const_IPADDRESS)
//         * \brief This function is used to ping the ip address.
//         * \return It returns true, if ip address is pinged successfully; otherwise returns false.
//         */
//        bool ping(const QString &r_const_IPADDRESS);

        /**
         * \fn bool processCommand(const QString &r_const_COMMAND)
         * \brief This function is used to process the system command and break if thread is not running.
         * \param[in] r_const_COMMAND used to set the system command.
         * \return It returns true, if given command execution is completed successfully; otherwise returns false.
         */
        bool processCommand(const QString &r_const_COMMAND);
    };
}
#endif // CNETWORK_H
