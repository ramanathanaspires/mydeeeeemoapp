#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QKeyEvent>
namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyevent);
    ~Dialog();

private:
    Ui::Dialog *ui;

private slots:
//    void on_pushButton_3_clicked();
//    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // DIALOG_H
