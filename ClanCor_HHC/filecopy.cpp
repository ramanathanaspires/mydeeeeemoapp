#include "filecopy.h"
#include "ui_filecopy.h"
#include <GlobalClass.h>
#include <QDebug>
#include <QMessageBox>

using namespace Globalclass;

FileCopy::FileCopy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileCopy)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("File Copy");

    QIcon icon1;
    g_bFileCopyFlag = true;
    icon1.addFile(":/icons/new_back.png",QSize());
    ui->pushButtonSource->setIconSize(QSize(30,30));
    ui->pushButtonDestination->setIconSize(QSize(30,30));
    ui->pushButtonSource->setIcon(icon1);
    ui->pushButtonDestination->setIcon(icon1);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    ui->pushButtonCopy->setAutoDefault(true);
    ui->pushButtonSource->setAutoDefault(true);
    ui->pushButtonDestination->setAutoDefault(true);
    ui->pushButtonSource->setFocus();
}

FileCopy::~FileCopy()
{
    delete ui;
}

void FileCopy::on_pushButtonSource_clicked()
{
    QString strFilePath = "";

    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        strFilePath = QString(f->path +"/" + f->txtFilename->text());
        QFile myfile(strFilePath);
        if(myfile.permissions()==(0x10|0x100|0x200|0x400|0x1000|0x2000|0x4000))
        {
            qDebug()<<"checking permission";
        }
        else if(!myfile.setPermissions(QFile::ExeOwner|QFile::ReadOwner|QFile::WriteOwner|QFile::ExeGroup|QFile::ExeUser))
        {
            qDebug("some thing wrong!!!!!!!");
        }
    }
    delete f;
    ui->lineEditSource->setText(strFilePath);
    if(ui->lineEditSource->text() != "")
        ui->pushButtonDestination->setFocus();
    else
        ui->pushButtonSource->setFocus();
}

void FileCopy::on_pushButtonDestination_clicked()
{
    QString strFilePath = "";
    fileDialog *f = new fileDialog();
    f->option = "OpenDir";
    f->option="Save";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        strFilePath = QString(f->path);
    }
    delete f;
    ui->lineEditDestination->setText(strFilePath);
    if(ui->lineEditDestination->text() != "")
        ui->pushButtonCopy->setFocus();
    else
        ui->pushButtonDestination->setFocus();
}

