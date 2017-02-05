/********************************************************************************
** Form generated from reading UI file 'gadgets.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GADGETS_H
#define UI_GADGETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GADGETS
{
public:
    QGroupBox *groupBoxUsb_2;
    QPushButton *pushButtonUsbIp;
    QPushButton *pushButtonOk;
    QRadioButton *radioButtonnormal;
    QRadioButton *radioButtonUSB;
    QRadioButton *radioButtonSerial;
    QRadioButton *radioButtonSDCard;
    QGroupBox *groupBoxUsbOnoff;
    QLabel *label;
    QPushButton *pushButtonUSBONOFF;
    QGroupBox *groupBoxUsb;
    QLabel *labelText;
    QLabel *labelHostIpaddress;
    QLineEdit *lineEditUsb;
    QLineEdit *lineEditHost;
    QPushButton *pushButton;
    QPushButton *pushButtonusbExit;
    QLabel *labelUsbIpaddress_2;

    void setupUi(QWidget *GADGETS)
    {
        if (GADGETS->objectName().isEmpty())
            GADGETS->setObjectName(QString::fromUtf8("GADGETS"));
        GADGETS->resize(320, 1000);
        groupBoxUsb_2 = new QGroupBox(GADGETS);
        groupBoxUsb_2->setObjectName(QString::fromUtf8("groupBoxUsb_2"));
        groupBoxUsb_2->setGeometry(QRect(0, 40, 320, 420));
        groupBoxUsb_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButtonUsbIp = new QPushButton(groupBoxUsb_2);
        pushButtonUsbIp->setObjectName(QString::fromUtf8("pushButtonUsbIp"));
        pushButtonUsbIp->setGeometry(QRect(170, 140, 141, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        pushButtonUsbIp->setFont(font);
        pushButtonOk = new QPushButton(groupBoxUsb_2);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setGeometry(QRect(110, 274, 70, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonOk->setFont(font1);
        radioButtonnormal = new QRadioButton(groupBoxUsb_2);
        radioButtonnormal->setObjectName(QString::fromUtf8("radioButtonnormal"));
        radioButtonnormal->setGeometry(QRect(45, 224, 151, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        radioButtonnormal->setFont(font2);
        radioButtonUSB = new QRadioButton(groupBoxUsb_2);
        radioButtonUSB->setObjectName(QString::fromUtf8("radioButtonUSB"));
        radioButtonUSB->setGeometry(QRect(45, 134, 171, 30));
        radioButtonUSB->setFont(font2);
        radioButtonSerial = new QRadioButton(groupBoxUsb_2);
        radioButtonSerial->setObjectName(QString::fromUtf8("radioButtonSerial"));
        radioButtonSerial->setGeometry(QRect(45, 94, 191, 22));
        radioButtonSerial->setFont(font2);
        radioButtonSDCard = new QRadioButton(groupBoxUsb_2);
        radioButtonSDCard->setObjectName(QString::fromUtf8("radioButtonSDCard"));
        radioButtonSDCard->setGeometry(QRect(45, 184, 109, 21));
        radioButtonSDCard->setFont(font2);
        groupBoxUsbOnoff = new QGroupBox(GADGETS);
        groupBoxUsbOnoff->setObjectName(QString::fromUtf8("groupBoxUsbOnoff"));
        groupBoxUsbOnoff->setGeometry(QRect(0, 0, 320, 40));
        groupBoxUsbOnoff->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label = new QLabel(groupBoxUsbOnoff);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(74, 14, 51, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        label->setFont(font3);
        pushButtonUSBONOFF = new QPushButton(groupBoxUsbOnoff);
        pushButtonUSBONOFF->setObjectName(QString::fromUtf8("pushButtonUSBONOFF"));
        pushButtonUSBONOFF->setGeometry(QRect(150, 9, 92, 27));
        pushButtonUSBONOFF->setFont(font);
        groupBoxUsb = new QGroupBox(GADGETS);
        groupBoxUsb->setObjectName(QString::fromUtf8("groupBoxUsb"));
        groupBoxUsb->setGeometry(QRect(10, 400, 320, 420));
        groupBoxUsb->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        labelText = new QLabel(groupBoxUsb);
        labelText->setObjectName(QString::fromUtf8("labelText"));
        labelText->setGeometry(QRect(-10, 40, 330, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DejaVu Sans"));
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setWeight(75);
        labelText->setFont(font4);
        labelHostIpaddress = new QLabel(groupBoxUsb);
        labelHostIpaddress->setObjectName(QString::fromUtf8("labelHostIpaddress"));
        labelHostIpaddress->setGeometry(QRect(0, 170, 131, 17));
        QFont font5;
        font5.setPointSize(12);
        labelHostIpaddress->setFont(font5);
        lineEditUsb = new QLineEdit(groupBoxUsb);
        lineEditUsb->setObjectName(QString::fromUtf8("lineEditUsb"));
        lineEditUsb->setGeometry(QRect(160, 100, 151, 27));
        lineEditHost = new QLineEdit(groupBoxUsb);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));
        lineEditHost->setGeometry(QRect(160, 160, 151, 27));
        pushButton = new QPushButton(groupBoxUsb);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 230, 71, 31));
        QFont font6;
        font6.setPointSize(10);
        pushButton->setFont(font6);
        pushButtonusbExit = new QPushButton(groupBoxUsb);
        pushButtonusbExit->setObjectName(QString::fromUtf8("pushButtonusbExit"));
        pushButtonusbExit->setGeometry(QRect(190, 230, 71, 31));
        labelUsbIpaddress_2 = new QLabel(groupBoxUsb);
        labelUsbIpaddress_2->setObjectName(QString::fromUtf8("labelUsbIpaddress_2"));
        labelUsbIpaddress_2->setGeometry(QRect(10, 110, 131, 17));
        labelUsbIpaddress_2->setFont(font5);

        retranslateUi(GADGETS);

        QMetaObject::connectSlotsByName(GADGETS);
    } // setupUi

    void retranslateUi(QWidget *GADGETS)
    {
        GADGETS->setWindowTitle(QApplication::translate("GADGETS", "GADGETS", 0, QApplication::UnicodeUTF8));
        groupBoxUsb_2->setTitle(QString());
        pushButtonUsbIp->setText(QApplication::translate("GADGETS", "NetworkConfiguration", 0, QApplication::UnicodeUTF8));
        pushButtonOk->setText(QApplication::translate("GADGETS", "OK", 0, QApplication::UnicodeUTF8));
        radioButtonnormal->setText(QApplication::translate("GADGETS", "Normal Mode", 0, QApplication::UnicodeUTF8));
        radioButtonUSB->setText(QApplication::translate("GADGETS", "Network Mode", 0, QApplication::UnicodeUTF8));
        radioButtonSerial->setText(QApplication::translate("GADGETS", "Serial Mode", 0, QApplication::UnicodeUTF8));
        radioButtonSDCard->setText(QApplication::translate("GADGETS", "SD Card", 0, QApplication::UnicodeUTF8));
        groupBoxUsbOnoff->setTitle(QString());
        label->setText(QApplication::translate("GADGETS", "USB ", 0, QApplication::UnicodeUTF8));
        pushButtonUSBONOFF->setText(QString());
        groupBoxUsb->setTitle(QString());
        labelText->setText(QApplication::translate("GADGETS", "DEVICE NETWORK GADGET", 0, QApplication::UnicodeUTF8));
        labelHostIpaddress->setText(QApplication::translate("GADGETS", "Host IPAddress", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GADGETS", "[F2] Ok", 0, QApplication::UnicodeUTF8));
        pushButtonusbExit->setText(QApplication::translate("GADGETS", "[F4] Exit", 0, QApplication::UnicodeUTF8));
        labelUsbIpaddress_2->setText(QApplication::translate("GADGETS", "USB IPAddress", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GADGETS: public Ui_GADGETS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GADGETS_H
