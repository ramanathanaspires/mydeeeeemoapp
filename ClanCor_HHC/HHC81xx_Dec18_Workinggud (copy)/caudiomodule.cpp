#include "caudiomodule.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include "cglobal.h"

#ifdef Q_WS_QWS
    #define AUDIO_DEVICE_USB 1
#else
    #define AUDIO_DEVICE_DSP 1
#endif

const int nCLOSE_DIALOG_TIMEOUT             = 60000;
using namespace ClanCor;
using namespace Global;

CPheripherals *pheripheralsPIC_Audio = NULL;

CAudioModule::CAudioModule()
{
#ifdef AUDIO_DEVICE_DSP
    DEBUGMESSAGE("audio:/dev/dsp ");
#endif
#ifdef AUDIO_DEVICE_USB
    DEBUGMESSAGE("usb audio:/dev/audio1 ");
#endif

    if ( NULL == gpheripheralsPIC ) {
        if ( gsharedMemPIC.attach() ) {
            /* do the process for not first application call */
            gbFirsCall = false;
            gLoadIntoSharedPIC(const_strSTARTED);
            pheripheralsPIC_Audio = new CPheripherals(COPROCESSOR_PORTNAME);
            gpheripheralsPIC = pheripheralsPIC_Audio;
            gLoadIntoSharedGSM(const_strCOMPLETED);
        }
    }

    /* create widget for display when converting to mp3 data */
    m_widgetMsgScreen = new QWidget;
    m_labelMsgStatus = new QLabel(m_widgetMsgScreen);
    m_widgetMsgScreen->setFixedSize(250,120);
    m_widgetMsgScreen->setWindowFlags(Qt::Dialog |  Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    m_widgetMsgScreen->setWindowModality(Qt::ApplicationModal);
    m_widgetMsgScreen->setWindowTitle("Please Wait ....");
    m_labelMsgStatus->setFixedSize(250,120);
    m_labelMsgStatus->setStyleSheet("background-color:white;color:black");
    m_labelMsgStatus->setFont(QFont("sans serif",14,2,false));
    m_labelMsgStatus->setAlignment(Qt::AlignCenter);
    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    vBoxLayoutMain->addWidget(m_labelMsgStatus);
    vBoxLayoutMain->setSpacing(0);
    vBoxLayoutMain->setMargin(0);
    m_widgetMsgScreen->setLayout(vBoxLayoutMain);
    m_widgetMsgScreen->setGeometry(30,60,260,120);
    m_nRate=32000;   /* the sampling rate */
    m_nSize=16;      /* sample size: 8 or 16 bits */
    m_nChannels=1;  /* 1 = mono 2 = stereo */
    m_nMaxRecording=90;

    /* create the audio dialog for recording & playing */
    m_dialogAudio = new QDialog;
    m_labelDisplayText = new QLabel();
    m_labelDisplayText->setFont(QFont("sans serif",14,1,false));
    m_labelDisplayText->setAlignment(Qt::AlignCenter);
    m_labelDisplayText->setWordWrap(true);
    m_labelDisplayText->setPalette(QPalette(QColor(Qt::black)));
    m_labelDisplayText->setAutoFillBackground(true);
    m_dialogAudio->setFixedSize(320,240);
    m_dialogAudio->setStyleSheet("QDialog {background-color:#eee8aa;} QPushButton {background-color:#e5ecff; color:black;border-width: 2px;border-style: solid; border-style: solid; border-color:black;} QPushButton:focus { background-color: #c1d7ee;}");
    connect(this, SIGNAL(error()), this, SLOT(displayError()));
    connect(this, SIGNAL(stopThread()), this, SLOT(stopProcess()));

    QPalette p;
    p.setColor(QPalette::Background, QColor(240,240,200));
    m_dialogAudio->setAutoFillBackground(true);
    m_dialogAudio->setPalette(p);

    m_labelDisplayText->setFixedSize(320,110);
//    m_pushButtonRecord = new QPushButton("Record -F1");
    m_pushButtonRecord = new QPushButton("Record");
    connect(m_pushButtonRecord, SIGNAL(clicked()), this, SLOT(on_pushButtonRecord_clicked()));
    m_pushButtonPlay = new QPushButton("&Play");
    connect(m_pushButtonPlay, SIGNAL(clicked()), this, SLOT(on_pushButtonPlay_clicked()));
//    m_pushButtonStop = new QPushButton("Stop -F3");
    m_pushButtonStop = new QPushButton("Stop");
    connect(m_pushButtonStop, SIGNAL(clicked()), this, SLOT(on_pushButtonStop_clicked()));
//    m_pushButtonOk = new QPushButton("Ok -F2");
    m_pushButtonOk = new QPushButton("Ok");
    connect(m_pushButtonOk, SIGNAL(clicked()), this, SLOT(on_pushButtonOk_clicked()));
    m_pushButtonOk->setFont(QFont("sans serif",12,QFont::Bold));
//    m_pushButtonCancel = new QPushButton("Exit -F4");
    m_pushButtonCancel = new QPushButton("Exit");
    connect(m_pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));
    m_pushButtonCancel->setFont(QFont("sans serif",12,QFont::Bold));
//    m_pushButtonRecord->setShortcut(QKeySequence(Qt::Key_F1));
    m_pushButtonPlay->setShortcut(QKeySequence("P"));
//    m_pushButtonStop->setShortcut(QKeySequence(Qt::Key_F3));
//    m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F2));
//    m_pushButtonCancel->setShortcut(QKeySequence(Qt::Key_F4));
    m_pushButtonRecord->setFixedSize(100,25);
    m_pushButtonPlay->setFixedSize(100,25);
    m_pushButtonStop->setFixedSize(100,25);
    m_pushButtonOk->setFixedSize(155,30);
    m_pushButtonCancel->setFixedSize(155,30);
    m_pushButtonRecord->setIcon(QIcon(":/icons-png/record.png"));
    m_pushButtonPlay->setIcon(QIcon(":/icons-png/play.png"));
    m_pushButtonStop->setIcon(QIcon(":/icons-png/stop.png"));
    m_pushButtonOk->setIcon(QIcon(":/icons-png/ok.png"));
    m_pushButtonRecord->setIconSize(QSize(20,20));
    m_pushButtonPlay->setIconSize(QSize(20,20));
    m_pushButtonStop->setIconSize(QSize(20,20));
    m_pushButtonOk->setIconSize(QSize(25,25));
    m_pushButtonCancel->setIconSize(QSize(25,25));
    m_pushButtonCancel->setIcon(QIcon(":/icons-png/exit.png"));
    m_labelStatus = new QLabel("Status:");
    m_labelStatus->setFixedSize(140,25);
    m_labelStatus->setFont(QFont("sans serif",12,1,false));
    m_labelTime = new QLabel("00:00/00:00");
    m_labelTime->setFont(QFont("sans serif",12,QFont::Bold));
    m_labelVolume = new QLabel(" 100 %");
    m_labelVolume->setFont(QFont("sans serif",12,QFont::Bold));
    m_sliderTime = new QSlider(Qt::Horizontal);
    m_sliderTime->setFocusPolicy(Qt::StrongFocus);
    m_sliderTime->setTickPosition(QSlider::NoTicks);
    m_sliderTime->setTickInterval(1);
    m_sliderTime->setFixedSize(200,25);
    m_sliderVolume = new QSlider(Qt::Horizontal);
    m_sliderVolume->setFocusPolicy(Qt::StrongFocus);
    m_sliderVolume->setTickPosition(QSlider::TicksBelow);
    m_sliderVolume->setTickInterval(10);
    m_sliderVolume->setMinimum(0);
    m_sliderVolume->setMaximum(100);
    m_sliderVolume->setValue(100);
    m_sliderVolume->setFixedSize(75,25);
    connect(m_sliderVolume, SIGNAL(valueChanged(int)), this, SLOT(updateVolume()));
    m_actionVolume = new QAction(QIcon(":/icons-png/volume.png"),"",m_dialogAudio);
    connect(m_actionVolume, SIGNAL(triggered()), this, SLOT(muteOnOff()));
    m_toolbarProgress = new QToolBar("Progress Status");
    m_toolbarProgress->addSeparator();
    m_toolbarProgress->addWidget(m_sliderTime);
    m_toolbarProgress->addSeparator();
    m_toolbarProgress->addWidget(m_labelTime);
    m_toolbarProgress->setFixedHeight(30);
    m_toolbarStatus = new QToolBar("Status");
    m_toolbarStatus->addWidget(m_labelStatus);
    m_toolbarStatus->addSeparator();
    m_toolbarStatus->addAction(m_actionVolume);
    m_toolbarStatus->addWidget(m_sliderVolume);
    m_toolbarStatus->addSeparator();
    m_toolbarStatus->addWidget(m_labelVolume);
    m_toolbarStatus->setFixedHeight(30);
    QVBoxLayout *vBoxLayoutAudio = new QVBoxLayout;
    QHBoxLayout *hBoxLayoutTop = new QHBoxLayout;
    QHBoxLayout *hBoxLayoutBottom = new QHBoxLayout;
    hBoxLayoutTop->addWidget(m_pushButtonRecord);
    hBoxLayoutTop->addWidget(m_pushButtonStop);
    hBoxLayoutTop->addWidget(m_pushButtonPlay);
    hBoxLayoutBottom->addWidget(m_pushButtonOk);
    hBoxLayoutBottom->addWidget(m_pushButtonCancel);
    vBoxLayoutAudio->addWidget(m_labelDisplayText);
    vBoxLayoutAudio->addLayout(hBoxLayoutTop);
    vBoxLayoutAudio->addWidget(m_toolbarProgress);
    vBoxLayoutAudio->addWidget(m_toolbarStatus);
    vBoxLayoutAudio->addLayout(hBoxLayoutBottom);
    vBoxLayoutAudio->setMargin(0);
    vBoxLayoutAudio->setSpacing(0);
    m_dialogAudio->setLayout(vBoxLayoutAudio);
    m_dialogAudio->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m_dialogAudio->setWindowModality(Qt::ApplicationModal);
    m_timerClose.setInterval(nCLOSE_DIALOG_TIMEOUT);
    connect(&m_timerClose, SIGNAL(timeout()), this, SLOT(on_timerClose_timeout()));
}

