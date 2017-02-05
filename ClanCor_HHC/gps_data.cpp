#include "gps_data.h"
#include "ui_gps_data.h"
#include "GlobalClass.h"

using namespace Globalclass;

GPS_data::GPS_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GPS_data)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    setWindowTitle("GPS Data");

    QGroupBox *grpbox = new QGroupBox(this);
    //    grpbox->setGeometry(192,185,124,34);
    grpbox->setGeometry(20,370,120,40);
    ui->btnRefresh->setParent(grpbox);
    //  ui->pushButton_Download->setParent(grpbox);
    grpbox->setStyleSheet("QPushButton:pressed{background-color: rgb(255, 186, 181);border-width: 5px;border-color:Magenta;border-style: solid;};");
    grpbox->setFocusPolicy(Qt::NoFocus);

    QSqlQuery qry_agps;
    qry_agps = db->SelectQuery("select * from agps_settings");
    db->clearAll();
    escapepressed=true;
    Automatic = false;
    ErrorCount=0;
    ui->pushButton_Download->setVisible(false);
    if(!db->IsLastError())
    {
        if(qry_agps.next())
        {
            FtpPath=qry_agps.value(0).toString();
            FtpUser=qry_agps.value(1).toString();
            FtpPassword=qry_agps.value(2).toString();
            Agps_configure=true;
            if(qry_agps.value(3).toBool()==true)
            {
                Automatic=true;
            }
            else
            {
                ui->pushButton_Download->setVisible(true);
                Automatic=false;
            }
        }
    }
    qry_agps.clear();
    ui->lblAltitude_val->setText("<font color=""red"">      Reading GPS Data ...");
    t= new QTimer;
    t->setInterval(1200);
    t->setSingleShot(false);
    connect(t, SIGNAL(timeout()), this, SLOT(Receive_File()));
    t->start();
    GPSfix = false;
    ui->btnRefresh->setFocus();
    show();
//    qDebug()<<"\r GPS end display...>>";
}

GPS_data::~GPS_data()
{    
    delete ui;
}

void GPS_data::Receive_File()
{
//    qDebug()<<"\r GPS receive...>>"<<Automatic<<"agps"<<Agps_configure;
    //    if(Automatic == true && Agps_configure == true)
    //    {
    //          qDebug()<<"\r GPS receive. if 1..>>";
    //        on_pushButton_Download_clicked();
    //    }
    if(g_ccmainObj->getGPSdata(strLatitude,strLongitude,strAltitude,strNo_of_sat,strSpeed,strtime))
    {
//        qDebug()<<"\r GPS receive...>> 2";
        if(strLongitude !="" && strLatitude !="")
        {
//            qDebug()<<"\r GPS receive...> 3>";

            ErrorCount=0;
            ui->lblLatitude_val->setText(strLatitude);
            ui->lblLongitude_val->setText(strLongitude);
            ui->lblAltitude_val->setText(strAltitude);
            ui->lblGrndSpeed_val->setText(strSpeed);
            ui->lblNo_sat_val->setText(strNo_of_sat);
        }
        else
        {
//            qDebug()<<"\r GPS receive..4 .>>";
            ErrorCount=0;
            ui->lblLatitude_val->clear();
            ui->lblLongitude_val->clear();
            ui->lblAltitude_val->setText("<font color=""red"">      Trying to fix GPS Position...");
            ui->lblGrndSpeed_val->clear();
            ui->lblNo_sat_val->clear();
        }
    }
    else
    {
//        qDebug()<<"\r GPS receive        5...>>";
        if(ErrorCount>=10)
        {
//            qDebug()<<"\r GPS receive...6>>";
            g_ccmainObj->EnableGPSModule(false);
            ui->lblLatitude_val->clear();
            ui->lblLongitude_val->clear();
            ui->lblAltitude_val->setText("<font color=""red"">            GPS Initialize Failed...");
            ui->lblGrndSpeed_val->clear();
            ui->lblNo_sat_val->clear();
            UpdateScreen(200);
            g_ccmainObj->EnableGPSModule(true);
            ErrorCount=0;
        }
        else
        {
//            qDebug()<<"\r GPS receive..7.>>";
            ErrorCount++;
        }
    }
}

void GPS_data::close_dia()
{
    t->stop();
    delete t;
    this->reject();
}

