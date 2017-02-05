#include "dialup_conf.h"
#include "ui_dialup_conf.h"
#include "ui_dialup_entry.h"

#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>


#include "GlobalClass.h"
using namespace Globalclass;

dialup_conf::dialup_conf(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::dialup_conf)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("Dial-up Settings");
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("[F2] Ok");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("[F4] Cancel");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setShortcut(Qt::Key_F2);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(Qt::Key_F4);

    model = new QStandardItemModel;
    ui->listView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setModel(model);
    QStandardItem *item;
    int i = 0;
    QSqlQuery qry_dialupentry;
    QModelIndex curr_index;

    qry_dialupentry = db->SelectQuery("select * from sqlite_master where name like 'dialup_settings'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry_dialupentry.clear();
        return;
    }
    if(qry_dialupentry.next())
    {
        qry_dialupentry.clear();
        qry_dialupentry = db->SelectQuery("select * from dialup_settings");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_dialupentry.clear();
            return;
        }
        while(qry_dialupentry.next())
        {

            item = new QStandardItem(qry_dialupentry.value(0).toString());
            model->setItem(i, 0, item);
            if(qry_dialupentry.value(3).toBool())
            {
                curr_index = model->index(model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
                QFont f;
                f.setBold(true);
                item = model->item(curr_index.row(), curr_index.column());
                item->setFont(f);

                model->setItem(i, 0, item);
            }
            i++;
        }

        if(curr_index.row() == -1)
            ui->listView->setCurrentIndex(model->index(0,0));
        else
            ui->listView->setCurrentIndex(curr_index);
        qry_dialupentry.clear();
        if(i == 5)
            ui->btnAdd_new->setEnabled(false);

        ui->btnEdit->setEnabled(true);
        ui->btnDelete->setEnabled(true);
    }
    else
    {
        qry_dialupentry.clear();
        if(model->rowCount(QModelIndex()) == 0)
        {
            item = new QStandardItem("No connection added");
            model->setItem(i, 0, item);
            ui->btnEdit->setEnabled(false);
            ui->btnDelete->setEnabled(false);
        }
    }
    ui->listView->setFocus();
}

dialup_conf::~dialup_conf()
{
    delete ui;
}

void dialup_conf::on_btnAdd_new_clicked()
{
    setVisible(false);
    setEnabled(false);

    if(model->rowCount() > 5)
    {
        QMessageBox::critical(0,"Error - New dialup connection","Maximum number of connections reached..");
        setVisible(true);
        setEnabled(true);
        ui->btnAdd_new->setFocus();
        return;
    }

    dialup_entry *newconnObj;
    if(ui->listView->currentIndex().row() != -1 || model->rowCount() != 0)
    {
        if(model->itemFromIndex(ui->listView->currentIndex())->text() == "No connection added")
            newconnObj = new dialup_entry("Connection" + QString::number(1));
        else
            newconnObj = new dialup_entry("Connection" + QString::number(model->rowCount() + 1));
    }
    else
    {
        newconnObj = new dialup_entry("Connection" + QString::number(1));
    }
    newconnObj->editflag = false;
    newconnObj->exec();

    if(newconnObj->result() == QDialog::Accepted)
    {
        QSqlQuery qry_dialupentry;

        qry_dialupentry = db->SelectQuery("select * from sqlite_master where name like 'dialup_settings'");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_dialupentry.clear();
            setVisible(true);
            setEnabled(true);
            ui->btnAdd_new->setFocus();
            return;
        }
        if(qry_dialupentry.next())
        {
            qry_dialupentry.clear();
            model->clear();
            qry_dialupentry = db->SelectQuery("select * from dialup_settings");
            db->clearAll();
            if(db->IsLastError())
            {
                qry_dialupentry.clear();
                setVisible(true);
                setEnabled(true);
                ui->btnAdd_new->setFocus();
                return;
            }
            QStandardItem *item;
            int i = 0;
            QModelIndex curr_index;
            while(qry_dialupentry.next())
            {

                item = new QStandardItem(qry_dialupentry.value(0).toString());
                model->setItem(i, 0, item);
                if(qry_dialupentry.value(3).toBool())
                {
                    curr_index = model->index(model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
                    QFont f;
                    f.setBold(true);
                    item = model->item(curr_index.row(), curr_index.column());
                    item->setFont(f);

                    model->setItem(i, 0, item);
                }
                i++;
            }
            if(curr_index.row() == -1)
                ui->listView->setCurrentIndex(model->index(0,0));
            else
                ui->listView->setCurrentIndex(curr_index);
        }
        qry_dialupentry.clear();
        if(!ui->btnEdit->isEnabled())
            ui->btnEdit->setEnabled(true);
        if(!ui->btnDelete->isEnabled())
            ui->btnDelete->setEnabled(true);
        if(model->rowCount() == 5)
            ui->btnAdd_new->setEnabled(false);
    }
    delete newconnObj;

    setVisible(true);
    setEnabled(true);
    ui->btnAdd_new->setFocus();
}

