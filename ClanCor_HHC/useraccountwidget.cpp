#include "useraccountwidget.h"
#include "ui_useraccountwidget.h"
#include "newuserwidget.h"
#include "GlobalClass.h"
using namespace Globalclass;

UserAccountWidget::UserAccountWidget(QWidget *parent) :
    QDialog(),
    ui(new Ui::UserAccountWidget)
{
    ui->setupUi(this);
    parentPtr = parent;
    model = new QStandardItemModel(0, 3);
    model->setHeaderData(0, Qt::Horizontal, tr("SNo"));
    model->setHeaderData(1, Qt::Horizontal, tr("User Id"));
    model->setHeaderData(2, Qt::Horizontal, tr("Type"));
    ui->tableView_users->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableView_users->setModel(model);
    ui->tableView_users->setColumnWidth(0,35);
    ui->tableView_users->setColumnWidth(1,160);
    ui->tableView_users->setColumnWidth(2,70);
    if (LOGIN_MANAGEMENT ==  true) {
        ui->checkBox->setChecked(true);
        on_checkBox_stateChanged(Qt::Checked);
    }
    else {
        on_checkBox_stateChanged(Qt::Unchecked);
        ui->checkBox->setChecked(false);
    }
    ui->checkBox->setFocus();
}

UserAccountWidget::~UserAccountWidget()
{
    delete ui;
}

void UserAccountWidget::on_pushButton_add_clicked()
{
    if(ui->tableView_users->model()->rowCount()==5)
    {
        QMessageBox::information(0,"User Account","You can create Maximum 5 users only!");
        return;
    }
    this->close();
    delete this;
/*    NewUserWidget *userWidget =new NewUserWidget(MdiArea);
    userWidget->setWindowFlags(Qt::FramelessWindowHint);
    userWidget->setFixedSize(320,220);    
    userWidget->show();
    userWidget->adduser();
    */
}

void UserAccountWidget::on_pushButton_modify_clicked()
{
    QString UserName;
    QModelIndexList indexes = ui->tableView_users->selectionModel()->selection().indexes();
    int selected=indexes.at(0).row();
    UserName=ui->tableView_users->model()->index(selected,1).data().toString();
    this->close();
    delete this;
/*    NewUserWidget *userWidget =new NewUserWidget(MdiArea);
    userWidget->setWindowFlags(Qt::FramelessWindowHint);
    userWidget->setFixedSize(320,220);    
    userWidget->changeuser(UserName);
    userWidget->show();
    */
}

void UserAccountWidget::on_tableView_users_clicked(const QModelIndex &Index)
{
    if(Index.row()<1)
    {
        ui->pushButton_delete->setEnabled(false);
    }
    else
    {
        ui->pushButton_delete->setEnabled(true);
    }
}

void UserAccountWidget::on_pushButton_delete_clicked()
{
    QModelIndexList indexes = ui->tableView_users->selectionModel()->selection().indexes();
    int selected=indexes.at(0).row();
    if(selected==0)
    {
        QMessageBox::information(0,"User Account","You can't delete this account");
    }
    else
    {
        if(QMessageBox::question(0,"User Account","Do you want to Delete the user?",QMessageBox::Ok | QMessageBox::Cancel)==QMessageBox::Ok)
        {
            if(db->DataBaseCommand("Delete from userAccount where Name='" + ui->tableView_users->model()->index(selected,1).data().toString()+"'") ==true)
            {
                ui->tableView_users->model()->removeRow(selected);
                ui->tableView_users->selectRow(selected-1);
            }
        }
    }
}

void UserAccountWidget::on_pushButton_close_clicked()
{
    close();
    exitWndSlot();
}

void UserAccountWidget::stateStart()
{
    QSqlQuery sqlQuery = db->SelectQuery("SELECT Name,Type from userAccount");
    db->clearAll();
    if(db->IsLastError())
    {
        sqlQuery.clear();
        return;
    }
    int Row=0;
    while(sqlQuery.next())
    {
        model->insertRow(Row+1);
        model->setItem(Row,0,new QStandardItem(QVariant(Row+1).toString()));
        model->setItem(Row,1,new QStandardItem(sqlQuery.value(0).toString()));
        if(sqlQuery.value(1).toString()=="A")
        {
            model->setItem(Row,2,new QStandardItem("ADMIN"));
        }else
        {
            model->setItem(Row,2,new QStandardItem("USER"));
        }
        Row++;
    }
    sqlQuery.clear();
    ui->tableView_users->selectRow(Row-1);
    ui->pushButton_add->setFocus();
}

void UserAccountWidget::exitWndSlot()
{    
    this->setEnabled(false);
    qApp->processEvents();
    QSqlQuery qry = db->SelectQuery("SELECT IsNeedLogin from userAccount where Type='A'");
    db->clearAll();
    if(qry.next())
    {
        if(qry.value(0).toBool()==false)
        {
            LOGIN_MANAGEMENT = false;
        }
    }
    if(ui->checkBox->isChecked())
    {
        LOGIN_MANAGEMENT = true;
        db->DataBaseCommand("UPDATE userAccount set IsNeedLogin=1 where Type='A'");
    }
    else
    {
        db->DataBaseCommand("UPDATE userAccount set IsNeedLogin=0 where Type='A'");
        LOGIN_MANAGEMENT = false;
    }

    this->close();
    delete this;
}

void UserAccountWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        close();
        exitWndSlot();
    }
}

void UserAccountWidget::on_checkBox_stateChanged(int state)
{
    if(state==Qt::Checked)
    {        
        ui->pushButton_add->setEnabled(true);
        ui->pushButton_delete->setEnabled(true);
        ui->pushButton_modify->setEnabled(true);
        ui->tableView_users->setEnabled(true);
    }
    else
    {
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_modify->setEnabled(false);
        ui->tableView_users->setEnabled(false);
    }
}
