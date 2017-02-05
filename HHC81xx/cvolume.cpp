#include "cvolume.h"
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

CVolume::CVolume()
{
    QString strData = "";
    m_nValue = 0;
    if ( gSysCommand("amixer","get 'Speaker'",strData) ) {
        int nStart = strData.indexOf("[");
        int nEnd = strData.indexOf("]",nStart);
        if ( nStart > 0 && nEnd > 0 ) {
            m_nValue = QVariant(strData.mid(nStart + 1,nEnd - nStart - 2)).toInt();
        }
    }
    QFrame *frameBox = new QFrame;
    QLabel *labelStatus = new QLabel("Speaker",frameBox);
    QLabel *labelSpeaker = new QLabel(frameBox);
    labelVolume = new QLabel(QVariant(m_nValue).toString(),frameBox);
    sliderSpeaker = new QSlider(Qt::Vertical,frameBox);
    sliderSpeaker->setFocusPolicy(Qt::StrongFocus);
    sliderSpeaker->setTickPosition(QSlider::NoTicks);
    sliderSpeaker->setTickInterval(1);
    sliderSpeaker->setEnabled(false);
    sliderSpeaker->setMaximum(100);
    sliderSpeaker->setFixedSize(30,120);
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setWordWrap(true);
    labelVolume->setAlignment(Qt::AlignCenter);
    labelVolume->setWordWrap(true);
    labelSpeaker->setPixmap(QPixmap::fromImage(QImage(":/icons-png/volume.png")));
    QVBoxLayout *vBoxLayoutSpeaker = new QVBoxLayout;
    vBoxLayoutSpeaker->addWidget(labelStatus);
    vBoxLayoutSpeaker->addWidget(labelSpeaker,0,Qt::AlignCenter);
    vBoxLayoutSpeaker->addWidget(sliderSpeaker,0,Qt::AlignCenter);
    vBoxLayoutSpeaker->addWidget(labelVolume);
    vBoxLayoutSpeaker->setSpacing(2);
    vBoxLayoutSpeaker->setMargin(1);

    frameBox->setLayout(vBoxLayoutSpeaker);
    frameBox->setLineWidth(3);
    frameBox->setMidLineWidth(3);
    frameBox->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QVBoxLayout *vBoxLayoutMain =new QVBoxLayout;
    vBoxLayoutMain->addWidget(frameBox);
    vBoxLayoutMain->setMargin(0);
    vBoxLayoutMain->setSpacing(0);
    setLayout(vBoxLayoutMain);

    setGeometry(120,25,60,200);
    setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    sliderSpeaker->setValue(m_nValue);
}

void CVolume::increaseVolume()
{
    QString strData="";
    if ( gSysCommand("amixer","get 'Speaker'",strData) ) {
        int nStart = strData.indexOf("[");
        int nEnd = strData.indexOf("]",nStart);
        if ( nStart > 0 && nEnd > 0 ) {
            m_nValue = QVariant(strData.mid(nStart + 1,nEnd - nStart - 2)).toInt();
            if ((m_nValue + 10) <= 100 ) {
                m_nValue += 10;
            }
            else {
                m_nValue = 100;
            }
            sliderSpeaker->setValue(m_nValue);
            labelVolume->setText(QVariant(m_nValue).toString());
            system(QString("amixer set Speaker " + QString::number(m_nValue) +"%").toLatin1());
        }
    }
    strData.clear();
}

void CVolume::decreaseVolume()
{
    QString strData="";
    if ( gSysCommand("amixer","get 'Speaker'",strData) ) {
        int nStart = strData.indexOf("[");
        int nEnd = strData.indexOf("]",nStart);
        if ( nStart > 0 && nEnd > 0 ) {
            m_nValue = QVariant(strData.mid(nStart + 1,nEnd - nStart - 2)).toInt();
            if ((m_nValue - 10) >= 0 ) {
                m_nValue -= 10;
            }
            else {
                m_nValue = 0;
            }
            sliderSpeaker->setValue(m_nValue);
            labelVolume->setText(QVariant(m_nValue).toString());
            system(QString("amixer set Speaker " + QString::number(m_nValue) +"%").toLatin1());
        }
    }
    strData.clear();
}

/*********************************************************************************/
//                           Class Volume Control GUI                            //
/*********************************************************************************/

const QString const_strSPEAKER          = "Speaker";
const QString const_strMIC              = "Mic";

