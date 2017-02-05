
#include "csignature.h"

#include <QPluginLoader>
#include <QTimer>

#include <QScrollArea>
#include <QMessageBox>
#include <QActionGroup>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDirModel>

#include <QLabel>

#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

/********************************************************************************
         This code is implemented by using sample called ts_test.c as modal
********************************************************************************/

extern "C"
{
#include "cfbutils.h"
}
static int palette [] =
{
    0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0
        };

#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))


int CPaintPanel::oldx =-1;
int CPaintPanel::oldy =-1;

#if 0
static void sig(int sig)
{
    fflush(stderr);
    fflush(stdout);
    exit(1);
}
#endif

/* Class to Design GUI for signature capture */
CSignature::CSignature() : QDialog()
{
    Saved=false;
        paintpanel = new CPaintPanel(this);
        pSave = new QPushButton("Ok",this);
        QPushButton *pClear = new QPushButton("Clear");
        QPushButton *pExit= new QPushButton("Cancel",this);
//        pSave->setShortcut(QKeySequence(Qt::Key_F2));
//        pExit->setShortcut(QKeySequence(Qt::Key_F4));
        pSave->setIcon(QIcon(":/icons-png/ok.png"));
        pExit->setIcon(QIcon(":/icons-png/exit.png"));
        pSave->setGeometry(5,400,150,50);
        pExit->setGeometry(160,400,150,50);
        QHBoxLayout *hLayout = new QHBoxLayout;
        QLabel *lblStatus=new QLabel("Put Your Signature Here:");
        lblStatus->setFont(QFont("sans serif",12,2,false));
        hLayout->addWidget(lblStatus);
        hLayout->addWidget(pClear);
        QFrame *grpBox = new QFrame(this);
        QGroupBox *grpBoxCapture = new QGroupBox(this);
        grpBox->setFrameStyle(QFrame::NoFrame);
        grpBox->setGeometry(2,2,316,70);
        grpBox->setLayout(hLayout);
        grpBoxCapture->setFixedSize(300,120);
        grpBoxCapture->setGeometry(10,100,300,120);
        paintpanel->setGeometry(10,100,300,120);
        paintpanel->setCursor( QCursor( Qt::BlankCursor ) );
        grpBoxCapture->setCursor( QCursor( Qt::BlankCursor ) );
        hLayout->setMargin(0);

        pSave->setEnabled(false);
        setWindowTitle(tr("Signature Capture"));
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFixedSize(320,480);
        timer=new QTimer;
        timer->setInterval(60000);
        connect(timer,SIGNAL(timeout()),this,SLOT(exitSig()));
    #ifdef Q_WS_QWS
        t = new CThreadSignature;
        t->start();
        connect(t,SIGNAL(sigEnable(bool)),pSave,SLOT(setEnabled(bool)));
    #endif

        connect(pSave,SIGNAL(clicked()),this,SLOT(save()));
        connect(pClear,SIGNAL(clicked()),this,SLOT(clearImage()));
        connect(pExit,SIGNAL(clicked()),this,SLOT(reject()));
        connect(this,SIGNAL(rejected()),this,SLOT(exitSig()));
        timer->start();
}

/* Fucntion to save drawn signature to a file */
void CSignature::save()
{
    this->setEnabled(false);
#ifdef Q_WS_QWS
    if(t->isRunning())
    {
        t->quit();
        t->active = true;
        t->sigenable = false;
    }
    getpixelvalues(10,100,310,220);
    uint x,y,tmp;
    /* signature capture sensitive region starts from x=6 & y=76 th pixel */
    x=10;
    y=100;

    /* the loop given below used to retrieve color values from pixel to save signature image */
    for (; y <220; y++) {
        for (tmp = x; tmp < 310; tmp++) {
            if(pixval[tmp-10][y-100]==0)
            {
                paintpanel->draw(tmp-10,y-100,0x000000);
            }
            else
            {
                paintpanel->draw(tmp-10,y-100,0xffffff);
            }
        }
    }
    this->setEnabled(true);
    pSave->setEnabled(false);
    /* save the created signature image into a instance of QImage */
    Image=paintpanel->theImage;
#endif
    Saved=true;
    reject();
}

