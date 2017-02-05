#include "patchupdates.h"
#include "ui_patchupdates.h"
#include <csettingsfiles.h>
#include <GlobalClass.h>
#include <QDebug>
#include <QMessageBox>

using namespace Globalclass;

Patchupdates::Patchupdates(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Patchupdates)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("File Copy");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);

    CHHC80xx::version(BUILDVERSION,BUILDDATE);
    g_ccmainObj->coProcessorVersion(Pic32Version,Pic32DT);
    Pic32Version = Pic32Version.remove(0,2);
    progressDialog = new QProgressDialog(this);

    ui->pushButton_Checkupdates->setAutoDefault(true);
    ui->pushButton_Cancel->setAutoDefault(true);
    ui->pushButton_updates->setAutoDefault(true);
    ui->pushButton_Cancel->setVisible(false);
    ui->pushButton_updates->setVisible(false);

    ui->checkBox_Clancor_HHC->setVisible(false);
    ui->checkBox_HHC_SDK->setVisible(false);
    ui->checkBox_CoProcessor->setVisible(false);

    strDownloadfile = "Patch.xml";
    bcheckupdates=false;
    count = 1;
    ui->pushButton_Checkupdates->setFocus();
    ui->checkBox_Clancor_HHC->setShortcut(Qt::Key_F1);
    ui->checkBox_HHC_SDK->setShortcut(Qt::Key_F2);
    ui->checkBox_CoProcessor->setShortcut(Qt::Key_F3);

    connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
}
void Patchupdates::cancelDownload()
{
    ftp->abort();
}


Patchupdates::~Patchupdates()
{
    delete ui;
}

void Patchupdates::on_pushButton_Checkupdates_clicked()
{
    g_ccmainObj->enableIdleMode(false);
    if(GPRSEnable())
    {
        ConnectFTP(strDownloadfile);
    }

}
void Patchupdates::enablePushbutton()
{
    ui->pushButton_Checkupdates->setVisible(false);
    ui->pushButton_Cancel->setVisible(true);
    ui->pushButton_updates->setVisible(true);
}

void Patchupdates::on_pushButton_updates_clicked()
{
    if(bcheckupdates == false)
    {
        if(ui->checkBox_Clancor_HHC->isChecked() && ui->checkBox_Clancor_HHC->isVisible())
        {
            bcheckupdates = true;
            qDebug()<<"enter into Clancor";
            strDownloadfile = "ClanCor_HHC" ;
            ftp = new QFtp;
            ftp->connectToHost("122.165.224.226");
            ftp->login("demo","demo");
            ftp->cd("/Kayshap/root");
            ftp->get(strDownloadfile.trimmed());
            connect(ftp,SIGNAL(listInfo(QUrlInfo)),this,SLOT(listInfo2(QUrlInfo)));
            connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(commandstarted(int)));
            connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished(int,bool)));
            connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64))
                    ,this,SLOT(viewProgress(qint64,qint64)));
            progressDialog->setWindowTitle("File Updates");
            progressDialog->setLabelText(tr("Downloading %1...").arg(strDownloadfile));
            progressDialog->show();

        }
    }
    if(bcheckupdates == false)
    {
        if(ui->checkBox_HHC_SDK->isChecked() && ui->checkBox_HHC_SDK->isVisible())
        {
            qDebug()<<"enter into lib";
            bcheckupdates = true;
            strDownloadfile = "libHHC81xx.so.1.0.0";
            ftp = new QFtp;
            ftp->connectToHost("122.165.224.226");
            ftp->login("demo","demo");
            ftp->cd("/Kayshap/usr/lib");
            ftp->get(strDownloadfile.trimmed());
            connect(ftp,SIGNAL(listInfo(QUrlInfo)),this,SLOT(listInfo2(QUrlInfo)));
            connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(commandstarted(int)));
            connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished(int,bool)));
            connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64))
                    ,this,SLOT(viewProgress(qint64,qint64)));
            progressDialog->setWindowTitle("File Updates");
            progressDialog->setLabelText(tr("Downloading %1...").arg(strDownloadfile));
            progressDialog->show();
        }
    }
    if(bcheckupdates == false)
    {
        if(ui->checkBox_CoProcessor->isChecked() && ui->checkBox_CoProcessor->isVisible())
        {
            qDebug()<<"enter into programfile";
            bcheckupdates = true;
            strDownloadfile = "Programfile.hex";
            ftp = new QFtp;
            ftp->connectToHost("122.165.224.226");
            ftp->login("demo","demo");
            ftp->cd("/Kayshap/mnt");
            ftp->get(strDownloadfile.trimmed());
            connect(ftp,SIGNAL(listInfo(QUrlInfo)),this,SLOT(listInfo2(QUrlInfo)));
            connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(commandstarted(int)));
            connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished(int,bool)));
            connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64))
                    ,this,SLOT(viewProgress(qint64,qint64)));
            progressDialog->setWindowTitle("File Updates");
            progressDialog->setLabelText(tr("Downloading %1...").arg(strDownloadfile));
            progressDialog->show();
        }
    }

}

