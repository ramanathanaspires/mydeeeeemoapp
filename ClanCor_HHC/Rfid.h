#ifndef RFID_H
#define RFID_H

#include <QtGui>
#include <QDialog>
#include <WebCamera.h>
#include <ccmain.h>
#include <printer.h>
class Rfid : public QDialog
{
    Q_OBJECT
private:
    QPushButton *btnReadUid;
    QPushButton *btnRead;
    QPushButton *btnWrite;
    QSpinBox *txt_Sector;
    QSpinBox *txt_block;
    QLineEdit *txt_Data;
public:
    Rfid(QWidget *parent = 0);
    ~Rfid(){};
private slots:
    void ReadUid_Click();
    void ReadData_Click();
    void WriteData_Click();
};


#endif // RFID_H
