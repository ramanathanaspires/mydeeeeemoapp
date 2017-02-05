#include "cinputmethod.h"
#include <unistd.h>
#include "cglobal.h"
#include "csymboldialog.h"

using namespace ClanCor;
using namespace Global;

const int const_nKEYPAD_UNLOCK_TIMER_INTERVAL       = 4000;
const int const_nWIFI_SEARCH_TIMER_INTERVAL         = 4000;
const int const_nMOBILE_KEYPAD_TIMER_INTERVAL       = 1000;
const int const_nONE_SECOND_TIMER_INTERVAL          = 1000;

CInputMethod::CInputMethod():
    m_bUpperCase(false), m_bActive(false), m_bRunning(false),
    m_bScreenLocked(false), m_bSystemIdle(false),
    m_nScreenLockTime(0), m_nIdleTime(0),m_nStandbyTime(0)
{
    /* set the mobile keypad move next position timer interval */
    m_timerKeypad.setInterval(const_nMOBILE_KEYPAD_TIMER_INTERVAL);

    m_timerScreenUnlock.setInterval(const_nKEYPAD_UNLOCK_TIMER_INTERVAL);

    /* create the widget for display the screenlock message */
    m_widgetScreenLock = new QWidget;
    QFrame *frameScreen = new QFrame;
    frameScreen->setLineWidth(3);
    frameScreen->setMidLineWidth(3);
    frameScreen->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    m_labelStatusLock = new QLabel(frameScreen);
    m_labelStatusLock->setStyleSheet("background-color:#454d63;color:white");
    m_labelStatusLock->setFont(QFont("sans serif",14,1,false));
    m_labelStatusLock->setAlignment(Qt::AlignCenter);
    m_labelStatusLock->setWordWrap(true);
    //    m_labelStatusLock->setFixedSize(210,120);

    m_labelWakeupInfo = new QLabel("Press On key or Touchscreen to Wakeup");
    m_labelWakeupInfo->setFocusPolicy(Qt::NoFocus);
    m_labelWakeupInfo->setFont(QFont("sans serif",15,1,false));
    m_labelWakeupInfo->setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint);
    m_labelWakeupInfo->setStyleSheet("border-width: 2px;border-color:#2b396a; border-style: solid; background-color:white;");
    m_labelWakeupInfo->setAlignment(Qt::AlignCenter);
    m_labelWakeupInfo->setGeometry(0,0,320,40);
    m_labelWakeupInfo->setVisible(false);

    m_labelLockImage = new QLabel(frameScreen);
    m_labelLockImage->setStyleSheet("background-color:#454d63;color:white");
    m_labelLockImage->setFixedSize(50,120);

    QHBoxLayout *hBoxLayoutScreen = new QHBoxLayout;
    hBoxLayoutScreen->addWidget(m_labelLockImage);
    hBoxLayoutScreen->addWidget(m_labelStatusLock);
    hBoxLayoutScreen->setSpacing(0);
    hBoxLayoutScreen->setMargin(0);
    frameScreen->setLayout(hBoxLayoutScreen);

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    vBoxLayoutMain->addWidget(frameScreen);
    vBoxLayoutMain->setMargin(0);
    vBoxLayoutMain->setSpacing(0);
    m_widgetScreenLock->setLayout(vBoxLayoutMain);
    m_widgetScreenLock->setGeometry(30,60,260,120);
    m_widgetScreenLock->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_widgetScreenLock->setWindowModality(Qt::ApplicationModal);
    m_widgetScreenLock->setStyleSheet("background-color:#454d63;color:white;");

    /* create the dialog for display shutdown options */
    m_dialogShutdown = new QDialog;
    QFrame *frameShutdown = new QFrame;
    m_pushButtonCancel = new QPushButton("Cancel",frameShutdown);
    m_pushButtonCancel->setIcon(QIcon(":/icons-png/exit.png"));
    m_pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));
    m_pushButtonCancel->setFixedSize(100,30);
    m_pushButtonCancel->setAutoDefault(true);
    m_pushButtonCancel->setStyleSheet("QPushButton {background-color: palegoldenrod; color:black; border-width: 2px;"
                                      "border-color: darkkhaki; border-style: solid; "
                                      "padding: 3px; min-width: 9ex; min-height: 2.5ex;}QPushButton:focus { background-color: #e5ecff;}");
    connect(m_pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    QLabel *labelStatus = new QLabel("Are you sure want to Logout?");
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setWordWrap(true);
    labelStatus->setFixedWidth(200);
    QLabel *labelLock = new QLabel("Lock",frameShutdown);
    labelLock->setFont(QFont("sans serif",10,QFont::Bold));
    labelLock->setAlignment(Qt::AlignCenter);
    //    QLabel *labelStandby = new QLabel("Stand by",frameShutdown);
    //    labelStandby->setFont(QFont("sans serif",8,QFont::Bold));
    //    labelStandby->setAlignment(Qt::AlignCenter);
    QLabel *labelShutdown = new QLabel("Shut down",frameShutdown);
    labelShutdown->setFont(QFont("sans serif",10,QFont::Bold));
    labelShutdown->setAlignment(Qt::AlignCenter);
    //    QLabel *labelRestart = new QLabel("Restart",frameShutdown);
    //    labelRestart->setFont(QFont("sans serif",8,QFont::Bold));
    //    labelRestart->setAlignment(Qt::AlignCenter);

    m_pushButtonLock = new QPushButton(frameShutdown);
    m_pushButtonLock->setIcon(QIcon(":/icons-png/lock1.png"));
    m_pushButtonLock->setIconSize(QSize(50,50));
    //    m_pushButtonLock->setFixedSize(50,50);
    m_pushButtonLock->setFixedSize(60,60);
    m_pushButtonLock->setAutoDefault(true);
    connect(m_pushButtonLock, SIGNAL(clicked()), this, SLOT(keypadLocked()));

    //    m_pushButtonStandby = new QPushButton(frameShutdown);
    //    m_pushButtonStandby->setIcon(QIcon(":/icons-png/standby.png"));
    //    m_pushButtonStandby->setIconSize(QSize(40,40));
    //    m_pushButtonStandby->setFixedSize(50,50);
    //    m_pushButtonStandby->setAutoDefault(true);

    //disable stand by for HHC81xx
    //    m_pushButtonStandby->setDisabled(true);
    //    m_pushButtonStandby->setDisabled(false);
    //    connect(m_pushButtonStandby, SIGNAL(clicked()), this, SLOT(on_pushButtonStandby_clicked()));

    m_pushButtonShutDown = new QPushButton(frameShutdown);
    m_pushButtonShutDown->setIcon(QIcon(":/icons-png/shutdown.png"));
    m_pushButtonShutDown->setIconSize(QSize(50,50));
    //    m_pushButtonShutDown->setFixedSize(50,50);
    m_pushButtonShutDown->setFixedSize(60,60);
    m_pushButtonShutDown->setAutoDefault(true);
    connect(m_pushButtonShutDown, SIGNAL(clicked()), this, SLOT(on_pushButtonShutDown_clicked()));

    //    m_pushButtonRestart = new QPushButton(frameShutdown);
    //    m_pushButtonRestart->setIcon(QIcon(":/icons-png/restart.png"));
    //    m_pushButtonRestart->setIconSize(QSize(50,50));
    //    m_pushButtonRestart->setFixedSize(50,50);
    //    m_pushButtonRestart->setAutoDefault(true);
    //    m_pushButtonRestart->setDisabled(true);
    m_dialogShutdown->setStyleSheet("QDialog {background-color:#21293f;}QLabel{color:white;} QPushButton {background-color:#454d63; color:white; border:none; border-style: solid;} QPushButton:focus { background-color: #e5ecff; border-width: 2px; border-color:black;color:black}");
    //    connect(m_pushButtonRestart, SIGNAL(clicked()), this, SLOT(on_pushButtonRestart_clicked()));

    QHBoxLayout *hBoxLayoutOptions = new QHBoxLayout;
    hBoxLayoutOptions->addWidget(m_pushButtonLock );
    //    hBoxLayoutOptions->addWidget(m_pushButtonStandby);
    hBoxLayoutOptions->addWidget(m_pushButtonShutDown);
    //    hBoxLayoutOptions->addWidget(m_pushButtonRestart);
    QHBoxLayout *hBoxLayoutLabels = new QHBoxLayout;
    hBoxLayoutLabels->addWidget(labelLock);
    //    hBoxLayoutLabels->addWidget(labelStandby);
    hBoxLayoutLabels->addWidget(labelShutdown);
    //    hBoxLayoutLabels->addWidget(labelRestart);
    QVBoxLayout *vBoxLayoutFrame = new QVBoxLayout;
    vBoxLayoutFrame->addWidget(labelStatus,0,Qt::AlignCenter);
    vBoxLayoutFrame->addLayout(hBoxLayoutOptions);
    vBoxLayoutFrame->addLayout(hBoxLayoutLabels);
    vBoxLayoutFrame->addWidget(m_pushButtonCancel,0,Qt::AlignRight);
    vBoxLayoutFrame->setSpacing(0);
    vBoxLayoutFrame->setMargin(0);

    frameShutdown->setLayout(vBoxLayoutFrame);
    frameShutdown->setLineWidth(3);
    frameShutdown->setMidLineWidth(3);
    frameShutdown->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    QVBoxLayout *vBoxLayoutShutdown = new QVBoxLayout;
    vBoxLayoutShutdown->addWidget(frameShutdown);
    vBoxLayoutShutdown->setMargin(0);
    vBoxLayoutShutdown->setSpacing(0);
    m_dialogShutdown->setLayout(vBoxLayoutShutdown);

    m_dialogShutdown->setWindowTitle("System");
    m_dialogShutdown->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    m_dialogShutdown->setGeometry(50,40,220,160);
    m_dialogShutdown->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_dialogShutdown->setWindowModality(Qt::ApplicationModal);

    /* connect signal & slots for timers */
    connect(&m_timerIdle, SIGNAL(timeout()), this, SLOT(on_timerIdle_timeout()));
    connect(&m_timerScreenLock, SIGNAL(timeout()), this, SLOT(keypadLocked()));
    //    connect(&m_timerStandby, SIGNAL(timeout()), this, SLOT(on_pushButtonStandby_clicked()));
    connect(&m_timerScreenUnlock, SIGNAL(timeout()), this, SLOT(on_timerScreenUnock_timeout()));
    connect(&m_timerPowerControl, SIGNAL(timeout()), this, SLOT(autoPowerControl()));
    connect(&m_timerKeypad, SIGNAL(timeout()), this, SLOT(on_timerKeypad_timeout()));

    getDateTime();
    //    autoPowerControl();
    m_nErrorCountWifi = 0;
    Controlkeypress=false;
}