/* Funtion to clear the drawn signature from display */
void CSignature::clearImage()
{
#ifdef Q_WS_QWS
    pSave->setEnabled(false);
    t->sigenable = false;
    if(t->active == true)
    {
        t->active = false;
        t->start();
    }
    paintpanel->theImage.fill(qRgb(255, 255, 255));
    paintpanel->update();
    cleansig();
#endif
    timer->stop();
    timer->start();
}

/* Function to wuit from signature capture window */
void CSignature::exitSig()
{
#ifdef Q_WS_QWS
    if(t->isRunning())
    {
        t->quit();
        t->active = true;
    }
#endif
    close();
}

/* Thread to update pixel values based on touch screen pressure sensed */
CThreadSignature::CThreadSignature()
{
    active =false;
    mode =0;

    unsigned int i;
    char *tsdevice=NULL;

    /* get touch screen device name from environment variable */
    if ((tsdevice = getenv("TSLIB_TSDEVICE")) == NULL) {
#ifdef USE_INPUT_API
        tsdevice = strdup ("/dev/input/event0");
#else
        tsdevice = strdup ("/dev/touchscreen/ucb1x00");
#endif /* USE_INPUT_API */
    }

    /* Open touch screen device */
    ts = ts_open (tsdevice, 0);

    if (!ts) {
        perror (tsdevice);
        exit(1);
    }

    /* configure touch screen device */
    if (ts_config(ts)) {
        perror("ts_config");
        exit(1);
    }

    /* Open frame buffer device */
    if (open_framebuffer()) {
//        qDebug()<<"Error in opening FB";
        exit(1);
    }

    /* identify mid point of the screen */
    x = xres/2;
    y = yres/2;

    for (i = 0; i < NR_COLORS; i++)
        setcolor (i, palette [i]);
    flag=-1;
    ti=700;
    sigenable = false;
}

void CThreadSignature::run()
{
    QTime LastTime;
    while (1) {
        struct ts_sample samp;

        /* Show the cross */

        /* To read raw touch touch sample's */
        ret = ts_read(ts, &samp, 1);
        if (ret < 0) {
            perror("ts_read");
            exit(1);
        }

        if (ret != 1)
            continue;
        if(active)
        {
            flag = -1;
            break;
        }

        if(flag==-1)
        {
            mode = 1;
            flag =1;
        }
        if (samp.pressure > 0) {
            if(samp.x>9 && samp.y>99 &&  (uint)samp.x < 310 && (uint)samp.y < 220)
            {
                LastTime=QDateTime::currentDateTime().time();
                if (mode == 0x80000001)
                {
                    line (x, y, samp.x, samp.y, 0x000000);
                }
                if(sigenable == false)
                {
                    emit sigEnable(true);
                }
                x = samp.x;
                y = samp.y;
                mode |= 0x80000000;
            }
            else
            {
                msleep(7);
                mode = 1;
            }
        } else
            mode &= ~0x80000000;
    }
}

void CThreadSignature::refreshval()
{
    msleep(7);
}


/* class CPaintPanel is used to convert from the display pixel values to QImage */
CPaintPanel::CPaintPanel(QWidget *parent) :
        QWidget(parent),
        theImage(300, 120, QImage::Format_RGB32),
        color(Qt::black),
        thickness(2),
        lastPos(-1, -1)
{
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoBackground);

    theImage.fill(qRgb(255, 255, 255));
    mutex = new QMutex(QMutex::Recursive);
}

QSize CPaintPanel::sizeHint() const
{
    return theImage.size();
}

void CPaintPanel::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawImage(QPoint(0, 0), theImage);
}


void CPaintPanel::draw(int x,int y,unsigned long val)
{/*Function used to draw image for the given pixel with given color */
    mutex->lock();
    theImage.setPixel(QPoint(x,y),(unsigned)val);
    mutex->unlock();
}





//#include "csignature.h"

//#include <QPluginLoader>
//#include <QTimer>

//#include <QScrollArea>
//#include <QMessageBox>
//#include <QActionGroup>
//#include <QAction>
//#include <QMenu>
//#include <QMenuBar>
//#include <QFileDialog>
//#include <QColorDialog>
//#include <QInputDialog>
//#include <QApplication>
//#include <QPainter>
//#include <QMouseEvent>
//#include <QLayout>
//#include <QGroupBox>
//#include <QPushButton>
//#include <QDirModel>

//#include <QLabel>

//#include <QDebug>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <signal.h>
//#include "cglobal.h"

//using namespace ClanCor;
//using namespace Global;

