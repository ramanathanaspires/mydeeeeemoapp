#include "cfpmodule.h"
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

const int const_nIMAGEHEIGHT    = 270;
const int const_nIMAGEWIDTH     = 192;
int nTIMEOUT_MSECS              = 60000; //60 seconds if timeout is -2 then unlimited

/**
 * \var QLabel *labelStatus
 * \brief used to display the status in the fingerprint dialog.
 */
QLabel *labelStatus;

/**
 * \var QLabel *labelImage
 * \brief used to display the status image in the fingerprint dialog.
 */
QLabel *labelImage;

/**
 * \var QProgressBar *progressBarCompleted
 * \brief used to display the progress value of an enrollment.
 */
QProgressBar *progressBarCompleted;

/**
 * \var bool bCancelOpeation
 * \brief used to store the fingerprint cancel operation.
 */
bool bCancelOpeation;

/**
 * \var bool bCancelOpeation
 * \brief used to store the fingerprint cancel operation.
 */

bool DisplayStatus;
bool DontDisplay;
bool bWrongFinger;

/**
 * \var PT_CONNECTION PConn
 * \brief used to store the connection of fingerprint device.
 */
PT_CONNECTION PConn;

/* Used to supress compiler warnings */
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(param)   (void)param
#endif

#define OUTPUT_FORMAT_ANSI
//#define OUTPUT_FORMAT_ISO

/* Check if output output format is selected correctly */

#if (((!defined(OUTPUT_FORMAT_ANSI)) && (!defined(OUTPUT_FORMAT_ISO))) || (defined(OUTPUT_FORMAT_ANSI) && defined(OUTPUT_FORMAT_ISO)))
#error "Select one and only one of output formats!"
#endif

/**
 * \fn void status_info(PT_STATUS status, QWidget *widget)
 * \brief This function is used to process the status value.
 * \param[in] status used to set the result status given by fingerprint library call.
 * \param[in] widget used to set the paprent for the messagebox.
 */
