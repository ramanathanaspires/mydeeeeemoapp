/**
 * \file "chhc80xxserver.h"
 * \brief it provides server functions of ClanCor HHC80xx hand-held device.
 *
 * This file is used to communicate ClanCor HHC80xx Desktop functions.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CHHC80XXSERVER_H
#define CHHC80XXSERVER_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QLabel>
#include<QProcess>
#include <QPushButton>
#include <QWidget>
#include <QToolBar>
#include <QCalendarWidget>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <CHHC80xxTypes>

namespace ClanCor
{
/**
     * \class CHHC80xxServer
     * \brief The CHHC80xxServer class provides the server methods & configuration functions for ClanCor HHC80xx Device.
     *
     *  you can use the existing HHC80xxpanel directly or reimplement the function for your own panel design.
     */
class CHHC80xxServer : public QObject
{
    Q_OBJECT
    /*****************************************************************************
                                PUBLIC
******************************************************************************/
public:
    /**
         * The enum describes the security mode of the wifi
         */
    enum E_SecurityMode
    {
        eSecurityMode_NONE = 0, /**< No security Mode */
        eSecurityMode_WPA2_PERSONAL = 1, /**< WPA2 Personal security */
        eSecurityMode_WEP = 2 /**< WEP security */
    };

    /**
         * \struct SWifiNetwork
         * \brief It provides the interface for Wifi Network configuaration.
         *
         * It stores the configuration details of the wifi network.
         */
    struct SWifiNetwork
    {
        QString m_strIpAddress; /** IP Address */
        QString m_strSubnetMask; /** Subnet Mask */
        QString m_strGateway; /** Gateway */
        QString m_strEssid; /** Wifi network name */
        bool m_bAdhoc; /** Whether Adhoc mode is ON/OFF */
        E_SecurityMode m_eSecurity; /** Security Mode of the Wifi Network */
        QString m_strKey; /** password key of the network */
    };

    /**
         * \fn CHHC80xxServer()
         * A constructor.
         * \brief Constructs a new HHC80xxServer method.
         * Use the CHHC80xx::setServerMethod() function to install it.
         *
         * \sa see also CHHC80xx::setServerMethod().
         */
    CHHC80xxServer();

    /**
         * \fn virtual ~CHHC80xxServer()
         * A destructor.
         * \brief Destroys this HHC80xxServer method, uninstalling it, if it is installed.
         */
    virtual ~CHHC80xxServer();


    /** For running second application QProcess is used
      **/

    QProcess *myProcess;

    bool gpsiconflag;

    /**
         * \fn QToolBar* HHC80xxPanel() const
         * \brief Returns tool bar of the default HHC80xx panel for the main window.
         * use this if you want to use the default HHC80xx panel.
         * \return It returns as toolbar of the HHC80xx panel.
         */
    QToolBar* HHC80xxPanel() const { return m_toolbarPanel; }

    /**
         * \fn bool setEthernetConfig(const QString &r_const_strIPADDRESS,const QString &r_const_strSUBNET,const QString &r_const_strGATEWAY) const
         * \brief This function is used to configure the ethernet.
         * it will configure the given details of the ethernet network.
         * \param[in] r_const_strIPADDRESS used to set the IP Address of the ethernet.
         * \param[in] r_const_strSUBNET used to set the Subnet Mask of the ethernet.
         * \param[in] r_const_strGATEWAY used to set the Gateway of the ethernet.
         * \return It returns true, if configuration saved successfully; otherwise returns false.
         */
    bool setEthernetConfig(const QString &r_const_strIPADDRESS,const QString &r_const_strSUBNET,const QString &r_const_strGATEWAY) const;

    /**
         * \fn bool ethernetConfig(QString &r_IpAddress,QString &r_SubnetMask,QString &r_Gateway) const
         * \brief This function is used to get the configuration of the ethernet.
         * it will give the configuration details of the ethernet network.
         * \param[out] r_IpAddress used to get the IP Address of the ethernet.
         * \param[out] r_SubnetMask used to get the Subnet Mask of the ethernet.
         * \param[out] r_Gateway used to get the Gateway of the ethernet.
         * \return It returns true, if configuration exists; otherwise returns false.
         */
    bool ethernetConfig(QString &r_IpAddress,QString &r_SubnetMask,QString &r_Gateway) const;

