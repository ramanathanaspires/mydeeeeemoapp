#include "dialog.h"
#include "ui_dialog.h"

#include <QProcess>
#include <QMessageBox>
#include <GlobalClass.h>
using namespace Globalclass;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setParent(MdiArea);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    bool bReturn;
    QString strResponse;
    ClanCor::CHHC80xx::SMagneticCardRead sMageneticCardRead;
    bReturn = g_ccmainObj->readMageneticCard(ClanCor::eMagneticCard_Read_ALL,sMageneticCardRead);

    if(bReturn)
    {
        ui->label_Card_No->setText(sMageneticCardRead.m_strTrack1);
        ui->label_Name->setText(sMageneticCardRead.m_strTrack2);
        ui->label_Valid->setText(sMageneticCardRead.m_strTrack3);
    }
    else
    {
        QMessageBox::critical(0, "Error - Magnetic Card read", "Failed Reading Magnic Card..");
    }
}
void Dialog::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key()== Qt::Key_Escape)
    {
            this->close();
    }

}
//void Dialog::on_pushButton_2_clicked()
//{
//    if(!objCHHC80xx.enableGprs())
//    {
//        ui->textEdit->setText(objCHHC80xx.lastError());
//    }
//    else
//    {
//        QProcess process;
//        process.setProcessChannelMode(QProcess::SeparateChannels);
//        process.start("ping -c 5 122.165.223.135");
//        while(process.state() == QProcess::Running || process.state() == QProcess::Starting)
//        {
//            if(process.waitForFinished(1000))
//            {
//                ui->textEdit->append(process.readAllStandardOutput());
//                ui->textEdit->append(process.readAllStandardError());
//            }
//        }
//        process.reset();
//    }
//}

//void Dialog::on_pushButton_3_clicked()
//{
//    if(!objCHHC80xx.disableGprs())
//    {
//        ui->textEdit->setText(objCHHC80xx.lastError());
//    }
//}