void status_info(PT_STATUS status, QWidget *widget)
{
    switch ( status ) {
    case PT_STATUS_OK :
        break;
    case PT_STATUS_GENERAL_ERROR :
        QMessageBox::critical(widget,"Finger Print", "General communication Error");
        break;
    case PT_STATUS_API_NOT_INIT:
        QMessageBox::critical(widget,"Finger Print", "API wasn't initialized");
        break;
    case PT_STATUS_API_ALREADY_INITIALIZED:
        QMessageBox::critical(widget,"Finger Print", "API was already initialized");
        break;
    case PT_STATUS_INVALID_PARAMETER:
        QMessageBox::critical(widget,"Finger Print", "Invalid Parameter");
        break;
    case PT_STATUS_INVALID_HANDLE:
        QMessageBox::critical(widget,"Finger Print", "Invalid Handle");
        break;
    case PT_STATUS_NOT_ENOUGH_MEMORY:
        QMessageBox::critical(widget,"Finger Print", "Not Enough memory to process given operation");
        break;
    case PT_STATUS_MALLOC_FAILED:
        QMessageBox::critical(widget,"Finger Print", "Failiure of Extern Memory Alloacatio");
        break;
    case PT_STATUS_NOT_ENOUGH_PERMANENT_MEMORY:
        QMessageBox::critical(widget,"Finger Print", "Not Enough Permenant Memory to Store Data");
        break;
    case PT_STATUS_MORE_DATA:
        QMessageBox::critical(widget,"Finger Print", "There is more data to return than the supplied buffer can contain");
        break;
    case PT_STATUS_FUNCTION_FAILED:
        QMessageBox::critical(widget,"Finger Print", "Function failed");
        break;
    case PT_STATUS_INVALID_INPUT_BIR_FORM:
        QMessageBox::critical(widget,"Finger Print", "Invalid form of PT_INPUT_BIR structure");
        break;
    case PT_STATUS_WRONG_RESPONSE:
        QMessageBox::critical(widget,"Finger Print", "TFM has returned wrong or unexpected response");
        break;
    case PT_STATUS_NOT_ENOUGH_TFM_MEMORY:
        QMessageBox::critical(widget,"Finger Print", "Not enough memory on TFM to process given operation");
        break;
    case PT_STATUS_ALREADY_OPENED:
        QMessageBox::critical(widget,"Finger Print", "Connection is already opened");
        break;
    case PT_STATUS_CANNOT_CONNECT:
        QMessageBox::critical(widget,"Finger Print", "Cannot connect to TFM");
        break;
    case PT_STATUS_TIMEOUT:
        QMessageBox::critical(widget,"Finger Print", "TIMEOUT elapsed");
        break;
    case PT_STATUS_BAD_BIO_TEMPLATE:
        QMessageBox::critical(widget,"Finger Print", "Bad biometric template");
        break;
    case PT_STATUS_SLOT_NOT_FOUND:
        QMessageBox::critical(widget,"Finger Print", "Requested slot was not found");
        break;
    case PT_STATUS_ANTISPOOFING_EXPORT:
        QMessageBox::critical(widget,"Finger Print", "Attempt to export antispoofing info from TFM");
        break;
    case PT_STATUS_ANTISPOOFING_IMPORT:
        QMessageBox::critical(widget,"Finger Print", "Attempt to import antispoofing info to TFM");
        break;
    case PT_STATUS_ACCESS_DENIED:
        QMessageBox::critical(widget,"Finger Print", "Access to operation is denied");
        break;
    case PT_STATUS_NO_TEMPLATE:
        QMessageBox::critical(widget,"Finger Print", "No template was captured in current session");
        break;
    case PT_STATUS_BIOMETRIC_TIMEOUT:
        qDebug()<<"Biometric operation timeout";
        break;
    case PT_STATUS_CONSOLIDATION_FAILED:
        QMessageBox::critical(widget,"Finger Print", "API wasn't initialized");
        break;
    case PT_STATUS_BIO_OPERATION_CANCELED:
        qDebug()<<"Biometric operation canceled";
        break;
    case PT_STATUS_AUTHENTIFICATION_FAILED:
        QMessageBox::critical(widget,"Finger Print", "Authentification failed");
        break;
    case PT_STATUS_UNKNOWN_COMMAND:
        QMessageBox::critical(widget,"Finger Print", "Unknown command");
        break;
    case PT_STATUS_GOING_TO_SLEEP:
        QMessageBox::critical(widget,"Finger Print", "Power off attempt failed");
        break;
    case PT_STATUS_NOT_IMPLEMENTED:
        QMessageBox::critical(widget,"Finger Print", "Function or service is not implemented");
        break;
    case PT_STATUS_COMM_ERROR:
        QMessageBox::critical(widget,"Finger Print", "communication error");
        break;
    case PT_STATUS_SESSION_TERMINATED:
        QMessageBox::critical(widget,"Finger Print", "Session was terminated");
        break;
    case PT_STATUS_TOUCH_CHIP_ERROR:
        QMessageBox::critical(widget,"Finger Print", "Touch chip error occured");
        break;
    case PT_STATUS_I2C_EEPROM_ERROR:
        QMessageBox::critical(widget,"Finger Print", "I2C EEPROM error occured");
        break;
    case PT_STATUS_INVALID_PURPOSE:
        QMessageBox::critical(widget,"Finger Print", "Purpose parameter (or BIR's purpose) is invalid for given operation");
        break;
    case PT_STATUS_SWIPE_TOO_BAD:
        QMessageBox::critical(widget,"Finger Print", "Finger swipe is too bad for image reconstruction");
        break;
    case PT_STATUS_NOT_SUPPORTED:
        QMessageBox::critical(widget,"Finger Print", "Requested functionality or value of parameter is not supported");
        break;
    case PT_STATUS_CALIBRATION_FAILED:
        QMessageBox::critical(widget,"Finger Print", "Calibration failed");
        break;
    case PT_STATUS_ANTISPOOFING_NOT_CAPTURED:
        QMessageBox::critical(widget,"Finger Print", "Antispoofing data were not captured");
        break;
    case PT_STATUS_LATCHUP_DETECTED:
        QMessageBox::critical(widget,"Finger Print", "Sensor latch-up event detected");
        break;
    case PT_STATUS_DIAGNOSTICS_FAILED:
        QMessageBox::critical(widget,"Finger Print", "Diagnostics failed");
        break;
    case PT_STATUS_SAME_VERSION:
        QMessageBox::critical(widget,"Finger Print", "Attempt to upgrade to same firmware version");
        break;
    case PT_STATUS_NO_SENSOR:
        QMessageBox::critical(widget,"Finger Print", "No sensor");
        break;
    case PT_STATUS_SENSOR_OUT_OF_LIMITS:
        QMessageBox::critical(widget,"Finger Print", "The measured values are out of allowable limits");
        break;
    case PT_STATUS_TOO_MANY_BAD_LINES:
        QMessageBox::critical(widget,"Finger Print", "Too many bad lines");
        break;
    case PT_STATUS_SENSOR_NOT_REPAIRABLE:
        QMessageBox::critical(widget,"Finger Print", "Sensor is not repairable");
        break;
    case PT_STATUS_GAIN_OFFSET:
        QMessageBox::critical(widget,"Finger Print", "Gain offset calibration error");
        break;
    case PT_STATUS_POWER_SHUTOFF:
        QMessageBox::critical(widget,"Finger Print", "Asynchronous power shut down");
        break;
    case PT_STATUS_OLD_VERSION:
        QMessageBox::critical(widget,"Finger Print", "Attempt to upgrade to older firmware version");
        break;
    case PT_STATUS_SUSPEND:
        QMessageBox::critical(widget,"Finger Print", "Connection interrupted because of suspend request");
        break;
    case PT_STATUS_DEVICE_NOT_FOUND:
        QMessageBox::critical(widget,"Finger Print", "Device not found");
        break;
    case PT_STATUS_DEVICE_SICK:
        QMessageBox::critical(widget,"Finger Print", "Device doesn't work as expected");
        break;
    case PT_STATUS_UNSUPPORTED_SPEED:
        QMessageBox::critical(widget,"Finger Print", "Host hardware doesn't support requested communication speed");
        break;
    case PT_STATUS_SENSOR_NOT_CALIBRATED:
        QMessageBox::critical(widget,"Finger Print", "Sensor is not calibrated");
        break;
    case PT_STATUS_SAFE_MODE:
        QMessageBox::critical(widget,"Finger Print", "Firmware is missing or corrupted, device is running in safe mode");
        break;
    case PT_STATUS_SENSOR_HW_ERROR:
        QMessageBox::critical(widget,"Finger Print", "Sensor hardware error occured");
        break;
    case PT_STATUS_SESSION_NOT_AUTHENTICATED:
        QMessageBox::critical(widget,"Finger Print", "Session was not authenticated yet");
        break;
    case PT_STATUS_SECURE_CHANNEL_ALREADY_ESTABLISHED:
        QMessageBox::critical(widget,"Finger Print", "Secure channel has been already established");
        break;
    case PT_STATUS_OTP_SEQUENCE_NUMBER_OVERFLOW:
        QMessageBox::critical(widget,"Finger Print", "Overflow of One Time Password sequence number");
        break;
    case PT_STATUS_NVM_ERROR:
        QMessageBox::critical(widget,"Finger Print", "General NVM error");
        break;
    case PT_STATUS_NVM_CANNOT_WRITE:
        QMessageBox::critical(widget,"Finger Print", "NVM write operation failed");
        break;
    case PT_STATUS_NVM_CANNOT_READ:
        QMessageBox::critical(widget,"Finger Print", "NVM read operation failed");
        break;
    case PT_STATUS_NVM_INVALID_FILE_ID:
        QMessageBox::critical(widget,"Finger Print", "Attempt to access non-existing internal NVM file");
        break;
    case PT_STATUS_CRYPTO_ERROR:
        QMessageBox::critical(widget,"Finger Print", "General crypto error");
        break;
    case PT_STATUS_CRYPTO_MECHANISM_NOT_SUPPORTED:
        QMessageBox::critical(widget,"Finger Print", "Requested cryptographic mechanism is not supported");
        break;
    case PT_STATUS_CRYPTO_PADDING_ERROR:
        QMessageBox::critical(widget,"Finger Print", "Padding error detected during crypto operation");
        break;
    case PT_STATUS_CRYPTO_KEY_TOO_LONG:
        QMessageBox::critical(widget,"Finger Print", "Key too long (probably due to the export regulations)");
        break;
    case PT_STATUS_CRYPTO_SYM_BAD_KEY:
        QMessageBox::critical(widget,"Finger Print", "Bad symmetric key used");
        break;
    case PT_STATUS_HW_RNG_INIT_ERROR:
        QMessageBox::critical(widget,"Finger Print", "HW random number generator initialization failed");
        break;
    case PT_STATUS_EX_ACCESS_VIOLATION:
        QMessageBox::critical(widget,"Finger Print", "Device is already opened for exclusive access by somebody else");
        break;
    case PT_STATUS_WRONG_FINGER_DATA_ACCESS_RIGHTS:
        QMessageBox::critical(widget,"Finger Print", "Used wrong finger data access rights");
        break;
    case PT_STATUS_NO_LAST_MATCH_DATA:
        QMessageBox::critical(widget,"Finger Print", "Last match data don't exist");
        break;
    case PT_STATUS_NO_DATA:
        QMessageBox::critical(widget,"Finger Print", "No data found");
        break;
    case PT_STATUS_CRYPTO_RSA_KEY_CHECK:
        QMessageBox::critical(widget,"Finger Print", "RSA key is not consistent");
        break;
    case PT_STATUS_CRYPTO_RSA_BAD_PUBLIC_KEY:
        QMessageBox::critical(widget,"Finger Print", "Bad RSA public key supplied");
        break;
    case PT_STATUS_SC_ERROR:
        QMessageBox::critical(widget,"Finger Print", "NVM has invalid format or is not formatted at all");
        break;
    case PT_STATUS_SC_NOT_SUPPORTED:
        QMessageBox::critical(widget,"Finger Print", "Communication with this card is not supported");
        break;
    case PT_STATUS_SC_COMM_FAIL:
        QMessageBox::critical(widget,"Finger Print", "Failure during communication with the card ");
        break;
    case PT_STATUS_SC_BAD_PARAM :
        QMessageBox::critical(widget,"Finger Print", "Incorrect parameter detected");
        break;
    case PT_STATUS_SC_NO_CARD :
        QMessageBox::critical(widget,"Finger Print", "the card is not present in the reader");
        break;
    }
}