    /**
         * \fn bool setWifiConfig(const SWifiNetwork &r_const_wifiCONFIG ) const
         * \brief This function is used to configure the Wifi network.
         * it will configure the given details of the Wifi network.
         * \param[in] r_wifiConfig used to set the configuration details.
         * \return It returns true, if configuration saved successfully; otherwise returns false.
         *
         * \sa see also SWifiNetwork.
         */
    bool setWifiConfig(const SWifiNetwork &r_const_wifiCONFIG ) const;

    /**
         * \fn bool wifiConfig(SWifiNetwork &r_wifiConfig) const
         * \brief This function is used to get the configuration of the Wifi network.
         * it will give the configuration details of the Wifi network.
         * \param[out] SWifiNetwork used to get the wifi configuration details.
         * \return It returns true, if configuration exists; otherwise returns false.
         *
         * \sa see also SWifiNetwork.
         */
    bool wifiConfig(SWifiNetwork &r_wifiConfig) const;

    /**
         * \fn bool setGprsApn(const QString &r_const_strNETWORK, const QString &r_const_strApn) const
         * \brief This function is used to set the Apn Name for the Gsm Network.
         * \param[in] r_const_strApn used to set the Apn address for the Gsm Network.
         * \return It returns true, if it is stored successfully; otherwise returns false.
         */
    bool setGprsApn(const QString &r_const_strApn) const;

    /**
         * \fn QString getgprsApn(const QString &r_const_strNETWORK) const
         * \brief This function is used to return the Apn Name of the given Last Stored Network.
         * it will return the apn name of the given Last Stored network, if it exists in the configuration
         * \return It returns the Apn name of the gsm network.
         */
    QString getgprsApn() const;

    /**
         * \fn bool setGadgetConfiguration( E_GadgetMode &r_Gadget_Mode,  E_MassStorage &r_Mass_Storage_Type) const
         * \brief This function is used to get the configuration of the Gadget.
         * it will give the configuration details of the Gadget.
         * \param[out] E_GadgetMode used to get the Gadget configuration details.
         * \return It returns true, if configuration exists; otherwise returns false.
         *
         * \sa see also QString.
         */
    void setGadgetConfiguration( E_GadgetMode &r_Gadget_Mode,  E_MassStorage &r_Mass_Storage_Type) const;


    /**
         * \fn bool GadgetConfiguration( E_GadgetMode &r_Gadget_Mode,  E_MassStorage &r_Mass_Storage_Type) const
         * \brief This function is used to get the configuration of the Database.
         * it will give the configuration details of the Gadget.
         * \param[out] E_GadgetMode used to get the Gadget Mode.
         * \param[out] E_MassStorage used to get the Mass Storage Type.
         * \return It returns true, if configuration exists; otherwise returns false.
         */
    bool GadgetConfiguration( E_GadgetMode &r_Gadget_Mode,  E_MassStorage &r_Mass_Storage_Type) const;

    /**
         * \fn void setKeypadLockTimeout(int nSecs)
         * \brief This function is used to set the timeout of the keypad lock.
         * It will store the given value in the configuration.
         * keypad lock will be disabled if given value is "0".
         * \param[in] nSecs used to set the keypadlock timeout in seconds.
         */
    void setKeypadLockTimeout(int nSecs);

    /**
         * \fn int keypadLockTimeout() const
         * \brief This function returns the value of current keypadlock time interval.
         * It will return the value from the configuration
         * \return It returns the keypadlock time interval, returns "0" if keypad lock is disabled .
         */
    int keypadLockTimeout() const;

    /**
         * \fn void setIdleModeTimeout(int nSecs)
         * \brief This function is used to set the timeout of the Idle mode.
         * It will store the given value in the configuration.
         * Idle mode option will be disabled if given value is "0".
         * \param[in] nSecs set the Idle mode timeout in seconds.
         */
    void setIdleModeTimeout(int nSecs);

    /**
         * \fn int idleModeTimeout() const
         * \brief This function returns the value of current Idle mode time.
         * It will get the value from the configuration.
         * \return It returns the Idle mode time interval, returns "0" if idle mode is disabled .
         */
    int idleModeTimeout() const;

    /**
         * \fn void setStandbyModeTimeout(int nSecs)
         * \brief This function is used to set the time out of the Standby mode.
         * It will store the given value in the configuration.
         * Standby mode option will be disabled if given value is "0".
         * \param[in] nSecs set the Standby mode timeout in seconds.
         */
    void setStandbyModeTimeout(int nSecs);

