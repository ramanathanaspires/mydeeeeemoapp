#ifndef SMARTCARD_CONTACTLESS_H
#define SMARTCARD_CONTACTLESS_H
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QThread>
#include <winscard.h>

namespace Ui {
    class smartcard_contactless;
}
class SC_CLthread;

class smartcard_contactless : public QDialog
{
    Q_OBJECT

public:
    explicit smartcard_contactless(QWidget *parent = 0);
    ~smartcard_contactless();

    bool isError;

private:
    Ui::smartcard_contactless *ui;
    SC_CLthread *obj_thrd;

    void keyPressEvent(QKeyEvent *e);

private slots:
    void slot_stateChanged(bool readerState);
    void slotclose();

};

class SC_CLthread : public QThread
{
    Q_OBJECT
public:
    SC_CLthread();

    QString  ATR, Cardstat, Reader, UID, LastError;
    bool connected, isError;
signals:
    void state_changed(bool);
    void error_close();
public slots:
    void thread_terminate();

private:
    void run();
    bool PerformTransmitAPDU(BYTE *, unsigned long);

    char *ptr, **readers;
    LONG rv;
    SCARDCONTEXT hContext;
    SCARDHANDLE hCard;
    SCARD_IO_REQUEST pioSendPci;
    BYTE pbRecvBuffer[256];
    LPTSTR mszReaders;
    DWORD dwReaders, dwReadersOld;
    SCARD_READERSTATE *rgReaderStates_t;
    QString RxedData, prev_atr;
    QStringList strlstReaders;
    int NoofReaders;
    bool loopflag;
private slots:
};

#endif // SMARTCARD_CONTACTLESS_H
