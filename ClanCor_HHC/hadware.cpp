#include "hadware.h"
#include "ui_hadware.h"
#include <QFile>
#include <QDebug>
#include <GlobalClass.h>
#include <CPrinter>
using namespace Globalclass;
Hadware::Hadware(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hadware)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowFlags(Qt::FramelessWindowHint);
    g_ccmainObj->EnablePRINTERModule(true);
    QString ss,sa;
    QFile file;
    if(QFile::exists("/dev/mmcblk0"))
    {
        system(QString("df -h /dev/mmcblk0p1 | tail -n+2 | awk '{print $2}' > /etc/uma").toLatin1());
        file.setFileName("/etc/uma");
        if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly))
        {
            sa = "SD Card : Inserted ( " + QString(file.readAll()).remove("\n") +"B )";
        }
        file.close();
    }
    else
    {
        sa = "SD Card : NotInserted";
    }

    file.setFileName("/root/Configfile.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::WriteOnly))
    {
        ss.append(QString(file.readAll()));
        ss.replace("SD Card :",sa);
        ui->textEdit->setText(ss+"\n");
    }
    file.close();
    ui->pushButtonPrint->setAutoDefault(true);
    ui->textEdit->setTabChangesFocus(true);
    ui->textEdit->setReadOnly(true);
    ui->pushButtonPrint->setFocus();
}

Hadware::~Hadware()
{
    delete ui;
}

void Hadware::on_pushButtonPrint_clicked()
{
    if(ui->textEdit->toPlainText().trimmed()=="")
    {
        QMessageBox::information(0,"Machine Configuration","No data found");
        return;
    }
    CPrinter prn;
    prn.addData("Machine Configuration",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_CENTER);
    prn.addData(ui->textEdit->toPlainText(),CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_LEFT);
    prn.paperFeed(6);
    prn.print(false,false);
}

void Hadware::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key()== Qt::Key_Escape)
    {
        this->close();
    }

}