CAudioModule::~CAudioModule()
{
    system(QString("amixer set Speaker " + gConvertToString( m_nPrevSpeakerVol) +"%").toLatin1());
    if ( m_bMuted ) {
        system(QString("amixer set Speaker mute").toLatin1());
    }
    else {
        system(QString("amixer set Speaker unmute").toLatin1());
    }
    if ( m_bMicMuted ) {
        system(QString("amixer sset Mic nocap").toLatin1());
    }
    else {
        system(QString("amixer sset Mic cap").toLatin1());
    }

    if ( NULL != pheripheralsPIC_Audio ) {
        if(!gsharedMemPIC.detach())
        {
            qDebug()<<"\Failed while detaching shared memory..";
        }
        delete pheripheralsPIC_Audio;
        pheripheralsPIC_Audio = NULL;
        gpheripheralsPIC = NULL;
    }
    /* free the alocated resources */
    delete m_dialogAudio;
    delete m_widgetMsgScreen;
}

bool CAudioModule::enableAudio()
{
    /* enable the audio deice */
    if ( ! QFile::exists("/dev/audio") ) {
        gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,true);
        sleep(1);
        if ( ! QFile::exists("/dev/audio") ) {
            sleep(1);
        }
    }
    return  QFile::exists("/dev/audio");
}

