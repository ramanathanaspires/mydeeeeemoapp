#include "gpssettings.h"
#include "ui_gpssettings.h"

#include "GlobalClass.h"
using namespace Globalclass;

GpsSettings::GpsSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GpsSettings)
{
    ui->setupUi(this);
    ui->pushButton_save->setShortcut(Qt::Key_F2);
    ui->pushButton_cancel->setShortcut(Qt::Key_F4);
    ui->checkBox->setShortcut(Qt::Key_F1);
    setParent(MdiArea);
    setWindowTitle("AGPS Settings");
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    QSqlQuery qry_agps;
    qry_agps = db->SelectQuery("select * from agps_settings");
    db->clearAll();
    if(!db->IsLastError())
    {
        if(qry_agps.next())
        {
            ui->lineEdit_ftp_url->setText(qry_agps.value(0).toString());
            ui->lineEdit_userName->setText(qry_agps.value(1).toString());
            ui->lineEdit_password->setText(qry_agps.value(2).toString());
            if(qry_agps.value(3).toBool()==true)
            {
                ui->checkBox->setChecked(true);
            }
            else
            {
                ui->checkBox->setChecked(false);
            }
        }
    }
    qry_agps.clear();
    ui->lineEdit_ftp_url->setFocus();
}

GpsSettings::~GpsSettings()
{
    delete ui;
}

void GpsSettings::on_pushButton_save_clicked()
{
    if(ui->lineEdit_ftp_url->text() == "")
    {
        QMessageBox::information(0,"AGPS","Enter Ftp url before Saving ..");
        ui->lineEdit_ftp_url->setFocus();
        return;
    }
    QUrl url(ui->lineEdit_ftp_url->text());
    if(!url.isValid())
    {
        QMessageBox::information(0,"AGPS","Invalid Url...");
        ui->lineEdit_ftp_url->setFocus();
        return;
    }
    if(ui->lineEdit_userName->text() == "")
    {
        QMessageBox::information(0,"AGPS","Enter UserName before saving ..");
        ui->lineEdit_userName->setFocus();
        return;
    }
    if(ui->lineEdit_password->text() == "")
    {
        QMessageBox::information(0,"AGPS","Enter Password before saving ..");
        ui->lineEdit_password->setFocus();
        return;
    }
    QSqlQuery rs(db->cn);
    rs.exec("delete from agps_settings ");
    rs.prepare("INSERT INTO agps_settings(FtpPath,Username,Password,Automatic)VALUES(?,?,?,?)");
    rs.addBindValue(ui->lineEdit_ftp_url->text());
    rs.addBindValue(ui->lineEdit_userName->text());
    rs.addBindValue(ui->lineEdit_password->text());
    rs.addBindValue(ui->checkBox->isChecked());
    if(!rs.exec())
    {
       QMessageBox::critical(0,"AGPS","Failed to save settings");
       return;
    }
    else
    {
        QMessageBox::information(0,"AGPS","Saved Successfully...");
        rs.clear();
    }
    rs.clear();
    reject();
}

void GpsSettings::on_pushButton_cancel_clicked()
{
    reject();
}

void GpsSettings::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape || e->key() == Qt::Key_F4)
    {
        reject();
    }
    else
    {
        QDialog::keyPressEvent(e);
    }
}
