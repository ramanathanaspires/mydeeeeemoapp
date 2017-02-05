#include "cpheripherals.h"
#include "cglobal.h"
extern "C"
{
#include "cbootloader.h"
}

using namespace ClanCor;
using namespace Global;

const int const_nWAIT_FOR_RESPONSE                  = 100;

CPheripherals::CPheripherals(const QString r_const_strPORTNAME):
    m_mutex(QMutex::Recursive), m_eChargeStatus(eChargeStatus_NONE),
    m_bHandshakePIC(false), m_bThreadRunning(false), m_bThreadPause(false),
    m_bIdleMode(false), m_bBatteryCharging(false), m_bInvalidCharger(false),
    m_bCapsLock(false), m_bKeypadModeLocked(false), m_nPrevBatt(101)
{
    /* create a dialog screen for adjust the brightness when grayscale printing */
    m_dialogGrayScale = new QDialog;

    m_labelImage = new QLabel(m_dialogGrayScale);
    m_labelImage->setBackgroundRole(QPalette::Base);
    m_labelImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_labelImage->setScaledContents(true);
    m_labelImage->setFixedSize(132,132);

    m_sliderBrightness = new QSlider(Qt::Horizontal,m_dialogGrayScale);
    m_sliderBrightness->setFocusPolicy(Qt::StrongFocus);
    m_sliderBrightness->setTickPosition(QSlider::TicksBelow);
    m_sliderBrightness->setTickInterval(10);
    m_sliderBrightness->setMaximum(100);
    m_sliderBrightness->setMinimum(-100);
    m_sliderBrightness->setTracking(true);
    m_sliderBrightness->setSingleStep(10);
    connect(m_sliderBrightness, SIGNAL(valueChanged(int)), SLOT(updateBrightness()));

    QScrollArea *scrollArea = new QScrollArea(m_dialogGrayScale);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(m_labelImage);
    scrollArea->setFixedSize(137,137);

    //    QPushButton *pushButtonPrint = new QPushButton("Print -F1",m_dialogGrayScale);
    QPushButton *pushButtonPrint = new QPushButton("Print",m_dialogGrayScale);
    //    pushButtonPrint->setShortcut(QKeySequence(Qt::Key_F1));
    pushButtonPrint->setFont(QFont("sans serif",12,QFont::Bold));
    pushButtonPrint->setFixedSize(155,25);
    connect(pushButtonPrint, SIGNAL(clicked()),     this, SLOT(on_pushButtonPrint_clicked()));

    //    QPushButton *pushButtonCancel = new QPushButton("Cancel -F4",m_dialogGrayScale);
    QPushButton *pushButtonCancel = new QPushButton("Cancel",m_dialogGrayScale);
    //    pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));
    pushButtonCancel->setFixedSize(155,25);
    connect(pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    QLabel *lableBrightness = new QLabel("Brightness:");

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    QHBoxLayout *hBoxLayoutBrightness = new QHBoxLayout;
    QHBoxLayout *hBoxLayoutBottom = new QHBoxLayout;

    hBoxLayoutBrightness->addWidget(lableBrightness);
    hBoxLayoutBrightness->addWidget(m_sliderBrightness);
    hBoxLayoutBottom->addWidget(pushButtonPrint);
    hBoxLayoutBottom->addWidget(pushButtonCancel);
    vBoxLayoutMain->addLayout(hBoxLayoutBrightness);
    vBoxLayoutMain->addWidget(scrollArea,0,Qt::AlignCenter);
    vBoxLayoutMain->addLayout(hBoxLayoutBottom);

    m_dialogGrayScale->setLayout(vBoxLayoutMain);
    m_dialogGrayScale->setGeometry(0,20,320,220);
    m_dialogGrayScale->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    m_dialogGrayScale->setWindowModality(Qt::ApplicationModal);

    /* create a dialog screen for showing when paper not available in printing */
    m_dialogPrint = new QDialog;

    m_labelPrinterStatus = new QLabel("Status:", m_dialogPrint);
    m_labelPrinterStatus->setFixedSize(250,25);
    m_labelPrinterStatus->setFont(QFont("sans serif",12,1,false));
    m_labelPrinterStatus->setAlignment(Qt::AlignCenter);

    //    m_pushButtonPrint = new QPushButton("Print -F1", m_dialogPrint);
    m_pushButtonPrint = new QPushButton("Print", m_dialogPrint);
    //    m_pushButtonPrint->setShortcut(QKeySequence(Qt::Key_F1));
    m_pushButtonPrint->setFont(QFont("sans serif",12,QFont::Bold));
    connect(m_pushButtonPrint,SIGNAL(clicked()),this,SLOT(on_pushButtonPrint_clicked()));

    //    m_pushButtonCancel = new QPushButton("Cancel -F4",m_dialogPrint);
    m_pushButtonCancel = new QPushButton("Cancel",m_dialogPrint);
    //    m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    m_pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));
    connect(m_pushButtonCancel,SIGNAL(clicked()),this,SLOT(on_pushButtonCancel_clicked()));

    QVBoxLayout *vBoxLayoutPrint=new QVBoxLayout(m_dialogPrint);
    QHBoxLayout *hBoxLayout=new QHBoxLayout;

    hBoxLayout->addWidget(m_pushButtonPrint);
    hBoxLayout->addWidget(m_pushButtonCancel);
    vBoxLayoutPrint->addWidget(m_labelPrinterStatus);
    vBoxLayoutPrint->addLayout(hBoxLayout);

    m_dialogPrint->setLayout(vBoxLayoutPrint);
    m_dialogPrint->setFixedSize(250,120);
    m_dialogPrint->setWindowTitle("Printer");
    m_dialogPrint->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint );
    m_dialogPrint->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    m_dialogPrint->setWindowModality(Qt::ApplicationModal);

    connect(m_dialogPrint, SIGNAL(rejected()), this, SLOT(on_pushButtonCancel_clicked()));

    qApp->setWindowIcon(QIcon(":/icons-png/logo.ico"));

    /* Initialize the co-processor port */
    portInitialize(r_const_strPORTNAME);
#ifdef Q_WS_QWS    
    m_bHandshakePIC = handShaking();
    if(m_bHandshakePIC) {

        /* set Machine id command, used to set machine id from software */
        //        sendData(const_cPHERIPHERAL_MACHINE, 'S', "00000000000800001144", 3000);

        /* Get battery charge status, to identify the battery charge status (charging / invalid charger) while initializing. */
        sendData(const_cPHERIPHERAL_IO_CONTROL, const_cPACKETID_SUPPLY_STATUS, "B", 1000);
        //For Enable GPRS from booting
        enableModule(emodule_GPRS,true);
        sleep(2);
        /*  To get updated battery status on display (GUI), change m_nPrevBat value to default value (101) because
            previous line might get update battery value before GUI objects initialized */
        m_nPrevBatt = 101;

        /* Get keypad status, to identify the status of keypad while initializing. (ie) whether locked or unloacked */
        sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_STATUS, "", 5000);      //Keypad status
    }
#endif
}

CPheripherals::~CPheripherals()
{
    /* stop the thread and close the port */
    stopThread();
    m_serialportCoProcessor->close();

    /* free the allocated resources */
    delete m_serialportCoProcessor;
    delete m_dialogGrayScale;
    delete m_dialogPrint;
}

bool CPheripherals::portInitialize(const QString &r_const_strPORTNAME)
{
    /* initialize the port for sending and receiving data */
    m_serialportCoProcessor = new QextSerialPort();
    DEBUGMESSAGE("Gsm module port name : " + r_const_strPORTNAME);
    m_serialportCoProcessor->setPortName(r_const_strPORTNAME);
    m_serialportCoProcessor->setDataBits(DATA_8);
    m_serialportCoProcessor->setParity(PAR_NONE);
    m_serialportCoProcessor->setFlowControl(FLOW_OFF);
    m_serialportCoProcessor->setStopBits(STOP_1);
    m_serialportCoProcessor->setBaudRate(BAUD115200);
    if ( m_serialportCoProcessor->open() ) {
        return true;
    }
    else {
        //        qDebug()<<"\rFailed  to open CoProcessor port..!";
        return false;
    }
}

bool CPheripherals::isBootloader()
{
    if ( isUSBBootloader() ) {
        /* check whether the device is switched on bootloader mode or not */
        return true;
    }
    else {
        return false;
    }
}

bool CPheripherals::programCoProcessor(const QString &r_const_FILENAME)
{    
    QFileInfo fileInfo(r_const_FILENAME);
    if ( ! fileInfo.exists() ) {
        /* check the co-processor program file is exist on given location */
        QMessageBox::critical(0,"HID Bootloader Error", "Program file does not exists on the path..\n\t\tAbort");
        return false;
    }

    pauseThread();
    /* create a dialog screen for show the status when updating co-processor program */
    QWidget widgetCoProcessor;
    /* used to show the gif image */
    QMovie movie;
    /* display the status of program dialog */
    QLabel labelStatus;
    /* used to apply the movie for animate gif image */
    QLabel labelMovie;
    movie.setFileName(":/icons-png/chip.gif");
    movie.setCacheMode(QMovie::CacheAll);
    labelMovie.setMovie(&movie);

    QHBoxLayout hBoxLayout;
    labelStatus.setText("Programming Coprocessor, \n Please wait...");
    hBoxLayout.addWidget(&labelMovie);
    hBoxLayout.addWidget(&labelStatus);

    widgetCoProcessor.setLayout(&hBoxLayout);
    widgetCoProcessor.setWindowTitle("Programming Coprocessor");
    widgetCoProcessor.setWindowFlags(Qt::Widget | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    widgetCoProcessor.setStyleSheet("background-color:black;color:white;font:bold;selection-color: white;selection-background-color: gray;");
    widgetCoProcessor.show();
    movie.start();
    gUpdateScreen(1000);

    widgetCoProcessor.move(QDesktopWidget().availableGeometry(-1).center().x() - widgetCoProcessor.frameGeometry().width()/2,
                           QDesktopWidget().availableGeometry(-1).center().y() - widgetCoProcessor.frameGeometry().height()/2);
    sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_RESET_REPROGRAM,"",3000); //reset pic32
    msleep(500);
    gUpdateScreen(100);
    if ( ! BootLoader(r_const_FILENAME.toLatin1()) )
    {
        /* program failed */
        //        QMessageBox::critical(0,"HID Bootloader Error", QString(err));
        //        labelStatus.setText("Program Aborted..!\n Device Shutting down...");
        gUpdateScreen();
        msleep(3500);
        if ( ! handShaking() ) {
            QMessageBox::critical(0,"Coprocessor Handshake", "Failed while initializing Coprocessor");
        }
        widgetCoProcessor.close();
        emit shutdown(false);
        return false;
    }
    labelStatus.setText("Program completed...\nDevice Shutting down...");
    gUpdateScreen(100);
    msleep(3500);
    gUpdateScreen(100);
    if ( ! handShaking() ) {
        QMessageBox::critical(0,"Coprocessor Handshake", "Failed while initializing Coprocessor");
    }
    widgetCoProcessor.close();
    emit shutdown(false);
    return true;
}