CVolumeSetting::CVolumeSetting()
{
    m_nSpeakerVol = 0;
    m_nMicVol = 0;
    QVBoxLayout *vblvol = new QVBoxLayout;
    QVBoxLayout *vblmic = new QVBoxLayout;
    QVBoxLayout *vblmain = new QVBoxLayout;
    QHBoxLayout *hblSubmain = new QHBoxLayout;
    QGroupBox *frameBoxvol = new QGroupBox("Speaker");
    QGroupBox *frameBoxmic = new QGroupBox("Mic");
    QFont f;
    f.setPointSize(8);
    frameBoxvol->setAlignment(Qt::AlignCenter);
    frameBoxmic->setAlignment(Qt::AlignCenter);
    frameBoxvol->setFont(f);
    frameBoxmic->setFont(f);;
    sliderSpeakerVol = new QSlider(Qt::Vertical);
    sliderMicVol = new QSlider(Qt::Vertical);
    sliderSpeakerVol->setObjectName(const_strSPEAKER);
    sliderMicVol->setObjectName(const_strMIC);
    pushButtonSpeaker = new QPushButton;
    pushButtonMic = new QPushButton;
    pushButtonDefault = new QPushButton("Default [F1]");
    pushButtonDefault->setShortcut(Qt::Key_F1);
    pushButtonDefault->setIcon(QIcon(":/img/icon_revert.png"));
    pushButtonSpeaker->setFixedSize(20,20);
    pushButtonMic->setFixedSize(20,20);
    pushButtonDefault->setFixedSize(100, 20);
    pushButtonSpeaker->setFlat(true);
    pushButtonMic->setFlat(true);
    pushButtonDefault->setFlat(true);

    pushButtonSpeaker->setFocusPolicy(Qt::NoFocus);
    pushButtonMic->setFocusPolicy(Qt::NoFocus);
    pushButtonDefault->setFocusPolicy(Qt::NoFocus);

    sliderSpeakerVol->setFocusPolicy(Qt::StrongFocus);
    sliderSpeakerVol->setTickPosition(QSlider::TicksLeft);
    sliderSpeakerVol->setTickInterval(10);
    sliderSpeakerVol->setSingleStep (10);
    sliderSpeakerVol->setMinimum(0);
    sliderSpeakerVol->setMaximum(100);

    sliderMicVol->setFocusPolicy(Qt::StrongFocus);
    sliderMicVol->setTickPosition(QSlider::TicksRight);
    sliderMicVol->setTickInterval(10);
    sliderMicVol->setSingleStep (10);
    sliderMicVol->setMinimum(0);
    sliderMicVol->setMaximum(100);

    vblvol->setSpacing(0);
    vblvol->setMargin(0);
    vblvol->addWidget(sliderSpeakerVol);
    vblvol->addWidget(pushButtonSpeaker);

    vblmic->addWidget(sliderMicVol);
    vblmic->addWidget(pushButtonMic);
    vblmic->setSpacing(0);
    vblmic->setMargin(0);

    frameBoxvol->setLayout(vblvol);
    frameBoxmic->setLayout(vblmic);
    hblSubmain->addWidget(frameBoxvol);
    hblSubmain->addWidget(frameBoxmic);
    hblSubmain->setMargin(0);
    hblSubmain->setSpacing(0);
    vblmain->addLayout(hblSubmain);
    vblmain->addWidget(pushButtonDefault);
    vblmain->setMargin(0);
    setLayout(vblmain);
    setFixedSize(100,160 );
    setWindowModality(Qt::ApplicationModal);
    int Vol;
    if(!getVolume(const_strSPEAKER,Vol,isMute)) return;
    sliderSpeakerVol->setValue(Vol);
    muteUnMute(const_strSPEAKER);
    if(!getVolume(const_strMIC,Vol,isMicMute)) return;
    sliderMicVol->setValue(Vol);
    muteUnMute(const_strMIC);
    connect(pushButtonMic,SIGNAL(clicked()),this,SLOT(slotBtnmic()));
    connect(pushButtonSpeaker,SIGNAL(clicked()),this,SLOT(slotBtnvol()));
    connect(pushButtonDefault,SIGNAL(clicked()),this,SLOT(setDefault()));
    connect(sliderSpeakerVol,SIGNAL(valueChanged(int)),this,SLOT(changeVal(int)));
    connect(sliderMicVol,SIGNAL(valueChanged(int)),this,SLOT(changeValmic(int)));
}