PT_STATUS myCallback(void *pGuiStateCallbackCtx, PT_DWORD dwGuiState,PT_BYTE *pbyResponse, PT_DWORD dwMessage,
                     PT_BYTE byProgress, void *pSampleBuffer,PT_DATA *pData)
{
    Q_UNUSED(pGuiStateCallbackCtx);
    Q_UNUSED(dwGuiState);
    Q_UNUSED(pSampleBuffer);
    Q_UNUSED(pData);
    if ( bCancelOpeation ) {
        /* cancel the operation */
        *pbyResponse = PT_CANCEL;
    }
    if ( DontDisplay ) {
        return PT_STATUS_OK;
    }
    switch (dwMessage) {
        /* Sometimes some info how the operation progressBarCompletedes is sent. */
    case 46: /* intimate Progress */
        if ( progressBarCompleted->value() != (int)byProgress ) {
            bWrongFinger = false;
        }
        progressBarCompleted->setValue((int)byProgress);
        break;
        case PT_GUIMSG_GOOD_IMAGE:
        case PT_GUIMSG_CONSOLIDATION_SUCCEED:
        if ( DisplayStatus ) {
            labelImage->setPixmap(QPixmap(":/icons-png/bfsucc.png"));
            labelStatus->setText("Success");
        }
        else {
            DontDisplay = true;
        }
        break;
        case PT_GUIMSG_CONSOLIDATION_FAIL:
        labelImage->setPixmap(QPixmap(":/icons-png/bffail.png"));
        labelStatus->setText("Failure");
        break;
        /* Prompt messages should inform the user that he should do
         * something. */
        case PT_GUIMSG_SWIPE_IN_PROGRESS:
        labelImage->setPixmap(QPixmap(":/icons-png/bfswife.png"));
        labelStatus->setText("Swipe the Finger");
        break;
        case PT_GUIMSG_PUT_FINGER:
        if ( ! bWrongFinger ) {
            labelImage->setPixmap(QPixmap(":/icons-png/bfput.png"));
            labelStatus->setText("Touch the Sensor");
            //                labelStatus->setText("Keep your finger");     // temperarily used this line for attendence project
        }
        break;
        case PT_GUIMSG_KEEP_FINGER:
        if ( bWrongFinger ) {
            labelImage->setPixmap(QPixmap(":/icons-png/bfwait.png"));
            labelStatus->setText("Don't Remove the Finger");
        }
        break;
        case PT_GUIMSG_REMOVE_FINGER:
        labelImage->setPixmap(QPixmap(":/icons-png/bfremove.png"));
        labelStatus->setText("Lift your finger away from the sensor");
        break;
        case PT_GUIMSG_CLEAN_SENSOR:
        labelStatus->setText("Clean the sensor");
        break;

        /* Quality messages come if something went wrong. E.g. the user
         * did not scan his finger in the right way. */
        case PT_GUIMSG_TOO_LEFT:
        labelImage->setPixmap(QPixmap(":/icons-png/bfleft.png"));
        labelStatus->setText("Bad Quality : too left");
        break;
        case PT_GUIMSG_TOO_RIGHT:
        labelImage->setPixmap(QPixmap(":/icons-png/bfright.png"));
        labelStatus->setText("Bad Quality : too right");
        break;
        case PT_GUIMSG_TOO_LIGHT:
        labelImage->setPixmap(QPixmap(":/icons-png/bflight.png"));
        labelStatus->setText("Bad Quality : too light");
        break;
        case PT_GUIMSG_TOO_DRY:
        labelStatus->setText("Bad Quality : too dry");
        break;
        case PT_GUIMSG_TOO_SMALL:
        labelImage->setPixmap(QPixmap(":/icons-png/bfsmall.png"));
        labelStatus->setText("Bad Quality : too small");
        break;
        case PT_GUIMSG_TOO_SHORT:
        labelImage->setPixmap(QPixmap(":/icons-png/bfshort.png"));
        labelStatus->setText("Bad Quality : too short");
        break;
        case PT_GUIMSG_TOO_HIGH:
        labelImage->setPixmap(QPixmap(":/icons-png/bfhigh.png"));
        labelStatus->setText("Bad Quality : too high");
        break;
        case PT_GUIMSG_TOO_LOW:
        labelImage->setPixmap(QPixmap(":/icons-png/bflow.png"));
        labelStatus->setText("Bad Quality : too low");
        break;
        case PT_GUIMSG_TOO_FAST:
        labelImage->setPixmap(QPixmap(":/icons-png/bffast.png"));
        labelStatus->setText("Bad Quality : too fast");
        break;
        case PT_GUIMSG_TOO_SKEWED:
        labelImage->setPixmap(QPixmap(":/icons-png/bfskew.png"));
        labelStatus->setText("Bad Quality : too skewed");
        break;
        case PT_GUIMSG_TOO_DARK:
        labelStatus->setText("Bad Quality : too dark");
        break;
        case PT_GUIMSG_BACKWARD_MOVEMENT:
        labelStatus->setText("Bad Quality : backward movement");
        break;
        case PT_GUIMSG_JOINT_DETECTED:
        labelStatus->setText("Bad Quality : joint detected");
        break;
       case 45: //Operation Failed
           labelImage->setPixmap(QPixmap(":/icons-png/bffail.png"));
           labelStatus->setText("Put Correct Finger");
           bWrongFinger=true;
       }
    qApp->processEvents();
    return PT_STATUS_OK;
}

