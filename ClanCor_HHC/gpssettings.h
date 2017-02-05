#ifndef GPSSETTINGS_H
#define GPSSETTINGS_H

#include <QDialog>

namespace Ui {
    class GpsSettings;
}

class GpsSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GpsSettings(QWidget *parent = 0);
    ~GpsSettings();

private:
    Ui::GpsSettings *ui;
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // GPSSETTINGS_H