CInputMethod::~CInputMethod()
{
    /* free the allocated resources */
    delete m_widgetScreenLock;
    delete m_dialogShutdown;
}

/* to filter Keyboard inputs*/
bool CInputMethod::filter(int nUnicode, int nKeycode, int nModifiers,
                          bool bIsPress, bool bAutoRepeat)
{
    QString strsharedMem;
    gLoadFromSharedKey(strsharedMem);
    //    qDebug()<<"\r Enetr into leypress"<<nKeycode <<"Mode "<<strsharedMem<<"nuni "<<nUnicode;
    Q_UNUSED(bAutoRepeat);
    int nCurrentGroup;
    if ( m_bRunning )
    {
        /* reject if process is running */
        return true;
    }
    else
    {
        if ( eventFilter(nKeycode) )
        {
            /* reject if keypad is locked or doing some process */
            return true;
        }
        else
        {
            if ( !m_bActive )
            {
                return false;
            }
            else
            {
                //key value F11 Mode change button Pressed
                if(nKeycode == 16777274 && !Controlkeypress)
                {
                    reset();
                    Controlkeypress=true;
                    if(strsharedMem=="10" )
                    {
                        gpheripheralsPIC->m_bCapsLock=true;
                        gLoadIntoSharedKey(const_strKEYPAD_ALPHABETS_CAPS);
                        usleep(500);
                        emit keypadMode(eKeypadMode_ALPHABETS_CAPS,true);
                    }
                    else if(strsharedMem=="20")
                    {
                        gpheripheralsPIC->m_bCapsLock=false;
                        gLoadIntoSharedKey(const_strKEYPAD_NUMERIC);
                        usleep(500);
                        emit keypadMode(eKeypadMode_NUMERIC,false);
                    }
                    else if(strsharedMem=="30")
                    {
                        gpheripheralsPIC->m_bCapsLock=false;
                        gLoadIntoSharedKey(const_strKEYPAD_ALPHABETS);
                        usleep(500);
                        emit keypadMode(eKeypadMode_ALPHABETS,false);
                    }
                    m_strLastText = QString::null;
                    return true;
                }
                //key value F12 Mode change through software
                else if(nKeycode == 16777275 && !Controlkeypress)
                {
                    Controlkeypress=true;
                    if(strsharedMem=="10" )
                    {
                        gpheripheralsPIC->m_bCapsLock=true;
                        usleep(500);
                        emit keypadMode(eKeypadMode_ALPHABETS,false);
                    }
                    else if(strsharedMem=="20")
                    {
                        gpheripheralsPIC->m_bCapsLock=false;
                        usleep(500);
                        emit keypadMode(eKeypadMode_ALPHABETS_CAPS,true);
                    }
                    else if(strsharedMem=="30")
                    {
                        gpheripheralsPIC->m_bCapsLock=false;
                        usleep(500);
                        emit keypadMode(eKeypadMode_NUMERIC,false);
                    }
                    m_strLastText = QString::null;
                    return true;
                }
                //key value F9 Mode Lock function
                else if(nKeycode==16777272 && !Controlkeypress && (strsharedMem=="11" || strsharedMem=="21" || strsharedMem =="31"))
                {
                    usleep(500);
                    emit keypadModeLocked(true);
                }
                //key value F10 Mode unlock function
                else if(nKeycode==16777273 && !Controlkeypress && (strsharedMem=="10" || strsharedMem=="20" || strsharedMem =="30"))
                {
                    usleep(500);
                    emit keypadModeLocked(false);
                }
                else if(strsharedMem=="30" && nKeycode != Qt::Key_Exclam)
                {
                    /*for the below error this is implemented
                    ASSERT: "!atEnd()" in file ../../include/QtGui/private/../../../src/gui/text/qfragmentmap_p.h */
                    /* check if retrieved key code is exclam (!), to show symbol dialog */
                    /* Key_At changed to Key_Exclam, due to Key_At added into char rotation on key 1*/
                    Controlkeypress=false;
                    return false;
                }
                else
                {
                    Controlkeypress=false;
                }
            }

            if(!(( nKeycode >= Qt::Key_0 && nKeycode <= Qt::Key_Z)
                 || nKeycode == Qt::Key_Space || nKeycode == Qt::Key_At
                 || nKeycode == Qt::Key_Comma || nKeycode == Qt::Key_Asterisk))
            {
                if(nKeycode==Qt::Key_Shift)
                {
                    return false;
                }
                reset();
                /* accept except these keys */
                /* check if retrieved key code is exclam (!), to show symbol dialog */
                if(nKeycode == Qt::Key_Exclam)      /* Key_At chacnged to Key_Exclam, due to Key_At added into char rotation on key 1*/
                {
                    QWidget *focusWidg = QApplication::focusWidget();
                    /* Show symbol dialog */
                    QString strSymbol = CSymbolDialog::getSymbol();
                    if ( strSymbol != "" )
                    {
                        if ( focusWidg )
                        {
                            /* send the key into the last focused widget */
                            QKeyEvent keyEvent(
                                        QEvent::KeyPress,
                                        strSymbol.at(0).toAscii(),
                                        Qt::NoModifier,
                                        strSymbol
                                        );
                            QApplication::sendEvent(focusWidg, &keyEvent);
                            focusWidg->setFocus();
                        }
                        else
                        {
#ifdef Q_WS_QWS
                            QInputMethodEvent inputMethodEvent;
                            /* set commit string -- symbol which is selected on symbol dialog */
                            inputMethodEvent.setCommitString ( strSymbol );
                            QWSInputMethod::sendEvent(&inputMethodEvent);
#endif
                        }
                    }
                }
                else
                {
                    return false;
                }
                /* reject the keys not completed */
                return true;
            }

            if ( bIsPress )
            {
                //16777248 shift
                //                if ( nKeycode == Qt::Key_Shift )
                //                {
                //                    return false;
                //                }
                //                else
                if(strsharedMem == "30")
                {
                    /* process the pressed key with group */
                    nCurrentGroup = whichGroup(nKeycode);
                    if ( nCurrentGroup > 0 && nCurrentGroup<=10)
                    {
                        m_strLastText = QString::number(nCurrentGroup);
                        if(m_strLastText=="10")
                            m_strLastText="0";
#ifdef Q_WS_QWS
                        if ( ! m_strLastText.isEmpty() )
                        {
                            /* commit the current text and move cursor to next position */
                            sendCommitString(m_strLastText);
                        }
                        m_strLastText = QString::null;
#endif
                    }
                }
                else
                {
                    /* process the pressed key with group */
                    nCurrentGroup = whichGroup(nKeycode);
                    if ( nCurrentGroup >= 0 )
                    {
                        if ( m_timerKeypad.isActive() )
                        {
                            m_timerKeypad.stop();
                            if ( m_nLastGroup != nCurrentGroup )
                            {
                                on_timerKeypad_timeout();
                            }
                        }
                        m_strLastText = QChar(nUnicode);
                        m_bUpperCase = (nModifiers & Qt::ShiftModifier) == Qt::ShiftModifier;
#ifdef Q_WS_QWS
                        sendPreeditString(m_strLastText, 0,1);
#endif
                        /* Start Key rotation timer */
                        m_timerKeypad.start();
                        m_nLastGroup = nCurrentGroup;
                    }
                }
            }
            /* reject the keys not completed */
            return true;
        }
    }
}