bool CPheripherals::handShaking()
{
    /* check the handshaking with co-processor */
    bool bResponse;
    m_bIdleMode = false;
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_HANDSHAKING, "", 3000);
    if(bResponse)
    {
        /* once get the machineid and co-processor version, date & time if sucessfully handshaking */
        sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_GET_VERSION,"",3000);
        sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_GET_MACHINE_ID,"",3000);
        enableModule(emodule_BARCODE,true);//Testing not enable when required for testing always magnetic
        if(m_strDeviceModel.contains("HHC-70"))
        {
            /* ADC shutdown & max value for HHC70xx */
            m_nADC_VALUE_SHUTDOWN = 505;
            m_nADCMaxValue = 626;
        }
        else
        {
            /* ADC shutdown & max value for HHC80xx, HHC71xx & HHC81xx models*/
            m_nADC_VALUE_SHUTDOWN = 355; //475 //520
            m_nADCMaxValue = 455; //635
        }
    }
    return bResponse;
}

bool CPheripherals::resetCoProcessor()
{
    /* reset the co-processor */
    bool bResponse;
    pauseThread();
    m_bIdleMode = false;
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_RESET_CO_PROCESSOR ,"",50); //reset pic32
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::gotoIdle()
{
    /* device is going to idle mode */
    //    qDebug()<<"\r PIC idle.....>>>";
    bool bResponse;
    pauseThread();
    m_bIdleMode = true;
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_POWER_CONTROL, QString(const_cPOWER_IDLE), 3000); //pic32 idle mode
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::wakeUpFromIdle()
{
    /* wakeup co-processor from idle mode */
    bool bResponse;
    pauseThread();
    m_bIdleMode = false;
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_POWER_CONTROL, QString(const_cPOWER_WAKEUP), 3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::gotoStandby()
{
    /* device is going to standby mode */
    bool bResponse;
    pauseThread();
    m_bIdleMode = false;
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_POWER_CONTROL, QString(const_cPOWER_STANDBY) ,3000); //Stand by
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::currentKeypadMode(E_KeypadMode &r_eKeypadMode)
{
    bool bResponse;
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_STATUS, "", 5000);      //Keypad status
    if ( m_bThreadPause ) {
        startThread();
    }
    r_eKeypadMode = gekeypadModeCurrent;
    return bResponse;
}

bool CPheripherals::capsLockStatus(bool &r_bCapsLock)
{
    bool bResponse;
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_STATUS, "", 5000);      //Keypad status
    if ( m_bThreadPause ) {
        startThread();
    }
    r_bCapsLock = m_bCapsLock;
    return bResponse;
}

bool CPheripherals::setKeypadMode(E_KeypadMode eMode)
{    
    bool bResponse = false;
    switch ((int)eMode)
    {
    case eKeypadMode_NUMERIC:
        /* set the keypad to numeric mode */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_SET_KEYPAD_MODE,"10",1000);
        break;
    case eKeypadMode_ALPHABETS:
        /* set the keypad to alphabets mode */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_SET_KEYPAD_MODE,"00",1000);
        break;
    case eKeypadMode_ALPHABETS_CAPS:
        /* set the keypad to alphabets capslock mode */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_SET_KEYPAD_MODE,"01",1000);
        break;
    }
    return bResponse;
}

bool CPheripherals::setKeypadModeLock(bool bModeLockON)
{
    bool bResponse;
    if(bModeLockON)
    {
        /* set to Lock keypad Mode */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_SET_KEYPADMODE_LOCK, "", 3000);
    }
    else
    {
        /* set to Unlock keypad Mode */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_SET_KEYPADMODE_UNLOCK, "", 3000);
    }
    return bResponse;
}

bool CPheripherals::setKeypadBeep(bool bKeypadBeepON)
{
    bool bResponse;
    pauseThread();
    if ( bKeypadBeepON ) {
        /* enable the keypad beep */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_BEEP,
                             QString(const_cKEYPAD_BEEP_ON), 3000);
    }
    else {
        /* disable the keypad beep */
        bResponse = sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_BEEP,
                             QString(const_cKEYPAD_BEEP_OFF), 3000);
    }
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::setBeep(E_BeepType eBeep)
{
    /* set the beep */
    bool bResponse;
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL, const_cPACKETID_BEEP, gConvertToString(eBeep), 3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::setBacklight(int nValue)
{
    if ( nValue < 0 || nValue > 5) {
        /* TFT screen backlight value must be 0 to 5 */
        return false;
    }
    else{
        /* set the TFT screen backlight level */
        bool bResponse;
        pauseThread();
        bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_TFT_BACKLIGHT, "T" + gAlignNumber(nValue,2),1000);//old 3000
        if ( m_bThreadPause ) {
            startThread();
        }
        return bResponse;
    }
}
bool CPheripherals::setAudioControl(int nValue)
{
    if ( nValue < 0 || nValue > 5) {
        /* Audio adjusting value must be 0 to 5 */
        return false;
    }
    else{
        /* set the Audio level */
        bool bResponse;
        pauseThread();
        bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_AUDIO_CONTROL,QString::number(nValue),3000);
        if ( m_bThreadPause ) {
            startThread();
        }
        return bResponse;
    }
}
bool CPheripherals::ChargeStatus(E_ChargeStatus &r_eChargeStatus)
{
    bool bResponse = false;
    if(gbFirsCall)
    {
        if(m_bHandshakePIC)
        {
            r_eChargeStatus = m_eChargeStatus;
            bResponse = true;
        }
        else
        {
            bResponse = false;
        }
    }
    else
    {
        int nCount = 0;
        QString strData = "";
        do {
            /* read the data after wait 50 milli seconds to check paused */
            usleep(50000);
            nCount ++;
            gLoadFromSharedPIC(strData);
            if(strData.trimmed() ==  const_strCHARGESTATUS_CONNECTED )             /**< charger connected */
            {
                r_eChargeStatus = eChargeStatus_CONNECTED;
                bResponse = true;
            }
            else if(strData.trimmed() == const_strCHARGESTATUS_REMOVED )           /**< charger removed */
            {
                r_eChargeStatus = eChargeStatus_REMOVED;
                bResponse = true;
            }
            else if(strData.trimmed() == const_strCHARGESTATUS_COMPLETED )         /**< charger completed */
            {
                r_eChargeStatus = eChargeStatus_COMPLETED;
                bResponse = true;
            }
            else if(strData.trimmed() == const_strCHARGESTATUS_INVALID)            /**< invalid charger */
            {
                r_eChargeStatus = eChargeStatus_INVALID;
                bResponse = true;
            }
            else
                bResponse = false;
        } while ( !bResponse && nCount < 50 );
    }
    return bResponse;
}

bool CPheripherals::enableSmartCardSlot(E_SmartcardSlot r_eSmartCard)
{
    bool bResponse;
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_ENABLE_DISABLE_MODULE,+"M"+QString::number(r_eSmartCard),3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::setDateTime(const QDateTime &r_const_dateTimeDT)
{
    pauseThread();
    bool bResponse;
    QString strData;
    int nYear, nMonth, nDay, nHour, nMinutes;
    nYear = r_const_dateTimeDT.date().year();
    nMonth = r_const_dateTimeDT.date().month();
    nDay = r_const_dateTimeDT.date().day();
    nHour = r_const_dateTimeDT.time().hour();
    nMinutes = r_const_dateTimeDT.time().minute();
    strData = gAlignNumber(nMinutes,2) + gAlignNumber(nHour,2) +
            gAlignNumber(nDay,2) + gAlignNumber(nMonth,2) +
            gAlignNumber(nYear,4).right(2) + gAlignNumber(r_const_dateTimeDT.date().dayOfWeek(),1);
    /* set the datetime to co-processor with given value */
    bResponse = sendData(const_cPHERIPHERAL_RTC, const_cPACKETID_SET_RTC, strData, 3000);
    if ( bResponse ) {
        /* update the date & time is os */
        system(QString("date -s \"" +
                       gConvertToString(nYear) + "-" +
                       gConvertToString(nMonth) + "-" +
                       gConvertToString(nDay) +" " +
                       gConvertToString(nHour) + ":" +
                       gConvertToString(nMinutes) + ":0\"").toLatin1());
    }
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::dateTime(QDateTime &r_dateTimeDT)
{
    pauseThread();
    bool bResponse;
    /* send request to get the date & time */
    bResponse = sendData(const_cPHERIPHERAL_RTC, const_cPACKETID_GET_RTC, "", 3000);
    if ( bResponse ) {
        r_dateTimeDT = m_dateTimeSystem;
    }
    else {
        r_dateTimeDT = QDateTime::currentDateTime();
    }
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::readMageneticCard(const E_MagneticCard &r_eMagneticCard, QString &r_strMCTrackInfo, unsigned int unTimeout_Sec)
{
    /* Read magnetic card */
    bool bResponse;
    m_strMCRData = "";
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_MAGNETICCARD_READER, const_cPACKETID_READ_MAGNETICCARD, gConvertToString(r_eMagneticCard), (unTimeout_Sec * 1000));
    if ( bResponse ) {
        r_strMCTrackInfo = m_strMCRData;
        switch (r_eMagneticCard)
        {
        case eMagneticCard_Read_ALL:
            if((m_strMCRData.split("?").size() - 1) != 3)
            {  /* in above condition -1 is used to remove last unwanted string */
                bResponse = false;
            }
            break;
        default:
            if((m_strMCRData.split("?").size() - 1) != 1)
            {
                bResponse = false;
            }
            break;
        }
    }
    m_strMCRData.clear();

    if(!bResponse)
    {
        sendData(const_cPHERIPHERAL_MAGNETICCARD_READER, const_cPACKETID_READ_TERMINATE_MC, "", 600);
        r_strMCTrackInfo = "";
    }
    
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::enableModule(CPheripherals::E_Module eModule,bool bState,bool bEnable_or_Statuscheck)
{
    gLoadIntoSharedPIC(const_strSTARTED);
    bool bResponse;
    QChar cModule;

    switch ( (int) eModule ) {
    case emodule_GPRS :
        cModule = 'G';
        break;
    case emodule_GPS :
        cModule = 'P';
        break;
    case emodule_AUDIO :
        cModule = 'L';
        break;
    case emodule_FlashLight:
        cModule = 'C';
        break;
    case emodule_RFID:
        cModule = 'R';
        break;
    case emodule_SAM:
        cModule = 'S';
        break;
    case emodule_BARCODE:
        cModule = 'B';
        break;
    case emodule_PRINTER:
        cModule = 'X';
        break;
    case emodule_KEYPAD:
        cModule = 'K';
        break;
    case emodule_SMARTCARD:
        cModule = 'M';
        break;
    case emodule_Hub:
        cModule = 'H';
        break;
    case emodule_WIFI:
        cModule = 'W';
        break;
    case emodule_BLUETOOTH:
        cModule = 'T';
        break;
    case emodule_EXTERNALUSB:
        cModule = 'U';
        break;
    default:
        cModule = 'A';
    }
    if(!bEnable_or_Statuscheck)
    {
        if ( bState ) {
            /* enable the given module */
            bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_ENABLE_DISABLE_MODULE, QString(cModule) + "1" ,3000);
        }
        else {
            /* disable the given module */
            bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_ENABLE_DISABLE_MODULE, QString(cModule) + "0" ,3000);
        }
        gLoadIntoSharedPIC(const_strCOMPLETED);
    }
    else
    {
        bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL,const_cPACKETID_ENABLE_DISABLE_MODULE, QString(cModule) + "S" ,1000);
        gLoadIntoSharedPIC(const_strCOMPLETED);
    }
    return bResponse;
}