///********************************************************************************
//         This code is implemented by using sample called ts_test.c as modal
//********************************************************************************/

//extern "C"
//{
//#include "cfbutils.h"
//}
//static int palette [] =
//{
//    0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0
//        };

//#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))


//int CPaintPanel::oldx =-1;
//int CPaintPanel::oldy =-1;

//#if 0
//static void sig(int sig)
//{
//    fflush(stderr);
//    fflush(stdout);
//    exit(1);
//}
//#endif

///* Class to Design GUI for signature capture */
//CSignature::CSignature() : QDialog()
//{
//    Saved=false;
//    paintpanel = new CPaintPanel(this);
//    pSave = new QPushButton("Ok",this);
//    QPushButton *pClear = new QPushButton("Clear");
//    QPushButton *pExit= new QPushButton("Cancel ",this);
////    pSave->setShortcut(QKeySequence(Qt::Key_F2));
////    pExit->setShortcut(QKeySequence(Qt::Key_F4));
//    pSave->setIcon(QIcon(":/icons-png/ok.png"));
//    pExit->setIcon(QIcon(":/icons-png/exit.png"));
////    pSave->setGeometry(5,200,150,25);
////    pExit->setGeometry(160,200,150,25);
//    pSave->setGeometry(10,430,150,25);
//    pExit->setGeometry(170,430,150,25);
//    QHBoxLayout *hLayout = new QHBoxLayout;
//    QLabel *lblStatus=new QLabel("Put Your Signature Here:");
//    lblStatus->setFont(QFont("sans serif",12,2,false));
//    hLayout->addWidget(lblStatus);
//    hLayout->addWidget(pClear);
//    QFrame *grpBox = new QFrame(this);
//    QGroupBox *grpBoxCapture = new QGroupBox(this);
//    grpBox->setFrameStyle(QFrame::NoFrame);
//    grpBox->setGeometry(2,2,316,50);
//    grpBox->setLayout(hLayout);
//    grpBoxCapture->setFixedSize(316,118);
//    grpBoxCapture->setGeometry(2,71,316,118);
//    paintpanel->setGeometry(5,75,310,110);
//    paintpanel->setCursor( QCursor( Qt::BlankCursor ) );
//    grpBoxCapture->setCursor( QCursor( Qt::BlankCursor ) );
//    hLayout->setMargin(0);

//    pSave->setEnabled(false);
//    setWindowTitle(tr("Signature Capture"));
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    setFixedSize(320,240);
//    timer=new QTimer;
//    timer->setInterval(60000);
//    connect(timer,SIGNAL(timeout()),this,SLOT(exitSig()));
//#ifdef Q_WS_QWS
//    t = new CThreadSignature;
//    t->start();
//    connect(t,SIGNAL(sigEnable(bool)),pSave,SLOT(setEnabled(bool)));
//#endif

//    connect(pSave,SIGNAL(clicked()),this,SLOT(save()));
//    connect(pClear,SIGNAL(clicked()),this,SLOT(clearImage()));
//    connect(pExit,SIGNAL(clicked()),this,SLOT(reject()));
//    connect(this,SIGNAL(rejected()),this,SLOT(exitSig()));
//    timer->start();
//}

///* Fucntion to save drawn signature to a file */
//void CSignature::save()
//{
//    this->setEnabled(false);
//#ifdef Q_WS_QWS
//    if(t->isRunning())
//    {
//        t->quit();
//        t->active = true;
//        t->sigenable = false;
//    }
//    getpixelvalues(6,76,xres-6,184);
//    uint x,y,tmp;
//    /* signature capture sensitive region starts from x=6 & y=76 th pixel */
//    x=6;
//    y=76;

//    /* the loop given below used to retrieve color values from pixel to save signature image */
//    for (; y <= 184; y++) {
//        for (tmp = x; tmp <= xres-6; tmp++) {

//            if(pixval[tmp-6][y-76]==0)
//            {
//                paintpanel->draw(tmp-6,y-76,0x000000);
//            }
//            else
//            {
//                paintpanel->draw(tmp-6,y-76,0xffffff);
//            }
//        }
//    }
//    this->setEnabled(true);
//    pSave->setEnabled(false);
//    /* save the created signature image into a instance of QImage */
//    Image=paintpanel->theImage;
//#endif
//    Saved=true;
//    reject();
//}

