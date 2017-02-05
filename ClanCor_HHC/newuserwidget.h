#ifndef NEWUSERWIDGET_H
#define NEWUSERWIDGET_H

#include <QDialog>

namespace Ui {
    class NewUserWidget;
}

class NewUserWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserWidget(QWidget *parent = 0);
    ~NewUserWidget();
    void adduser();
    void changeuser(const QString &UserId);
private:
    Ui::NewUserWidget *ui;
    QImage fingerPrintImage;
    QByteArray saveFingerData;
    void keyPressEvent(QKeyEvent *event);
    void exitWndSlot();
private slots:

    void on_pushButton_fingerPrint_clicked();
    void on_comboBox_currentIndexChanged(int);
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // NEWUSERWIDGET_H