void CAudioModule::initVolumeDetails()
{
    system(QString("alsactl restore").toLatin1());
    QString strData = "";
    if ( gSysCommand("amixer","get 'Speaker'",strData) ) {
        /* get the speaker volume from received data */
        int nStart = strData.indexOf("[");
        int nEnd = strData.indexOf("]",nStart);
        if ( nStart > 0 && nEnd > 0 ) {
             m_nPrevSpeakerVol = QVariant(strData.mid(nStart + 1, nEnd - nStart-2)).toInt();
            if ( strData.right(5).contains("on") ) {
                m_bMuted = false;
            }
            else {
                m_bMuted = true;
            }
            m_sliderVolume->setValue( m_nPrevSpeakerVol);
            m_bMute =! m_bMuted;
        }
        if ( gSysCommand("amixer","get 'Mic'",strData) ) {
            /* get the mic volume from received data */
            if ( strData.right(5).contains("on") ) {
                m_bMicMuted = false;
            }
            else {
                m_bMicMuted = true;
            }
        }
        muteOnOff();
        updateVolume();
    }
    m_strDummy.clear();
}

bool CAudioModule::init()
{
    /* open sound device */
    #ifdef AUDIO_DEVICE_DSP
        m_nFd =::open("/dev/dsp", O_RDWR,0);
        gSysCommand("amixer -D 'hw:0'"); //change Device
    #endif
    #ifdef AUDIO_DEVICE_USB
//        m_nFd =::open("/dev/audio", O_RDWR,0);
//        qDebug()<<"\r audio device in read mode";
         m_nFd =::open("/dev/audio", O_RDONLY,0);
    #endif
//         qDebug()<<"\r value"<<m_nFd;
    if (m_nFd < 0) {
        QMessageBox::critical(0,"Audio Recording","Audio Device is Not connected");
        DEBUGMESSAGE("open audio device failed ");
        ::close(m_nFd);
        return false;
    }else

  /* set sampling parameters */
  m_nArg = m_nSize;   /* sample size */
  m_nStatus =::ioctl(m_nFd, SOUND_PCM_WRITE_BITS, &m_nArg);
  if ( m_nStatus == -1 ) {
      DEBUGMESSAGE("SOUND_PCM_WRITE_BITS ioctl failed");
  }
  if ( m_nArg != m_nSize ) {
      DEBUGMESSAGE("unable to set sample size");
  }
  m_nArg = m_nChannels;  /* mono or stereo */
  m_nStatus = ::ioctl(m_nFd, SOUND_PCM_WRITE_CHANNELS, &m_nArg);
  if ( m_nStatus == -1 ) {
      DEBUGMESSAGE("SOUND_PCM_WRITE_CHANNELS ioctl failed");
  }
  if ( m_nArg != m_nChannels ) {
      DEBUGMESSAGE("unable to set number of channels\n");
  }

  m_nArg = m_nRate;   /* sampling rate */
  m_nStatus = ::ioctl(m_nFd,SOUND_PCM_WRITE_RATE, &m_nArg);
  if ( m_nStatus == -1 ) {
      DEBUGMESSAGE("SOUND_PCM_WRITE_WRITE ioctl failed");
  }
  return true;
}

