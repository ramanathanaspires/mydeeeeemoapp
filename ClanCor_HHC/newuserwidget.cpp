#include "newuserwidget.h"
#include "ui_newuserwidget.h"
#include  <CFingerPrint>
#include "GlobalClass.h"
#include "useraccountwidget.h"
using namespace Globalclass;
NewUserWidget::NewUserWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserWidget)
{
    ui->setupUi(this);
    ui->pushButton_save->setShortcut(Qt::Key_F2);
    ui->pushButton_cancel->setShortcut(Qt::Key_F4);
    ui->pushButton_fingerPrint->setEnabled(false);
    ui->lineEdit_LoginID->setFocus();
}

NewUserWidget::~NewUserWidget()
{
    delete ui;
}

void NewUserWidget::adduser()
{
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_LoginID->setFocus();
}

void NewUserWidget::changeuser(const QString &UserId)
{
    ui->lineEdit_LoginID->setEnabled(false);
    QSqlQuery qry = db->SelectQuery("SELECT * from userAccount where Name='" +UserId +"'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
        return;
    }
    if(qry.next())
    {
        ui->lineEdit_LoginID->setText(UserId);
        ui->lineEdit_Password->setText(qry.value(2).toString());

        if(qry.value(4).toInt()==0)
        {
            ui->comboBox->setCurrentIndex(0);
        }
        else
        {
            QByteArray ba;
            QPixmap pixmap;
            ui->comboBox->setCurrentIndex(qry.value(4).toInt());
            ui->pushButton_fingerPrint->setText("");
            saveFingerData=qry.value(5).toByteArray();
            ba= qry.value(6).toByteArray();
            fingerPrintImage.loadFromData(ba,"jpg");
            pixmap=QPixmap::fromImage(fingerPrintImage.scaled(80,70));
            ui->pushButton_fingerPrint->setIcon(QIcon(pixmap));            
        }
    }
    ui->lineEdit_Password->setFocus();
}

void NewUserWidget::on_comboBox_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui->pushButton_fingerPrint->setEnabled(false);
    }
    else
    {
        ui->pushButton_fingerPrint->setEnabled(true);
    }
}

void NewUserWidget::on_pushButton_fingerPrint_clicked()
{
    setEnabled(false);
    saveFingerData.clear();
    /* call the API to construct Fingerprint object and capture the Finger
     * Data and Image.
     */
    CFingerPrint *Fpt=new CFingerPrint();
    if(Fpt->enrollFinger(saveFingerData, fingerPrintImage))
    {
        QPixmap pixmap;
        pixmap=QPixmap::fromImage(fingerPrintImage.scaled(80,70));
        ui->pushButton_fingerPrint->setText("");
        ui->pushButton_fingerPrint->setIcon(pixmap);
    }
    delete Fpt;
    setEnabled(true);
}

void NewUserWidget::on_pushButton_save_clicked()
{
    QString UserId,Password;
    UserId=ui->lineEdit_LoginID->text().trimmed();
    Password=ui->lineEdit_Password->text().trimmed();
    QByteArray fingerData;
    QBuffer bufferFinger(&fingerData);
    bufferFinger.open(QIODevice::WriteOnly);
    fingerPrintImage.save( &bufferFinger, "jpg" );
    bufferFinger.close();
    if(UserId=="")
    {
        QMessageBox::critical(0,"User Account","Please enter the User Id!");
        return;
    }
    if(ui->comboBox->currentIndex() > 0)
    {
        if(saveFingerData.count()==0)
        {
            QMessageBox::critical(0,"User Account","Please capture the fingerprint");
            return;
        }
    }
    if(ui->lineEdit_LoginID->isEnabled()==true)
    {
        QSqlQuery qry = db->SelectQuery("SELECT * from userAccount where Name='" +UserId +"'");
        db->clearAll();
        if(db->IsLastError())
        {
            qry.clear();
            return;
        }
        if(qry.next())
        {
            QMessageBox::critical(0,"Error...","This User name already exist!");
        }
        else
        {
            qry.clear();
            if(QMessageBox::question(0,"User Account","Do you want to Save the user?",QMessageBox::Ok | QMessageBox::Cancel)==QMessageBox::Ok)
            {
                QSqlQuery rs;
                if(ui->comboBox->currentIndex()==0)
                {
                    rs.prepare("insert into userAccount(Name,Password,Type,IsFprint,FingerData,FingerImage,IsNeedLogin) values(?,?,'U',0,NULL,NULL,1)");
                    rs.addBindValue(UserId);
                    rs.addBindValue(Password);
                }
                else
                {
                    rs.prepare("insert into userAccount(Name,Password,Type,IsFprint,FingerData,FingerImage,IsNeedLogin) values(?,?,'U',?,?,?,1)");
                    rs.addBindValue(UserId);
                    rs.addBindValue(Password);
                    rs.addBindValue(ui->comboBox->currentIndex());
                    rs.addBindValue(saveFingerData);
                    rs.addBindValue(fingerData);
                }
                if(!rs.exec())
                {
                    rs.clear();
                    QMessageBox::critical(0,"Error","Error in saving");
                }
                else
                {
                    rs.clear();
                    QMessageBox::information(0,"User Account","Saved Successfully...");
                    exitWndSlot();
                }
            }
        }
    }
    else
    {
        if(QMessageBox::question(0,"User Account","Do you want to Save the changes?",QMessageBox::Ok | QMessageBox::Cancel)==QMessageBox::Ok)
        {
            QSqlQuery rs;
            if(ui->comboBox->currentIndex() == 0 )
            {
                rs.prepare("update userAccount set Password=?,IsFprint=0,FingerData=NULL,FingerImage=NULL where Name=?");
                rs.addBindValue(Password);
                rs.addBindValue(UserId);
            }
            else
            {
                rs.prepare("update userAccount set Password=?,IsFprint=1,FingerData=?,FingerImage=? where Name=?");
                rs.addBindValue(Password);
                rs.addBindValue(saveFingerData);
                rs.addBindValue(fingerData);
                rs.addBindValue(UserId);
            }
            if(!rs.exec())
            {
                rs.clear();
                QMessageBox::critical(0,"Error","Error in saving");
            }
            else
            {
                rs.clear();
                QMessageBox::information(0,"User Account","Changed Successfully...");
                exitWndSlot();
            }
        }
    }
}

void NewUserWidget::on_pushButton_cancel_clicked()
{
    exitWndSlot();
}

void NewUserWidget::exitWndSlot()
{
    this->close();
    delete this;
    UserAccountWidget *userWidget =new UserAccountWidget(MdiArea);
    userWidget->setWindowFlags(Qt::FramelessWindowHint);
    userWidget->setFixedSize(320,220);    
    userWidget->show();
    userWidget->stateStart();
}

void NewUserWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        exitWndSlot();
    }
}
