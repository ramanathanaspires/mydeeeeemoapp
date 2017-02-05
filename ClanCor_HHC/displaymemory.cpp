#include "displaymemory.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include "ui_displaymemory.h"
#include<sys/statvfs.h>

DisplayMemory::DisplayMemory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayMemory)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->progressBarFlashUsedMemory->setFocus();
    Memory_status();
}

DisplayMemory::~DisplayMemory()
{
    delete ui;
}

void DisplayMemory::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key()== Qt::Key_Escape)
    {
        this->close();
    }
}

void DisplayMemory::Memory_status()
{
    //For Pendrive process
    system("df -h | grep /dev/sd > /root/Memory");//For pendrive for device
    QFile file("/root/Memory");
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream in(&file);
        QString str = in.readAll();
        if(str =="")
        {
            ui->progressBarThumbdriveUsedMemory->hide();
            ui->labelPendriveMem->hide();
            ui->labelPendrivetitle->hide();
        }
        else
        {
            QStringList strSplit;
            QString strDisplay;
            strSplit = str.split(" ");
            strDisplay=strSplit.at(22)+" / "+strSplit.at(17);
            ui->labelPendriveMem->setText(strDisplay);
            ui->progressBarThumbdriveUsedMemory->setValue(str.mid((str.lastIndexOf("/media/thumbdrive")-4),2).toInt());
        }
        system("rm /root/Memory");
        file.close();
    }

    //For SD Card memory size
    system(" df -h | grep /dev/mmcblk0p1  > /root/Memory");//For flash for device
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream in(&file);
        QString str = in.readAll();
        if(str =="")
        {
            ui->progressBarSDUsedMemory->hide();
            ui->labelSDMem->hide();
            ui->labelSDtitle->hide();
            if(!ui->progressBarThumbdriveUsedMemory->isHidden())
            {
                ui->progressBarRAMUsedMemory->move(140,65);
                ui->labelRAMtitle->move(3,65);
                ui->labelRAMMem->move(143,46);
                ui->progressBarFlashUsedMemory->move(140,110);
                ui->labelFlashtitle->move(3,110);
                ui->labelFlashMem->move(143,91);
                ui->progressBarThumbdriveUsedMemory->move(140,155);
                ui->labelPendrivetitle->move(3,155);
                ui->labelPendriveMem->move(143,136);
            }
            else
            {
                ui->progressBarRAMUsedMemory->move(140,85);
                ui->labelRAMtitle->move(3,85);
                ui->labelRAMMem->move(143,66);
                ui->progressBarFlashUsedMemory->move(140,130);
                ui->labelFlashtitle->move(3,130);
                ui->labelFlashMem->move(143,111);
            }
        }
        else
        {
            QStringList strSplit;
            QString strDisplay;
            strSplit = str.split(" ");
            strDisplay=strSplit.at(14)+" / "+strSplit.at(10);
            ui->labelSDMem->setText(strDisplay);
            ui->progressBarSDUsedMemory->setValue(str.mid((str.lastIndexOf("/media/sdcard")-4),2).toInt());
            if(ui->progressBarThumbdriveUsedMemory->isHidden())
            {
                ui->progressBarRAMUsedMemory->move(140,65);
                ui->labelRAMtitle->move(3,65);
                ui->labelRAMMem->move(143,46);
                ui->progressBarFlashUsedMemory->move(140,110);
                ui->labelFlashtitle->move(3,110);
                ui->labelFlashMem->move(143,91);
                ui->progressBarSDUsedMemory->move(140,155);
                ui->labelSDtitle->move(3,155);
                ui->labelSDMem->move(143,136);
            }
        }
        system("rm /root/Memory");
        file.close();
    }

    //For RAM process
    //    system("cat /proc/meminfo > /home/mahe/Desktop/Memory");//For RAM checking for PC
    system("cat /proc/meminfo > /root/Memory");//For RAM checking for device
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream in(&file);
        QString str = in.readAll();
        int nTotalmem,nFreemem,nUsedmem;
        nTotalmem=str.mid(17,str.lastIndexOf("MemF")-20).toInt();
        nFreemem=str.mid(46,str.indexOf("Buffers:")-50).toInt();
        ////        nUsedmem= (nTotalmem - nFreemem)/1000;
        //        nUsedmem= ((nTotalmem - nFreemem)/nTotalmem)*100;
        //        ui->progressBarRAMUsedMemory->setValue(nUsedmem);
        //New alteration
        nUsedmem = (nTotalmem - nFreemem);
        nUsedmem = nUsedmem/nTotalmem;
        nUsedmem =  (nUsedmem)*(100);
        ui->progressBarRAMUsedMemory->setValue(nUsedmem);
        system("rm /root/Memory");
        file.close();
    }
    system("free help | grep Mem: > /root/Memory");//For RAM for device
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream in(&file);
        QString str = in.readAll();
        QStringList strSplit;
        QString strDisplay;
        strSplit = str.split(" ");
        //        strDisplay=strSplit.at(17)+"M  /  "+strSplit.at(9)+"M";
        strDisplay=strSplit.at(17)+"MB / "+strSplit.at(9)+"MB";
        ui->labelRAMMem->setText(strDisplay);
        system("rm /root/Memory");
        file.close();
    }

    //Testing flash memory
    system(" df -h | grep ubi0:root  > /root/Memory");//For flash for device
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream in(&file);
        QString str = in.readAll();
        QStringList strSplit;
        QString strDisplay;
        strSplit = str.split(" ");
        //        strDisplay=strSplit.at(20)+" / "+strSplit.at(15);
        strDisplay=strSplit.at(20)+"B"+" / "+strSplit.at(15)+"B";
        ui->labelFlashMem->setText(strDisplay);
        ui->progressBarFlashUsedMemory->setValue(str.mid((str.lastIndexOf("/")-4),2).toInt());
        system("rm /root/Memory");
        file.close();
    }
    //MemTotal:
}