    /**
         * \fn int standbyModeTimeout() const
         * \brief This function returns the value of current Standby mode time.
         * It will get the value from the configuration.
         * \return It returns the Standby mode time interval, returns "0" if standby mode is disabled .
         */
    int standbyModeTimeout() const;

    /**
         * \fn bool setBacklight(int nLevel) const
         * \brief This function is used to control the display backlight level.
         * \param[in] nLevel used to set the backlight level. it must be 1 to 5.
         * \return It returns true, if level updated successfully; otherwise returns false.
         */
    bool setBacklight(int nLevel) const;

    /**
         * \fn int backlight() const
         * \brief This function returns the value of current backlight brightness level.
         * It will get the value from the configuration.
         * \return It returns the brightness level value. value should be 1 to 5
         */
    int backlight() const;

    /**
         * \fn bool touchCalibrateDialog() const
         * \brief This function is used to show the calibration dialog to calibrate the touch coordinate.
         * Device will be restarted once the calibration successfull.
         * \return It returns false, if calibration failed.
         */
    bool touchCalibrateDialog() const;

    /**
         * \fn bool volumeControlDialog() const
         * \brief This function is used to show the volume control dialog to configure the Speaker & Mic volume.
         * It will store the configured Speaker & Mic volume.
         * \return It returns false, if audio device is not found; otherwise returns true.
         */
    bool volumeControlDialog() const;

    /**
         * \fn void shutdownDialog()
         * \brief This function is used to show the shutdown dialog.
         * it will consists of options like lock,standby,shutdown and restart.
         */
    void shutdownDialog();

    /**
         * \fn bool programCoProcessor(const QString &r_const_FILENAME) const
         * \brief This function is used to reprogram the coprocessor.
         * Device will be shutdown once the reprogramming is successful or failed.
         * \param[in] r_const_FILENAME used to pass the path of the program filename.
         */
    bool programCoProcessor(const QString &r_const_FILENAME) const;

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
    bool disableWifiModule();

    /**
         * \fn void setgprsAlwaysON_OF(bool bflag) const
         * \brief This function is used to setgrps is always ON or OFF.
         */
    void setgprsAlwaysON_OFF(bool bflag) const;
    /**
         * \fn    bool getgprsAlwaysON_OF() const;
         * \brief This function is used to get whether grps always ON or OFF status.
         */
    bool getgprsAlwaysON_OFF() const;
    /**
            * \fn void setWIFION_OFF(bool bflag) const
            * \brief This function is used to setwifi is always ON or OFF.
            */
    void setWIFION_OFF(bool bflag) const;
    /**
            * \fn    bool getWIFION_OFF() const;
            * \brief This function is used to get whether WIFI ON or OFF status.
            */
    bool getWIFION_OFF() const;    
    /**
            * \fn    bool getUSBON_OFF() const;
            * \brief This function is used to get whether USB ON or OFF status.
     */
    bool getUSBON_OFF() const;

    /**
         * \fn  bool setMachineId(QString machineId, QString deviceModel, QString ModuleId) const;
         * \brief This Function is used to set the Device Machine Id,devicemodel and GPRS module type through Software
         * \return It returns true if it sets machineid else False.
         */
    bool setMachineId(QString machineId, QString deviceModel, QString ModuleId) const;

    /*****************************************************************************
                                PUBLIC SLOTS
******************************************************************************/
public slots:
    /**
         * \fn virtual void flashMessage(const QString &r_const_strDISPLAYTEXT)
         * \brief This fucntion is used to show the flash Message.
         * In your reimplementation of this function to receive & customize the flash messages.
         * \param[in] r_const_strDISPLAYTEXT it gives the message to be shown as flash with some interval.
         */
    virtual void flashMessage(const QString &r_const_strDISPLAYTEXT);

    /**
         * \fn virtual void popUpMessage(const QString &r_const_strDISPLAYTEXT)
         * \brief This fucntion is used to show the popup message.
         * In your reimplementation of this function to receive & customize the popup messages.
         * \param[in] r_const_strDISPLAYTEXT it gives the message to be shown as popup with some interval.
         */
    virtual void popUpMessage(const QString &r_const_strDISPLAYTEXT);