void dialup_conf::on_btnEdit_clicked()
{
    setVisible(false);
    setEnabled(false);
    if(model->rowCount(QModelIndex()) > 0)
    {
        if(model->itemFromIndex(ui->listView->currentIndex())->text() != "")
        {
            dialup_entry *newconnObj = new dialup_entry(model->itemFromIndex(ui->listView->currentIndex())->text() );
            newconnObj->editflag = true;
            newconnObj->exec();

            if(newconnObj->result() == QDialog::Accepted)
            {
                QSqlQuery qry_dialupentry;

                qry_dialupentry = db->SelectQuery("select * from sqlite_master where name like 'dialup_settings'");
                db->clearAll();
                if(db->IsLastError())
                {
                    qry_dialupentry.clear();
                    setVisible(true);
                    setEnabled(true);
                    ui->btnEdit->setFocus();
                    return;
                }
                if(qry_dialupentry.next())
                {
                    qry_dialupentry.clear();
                    model->clear();
                    qry_dialupentry = db->SelectQuery("select * from dialup_settings");
                    db->clearAll();
                    if(db->IsLastError())
                    {
                        qry_dialupentry.clear();
                        setVisible(true);
                        setEnabled(true);
                        ui->btnEdit->setFocus();
                        return;
                    }
                    QStandardItem *item;
                    int i = 0;
                    QModelIndex curr_index;
                    while(qry_dialupentry.next())
                    {
                        item = new QStandardItem(qry_dialupentry.value(0).toString());
                        model->setItem(i, 0, item);
                        if(qry_dialupentry.value(3).toBool())
                        {
                            curr_index = model->index(model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
                            QFont f;
                            f.setBold(true);
                            item = model->item(curr_index.row(), curr_index.column());
                            item->setFont(f);

                            model->setItem(i, 0, item);
                        }
                        i++;
                    }
                    if(curr_index.row() == -1)
                        ui->listView->setCurrentIndex(model->index(0,0));
                    else
                        ui->listView->setCurrentIndex(curr_index);
                }
                qry_dialupentry.clear();
            }
            delete newconnObj;
        }
    }
    setVisible(true);
    setEnabled(true);
    ui->btnEdit->setFocus();
}

void dialup_conf::on_btnDelete_clicked()
{
    setEnabled(false);
    if(model->rowCount(QModelIndex()) > 0)
    {
        if(model->itemFromIndex(ui->listView->currentIndex())->text() != "")
        {
            QSqlQuery qry_dialupentry;

            qry_dialupentry = db->SelectQuery("select * from dialup_settings where Active_status like 'true'");
            db->clearAll();
            if(db->IsLastError())
            {
                qry_dialupentry.clear();
                setEnabled(true);
                ui->btnDelete->setFocus();
                return;
            }
            if(qry_dialupentry.next())
            {
                if(model->itemFromIndex(ui->listView->currentIndex())->text() == qry_dialupentry.value(0).toString())
                {
                    QMessageBox::critical(0,"Error - Delete connection","Active connection can not be deleted..");
                    qry_dialupentry.clear();
                    setEnabled(true);
                    ui->btnDelete->setFocus();
                    return;
                }
            }
            qry_dialupentry.clear();

            bool b = db->DataBaseCommand("delete from dialup_settings where Connection_name = '" + model->itemFromIndex(ui->listView->currentIndex())->text() + "'");
            if(!b)
            {
                QMessageBox::critical(0,"Error - Delete connection","Error while deleting the connection..");
                setEnabled(true);
                ui->btnDelete->setFocus();
                return;
            }
            model->removeRow(ui->listView->currentIndex().row(), QModelIndex());
            if(model->rowCount() == 0)
            {
                ui->btnDelete->setEnabled(false);
                ui->btnEdit->setEnabled(false);
            }
            if(model->rowCount() < 5)
                ui->btnAdd_new->setEnabled(true);
        }
    }
    setEnabled(true);
    ui->btnDelete->setFocus();
}


/*************************Dialup Entry form for new Connection****************/

dialup_entry::dialup_entry(QString connection_name, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::dialup_entry)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("New Dial-up connection");
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);

    connection = connection_name;
    connection_name.clear();
    ui->cmbNetwork->addItem("GPRS");
    ui->cmbNetwork->addItem("PSTN");
    QSqlQuery qry_dialupentry;
    qry_dialupentry = db->SelectQuery("select * from sqlite_master where name like 'dialup_settings'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry_dialupentry.clear();
        return;
    }
    if(qry_dialupentry.next())
    {
        qry_dialupentry.clear();
        qry_dialupentry = db->SelectQuery("select * from dialup_settings where Connection_name like '"+ connection +"'");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_dialupentry.clear();
            return;
        }
        if(qry_dialupentry.next())
        {
            ui->txtConnectionName->setText(qry_dialupentry.value(0).toString());
            int i = 0;
            while(ui->cmbNetwork->count() > i)
            {
                if(ui->cmbNetwork->itemText(i) == qry_dialupentry.value(1).toString())
                {
                    ui->cmbNetwork->setCurrentIndex(i);
                }
                i++;
            }

            if(qry_dialupentry.value(2).toString() == "Always_On")
                ui->rbtnAlways_On->setChecked(true);
            else if(qry_dialupentry.value(2).toString() == "Manual")
                ui->rbtnManual->setChecked(true);
        }
        else
        {
            ui->txtConnectionName->setText(connection);
        }
    }
    else
    {
        qry_dialupentry.clear();
        QMessageBox::critical(0, "Error - New dialup connection", "Error in dialup_settings table..");
        return;
    }
    if(!editflag)
        ui->rbtnManual->setChecked(true);
    ui->txtConnectionName->setFocus();
}

