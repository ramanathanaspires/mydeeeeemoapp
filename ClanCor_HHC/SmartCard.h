#ifndef SMARTCARD_H
#define SMARTCARD_H
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QThread>

#include <winscard.h>
#include <QMutex>

namespace Ui {
    class SmartCard;
}
class SC_thread;

class SmartCard : public QDialog
{
    Q_OBJECT

public:
    explicit SmartCard(QWidget *parent = 0);
    ~SmartCard();

    bool isError;

private:
    Ui::SmartCard *ui;
    SC_thread *obj_thrd;
    int prevIndex;
    QMutex mutex;
    QString RxedData, strUserID_old, strUserName_old, strMobileNo_old, strCity_old, LastErr;

    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_btnSave_clicked();
    void on_btnClose_clicked();
    void txt_UserID_textChanged(QString );
    void txt_UserName_textChanged(QString );
    void txtCity_textChanged(QString );
    void txt_MobileNo_textChanged(QString );
    void on_cmb_ReaderName_currentIndexChanged(int index);
    void on_btn_Read_clicked();
    void slot_stateChanged(int index);
    void slotclose();

    bool Read_SmartCard(QString Reader);
    bool Write_SmartCard(QString Reader);
    bool PerformTransmitAPDU(SCARDHANDLE,LPCSCARD_IO_REQUEST , BYTE *, unsigned long);

//    void on_cmb_Module_select_currentIndexChanged(const QString &arg1);
//    void on_cmb_smartcard_slot_currentIndexChanged(const QString &arg1);
//    void on_pushButton_clicked();
    void on_pushButtonSam_clicked();
    void on_pushButtonSmartcard1_clicked();
    void on_pushButtonSmartcard2_clicked();
};

class SC_thread : public QThread
{
    Q_OBJECT
public:
    SC_thread();

    int NoofReaders;
    QStringList strlstReaders, strlstCardstat, strlstATR, strlstCardPresent;
    QString  LastError;
    bool connected, isError;

signals:
    void state_changed(int index);
    void error_close();
public slots:
    void thread_start();
    void thread_terminate();

private:
    void run();

    SCARDCONTEXT hCont;
    bool CardPresent;
    QMutex mutex;

private slots:
};

#endif // SMARTCARD_H
