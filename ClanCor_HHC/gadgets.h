#ifndef GADGETS_H
#define GADGETS_H

#include <QWidget>
#include<CHHC80xx>
#include<CHHC80xxServer>
#include <QDialog>
using namespace ClanCor;
namespace Ui {
class GADGETS;
}

class GADGETS : public QDialog
{
    Q_OBJECT
    
public:
    explicit GADGETS(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyevent);
    QString usbip,hostip;
//    CHHC80xx *Cobj;
    E_GadgetMode Gadeget;
    E_MassStorage MassStorage;
    bool busbFlag;

    ~GADGETS();
    
private slots:


    void on_pushButtonOk_clicked();

    void on_pushButtonUsbIp_clicked();

    void on_pushButton_clicked();

    void on_pushButtonusbExit_clicked();

    void on_lineEditUsb_returnPressed();

    void on_lineEditHost_returnPressed();

    void on_pushButtonUSBONOFF_clicked();

private:
    Ui::GADGETS *ui;
};

#endif // GADGETS_H