CFpModule::CFpModule()
{
    /* create a fingerprint dialog for display the status */
    m_dialogFingerPrint = new QDialog;
    connect(m_dialogFingerPrint, SIGNAL(rejected()), this, SLOT(on_pushButtonCancel_clicked()));

    labelImage = new QLabel(m_dialogFingerPrint);
    labelImage->setFont(QFont("sans serif",14,1,false));
    labelImage->setAlignment(Qt::AlignCenter);
    labelImage->setWordWrap(true);
    labelImage->setPalette(QPalette(QColor(Qt::white)));
    labelImage->setAutoFillBackground(true);
    labelImage->setPixmap(QPixmap(":/icons-png/bfput.png"));
    labelImage->setFixedSize(320,140);

    labelStatus = new QLabel("Put Your Finger",m_dialogFingerPrint);
    labelStatus->setFont(QFont("sans serif",12,QFont::Bold));
    labelStatus->setStyleSheet("background-color: black;color:white");
    labelStatus->setAlignment(Qt::AlignCenter);

    progressBarCompleted = new QProgressBar(m_dialogFingerPrint);
    progressBarCompleted->setRange(0,100);
    progressBarCompleted->setValue(0);
    progressBarCompleted->setFixedWidth(270);

    m_pushButtonCancel = new QPushButton("Cancel -F4",m_dialogFingerPrint);
    m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    m_pushButtonCancel->setFixedWidth(170);
    m_pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));
    m_pushButtonCancel->setIcon(QIcon(":/icons-png/cancel.png"));
    connect(m_pushButtonCancel,SIGNAL(clicked()),this,SLOT(on_pushButtonCancel_clicked()));

    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout(m_dialogFingerPrint);
    vBoxLayoutMain->addWidget(labelImage);
    vBoxLayoutMain->addWidget(labelStatus);
    vBoxLayoutMain->addWidget(progressBarCompleted, 3, Qt::AlignCenter);
    vBoxLayoutMain->addWidget(m_pushButtonCancel, 1, Qt::AlignCenter);
    vBoxLayoutMain->setMargin(0);
    vBoxLayoutMain->setSpacing(0);

    m_dialogFingerPrint->setFixedSize(320,240);
    m_dialogFingerPrint->setLayout(vBoxLayoutMain);
    m_dialogFingerPrint->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_dialogFingerPrint->setWindowModality(Qt::ApplicationModal);
}

CFpModule::~CFpModule()
{
    /* free the allocated resources */
    delete m_dialogFingerPrint;
}

QString CFpModule::reverse(const QString &r_const_strDATA)
{
    QString strOutput;
    for ( int nIndex = 0; nIndex < r_const_strDATA.length(); nIndex = nIndex + 2) {
        strOutput = r_const_strDATA.mid(nIndex,2) + strOutput;
    }
    return strOutput;
}

