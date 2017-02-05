#ifndef WIFI_CONF_H
#define WIFI_CONF_H

#include <QDialog>
//#include "GlobalClass.h"
//using namespace Globalclass;

namespace Ui {
    class WIFI_Conf;
}

class WIFI_Conf : public QDialog
{
    Q_OBJECT

public:
    explicit WIFI_Conf(QWidget *parent = 0);
//    E_GadgetMode Gadeget;
//    E_MassStorage MassStorage;
    ~WIFI_Conf();
    bool bWifiONOFFflag;

private:
    Ui::WIFI_Conf *ui;
    int Prev_enc;
    QString Prev_key;

private slots:
    void on_cmbEncryption_currentIndexChanged(int index);
    void on_BtnCancel_clicked();
    void on_BtnOk_clicked();
    void makeEnable();
    void on_BtnON_OFF_clicked();
};

#endif // WIFI_CONF_H
