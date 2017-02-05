#ifndef PIC32WIDGET_H
#define PIC32WIDGET_H

#include <QDialog>

namespace Ui {
    class Pic32Widget;
}

class Pic32Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Pic32Widget(QWidget *parent = 0);
    ~Pic32Widget();

private:
    Ui::Pic32Widget *ui;
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pushButton_setBacklight_clicked();
    void on_pushButton_setKeypadMode_clicked();
    void on_pushButton_setBeep_clicked();
    void on_pushButton_setkeypadBeep_clicked();
    void on_pushButton_getMachineId_clicked();
    void on_pushButton_testRTC_clicked();
    void on_pushButton_testPrinter_clicked();

};

#endif // PIC32WIDGET_H