void Patchupdates::on_pushButton_Cancel_clicked()
{
    this->close();
}

bool Patchupdates::ConnectFTP(QString DownloadFile)
{    
    ftp = new QFtp;
    ftp->connectToHost("122.165.224.226");
    ftp->login("demo","demo");
    qDebug()<<"\r Download file"<<DownloadFile;
    ftp->cd("/Kayshap");
    ftp->list();
    ftp->get(DownloadFile.trimmed());
    connect(ftp,SIGNAL(listInfo(QUrlInfo)),this,SLOT(listInfo2(QUrlInfo)));
    connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(commandstarted(int)));
    connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(commandFinished(int,bool)));
    connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64))
            ,this,SLOT(viewProgress(qint64,qint64)));
    progressDialog->setWindowTitle("File Updates");
    progressDialog->setLabelText(tr("Downloading %1...").arg(strDownloadfile));
    progressDialog->exec();
}

void Patchupdates::viewProgress(qint64 done ,qint64 total)
{
    progressDialog->setMaximum(total);
    progressDialog->setValue(done);
    if(done == total)
    {
        QByteArray ba;
        ba = ftp->readAll();
        if(strDownloadfile.contains("Patch.xml"))
        {
            QFile file("/tmp/"+strDownloadfile);
            if(file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                file.write(ba);
            }
            file.close();
            ba.clear();
            system(QString("chmod 777 /tmp/"+strDownloadfile).toLatin1());

            checkfile();
            count = 0;
            bcheckupdates = false;
        }

        if(strDownloadfile.contains("ClanCor"))
        {
            QFile file("/tmp/"+strDownloadfile);
            if(file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                file.write(ba);
            }
            file.close();
            ba.clear();

            system(QString("chmod 777 /tmp/"+strDownloadfile).toLatin1());
            QString copycmd = "cp /tmp/"+strDownloadfile  +" /root";
            const char *ch1;
            ch1 = copycmd.toLatin1();
            system(QString(ch1).toLatin1());

            ftp->close();
            progressDialog->hide();
            bcheckupdates=true;
            qDebug()<<"\r Total bytes"<<total << "\r done"<<done;
            bcheckupdates = false;
            ui->checkBox_Clancor_HHC->setChecked(false);
            ui->checkBox_Clancor_HHC->setDisabled(true);
            if(downloaddata.size() > 0)
            {
                count = count + 1;
            }
            on_pushButton_updates_clicked();
        }

        if(strDownloadfile.contains("libHH") && ba.size() > 0)
        {
            QFile file("/tmp/"+strDownloadfile);
            if(file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                file.write(ba);
            }
            file.close();

            system(QString("chmod 777 /tmp/"+strDownloadfile).toLatin1());
            QString copycmd = "cp /tmp/"+strDownloadfile  +" /usr/lib";
            const char *ch1;
            ch1 = copycmd.toLatin1();
            system(QString(ch1).toLatin1());
            ftp->close();
            ba.clear();
            progressDialog->hide();
            bcheckupdates=true;

            qDebug()<<"\r Total bytes"<<total << "\r done"<<done;
            bcheckupdates = false;
            ui->checkBox_HHC_SDK->setChecked(false);
            ui->checkBox_HHC_SDK->setDisabled(true);
            if(downloaddata.size() > 0)
            {
                count = count + 1;
            }
            on_pushButton_updates_clicked();
        }
        if(strDownloadfile.contains("Program") && ba.size() > 0)
        {
            qDebug()<<"\r Total bytes"<<total << "\r done"<<done;

            QFile file("/tmp/"+strDownloadfile);
            if(file.open(QIODevice::ReadWrite | QIODevice::Text))
            {
                file.write(ba);
            }
            file.close();

            system(QString("chmod 777 /tmp/"+strDownloadfile).toLatin1());
            QString copycmd = "cp /tmp/"+strDownloadfile  +" /mnt";
            const char *ch1;
            ch1 = copycmd.toLatin1();
            system(QString(ch1).toLatin1());

            ftp->close();
            ba.clear();
            progressDialog->hide();
            bcheckupdates=true;
            ui->checkBox_CoProcessor->setChecked(false);
            ui->checkBox_CoProcessor->setDisabled(true);
            if(downloaddata.size() > 0)
            {
                count = count + 1;
            }
        }
    }
    if(updatecount == count)
    {
        g_ccmainObj->disableGprs();
        if(count != 0)
            g_ccmainObj->shutDown();
    }
}