int CInputMethod::whichGroup(int nKeycode)
{
    /* process the which group by given key */
    int groupNo=0;
    switch ( nKeycode )
    {
    /* group the keys with unique group numbers */
    case Qt::Key_At:
    case Qt::Key_Comma:
        //    case Qt::Key_Period:
        //        case Qt::Key_Underscore:
    case Qt::Key_Asterisk:
    case Qt::Key_1:
    {
        /* commented to implement character rotation on key 1 during alphabet mode in 70xx model*/
        //            QWidget *focusWidg = QApplication::focusWidget();
        //            /* Show symbol dialog */
        //            QString strSymbol = CSymbolDialog::getSymbol();
        //            if ( strSymbol != "" ) {
        //                if ( focusWidg ) {
        //                    /* send the key into the last focused widget */
        //                    QKeyEvent keyEvent(
        //                            QEvent::KeyPress,
        //                            strSymbol.at(0).toAscii(),
        //                            Qt::NoModifier,
        //                            strSymbol
        //                            );
        //                    QApplication::sendEvent(focusWidg, &keyEvent);
        //                    focusWidg->setFocus();
        //                }
        //                else
        //                {
        //                    QInputMethodEvent inputMethodEvent;
        //                    /* set commit string -- symbol which is selected on symbol dialog */
        //                    inputMethodEvent.setCommitString ( strSymbol );
        //                    QWSInputMethod::sendEvent(&inputMethodEvent);
        //                }
        //          }
        groupNo = 1;
        break;
    }
    case Qt::Key_A:
    case Qt::Key_B:
    case Qt::Key_C:
    case Qt::Key_2:
    {
        groupNo = 2;
        break;
    }
    case Qt::Key_D:
    case Qt::Key_E:
    case Qt::Key_F:
    case Qt::Key_3:
    {
        groupNo = 3;
        break;
    }
    case Qt::Key_G:
    case Qt::Key_H:
    case Qt::Key_I:
    case Qt::Key_4:
        groupNo = 4;
        break;
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_5:
        groupNo = 5;
        break;
    case Qt::Key_M:
    case Qt::Key_N:
    case Qt::Key_O:
    case Qt::Key_6:
        groupNo = 6;
        break;
    case Qt::Key_P:
    case Qt::Key_Q:
    case Qt::Key_R:
    case Qt::Key_S:
    case Qt::Key_7:
        groupNo = 7;
        break;
    case Qt::Key_T:
    case Qt::Key_U:
    case Qt::Key_V:
    case Qt::Key_8:
        groupNo = 8;
        break;
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
    case Qt::Key_9:
        groupNo = 9;
        break;
    case Qt::Key_0:
    case Qt::Key_Space:
        groupNo = 10;
        break;
    default:
        groupNo = 12;
    }
    return groupNo;
}

