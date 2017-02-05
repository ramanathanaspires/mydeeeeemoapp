#include "cwebcamera.h"
#include <QAction>
#include <QDebug>
#include <QDir>

#include <fcntl.h>
#include "cwebcam.h"
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

CWebcam *webcamCamera;
CWebCamera::CWebCamera()
{
    /* initialize the camera dialog */
    m_dialogCamera = new QDialog;
    m_timerClose.setInterval(60000);
    connect(&m_timerClose, SIGNAL(timeout()), this, SLOT(on_timerClose_timeout()));
//    QPalette p;
//    p.setColor(QPalette::Button,QColor(255,252,215));
//    p.setColor(QPalette::Background,QColor(255,252,215));
//    m_dialogCamera->setAutoFillBackground(true);
//    m_dialogCamera->setPalette(p);
    m_dialogCamera->setStyleSheet("QPushButton {background-color:#d8e7f6; border-width: 2px;"
                          "border-color: darkkhaki; border-style: solid; "
                          "padding: 3px; min-width: 9ex; min-height: 2.5ex;}");

    m_labelStatus = new QLabel(m_dialogCamera);
    m_dialogCamera->setFixedSize(320,240);
    m_labelStatus->setFixedSize(320,215);
    m_pushButtonCancel = new QPushButton(m_dialogCamera);
    connect(m_pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));
    m_pushButtonCapture = new QPushButton(m_dialogCamera);
    m_pushButtonCapture->setAutoDefault(true);
    connect(m_pushButtonCapture, SIGNAL(clicked()), this, SLOT(on_pushButtonCapture_clicked()));
    m_pushButtonCancel->setFixedSize(158,25);
    m_pushButtonCapture->setFixedSize(158,25);
    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    QHBoxLayout *hBoxLayoutBottom = new QHBoxLayout;
    webcamCamera = new CWebcam();
    webcamCamera->setFixedSize(320,215);//old
//    webcamCamera->setFixedSize(320,455);
    connect(webcamCamera,SIGNAL(ready()),this,SLOT(started()));
    connect(webcamCamera,SIGNAL(disconnected()),this,SLOT(deviceDisconnected()));

    vBoxLayoutMain->addWidget(webcamCamera);
    hBoxLayoutBottom->addWidget(m_pushButtonCapture);
    hBoxLayoutBottom->addWidget(m_pushButtonCancel);
    vBoxLayoutMain->addLayout(hBoxLayoutBottom);
    vBoxLayoutMain->setMargin(0);
    vBoxLayoutMain->setSpacing(0);
    m_dialogCamera->setLayout(vBoxLayoutMain);
    m_dialogCamera->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_dialogCamera->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    m_dialogCamera->setWindowModality(Qt::ApplicationModal);
    /* default camera device is video0 but usb device is reattached it maybe attached as video1 */
    if ( QFile::exists("/dev/video0") ) {
        m_strDeviceName = tr("/dev/video0");
    }
    else {
        m_strDeviceName = tr("/dev/video1");
    }
    m_pushButtonCapture->setFont(QFont("sans serif",12,QFont::Bold));//m_pushButtonCapture->setFont(QFont("sans serif",12,1,false));
    m_pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));

    connect(&m_timerFoundCamera, SIGNAL(timeout()), this, SLOT(getDeviceCapabilities()));
    connect(m_dialogCamera, SIGNAL(rejected()), this, SLOT(on_pushButtonCancel_clicked()));
//    m_dialogCamera->setFixedSize(320,460);
//    m_dialogCamera->setGeometry(0,20,320,460);
}

CWebCamera::~CWebCamera()
{
    /* destroy the allocated resources */
    delete webcamCamera;
    delete m_dialogCamera;
}