dialup_entry::~dialup_entry()
{
    delete ui;
}

void dialup_entry::on_btnOk_clicked()
{
    if(ui->txtConnectionName->text() == "")
    {
        QMessageBox::critical(0,"Error - New dialup connection","Enter Connection name before saving ..");
        return;
    }

    QSqlQuery qry_dialupentry;
    qry_dialupentry = db->SelectQuery("select * from sqlite_master where name like 'dialup_settings'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry_dialupentry.clear();
        return;
    }
    if(qry_dialupentry.next())
    {
        qry_dialupentry.clear();
        qry_dialupentry = db->SelectQuery("select * from dialup_settings where Connection_name like '"+ ui->txtConnectionName->text() +"'");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_dialupentry.clear();
            return;
        }
        if(qry_dialupentry.next())
        {
            if(!editflag)
            {
                qry_dialupentry.clear();
                QMessageBox::critical(0, "Error - New dialup connection", "Connection name already exists...\n\tUse a different name...");
                return;
            }
        }
        qry_dialupentry.clear();
        qry_dialupentry = db->SelectQuery("select * from dialup_settings");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_dialupentry.clear();
            return;
        }
        int No_of_recs = db->Size(qry_dialupentry);
        qry_dialupentry.clear();

        if(No_of_recs > 0)
        {
            int res=QMessageBox::information(0, "Dialup connection", "Do you want to make this connection, \n\t as default active connection?",QMessageBox::Yes,QMessageBox::No);
            if(res==QMessageBox::Yes)
            {
                bool b = false;
                b = db->DataBaseCommand("update dialup_settings set Active_status = 'false'");
                if(!b)
                {
                    QMessageBox::critical(0,"Error - New dialup connection","Error in saving the new connection");
                    return;
                }
                if(editflag)
                {
                    if(ui->rbtnAlways_On->isChecked())
                        b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnAlways_On->accessibleName() + "', Active_status = 'true' where Connection_name = '" + connection + "'");
                    else
                        b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnManual->accessibleName() + "', Active_status = 'true' where Connection_name = '" + connection + "'");
                }
                else
                {
                    if(ui->rbtnAlways_On->isChecked())
                        b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnAlways_On->accessibleName() + "','true')");
                    else
                        b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnManual->accessibleName() + "','true')");
                }
                if(!b)
                {
                    QMessageBox::critical(0,"Error - New dialup connection","Error in saving the new connection");
                    return;
                }
            }
            else
            {
                bool b = false;
                if(editflag)
                {
                    if(ui->rbtnAlways_On->isChecked())
                        b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnAlways_On->accessibleName() + "', Active_status = 'false' where Connection_name = '" + connection + "'");
                    else
                        b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnManual->accessibleName() + "', Active_status = 'false' where Connection_name = '" + connection + "'");
                }
                else
                {
                    if(ui->rbtnAlways_On->isChecked())
                        b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnAlways_On->accessibleName() + "', 'false')");
                    else
                        b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnManual->accessibleName() + "', 'false')");
                }
                if(!b)
                {
                    QMessageBox::critical(0,"Error - New dialup connection","Error in saving the new connection");
                    return;
                }
            }
        }
        else
        {
            bool b;
            if(editflag)
            {
                if(ui->rbtnAlways_On->isChecked())
                    b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnAlways_On->accessibleName() + "', Active_status = 'true' where Connection_name = '" + connection + "'");
                else
                    b = db->DataBaseCommand("update dialup_settings set Connection_name = '" + ui->txtConnectionName->text() + "', Network = '" + ui->cmbNetwork->currentText() + "', Connection_type = '" + ui->rbtnManual->accessibleName() + "', Active_status = 'true' where Connection_name = '" + connection + "'");
            }
            else
            {
                if(ui->rbtnAlways_On->isChecked())
                    b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnAlways_On->accessibleName() + "','true')");
                else
                    b = db->DataBaseCommand("insert into dialup_settings(Connection_name, Network, Connection_type, Active_status) values('" + ui->txtConnectionName->text() + "','" + ui->cmbNetwork->currentText() + "','" + ui->rbtnManual->accessibleName() + "','true')");
            }
            if(!b)
            {
                QMessageBox::critical(0,"Error - New dialup connection","Error in saving the new connection");
                return;
            }
        }
    }
    else
    {
        qry_dialupentry.clear();
        QMessageBox::critical(0, "Error - New dialup connection", "Error in dialup_settings table..");
        return;
    }
    QMessageBox::information(0, "Saved - New Connection", "New connection has been saved successfully..");
    accept();
}



void dialup_entry::on_btnCancel_clicked()
{
    slotclose();
}

void dialup_entry::slotclose()
{
    reject();
}

void dialup_entry::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape || e->key() == Qt::Key_F4)
    {
        slotclose();
    }

    else
    {
        QDialog::keyPressEvent(e);
    }
}