///* Funtion to clear the drawn signature from display */
//void CSignature::clearImage()
//{
//#ifdef Q_WS_QWS
//    pSave->setEnabled(false);
//    t->sigenable = false;
//    if(t->active == true)
//    {
//        t->active = false;
//        t->start();
//    }
//    paintpanel->theImage.fill(qRgb(255, 255, 255));
//    paintpanel->update();
//    cleansig();
//#endif
//    timer->stop();
//    timer->start();
//}

///* Function to wuit from signature capture window */
//void CSignature::exitSig()
//{
//#ifdef Q_WS_QWS
//    if(t->isRunning())
//    {
//        t->quit();
//        t->active = true;
//    }
//#endif
//    close();
//}

///* Thread to update pixel values based on touch screen pressure sensed */
//CThreadSignature::CThreadSignature()
//{
//    active =false;
//    mode =0;

//    unsigned int i;
//    char *tsdevice=NULL;

//    /* get touch screen device name from environment variable */
//    if ((tsdevice = getenv("TSLIB_TSDEVICE")) == NULL) {
//#ifdef USE_INPUT_API
//        tsdevice = strdup ("/dev/input/event0");
//#else
//        tsdevice = strdup ("/dev/touchscreen/ucb1x00");
//#endif /* USE_INPUT_API */
//    }

//    /* Open touch screen device */
//    ts = ts_open (tsdevice, 0);

//    if (!ts) {
//        perror (tsdevice);
//        exit(1);
//    }

//    /* configure touch screen device */
//    if (ts_config(ts)) {
//        perror("ts_config");
//        exit(1);
//    }

//    /* Open frame buffer device */
//    if (open_framebuffer()) {
//        qDebug()<<"Error in opening FB";
//        exit(1);
//    }

//    /* identify mid point of the screen */
//    x = xres/2;
//    y = yres/2;

//    for (i = 0; i < NR_COLORS; i++)
//        setcolor (i, palette [i]);
//    flag=-1;
//    ti=700;
//    sigenable = false;
//}

//void CThreadSignature::run()
//{
//    QTime LastTime;
//    while (1) {
//        struct ts_sample samp;

//        /* Show the cross */

//        /* To read raw touch touch sample's */
//        ret = ts_read(ts, &samp, 1);
//        if (ret < 0) {
//            perror("ts_read");
//            exit(1);
//        }

//        if (ret != 1)
//            continue;
//        if(active)
//        {
//            flag = -1;
//            break;
//        }

//        if(flag==-1)
//        {
//            mode = 1;
//            flag =1;
//        }
//        if (samp.pressure > 0) {
//            if(samp.x>6 && samp.y>75 &&  (uint)samp.x < xres-6 && (uint)samp.y < yres-56)
//            {
//                LastTime=QDateTime::currentDateTime().time();
//                if (mode == 0x80000001)
//                {
//                    line (x, y, samp.x, samp.y, 0x000000);
//                }
//                if(sigenable == false)
//                {
//                    emit sigEnable(true);
//                }
//                x = samp.x;
//                y = samp.y;
//                mode |= 0x80000000;
//            }
//            else
//            {
//                msleep(7);
//                mode = 1;
//            }
//        } else
//            mode &= ~0x80000000;
//    }
//}

//void CThreadSignature::refreshval()
//{
//    msleep(7);
//}


///* class CPaintPanel is used to convert from the display pixel values to QImage */
//CPaintPanel::CPaintPanel(QWidget *parent) :
//        QWidget(parent),
//        theImage(310, 110, QImage::Format_RGB32),
//        color(Qt::black),
//        thickness(2),
//        lastPos(-1, -1)
//{
//    setAttribute(Qt::WA_StaticContents);
//    setAttribute(Qt::WA_NoBackground);

//    theImage.fill(qRgb(255, 255, 255));
//    mutex = new QMutex(QMutex::Recursive);
//}

//QSize CPaintPanel::sizeHint() const
//{
//    return theImage.size();
//}

//void CPaintPanel::paintEvent(QPaintEvent * /* event */)
//{
//    QPainter painter(this);
//    painter.setPen(Qt::black);
//    painter.drawImage(QPoint(0, 0), theImage);
//}


//void CPaintPanel::draw(int x,int y,unsigned long val)
//{/*Function used to draw image for the given pixel with given color */
//    mutex->lock();
//    theImage.setPixel(QPoint(x,y),(unsigned)val);
//    mutex->unlock();
//}