void CWebCamera::getDeviceCapabilities()
{        
        int nResult = 0;
        if ( ! (nResult = webcamCamera->open(m_strDeviceName.toLatin1().constData())) ) {
            /* read the device capabilities when camera is opened */
            QList<int> listFormat;
            QList<QString> listFormatName;
            if ( m_timerFoundCamera.isActive() ) {
                m_timerFoundCamera.stop();
            }
            listFormat = webcamCamera->getFormatList(listFormatName);

            qDebug()<<" * Device is :" << m_strDeviceName;

            webcamCamera->setFormat(320, 240, listFormat.at(0) );

        }
        else {
            qDebug()<<" * No webcam pluged in (unable to open ";
            qDebug()<<" * Waiting for you .";
            m_labelStatus->setText("No Webcam found !\n");
            m_timerFoundCamera.start(2000);
            //TODO: This utility could use QDbus...
        }
}

void CWebCamera::deviceDisconnected()
{
    QMessageBox::critical(m_dialogCamera, "Camera", "Camera - device not found..!");
    on_timerClose_timeout();
}

bool CWebCamera::previewCamera(QImage &r_imageCaptured)
{    
    int fd = ::open(m_strDeviceName.toLatin1(), O_RDWR, 0);
    if ( fd < 0 ) {
        QMessageBox::critical(0,"Camera","Camera - device not found..");
        return false;
    }
    ::close(fd);

    gLoadIntoSharedPIC(const_strPAUSE_THREADS);
    m_pushButtonCapture->setEnabled(false);
    m_labelStatus->clear();
    m_labelStatus->setPalette(QPalette(QColor(Qt::black)));
    m_labelStatus->setAutoFillBackground(true);
    m_labelStatus->setFont(QFont("sans serif",14,QFont::Bold));
    m_labelStatus->setText("Please Wait...\nInitializing Camera...");
    m_labelStatus->setAlignment(Qt::AlignCenter);
    webcamCamera->clear();

    getDeviceCapabilities();
    int defaultSat, defaultBright, defaultCont;

    webcamCamera->defaultCtrlVal(CWebcam::Saturation, defaultSat); // Get default Saturation
    webcamCamera->defaultCtrlVal(CWebcam::Brightness, defaultBright);  // Get default Brightness
    webcamCamera->defaultCtrlVal(CWebcam::Contrast, defaultCont);  // Get default Contrast

    #ifdef USE_UVCVIDEO
        int defaultFreq, defaultSharp;
        webcamCamera->defaultCtrlVal(CWebcam::PowerLineFreq, defaultFreq);  // Get default Frequency
        webcamCamera->defaultCtrlVal(CWebcam::Sharpness, defaultSharp);  // Get default Sharpness
        bool m_bPanTiltSupported = webcamCamera->m_bPanTiltSupported();
    #endif
//    defaultSat=32;
//    defaultBright=5;
//    defaultCont=15;
//    webcamCamera->changeCtrl(CWebcam::Saturation, defaultSat); // Saturation to default
//    webcamCamera->changeCtrl(CWebcam::Brightness, defaultBright);  // Brightness to default
//    webcamCamera->changeCtrl(CWebcam::Contrast, defaultCont);  // Contrast to default
    #ifdef USE_UVCVIDEO
        webcamCamera->changeCtrl(CWebcam::PowerLineFreq, defaultFreq);  // Frequency to default
        webcamCamera->changeCtrl(CWebcam::Sharpness, defaultSharp);  // Contrast to default
        if (m_bPanTiltSupported)
                webcamCamera->changeCtrl(CWebcam::PanTiltReset); // Reset to the center position
    #endif
    m_pushButtonCapture-> setText("Capture");
    m_pushButtonCancel->setText("Exit");
    m_pushButtonCapture->setShortcut(Qt::Key_F2);
//    m_pushButtonCapture->setShortcut(QKeySequence(Qt::Key_F2));
    m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    m_pushButtonCapture->setIcon(QIcon(":/icons-png/capture.png"));
    m_pushButtonCancel->setIcon(QIcon(":/icons-png/exit.png"));
    m_bSavedImage = false;
    startStopVideo();
    m_timerClose.start();
    /* Below code is used to switch ON flash light through controller */
//    gpheripheralsPIC->enableModule(CPheripherals::emodule_FlashLight, true);
    m_dialogCamera->exec();

    m_timerClose.stop();
    if ( m_bSavedImage ) {
        /* captured image */
        r_imageCaptured = webcamCamera->captured();
    }
    if ( m_timerFoundCamera.isActive() ) {
        m_timerFoundCamera.stop();
    }
    webcamCamera->close();
    m_dialogCamera->close();
    gLoadIntoSharedPIC(const_strWAKEUP_THREADS);
    return m_bSavedImage;
}