bool CFpModule::init(bool bShowDialog)
{
    /* Initialize PTAPI */
    PConn = NULL;
    bCancelOpeation = false;
    DisplayStatus = true;
    DontDisplay = false;
    //gGrabImageSupported = ABS_FALSE;
    m_PStatus= PTInitialize(0);
    if ( m_PStatus != PT_STATUS_OK ) {
        if ( m_PStatus != PT_STATUS_API_ALREADY_INITIALIZED ) {
            printf("ABSInitilize() failed\n");
            status_info(m_PStatus,m_dialogFingerPrint);
            return false;
        }
    }    
#if 0 /* get the list of devices found */
    PT_DEVICE_LIST* dev_list;
    int nDevIndex;
    m_PStatus = PTEnumerateDevices("usb", &dev_list);
    if ( m_PStatus != PT_STATUS_OK ) {
        printf("ABSEnumerateDevices() failed.\n");
        status_info(m_PStatus,m_dialogFingerPrint);
        return FALSE;
    }
    if ( dev_list->NumDevices == 0) {
        printf("No fingerprint device found.\n");
        return FALSE;
    }
    if ( dev_list->NumDevices >= 1) {
        /* There is a single device, so take it. */
        nDevIndex = 0;
    }
    m_PStatus = PTOpen(dev_list->List[nDevIndex].DsnSubString, &PConn);
#endif
    /* Open BSAPI session */
    m_PStatus = PTOpen(const_cast <PT_CHAR *>("usb"), &PConn);
    if ( m_PStatus != PT_STATUS_OK ) {
        printf("ABSOpen() failed.\n");
        status_info(m_PStatus, m_dialogFingerPrint);
        return false;
    }
    else {
        PT_SESSION_CFG_V3 *config;
        PT_WORD Lenght;

        /* get the session configuration */
        PTGetSessionCfgEx(PConn,PT_CURRENT_SESSION_CFG,&Lenght,&config);

        /* change the session configuration as follows */
        config->SecuritySetting = PT_MATCH_HIGHER_SECURITY;
        config->MultipleEnroll = PT_TRUE;
        config->SensorDisabling = PT_TRUE;
        config->CallbackLevel= CALLBACKS_ADVANCED;        
        config->WakeUpByFinger = PT_TRUE;
        config->WakeUpByFingerTimeout = 100;
        config->ConsolidationType = PT_CONSOLIDATION_STRICT;        
        PTSetSessionCfgEx(PConn, PT_CURRENT_SESSION_CFG, Lenght, config);

        free(config);
        if ( bShowDialog ) {
            qApp->processEvents();
            m_dialogFingerPrint->show();
            qApp->processEvents();
        }
        gLoadIntoSharedPIC(const_strPAUSE_THREADS);
        return true;
    }
}

bool CFpModule::terminate()
{
    /* close the fingerprint device & terminate the library */
    PTClose(PConn);
    m_PStatus = PTTerminate();
    m_dialogFingerPrint->close();
    gLoadIntoSharedPIC(const_strWAKEUP_THREADS);
    if ( m_PStatus == PT_STATUS_OK ) {
        return true;
    }
    else {
        return false;
    }
}

bool CFpModule::getFingerImage(QImage &r_imageFinger)
{
    progressBarCompleted->setVisible(false);
    if ( init() ) {
        PT_DATA  *pImage;

        /* Grab image */
        PTSetGUICallbacks (PConn, NULL, NULL, myCallback, NULL);

        m_PStatus = PTGrab (PConn, PT_GRAB_TYPE_381_381_8, nTIMEOUT_MSECS, PT_TRUE, &pImage, 0, 0);
        if ( m_PStatus != PT_STATUS_OK ) {
            printf("ABSGrabImag() failed.");
            status_info(m_PStatus,m_dialogFingerPrint);
            terminate();
            return false;
        }
        /* Get sensor id */
        DEBUGMESSAGE("Grab image success");
        drawImage(pImage, r_imageFinger);
#if 0 /* Convert grabbed image ANSI/ISO format */
        PT_BYTE *pstrOutputImage = NULL;
        PT_DWORD lenstrOutput = const_nIMAGEHEIGHT * const_nIMAGEWIDTH + 36 + 14;
        pstrOutputImage = (PT_BYTE *) malloc(lenstrOutput);
        m_PStatus = absSampleToAnsiIso(pImage,  pstrOutputImage, &lenstrOutput );
        if ( m_PStatus != 0 ) {
            printf("Error in image conversion\n");
            return false;
        }
        else {
            drawImage(pImage,r_imageFinger);
        }
#endif
        /* Free grabwibed image */
        PTFree(pImage);
        terminate();
        return true;
    }else {
        return false;
    }
}