/* to filter mouse inputs*/
bool CInputMethod::filter(const QPoint &pointPosition, int nState, int nWheel)
{
    Q_UNUSED(pointPosition);
    Q_UNUSED(nState);
    Q_UNUSED(nWheel);
    if ( m_bRunning ) {
        /* reject if process is running */
        return true;
    }
    else {
        /* accept or reject to process it*/
        return eventFilter(-1);
    }
}

void CInputMethod::on_pushButtonShutDown_clicked()
{
    /* shutdown the device */
    m_dialogShutdown->close();
    glabelStatus->setText("Device is Shutting Down... ");
    glabelStatus->show();
    gUpdateScreen();
    gpheripheralsPIC->setBeep(eBeepType_LONG_BEEP);
    /*Check if the device 80xx then dim backlight */
    if ( gstrDeviceModel.contains("HHC-80") ) {
        /* decrease the backlight step by step */
        for ( int nValue = 2; nValue >= 0; nValue -- ) {
            usleep(500000);
            gpheripheralsPIC->setBacklight(nValue);
        }
    }
    /* intimate shutdown to co-processor */
    gpheripheralsPIC->shutDown();
    /* intimate shutdown to os */
    system(QString("poweroff").toLatin1());
}

void CInputMethod::on_pushButtonStandby_clicked()
{    
    //    /* emit idle mode if gbProcessRunning & gbIdleStatus is false */
    //    if ( ( ! gbProcessRunning ) && ( ! gbIdleStatus ) ) {
    //        emit standbyTimeout();
    //    }
    //    m_dialogShutdown->close();
}