bool CPheripherals::loadHeaderImage(const QImage &r_const_imageHEADER)
{
    /* load the header image for printing */
    bool bResponse;
    pauseThread();
    bResponse = loadImage(r_const_imageHEADER,const_cPACKETID_LOAD_HEADER_IMAGE,50,384);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::loadFooterImage(const QImage &r_const_imageFOOTER)
{
    /* load the footer image for printing */
    bool bResponse;
    pauseThread();
    bResponse = loadImage(r_const_imageFOOTER,const_cPACKETID_LOAD_FOOTER_IMAGE,50,384);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::printData(const QList<QString> &listDatas, const QList<QImage> &listImages)
{
    //    if ( gbFirsCall ) {
    //        /* check the battery percentage if only one application using library */
    //        if ( ! m_bBatteryCharging )
    //        {
    //            if ( m_nPrevBatt < 15 )
    //            {
    //                if(gbEnableMessageBoxPrinter)
    //                    QMessageBox::critical(0,"Printer","Battery has less than 15 % \n So,You Cannot Print.");
    //                return false;
    //            }
    //        }
    //    }
    // before pinting start pause PIC thread 5/7/13 uma
    pauseThread();

    bool bResponse = false;
    bool bRePrint, bPrevNatLang;
    m_bPrinterReady = true;
    m_bDoorClosed = true;
    m_bPaperAvailable = true;
    bPrevNatLang = false;
    do {
        bRePrint = false;
        QString strData;
        QString strPrintData = "";
        int nImageIndex = 0, nCurrentIndex = 0;
        foreach ( strData, listDatas )
        {
            /* read data one by one from list */
            bResponse = false;
            if(strData.length() > 0)
            {
                if ( strData == "image" )       //Check if print data has image to be printed
                {
                    if ( strPrintData != "" )
                    {
                        /* print existing data if available in print buffer before printing image */
                        bResponse = sendPrintData(strPrintData, bPrevNatLang);
                        if(bResponse)
                        {
                            strPrintData = "";
                        }
                        else
                        {
                            /* Break printing process if error */
                            break;
                        }
                    }
                    if ( ! imagePrinting(listImages.at(nImageIndex)) )
                    {
                        /* Break printing process if error */
                        break;
                    }
                    nImageIndex ++;
                }

                if ((strData.at(strData.length() - 1) != const_cEND_BYTE) && (strData != const_StringEndOfPrint) )
                {
                    /* To achieve printing speed, we send the multiple lines of data to co-up */
                    if(strData.mid(strData.length() - 2).simplified() == const_StringNativeData_EOP)        //Condition to check print data contains native data EOP
                    {
                        /* If print data contains Native language */
                        strData = strData.left(strData.length() - 2);
                        if((!bPrevNatLang) && (strPrintData != ""))
                        {
                            /* If existing print data in buffer is non native, then print immediately */
                            bResponse = sendPrintData(strPrintData, bPrevNatLang);
                            if(bResponse)
                            {
                                /* Clear buffer to append data to be printed next */
                                strPrintData = "";
                                strPrintData += strData + "~";
                            }
                            else
                            {
                                /* Break printing process if error */
                                break;
                            }
                        }
                        else
                        {
                            /* To append data to be printed */
                            strPrintData += strData + "~";
                        }
                        bPrevNatLang = true;
                    }
                    else
                    {
                        /* If print data contains Non-Native language */
                        if((bPrevNatLang) && (strPrintData != ""))
                        {
                            /* If existing print data in buffer is native, then print immediately */
                            bResponse = sendPrintData(strPrintData, bPrevNatLang);
                            if(bResponse)
                            {
                                /* Clear buffer to append data to be printed next */
                                strPrintData = "";
                                strPrintData += strData + "~";
                            }
                            else
                            {
                                /* Break printing process if error */
                                break;
                            }
                        }
                        else
                        {
                            /* To append data to be printed into the buffer*/
                            strPrintData += strData + "~";
                        }
                        bPrevNatLang = false;
                    }
                }
                if ( strData.at(strData.length() - 1) == const_cEND_BYTE )
                {
                    /* the data has an end of byte */
                    if ( strPrintData != "" )
                    {
                        /* format & send combined data if available */
                        bResponse = sendPrintData(strPrintData, bPrevNatLang);
                        if(bResponse)
                        {
                            strPrintData = "";
                        }
                        else
                        {
                            /*Break foreach loop, if print failed */
                            break;
                        }
                    }
                    /* send the formatted data other native & Non-Native like header,
                        footer, drawline and Barcode */
                    bResponse = sendData(strData,3000);
                    if ( ! bResponse )
                    {
                        /* send last print response packet , to get last print packet's response -- the below logic implemented to fix success packet loss in 71xx*/
                        if(!m_bNegativeAck)         // Skip the below process if negative ack received
                        {
                            /* Get last print response packet */
                            bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_LAST_PRINT_RESPONSE, "", 2000);
                        }

                        if ( !bResponse)
                        {
                            if(gbEnableMessageBoxPrinter)
                                QMessageBox::critical(0, "Printer", "Error while printing data..");
                            /*Break foreach loop, if print failed */
                            break;
                        }
                    }
                }
                else if ( strPrintData.length() >= 950 || ( (strData == const_StringEndOfPrint) && (strPrintData != "") ) )
                {
                    /* Print packet should't be exceed 1000 bytes , So print immediately */
                    bResponse = sendPrintData(strPrintData, bPrevNatLang);
                    if(bResponse)
                    {
                        strPrintData = "";
                    }
                    else
                    {
                        /*Break foreach loop, if print failed */
                        break;
                    }
                }
                if ( bResponse )
                {
                    /* if successfull response may be printing completed or paper not available */
                    if ( ! m_bPrinterReady)
                    {
                        if(gbEnableMessageBoxPrinter)
                            QMessageBox::critical(0, "Printer", "Printer not connected..!");
                        bResponse = false;
                        break;
                    }
                    else if ( ( ! m_bDoorClosed ) || ( ! m_bPaperAvailable ) )
                    {
                        /* paper not available show the printer status dialog */
                        if(gbEnableMessageBoxPrinter)
                            bRePrint = waitForPrinting();
                        bResponse = false;
                        break;
                    }
                }
                strData.clear();
            }
            nCurrentIndex++;
        }
        strPrintData.clear();
        /* check for reprinting */
    } while ( bRePrint );

    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::sendPrintData(const QString &r_const_strPrintData, const bool &r_const_bNativeLanguage)
{
    bool bResponse;

    if( r_const_bNativeLanguage)
    {
        bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_LANGUAGE, r_const_strPrintData, 5000);
    }
    else
    {
        bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_DATA, r_const_strPrintData, 5000);
    }
    if ( ! bResponse ) {
        /* send last print response packet , to get last print packet's response -- the below logic implemented to fix success packet loss in 71xx*/
        if(!m_bNegativeAck)         // Skip the below process if negative ack received
        {
            /* Get last print response packet */
            bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_LAST_PRINT_RESPONSE, "", 2000);
        }
        if ( ! bResponse)
        {
            if(gbEnableMessageBoxPrinter)
                QMessageBox::critical(0, "Printer", "Error while printing data..");
            return false;
        }
    }
    return bResponse;
}

bool CPheripherals::imagePrinting(const QImage &r_const_imagePRINT)
{    
    bool bResponse = false ;
    pauseThread();
    /* covert image to mono & dithering */
    QImage imageMono;
    QByteArray strImageData;
    strImageData = "";
    int Maxwidth = 384;
    if ( r_const_imagePRINT.width() > Maxwidth ) {
        imageMono = r_const_imagePRINT.copy(0,0,Maxwidth,r_const_imagePRINT.height());
    }
    else {
        imageMono = r_const_imagePRINT;
    }
    int nWidth = imageMono.width() / 8;
    int nRemainingBytes = imageMono.width() % 8;
    if (  nRemainingBytes != 0 ) {
        nWidth ++;
    }
    int MaxHeight = 9240 / nWidth ;
    if ( imageMono.height() > MaxHeight ) {
        imageMono = imageMono.copy(0,0,imageMono.width(),MaxHeight);
    }
    QString strReformatted;
    int nPosition = 0;
#if 0 // code removed
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    imageMono.save(&buffer, "BMP");

    QByteArray byteArrayHex = byteArray.toHex();
    byteArray.clear();
    buffer.close();
    // save o a file

    nPosition = byteArrayHex.size();

    /* while loop to reformat the converted hexadecimal image data into the proper alignment,
       while converting image data to hex values, it converts from last line, for ex, 240 x 320
       file, it starts convertion from 320 th line to 1st line
    */
    while ( nPosition > 124 ) {
        /*In each line of hex converted data 2 byte hex values inserted extra to remove that
          we are skipping that 2 byte while reformatting*/
        nPosition -= ( nWidth * 2 ) ;
        strReformatted += byteArrayHex.mid(nPosition, ( nWidth * 2 )).toUpper() ;
    }
#else
    strReformatted= "";
    QString strBinary="";

    /* convert QImage formatted image file into hex data's */
    for ( int nRow = 0; nRow < imageMono.height(); nRow ++ ) {
        QString strData="";
        for (int nCol = 0; nCol < imageMono.width(); nCol ++ ) {
            /* identify current pixel value is high or low */
            int nRed = qRed(imageMono.pixel(nCol,nRow));
            if ( nRed == 0 ) {
                strBinary += "1";
            }
            else {
                strBinary += "0";
            }
            if ( strBinary.length() == 8 ) {
                /* convert 8 bit result binary data(in ascii format) into hex data */
                strData += QString::number(strBinary.toInt(0,2),16).rightJustified(2,'0',true).toUpper();
                strBinary = "";
            }
        }
        if ( strBinary.length() > 0 ) {
            /* fill the remaining bits with 0 value  (for ex, we might get 4 bits finally. so we will fill the remaining bits with 0's */
            strBinary=strBinary.leftJustified(8,'0',true);
            strData += QString::number(strBinary.toInt(0,2),16).rightJustified(2,'0',true).toUpper();
            strBinary = "";
        }
        strReformatted += strData;
    }
#endif
    QByteArray bytearrayImage;
    bytearrayImage.append(strReformatted);
    bytearrayImage = QByteArray::fromHex(bytearrayImage);
    nPosition = 0;

    int nMaxCount = bytearrayImage.length() / 2640;
    if ( ( bytearrayImage.length() % 2640 ) != 0 ) {
        nMaxCount ++;
    }

    /* divide & send images as packet of size 2640 bytes each */
    for ( int nCount = 0; nCount < nMaxCount; nCount ++ )
    {
        strImageData = bytearrayImage.mid(nPosition,2640);
        //        qDebug()<<"\rstrImagedata"<<strImageData.size();
        bResponse = sendImage(const_cPHERIPHERAL_PRINTER, const_cPACKETID_LOAD_IMAGE_DATA ,strImageData,6000);
        if ( ! bResponse ) {
            if(!m_bNegativeAck)         // Skip the below process if negative ack received
            {
                /* Get last print response packet */
                bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_LAST_PRINT_RESPONSE, "", 2000);

            }
            else
            {
                if(gbEnableMessageBoxPrinter)
                    QMessageBox::critical(0, "Printer", "Error while printing image..");
                break;
            }
            break;
        }
        nPosition += 2640;
    }
    if ( bResponse ) {
        m_bPrinterReady = true;
        m_bDoorClosed = true;
        m_bPaperAvailable = true;
        bool bRePrint;
        do {
            /* reprint the image again if paper not available */
            bRePrint = false;
            if(gstrImageBrightness=="L")
            {
                bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_IMAGE, QString(const_cPRINT_PHOTO)+"L" + gAlignNumber(nWidth, 2) , 5000);
            }
            else
            {
                bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_IMAGE, QString(const_cPRINT_PHOTO)+"H" + gAlignNumber(nWidth, 2) , 5000);
            }
