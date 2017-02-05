#ifndef CENREG_H
#define CENREG_H
#include <QMdiSubWindow>
#include "GlobalClass.h"
#include "WebCamera.h"
#include "FingerPrint.h"

/*************************class census mainmenu******************************/

class censusMenu : public QMdiSubWindow
{
    Q_OBJECT
    public:
        censusMenu(QWidget *parent=0);
    private:
        QVBoxLayout *layout;
        QPushButton *regBtn, *uploadBtn, *exitBtn;

        void keyPressEvent(QKeyEvent *);
    private slots:
        void regTrans();
        void uploadTrans();
        void exitTrans();
};


/*************************Cenreg class******************************/

class cenReg : public QMdiSubWindow
{
    Q_OBJECT

public:
    cenReg(QWidget *parent = 0);
    ~cenReg();
private:
    QScrollArea *scrollArea;
    QGroupBox *g;
    QGridLayout *layout;
    QLabel *lbl,*lblId,*lblPhoto,*lblFinger, *lblSign;
    QLineEdit *txtName,*txtDno,*txtAge;
    QComboBox *txtGen,*txtAdd1,*txtAdd2,*txtCity,*txtTk,*txtDt,*txtOcc;
    QPushButton *btnPhoto,*btnFinger, *btnSign,*btnSave,*btnCancel;
    WebCamera *Preview;
    FingerPrint *fpt;
    QByteArray fingerData,fingerImage,imgData, signData;
    bool imgFlag,fingFlag, signFlag;
    int ID;
    QImage tmp;

    void keyPressEvent(QKeyEvent *);
private slots:
    void saveTrans();
    void cancelTrans();
    void printTrans();
    void imgTrans();
    void fingerTrans();
    void signTrans();
};

#endif // CENREG_H