//
/* Paints the CFpModule sample image. */
void CFpModule::drawImage(PT_DATA *pImage, QImage &r_imageFinger)
{
    int nMax = pImage->Length;
    char arr_cBuffer[nMax];
    int i;
    int j = nMax - 1;
    for ( i = 0; i < nMax; i ++ ) {
        arr_cBuffer[j] = pImage->Data[i];
        j --;
    }
    int nlen ;
    QString strHeaderInfo;

    //*****************************FILE****************************************************************
    uint ValidByt;

    /* Header info for bmp image file */
    //strHeaderInfo="424D00000000000000003604000028000000000100006801000001000800000000000000000000000000000000000001000000010000";
    QFile f(QDir::currentPath() +"/ftmp.bmp");
    if ( f.open(QIODevice::WriteOnly) ) {
        QDataStream out(&f);

        SBMPHeader bmpHeader;
        bmpHeader.m_nSize = 0;
        bmpHeader.m_nReserved = 0;
        bmpHeader.m_nOffset = 1078;
        bmpHeader.m_nheader_sz = 40;
        bmpHeader.m_nWidth = const_nIMAGEWIDTH;
        bmpHeader.m_nHeight = const_nIMAGEHEIGHT;
        bmpHeader.m_nplanes = 1;
        bmpHeader.m_nBitspp = 8;
        bmpHeader.m_ncompress_type = 0;
        bmpHeader.m_nBmp_bytesz = 0;
        bmpHeader.m_nHres = 0;
        bmpHeader.m_nVres = 0;
        bmpHeader.m_ncolors = 256;
        bmpHeader.nimpcolors = 256;

        /* convert to big-endian format */
        strHeaderInfo = "424D" +
                        reverse(QString::number(bmpHeader.m_nSize,16).rightJustified(sizeof(bmpHeader.m_nSize)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nReserved,16).rightJustified(sizeof(bmpHeader.m_nReserved)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nOffset,16).rightJustified(sizeof(bmpHeader.m_nOffset)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nheader_sz,16).rightJustified(sizeof(bmpHeader.m_nheader_sz)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nWidth,16).rightJustified(sizeof(bmpHeader.m_nWidth)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nHeight,16).rightJustified(sizeof(bmpHeader.m_nHeight)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nplanes,16).rightJustified(sizeof(bmpHeader.m_nplanes)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nBitspp,16).rightJustified(sizeof(bmpHeader.m_nBitspp)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_ncompress_type,16).rightJustified(sizeof(bmpHeader.m_ncompress_type)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nBmp_bytesz,16).rightJustified(sizeof(bmpHeader.m_nBmp_bytesz)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nHres,16).rightJustified(sizeof(bmpHeader.m_nHres)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_nVres,16).rightJustified(sizeof(bmpHeader.m_nVres)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.m_ncolors,16).rightJustified(sizeof(bmpHeader.m_ncolors)*2,'0').toUpper()) +
                        reverse(QString::number(bmpHeader.nimpcolors,16).rightJustified(sizeof(bmpHeader.nimpcolors)*2,'0').toUpper());
        nlen = strHeaderInfo.length();
        for ( int i = 0; i < (nlen - 1); i += 2 ) {
            ValidByt  = strHeaderInfo.mid(i, 2).toInt(0,16);
            out<<(quint8)ValidByt;
        }

        //ColorInfo 1024 bytes
        for ( int i = 0; i <= 255; i++ ) {
            out<<(quint8) i;
            out<<(quint8) i;
            out<<(quint8) i;
            out<<(quint8) 0;
        }
        //PIXELS

        for ( int nIndex = 0; nIndex < nMax; nIndex ++ ) {
            out<<(quint8) arr_cBuffer[nIndex];
        }
    }
    f.close();
    QMatrix m;
    r_imageFinger = QImage(QDir::currentPath() +"/ftmp.bmp");
    //m.rotate( (double)180 );
    m.scale(-1,1); //horizontal scale
    //m.scale(1,-1); //verical scale
    r_imageFinger = r_imageFinger.transformed( m,Qt::SmoothTransformation );
    r_imageFinger.save(QDir::currentPath() +"/thumb.jpg");
    r_imageFinger = QImage(QDir::currentPath() +"/thumb.jpg");
    if ( QFile::exists(QDir::currentPath() +"/ftmp.bmp") ) {
        QFile::remove(QDir::currentPath() +"/ftmp.bmp");
    }
}


int CFpModule::absSampleToAnsiIso(const PT_DATA *pImage,PT_BYTE *pstrOutputImage, PT_DWORD *pLenstrOutput )
{
    int lenstrOutput = 0;
    PT_BYTE *pData = pstrOutputImage;
    PT_BYTE gSignatureImageAnsiIso[] = { 'F', 'I', 'R', 0 };
    /* Check output buffer size first */

#ifdef OUTPUT_FORMAT_ANSI
    lenstrOutput = const_nIMAGEHEIGHT * const_nIMAGEWIDTH + 36 + 14;
#endif

#ifdef OUTPUT_FORMAT_ISO
    lenstrOutput = const_nIMAGEHEIGHT * const_nIMAGEWIDTH + 32 + 14;
#endif
    if ( lenstrOutput < *pstrOutputImage ) {
        /* strOutput buffer too small, return required size */
        *pLenstrOutput = lenstrOutput;
        return -1;
    }

    /* strOutput buffer size is good, fill real length of output data */
    *pLenstrOutput = lenstrOutput;

    /* Start with signature */
    memcpy( pData, gSignatureImageAnsiIso, sizeof(gSignatureImageAnsiIso));
    pData += sizeof(gSignatureImageAnsiIso);

    /* Specification version */
    putUintBigEndian( &pData, ANSI_ISO_SPECIFICATION_IMAGE_VERSION, 4 );

    /* Record length - upper 2 bytes always zero */
    putUintBigEndian( &pData, 0, 2 );

    /* Real value of the length (utilise the fact *pLenstrOutput is already set) */
    putUintBigEndian( &pData, *pLenstrOutput, 4 );

#ifdef OUTPUT_FORMAT_ANSI

    /* CBEFF PID */
    putUintBigEndian( &pData, CBEFF_ID_UPEK, 4 );

#endif

    /* Device ID - sensor type provided as parameter is used here */
    long DevideId=1711800358;
    putUintBigEndian( &pData, DevideId & 0xff, 2 );

#ifdef OUTPUT_FORMAT_ISO

    /* Acquisition level */
    putUintBigEndian( &pData, 31, 2 );

#endif

    /* Number of fingers/palms */
    putUintBigEndian( &pData, 1, 1 );

    /* Scale units (1 = ppi) */
    putUintBigEndian( &pData, 1, 1 );
    int ResolutionX,ResolutionY;
    ResolutionX=308;
    ResolutionY=308;
    /* Scan resolution */
    putUintBigEndian( &pData,ResolutionX, 2 );
    putUintBigEndian( &pData,ResolutionX, 2 );

    /* Image resolution */
    putUintBigEndian( &pData, ResolutionX, 2 );
    putUintBigEndian( &pData, ResolutionX, 2 );

    /* Pixel depth
     * Simplified decision is made, based of the fact we know pixel depth
     * can be only 8 or 4 here */
    int ColorCount=256;
    putUintBigEndian( &pData, (ColorCount < 256) ? 4 : 8, 1 );

    /* Image compression algorithm (0 = no compression) */
    putUintBigEndian( &pData, 0, 1 );

    /* Reserved */

#ifdef OUTPUT_FORMAT_ISO

    putUintBigEndian( &pData, 0, 2 );

#endif

#ifdef OUTPUT_FORMAT_ANSI

    putUintBigEndian( &pData, 0, 4 );

#endif

    /* Finished with general record header, start image header */

    /* Image block length (data length + 14) */
    putUintBigEndian( &pData, const_nIMAGEHEIGHT * const_nIMAGEWIDTH + 14, 4 );

    /* Position */
    putUintBigEndian( &pData, 0, 1 );

    /* Count of views */
    putUintBigEndian( &pData, 1, 1 );

    /* View number */
    putUintBigEndian( &pData, 1, 1 );

    /* Quality (254 = undefined) */
    putUintBigEndian( &pData, 254, 1 );

    /* Impression type (0 = unknown finger) */
    putUintBigEndian( &pData, 0, 1 );

    /* Horizontal line length */
    putUintBigEndian( &pData, const_nIMAGEWIDTH, 2 );

    /* Vertical line length */
    putUintBigEndian( &pData, const_nIMAGEHEIGHT, 2 );

    /* Reserved */
    putUintBigEndian( &pData, 0, 1 );

    /* Finished with headers, put data */
    memcpy( pData, pImage->Data, const_nIMAGEHEIGHT * const_nIMAGEWIDTH );

    return 0;
}

