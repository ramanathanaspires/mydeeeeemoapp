#ifndef PATCHUPDATES_H
#define PATCHUPDATES_H

#include <QDialog>
#include <QFtp>
#include "QFile"
#include "QKeyEvent"
#include <QProgressDialog>


namespace Ui {
class Patchupdates;
}

class Patchupdates : public QDialog
{
    Q_OBJECT
    
public:
    explicit Patchupdates(QWidget *parent = 0);
    QFtp *ftp;
    int count,updatecount;
    QProgressDialog *progressDialog;
    QStringList downloaddata;
    QString strDownloadfile,Pic32Version,Pic32DT,BUILDVERSION,BUILDDATE;
    void enablePushbutton();
    void checkfile();
    virtual void keyPressEvent(QKeyEvent * e);
    bool ConnectFTP(QString DownloadFile);
    bool bcheckupdates;
    ~Patchupdates();
    
private slots:
    void cancelDownload();
    void on_pushButton_Checkupdates_clicked();

    void on_pushButton_updates_clicked();

    void on_pushButton_Cancel_clicked();

    void viewProgress(qint64 done ,qint64 total);

    void listInfo2(QUrlInfo info);

    void commandFinished(int id,bool error);

    void commandstarted(int id);


    void on_checkBox_Clancor_HHC_clicked();

    void on_checkBox_HHC_SDK_clicked();

    void on_checkBox_CoProcessor_clicked();

private:
    Ui::Patchupdates *ui;
};

#endif // PATCHUPDATES_H