//            gstrImageBrightness="";
            gstrImageBrightness.clear();
            if ( bResponse ) {
                if ( ! m_bPrinterReady )
                {
                    if(gbEnableMessageBoxPrinter)
                        QMessageBox::critical(0, "Printer", "Printer not connected..!");
                    bResponse = false;
                }
                else if ( ( ! m_bDoorClosed )  || ( ! m_bPaperAvailable ) )
                {
                    if(gbEnableMessageBoxPrinter)
                        bRePrint = waitForPrinting();
                    bResponse = false;
                }
            }
            else {
                //alter by maheswari
                /* send last print response packet , to get last print packet's response -- the below logic implemented to fix success packet loss in 71xx*/
                if(!m_bNegativeAck)         // Skip the below process if negative ack received
                {
                    /* Get last print response packet */
                    bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_LAST_PRINT_RESPONSE, "", 2000);
                }
                else
                {
                    if(gbEnableMessageBoxPrinter)
                        QMessageBox::critical(0, "Printer", "Failed while printing image..");
                    break;
                }
                if ( !bResponse )
                {
                    if(gbEnableMessageBoxPrinter)
                        QMessageBox::critical(0, "Printer", "Failed while printing data..");
                    /*Break foreach loop, if print failed */
                    break;
                }
            }
        } while ( bRePrint );
    }
    else if(gbEnableMessageBoxPrinter)
    {
        QMessageBox::critical(0, "Printer", "Failed while sending image data..");
    }
    strReformatted.clear();
    strImageData.clear();
    if ( m_bThreadPause )
        startThread();
    return bResponse;
}

bool CPheripherals::getPowerLog(QString &r_strData)
{
    /* read the power log from co-processor */
    bool bResponse = false;
    pauseThread();
    msleep(200);
    r_strData = "";
    m_strLogData = "";
    glabelStatus->setText("Downloading Power Log.....");
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_LOG,
                         QString(const_cGET_POWER_LOG), 500);
    if(bResponse)
    {
        bResponse = getLog(r_strData);
    }
    if ( m_bThreadPause )
        startThread();
    return bResponse;
}

bool CPheripherals::getProcessLog(QString &r_strData)
{
    /* read the process log from co-processor */
    bool bResponse = false;
    pauseThread();
    msleep(200);
    r_strData = "";
    m_strLogData = "";
    glabelStatus->setText("Downloading Proces Log.....");
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_LOG,
                         QString(const_cGET_PROCESS_LOG), 500);
    if(bResponse)
    {
        bResponse = getLog(r_strData);
    }
    if ( m_bThreadPause )
        startThread();
    return bResponse;
}

bool CPheripherals::getLog(QString &r_strData)
{
    /* read the power/process log from co-processor
       log data retrieval fininshed if the received data packet contains
       (^MS) success packet (or) if we didn't get the data for 3 times
    */
    r_strData = "";
    int nCount = 0;
    glabelStatus->show();
    gUpdateScreen();
    /* copy the retrieved data */
    r_strData += m_strLogData;
    /* To remove the acknowledgement packet */
    if(r_strData.contains(const_cSTART_BYTE))
    {
        r_strData = r_strData.mid(6 + const_nSIZE_OF_NO_OF_BYTES);
    }
    do {
        m_strLogData.clear();
        msleep(100);
        arrivedData();
        /* check the log data is receiving */
        if( m_strLogData == "")
        {
            nCount++;
        }
        else
        {
            /* copy the received data */
            r_strData += m_strLogData;
        }
    } while ((nCount < 3) && (!m_strLogData.contains("^MS")));

    /*  To remove the success packet from the end of packet */
    if(r_strData.contains("^MS"))
    {
        r_strData = r_strData.mid(0, r_strData.indexOf("^MS"));
    }
    glabelStatus->close();
    gUpdateScreen();
    return true;
}