void CInputMethod::on_pushButtonRestart_clicked()
{
    /* restart the device */
    m_dialogShutdown->close();
    glabelStatus->setText("Restarting Device... ");
    glabelStatus->show();
    gUpdateScreen();
    /*Check if the device 80xx then dim backlight */
    if ( gstrDeviceModel.contains("HHC-80") ) {
        /* decrease the backlight step by step */
        for ( int nValue = 2; nValue >= 0; nValue -- ) {
            usleep(500000);
            gpheripheralsPIC->setBacklight(nValue);
        }
    }
    /* intimate reset to co-processor */
    gpheripheralsPIC->resetCoProcessor();
    /* intimate reboot to os */
    system(QString("reboot").toLatin1());
}

void CInputMethod::on_pushButtonCancel_clicked()
{
    m_dialogShutdown->close();
}

void CInputMethod::on_timerIdle_timeout()
{
    /* emit idle mode if gbProcessRunning & gbIdleStatus is false */
    if ( ( ! gbProcessRunning ) && ( ! gbIdleStatus ) ) {
        emit idleModeTimeout();
    }
}

void CInputMethod::shutdownDialog()
{
    if ( m_bScreenLocked ) {
        /* show screen locked */
        m_widgetScreenLock->show();
        gUpdateScreen();
        resetTimer();
    }
    else {
        /* display shutdown dialog */
        m_pushButtonLock->setFocus();
        m_dialogShutdown->show();
        m_dialogShutdown->move(50,40);
        gUpdateScreen();
    }
}