/* Helper function for writing unsigned values in big endian format */

void CFpModule::putUintBigEndian( PT_BYTE **ppData, PT_DWORD value, PT_DWORD cntBytes )
{
    PT_DWORD mask;
    PT_DWORD shift;

    mask = 0xff << ((cntBytes - 1) * 8);
    shift = (cntBytes - 1) * 8;

    for (;;)
    {
        /* Special treatment for last step */

        if ( shift == 0 )
        {
            **ppData = (PT_BYTE) (value & 0xff);
            (*ppData)++;
            break;
        }

        /* Mask value, shift down, store and advance pointer */

        **ppData = (PT_BYTE) ((value & mask) >> shift);
        (*ppData)++;

        /* Update shift and mas values */
        shift -= 8;
        mask >>= 8;
    }
}

bool CFpModule::enroll(QByteArray &r_byteArrayTemplate)
{
    /* set gui call back to get the fingerprint status  */
    PTSetGUICallbacks (PConn, NULL, NULL, myCallback, NULL);
    PT_BIR* bir;
    m_PStatus = PTEnroll(PConn,PT_PURPOSE_ENROLL,0,&bir,NULL,0,nTIMEOUT_MSECS,0,0,0);
    if ( m_PStatus != PT_STATUS_OK ) {
        printf("Enroll failed.");
        status_info(m_PStatus,m_dialogFingerPrint);
        terminate();
        return false;
    }

    /* conver the bir template data into bytearray */
    PT_BYTE *data = bir->Data;
    int nMax = bir->Header.Length;
    char arr_cBuffer[nMax];
    for ( int nIndex = 0; nIndex < nMax; nIndex ++ ) {
        arr_cBuffer[nIndex] = data[nIndex];
    }
    r_byteArrayTemplate.clear();
    r_byteArrayTemplate.append(QByteArray::fromRawData(arr_cBuffer, nMax));

    /* free the allocated memory */
    PTFree(bir);
    return true;
}

bool CFpModule::enrollFinger(QByteArray &r_byteArrayTemplate)
{
    /* enroll fingerprint template only */
    bool bResponse;
    progressBarCompleted->setVisible(true);
    if ( init() ) {
        bResponse = enroll(r_byteArrayTemplate);
        terminate();
        return bResponse;
    }
    else {
        return false;
    }
}
bool CFpModule::enrollFinger(QByteArray &r_byteArrayTemplate,QImage &r_imageFinger)
{
    /* enroll fingerprint template data & image should be same */
    progressBarCompleted->setVisible(true);
    if ( init() ) {
        DisplayStatus = false;
        if ( ! enroll(r_byteArrayTemplate) ) {
            terminate();
            return false;
        }

        PT_BOOL bResult;
        PT_INPUT_BIR *TemplateIn=NULL;

        /* create template for enrollemnt data */
        createTemplate(r_byteArrayTemplate,&TemplateIn);
        /* verify with the live finger, if not matched cancel the enrollment */
        m_PStatus = PTVerify(PConn, 0, 0, 0, TemplateIn, 0, &bResult, 0, 0, 0, nTIMEOUT_MSECS, PT_TRUE, 0, 0, 0);
        free(TemplateIn);
        if ( m_PStatus != PT_STATUS_OK ) {
            QMessageBox::critical(m_dialogFingerPrint, "Finger Print", "Verification Failed");
            terminate();
            return false;
        }
        if ( bResult == PT_TRUE) {
            /* verfication successfully, then grab the finger image */
            PT_DATA  *pImage;
            DontDisplay=true;
            m_PStatus = PTGrab (PConn, PT_GRAB_TYPE_381_381_8, nTIMEOUT_MSECS, PT_TRUE, &pImage, 0, 0);
            if ( m_PStatus != PT_STATUS_OK ) {
                QMessageBox::critical(m_dialogFingerPrint,"Finger Print", "Image Processing Failed");
                terminate();
                return false;
            }
            labelImage->setPixmap(QPixmap(":/icons-png/bfsucc.png"));
            labelStatus->setText("Success");
            qApp->processEvents();
            drawImage(pImage,r_imageFinger);
            PTFree(pImage);
            terminate();
            return true;
        }
        else {
            QMessageBox::critical(m_dialogFingerPrint,"Finger Print", "Verification Failed");
            terminate();
            return false;
        }
    }
    else {
        return false;
    }
}

