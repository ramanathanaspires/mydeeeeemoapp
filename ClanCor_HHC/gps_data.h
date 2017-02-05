#ifndef GPS_DATA_H
#define GPS_DATA_H

#include <QDialog>
#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QDateTime>
#include <QByteArray>
#include <QTextStream>
#include <QFtp>
#include <QFile>
#include <QProgressDialog>

namespace Ui {
class GPS_data;
}


class GPS_data : public QDialog
{
    Q_OBJECT

public:
    explicit GPS_data(QWidget *parent = 0);
    ~GPS_data();
    float flatitude,flongtitude;
    QString strLongitude, strAltitude,strLatitude,strNo_of_sat,strSpeed,strtime;
private:
    Ui::GPS_data *ui;

    QLabel *lbl_Grndspeed;
    QTimer *t;
    int ErrorCount;
    void GPSDatafun();
    void delay(int nMSec);
    QProgressDialog *progressDialog;

    void keyPressEvent(QKeyEvent *e);

    bool GPSfix;
    bool Automatic;
    QString FtpPath;
    QString FtpUser;
    QString FtpPassword;
    bool escapepressed;
    bool Agps_configure;
    QFtp *ftp;
    QFile *file;
    void DownloadFile();
signals:
    void showgpsicon(bool flag);
private slots:
    void close_dia();
    void Receive_File();
    void on_btnRefresh_clicked();
    void on_pushButton_Download_clicked();
    void viewProgress(qint64 done ,qint64 total);
    void reply(int code);
    void listInfo2(QUrlInfo info);
    void commandFinished(int id,bool error);
    void commandstarted(int id);
};

#endif // GPS_DATA_H
