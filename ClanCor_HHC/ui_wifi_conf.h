/********************************************************************************
** Form generated from reading UI file 'wifi_conf.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIFI_CONF_H
#define UI_WIFI_CONF_H

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

class Ui_WIFI_Conf
{
public:
    QGroupBox *groupBox_Main;
    QGroupBox *groupBox_Settings;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txtIPaddress;
    QLineEdit *txtSubnet;
    QLineEdit *txtGateway;
    QLabel *label_4;
    QLabel *label_7;
    QGroupBox *grpbxSecurity;
    QLabel *label_8;
    QComboBox *cmbEncryption;
    QLineEdit *txtKey;
    QLabel *label_9;
    QLineEdit *txtSSID;
    QComboBox *cmbAdhoc;
    QPushButton *BtnOk;
    QPushButton *BtnCancel;
    QGroupBox *groupBox_ON_OFF;
    QLabel *label_WIFI;
    QPushButton *BtnON_OFF;

    void setupUi(QDialog *WIFI_Conf)
    {
        if (WIFI_Conf->objectName().isEmpty())
            WIFI_Conf->setObjectName(QString::fromUtf8("WIFI_Conf"));
        WIFI_Conf->resize(320, 460);
        WIFI_Conf->setStyleSheet(QString::fromUtf8("QDialog{Background-color:rgb(238, 238, 238)};"));
        groupBox_Main = new QGroupBox(WIFI_Conf);
        groupBox_Main->setObjectName(QString::fromUtf8("groupBox_Main"));
        groupBox_Main->setGeometry(QRect(0, 0, 310, 460));
        groupBox_Settings = new QGroupBox(groupBox_Main);
        groupBox_Settings->setObjectName(QString::fromUtf8("groupBox_Settings"));
        groupBox_Settings->setGeometry(QRect(0, 44, 310, 420));
        label = new QLabel(groupBox_Settings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 34, 81, 16));
        label->setWordWrap(true);
        label_2 = new QLabel(groupBox_Settings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(6, 75, 90, 16));
        label_2->setWordWrap(true);
        label_3 = new QLabel(groupBox_Settings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(6, 113, 114, 20));
        label_3->setWordWrap(true);
        txtIPaddress = new QLineEdit(groupBox_Settings);
        txtIPaddress->setObjectName(QString::fromUtf8("txtIPaddress"));
        txtIPaddress->setGeometry(QRect(126, 29, 160, 22));
        txtSubnet = new QLineEdit(groupBox_Settings);
        txtSubnet->setObjectName(QString::fromUtf8("txtSubnet"));
        txtSubnet->setGeometry(QRect(126, 70, 160, 22));
        txtGateway = new QLineEdit(groupBox_Settings);
        txtGateway->setObjectName(QString::fromUtf8("txtGateway"));
        txtGateway->setGeometry(QRect(126, 111, 160, 22));
        label_4 = new QLabel(groupBox_Settings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(6, 208, 110, 14));
        label_7 = new QLabel(groupBox_Settings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(6, 165, 110, 10));
        grpbxSecurity = new QGroupBox(groupBox_Settings);
        grpbxSecurity->setObjectName(QString::fromUtf8("grpbxSecurity"));
        grpbxSecurity->setGeometry(QRect(5, 244, 300, 110));
        grpbxSecurity->setCheckable(false);
        grpbxSecurity->setChecked(false);
        label_8 = new QLabel(grpbxSecurity);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 39, 101, 16));
        cmbEncryption = new QComboBox(grpbxSecurity);
        cmbEncryption->setObjectName(QString::fromUtf8("cmbEncryption"));
        cmbEncryption->setGeometry(QRect(120, 31, 160, 24));
        txtKey = new QLineEdit(grpbxSecurity);
        txtKey->setObjectName(QString::fromUtf8("txtKey"));
        txtKey->setGeometry(QRect(120, 80, 160, 22));
        label_9 = new QLabel(grpbxSecurity);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 90, 101, 16));
        txtSSID = new QLineEdit(groupBox_Settings);
        txtSSID->setObjectName(QString::fromUtf8("txtSSID"));
        txtSSID->setGeometry(QRect(126, 157, 160, 22));
        cmbAdhoc = new QComboBox(groupBox_Settings);
        cmbAdhoc->setObjectName(QString::fromUtf8("cmbAdhoc"));
        cmbAdhoc->setGeometry(QRect(126, 201, 160, 24));
        BtnOk = new QPushButton(groupBox_Settings);
        BtnOk->setObjectName(QString::fromUtf8("BtnOk"));
        BtnOk->setGeometry(QRect(30, 369, 89, 27));
        BtnCancel = new QPushButton(groupBox_Settings);
        BtnCancel->setObjectName(QString::fromUtf8("BtnCancel"));
        BtnCancel->setGeometry(QRect(170, 369, 89, 27));
        groupBox_ON_OFF = new QGroupBox(groupBox_Main);
        groupBox_ON_OFF->setObjectName(QString::fromUtf8("groupBox_ON_OFF"));
        groupBox_ON_OFF->setGeometry(QRect(0, 0, 310, 40));
        groupBox_ON_OFF->setAlignment(Qt::AlignCenter);
        label_WIFI = new QLabel(groupBox_ON_OFF);
        label_WIFI->setObjectName(QString::fromUtf8("label_WIFI"));
        label_WIFI->setGeometry(QRect(90, 15, 46, 17));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_WIFI->setFont(font);
        label_WIFI->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        BtnON_OFF = new QPushButton(groupBox_ON_OFF);
        BtnON_OFF->setObjectName(QString::fromUtf8("BtnON_OFF"));
        BtnON_OFF->setGeometry(QRect(140, 8, 93, 27));
        QWidget::setTabOrder(BtnON_OFF, txtIPaddress);
        QWidget::setTabOrder(txtIPaddress, txtSubnet);
        QWidget::setTabOrder(txtSubnet, txtGateway);
        QWidget::setTabOrder(txtGateway, txtSSID);
        QWidget::setTabOrder(txtSSID, cmbAdhoc);
        QWidget::setTabOrder(cmbAdhoc, cmbEncryption);
        QWidget::setTabOrder(cmbEncryption, txtKey);
        QWidget::setTabOrder(txtKey, BtnOk);
        QWidget::setTabOrder(BtnOk, BtnCancel);

        retranslateUi(WIFI_Conf);

        QMetaObject::connectSlotsByName(WIFI_Conf);
    } // setupUi

    void retranslateUi(QDialog *WIFI_Conf)
    {
        WIFI_Conf->setWindowTitle(QApplication::translate("WIFI_Conf", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox_Main->setTitle(QString());
        groupBox_Settings->setTitle(QApplication::translate("WIFI_Conf", "Wifi Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WIFI_Conf", "IP Address:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WIFI_Conf", "Subnet mask:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WIFI_Conf", "Gateway Address:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WIFI_Conf", "Wireless - Ad-hoc", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WIFI_Conf", "Wireless - (SSID)", 0, QApplication::UnicodeUTF8));
        grpbxSecurity->setTitle(QApplication::translate("WIFI_Conf", "Security", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WIFI_Conf", "Mode", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("WIFI_Conf", "Wireless - Key", 0, QApplication::UnicodeUTF8));
        BtnOk->setText(QApplication::translate("WIFI_Conf", " Ok", 0, QApplication::UnicodeUTF8));
        BtnOk->setShortcut(QApplication::translate("WIFI_Conf", "F2", 0, QApplication::UnicodeUTF8));
        BtnCancel->setText(QApplication::translate("WIFI_Conf", " Cancel", 0, QApplication::UnicodeUTF8));
        BtnCancel->setShortcut(QApplication::translate("WIFI_Conf", "F4", 0, QApplication::UnicodeUTF8));
        groupBox_ON_OFF->setTitle(QString());
        label_WIFI->setText(QApplication::translate("WIFI_Conf", "WIFI ", 0, QApplication::UnicodeUTF8));
        BtnON_OFF->setText(QApplication::translate("WIFI_Conf", "ON", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WIFI_Conf: public Ui_WIFI_Conf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIFI_CONF_H