    /*****************************************************************************
                                PROTECTED SLOTS
******************************************************************************/
protected slots:
    /**
         * \fn virtual void activeNetwork(E_NetworkStatus eStatus,int nLevel)
         * \brief In your reimplementation of this function to receive the active network.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] eStatus it gives active network is Ethernet/GPRS/WIFI/NONE.
         * \param[in] nLevel it gives the Level of the wifi signal. signal Level would be 0 to 5.
         * If level is -1, router might be switched off or invalid configuration.
         *
         * \sa see also E_NetworkStatus.
         */
    virtual void activeNetwork(E_NetworkStatus eStatus,int nLevel);

    /**
         * \fn virtual void batteryLevel(int nLevel,int nPercentage)
         * \brief In your reimplementation of this function to receive the battery level and percentage.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] nLevel it gives the battery level. It would be 0 to 5.
         * \param[in] nPercentage it gives the battery percentage. It would be 0 to 100.
         */
    virtual void batteryLevel(int nLevel,int nPercentage);

    /**
         * \fn virtual void batteryChargeStatus(E_ChargeStatus eStatus)
         * \brief In your reimplementation of this function to receive the charging status of the battery.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] eStatus it gives the charging status as Connected/Removed/Completed/Invalid.
         *
         * \sa see also E_ChargeStatus.
         */
    virtual void batteryChargeStatus(E_ChargeStatus eStatus);

    /**
         * \fn virtual void keypadMode(E_KeypadMode eMode,bool bCapsOn)
         * \brief In your reimplementation of this function to receive the keypad mode.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] eMode it gives the keypad mode whether Numeric/Alphabets
         * \param[in] bCapsOn it gives the CapsLock is ON/OFF.
         *
         * \sa see also E_KeypadMode.
         */
    virtual void keypadMode(E_KeypadMode eMode,bool bCapsOn);

    /**
         * \fn virtual void keypadModeLocked( bool bModeLocked )
         * \brief In your reimplementation of this function to receive the keypad mode lock status.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] bModeLocked it gives the keypad mode is LOCKED/UNLOCKED.
         *
         */
    virtual void keypadModeLocked( bool bModeLocked );


    /**
         * \fn virtual void gsmNetworkSignal(int nLevel)
         * \brief In your reimplementation of this function to receive the gsm network signal.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] nLevel it gives the signal level. The signal level would be 0 to 5.
         */
    virtual void gsmNetworkSignal(int nLevel);

    /**
         * \fn virtual void keypadLockStatus(bool bLocked)
         * \brief In your reimplementation of this function, do the work after keypad is locked or unlocked.
         * Reimplement this if you don't want to use the default HHC80xx panel.
         * \param[in] bLocked It gives keypad is Locked/Unlocked.
         */
    virtual void keypadLockStatus(bool bLocked);

    /**
         * \fn virtual void showDesktop()
         * \brief In your reimplementation of this function, do the work when second application requires to show main application.
         */
    virtual void showDesktop();

    /**
         * \fn virtual void wakeupFromIdleMode()
         * \brief In your reimplementation of this function, do the work after wakeup from the idle mode.
         */
    virtual void wakeupFromIdleMode();

    /**
         * \fn virtual void wakeupFromStandbyMode()
         * \brief In your reimplementation of this function, do the work after wakeup from the standby mode.
         */
    virtual void wakeupFromStandbyMode();

    /**
         * \fn virtual bool acceptIdleMode()
         * \brief This virtual function receives event to customize the behaviour of the idle mode.
         * In your reimplementation of this function, do the work before the idle mode.
         * \return return true to accept and command to process the idle mode; otherwise returns false.
         */
    virtual bool acceptIdleMode();

    /**
         * \fn virtual bool acceptStandby()
         * \brief This virtual function receives event to customize the behaviour of the standby mode.
         * In your reimplementation of this function, do the work before the standby mode.
         * \return return true to accept and command to process the standby mode; otherwise returns false.
         */
    virtual bool acceptStandby();
    /**
         * \fn  virtual void showgps(bool flag);
         * \brief This virtual function is used to show the gps icon .
         */
    virtual void showgps(bool flag);


