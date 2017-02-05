#ifndef MYSERVER_H
#define MYSERVER_H
#include <QtGui>
#include <CHHC80xxServer>
using namespace ClanCor;

class MyServer : public CHHC80xxServer
{
    Q_OBJECT
public:
    QToolBar *myTopbar;
    MyServer();
    ~MyServer();
private:
    QWidget *Mainbar;
    QTimer *Timer;
    QPushButton *lblBattery;
    QPushButton *lblLocked;
    QLabel *lblTower;
    QLabel *lblGps;
    QLabel *lbl_Keypad;
    QLabel *lbl_Penceil;
    QPushButton *btnDateTime;
    QPushButton *btn_LanorGPRS;
    QCalendarWidget *calender;
    QTimer t;
    QTimer VolumeTimer;
    QTimer timerDT;
    QTimer timerCharging;
    QSettings *settings;
    QMenu *menu_Option;
    QAction *actionDisconnect;
    int Current;
    int Last_Batval;
    int BatteryPercentage;

    virtual void activeNetwork(E_NetworkStatus nStatus,int nLevel);
    virtual void batteryLevel(int nLevel,int nPercentage);
    virtual void batteryChargeStatus(E_ChargeStatus eStatus);
    virtual void keypadMode(E_KeypadMode eMode,bool bCapsOn);
    virtual void keypadModeLocked( bool bModeLocked) ;
    virtual void gsmNetworkSignal(int nLevel);
    virtual void keypadLockStatus(bool bLocked);
    virtual void showDesktop();
    virtual void wakeupFromStandbyMode();
    virtual bool acceptStandby();
    virtual void showgps(bool flag);

signals:
    void EnableGPRS();

private slots:
    void DateTime_Click();
    void showPercentage();
    void updateCharging();
    void updateDateTime();
    void GPRS_Click();
    void menu_option_selected(QAction *action);
};

#endif // MYSERVER_H