bool CAudioModule::record(QByteArray &r_byteArrayRecordedData,
                          CAudio::E_AudioQuality eQuality,
                          const QString &r_const_strDISPLAYTEXT)
{
    if ( ! enableAudio() ) {
        QMessageBox::critical(0,"Audio Recording","Audio - Device not found..!");
        return false;
    }
    m_bAudioRecording = true;
    m_bPlaying = false;
    m_bMute = false;
    initVolumeDetails();
    /* the sampling rate */
    switch ( (int) eQuality ) {
        case CAudio::eAudioQuality_VERY_LOW:
            m_nRate = 16000;
            break;
        case CAudio::eAudioQuality_LOW:
            m_nRate = 24000;
            break;
        case CAudio::eAudioQuality_MEDIUM:
            m_nRate = 32000;
            break;
        case CAudio::eAudioQuality_HIGH:
            m_nRate = 48000;
            break;
        default:
            m_nRate = 64000;
    }

    m_nSize = 16;      /* sample size: 8 or 16 bits */
    m_nChannels = 1;  /* 1 = mono 2 = stereo */
    m_nCountPerSec = ( 1 * m_nRate * m_nSize * m_nChannels ) / 8;
    enableButton(true);
    m_pushButtonRecord->setVisible(true);
    m_pushButtonPlay->setVisible(true);
    m_pushButtonStop->setVisible(true);
    m_pushButtonOk->setText("Ok -F2");
    m_pushButtonOk->setIcon(QIcon(":/icons-png/ok.png"));
    m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F2));
    m_labelDisplayText->setFixedSize(320,110);
    m_bRecorded = false;
    if ( init() ) {
        /* show the dialog only device is initialized */
        gLoadIntoSharedPIC(const_strPAUSE_THREADS);
        m_sliderTime->setValue(0);
        m_sliderTime->setEnabled(false);
        m_pushButtonPlay->setEnabled(false);
        m_pushButtonOk->setEnabled(false);
        m_labelStatus->setText("Ready");
        m_labelTime->setText(formatTime(0) +"/" + formatTime(m_nMaxRecording));
        m_labelDisplayText->setText(r_const_strDISPLAYTEXT);
        m_pushButtonStop->setEnabled(false);
        m_timerClose.start();
        m_dialogAudio->exec();
        m_timerClose.stop();
        gLoadIntoSharedPIC(const_strWAKEUP_THREADS);
        if ( m_bRecorded ) {
            /* return the recorded converted mp3 data */
            r_byteArrayRecordedData = m_byteArraySaved;
        }
        closed();
        msleep(500);
    }
    gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,false);
    return m_bRecorded;
}

