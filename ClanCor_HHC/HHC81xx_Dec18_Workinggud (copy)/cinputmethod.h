/**
 * \file "cinputmethod.h"
 * \brief it provides an interface for handling automatically keypadlock, idle mode and standby mode
 * using QWSInputMethod class to filter the event (keyboard and mouse events).
 *
 * This file is also used to dispaly the text when using modbile keypad.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CINPUTMETHOD_H
#define CINPUTMETHOD_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QWSInputMethod>
#include <QtGui>
#include <QObject>
#include <QLabel>
#include <QLineEdit>

namespace ClanCor
{
    /**
     * \class CInputMethod
     * \brief The CInputMethod class provides the methods for control the automatic
     * keypad lock, idle mode and standby mode timeout and process the display text in
     * mobile keypad.
     *
     * It inherits QWSInputMethod class to filter the keyboard and mouse events.
     */
    #ifdef Q_WS_QWS
    class CInputMethod : public QWSInputMethod
    #else
    class CInputMethod : public QObject
    #endif
    {
        Q_OBJECT
    public:
        /**
         * \fn CInputMethod()
         * A constructor.
         * \brief It initialize the shutdown dialog, keypad locked dialog and allocate the needed resources.
         */
        CInputMethod();

        /**
         * \fn ~CInputMethod()
         * A destructor.
         * \brief free all the allocated resources.
         */
        ~CInputMethod();

        /**
         * \fn bool shutdownDialog()
         * \brief This function is used to show the shutdown dialog if keypad is not locked.
         */
        void shutdownDialog();

        /**
         * \fn void setKeypadLockTimeout(int nSecs)
         * \brief This function is used to set the timeout of the keypad lock.
         * keypad lock will be disabled if given value is "0".
         * \param[in] nSecs used to set the keypadlock timeout in seconds.
         */
        void setKeypadLockTimeout(int nSecs);

        /**
         * \fn void setIdleModeTimeout(int nSecs)
         * \brief This function is used to set the timeout of the Idle mode.
         * Idle mode option will be disabled if given value is "0".
         * \param[in] nSecs set the Idle mode timeout in seconds.
         */
        void setIdleModeTimeout(int nSecs);

        /**
         * \fn void setStandbyModeTimeout(int nSecs)
         * \brief This function is used to set the time out of the Standby mode.
         * Standby mode option will be disabled if given value is "0".
         * \param[in] nSecs set the Standby mode timeout in seconds.
         */
        void setStandbyModeTimeout(int nSecs);

        /**
         * \fn void reset()
         * \brief This function is used to commit the string in display in mobile keypad.
         */
        void reset();

        /**
         * \fn void setActiveMobileKeypad(bool bActive)
         * \brief This function is used to commit the string in display in mobile keypad.
         * \arg[in] bActive used to set enable/disable for process the mobile keypad.
         */
        void setActiveMobileKeypad(bool bActive);
        /**
         * \fn void bool activeMobileKeypad()
         * \brief This function is used to return the mobile keypad is active or not.
         * \return It returns true, if mobile keypad is active; otherwise return false.
         */
        bool activeMobileKeypad() const { return m_bActive; }

    public slots:
        /**
         * \fn void resetTimer()
         * \brief This function is used to reset the keypadlock, idle and standby timers.
         */
         void resetTimer();

         /**
          * \fn void on_pushButtonShutDown_clicked()
          * \brief This function is used to shutdown the device.
          */
         void on_pushButtonShutDown_clicked();

         /**
          * \fn void on_pushButtonRestart_clicked()
          * \brief This function is used to restart the device.
          */
         void on_pushButtonRestart_clicked();

         /**
          * \fn void wakeup(bool bFlagStandby)
          * \brief This function is used to wakeup from idle or standby mode.
          * \arg[in] bFlagStandby used to set device is wakeup from standby or idle.
          */
         void wakeup(bool bFlagStandby);

         /**
          * \fn void resetKeyboard()
          * \brief This function is used to reset the keyboard.
          */
         void resetKeyboard();

         /**
          * \fn void closeKeyboard()
          * \brief This function is used to close the keyboard.
          */
         void closeKeyboard();

         /**
          * \fn void idleMode()
          * \brief This function is used to do the process for going to idle mode.
          */
         void idleMode();

         /**
          * \fn void standbyMode()
          * \brief This function is used to do the process for going to standby mode.
          */
         void standbyMode();

         /**
          * \fn void sendBarcodeData(const QString &r_const_strDATA)
          * \brief This function is used to send the barcode data to focused widgets.
          * \arg[in] r_const_strDATA used to set the data which to be displayed.
          */
         void sendBarcodeData(const QString &r_const_strDATA);

    signals:    /** Signals */
        /*\@{*/

         /**
          * \fn void keypadLockStatus(bool bLocked)
          * \brief This signal is emitted whenever keypad is locked and unlocked.
          * \param[in] bLocked it gives the keypad is going to lock or unlocked.
          */
         void keypadLockStatus(bool bLocked);

         /**
          * \fn void wakeupFromIdleMode()
          * \brief This signal is emitted after wakeup from idle mode.
          */
         void wakeupFromIdleMode();

         /**
          * \fn void wakeupFromStandbyMode()
          * \brief This signal is emitted after wakeup from standby mode.
          */
         void wakeupFromStandbyMode();

         /**
          * \fn void standbyTimeout()
          * \brief This signal is emitted before standby for accept or reject the standby mode.
          */
         void standbyTimeout();

         /**
          * \fn void idleModeTimeout()
          * \brief This signal is emitted before idle mode for accept or reject the idle mode.
          */
         void idleModeTimeout();

         /*\@}*/

    private:
         /**
          * \var QWidget *m_widgetScreenLock
          * \brief used to show the message when user press if keypad is locked.
          */
         QWidget *m_widgetScreenLock;
         /**
          * \var QDialog *m_dialogShutdown
          * \brief used to show the shutdown dialog.
          */
         QDialog *m_dialogShutdown;
         /**
          * \var QLabel *m_labelStatusLock
          * \brief used to show the status of keypad lock widget.
          */
         QLabel *m_labelStatusLock;
         /**
          * \var QLabel *m_labelLockImage
          * \brief used to show the keypad locked and unlocked image.
          */
         QLabel *m_labelLockImage;
         /**
          * \var QLabel *m_labelWakeupInfo
          * \brief used to show the wakeup information in top bar when idle mode.
          */
         QLabel *m_labelWakeupInfo;
         /**
          * \var QTimer m_timerIdle
          * \brief used to process the idle timeout.
          */
         QTimer m_timerIdle;
         /**
          * \var QTimer m_timerScreenLock
          * \brief used to process the screen lock timeout.
          */
         QTimer m_timerScreenLock;
         /**
          * \var QTimer m_timerStandby
          * \brief used to process the standby timeout.
          */
         QTimer m_timerStandby;
         /**
          * \var QTimer m_timerScreenUnlock
          * \brief used to process the screen unlocked timeout.
          */
         QTimer m_timerScreenUnlock;
//         /**
//          * \var QTimer m_timerWifiSearch
//          * \brief used to search the wifi device after sometime.
//          */
//         QTimer m_timerWifiSearch;
         /**
          * \var QMutex m_Mutex
          * \brief used to lock and unlock the code for serialise the process.
          */
         QMutex m_Mutex;
         /**
          * \var QPushButton *m_pushButtonCancel
          * \brief used to display cancel button in shutdown dialog.
          */
         QPushButton *m_pushButtonCancel;
         /**
          * \var QPushButton *m_pushButtonCancel
          * \brief used to display screen Lock option in shutdown dialog.
          */
         QPushButton *m_pushButtonLock;
         /**
          * \var QPushButton *m_pushButtonStandby
          * \brief used to display standby option in shutdown dialog.
          */
         QPushButton *m_pushButtonStandby;
         /**
          * \var QPushButton *m_pushButtonShutDown
          * \brief used to display shutdown option in shutdown dialog.
          */
         QPushButton *m_pushButtonShutDown;
         /**
          * \var QPushButton *m_pushButtonRestart
          * \brief used to display restart option in shutdown dialog.
          */
         QPushButton *m_pushButtonRestart;
         /**
          * \var QString m_strLastText
          * \brief used to store the last text for mobile keypad.
          */
         QString m_strLastText;
         /**
          * \var QTimer m_timerKeypad
          * \brief used to process the display text timeout in mobile keypad.
          */
         QTimer m_timerKeypad;
         /**
          * \var QTimer m_timerPowerControl
          * \brief used to process the power control for usb devices when startup & standby.
          */
         QTimer m_timerPowerControl;
         /**
          * \var bool m_bUpperCase
          * \brief used to store the caps lock in On/Off in mobile keypad.
          */
         bool m_bUpperCase;
         /**
          * \var bool m_bActive
          * \brief used to store the mobile keypad is active or not.
          */
         bool m_bActive;
         /**
          * \var bool m_bRunning
          * \brief used to store the some process is running in this class.
          */
         bool m_bRunning;
         /**
          * \var bool m_bScreenLocked
          * \brief used to store the keypad is locked it not.
          */
         bool m_bScreenLocked;
         /**
          * \var bool m_bSystemIdle
          * \brief used to store the system is idle mode or not.
          */
         bool m_bSystemIdle;
         /**
          * \var int m_nLastGroup
          * \brief used to store the key group of last pressed key in mobile keypad.
          */
         int m_nLastGroup;
         /**
          * \var int m_nScreenLockTime
          * \brief used to store the keypad lock timeout value.
          */
         int m_nScreenLockTime;
         /**
          * \var int m_nIdleTime
          * \brief used to store the idle mode timeout value.
          */
         int m_nIdleTime;
         /**
          * \var int m_nStandbyTime
          * \brief used to store the standby timeout value.
          */
         int m_nStandbyTime;
         /**
          * \var int m_nErrorCountWifi
          * \brief used to store the count for wifi search.
          */
         int m_nErrorCountWifi;

         /**
          * \fn virtual bool filter ( int nUnicode, int nKeycode, int nModifiers, bool bIsPress, bool bAutoRepeat )
          * \brief This function is remplemented of QWSInputMethod class for filtering the keyboard events.
          * Filters the key input identified by the given unicode, keycode, modifiers, isPress and autoRepeat parameters.
          * Note that the default implementation does nothing; reimplement this function to handle input from both physical and virtual devices.
          * The keycode is a Qt::Key value, and the modifiers is an OR combination of Qt::KeyboardModifiers. The isPress parameter is telling whether the input is a key press or key release, and the autoRepeat parameter determines whether the input is autorepeated ( i.e., in which case the QWSKeyboardHandler::beginAutoRepeat() function has been called).
          * \returns it returns true, to block keypad the event from further processing. the default implementation returns false.
          */
         virtual bool filter ( int nUnicode, int nKeycode, int nModifiers, bool bIsPress, bool bAutoRepeat );

         /**
          * \fn virtual bool filter ( const QPoint & pointPosition, int nState, int nWheel )
          * \brief This function is remplemented of QWSInputMethod class for filtering the mouse events.
          * Filters the mouse input identified by the given position, state, and wheel parameters
          * \returns it returns true, to block the mouse event from further processing. the default implementation returns false.
          */
         virtual bool filter ( const QPoint & pointPosition, int nState, int nWheel );

         /**
          * \fn bool eventFilter(int nKeycode)
          * \brief This function is used to process the keypad or mouse to be filtered or not.
          * \arg[in] nKeycode used to set the keycode of pressed.
          * \returns it returns true, if the keyboard & mouse event to be blocked from further processing. otherwise returns false.
          */
         bool eventFilter(int nKeycode);

         /**
          * \fn int whichGroup(int nKeycode)
          * \brief This function is used to identify the key in which group for 70/71xx mobile keypad.
          * \arg[in] nKeycode used to set the keycode of pressed.
          * \returns it returns the group number.
          */
         int whichGroup(int nKeycode);

         /**
          * \fn void waitForKeyboard()
          * \brief This function is used to wait until keyboard event is found or timeout.
          */
         void waitForKeyboard();

         /**
          * \fn bool getDateTime()
          * \brief This function is used to get the datetime from co-processor and update it to os.
          * \return it returns true, if sucessfully datetiem read from co-processor; otherwise return false.
          */
         bool getDateTime();

    private slots:
         /**
          * \fn void waitForKeyboard()
          * \brief This function is called before going to standby.
          */
         void on_pushButtonStandby_clicked();

         /**
          * \fn void waitForKeyboard()
          * \brief This function is used to cancel the shutdown dialog.
          */
         void on_pushButtonCancel_clicked();

         /**
          * \fn void on_timerIdle_timeout()
          * \brief This function is called before going to idle mode.
          */
         void on_timerIdle_timeout();

         /**
          * \fn void on_timerScreenUnock_timeout()
          * \brief This function is used to close the screen lock widget after timeout.
          */
         void on_timerScreenUnock_timeout();

         /**
          * \fn void on_timerKeypad_timeout()
          * \brief This function is used to moveto next position, when mobile keypad timeout.
          */
         void on_timerKeypad_timeout();

//         /**
//          * \fn void on_timerWifiSearch_timeout()
//          * \brief This function is used to search the wifi device if not found.
//          */
//         void on_timerWifiSearch_timeout();

         /**
          * \fn void keypadLocked()
          * \brief This function is used to process when keypad is locked.
          */
         void keypadLocked();

         /**
          * \fn void keypadUnLocked()
          * \brief This function is used to process when keypad is unlocked.
          */
         void keypadUnLocked();

         /**
          * \fn void autoPowerControl()
          * \brief This function is used to process the auto power consumption of usb devices.
          */
         void autoPowerControl();
    };
}
#endif // CINPUTMETHOD_H
