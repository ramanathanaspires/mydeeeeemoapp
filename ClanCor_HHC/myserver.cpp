#include "myserver.h"
#include <sys/vfs.h>
#include <sys/statfs.h>
#include "GlobalClass.h"
#include <gps_data.h>
#include <csettingsfiles.h>
using namespace Globalclass;

MyServer::MyServer()
{
    Current=1;
    BatteryPercentage=0;
    Last_Batval=6;
    Mainbar=new QWidget;
    btnDateTime=new QPushButton(Mainbar);
    calender=new QCalendarWidget(Mainbar);
    calender->setFixedSize(240,160);
    calender->hide();
    calender->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint);

    QPushButton *lblLogo=new QPushButton(Mainbar);
    lblLogo->setIcon(QIcon(":/icons-lib/logo.png"));
    lblLogo->setFocusPolicy(Qt::NoFocus);
    lblLogo->setStyleSheet("border:0");
    lblLogo->setIconSize(QSize(40,20));
    //    lblLogo->setGeometry(0,0,20,20);
    lblLogo->setGeometry(0,0,30,20);
    connect(lblLogo,SIGNAL(clicked()),this,SLOT(showDesktop()));

    lblTower=new QLabel(Mainbar);
//    lblTower->setGeometry(25,0,30,20);
     lblTower->setGeometry(25,0,30,20);
    lblTower->setPixmap(QPixmap(":/icons-lib/t0.png"));
//Present below icon not need when GPS is fixed that time icon have to dispaly alter on Oct 21 2013 by Mahesh
//    //ADD GPS ICON
    CSettingsFiles setting("ClanCor","config.xml");
    setting.beginSettingsGroup("SDKConfiguration");
    gstrXMLConfig= setting.value("GPS");
    if(gstrXMLConfig.toLower() == "yes")
    {
        lblGps = new QLabel(Mainbar);
//        lblGps->setGeometry(55,-3,20,20);
        lblGps->setGeometry(55,-3,30,20);
//        lblGps->setPixmap(QPixmap(":/icons-lib/GPSy.png"));
    }

    lbl_Penceil=new QLabel(Mainbar);
//    lbl_Penceil->setGeometry(75,0,20,20);
    lbl_Penceil->setGeometry(75,0,30,20);
    lbl_Penceil->setPixmap(QPixmap(":/icons-lib/pencil.png"));

    lbl_Keypad=new QLabel(Mainbar);
//    lbl_Keypad->setGeometry(95,0,25,20);
    lbl_Keypad->setGeometry(95,0,35,20);
    //    lbl_Keypad->setFont(QFont("sans serif",9,QFont::Bold));
    lbl_Keypad->setFont(QFont("sans serif",13,QFont::Bold));
    lbl_Keypad->setText("abc");

    lblLocked=new QPushButton(Mainbar);
    lblLocked->setGeometry(120,0,20,20);
    lblLocked->setFocusPolicy(Qt::NoFocus);
    lblLocked->setStyleSheet("border:0");
    lblLocked->setIconSize(QSize(20,20));

    btnDateTime->setFlat(true);
    btnDateTime->setFocusPolicy(Qt::NoFocus);
    btnDateTime->setStyleSheet("border:0");
//    btnDateTime->setGeometry(150,0,110,20);
        btnDateTime->setGeometry(130,0,130,20);
    //    btnDateTime->setFont(QFont("sans serif",9,QFont::Normal));
    btnDateTime->setFont(QFont("sans serif",14,QFont::Bold));
    connect(btnDateTime,SIGNAL(clicked()),this,SLOT(DateTime_Click()));
    btn_LanorGPRS=new QPushButton(Mainbar);
    btn_LanorGPRS->setFocusPolicy(Qt::NoFocus);
    btn_LanorGPRS->setStyleSheet("border:0");
//    btn_LanorGPRS->setIconSize(QSize(20,20));
//    btn_LanorGPRS->setGeometry(260,0,20,20);
    btn_LanorGPRS->setIconSize(QSize(30,20));
    btn_LanorGPRS->setGeometry(255,0,30,20);
    connect(btn_LanorGPRS,SIGNAL(clicked()),this,SLOT(GPRS_Click()));

    lblBattery=new QPushButton(Mainbar);
    /* To get current battery charge status from library */
    E_ChargeStatus eChargeStatus;
    if(g_ccmainObj->batteryChargeStatus(eChargeStatus))
    {
        if(eChargeStatus == ClanCor::eChargeStatus_NONE)
        {
            lblBattery->setIcon(QIcon(":/icons-lib/b0.png"));
        }
        else
        {
            batteryChargeStatus(eChargeStatus);
        }
    }
    else
    {
        lblBattery->setIcon(QIcon(":/icons-lib/b0.png"));
    }

    lblBattery->setFocusPolicy(Qt::NoFocus);
    lblBattery->setStyleSheet("border:0");
    lblBattery->setIconSize(QSize(35,20));