void CVolumeSetting::keyPressEvent(QKeyEvent *keyEvent)
{
    if ( keyEvent->key()==Qt::Key_M || keyEvent->key() == Qt::Key_Colon ) {
        QWidget *w = focusWidget();
        if ( w->objectName() == const_strSPEAKER ) {
            slotMute(w->objectName(), ! isMute);
        }
        else {
            slotMute(w->objectName(), ! isMicMute);
        }
    }
    else {
        QDialog::keyPressEvent(keyEvent);
    }
}

void CVolumeSetting::slotVol()
{
    system(QString("amixer set Speaker " + QVariant(m_nSpeakerVol).toString() +"%").toLatin1());
}

void CVolumeSetting::slotVolmic()
{
    system(QString("amixer set Mic " + QVariant(m_nMicVol).toString() +"%").toLatin1());
}


void  CVolumeSetting::slotMute(const QString &r_const_strELEMENT, bool bMute)
{
    if ( r_const_strELEMENT == const_strSPEAKER ) {
        if ( bMute ) {
            system(QString("amixer set Speaker mute").toLatin1());
        }
        else {
            system(QString("amixer set Speaker unmute").toLatin1());
        }
    }
    else if ( r_const_strELEMENT == const_strMIC ) {
        if ( bMute ) {
            system(QString("amixer  sset Mic nocap").toLatin1());
        }
        else {
            system(QString("amixer sset Mic cap").toLatin1());
        }
    }
    muteUnMute(r_const_strELEMENT);
}

void CVolumeSetting::muteUnMute(const QString &r_const_strELEMENT)
{
    QIcon icon;
    int Vol;
    if ( r_const_strELEMENT == const_strSPEAKER ) {
        if ( ! getVolume(r_const_strELEMENT,Vol,isMute) ) {
            return;
        }
        if ( isMute ) {
            icon.addFile(":/icons-png/mutetr.png");
            pushButtonSpeaker->setIconSize(QSize(20,20));
            pushButtonSpeaker->setIcon(icon);
        }
        else {
            icon.addFile(":/icons-png/unmutetr.png");
            pushButtonSpeaker->setIconSize(QSize(20,20));
            pushButtonSpeaker->setIcon(icon);
        }
    }
    else if ( r_const_strELEMENT == const_strMIC ) {
        if ( ! getVolume(r_const_strELEMENT,Vol,isMicMute) ) {
            return;
        }
        if ( isMicMute ) {
            icon.addFile(":/icons-png/mic-mute.png");
            pushButtonMic->setIconSize(QSize(20,20));
            pushButtonMic->setIcon(icon);
        }
        else {
            icon.addFile(":/icons-png/mic.png");
            pushButtonMic->setIconSize(QSize(20,20));
            pushButtonMic->setIcon(icon);
        }
    }
}

void CVolumeSetting::changeVal(int nValue)
{
    m_nSpeakerVol = nValue;
    slotVol();
}

void CVolumeSetting::changeValmic(int nValue)
{
    m_nMicVol = nValue;
    slotVolmic();
}

void CVolumeSetting::slotBtnvol()
{
    slotMute(const_strSPEAKER, ! isMute);
}

void CVolumeSetting::slotBtnmic()
{
    slotMute(const_strMIC, ! isMicMute);
}

void CVolumeSetting::setDefault()
{
    sliderSpeakerVol->setValue(80);
    sliderMicVol->setValue(65);
    slotMute(const_strSPEAKER, false);
    slotMute(const_strMIC, false);
}

bool CVolumeSetting::getVolume(const QString &r_const_strELEMENT, int &r_nVolume, bool &r_bMute)
{
    QString strData = "";
    bool bResponse = false;
    if ( gSysCommand("amixer","get " + r_const_strELEMENT, strData) ) {
        int nPos = 0;
        if ( r_const_strELEMENT == "Mic" ) {
            nPos = strData.indexOf("Capture");
        }
        int nStart = strData.indexOf("[",nPos);
        int nEnd = strData.indexOf("]",nStart);
        if ( nStart > 0 && nEnd > 0 ) {
            r_nVolume = QVariant(strData.mid(nStart + 1, nEnd - nStart - 2)).toInt();
            if ( strData.right(5).contains("on") ) {
                r_bMute = false;
            }
            else {
                r_bMute = true;
            }
            bResponse = true;
        }
    }
    strData.clear();
    return bResponse;
}
