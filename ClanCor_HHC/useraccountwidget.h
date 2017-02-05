#ifndef USERACCOUNTWIDGET_H
#define USERACCOUNTWIDGET_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
    class UserAccountWidget;
}

class UserAccountWidget : public QDialog
{
    Q_OBJECT

public:
    explicit UserAccountWidget(QWidget *parent = 0);
    ~UserAccountWidget();
    void stateStart();
private:
    Ui::UserAccountWidget *ui;
    QWidget *parentPtr;
    QStandardItemModel *model;
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_checkBox_stateChanged(int );
    void on_pushButton_add_clicked();
    void on_pushButton_modify_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_close_clicked();
    void on_tableView_users_clicked(const QModelIndex &Index);
    void exitWndSlot();
};

#endif // USERACCOUNTWIDGET_H