//    lblBattery->setGeometry(285,1,30,15);
     lblBattery->setGeometry(280,1,35,20);
    connect(lblBattery,SIGNAL(clicked()),this,SLOT(showPercentage()));

    myTopbar=new QToolBar("Top bar");
    myTopbar->setFocusPolicy(Qt::NoFocus);
    myTopbar->setFocus(Qt::NoFocusReason);
    myTopbar->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    myTopbar->setMovable(false);
    //    myTopbar->setFixedSize(320,20);
    myTopbar->setFixedSize(320,25);
    myTopbar->addWidget(Mainbar);

    myTopbar->layout()->setMargin(0);
    myTopbar->layout()->setSpacing(0);
    //Mainbar->setStyleSheet("background-color:#b9d0e8");
    //myTopbar->setStyleSheet("background-color:#b3c4d4");
    Mainbar->setFocusPolicy(Qt::NoFocus);
    Mainbar->setFocus(Qt::NoFocusReason);
    Mainbar->setWindowFlags(Qt::FramelessWindowHint);
    Mainbar->setFixedSize(320,240);

    updateDateTime();
    connect(&timerDT,SIGNAL(timeout () ), this, SLOT(updateDateTime()));
    timerDT.start(1000);
    connect(&timerCharging,SIGNAL(timeout () ), this, SLOT(updateCharging()));
    menu_Option=new QMenu;
    actionDisconnect =new QAction("Disconnect",this);
    menu_Option->addAction(actionDisconnect);
    connect(menu_Option,SIGNAL(triggered(QAction*)),this,SLOT(menu_option_selected(QAction*)));


}

MyServer::~MyServer()
{
    delete myTopbar;
}

void MyServer::activeNetwork(E_NetworkStatus eStatus, int nLevel)
{
    switch ((int)eStatus) {
    case eNetworkStatus_ETHERNET:
        btn_LanorGPRS->setIcon(QIcon(":/icons-lib/lan-connected.png"));
        break;
    case eNetworkStatus_GPRS:
        btn_LanorGPRS->setIcon(QIcon(":/icons-lib/gprs-connected.png"));
        break;
    case eNetworkStatus_WIFI:
        if( nLevel < 0) {
            if(nLevel == -1)
            {
                btn_LanorGPRS->setIcon(QIcon(":/icons-lib/wirelessfailed.png"));
            }
            else if(nLevel == -2)
            {
                btn_LanorGPRS->setIcon(QIcon(":/icons-lib/wirelessConnect.png"));
            }
        }
        else {
            btn_LanorGPRS->setIcon(QIcon(":/icons-lib/wireless" + QVariant(nLevel).toString() + ".png"));
        }
        break;
    default:
        btn_LanorGPRS->setIcon(QIcon(":/none.png"));
    }
}

void MyServer::batteryChargeStatus(E_ChargeStatus eStatus)
{
    switch ((int)eStatus) {
    case eChargeStatus_CONNECTED:
        flashMessage("Charger Connected");
        Current=1;
        timerCharging.start(500);
        break;
    case eChargeStatus_REMOVED:
        flashMessage("Charger Removed");
        Current=1;
        timerCharging.stop();
        break;
    case eChargeStatus_COMPLETED:
        flashMessage("Charge Full");
        timerCharging.stop();
        break;
    case eChargeStatus_INVALID:
        timerCharging.stop();
        lblBattery->setIcon(QIcon(":/icons-lib/b-1.png"));
        flashMessage("Invalid Charger \nor\n Battery not available..!");
        break;
    }
    Last_Batval=6;
}

void MyServer::batteryLevel(int nLevel, int nPercentage)
{
    if(nLevel==0)
    {
        if(Current==1)
        {
            flashMessage("Battery is Low!");
            g_ccmainObj->setBeep(eBeepType_ERROR_BEEP);
        }
        Current++;
        if(Current==3) Current=1;
    }
    if(Last_Batval!=nLevel)
    {
        Last_Batval=nLevel;
        //qDebug()<<"Update Battery Level: "+QVariant(nLevel).toString() +" Percentage: " +QVariant(nPercentage).toString() ;
        lblBattery->setIcon(QIcon(":/icons-lib/b"+ QString::number(nLevel) +".png"));
    }
    BatteryPercentage=nPercentage;
}