void  CAudioModule::on_timerClose_timeout()
{
    if ( ! isRunning() ) {
        on_pushButtonCancel_clicked();
    }
}

bool CAudioModule::play(const QByteArray &r_const_byteArrayDATA, const QString &r_const_strDISPLAYTEXT)
{
    if ( ! enableAudio() ) {
        QMessageBox::critical(0,"Audio Recording","Audio - Device not found..!");
        return false;
    }
    m_bAudioRecording = false;
    m_bPlaying = true;
    m_bMute = false;
    m_pushButtonRecord->setVisible(false);
    m_pushButtonPlay->setVisible(false);
    m_pushButtonStop->setVisible(false);
    m_labelDisplayText->setFixedSize(320,145);
    initVolumeDetails();
    if ( init() ) {
        /* show the dialog only device is initialized */

        m_byteArraySaved = r_const_byteArrayDATA;
        m_pushButtonOk->setText("");
        m_pushButtonOk->setIcon(QIcon(":/icons-png/pause.png"));
        m_pushButtonOk->setEnabled(true);
        m_sliderTime->setValue(0);
        m_sliderTime->setEnabled(false);
        m_pushButtonPlay->setEnabled(false);
        m_pushButtonCancel->setEnabled(true);
        m_labelStatus->setText("Loading..");
        m_labelDisplayText->setText(r_const_strDISPLAYTEXT);
        m_pushButtonStop->setEnabled(false);
        on_pushButtonOk_clicked();
        m_dialogAudio->exec();
        closed();
        gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,false);
        return true;
    }
    else {
        gpheripheralsPIC->enableModule(CPheripherals::emodule_AUDIO,false);
        return false;
    }
}

void CAudioModule::on_pushButtonRecord_clicked()
{
    ::close(m_nFd);
    init();
#ifdef AUDIO_DEVICE_DSP
    gSysCommand("amixer -D 'hw:0' set Master unmute");
#endif
#ifdef AUDIO_DEVICE_USB
    gSysCommand("amixer  set Speaker mute");
    if ( ! m_bMicMuted ) {
        gSysCommand("amixer  sset Mic cap");
    }
#endif
    m_actionVolume->setIcon(QIcon(":/icons-png/volume.png"));
    enableButton(false);
    m_actionVolume->setEnabled(false);
    m_sliderVolume->setEnabled(false);
    m_pushButtonStop->setEnabled(true);
    m_pushButtonStop->setFocus();
    m_sliderTime->setEnabled(false);
    m_labelStatus->setText("Recording...");
    m_sliderTime->setValue(0);
    m_sliderTime->setMaximum(m_nMaxRecording);
    m_labelTime->setText(formatTime(0) +"/" + formatTime(m_nMaxRecording));
    m_byteArraySaved.clear();
    m_byteArrayTemp.clear();
    m_bRecording = true;
    start();
}

void CAudioModule::on_pushButtonPlay_clicked()
{
#ifdef AUDIO_DEVICE_DSP
    gSysCommand("amixer -D 'hw:0' set Maser 100%");
#endif
#ifdef AUDIO_DEVICE_USB
    gSysCommand("amixer sset Mic nocap");
    if ( ! m_bMute ) {
        gSysCommand("amixer set Speaker unmute");
    }
#endif
    updateVolume();
    enableButton(false);
    m_pushButtonStop->setEnabled(true);
    m_sliderTime->setEnabled(true);
    m_labelStatus->setText("Playing...");
    m_nMaxPlaying = ( m_byteArraySaved.count() / m_nCountPerSec );
    m_sliderTime->setValue(0);
    m_sliderTime->setMaximum(m_nMaxPlaying);
    m_labelTime->setText(formatTime(0) + "/" + formatTime(m_nMaxPlaying));
    m_bPlaying = true;
    init();
    if ( ! isRunning() ) {
        start();
    }
    m_pushButtonStop->setFocus();
}

