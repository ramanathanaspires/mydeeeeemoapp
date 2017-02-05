#include "emulator.h"
#include "ui_emulator.h"
#include <GlobalClass.h>
#include<QDebug>

using namespace Globalclass;

Emulator::Emulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emulator)
{
    ui->setupUi(this);
    setParent(MdiArea);
    process = new QProcess;
    ui->textEdit->setReadOnly(true);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit->setFocus();
}

Emulator::~Emulator()
{
    delete ui;
}

void Emulator::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void Emulator::on_lineEdit_returnPressed()
{
    commandexe = ui->lineEdit->text();
    if(commandexe.mid(0,2)=="vi"||commandexe.mid(0,2)=="rm"||commandexe.mid(0,3)=="top")
    {
        return;
    }
    else
    {
        if(commandexe.mid(0,4)=="ping")
            commandexe+=" -c 5";
        process->start(commandexe);
        QByteArray byteobj;
        process->setProcessChannelMode(QProcess::SeparateChannels);
        while(process->state() == QProcess::Running || process->state() == QProcess::Starting)
        {
            if(process->waitForFinished(1000))
            {
                byteobj.append(process->readAllStandardOutput());
                QString strprocess(byteobj);
                ui->textEdit->setText(strprocess);
                ui->lineEdit->clear();
            }
        }
    }
}