void MyServer::updateCharging()
{
    lblBattery->setIcon(QIcon(":/icons-lib/b"+ QString::number(Current) +".png"));
    if (Current<5) Current++; else Current=1;
}

void MyServer::keypadMode(E_KeypadMode eMode, bool bCapsOn)
{
    //    qDebug()<<"\r clancorMode"<<eMode<<"cap"<<bCapsOn;
    if (eMode==eKeypadMode_NUMERIC)
    {
        lbl_Keypad->setText("123");
    }else
    {
        if (bCapsOn==true)
            lbl_Keypad->setText("ABC");
        else
            lbl_Keypad->setText("abc") ;
    }
    //    qDebug()<<"Update Keypad Status:" + lbl_Keypad->text();
}

void MyServer::keypadModeLocked( bool bModeLocked )
{

    if(bModeLocked)
    {

        lbl_Penceil->setPixmap(QPixmap(":/icons-lib/pencil_locked.png"));
    }
    else
    {
        lbl_Penceil->setPixmap(QPixmap(":/icons-lib/pencil.png"));
    }
}
void MyServer::showgps(bool flag)
{
    if(flag)
    {
        lblGps->setPixmap(QPixmap(":/icons-lib/gpsfinal_new.png"));
    }
    else
    {
//        lblGps->setPixmap(QPixmap(":/icons-lib/GPSy.png"));
         lblGps->setPixmap(QPixmap(" "));
    }
}


void MyServer::gsmNetworkSignal(int nLevel)
{
    lblTower->setPixmap(QPixmap(":/icons-lib/t"+ QString::number(nLevel) +".png"));
}

void MyServer::keypadLockStatus(bool bLocked)
{
    if( bLocked == true ) {
        lblLocked->setIcon(QPixmap(":/icons-lib/lockedkey.png"));
        flashMessage("Keypad Locked");
    }
    else {
        lblLocked->setIcon(QIcon(":/none.png"));
        flashMessage("Keypad Active");
    }
}

void MyServer::showDesktop()
{
    if(RunningApplication && (LoginId!="" || LOGIN_MANAGEMENT == false))
    {
        if(!mainobj->isVisible())  mainobj->show(); else mainobj->hide();
    }
}

void MyServer::wakeupFromStandbyMode()
{
    if ( LoginId!="" ) {
        if ( LOGIN_MANAGEMENT ==  true )
            loadForm(LOGIN, 0);
        else
            loadForm(DESKTOP, 0);
    }
    if ( g_ccmainObj->isGprsInitiated() ) {
        emit EnableGPRS();
    }
}

void MyServer::updateDateTime()
{
    btnDateTime->setText(QDateTime::currentDateTime().toString("MMM dd, hh:mm AP"));
}

void MyServer::DateTime_Click()
{
    if(calender->isVisible())
    {
        btnDateTime->setStyleSheet("border:0");
        calender->close();
    }else
    {
        calender->setSelectedDate(QDateTime::currentDateTime().date());
        calender->move(QPoint(80,21));
        btnDateTime->setStyleSheet("border-width: 2px;border-color:#174763; border-style: solid; background-color:#eee8aa");
        calender->show();
    }
}

void MyServer::showPercentage()
{
    if(!timerCharging.isActive())
        popUpMessage("Battery: " +QVariant(BatteryPercentage).toString() +" %");
    else
        popUpMessage("Battery Charging");
}

void MyServer::GPRS_Click()
{
    if( g_ccmainObj->isGprs() == true ) {
        if( menu_Option->isVisible() == false ) {
            menu_Option->popup(QPoint(250,21));
            menu_Option->setActiveAction(actionDisconnect);
        }
        else {
            menu_Option->setVisible(false);
        }
    }
}

void MyServer::menu_option_selected(QAction *action)
{
    if(action->text()=="Disconnect")
    {
        if(QMessageBox::critical(0,"GPRS","Are you sure? \n Do you want to Disconnect?",QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
        {
            g_ccmainObj->disableGprs();
        }
    }
}

bool MyServer::acceptStandby()
{
    if(g_ccmainObj->isGprs())
    {
        if(DialupAutoGPRS_flag==true)
        {
            if(QMessageBox::critical(0,"GPRS","Are you sure? \n Do you want to Disconnect GPRS?",QMessageBox::Yes | QMessageBox::No)==QMessageBox::No)
            {
                return false;
            }
            else
            {
                g_ccmainObj->disableGprs();
            }
        }
        else
        {
            QMessageBox::critical(0,"GPRS","GPRS Active.. Standby Restricted..!");
            return false;
        }
    }
    return true;
}