bool CPheripherals::bootPassword(QString &r_strPsw)
{
    /* read the boot password which is stored in the co-processor */
    bool bResponse;
    m_strRootPassword = "";
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_BOOT_PSW,
                         QString(const_cGET_BOOT_PSW), 3000);
    if ( bResponse ) {
        r_strPsw = m_strRootPassword;
    }
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::setBootPassword(const QString &r_const_strPSW)
{
    /* set the boot password to store in the co-processor */
    bool bResponse;
    pauseThread();
    bResponse = sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_BOOT_PSW,
                         QString(const_cSTORE_BOOT_PSW) + r_const_strPSW.leftJustified(8,' ', true), 3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

QString CPheripherals::formPacket(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA)
{
    /* form the packet for send data to co-processor */
    QString strData;
    /* protocol format
       StartByte        = 1 byte
       Pheripheral Id   = 1 byte
       Packet Id        = 1 byte
       Data             = ...(variable lenght)
       Checksum         = 2 bytes
       Endbyte          = 1 byte
    */
    int nTotalBytes = 6 + const_nSIZE_OF_NO_OF_BYTES + r_const_strDATA.length();
    strData = const_cSTART_BYTE + cPheripheralId + cPacketId +
            gAlignNumber(nTotalBytes,const_nSIZE_OF_NO_OF_BYTES) + r_const_strDATA;
    return (strData + checkSum(strData) + const_cEND_BYTE);
}

QString CPheripherals::checkSum(const QString &r_const_strDATA)
{
    /* calculate the checksum value for given data */
    int Checksum = 0;
    for ( int nIndex = 0; nIndex < r_const_strDATA.length(); nIndex ++ ) {
        /* add the current character ascii value */
        Checksum += r_const_strDATA[nIndex].toAscii();
    }
    /* return 2 bytes of right side */
    return QString::number(Checksum, 16).toUpper().right(2);

}

QString CPheripherals::ImagecheckSum(const QString &r_const_strHDRDATA, const QByteArray &r_const_strIMGDATA)
{
    /* calculate the checksum value for given data */
    int Checksum = 0;

    /* calculate the checksum value for r_const_strHDRDATA */
    for ( int nIndex = 0; nIndex < r_const_strHDRDATA.length(); nIndex ++ ) {
        /* add the current character ascii value */
        Checksum += r_const_strHDRDATA[nIndex].toAscii();
    }

    /* calculate the checksum value for r_const_strIMGDATA */
    for ( int nIndex = 0; nIndex < r_const_strIMGDATA.length(); nIndex ++ ) {
        /* add the current character ascii value */
        Checksum += (int)r_const_strIMGDATA.at(nIndex);
    }
    /* return 2 bytes of right side */
    return QString::number(Checksum, 16).toUpper().right(2);
}

// continuous sending function and receiving function
void CPheripherals::run()
{        
    /* send battery status command once for 3 keypad status command
       ---because we need to update keypad status in display immediately, if it is changed*/
    int nBatteryCount = 3;
    if(!m_bHandshakePIC)
    {
        m_bHandshakePIC = handShaking();
    }
    else
    {
        //if handshake true do nothing
    }
    while ( m_bThreadRunning )
    {
        if ( m_bIdleMode )
        {
            /* In idle mode, read data to get the wakeup intimation from co-processor when POWER_ON key pressed*/
            m_strPreviousData = "";
            msleep(300);
            arrivedData();
        }
        else {
            QString strSharedMemory;
            /* read the data from shared memory */
            gLoadFromSharedPIC(strSharedMemory);
            if ( const_strRUNNING == strSharedMemory || const_strIDLESTATUS == strSharedMemory )
            {
                /* send the data if shared memory has Running or IdleStatus */
                if ( nBatteryCount == 3 ) {
                    /* send data to get battery status */
                    nBatteryCount = 0;
                    sendData(const_cPHERIPHERAL_IO_CONTROL, const_cPACKETID_SUPPLY_STATUS, "B", 2000);
                }
                else
                {
                    /* send data to get the keypad mode */
                    nBatteryCount ++;
                    sendData(const_cPHERIPHERAL_HID, const_cPACKETID_KEYPAD_STATUS, "", 1000);
                }
                int nSleepcount = 0;
                bool bSharedMemDataChanged = false;
                do
                {
                    gLoadFromSharedPIC(strSharedMemory);
                    if ( (const_strKEYPAD_NUMERIC == strSharedMemory) || (const_strKEYPAD_ALPHABETS == strSharedMemory) || (const_strKEYPAD_ALPHABETS_CAPS == strSharedMemory) ) {
                        /* set the keypad mode numeric */
                        if(const_strKEYPAD_NUMERIC == strSharedMemory)
                        {
                            setKeypadMode(eKeypadMode_NUMERIC);
                        }
                        else if(const_strKEYPAD_ALPHABETS == strSharedMemory)
                        {
                            setKeypadMode(eKeypadMode_ALPHABETS);
                        }
                        else
                        {
                            setKeypadMode(eKeypadMode_ALPHABETS_CAPS);
                        }
                        gLoadIntoSharedPIC(const_strRUNNING);
                        continue;
                    }
                    else if(const_strRUNNING == strSharedMemory || const_strIDLESTATUS == strSharedMemory)
                    {
                        nSleepcount++;
                        msleep(100);
                    }
                    else
                    {
                        bSharedMemDataChanged = true;
                    }
                }while((nSleepcount < 2) && (!bSharedMemDataChanged));
            }
            else if ( const_strSTARTED == strSharedMemory )
            {
                /* before sending data from second application, stop sending data in thread */
                arrivedData();
                gLoadIntoSharedPIC(const_strPAUSED);
                gbProcessRunning = true;
            }
            else if ( const_strCOMPLETED == strSharedMemory )
            {
                /* after sending data from second application, start sending data in thread */
                gLoadIntoSharedPIC(const_strRUNNING);
                emit resetTimer();
                gbProcessRunning = false;
            }
            else if ( const_strPAUSE_THREADS == strSharedMemory )
            {
                /* pause the all threads for do some work like signature capture,calibration,..,etc*/
                gLoadIntoSharedPIC(const_strWAIT);
                gbProcessRunning = true;
                gnetworkActive->pauseThread();
                if(gstrCheckGPRSConfiguration.toLower() == "yes")
                {
                    ggsmModuleSimCom->pauseThread();
                }
            }
            else if ( const_strWAKEUP_THREADS == strSharedMemory )
            {
                /* wakeup all threads after do some work */
                gLoadIntoSharedPIC(const_strRUNNING);
                emit resetTimer();
                gbProcessRunning = false;
                gnetworkActive->startThread();
                if(gstrCheckGPRSConfiguration.toLower() == "yes")
                {
                    ggsmModuleSimCom->startThread();
                }
            }
            else if ( const_strPAUSETIMER == strSharedMemory )
            {
                /* it won't allow to goto idle mode or standby mode */
                gLoadIntoSharedPIC(const_strIDLESTATUS);
                gbIdleStatus = true;
            }
            else if ( const_strRESUMETIMER == strSharedMemory )
            {
                /* resume timer to allow time out to goto idle or standby mode */
                gLoadIntoSharedPIC(const_strIDLESTATUS);
                emit resetTimer();
                gbIdleStatus = false;
            }
            else if ( (const_strKEYPAD_NUMERIC == strSharedMemory) || (const_strKEYPAD_ALPHABETS == strSharedMemory) || (const_strKEYPAD_ALPHABETS_CAPS == strSharedMemory) )
            {
                /* set the keypad mode numeric */
                if(const_strKEYPAD_NUMERIC == strSharedMemory)
                    setKeypadMode(eKeypadMode_NUMERIC);
                else if(const_strKEYPAD_ALPHABETS == strSharedMemory)
                    setKeypadMode(eKeypadMode_ALPHABETS);
                else
                    setKeypadMode(eKeypadMode_ALPHABETS_CAPS);
                gLoadIntoSharedPIC(const_strRUNNING);
            }
            else if ( const_strSHOW_DESKTOP == strSharedMemory )
            {
                /* intimate the first applicaion to show the desktop if second application call */
                gLoadIntoSharedPIC(const_strRUNNING);
                emit showDesktop();
            }
            else if ( const_strCHARGESTATUS == strSharedMemory ) {
                gbProcessRunning = true;
                if(m_eChargeStatus == eChargeStatus_CONNECTED )              /**< charger connected */
                    gLoadIntoSharedPIC(const_strCHARGESTATUS_CONNECTED);
                else if(m_eChargeStatus == eChargeStatus_REMOVED )           /**< charger removed */
                    gLoadIntoSharedPIC(const_strCHARGESTATUS_REMOVED);
                else if(m_eChargeStatus == eChargeStatus_COMPLETED )         /**< charger completed */
                    gLoadIntoSharedPIC(const_strCHARGESTATUS_COMPLETED);
                else if(m_eChargeStatus == eChargeStatus_INVALID )           /**< invalid charger */
                    gLoadIntoSharedPIC(const_strCHARGESTATUS_INVALID);
            }
            else if( const_strCHARGESTATUS_CLOSE == strSharedMemory ) {
                /* after sending data from second application, start sending data in thread */
                gLoadIntoSharedPIC(const_strRUNNING);
                emit resetTimer();
                gbProcessRunning = false;
            }
            else {
                msleep(150);
            }
        }
    }
}

void CPheripherals::startThread()
{
    if ( ! isRunning() && gbFirsCall) {
        /* start the thread */
        m_bThreadRunning = true;
        emit resetTimer();
        gbProcessRunning = false;
        m_nCount = 0;
        m_nADCTotal = 0;
#ifdef Q_WS_QWS
        start();
#endif
    }
}

void CPheripherals::pauseThread()
{
    if ( m_bThreadRunning && isRunning() ) {
        /* pause the thread */
        m_bThreadRunning = false;
        m_bThreadPause = true;
        gbProcessRunning = true;
        wait();
    }
}

void CPheripherals::stopThread()
{    
    if ( isRunning() ) {
        /* stop the thread */
        m_bThreadRunning = false;
        m_bThreadPause = false;
        wait();
        terminate();
        msleep(50);
    }
}

bool CPheripherals::sendData(QChar cPheripheralId, QChar cPacketId, const QString &r_const_strDATA, long nWait)
{
    return sendData(formPacket(cPheripheralId, cPacketId, r_const_strDATA), nWait);
}

bool CPheripherals::sendImage(QChar cPheripheralId, QChar cPacketId, const QByteArray &bytearrayImage, long nWait)
{
    m_mutex.lock();
    /* form the packet for send data to co-processor */
    QString strSOBHeader, strEOBChksum;
    QByteArray bytearrayPrintData;
    /* protocol format
       StartByte        = 1 byte
       Pheripheral Id   = 1 byte
       Packet Id        = 1 byte
       Data             = ...(variable lenght)
       Checksum         = 2 bytes
       Endbyte          = 1 byte
    */

    int nTotalBytes = 6 + const_nSIZE_OF_NO_OF_BYTES + bytearrayImage.length();
    strSOBHeader = const_cSTART_BYTE + cPheripheralId + cPacketId +
            gAlignNumber(nTotalBytes,const_nSIZE_OF_NO_OF_BYTES);
    strEOBChksum = ImagecheckSum(strSOBHeader, bytearrayImage) + const_cEND_BYTE;
    int nErrorcount;
    nErrorcount = 1;
    do {
        /* check the port is opened */
        if ( ! m_serialportCoProcessor->isOpen() ) {
            m_mutex.unlock();
            return false;
        }
        /* read the data if already exist */
        arrivedData();
        m_bResponse = false;
        m_bNegativeAck = false;
        m_strPreviousData = "";
        /* write the data to co-processor */

        bytearrayPrintData.append( strSOBHeader.toAscii());
        bytearrayPrintData.append(bytearrayImage);
        bytearrayPrintData.append( strEOBChksum.toAscii());
        m_serialportCoProcessor->writeData(bytearrayPrintData.data(), bytearrayPrintData.length());
//        qDebug()<<"\r"<<"\n Image transmitted:" + bytearrayPrintData;
        //        DEBUGMESSAGE("transmitted:" + strData);
        int nMaxCount = nWait / const_nWAIT_FOR_RESPONSE;
        /* wait n milli seconds for an acknowlegment after sending the data. */
        for ( int nCount = 0; nCount < nMaxCount; nCount ++ )
        {
            /* break the loop if succesfull response */
            if ( m_bResponse )
                break;
            else
            {
                /* read the data after waiting for 100 milli seconds for response from co-processor */
                msleep(const_nWAIT_FOR_RESPONSE);
                arrivedData();
            }
        }
        nErrorcount ++;
        /* try with 3 times for negative acknowledgment */
    } while ( ( nErrorcount > 0 && nErrorcount < 3 ) && m_bNegativeAck );
    m_strPreviousData = "";
    m_mutex.unlock();
    return m_bResponse;
}

bool CPheripherals::sendData(const QString &r_const_strDATA, long nWait)
{
    /* QMutex lock is to protect the section of code so that only one thread
       can access it at a time. successor call will wait until mutex unlocked. */
    m_mutex.lock();
    int nErrorcount = 0;
    do
    {
        /* check the port is opened */
        if ( ! m_serialportCoProcessor->isOpen() )
        {
            m_mutex.unlock();
            return false;
        }
        /* read the data if already exist */
        arrivedData();
        m_bResponse = false;
        m_bNegativeAck = false;
        m_strPreviousData = "";
        /* write the data to co-processor */

        // if print packet is not repeted to PIC //17/09/2012 uma
        if(((r_const_strDATA.contains("^PB") || (r_const_strDATA.contains("^PF")) || (r_const_strDATA.contains("^PL"))) && nErrorcount > 0))
        {
        }
        else
        {
            m_serialportCoProcessor->writeData(r_const_strDATA.toAscii(),r_const_strDATA.length());
        }
        DEBUGMESSAGE("transmitted:" + r_const_strDATA);
//        qDebug()<<"\r\n  transmitted:" + r_const_strDATA;
        int nMaxCount = nWait / const_nWAIT_FOR_RESPONSE;
        /* wait n milli seconds for an acknowlegment after sending the data. */
        for ( int nCount = 0; nCount < nMaxCount; nCount ++ )
        {
            if ( m_bResponse ) {
                /* break the loop if succesfull response */
                break;
            }
            else {
                /* read the data after waiting for 100 milli seconds for response from co-processor */
                msleep(const_nWAIT_FOR_RESPONSE);
                msleep(const_nWAIT_FOR_RESPONSE);
                arrivedData();
                if(m_bNegativeAck)
                {
                    break;
                }
            }
        }
        if(m_bResponse)
        {
            nErrorcount = 0;
        }
        else
        {
            nErrorcount ++;
        }
        /* try with 3 times for negative acknowledgment */
    } while ( ( nErrorcount > 0 && nErrorcount < 3 ) && (m_bNegativeAck ));
    m_strPreviousData = "";
    m_mutex.unlock();
    return m_bResponse;
}

bool CPheripherals::testPrinter()
{
    //    if ( gbFirsCall ) {
    //        /* check the battery percentage if only one application using library */
    //        if ( ! m_bBatteryCharging ) {
    //            if ( m_nPrevBatt < 15 )
    //            {
    //                if(gbEnableMessageBoxPrinter)
    //                    QMessageBox::critical(0,"Printer","Battery has less than 15 % \n So,You Cannot Print.");
    //                return false;
    //            }
    //        }
    //    }
    bool bRePrint;
    bool bResponse = false;
    pauseThread();
    m_bPrinterReady = true;
    m_bDoorClosed = true;
    m_bPaperAvailable = true;
    do {
        bRePrint = false;
        /* send test print data */
        bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_TEST_PRINT, "", 2000);
        if ( ! bResponse && gbEnableMessageBoxPrinter) {
            QMessageBox::critical(0, "Printer", "Error while printing image..");
        }
        else if ( ! m_bPrinterReady )
        {
            if(gbEnableMessageBoxPrinter)
                QMessageBox::critical(0, "Printer", "Printer not connected..!");
            bResponse = false;
        }
        else if ( ( ! m_bDoorClosed )  || ( ! m_bPaperAvailable ) )
        {
            /* paper not available show the printer status dialog */
            if(gbEnableMessageBoxPrinter)
                bRePrint = waitForPrinting();
            bResponse = false;
        }
        /* check for reprinting */
    } while ( bRePrint );
    if ( m_bThreadPause )
    {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::batteryvoltage(float &r_value)
{
    bool bResponse;
    int nbattcount = 0, nbatvalue=0;
    //    float ADCResolution=0.013256718;//Old value alter by Boopathi
    float ADCResolution=0.01839;//Alter by mahesh on Oct 15 2013
    pauseThread();
    while(nbattcount <= 4)
    {
        bResponse = sendData(const_cPHERIPHERAL_IO_CONTROL, const_cPACKETID_SUPPLY_STATUS, "B", 5000);
        if(bResponse)
        {
            nbatvalue+=nADCValue;
            nbattcount++;
        }
    }
    r_value = ((nbatvalue)/5 * ADCResolution);
    startThread();
}

bool CPheripherals::checkPrinterStatus()
{
    /* check the printer paper status */
    pauseThread();
    bool bResponse = false;
    m_bPrinterReady = false;
    m_bDoorClosed = false;
    m_bPaperAvailable = false;
    bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_STATUS,"",3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::checkPaperStatus(bool &r_bPaperAvailable)
{
    /* check the printer paper status */
    pauseThread();
    bool bResponse = false;
    m_bPrinterReady = false;
    m_bDoorClosed = false;
    m_bPaperAvailable = false;
    bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_STATUS,"",3000);
    r_bPaperAvailable = m_bPaperAvailable;
    if ( m_bThreadPause ) {
        startThread();
    }
    return bResponse;
}

bool CPheripherals::loadImage(const QImage &r_const_imageLOAD, QChar cPacketId, int nMaxHeight, int nMaxWidth)
{
    bool bResponse;
    int nRed, nRow, nCol, nMaxDataWidth;
    QString strBinary,Data,strImageData;
    QChar cPrintPacketType;
    /* convert image into mono*/
    QImage imageMono = r_const_imageLOAD.convertToFormat(QImage::Format_Mono);
    int nMaxLine = 10; /* send max line of data */
    nMaxDataWidth = nMaxWidth / 4;
    Data = "";
    int n = ( nMaxWidth - imageMono.width() ) / 8;
    if ( (n % 2) != 0 ) n --;
    for ( nRow = 0; nRow < nMaxHeight; nRow ++ ) {
        if ( nRow == ( imageMono.height() - 1 ) ) {
            break;
        }
        strBinary = "";
        Data = "";
        if ( imageMono.width() < nMaxWidth ) {
            Data = Data.leftJustified(n,'0');
        }
        for ( nCol = 0; nCol < nMaxWidth; nCol ++ ) {
            if ( nCol == ( imageMono.width() - 1 ) ) {
                break;
            }
            nRed = qRed(imageMono.pixel(nCol,nRow));
            if ( nRed == 0 ) {
                strBinary += "1";
            }
            else {
                strBinary += "0";
            }
            if ( strBinary.length() == 8 ) {
                /* convert 8 bit binary data to decimal */
                Data += QString::number(strBinary.toInt(0,2),16).rightJustified(2,'0',true).toUpper();
                strBinary = "";
            }
        }
        if ( strBinary.length() > 0 ) {
            strBinary=strBinary.leftJustified(8,'0',true);
            Data += QString::number(strBinary.toInt(0,2),16).rightJustified(2,'0',true).toUpper();
            strBinary = "";
        }
        Data = Data.leftJustified(nMaxDataWidth,'0',true);
        strImageData += Data;
        if ( ( ( nRow + 1) % nMaxLine ) == 0 ) {
            if ( nRow == ( nMaxLine - 1) ) {
                cPrintPacketType = 's';
            }
            else if ( nRow == ( nMaxHeight - 1 ) ) {
                cPrintPacketType = 'e';
            }
            else {
                cPrintPacketType = 'c';
            }
            bResponse = sendData(const_cPHERIPHERAL_PRINTER, cPacketId, cPrintPacketType + strImageData,3000);
            strImageData="";
            if ( ! bResponse ) {
                return false;
            }
        }
    }
    for ( int nCount = nRow; nCount < nMaxHeight; nCount ++ ) {
        Data = Data.leftJustified(nMaxDataWidth,'0',true);
        strImageData += Data;
        if ( ( ( nCount + 1 ) % nMaxLine ) == 0 ) {
            if ( nRow == ( nMaxLine - 1) ) {
                cPrintPacketType = 's';
            }
            else if ( nRow == ( nMaxHeight - 1 ) ) {
                cPrintPacketType = 'e';
            }
            else {
                cPrintPacketType = 'c';
            }
            bResponse = sendData(const_cPHERIPHERAL_PRINTER,cPacketId, cPrintPacketType + strImageData,3000);
            strImageData = "";
            if ( ! bResponse ) {
                return false;
            }
        }
    }
    return true;
}

bool CPheripherals::grayscalePrint(const QImage &r_const_imageGRAYSCALE)
{
    bool bResponse;
    int nMaxHeight;
    int nMaxWidth;
    nMaxHeight = r_const_imageGRAYSCALE.height();//nMaxHeight=132;
    nMaxWidth = 264;
    int nRow, nCol, Max;
    int nRed, nGreen, nBlue;
    QString str,Data,strImageData;
    QImage image;
    bool bRePrint;
    Max = nMaxWidth/4;
    image = r_const_imageGRAYSCALE.scaled(r_const_imageGRAYSCALE.width() *2,r_const_imageGRAYSCALE.height());
    //image=image.convertToFormat(QImage::Format_Indexed8);
    //image=image.convertToFormat(QImage::Format_Mono,Qt::ThresholdDither);
    pauseThread();
    m_bPrinterReady = true;
    m_bDoorClosed = true;
    m_bPaperAvailable = true;
    do {
        bRePrint = false;
        strImageData="";
        for ( nRow = 0; nRow < nMaxHeight; nRow ++ ) {
            if ( nRow == image.height() - 1 ) {
                break;
            }
            bResponse = false;
            str = "";
            Data = "";
            for ( nCol = 0; nCol < nMaxWidth; nCol ++ ) {
                if ( nCol == image.width() - 1 ) {
                    break;
                }
                nRed = qRed(image.pixel(nCol,nRow));
                nGreen = qGreen(image.pixel(nCol,nRow));
                nBlue = qBlue(image.pixel(nCol,nRow));
                //increase Brightness
                int nBrightness = m_sliderBrightness->value();
                if ( ( nRed + nBrightness ) < 256 ) {
                    nRed += nBrightness;
                }
                else {
                    nRed = 255;
                }
                if ( ( nGreen + nBrightness < 256 ) ) {
                    nGreen += nBrightness;
                }
                else {
                    nGreen = 255;
                }
                if ( ( nBlue + nBrightness) < 256 ) {
                    nBlue += nBrightness;
                }
                else {
                    nBlue = 255;
                }

                //unsigned int bit3 = ((R & 128) >> 5) | ((G & 128) >> 6) | ((B & 128) >> 7); //3 bit color conversion
                unsigned int bit3 =(unsigned char)((nRed * 0.3) + (nGreen * 0.59) + (nBlue * 0.11));  //or (unsigned char)((R +G +B)/3); or (unsigned char)((Max3(R,G,B)+Min3(R,G,B))/2);

                if(bit3<75) bit3=0;
                else if(bit3>=75 && bit3<100) bit3=1;
                else if(bit3>=100 && bit3<128) bit3=2;
                else if(bit3>=128 && bit3<156) bit3=3;
                else if(bit3>=156 && bit3<181) bit3=4;
                else if(bit3>=181 && bit3<210) bit3=5;
                else if(bit3>=210 && bit3<240) bit3=6;
                else if(bit3>=240 && bit3<250) bit3=7;
                else if(bit3>=250) bit3=8;

                str += QString::number(bit3,2).rightJustified(4,'0',true);
                if ( str.length() == 8 ) {
                    Data += QString::number(str.toInt(0,2),16).rightJustified(2,'0',true).toUpper();
                    str = "";
                }
            }
            strImageData += Data.leftJustified(nMaxWidth,'8',true);
            if ( (nRow+1) % 10 == 0 ) {
                bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_DATA, strImageData, 5000);
                if ( ( ! bResponse ) || ( ! m_bPrinterReady ) || ( ! m_bDoorClosed )  || ( ! m_bPaperAvailable ) ) {
                    break;
                }
                strImageData = "";
            }
        }
        strImageData = strImageData.leftJustified(nMaxWidth*10,'8',true);
        if ( ( ( nRow % 10 ) != 0 ) && bResponse ) {
            /* send remaining lines of data */
            bResponse = sendData(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_DATA ,strImageData,5000);
        }
        if ( ! bResponse )
        {
            if(gbEnableMessageBoxPrinter)
                QMessageBox::critical(0, "Printer", "Failed while printing image..");
            break;
        }
        else if ( ! m_bPrinterReady )
        {
            if(gbEnableMessageBoxPrinter)
                QMessageBox::critical(0, "Printer", "Printer not connected..!");
            bResponse = false;
        }
        else if ( ( ! m_bDoorClosed ) || ( ! m_bPaperAvailable ) )
        {
            /* paper not available show the printer status dialog */
            if(gbEnableMessageBoxPrinter)
                bRePrint = waitForPrinting();
            bResponse = false;
        }
    } while ( bRePrint );

    if ( m_bThreadPause ) {
        startThread();
    }
    //image.save("abc.jpg");
    return bResponse;
}

bool CPheripherals::grayScalePrinting(const QImage &r_const_imageGRAYSCALE)
{
    /* conver the image to maximum width and update the brightness */
    bool bResponse = false;
    m_imageGrayScale = r_const_imageGRAYSCALE;
    m_sliderBrightness->setValue(0);
    if ( ! m_imageGrayScale.isNull() ) {
        if ( m_imageGrayScale.width() > 132 ) {
            m_imageGrayScale = m_imageGrayScale.scaledToWidth(132);
        }
        updateBrightness();
        m_dialogGrayScale->exec();
        pauseThread();
        /* send the adjust brighness grayscale image to print */
        bResponse = grayscalePrint(QImage(m_labelImage->pixmap()->toImage()));
        if ( m_bThreadPause ) {
            startThread();
        }
    }
    return bResponse;
}

bool CPheripherals::shutDown()
{
    //       qDebug()<<"\r PIC shutdown";
    pauseThread();
    //    if(gstrCheckgpsConfiguration.toLower()=="yes")
    //        objGps->setGPSStandby();
    /* intimate shutdown to co-processor */
    sendData(const_cPHERIPHERAL_MACHINE, const_cPACKETID_SHUTDOWN, "", 700);
    if ( m_bThreadPause ) {
        startThread();
    }
    //    qDebug()<<"\r PIC shutdown end";
}

bool CPheripherals::waitForPrinting()
{
    /* show dialog for reprint or cancel the print */
    m_dialogPrint->show();
    m_bPrintClicked = false;
    m_bPrintCanceled = false;
    do {
        if(!checkPrinterStatus())
            break;
        gUpdateScreen(100);
        /* check the printer status and wait until print is clicked or canceled */
    } while ( ! ( m_bPrintClicked || m_bPrintCanceled ));
    return m_bPrintClicked;
}

bool CPheripherals::testRTC()
{
    bool bResponse;
    pauseThread();

    /* send data to test the RTC is working fine or not */
    bResponse = sendData(const_cPHERIPHERAL_RTC, const_cPACKETID_TEST_RTC, "",5000);
    if ( m_bThreadPause ) {
        startThread();
    }
    //    qDebug()<<"\r TEST RTC IN PIC"<<bResponse;
    if ( bResponse ) {
        //        qDebug()<<"\r TEST RTC IN PIC 1 if"<<bResponse;
        if ( m_strRtc == "01" ) {
            QMessageBox::information(0,"RTC","RTC Battery is Low! Working Good!" );
            return true;
        }
        else if ( m_strRtc == "11" ) {
            QMessageBox::information(0,"RTC","RTC  Working Good!");
            return true;
        }
        else {
            QMessageBox::critical(0,"RTC","RTC  Failed!" );
            return false;
        }
    }
    else {
        //        qDebug()<<"\r TEST RTC IN PIC else "<<bResponse;
        return false;
    }
}

bool CPheripherals::setMachineId(QString machineId, QString deviceModel, QString ModuleId)
{
    bool bResponse;
    pauseThread();

    bResponse = sendData(const_cPHERIPHERAL_MACHINE, 'S', "00000000000"+machineId +"#"+deviceModel+"#"+ModuleId, 3000);
    if ( m_bThreadPause ) {
        startThread();
    }
    if(bResponse)
    {
        m_strMachineId = "00000000000"+machineId;
        return true;
    }
    else
    {
        m_strMachineId = "";
        QMessageBox::information(0,"MACHINE ID","MachineId set fail");
        return false;
    }
}

void CPheripherals::handleMessage(const QString &r_const_strDATA)
{
    /* handle the received data from co-processor */
    DEBUGMESSAGE("Received:" + r_const_strDATA);
    gPicDebugging(r_const_strDATA);
    if ( r_const_strDATA.at(r_const_strDATA.length()-1) == const_cEND_BYTE )
    {
        m_strPreviousData = "";
    }
    else
    {
        m_strPreviousData = m_strPreviousData.mid(m_strPreviousData.lastIndexOf(const_cSTART_BYTE,0));
    }
    QString strReceivedPacket;
    strReceivedPacket = r_const_strDATA.mid(6 + const_nSIZE_OF_NO_OF_BYTES);
    //Handle missing packets......................................// by uma
    QString strTotalNoofPackets = strReceivedPacket.mid(3,4);
    int nTotalPackets = strTotalNoofPackets.toInt();

    //Change for Printing logic
    if(nTotalPackets == strReceivedPacket.length())
    {
        //        qDebug()<<"\rsuccessPackets";
    }
    else
    {
        qDebug()<<"\r Negative ACK in missing packets";
        m_bResponse = false;
        return;
    }

    const char const_cACK = r_const_strDATA.at(2).toLatin1();
    if ( const_cACK == const_cPACKETID_SUCCESS_ACK)
    {

        /* successful response for the last requested command */
        m_bResponse = true;
        m_strPreviousData = "";
        QString strReceivedPacket;
        strReceivedPacket = r_const_strDATA.mid(6 + const_nSIZE_OF_NO_OF_BYTES);
        const char const_cPHERIPHERAL = strReceivedPacket.at(1).toLatin1();
        const char const_cPACKETID = strReceivedPacket.at(2).toLatin1();
        int nDataStart = 3 + const_nSIZE_OF_NO_OF_BYTES;
        QString strData = strReceivedPacket.mid(nDataStart,  strReceivedPacket.length() - nDataStart - 3);
        switch ( const_cPHERIPHERAL )
        {
        case const_cPHERIPHERAL_RTC :
            /* process pheripheral RTC related command response */
            if ( const_cPACKETID == const_cPACKETID_SET_RTC )
            {
                /* read date & time from data */
                QString strDateTime = strData; /* data format : ssmmhhDDMMYYd */
                DEBUGMESSAGE("Date:"<<strDateTime);
                m_dateTimeSystem.setDate(QDate(2000 + strDateTime.mid(10,2).toInt(),strDateTime.mid(8,2).toInt(), strDateTime.mid(6,2).toInt()));
                m_dateTimeSystem.setTime(QTime(strDateTime.mid(4,2).toInt(),strDateTime.mid(2,2).toInt(),strDateTime.left(2).toInt(),0));
                strDateTime.clear();
            }
            else if ( const_cPACKETID == const_cPACKETID_TEST_RTC )
            {
                /* data of test RTC */
                m_strRtc = strData.left(2);
            }
            break;

        case const_cPHERIPHERAL_IO_CONTROL :
            /* process pheripheral io control related command response */
            if ( const_cPACKETID == const_cPACKETID_SUPPLY_STATUS )
            {
                switch ( strData.at(0).toLatin1() )
                {

                case 'C':
                    if ( strData.mid(1,2) == "01" || strData.mid(1,2) == "10" )
                    {
                        /* charger is connected or charging */
                        if ( ! m_bBatteryCharging )
                        {
                            m_eChargeStatus = eChargeStatus_CONNECTED;
                            emit batteryChargeStatus(m_eChargeStatus);
                            m_bBatteryCharging = true;
                            if(m_bInvalidCharger)
                            {
                                m_bInvalidCharger = false;
                            }
                        }
                    }
                    else if ( strData.mid(1,2) == "00" )
                    {
                        /* charger is removed */
                        m_bBatteryCharging = false;
                        if(m_bInvalidCharger)
                        {
                            m_bInvalidCharger = false;
                        }
                        m_eChargeStatus = eChargeStatus_REMOVED;
                        emit batteryChargeStatus(m_eChargeStatus);
                        m_nPrevBatt = 101;
                        m_nADCTotal = 0;
                        m_nCount = 0;
                    }
                    else
                    {
                        /* Emitted when device switched ON with charger without battery */
                        if((!m_bInvalidCharger))
                        {
                            m_bInvalidCharger = true;
                            if(m_bBatteryCharging)
                            {
                                m_bBatteryCharging = false;
                            }
                            m_eChargeStatus = eChargeStatus_INVALID;
                            emit batteryChargeStatus(m_eChargeStatus);
                        }
                    }
                    break;

                case 'B':
                    nADCValue = strData.mid(3,3).toInt();
                    if (m_bBatteryCharging )
                    {
                        /* get the ADC value when it is charging means Battery full */
                        if(m_nADC_VALUE_SHUTDOWN > nADCValue)
                        {   /* to ensure received ADC value is valid, During battry full status */
                            m_nADCMaxValue = nADCValue;
                        }
                        m_bBatteryCharging = false;
                        m_nCount = 0;
                        m_nADCTotal = 0;
                        m_nPrevBatt = 101;
                        m_eChargeStatus = eChargeStatus_COMPLETED;
                        emit batteryChargeStatus(m_eChargeStatus);
                        emit batteryLevel(5,100);
                    }
                    if ( ! m_bBatteryCharging )
                    {
                        if ( nADCValue > m_nADCMaxValue )
                        {
                            m_nADCMaxValue = nADCValue;
                        }
                        if ( nADCValue <= m_nADC_VALUE_SHUTDOWN )
                        {
                            if(m_strDeviceModel.contains("HHC-7"))
                            {
                                /* shutdown the device for lowbattery */
                                emit shutdown(false);
                                return;
                            }
                            else
                            {
                                //LOW BATTERY SHUTDOWN in 81xx 01/11/2012 uma
                                if(m_strDeviceModel.contains("HHC-8"))
                                {
                                    emit shutdown(false);
                                    return;
                                }
                            }
                        }
                        if ( m_nCount > 0 && m_nCount <= 5 )
                        {
                            m_nADCTotal += nADCValue;
                            m_nCount ++;
                        }
                        else
                        {
                            int nBatteryLevel;
                            int nPercentage;
                            if ( m_nCount > 0 )
                            {
                                /* average of last 5 ADC value */
                                nADCValue = m_nADCTotal / 5;
                            }
                            m_nCount = 1;
                            m_nADCTotal = 0;
                            /* calculate percentage for ADC value */
                            nPercentage = ( (nADCValue - m_nADC_VALUE_SHUTDOWN) * 100 / (m_nADCMaxValue - m_nADC_VALUE_SHUTDOWN));
                            if ( nPercentage > m_nPrevBatt )
                            {
                                /* ignore charging value, if current percentage is greater than previous percentage. */
                                if ( (nPercentage - m_nPrevBatt) > 0 )
                                {    //modified like -- if ( (nPercentage - m_nPrevBatt) > 10 )
                                    return;
                                }
                            }
                            if ( nPercentage != m_nPrevBatt )
                            {
                                /* process only percentage is changed with previous value */
                                nBatteryLevel = getBatteryLevel(nPercentage);
                                m_nPrevBatt = nPercentage;
                                emit batteryLevel(nBatteryLevel, nPercentage);
                            }
                        }
                    }
                    break;

                case 'F':
                    /* charger failed */
                    if ( strData.mid(1,2) == "00")
                    {
                        /* invalid charger is plugged */
                        //                                m_eChargeStatus = eChargeStatus_INVALID;
                        /* temperarily commented for 70XX*/
                        //                                emit batteryChargeStatus(m_eChargeStatus);
                    }
                    else if(r_const_strDATA.mid(1,2) == "01")
                    {
                        //emit batteryChargeStatus("healthy status");
                    }
                    break;

                case 'D':
                    /* show shutdown dialog, if the power key hold down for more than 3 seconds */
                    emit shutdown(true);
                    break;

                case 'P':
                    /* shutdown directly without showing dialog. long press on key */
                    emit shutdown(false);
                    break;
                }
            }
            break;

        case const_cPHERIPHERAL_PRINTER :
            /* process pheripheral printer related command response */
            if ( const_cPACKETID == const_cPACKETID_PRINTER_STATUS )
            {
                /* response for paper not available when printing or get printer status */
                if ( strData.at(0) == 'o' )
                {
                    /* paper lock door is opened. it is now implemented in 80xx hardware */
                    m_bDoorClosed = false;
                    m_labelPrinterStatus->setText("Printer Door Opened");
                    m_pushButtonPrint->setEnabled(false);
                }
                else if ( strData.at(0) == 'd' )
                {
                    /* door closed but check paper is available or not */
                    m_bDoorClosed = true;
                    if ( strData.at(1) == 'a' )
                    {
                        m_bPaperAvailable = true;
                        m_labelPrinterStatus->setText("Paper Available");
                        m_pushButtonPrint->setEnabled(true);
                    }
                    else if ( strData.at(1) == 'n' )
                    {
                        m_bPaperAvailable = false;
                        m_labelPrinterStatus->setText("Paper not Available.. \nPlease Load..!");
                        m_pushButtonPrint->setEnabled(false);
                    }
                }
                if ( strData.at(2) == 'b' )
                {
                    /* printer is not ready */
                    m_bPrinterReady = false;
                }
                else if ( strData.at(2) == 'r')
                {
                    /* printer is ready */
                    m_bPrinterReady = true;
                }
            }
            break;

        case const_cPHERIPHERAL_MACHINE :
            /* process pheripheral memory device related command response */
            if ( const_cPACKETID == const_cPACKETID_ACK_MACHINE_ID )
            {
                /* get the machine id -- 20 char's length ---*/
                m_strMachineId = strData.mid(0,20);
            }
            else if ( const_cPACKETID == const_cPACKETID_GET_VERSION )
            {
                /* read co-processor version, datetime & device model */
                //                qDebug()<<"\r PIC GPRS str"<<strData;
                m_strPicVersion = strData.mid(11,6);
                m_strDeviceModel = strData.mid(17,3) + "-" + strData.mid(20,4);
                m_strPicDateTime = strData.mid(26,6);
                gnGPRSModuleType = strData.mid(36,2).toInt();
                //                qDebug()<<"\r PIC GPRS"<<gnGPRSModuleType;
                m_strPicDateTime = "20" + m_strPicDateTime.mid(4,2) + "-" +
                        m_strPicDateTime.mid(2,2) + "-" + m_strPicDateTime.mid(0,2) +
                        "T12:00:00";
            }
            else if ( const_cPACKETID == const_cPACKETID_POWER_CONTROL )
            {
                /* wakeup from idle mode */
                m_bIdleMode = false;
                emit wakeup(false);
            }
            else if ( const_cPACKETID == const_cPACKETID_BOOT_PSW )
            {
                /* get root password */
                m_strRootPassword = strData.left(8).trimmed();
            }
            else if ( const_cPACKETID == const_cPACKETID_NEGATIVE_ACK)
            {
                /* Negative acknowledgement returned */
                m_bNegativeAck = true;
                m_bResponse = false;
                break;
            }
            break;

        case const_cPHERIPHERAL_HID : // Keypad
            /* process pheripheral hid related command response */
            if ( const_cPACKETID == const_cPACKETID_ACK_KEYPAD_STATUS )
            {
                /* get the keypad mode */
                m_strLastkeypadMode = strData.mid(0,2);
                if ( strData.at(1) == 'U' ) {       //Upper Case
                    //                    qDebug()<<"\r Caplock true set";
                    m_bCapsLock = true;
                    if( m_bKeypadModeLocked )
                    {
                        m_bKeypadModeLocked = false;
                        emit keypadModeLocked(m_bKeypadModeLocked);
                    }
                }
                else if ( strData.at(1) == 'L' ) {  //Lower Case
                    m_bCapsLock = false;
                    if( m_bKeypadModeLocked )
                    {
                        m_bKeypadModeLocked = false;
                        emit keypadModeLocked(m_bKeypadModeLocked);
                    }
                }
                else if ( strData.at(1) == 'R' ) {  //Restricted Keypad Mode Change
                    if( !m_bKeypadModeLocked )
                    {
                        m_bKeypadModeLocked = true;
                        emit keypadModeLocked(m_bKeypadModeLocked);
                    }
                }
                if ( strData.at(0) == 'N' ) {
                    /* numeric mode */
                    if ( ginputMethodObj !=NULL ) {
                        /* for mobile keypad, to commit last entered key */
                        ginputMethodObj->reset();
                    }
                    gekeypadModeCurrent = eKeypadMode_NUMERIC;
                }
                else if ( strData.at(0) == 'A' ) {
                    if(m_bCapsLock)
                    {
                        /* alphabets mode capslock */
                        gekeypadModeCurrent = eKeypadMode_ALPHABETS_CAPS;
                    }
                    else
                    {
                        /* alphabets mode */
                        gekeypadModeCurrent = eKeypadMode_ALPHABETS;
                    }
                }
                else{
                    // do nothing
                }
                emit keypadMode(gekeypadModeCurrent,m_bCapsLock);
            }
            else if ( const_cPACKETID == const_cPACKETID_GET_VERSION )
            {
                if ( strData.mid(0,2)=="10" )
                {
                    emit volumeIncrease(true);
                }
                else
                {
                    emit volumeIncrease(false);
                }
            }
            break;

        case const_cPHERIPHERAL_MAGNETICCARD_READER:
            if( const_cPACKETID == const_cPACKETID_ACK_READ_MAGNETICCARD)
            {
                m_strMCRData = strData;
            }
            break;
        }
    }
    else if ( const_cACK == const_cPACKETID_NEGATIVE_ACK )
    {
        /* negative ack from module detection */
        m_bNegativeAck = true;
        m_bResponse = false;
    }
    else
    {
        qDebug()<<"\rinvalid data from co-processor";
    }
}

int CPheripherals::getBatteryLevel(int nPercentage)
{
    int nBatteryLevel;
    if ( nPercentage >= 80 )
    {
        nBatteryLevel = 5;
    }
    else if ( nPercentage >= 68 && nPercentage < 80 )
    {
        nBatteryLevel = 4;
    }
    else if ( nPercentage >= 50 && nPercentage < 68 )
    {
        nBatteryLevel = 3;
    }
    else if ( nPercentage >= 44 && nPercentage < 50 )
    {
        nBatteryLevel = 2;
    }
    else if ( nPercentage >= 30 && nPercentage < 44 )
    {
        nBatteryLevel = 1;
    }
    else
    {
        nBatteryLevel = 0;
    }
    return nBatteryLevel;

    //Testing comment below for testing battery levels

    /* calculate the battery level with given percentage */
//    int nBatteryLevel;
//    if ( nPercentage >= 80 )
//    {
//        nBatteryLevel = 5;
//    }
//    else if ( nPercentage >= 68 && nPercentage < 80 )
//    {
//        nBatteryLevel = 4;
//    }
//    else if ( nPercentage >= 56 && nPercentage < 68 )
//    {
//        nBatteryLevel = 3;
//    }
//    else if ( nPercentage >= 44 && nPercentage < 56 )
//    {
//        nBatteryLevel = 2;
//    }
//    else if ( nPercentage >= 24 && nPercentage < 44 )
//    {
//        nBatteryLevel = 1;
//    }
//    else
//    {
//        nBatteryLevel = 0;
//    }
//    return nBatteryLevel;
}

void CPheripherals::arrivedData()
{
    /* read the data from the buffer */
    char arr_cReadbuffer[1024];
    int nBytesAvailable = m_serialportCoProcessor->bytesAvailable();
    if ( nBytesAvailable > 0 ) {
        /* read the available bytes */
        int nBytesReceived = m_serialportCoProcessor->readData(arr_cReadbuffer,nBytesAvailable);
        if ( nBytesReceived > 0 ) {
            /* received buffer data */
            int nStart, nEnd;
            arr_cReadbuffer[nBytesReceived] = '\0';
            QString strData(arr_cReadbuffer);
            QString strReceivedBuffer;
            strReceivedBuffer = strData.left(nBytesReceived);
//            qDebug()<<"\r\n Received"<<strReceivedBuffer;
            m_strLogData += strReceivedBuffer;
            strReceivedBuffer = m_strPreviousData.append(strReceivedBuffer);
            nStart = strReceivedBuffer.indexOf(const_cSTART_BYTE,0);
            nEnd = strReceivedBuffer.indexOf(const_cEND_BYTE,0);

            if ( nStart >=0 && nEnd > 0 )
            {
                if ( strReceivedBuffer.contains("^MN") ) {
                    /* negative acknowledgement given by co-processor */
                    handleMessage(strReceivedBuffer);
                    m_strLogData.clear();
                }
                else if ( strReceivedBuffer.contains("^MK") ) {
                    /* handle message if successful received by co-processor */
                    nStart = strReceivedBuffer.indexOf(const_cSTART_BYTE,9);
                    nEnd = strReceivedBuffer.indexOf(const_cEND_BYTE,10);
                    if ( nStart >= 0 && nEnd > 0 )
                    {
                        /* data received completed */
                        handleMessage(strReceivedBuffer);
                        m_strLogData.clear();
                    }
                }
            }
            /* data might be not fully arrived, so keep it in previous data */
            m_strPreviousData = strReceivedBuffer;
            strReceivedBuffer.clear();
            strData.clear();
        }
    }
}

void CPheripherals::updateBrightness()
{
    /* update the brightness for grayscale imae with current brightness value */
    int nRed, nGreen, nBlue;
    QImage image = m_imageGrayScale;
    for ( int nPosY = 0; nPosY < image.height(); nPosY ++ )
    {
        for ( int nPosX = 0; nPosX < image.width(); nPosX ++ )
        {
            nRed = qRed(image.pixel(nPosX,nPosY));
            nGreen = qGreen(image.pixel(nPosX,nPosY));
            nBlue = qBlue(image.pixel(nPosX,nPosY));
            int nBrightness = m_sliderBrightness->value();
            /* increase the brightness with rgb values */
            if ( ( nRed + nBrightness ) < 256 )
            {
                nRed += nBrightness;
            }
            else
            {
                nRed = 255;
            }
            if ( ( nGreen + nBrightness < 256 ) )
            {
                nGreen += nBrightness;
            }
            else
            {
                nGreen = 255;
            }
            if ( ( nBlue + nBrightness) < 256 )
            {
                nBlue += nBrightness;
            }
            else
            {
                nBlue = 255;
            }
            /* convert into 3-bit grayscale value */
            unsigned int nBit3 = (unsigned char)((nRed * 0.3) + (nGreen * 0.59) + (nBlue * 0.11));
            unsigned int nRetVal=0;
            nRetVal = nRetVal + nBit3;
            nRetVal = nRetVal * 256 ;
            nRetVal = nRetVal + nBit3;
            nRetVal = nRetVal * 256 ;
            nRetVal = nRetVal + nBit3;
            image.setPixel(nPosX,nPosY,nRetVal);
        }
    }
    m_labelImage->setPixmap(QPixmap::fromImage(image));
}

void CPheripherals::on_pushButtonPrint_clicked()
{
    /* close the dialog & print the data again */
    m_bPrintClicked = true;
    m_bPrintCanceled = false;
    m_dialogGrayScale->close();
    m_dialogPrint->close();
}

void CPheripherals::on_pushButtonCancel_clicked()
{
    /* close the dialog & cancel the print */
    m_bPrintCanceled = true;
    m_dialogGrayScale->close();
    m_dialogPrint->close();
}
