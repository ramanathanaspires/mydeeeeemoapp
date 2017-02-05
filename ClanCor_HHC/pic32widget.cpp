#include "pic32widget.h"
#include "ui_pic32widget.h"
#include "GlobalClass.h"
using namespace Globalclass;

Pic32Widget::Pic32Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pic32Widget)
{
    ui->setupUi(this);
}

Pic32Widget::~Pic32Widget()
{
    delete ui;
}

void Pic32Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape )
    {
        ui->spinBox_backLight->setFocus();
        return;
    }
    if(event->key() == Qt::Key_F4)
    {
        qApp->quit();
    }
}

void Pic32Widget::on_pushButton_setBacklight_clicked()
{
    g_ccmainObj->setBacklight(ui->spinBox_backLight->value());
}

void Pic32Widget::on_pushButton_setKeypadMode_clicked()
{
    if(ui->comboBox_keypadBeep->currentIndex()==0)
    {
        g_ccmainObj->setKeypadMode(ClanCor::eKeypadMode_NUMERIC);
    }
    else
    {
        g_ccmainObj->setKeypadMode(ClanCor::eKeypadMode_ALPHABETS);
    }
}

void Pic32Widget::on_pushButton_setBeep_clicked()
{
    if(ui->comboBox_Beep->currentIndex()==0)
    {
        g_ccmainObj->setBeep(ClanCor::eBeepType_SINGLE_BEEP);
    }
    else if(ui->comboBox_Beep->currentIndex()==1)
    {
        g_ccmainObj->setBeep(ClanCor::eBeepType_SUCCESS_BEEP);
    }
    else if(ui->comboBox_Beep->currentIndex()==2)
    {
        g_ccmainObj->setBeep(ClanCor::eBeepType_ERROR_BEEP);
    }
    else
    {
        g_ccmainObj->setBeep(ClanCor::eBeepType_LONG_BEEP);
    }
}

void Pic32Widget::on_pushButton_setkeypadBeep_clicked()
{
    if(ui->comboBox_keypadBeep->currentIndex()==0)
    {
        g_ccmainObj->setKeypadBeep(true);
    }
    else
    {
        g_ccmainObj->setKeypadBeep(false);
    }
}

void Pic32Widget::on_pushButton_getMachineId_clicked()
{
    QMessageBox::information(0,"Machine Id",g_ccmainObj->machineId());
}

void Pic32Widget::on_pushButton_testRTC_clicked()
{
    g_ccmainObj->testRtc();
}

void Pic32Widget::on_pushButton_testPrinter_clicked()
{
    CPrinter prn;
    //prn.testPrinter();
}
