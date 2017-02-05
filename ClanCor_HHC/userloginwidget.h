#ifndef USERLOGINWIDGET_H
#define USERLOGINWIDGET_H

#include <QDialog>

namespace Ui {
    class UserLoginWidget;
}

class UserLoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit UserLoginWidget(QWidget *parent = 0);
    ~UserLoginWidget();
    void stateStart();
private:
    Ui::UserLoginWidget *ui;
    bool isRunningApplication;
    bool isFingeprintOnly();
    void keyPressEvent(QKeyEvent *event);
private slots:    
    void comboBox_LoginID_returnPressed();
    void on_comboBox_LoginID_editTextChanged ( const QString & text );
    void on_lineEdit_Password_returnPressed();
    void on_toolButton_login_clicked();
};

#endif // USERLOGINWIDGET_H
