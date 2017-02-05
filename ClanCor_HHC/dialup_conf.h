#ifndef DIALUP_CONF_H
#define DIALUP_CONF_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class dialup_conf;
    class dialup_entry;
}

class dialup_conf : public QDialog
{
    Q_OBJECT

public:
    explicit dialup_conf(QWidget *parent = 0);
    ~dialup_conf();

private:
    Ui::dialup_conf *ui;
    QStandardItemModel *model;

private slots:
    void on_btnDelete_clicked();
    void on_btnEdit_clicked();
    void on_btnAdd_new_clicked();
};


class dialup_entry : public QDialog
{
    Q_OBJECT

public:
    explicit dialup_entry(QString connection_name, QWidget *parent = 0);
    ~dialup_entry();
    bool editflag;

private:
    Ui::dialup_entry *ui;
    QString connection;

    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void slotclose();
};

#endif // DIALUP_CONF_H