void Patchupdates::checkfile()
{
    QString strroot,strlib,strhex;
    CSettingsFiles file1;
    file1.beginSettingsGroup("ROOT");
    strroot = file1.value("root");
    strlib  = file1.value("usr");
    strhex   = file1.value("mnt");
    qDebug()<<"strRoot"<<strroot <<strlib <<strhex;
    if(strroot.trimmed() != RELEASEVERSION)
    {
        enablePushbutton();
        downloaddata.append(strroot);
        ui->checkBox_Clancor_HHC->setVisible(true);
        ui->checkBox_Clancor_HHC->setChecked(true);
        ui->label_Ver_Clancor->setText("Available Ver:"+strroot);
        ui->checkBox_Clancor_HHC->move(10,74);
        ui->label_Ver_Clancor->move(150,74);
    }
    if(strlib.trimmed() != BUILDVERSION)
    {
        enablePushbutton();
        downloaddata.append(strlib);
        ui->checkBox_HHC_SDK->setVisible(true);
        ui->checkBox_HHC_SDK->setChecked(true);
        ui->label_Ver_SDK->setText("Available Ver:"+strlib);
        ui->checkBox_Clancor_HHC->move(10,46);
        ui->label_Ver_Clancor->move(150,46);
        ui->checkBox_HHC_SDK->move(10,102);
        ui->label_Ver_SDK->move(150,102);
    }
    if(strhex.trimmed() != Pic32Version)
    {
        enablePushbutton();
        downloaddata.append(strhex);
        ui->checkBox_CoProcessor->setVisible(true);
        ui->checkBox_CoProcessor->setChecked(true);
        ui->label_Ver_Coprocessor->setText("Available Ver: "+strhex);
        ui->checkBox_Clancor_HHC->move(10,34);
        ui->label_Ver_Clancor->move(150,34);
        ui->checkBox_HHC_SDK->move(10,74);
        ui->label_Ver_SDK->move(150,74);
        ui->checkBox_CoProcessor->move(10,114);
        ui->label_Ver_Coprocessor->move(150,114);
    }
    if(downloaddata.size()== 0)
    {
        QMessageBox::critical(0,"FTP Download","No updates found");
    }
    updatecount = downloaddata.size();
}


void Patchupdates::listInfo2(QUrlInfo info)
{
    //    qDebug()<<"\rListing URL Info:"<<info.name()<<endl;
}

void Patchupdates::commandFinished(int id,bool error)
{
    qDebug()<<"\rCommand Finished! Id:"<<id<<"Status:"<<error<<endl;

    if (ftp->currentCommand() == QFtp::ConnectToHost)
    {
        if (error) {
            QMessageBox::information(this, tr("FTP"),
                                     tr("Unable to connect to the FTP server "
                                        "at %1. Please check that the host "
                                        "name is correct."));
            return;
        }
    }
    if (ftp->currentCommand() == QFtp::Login)
        ftp->list();
}

void Patchupdates::commandstarted(int id)
{   
    //        qDebug()<<"\rCommand Started ! Id:"<<id;
}


void Patchupdates::keyPressEvent(QKeyEvent * e)
{
    if(e->key() == Qt::Key_Escape)
    {
        g_ccmainObj->enableIdleMode(true);
        g_ccmainObj->disableGprs();
        this->close();
    }
}


void Patchupdates::on_checkBox_Clancor_HHC_clicked()
{
    if(!ui->checkBox_Clancor_HHC->isChecked())
    updatecount=updatecount-1;
}

void Patchupdates::on_checkBox_HHC_SDK_clicked()
{
    if(!ui->checkBox_HHC_SDK->isChecked())
    updatecount=updatecount-1;
}

void Patchupdates::on_checkBox_CoProcessor_clicked()
{
    if(!ui->checkBox_CoProcessor->isChecked())
    updatecount=updatecount-1;
}