void FileCopy::on_pushButtonCopy_clicked()
{
    SourcePath = ui->lineEditSource->text();
    DestinationPath = ui->lineEditDestination->text();
    QString copycmd = "cp "+SourcePath +" "+DestinationPath ;
    QString strComparepath;
    strComparepath=SourcePath.mid(SourcePath.lastIndexOf("/")+1,SourcePath.size());
    system(QString("ls -r "+DestinationPath+" > /root/FileCopytest").toLatin1());
    UpdateScreen(200);
    QFile file("/root/FileCopytest");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream textstreamObj(&file);
    QString strCheckingFilename = textstreamObj.readAll();
    QString samePath = SourcePath.mid(0,SourcePath.lastIndexOf("/")+1);
    if(ui->lineEditSource->isEnabled() && ui->lineEditDestination->isEnabled())
    {
        ui->pushButtonSource->setFocus();
        if(ui->lineEditSource->text()=="")
        {
            QMessageBox::information(0,"FileCopy","Please select the source file ");
            ui->pushButtonSource->setFocus();
            return;
        }
        else if(ui->lineEditDestination->text()=="")
        {
            QMessageBox::information(0,"FileCopy","Please select the destination file");
            ui->pushButtonDestination->setFocus();
            return;
        }
        else if(SourcePath.contains(" "))
        {
            QMessageBox::information(0,"FileCopy","Filename contains space \n So file cannot be Copied \n Please avoid space in filename");
            ui->pushButtonDestination->setFocus();
            return;
        }
        else if(samePath == DestinationPath)
        {
            QMessageBox::information(0,"FileCopy","File Cannot be Copied in samepath!");
            ui->lineEditSource->clear();
            ui->lineEditDestination->clear();
            ui->pushButtonSource->setFocus();
            return;
        }
        else if(strCheckingFilename.contains(strComparepath))
        {
            if(QMessageBox::information(0,"FileCopy","File exits...\n do you want to replace the file",
                                        QMessageBox::Yes |QMessageBox::No
                                        )==QMessageBox::Yes)
            {
                system( QString("rm "+DestinationPath+strComparepath).toLatin1());
                UpdateScreen(100);
                system( QString(copycmd).toLatin1());
                QMessageBox::information(0,"FileCopy","File Copied sucessfully.");
                ui->lineEditSource->clear();
                ui->lineEditDestination->clear();
                system("rm /root/FileCopytest");
                ui->pushButtonSource->setFocus();
                return;
            }
            else
            {
                system("rm /root/FileCopytest");
                ui->lineEditSource->clear();
                ui->lineEditDestination->clear();
                ui->pushButtonSource->setFocus();
                return;
            }
        }
        else
        {
            if(QMessageBox::information(0,"FileCopy","Are you sure \n You want to copy file to the destination path",
                                        QMessageBox::Yes |QMessageBox::No
                                        )==QMessageBox::Yes)
            {
                system( QString("cp "+SourcePath+"  "+DestinationPath).toLatin1());
                QMessageBox::information(0,"FileCopy","File Copied sucessfully..");
                ui->lineEditSource->clear();
                ui->lineEditDestination->clear();
                system("rm /root/FileCopytest");
                ui->pushButtonSource->setFocus();
                return;
            }
            else
            {
                system("rm /root/FileCopytest");
                ui->lineEditSource->clear();
                ui->lineEditDestination->clear();
                ui->pushButtonSource->setFocus();
                return;
            }
        }
    }
    else
    {
        ui->lineEditSource->setEnabled(true);
        ui->lineEditDestination->setEnabled(true);
        ui->pushButtonDestination->setEnabled(true);
        ui->pushButtonSource->setEnabled(true);
        ui->lineEditSource->setFocus();
        return;
    }

}
void FileCopy::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key()== Qt::Key_Escape)
    {
        g_bFileCopyFlag = false;
        this->close();
    }
}


void FileCopy::on_pushButtonRemove_clicked()
{
    ui->lineEditDestination->setEnabled(false);
    ui->pushButtonDestination->setEnabled(false);
    SourcePath = ui->lineEditSource->text();
    if(SourcePath =="")
    {
        QMessageBox::information(0,"FileCopy","Please select the source file to remove");
        ui->lineEditDestination->setEnabled(true);
        ui->pushButtonDestination->setEnabled(true);
        ui->lineEditSource->clear();
        ui->lineEditDestination->clear();
        ui->pushButtonSource->setFocus();
        return;
    }
    else if(SourcePath.contains("ClanCor_HHC") || SourcePath.contains("libHHC81xx.so"))
    {
        QMessageBox::information(0,"FileCopy","This file cannot be removed");
        ui->lineEditDestination->setEnabled(true);
        ui->pushButtonDestination->setEnabled(true);
        ui->lineEditSource->clear();
        ui->lineEditDestination->clear();
        ui->pushButtonSource->setFocus();
        return;
    }
    else if(QMessageBox::information(0,"FileCopy","Are you sure \n You want to remove file specified in the source path?",
                                     QMessageBox::Yes |QMessageBox::No
                                     )==QMessageBox::Yes)
    {
        system( QString("rm "+SourcePath).toLatin1());
        UpdateScreen(100);
        QMessageBox::information(0,"FileCopy","File removed sucessfully..");
        ui->lineEditDestination->setEnabled(true);
        ui->pushButtonDestination->setEnabled(true);
        ui->lineEditSource->clear();
        ui->lineEditDestination->clear();
        ui->pushButtonSource->setFocus();
    }
    else
    {
        ui->lineEditDestination->setEnabled(true);
        ui->pushButtonDestination->setEnabled(true);
        ui->lineEditSource->clear();
        ui->lineEditDestination->clear();
        ui->pushButtonSource->setFocus();
    }
}