void CAudioModule::on_pushButtonStop_clicked()
{
    m_actionVolume->setEnabled(true);
    m_sliderVolume->setEnabled(true);
    //if (m_bPlaying==false) msleep(200);
    m_bPlaying = false;
    m_bRecording = false;
    m_pushButtonStop->setEnabled(false);
}

void CAudioModule::stopProcess()
{
    /* stop the thread */
    wait();
    terminate();
    msleep(50);

    if ( m_pushButtonOk->text() != "Play -F2" || m_sliderTime->value() == m_sliderTime->maximum() ) {
        m_sliderTime->setValue(0);
        m_labelTime->setText(formatTime(m_sliderTime->value()) + "/" + formatTime(m_sliderTime->maximum()));
        if ( m_byteArraySaved.count() < m_nCountPerSec ) {
            m_pushButtonPlay->setEnabled(false);
            m_pushButtonRecord->setFocus();
        }
        m_sliderTime->setEnabled(false);
        m_labelStatus->setText("Stopped");
        m_byteArrayTemp.clear();
    }
    on_pushButtonStop_clicked();
    m_nMaxPlaying = ( m_byteArraySaved.count() / m_nCountPerSec );
    enableButton(true);
    m_pushButtonPlay->setFocus();
    m_pushButtonOk->setEnabled(true);
    if ( ! m_bAudioRecording ) {
        m_pushButtonOk->setText("Play -F2");
        m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F2));
        m_pushButtonOk->setIcon(QIcon(":/icons-png/play.png"));
    }
    else {
        m_sliderTime->setMaximum(m_nMaxPlaying);
        m_labelTime->setText(formatTime(0) + "/" + formatTime(m_nMaxPlaying));
    }
    ::close(m_nFd);
    m_timerClose.stop();
    m_timerClose.start();
}