    /*****************************************************************************
                                PRIVATE
******************************************************************************/
private:
    /**
         * \var QToolBar *m_toolbarPanel
         * \brief used to display status panel for HHC80xx.
         */
    QToolBar *m_toolbarPanel;
    /**
         * \var QLabel *m_labelMessage
         * \brief used to display the flash message.
         */
    QLabel *m_labelMessage;
    /**
         * \var QLabel *m_labelBaloon
         * \brief used to display the popup message.
         */
    QLabel *m_labelBaloon;
    /**
         * \var QPushButton *m_pushButtonLocked
         * \brief used to display the keypad locked icon.
         */
    QPushButton *m_pushButtonLocked;
    /**
         * \var QWidget *m_widgetPanel
         * \brief used to store all widgets for HHC80xx panel.
         */
    QWidget *m_widgetPanel;
    /**
         * \var QPushButton *m_pushuttonBattery
         * \brief used to display the battery status in panel.
         */
    QPushButton *m_pushuttonBattery;
    /**
         * \var QLabel *m_labelTower
         * \brief used to display the gsm tower level.
         */
    QLabel *m_labelTower;
    /**
         * \var QLabel *m_labelGPS
         * \brief used to display the gps Module.
         */
    QLabel *m_labelGps;
    /**
         * \var QLabel *m_labelPencil
         * \brief used to display the pencil icon for keypad mode.
         */
    QLabel *m_labelPencil;
    /**
         * \var QLabel *m_labelkeypad
         * \brief used to display the keypad mode.
         */
    QLabel *m_labelkeypad;
    /**
         * \var QPushButton *m_pushButtonDate
         * \brief used to display the current date & time.
         */
    QPushButton *m_pushButtonDate;
    /**
         * \var QPushButton *m_pushButtonNetworkIcon
         * \brief used to display the active network.
         */
    QPushButton *m_pushButtonNetworkIcon;
    /**
         * \var QCalendarWidget *m_calendarWidget
         * \brief used to display the calendar widget.
         */
    QCalendarWidget *m_calendarWidget;

    /**
         * \var QTimer m_timerFlash
         * \brief used for close the flash message.
         */
    QTimer m_timerFlash;
    /**
         * \var QTimer m_timerToolTip
         * \brief used for close the popup message.
         */
    QTimer m_timerToolTip;
    /**
         * \var QTimer m_timerCharging
         * \brief used for update the charging icon.
         */
    QTimer m_timerCharging;
    /**
         * \var QTimer m_timerDT
         * \brief used for update the date & time.
         */
    QTimer m_timerDT;

    /**
         * \var int m_nCurrent
         * \brief used to store the count for update the battery icon when charging.
         */
    int m_nCurrent;
    /**
         * \var int m_nBatteryVal
         * \brief used to store the last battery value.
         */
    int m_nBatteryVal;

    /**
         * \var int m_nBatteryPer
         * \brief used to store the last battery percentage.
         */
    int m_nBatteryPer;



    /*****************************************************************************
                               PRIVATE SLOTS
******************************************************************************/
private slots:
    /**
         * \fn void timerFlash_timeout()
         * \brief This function is used to close the flash message.
         */
    void timerFlash_timeout();

    /**
         * \fn void closeBaloon()
         * \brief This function is used to close the popup message.
         */
    void closeBaloon();

    /**
         * \fn void dateTime_clicked()
         * \brief This function is used to show or hide the calendar widget.
         */
    void dateTime_clicked();

    /**
         * \fn void dateTime_clicked()
         * \brief This function is used to show the battery percentage.
         */
    void showPercentage();

    /**
         * \fn void updateCharging()
         * \brief This function is used to update battery icon when charging.
         */
    void updateCharging();

    /**
         * \fn void updateDateTime()
         * \brief This function is used to update date & time in the panel.
         */
    void updateDateTime();

    /**
         * \fn void shutDown(bool bMessage)
         * \brief This function is used to call direct shutdown or show the shutdown dialog.
         * \arg[in] bMessage used to set true to show the shutdown dialog.
         */
    void shutDown(bool bMessage);

    /**
         * \fn void updateDateTime()
         * \brief This function is used to set the apn of current network.
         */
    void setNetworkApn();

    /**
         * \fn void standby_click()
         * \brief This function is used to goto standby.
         */
    void standby_click();

    /**
         * \fn void idleMode_timeout()
         * \brief This function is used to goto idle mode.
         */
    void idleMode_timeout();
};
}
#endif // CHHC80XXSERVER_H
