/********************************************************************************
** Form generated from reading UI file 'SmartCard.ui'
**
** Created: Tue Feb 11 18:04:02 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMARTCARD_H
#define UI_SMARTCARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SmartCard
{
public:
    QGroupBox *groupBox;
    QLabel *name_lblReader;
    QComboBox *cmb_ReaderName;
    QGroupBox *grpBx_main;
    QLabel *lblCardstat;
    QLabel *lblATR;
    QPushButton *btn_Read;
    QLabel *name_lblCardstat;
    QLabel *name_lblATR;
    QLabel *name_lblReader_2;
    QPushButton *pushButtonSam;
    QPushButton *pushButtonSmartcard1;
    QPushButton *pushButtonSmartcard2;
    QLabel *labelCardMode;
    QGroupBox *grpBx_data;
    QPushButton *btnSave;
    QLabel *lbl_UserID;
    QLabel *lbl_UserName;
    QLabel *lbl_MobileNo;
    QLabel *lbl_City;
    QLineEdit *txt_UserID;
    QLineEdit *txt_UserName;
    QLineEdit *txt_MobileNo;
    QLineEdit *txtCity;
    QPushButton *btnClose;

    void setupUi(QDialog *SmartCard)
    {
        if (SmartCard->objectName().isEmpty())
            SmartCard->setObjectName(QString::fromUtf8("SmartCard"));
        SmartCard->resize(320, 480);
        SmartCard->setStyleSheet(QString::fromUtf8("color:rgb(0,0,0);background-color: rgb(220, 220, 220);"));
        groupBox = new QGroupBox(SmartCard);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(3, 3, 315, 460));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{color:rgb(231, 249, 255); border:1px solid gray;border-color:rgb(104, 0, 0); border-radius: 2px;}"));
        name_lblReader = new QLabel(groupBox);
        name_lblReader->setObjectName(QString::fromUtf8("name_lblReader"));
        name_lblReader->setGeometry(QRect(14, 14, 91, 20));
        cmb_ReaderName = new QComboBox(groupBox);
        cmb_ReaderName->setObjectName(QString::fromUtf8("cmb_ReaderName"));
        cmb_ReaderName->setGeometry(QRect(112, 12, 185, 24));
        grpBx_main = new QGroupBox(groupBox);
        grpBx_main->setObjectName(QString::fromUtf8("grpBx_main"));
        grpBx_main->setGeometry(QRect(1, 40, 313, 400));
        lblCardstat = new QLabel(grpBx_main);
        lblCardstat->setObjectName(QString::fromUtf8("lblCardstat"));
        lblCardstat->setGeometry(QRect(90, 224, 214, 25));
        lblCardstat->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(0, 81, 5);\n"
"border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        lblCardstat->setWordWrap(true);
        lblATR = new QLabel(grpBx_main);
        lblATR->setObjectName(QString::fromUtf8("lblATR"));
        lblATR->setGeometry(QRect(90, 177, 214, 41));
        lblATR->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(131, 0, 100);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        lblATR->setWordWrap(true);
        btn_Read = new QPushButton(grpBx_main);
        btn_Read->setObjectName(QString::fromUtf8("btn_Read"));
        btn_Read->setGeometry(QRect(242, 256, 90, 40));
        btn_Read->setAutoDefault(true);
        name_lblCardstat = new QLabel(grpBx_main);
        name_lblCardstat->setObjectName(QString::fromUtf8("name_lblCardstat"));
        name_lblCardstat->setGeometry(QRect(7, 230, 79, 14));
        name_lblATR = new QLabel(grpBx_main);
        name_lblATR->setObjectName(QString::fromUtf8("name_lblATR"));
        name_lblATR->setGeometry(QRect(30, 193, 40, 14));
        name_lblReader_2 = new QLabel(grpBx_main);
        name_lblReader_2->setObjectName(QString::fromUtf8("name_lblReader_2"));
        name_lblReader_2->setGeometry(QRect(12, 70, 91, 20));
        pushButtonSam = new QPushButton(grpBx_main);
        pushButtonSam->setObjectName(QString::fromUtf8("pushButtonSam"));
        pushButtonSam->setGeometry(QRect(10, 100, 81, 30));
        pushButtonSmartcard1 = new QPushButton(grpBx_main);
        pushButtonSmartcard1->setObjectName(QString::fromUtf8("pushButtonSmartcard1"));
        pushButtonSmartcard1->setGeometry(QRect(100, 100, 91, 29));
        pushButtonSmartcard2 = new QPushButton(grpBx_main);
        pushButtonSmartcard2->setObjectName(QString::fromUtf8("pushButtonSmartcard2"));
        pushButtonSmartcard2->setGeometry(QRect(210, 100, 93, 29));
        labelCardMode = new QLabel(grpBx_main);
        labelCardMode->setObjectName(QString::fromUtf8("labelCardMode"));
        labelCardMode->setGeometry(QRect(110, 70, 191, 20));
        grpBx_data = new QGroupBox(groupBox);
        grpBx_data->setObjectName(QString::fromUtf8("grpBx_data"));
        grpBx_data->setGeometry(QRect(312, 276, 290, 460));
        btnSave = new QPushButton(grpBx_data);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(42, 233, 90, 40));
        btnSave->setAutoDefault(true);
        lbl_UserID = new QLabel(grpBx_data);
        lbl_UserID->setObjectName(QString::fromUtf8("lbl_UserID"));
        lbl_UserID->setGeometry(QRect(12, 116, 91, 20));
        lbl_UserName = new QLabel(grpBx_data);
        lbl_UserName->setObjectName(QString::fromUtf8("lbl_UserName"));
        lbl_UserName->setGeometry(QRect(12, 146, 91, 20));
        lbl_MobileNo = new QLabel(grpBx_data);
        lbl_MobileNo->setObjectName(QString::fromUtf8("lbl_MobileNo"));
        lbl_MobileNo->setGeometry(QRect(12, 176, 91, 20));
        lbl_City = new QLabel(grpBx_data);
        lbl_City->setObjectName(QString::fromUtf8("lbl_City"));
        lbl_City->setGeometry(QRect(12, 206, 91, 20));
        txt_UserID = new QLineEdit(grpBx_data);
        txt_UserID->setObjectName(QString::fromUtf8("txt_UserID"));
        txt_UserID->setGeometry(QRect(92, 115, 151, 22));
        txt_UserName = new QLineEdit(grpBx_data);
        txt_UserName->setObjectName(QString::fromUtf8("txt_UserName"));
        txt_UserName->setGeometry(QRect(92, 143, 151, 22));
        txt_MobileNo = new QLineEdit(grpBx_data);
        txt_MobileNo->setObjectName(QString::fromUtf8("txt_MobileNo"));
        txt_MobileNo->setGeometry(QRect(92, 172, 151, 22));
        txtCity = new QLineEdit(grpBx_data);
        txtCity->setObjectName(QString::fromUtf8("txtCity"));
        txtCity->setGeometry(QRect(92, 202, 151, 22));
        btnClose = new QPushButton(grpBx_data);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(162, 233, 90, 40));
        btnClose->setAutoDefault(true);
        grpBx_main->raise();
        grpBx_data->raise();
        name_lblReader->raise();
        cmb_ReaderName->raise();
        QWidget::setTabOrder(cmb_ReaderName, btn_Read);
        QWidget::setTabOrder(btn_Read, txt_UserID);
        QWidget::setTabOrder(txt_UserID, txt_UserName);
        QWidget::setTabOrder(txt_UserName, txt_MobileNo);
        QWidget::setTabOrder(txt_MobileNo, txtCity);
        QWidget::setTabOrder(txtCity, btnSave);
        QWidget::setTabOrder(btnSave, btnClose);

        retranslateUi(SmartCard);

        QMetaObject::connectSlotsByName(SmartCard);
    } // setupUi

    void retranslateUi(QDialog *SmartCard)
    {
        SmartCard->setWindowTitle(QApplication::translate("SmartCard", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        name_lblReader->setText(QApplication::translate("SmartCard", "Reader Name:", 0, QApplication::UnicodeUTF8));
        grpBx_main->setTitle(QString());
        lblCardstat->setText(QString());
        lblATR->setText(QString());
        btn_Read->setText(QApplication::translate("SmartCard", "Read / Write", 0, QApplication::UnicodeUTF8));
        name_lblCardstat->setText(QApplication::translate("SmartCard", "Card Status:", 0, QApplication::UnicodeUTF8));
        name_lblATR->setText(QApplication::translate("SmartCard", "ATR:", 0, QApplication::UnicodeUTF8));
        name_lblReader_2->setText(QApplication::translate("SmartCard", "Card Mode:", 0, QApplication::UnicodeUTF8));
        pushButtonSam->setText(QApplication::translate("SmartCard", "SAM", 0, QApplication::UnicodeUTF8));
        pushButtonSmartcard1->setText(QApplication::translate("SmartCard", "SMARTCARD1", 0, QApplication::UnicodeUTF8));
        pushButtonSmartcard2->setText(QApplication::translate("SmartCard", "SMARTCARD2", 0, QApplication::UnicodeUTF8));
        labelCardMode->setText(QString());
        grpBx_data->setTitle(QString());
        btnSave->setText(QApplication::translate("SmartCard", "Save", 0, QApplication::UnicodeUTF8));
        lbl_UserID->setText(QApplication::translate("SmartCard", "User ID:", 0, QApplication::UnicodeUTF8));
        lbl_UserName->setText(QApplication::translate("SmartCard", "User Name:", 0, QApplication::UnicodeUTF8));
        lbl_MobileNo->setText(QApplication::translate("SmartCard", "Mobile No:", 0, QApplication::UnicodeUTF8));
        lbl_City->setText(QApplication::translate("SmartCard", "City:", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("SmartCard", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SmartCard: public Ui_SmartCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTCARD_H