void CAudioModule::on_pushButtonOk_clicked()
{
    m_timerClose.stop();
    if ( QFile::exists("/tmp/test.pcm") ) {
        QFile::remove("/tmp/test.pcm");
    }
    if ( m_bAudioRecording ) {
       m_labelMsgStatus->setText("Converting Raw Data into\n Mp3 Format");
       m_widgetMsgScreen->show();
       qApp->processEvents();
       QFile fileOut("/tmp/test.pcm");
       if ( fileOut.open(QIODevice::WriteOnly) ) {
           fileOut.write(m_byteArraySaved);
           fileOut.setPermissions(QFile::ReadOwner | QFile::WriteOwner |
                                  QFile::ExeOwner | QFile::ReadGroup |
                                  QFile::ExeGroup | QFile::ReadOther |
                                  QFile::ExeOther);
           fileOut.close();
       }
       ::close(m_nFd);       

       /* converting raw pcm data into mp3 data using lame */
       gSysCommand("/root/lame -m s -a -r -s "+QString::number(m_nRate/2) +" -b "+ QString::number(m_nRate/1000) +" -x /tmp/test.pcm" +" /tmp/test.mp3");
       m_widgetMsgScreen->close();
       qApp->processEvents();
       QFile fileIn("/tmp/test.mp3");
       if ( fileIn.open(QIODevice::ReadWrite) ) {
           QByteArray byteArrayData;
           byteArrayData = fileIn.readAll();
           fileIn.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
           fileIn.close();
           m_byteArraySaved = byteArrayData;
           byteArrayData.clear();
           m_bRecorded = true;
       }
       else {
           m_bRecorded = false;
           DEBUGMESSAGE("Couldn't save the file");
       }
       m_dialogAudio->close();
   }
   else {
       /* audio playing data */
//       qDebug()<<"\r in play option";
       if ( m_pushButtonOk->text() == "Pause -F3") {
           m_sliderTime->setEnabled(false);
           m_bPlaying = false;
           m_pushButtonOk->setText("Play -F2");
           m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F2));
           m_pushButtonOk->setIcon(QIcon(":/icons-png/play.png"));
           m_labelStatus->setText("Paused..");
           return;
       }
       else if ( m_pushButtonOk->text() == "Play -F2") {
           m_sliderTime->setEnabled(true);
           m_bPlaying = true;
           ::close(m_nFd);
           init();
           start();
           m_pushButtonOk->setText("Pause -F3");
           m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F3));
           m_pushButtonOk->setIcon(QIcon(":/icons-png/pause.png"));
           m_labelStatus->setText("Playing..");
       }
       else {
           m_labelMsgStatus->setText("Loading Data into Memory");
           m_widgetMsgScreen->show();
           qApp->processEvents();
           m_pushButtonOk->setText("Pause -F3");
           m_pushButtonOk->setShortcut(QKeySequence(Qt::Key_F3));
           if ( QFile::exists("/tmp/test.mp3") ) {
               QFile::remove("/tmp/test.mp3");
           }
           QFile fileOut("/tmp/test.mp3");
           if ( fileOut.open(QIODevice::WriteOnly) ) {
               fileOut.write(m_byteArraySaved);
               fileOut.close();
           }
           m_byteArraySaved.clear();
           /* converting mp3 data into pcm data using lame */
           gSysCommand("/root/lame --decode -t /tmp/test.mp3 /tmp/test.pcm", "",m_strDummy);
           int nStart,nEnd;
           nStart = m_strDummy.indexOf("(",0);
           nEnd = m_strDummy.indexOf("kHz",0);
           m_nRate = (int) m_strDummy.mid(nStart+1,nEnd-nStart-2).toFloat()*1000;
           nEnd = m_strDummy.indexOf("channel",0);
           m_nChannels = m_strDummy.mid(nEnd-2,1).toInt();
           nStart = m_strDummy.indexOf("(",nEnd);
           nEnd = m_strDummy.indexOf("bit",nStart);
           m_nSize = m_strDummy.mid(nStart+1,nEnd-nStart-2).toInt();
           DEBUGMESSAGE("Rate:" + gConvertToString(m_nRate) +
                        "Channel:" + gConvertToString(m_nChannels) +
                        "Size:" + gConvertToString(m_nSize));
           m_strDummy.clear();
           m_nCountPerSec=1*m_nRate*m_nSize*m_nChannels/8;
           ::close(m_nFd);
           m_labelStatus->setText("Ready");
           QFile fileIn("/tmp/test.pcm");
           if ( fileIn.open(QIODevice::ReadOnly) ) {
                 m_byteArraySaved= fileIn.readAll();
                 DEBUGMESSAGE("Raw count:" + gConvertToString(m_byteArraySaved.count()/1024) +" Kb");
                 fileIn.close();
                 qDebug()<<"\rb4 play";
                 on_pushButtonPlay_clicked();
            }
            m_widgetMsgScreen->close();
            qApp->processEvents();            
         }
    }
}

void CAudioModule::on_pushButtonCancel_clicked()
{
    m_bPlaying = false;
    m_bRecorded = false;
    m_dialogAudio->close();
}

void CAudioModule::closed()
{
    if ( isRunning() ) {
        on_pushButtonStop_clicked();
        on_pushButtonCancel_clicked();
    }
    if ( isRunning() ) {
        /* stop the thread */
        wait();
        terminate();
    }
    ::close(m_nFd);
    if ( QFile::exists("/tmp/test.pcm") ) {
        QFile::remove("/tmp/test.pcm");
    }
    if ( QFile::exists("/tmp/test.mp3") ) {
        QFile::remove("/tmp/test.mp3");
    }
    m_strDummy.clear();
    m_labelDisplayText->clear();
    m_byteArraySaved.clear();
    m_dialogAudio->close();
}

