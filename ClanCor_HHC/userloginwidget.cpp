#include "userloginwidget.h"
#include "ui_userloginwidget.h"
#include "GlobalClass.h"
using namespace Globalclass;

UserLoginWidget::UserLoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLoginWidget)
{
    ui->setupUi(this);
    connect(ui->comboBox_LoginID->lineEdit(),SIGNAL(returnPressed()),this,SLOT(comboBox_LoginID_returnPressed()));
    isRunningApplication=false;
    QSqlQuery sqlQuery = db->SelectQuery("SELECT Name from userAccount where Type='U'");
    db->clearAll();
    if(db->IsLastError())
    {
        sqlQuery.clear();
        return;
    }
    while(sqlQuery.next())
    {
        ui->comboBox_LoginID->addItem(sqlQuery.value(0).toString());
    }
    sqlQuery.clear();
}

UserLoginWidget::~UserLoginWidget()
{
    delete ui;
}

void UserLoginWidget::comboBox_LoginID_returnPressed()
{
    if(ui->lineEdit_Password->isEnabled()==true)
    {
        ui->lineEdit_Password->setFocus();
    }
    else
    {
        ui->toolButton_login->setFocus();
    }
}
void UserLoginWidget::on_comboBox_LoginID_editTextChanged ( const QString & text )
{
    Q_UNUSED(text);
    isFingeprintOnly();
}

void UserLoginWidget::on_lineEdit_Password_returnPressed()
{
    ui->toolButton_login->setFocus();    
}

bool UserLoginWidget::isFingeprintOnly()
{
    QString userId;
    userId=ui->comboBox_LoginID->currentText().trimmed();
    QSqlQuery qry = db->SelectQuery("SELECT * from userAccount where Name='" +userId +"'" );
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
        return false;
    }
    if(qry.next())
    {
        int isFinger=qry.value(4).toInt();
        if(isFinger==1)
        {
            ui->lineEdit_Password->setEnabled(false);
        }
        else
        {
            ui->lineEdit_Password->setEnabled(true);
        }
    }
    else
    {
        ui->lineEdit_Password->setEnabled(true);
    }
    qry.clear();
    return ui->lineEdit_Password->isEnabled();
}

void UserLoginWidget::on_toolButton_login_clicked()
{
    QString userId;
    userId=ui->comboBox_LoginID->currentText().trimmed();
    Password=ui->lineEdit_Password->text().trimmed();
    QSqlQuery qry = db->SelectQuery("SELECT * from userAccount where Name='" +userId +"'" );
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
        return;
    }
    if(qry.next())
    {
        int isFinger=qry.value(4).toInt();
        if(qry.value(3).toString()=="A")
        {
            typeUser=false;
        }
        else
        {
            typeUser=true;
        }
        if(isFinger==1 || isFinger==2)
        {
            if(isFinger==2)
            {
                if(qry.value(2).toString()!=Password)
                {
                    qry.clear();
                    QMessageBox::critical(0,"Error..,","Invalid Password!");
                    ui->lineEdit_Password->setText("");
                    ui->lineEdit_Password->setFocus();
                    return;
                }
            }
            QByteArray saveFingerData;
//            bool Result;
            saveFingerData=qry.value(5).toByteArray();
            qry.clear();
/*            CFingerPrint *Fpt=new CFingerPrint();
            if(Fpt->verifyFinger(saveFingerData, Result))
            {
                if(Result==true)
                {
                    LoginId=userId;
                    if(ui->comboBox_LoginID->isEnabled())
                    {
                        delete this;                        
                        loadForm(DESKTOP, 0);
                    }
                    else
                    {
                        delete this;
                    }
                }
                else
                {
                    QMessageBox::critical(0,"Login","Invalid Finger!");
                }
                return;
            }
	    */
        }
        else
        {
            if(qry.value(2).toString()!=Password)
            {
                qry.clear();
                QMessageBox::critical(0,"UserLogin","Invalid Password!");
                ui->lineEdit_Password->setText("");
                ui->lineEdit_Password->setFocus();
            }
            else
            {
                LoginId=userId;
                if(ui->comboBox_LoginID->isEnabled())
                {
                    qry.clear();
                    delete this;                    
                    loadForm(DESKTOP, 0);
                }
                else
                {
                    delete this;
                }
            }
            return;
        }
    }
    else
    {
        QMessageBox::critical(0,"User Login","Invalid User!");
        if(ui->comboBox_LoginID->isEnabled())
        {
            stateStart();
        }
        else
        {
             ui->lineEdit_Password->setText("");
             ui->lineEdit_Password->setFocus();
        }
    }
    qry.clear();
}

void UserLoginWidget::stateStart()
{    
    ui->comboBox_LoginID->setCurrentIndex(-1);
    ui->lineEdit_Password->setText("");
    if(LoginId=="")
    {
        ui->comboBox_LoginID->setFocus();
    }
    else
    {
        ui->comboBox_LoginID->lineEdit()->setText(LoginId);
        ui->comboBox_LoginID->setEnabled(false);
        LoginId="";
        if(ui->lineEdit_Password->isEnabled()==true)
        {
            ui->lineEdit_Password->setFocus();
        }
        else
        {
            ui->toolButton_login->setFocus();
        }
    }
}

void UserLoginWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape )
    {
        return;
    }
}
