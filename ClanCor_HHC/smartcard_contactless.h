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
    void slot_stateChanged();
    void slotclose();

};

class SC_CLthread : public QThread
{
    Q_OBJECT
public:
    SC_CLthread();

    QString  ATR, Target, Reader, UID, LastError;
    bool connected, isError;
signals:
    void state_changed();
    void error_close();
public slots:
    void thread_terminate();

private:
    void run();

private slots:
};

#endif // SMARTCARD_CONTACTLESS_H