void CAudioModule::run()                                                  // continuous snEnding function and receiving function
{
    if ( m_bPlaying ) {
        /* playing data */
        while ( m_bPlaying ) {
            playData();
       }
    }
    else {
        /* recording data */
        char arr_Buffer[1000];
        while ( m_bRecording ) {
            m_nStatus = ::read(m_nFd, arr_Buffer, sizeof(arr_Buffer)); /* record some sound */
            if ( m_nStatus != sizeof(arr_Buffer) ) {
//                qDebug()<<"read wrong number of bytes:"<<"Size:"<<m_nStatus;
                emit error();
                return;
            }
            m_byteArrayTemp.append(QByteArray::fromRawData(arr_Buffer, sizeof(arr_Buffer)));
            if ( m_byteArrayTemp.count() == m_nCountPerSec ) {
                /* read every 1 second of data then append into buffer */
                m_byteArraySaved.append(m_byteArrayTemp);
                m_byteArrayTemp.clear();
                updateProgressTime();
            }
        }
    }
    emit stopThread();
}

void CAudioModule::displayError()
{
    /* stop the thread */
    wait();
    terminate();
    msleep(50);
    QMessageBox::critical(m_dialogAudio, "Audio", "Audio Device not found!");
    on_pushButtonCancel_clicked();
}

void CAudioModule::playData()
{
    QByteArray byteArrayData;
    /* play one second of data */
    byteArrayData = m_byteArraySaved.mid(m_sliderTime->value() * m_nCountPerSec, m_nCountPerSec);
    if ( byteArrayData.count() == m_nCountPerSec ) {
        m_nStatus = ::write(m_nFd, byteArrayData.data(), m_nCountPerSec); /* play it back */
        if ( m_nStatus != m_nCountPerSec ) {
            DEBUGMESSAGE("wrote wrong number of bytes");
        }
        else {
        #ifdef AUDIO_DEVICE_USB
            sleep(1);
        #endif
            updateProgressTime();
        }
    }
    byteArrayData.clear();
}

void CAudioModule::enableButton(bool bState)
{
    m_pushButtonRecord->setEnabled(bState);
    m_pushButtonPlay->setEnabled(bState);
    if ( m_bAudioRecording ) {
        m_pushButtonOk->setEnabled(bState);
        m_pushButtonCancel->setEnabled(bState);
    }
}

void CAudioModule::updateProgressTime()
{    
    m_sliderTime->setValue(m_sliderTime->value() + 1);
    m_labelTime->setText(formatTime(m_sliderTime->value()) +"/" + formatTime(m_sliderTime->maximum()));
    if ( m_sliderTime->value() == m_sliderTime->maximum() ) {
        m_bPlaying = false;
        m_bRecording = false;
    }
}

QString CAudioModule::formatTime(int nSecs) {
    /* format the seconds into minutes & seconds */
    int t = nSecs;
    int hours = (int) t / 3600;
    t -= hours * 3600;
    int nMinutes = (int) t / 60;
    t -= nMinutes * 60;
    int nSeconds = t;
    return m_strDummy.sprintf("%02d:%02d",nMinutes,nSeconds);
}

void CAudioModule::muteOnOff()
{
    if ( m_bMute ) {
        /* speaker unmute */
        m_bMute = false;
        #ifdef AUDIO_DEVICE_DSP
            gSysCommand("amixer -D 'hw:0' set PCM unmute");
        #endif
        #ifdef AUDIO_DEVICE_USB
            gSysCommand("amixer  set Speaker unmute");
        #endif
        m_actionVolume->setIcon(QIcon(":/icons-png/volume.png"));
    }
    else {
        /* speaker mute */
        m_bMute = true;
        #ifdef AUDIO_DEVICE_DSP
            gSysCommand("amixer -D 'hw:0' set PCM mute");
        #endif
        #ifdef AUDIO_DEVICE_USB
            gSysCommand("amixer set Speaker mute");
        #endif
        m_actionVolume->setIcon(QIcon(":/icons-png/mute.png"));
    }
}

void CAudioModule::updateVolume()
{
 //int vol=(int)(m_sliderVolume->value()/100.0*31);

 m_labelVolume->setText(" " +QVariant(m_sliderVolume->value()).toString() +" %");
 #ifdef AUDIO_DEVICE_DSP
       gSysCommand("amixer -D 'hw:0' set PCM " + QVariant(m_sliderVolume->value()).toString() +"%");
 #endif
 #ifdef AUDIO_DEVICE_USB
       gSysCommand("amixer set Speaker " + QVariant(m_sliderVolume->value()).toString() +"%");
 #endif

}