void CInputMethod::setKeypadLockTimeout(int nSecs)
{
    m_nScreenLockTime = nSecs;
    m_timerScreenLock.stop();
    m_timerScreenLock.setInterval(nSecs * const_nONE_SECOND_TIMER_INTERVAL);
    if ( nSecs > 0 ) {
        m_timerScreenLock.start();
    }
}

void CInputMethod::setIdleModeTimeout(int nSecs)
{
    m_nIdleTime = nSecs;
    m_timerIdle.stop();
    m_timerIdle.setInterval(nSecs * const_nONE_SECOND_TIMER_INTERVAL);
    if ( nSecs > 0 ) {
        m_timerIdle.start();
    }
}

void CInputMethod::setStandbyModeTimeout(int nSecs)
{
    //    m_nStandbyTime = nSecs;
    //    m_timerStandby.stop();
    //    m_timerStandby.setInterval(nSecs * const_nONE_SECOND_TIMER_INTERVAL);
    //    if ( nSecs > 0 ) {
    //        m_timerStandby.start();
    //    }
}

void CInputMethod::resetTimer()
{        
    if ( ! m_bRunning ) {
        /* restart the timer */
        m_Mutex.lock();
        m_timerIdle.stop();
        m_timerScreenLock.stop();
        m_timerStandby.stop();
        if ( m_nScreenLockTime > 0 ) {
            m_timerScreenLock.start();
        }
        if ( m_nIdleTime > 0 ) {
            m_timerIdle.start();
        }
        if ( m_nStandbyTime > 0 ) {
            m_timerStandby.start();
        }
        gbProcessRunning = false;
        m_Mutex.unlock();
    }
}

bool CInputMethod::eventFilter(int nKeycode)
{
    if ( m_bSystemIdle  && ( ! gbProcessRunning ) ) {
        /* wake up from touch screen */
        m_bSystemIdle = false;
        gpheripheralsPIC->wakeUpFromIdle();
        wakeup(false);
        return true;
    }
    if ( glabelStatus->isVisible() || m_labelWakeupInfo->isVisible() ) {
        /* reject the key during screenlock/idle/standby mode */
        return true;
    }
    if ( ! m_bSystemIdle ) {
        if ( ! gbProcessRunning ){
            /* reset the timer */
            resetTimer();
        }
        if ( m_bScreenLocked ) {
            if ( nKeycode >= 0 ) {
                /* unlock the keypad press escape then press enter */
                if ( m_labelStatusLock->windowIconText() == "Escape" ) {
                    if ( nKeycode == Qt::Key_Escape ) {
                        m_labelStatusLock->setText("Now Press Enter key");
                        m_labelStatusLock->setWindowIconText("Enter");
                        m_labelLockImage->setPixmap(QPixmap(":/icons-png/key.png"));
                    }
                }
                else {
                    if ( nKeycode == Qt::Key_Return ) {
                        keypadUnLocked();
                    }
                }
            }
            if ( m_bScreenLocked ) {
                /* display the message 4 second if screen is locked */
                m_widgetScreenLock->show();
                m_timerScreenUnlock.stop();
                m_timerScreenUnlock.start();
                gUpdateScreen();
            }
            return true;
        }
    }
    return false;
}

void CInputMethod::on_timerScreenUnock_timeout()
{
    m_timerScreenUnlock.stop();
    m_widgetScreenLock->close();
    m_labelStatusLock->setText("Press Escape key and then Enter key");
    m_labelLockImage->setPixmap(QPixmap(":/icons-png/lock.png"));
    m_labelStatusLock->setWindowIconText("Escape");
}

void CInputMethod::idleMode()
{    
    /* pause the threads before goto idle mode */
    qDebug()<<"Going to Idle Mode";
    gbProcessRunning = true;
    m_bRunning = true;
    m_timerIdle.stop();
    m_labelStatusLock->setText("Press Escape key and then Enter key");
    m_labelLockImage->setPixmap(QPixmap(":/icons-png/lock.png"));
    m_labelStatusLock->setWindowIconText("Escape");
    glabelStatus->setText("Idle Mode...");
    m_labelWakeupInfo->setText("Press On key or Touchscreen to Wakeup");
    m_labelWakeupInfo->setVisible(true);
    glabelStatus->show();
    gUpdateScreen();
    QEventLoop leventloopDelay;
    QTimer::singleShot(1500, &leventloopDelay, SLOT(quit()));
    leventloopDelay.exec();

    closeKeyboard();
    if ( gbAudioRunning ) {
        system(QString("alsactl store").toLatin1());
    }
    gnetworkActive->suspendNWThread();
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ggsmModuleSimCom->isInitiated() && ( ! gbGprsConnected ) ) {
            ggsmModuleSimCom->pauseThread();
        }
    }
    gpheripheralsPIC->gotoIdle();
    m_bSystemIdle = true;
    m_widgetScreenLock->close();
    glabelStatus->close();
    gbProcessRunning = false;
    m_bRunning = false;
}

