#include "qmaps.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <gps_data.h>
#include <unistd.h>
Maps::Maps(QDialog *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setupUI();
}

void Maps::setupUI()
{
    QGridLayout *layout = new QGridLayout( this );
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    QHBoxLayout *hbox = new QHBoxLayout(this);
    //
    // Buttons
    //
    this->setFixedSize(320,240);
    qDebug()<<"Enter into Setup";
//    QPushButton *btnLeft = new QPushButton( "Left", this );
//    QPushButton *btnRight = new QPushButton( "Right", this );
//    QPushButton *btnUp = new QPushButton( "Up", this );
//    QPushButton *btnDown = new QPushButton( "Down", this );
//    QPushButton *btnHome = new QPushButton( "Home", this );
//    QPushButton *btnExit = new QPushButton("Exit",this);
//    btnLeft->setFixedSize(40,20);
//    btnRight->setFixedSize(40,20);
//    btnUp->setFixedSize(40,20);
//    btnDown->setFixedSize(40,20);
//     btnHome->setFixedSize(40,20);
//     btnExit->setFixedSize(40,20);
//    connect( btnHome, SIGNAL(clicked()), this, SLOT(goHome()) );
//    connect( btnLeft, SIGNAL(clicked()), this, SLOT(goLeft()) );
//    connect( btnRight, SIGNAL(clicked()), this, SLOT(goRight()) );
//    connect( btnUp, SIGNAL(clicked()), this, SLOT(goUp()) );
//    connect( btnDown, SIGNAL(clicked()), this, SLOT(goDown()) );
//    connect( btnExit, SIGNAL(clicked()), this, SLOT(btnExitClicked()));

//    layout->addWidget( btnLeft, 3, 1 );
//    layout->addWidget( btnRight, 3, 3 );
//    layout->addWidget( btnUp, 2, 2 );
//    layout->addWidget( btnDown, 4, 2 );
//    layout->addWidget( btnHome, 3, 2 );

//    layout->addWidget( btnHome, 0, 0);
//    layout->addWidget( btnRight, 0, 1 );
//    layout->addWidget( btnLeft,0, 2 );
//    layout->addWidget( btnUp, 0, 3 );
//    layout->addWidget( btnDown, 0, 4 );
//    layout->addWidget(btnExit,0,5);


//    layout->addWidget( btnLeft);
//    layout->addWidget( btnRight);
//    layout->addWidget( btnUp);
//    layout->addWidget( btnDown);
//    layout->addWidget( btnHome);
    //
    // Embedded webpage
    //
    mView = new QWebView( this );
    mView->setFixedSize(312,230);
    mView->settings()->setAttribute( QWebSettings::JavascriptEnabled, true );
    QString fileName = qApp->applicationDirPath() + "/test.html";
    if( !QFile(fileName).exists() ) {
        qDebug() << "File not found:" << fileName;
    }
    QUrl url = QUrl::fromLocalFile( fileName );
    mView->load( url );

    layout->addWidget( mView, 0, 0,0, 5 );
//     btnHome->setFocus();
//    hbox->addWidget(mView);
//    hbox->addLayout(layout);
}
void Maps::btnExitClicked()
{

    qDebug()<<"Enter into Exit";
    this->close();
     GPS_data *gps = new GPS_data;
     gps->show();
     QEventLoop eventloop;
     connect(gps, SIGNAL(destroyed()), &eventloop, SLOT(quit()));
     eventloop.exec();
}

