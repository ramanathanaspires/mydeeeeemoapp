/********************************************************************************
** Form generated from reading UI file 'smartcard_contactless.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMARTCARD_CONTACTLESS_H
#define UI_SMARTCARD_CONTACTLESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_smartcard_contactless
{
public:
    QLabel *name_lblReader;
    QLabel *lblReader;
    QLabel *lblATR;
    QLabel *name_lblUID;
    QLabel *lblUID;
    QLabel *name_lblTarget;
    QLabel *name_lblATR;
    QLabel *lblTarget;
    QGroupBox *groupBox;

    void setupUi(QDialog *smartcard_contactless)
    {
        if (smartcard_contactless->objectName().isEmpty())
            smartcard_contactless->setObjectName(QString::fromUtf8("smartcard_contactless"));
        smartcard_contactless->resize(320, 480);
        smartcard_contactless->setStyleSheet(QString::fromUtf8("color:rgb(0,0,0);background-color: rgb(220, 220, 220);"));
        name_lblReader = new QLabel(smartcard_contactless);
        name_lblReader->setObjectName(QString::fromUtf8("name_lblReader"));
        name_lblReader->setGeometry(QRect(20, 84, 91, 20));
        lblReader = new QLabel(smartcard_contactless);
        lblReader->setObjectName(QString::fromUtf8("lblReader"));
        lblReader->setGeometry(QRect(40, 109, 260, 26));
        lblReader->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(71, 109, 170);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        lblATR = new QLabel(smartcard_contactless);
        lblATR->setObjectName(QString::fromUtf8("lblATR"));
        lblATR->setGeometry(QRect(40, 179, 260, 26));
        lblATR->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(131, 0, 100);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        name_lblUID = new QLabel(smartcard_contactless);
        name_lblUID->setObjectName(QString::fromUtf8("name_lblUID"));
        name_lblUID->setGeometry(QRect(20, 289, 57, 14));
        lblUID = new QLabel(smartcard_contactless);
        lblUID->setObjectName(QString::fromUtf8("lblUID"));
        lblUID->setGeometry(QRect(40, 315, 260, 26));
        lblUID->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(85, 85, 127);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        name_lblTarget = new QLabel(smartcard_contactless);
        name_lblTarget->setObjectName(QString::fromUtf8("name_lblTarget"));
        name_lblTarget->setGeometry(QRect(20, 220, 80, 14));
        name_lblATR = new QLabel(smartcard_contactless);
        name_lblATR->setObjectName(QString::fromUtf8("name_lblATR"));
        name_lblATR->setGeometry(QRect(20, 156, 60, 14));
        lblTarget = new QLabel(smartcard_contactless);
        lblTarget->setObjectName(QString::fromUtf8("lblTarget"));
        lblTarget->setGeometry(QRect(40, 245, 260, 26));
        lblTarget->setStyleSheet(QString::fromUtf8("Background-color:rgb(255, 255, 244); color:rgb(0, 81, 5);\n"
"border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;"));
        groupBox = new QGroupBox(smartcard_contactless);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 8, 301, 460));
        groupBox->setStyleSheet(QString::fromUtf8("color:rgb(231, 249, 255); border:1px solid gray;border-color:rgb(104, 0, 0); border-radius: 2px;"));
        groupBox->raise();
        name_lblReader->raise();
        lblReader->raise();
        lblATR->raise();
        name_lblUID->raise();
        lblUID->raise();
        name_lblTarget->raise();
        name_lblATR->raise();
        lblTarget->raise();

        retranslateUi(smartcard_contactless);

        QMetaObject::connectSlotsByName(smartcard_contactless);
    } // setupUi

    void retranslateUi(QDialog *smartcard_contactless)
    {
        smartcard_contactless->setWindowTitle(QApplication::translate("smartcard_contactless", "Dialog", 0, QApplication::UnicodeUTF8));
        name_lblReader->setText(QApplication::translate("smartcard_contactless", "Reader Name", 0, QApplication::UnicodeUTF8));
        lblReader->setText(QString());
        lblATR->setText(QString());
        name_lblUID->setText(QApplication::translate("smartcard_contactless", "UID", 0, QApplication::UnicodeUTF8));
        lblUID->setText(QString());
        name_lblTarget->setText(QApplication::translate("smartcard_contactless", "Target", 0, QApplication::UnicodeUTF8));
        name_lblATR->setText(QApplication::translate("smartcard_contactless", "ATR", 0, QApplication::UnicodeUTF8));
        lblTarget->setText(QString());
        groupBox->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class smartcard_contactless: public Ui_smartcard_contactless {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMARTCARD_CONTACTLESS_H