void CWebCamera::startStopVideo()
{
    int ret = 0;
    if ( webcamCamera->isStreaming() ) {
        /* stop the streaming */
        qDebug()<<"webcamCamera is Stopped";
        if ( webcamCamera->stopStreaming() == EXIT_SUCCESS ) {
                qDebug()<<"Stop Streaming";
        }
    }
    else {
        if ( ! webcamCamera->isOpened() ) {
            webcamCamera->open(m_strDeviceName.toLatin1().constData());
        }        
        /* start the streaming */
        ret = webcamCamera->startStreaming();
        if ( ret == EXIT_FAILURE ) {
            m_labelStatus->setText("An error occured while restarting the webcamCamera.");
            qDebug()<<"***Unable to start streaming.";
        }
    }
}

void CWebCamera::started()
{
    /* enable the button when streaming is started */
    m_pushButtonCapture->setEnabled(true);
    m_pushButtonCapture->setFocus();
}

void  CWebCamera::on_timerClose_timeout()
{
    if ( QString::compare(m_pushButtonCapture->text(),"Capture") != 0 ) {
        on_pushButtonCancel_clicked();
    }
    on_pushButtonCancel_clicked();
}

void CWebCamera::on_pushButtonCapture_clicked()
{
    m_timerClose.stop();
    m_timerClose.start();
    if ( QString::compare(m_pushButtonCapture->text(),"OK") == 0 ) {
        m_bSavedImage = true;
        m_dialogCamera->close();
    }
    else {
        /* pause the streaming */
        //PlayWav(":/Resources/capture.wav");

        /* Below code is used to switch OFF flash light through controller */
//        gpheripheralsPIC->enableModule(CPheripherals::emodule_FlashLight, false);
        webcamCamera->setPause(true); //if(webcamCamera->isStreaming()) webcamCamera->stopStreaming();
        m_pushButtonCapture->setText("OK");
        m_pushButtonCancel->setText("Cancel");
        m_pushButtonCapture->setIcon(QIcon(":/icons-png/ok.png"));
        m_pushButtonCancel->setIcon(QIcon(":/icons-png/cancel.png"));
        m_pushButtonCapture->setShortcut(QKeySequence(Qt::Key_F2));
        m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    }
}

void CWebCamera::on_pushButtonCancel_clicked()
{
    m_timerClose.stop();
    m_timerClose.start();
    if ( QString::compare(m_pushButtonCapture->text(), "Capture" ) == 0 ) {
        /* Below code is used to switch OFF flash light through controller */
//        gpheripheralsPIC->enableModule(CPheripherals::emodule_FlashLight, false);
        m_bSavedImage = false;
        m_dialogCamera->close();
    }
    else {
        /* cancel the paused for update the streams */

        /* Below code is used to switch ON flash light through controller */
//        gpheripheralsPIC->enableModule(CPheripherals::emodule_FlashLight, true);
        webcamCamera->setPause(false);//webcamCamera->startStreaming();
        m_pushButtonCapture-> setText("Capture");
        m_pushButtonCancel->setText("Exit");
        m_pushButtonCapture->setIcon(QIcon(":/icons-png/capture.png"));
        m_pushButtonCancel->setIcon(QIcon(":/icons-png/exit.png"));
        m_pushButtonCapture->setShortcut(QKeySequence(Qt::Key_F2));
        m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    }
}

//void CWebCamera::error(int nValue)
//{
//    switch (nValue){
//        case 16:
//            m_labelStatus->setText("Camera is already in use. You still can control the webcamCamera.");
//            break;
//        default :
//            m_labelStatus->setText("An unknown error occured.");
//            qDebug()<<"An unknown error occured";
//            break;
//    }
//}