void CInputMethod::closeKeyboard()
{
#ifdef Q_WS_QWS
    if ( gserverObj != NULL ) {
        //QWSServer::setDefaultKeyboard("LinuxInput:/dev/input/event1");
        gserverObj->closeKeyboard();
    }
#endif
}

void CInputMethod::resetKeyboard()
{
#ifdef Q_WS_QWS
    if ( gserverObj != NULL ) {
        //QWSServer::setDefaultKeyboard("LinuxInput:/dev/input/event1");
        qDebug()<<"Reset keyboard";
        gserverObj->closeKeyboard();
        gserverObj->openKeyboard();
        gserverObj->refresh();
        //#if SERIAL_DEBUG_FLAG
        //        gserialportDebug->close();
        //        gserialportDebug->open();
        //#endif
    }
#endif
}

void CInputMethod::keypadLocked()
{
    if ( ( ! gbProcessRunning ) && ( ! m_bScreenLocked ) ) {
        /* keypad is locked */
        m_dialogShutdown->close();
        m_timerScreenLock.stop();
        m_labelStatusLock->setText("Press Escape key and then Enter key");
        m_labelLockImage->setPixmap(QPixmap(":/icons-png/lock.png"));
        m_labelStatusLock->setWindowIconText("Escape");
        emit keypadLockStatus(true);
        m_bScreenLocked = true;
    }
}


void CInputMethod::keypadUnLocked()
{
    /* keypad is unlocked */
    m_widgetScreenLock->close();
    resetTimer();
    m_timerScreenUnlock.stop();
    emit keypadLockStatus(false);
    m_bScreenLocked = false;
}

void CInputMethod::autoPowerControl()
{
    /*auto power control to all usb devices */
    QDir dir;
    QString strDevice;
    if(m_timerPowerControl.isActive())
        m_timerPowerControl.stop();
    /* To remove wifi module, due to device got hanged when auto power control was set*/
    //    system(QString("rmmod 8192cu").toLatin1());

    /* to set auto power control for all the available usb devices */
    for ( int nId = 0; nId < 10; nId ++ ) {
        strDevice ="/sys/bus/usb/devices/1-1." + gConvertToString(nId);
        if ( dir.exists(strDevice) ) {
            strDevice = "echo auto >" + strDevice + "/power/control";
            system(strDevice.toLatin1());
        }
        strDevice.clear();
    }
    if( QFile::exists("/dev/audio") ) {
        if ( gbAudioRunning ) {
            system(QString("alsactl restore").toLatin1());
        }
        else {
            gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO, false,false);
        }
    }
}

void CInputMethod::wakeup(bool bFlagStandby)
{
    /* wake up from idle or standby */
    //    system("ifdown eth0");
    m_bSystemIdle = false;
    gbProcessRunning = true;
    m_bRunning = true;
    m_timerIdle.stop();
    m_timerScreenLock.stop();
    int nBrightness = ghhc80xxServerObj->backlight();
    //***************************************************************//
    //     ghhc80xxServerObj->setBacklight(nBrightness);//
    //********following code was changed by askar on 31Oct, Found an bug that display brightness is dim in 70xx while waking up from idle / standby mode*//
    //    qDebug()<<"\r"<<gstrDeviceModel<<nBrightness;
    if ( nBrightness != 0 ) {
        gpheripheralsPIC->setBacklight(nBrightness);
    }
    //***************************************************************//
    m_labelWakeupInfo->setText("Please wait ....");
    gUpdateScreen();
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if ( ggsmModuleSimCom->isInitiated() && ( ! gbGprsConnected ) )
        {
            if ( bFlagStandby )
            {
                /* gsm module would be powered off in standby mode */
                gpheripheralsPIC->enableModule(CPheripherals::emodule_GPRS,true,false);
                sleep(3);
                ggsmModuleSimCom->initModule();
                ggsmModuleSimCom->startThread();
            }
            else
            {
                ggsmModuleSimCom->startThread();
            }
        }
    }
    waitForKeyboard();
    gnetworkActive->startThreadWakeUp();
    m_timerPowerControl.start(8000);
    //#if SERIAL_DEBUG_FLAG
    //    gserialportDebug->close();
    //    gserialportDebug->open();
    //#endif
    m_bRunning = false;
    resetTimer();
    m_labelWakeupInfo->setVisible(false);
    if ( bFlagStandby ) {
        //#if SERIAL_DEBUG_FLAG
        //        gWriteDataToComport("Wakeup from Standby Mode");
        //#endif
        getDateTime();
        emit wakeupFromStandbyMode();
    }
    else {
        //#if SERIAL_DEBUG_FLAG
        //        gWriteDataToComport("Wakeup from Idle Mode");
        //#endif
        emit wakeupFromIdleMode();
    }
}