void GPS_data::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {
//          g_ccmainObj->EnableGPSModule(false);
          g_ccmainObj->serverMethod()->gpsiconflag = true;
          g_ccmainObj->gpsStandby();
          close_dia();
    }
    else if(e->key()==Qt::Key_Escape || e->key() == Qt::Key_F4)
    {
        if(escapepressed)
        {
//            MyServerObj->showgps(false);
//            emit showgpsicon(false);
            escapepressed=false;
            g_ccmainObj->serverMethod()->gpsiconflag = true;
            g_ccmainObj->gpsStandby();
            close_dia();
        }
    }
    else
    {
        QDialog::keyPressEvent(e);
    }
}

void GPS_data::delay(int nMSec)
{
    QEventLoop eventLoop;
    QTimer timerTimeout;
    timerTimeout.setInterval(nMSec);
    timerTimeout.setSingleShot(true);
    QObject::connect(&timerTimeout, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timerTimeout.start(nMSec);
    eventLoop.exec();
    timerTimeout.stop();
}

void GPS_data::on_btnRefresh_clicked()
{
    setEnabled(false);
    ui->btnRefresh->setEnabled(false);
    t->stop();
    ui->lblNo_sat_val->clear();
    ui->lblLatitude_val->clear();
    ui->lblLongitude_val->clear();
    ui->lblAltitude_val->clear();
    ui->lblGrndSpeed_val->clear();
    ui->btnRefresh->setText("Please wait..");
    UpdateScreen();
    t->start();
    ui->btnRefresh->setText("Refresh");
    ui->btnRefresh->setEnabled(true);
    setEnabled(true);
    ui->btnRefresh->setFocus();
}

void GPS_data::on_pushButton_Download_clicked()
{
    qDebug()<<"\r GPS receive. download clicjked..>>";
    t->stop();
    if(FtpPath != "" && FtpUser != "" && FtpPassword != "")
    {
        if(GPRSEnable())
        {
            DownloadFile();
        }
        else
        {
            QMessageBox::about(0,"AGPS","Download Failed-E02");
        }
    }
    else
    {
        QMessageBox::about(0,"AGPS","Please enter FTP Details");
    }
}

void GPS_data::DownloadFile()
{
    progressDialog = new QProgressDialog;
    ftp = new QFtp;
    ftp->connectToHost("agps.gtop-tech.com");
    ftp->login("gtopepo","gtop1234");
    //    ftp->connectToHost(FtpPath);
    //    ftp->login(FtpUser,FtpPassword);
    ftp->list();
    ftp->get("MTK7d.EPO");
    connect(ftp,SIGNAL(listInfo(QUrlInfo)),this,SLOT(listInfo2(QUrlInfo)));
    connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(commandstarted(int)));
    connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished(int,bool)));
    connect(ftp, SIGNAL(rawCommandReply(int, const QString&)),
            this, SLOT(reply(int, const QString&)));
    connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64))
            ,this,SLOT(viewProgress(qint64,qint64)));
    progressDialog->setLabelText(tr("Downloading %1...").arg("MTK7d.EPO"));
    progressDialog->show();
}

void GPS_data::viewProgress(qint64 done ,qint64 total)
{
    progressDialog->setMaximum(total);
    progressDialog->setValue(done);
    QByteArray ba;
    if(done == total)
    {
        ba = ftp->readAll();
        QFile file("/root/MTK7d.EPO");
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            file.write(ba);
        }
        GPSfix  = true;

        system(QString("chmod 755 /root/MTK7d.EPO").toLatin1());

        ftp->close();
        progressDialog->close();
        if(GPSfix == true)
        {
            escapepressed=false;
            g_ccmainObj->agpsDownload();
        }
        else
        {
            QMessageBox::about(0,"AGPS","Download Failed-E01");
        }
        g_ccmainObj->disableGprs();
        escapepressed=true;
        t->start();
    }
}

void GPS_data::reply(int code)
{
    if (code / 100 == 2)
        qDebug()<<"success";
    else
        qDebug()<<"Failed";
}

void GPS_data::listInfo2(QUrlInfo info)
{
    qDebug()<<"\rListing URL Info:"<<info.name()<<endl;
}

void GPS_data::commandFinished(int id,bool error)
{
    qDebug()<<"\rCommand Finished! Id:"<<id<<"Status:"<<error<<endl;
}

void GPS_data::commandstarted(int id)
{
    qDebug()<<"\rCommand Started ! Id:"<<id;

}