bool CFpModule::createTemplate(const QByteArray &r_const_byteArrayTEMPLATE, PT_INPUT_BIR **ppAdaptedTemplate)
{
    PT_BIR *bir;
    /* allocate the memory for create the template */
    *ppAdaptedTemplate = (PT_INPUT_BIR *)malloc(sizeof (PT_INPUT_BIR));
    if ( ! *ppAdaptedTemplate ) {
        /* failed to allocate the memory */
        return false;
    }
    (*ppAdaptedTemplate)->byForm = PT_FULLBIR_INPUT;
    (*ppAdaptedTemplate)->InputBIR.pBIR = (PT_BIR *)malloc(sizeof(PT_BIR) + sizeof(PT_BYTE) + r_const_byteArrayTEMPLATE.count());
    bir = (*ppAdaptedTemplate)->InputBIR.pBIR;

    /* load the header information */
    bir->Header.Length = r_const_byteArrayTEMPLATE.count();
    bir->Header.FactorsMask = 8;
    bir->Header.FormatID = 0;
    bir->Header.FormatOwner = 18;
    bir->Header.HeaderVersion = 1;
    bir->Header.Purpose = 3;
    bir->Header.Quality = -2;
    bir->Header.Type = 4;
    /* load the data */
    for(int nIndex = 0; nIndex < r_const_byteArrayTEMPLATE.count(); nIndex ++ ) {
        bir->Data[nIndex] = (PT_BYTE)r_const_byteArrayTEMPLATE.at(nIndex);
    }
    return true;
}

bool  CFpModule::verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1, const QByteArray &r_const_byteArrayTEMPLATE2, bool &r_bMatch)
{
    progressBarCompleted->setVisible(false);
    if ( init(false) ) {
        /* set gui call back to get the fingerprint status  */
        PTSetGUICallbacks (PConn, NULL, NULL, myCallback, NULL);
        PT_BOOL bResult;
        PT_INPUT_BIR *TemplateIn = NULL;
        PT_INPUT_BIR *TemplateVerify = NULL;

        /* verify the creates two templates. */
        createTemplate(r_const_byteArrayTEMPLATE1, &TemplateIn);
        createTemplate(r_const_byteArrayTEMPLATE2, &TemplateVerify);

        m_PStatus = PTVerifyMatch(PConn,0,0,0,TemplateIn,TemplateVerify,0,&bResult,0,0,0);
#if DEBUG
        qDebug()<<"Staus:"<<m_PStatus<<"Result:"<<bResult;
#endif
        free(TemplateIn);
        free(TemplateVerify);
        if ( m_PStatus != PT_STATUS_OK ) {
            status_info(m_PStatus,m_dialogFingerPrint);
            terminate();
            return false;
        }
        terminate();
        if ( bResult == PT_TRUE ) {
            /* template is matched */
            r_bMatch = true;
        }
        else {
            /* template not matched */
            r_bMatch = false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool  CFpModule::verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE, bool &r_bMatch)
{
    progressBarCompleted->setVisible(false);
    r_bMatch = false;
    if ( init() ) {
        PTSetGUICallbacks (PConn, NULL, NULL, myCallback, NULL);
        PT_BOOL bResult;
        PT_INPUT_BIR *TemplateIn=NULL;

        /* create template for verify with live finger data */
        createTemplate(r_const_byteArrayTEMPLATE,&TemplateIn);
        m_PStatus = PTVerify(PConn,0,0,0,TemplateIn,0,&bResult,0,0,0,nTIMEOUT_MSECS,PT_TRUE,0,0,0);
#if DEBUG
        qDebug()<<"Staus:"<<m_PStatus<<"result:"<<bResult;
#endif
        free(TemplateIn);
        if ( m_PStatus != PT_STATUS_OK ) {
            status_info(m_PStatus,m_dialogFingerPrint);
            terminate();
            return false;
        }
        terminate();
        if ( bResult == PT_TRUE ) {
            /* template is matched */
            r_bMatch = true;
        }
        else {
            /* template not matched */
            r_bMatch = false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool  CFpModule::captureFinger(QByteArray &r_byteArrayTemplate)
{
    progressBarCompleted->setVisible(false);
    if ( init() ) {
        /* set gui call back to get the fingerprint status  */
        PTSetGUICallbacks (PConn, NULL, NULL, myCallback, NULL);
        PT_BIR *bir;
        m_PStatus = PTCapture(PConn,PT_PURPOSE_VERIFY,&bir,nTIMEOUT_MSECS,0,0,0);
        if ( m_PStatus != PT_STATUS_OK ) {
            status_info(m_PStatus,m_dialogFingerPrint);
            terminate();
            return false;
        }

        /* process captured template data into bytearray */
        PT_BYTE *data = bir->Data;
        int nMax = bir->Header.Length;
        char arr_cBuffer[nMax];
        for ( int nIndex = 0; nIndex < nMax; nIndex ++ ) {
            arr_cBuffer[nIndex] = data[nIndex];
        }
        r_byteArrayTemplate.clear();
        r_byteArrayTemplate.append(QByteArray::fromRawData(arr_cBuffer, nMax));

        PTFree(bir);
        terminate();
        return true;
    }
    else {
        return false;
    }
}

void CFpModule::on_pushButtonCancel_clicked()
{
    /* intimate cancel the fingerprint operaton */
    bCancelOpeation = true;
}