void CInputMethod::waitForKeyboard()
{
    /* open the keyboard input event if input event device is found */
    bool nFound = false;
    for ( int nCount = 0; nCount < 40; nCount ++ ) {
        usleep(100000);
        if ( QFile::exists("/dev/input/event1") ) {
            nFound = true;
            break;
        }
    }
    if ( nFound ) {
        resetKeyboard();
    }
    else {
        //#if SERIAL_DEBUG_FLAG
        //        gWriteDataToComport("input event1 not found");
        //#endif

    }
}

bool CInputMethod::getDateTime()
{
    QDateTime datetimeDT;
    if ( gpheripheralsPIC->dateTime(datetimeDT) ) {
        int nYear, nMonth, nDay, nHour, nMinutes;
        nYear = datetimeDT.date().year();
        nMonth = datetimeDT.date().month();
        nDay = datetimeDT.date().day();
        nHour = datetimeDT.time().hour();
        nMinutes = datetimeDT.time().minute();
        system(QString("date -s \"" +
                       gConvertToString(nYear) + "-" +
                       gConvertToString(nMonth) + "-" +
                       gConvertToString(nDay) +" " +
                       gConvertToString(nHour) + ":" +
                       gConvertToString(nMinutes) +":0\"").toLatin1());
        //        qDebug("\n" + datetimeDT.toString("dd-MM-yyyy hh:mm:ss").toLatin1());
        return true;
    }
    else {
        qDebug("\rFailed to Get Datetime from CoProcessor\n");
        return false;
    }
}

void CInputMethod::standbyMode()
{
    //    /* do the process standby */
    //    qDebug()<<"Going to standby Mode";
    //    m_labelWakeupInfo->close();
    //    m_timerIdle.stop();
    //    m_timerStandby.stop();
    //    m_dialogShutdown->close();
    //    m_bRunning = true;
    //    gbProcessRunning = true;
    //    closeKeyboard();
    //    glabelStatus->setText("Standby Mode... ");
    //    glabelStatus->show();
    //    gUpdateScreen();

    //    QEventLoop leventloopDelay;
    //    QTimer::singleShot(1500, &leventloopDelay, SLOT(quit()));
    //    leventloopDelay.exec();

    //    if ( gbAudioRunning ) {
    //        system(QString("alsactl store").toLatin1());
    //    }
    //    gnetworkActive->suspendNWThread();
    //    if ( ggsmModuleSimCom->isInitiated() && ( ! gbGprsConnected ) ) {
    //        ggsmModuleSimCom->pauseThread();
    //    }
    //    if ( gbLanConnected ) {
    //        iffDown("eth0");
    //    }
    //    gsplash->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //    qApp->setActiveWindow(gsplash);
    //    gsplash->show();
    //    gsplash->showMessage("\nResuming ...\n Please Wait...", Qt::AlignCenter|Qt::AlignBottom, Qt::black);
    //    glabelStatus->close();
    //    gUpdateScreen(100);
    //    qApp->processEvents();
    //    gpheripheralsPIC->gotoStandby();
    //    system(QString("echo standby >/sys/power/state").toLatin1());
    //    wakeup(true);
    //    m_bRunning = false;
    //    gsplash->close();
    //    qApp->processEvents();
}

void CInputMethod::setActiveMobileKeypad(bool bActive)
{
    if ( bActive && ( bActive != m_bActive ) ) {
        m_strLastText.clear();
        m_bUpperCase = false;
    }
    m_bActive = bActive;
}

void CInputMethod::reset()
{
#ifdef Q_WS_QWS
    if ( ! m_strLastText.isEmpty() ) {
        sendCommitString(m_strLastText);
    }
    m_bUpperCase = false;
    m_strLastText = QString::null;
#endif
}

void CInputMethod::on_timerKeypad_timeout()
{
#ifdef Q_WS_QWS
    m_timerKeypad.stop();
    if ( ! m_strLastText.isEmpty() ) {
        /* commit the current text and move cursor to next position */
        sendCommitString(m_strLastText);
    }
    m_bUpperCase = false;
    m_strLastText = QString::null;
#endif
}

void CInputMethod::sendBarcodeData(const QString &r_const_strDATA)
{
#ifdef Q_WS_QWS
    sendCommitString(r_const_strDATA +"\n");
    gpheripheralsPIC->setBeep(eBeepType_SUCCESS_BEEP);
#endif
}
