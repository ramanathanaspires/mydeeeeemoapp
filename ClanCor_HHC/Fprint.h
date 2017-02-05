#ifndef Fprint_H
#define Fprint_H

#include <QtGui>
#include <QDialog>
#include <sqlite3.h>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriver>
#include <cFP_Morpho.h>
using namespace ClanCor;

class Fprint : public QDialog
{
    Q_OBJECT
private:
    QSqlDatabase cn;
    QLabel *imageLabel;
    QLineEdit *txtUser;
    QComboBox *cmbUsers, *cmbTemplateType;
    QPushButton *btnGetimage;
    QPushButton *btnEnroll;
    QPushButton *btnVerify;
    QPushButton *btnIdentify;    
    QByteArray sample;
    int size;
    int m_nTemplateTypeIndex;
    CFP_Morpho::E_FPTemplateType m_eFPTemplate;

    bool OpenDatabase(QString);
    bool ExecuteQuery(QString);
    bool ExecuteQuery(QString ,QSqlQuery *);
public:
    Fprint(QWidget *parent = 0);
    ~Fprint();
private slots:
    void Getimage_Click();
    void EnrollFinger_Click();
    void VerifyFinger_Click();
    void VerifyFinger_match();
    void IdentifyFinger_Click();
    void IdentifyFinger_match();
    void slot_setTemplateType(int);
};

#endif // Fprint_H
