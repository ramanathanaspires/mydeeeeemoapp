/********************************************************************************
** Form generated from reading UI file 'dialup_entry.ui'
**
** Created: Sat May 4 15:49:27 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALUP_ENTRY_H
#define UI_DIALUP_ENTRY_H

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
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_dialup_entry
{
public:
    QGroupBox *groupBox;
    QLabel *lblConnectionName;
    QLabel *lblNetwork;
    QGroupBox *groupBox_2;
    QRadioButton *rbtnAlways_On;
    QRadioButton *rbtnManual;
    QLineEdit *txtConnectionName;
    QComboBox *cmbNetwork;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *dialup_entry)
    {
        if (dialup_entry->objectName().isEmpty())
            dialup_entry->setObjectName(QString::fromUtf8("dialup_entry"));
        dialup_entry->resize(320, 220);
        dialup_entry->setStyleSheet(QString::fromUtf8("QDialog{background-color: rgb(135, 135, 104);}"));
        groupBox = new QGroupBox(dialup_entry);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 5, 310, 210));
        groupBox->setStyleSheet(QString::fromUtf8("QPushButton:pressed{background-color: rgb(255, 186, 181);border-width: 5px;border-color:Magenta;border-style: solid;}"));
        lblConnectionName = new QLabel(groupBox);
        lblConnectionName->setObjectName(QString::fromUtf8("lblConnectionName"));
        lblConnectionName->setGeometry(QRect(30, 30, 113, 22));
        lblNetwork = new QLabel(groupBox);
        lblNetwork->setObjectName(QString::fromUtf8("lblNetwork"));
        lblNetwork->setGeometry(QRect(30, 60, 113, 22));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 100, 231, 51));
        rbtnAlways_On = new QRadioButton(groupBox_2);
        rbtnAlways_On->setObjectName(QString::fromUtf8("rbtnAlways_On"));
        rbtnAlways_On->setGeometry(QRect(10, 20, 104, 19));
        rbtnManual = new QRadioButton(groupBox_2);
        rbtnManual->setObjectName(QString::fromUtf8("rbtnManual"));
        rbtnManual->setGeometry(QRect(140, 20, 104, 19));
        txtConnectionName = new QLineEdit(groupBox);
        txtConnectionName->setObjectName(QString::fromUtf8("txtConnectionName"));
        txtConnectionName->setGeometry(QRect(150, 30, 141, 22));
        cmbNetwork = new QComboBox(groupBox);
        cmbNetwork->setObjectName(QString::fromUtf8("cmbNetwork"));
        cmbNetwork->setGeometry(QRect(150, 60, 141, 24));
        btnOk = new QPushButton(groupBox);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(220, 170, 85, 30));
        btnCancel = new QPushButton(groupBox);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(130, 170, 85, 30));

        retranslateUi(dialup_entry);

        QMetaObject::connectSlotsByName(dialup_entry);
    } // setupUi

    void retranslateUi(QDialog *dialup_entry)
    {
        dialup_entry->setWindowTitle(QApplication::translate("dialup_entry", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("dialup_entry", "New Dial-up Connection", 0, QApplication::UnicodeUTF8));
        lblConnectionName->setText(QApplication::translate("dialup_entry", "Connection Name", 0, QApplication::UnicodeUTF8));
        lblNetwork->setText(QApplication::translate("dialup_entry", "Network", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("dialup_entry", "Connection Type", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        rbtnAlways_On->setAccessibleName(QApplication::translate("dialup_entry", "Always_On", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        rbtnAlways_On->setText(QApplication::translate("dialup_entry", "Always On", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        rbtnManual->setAccessibleName(QApplication::translate("dialup_entry", "Manual", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        rbtnManual->setText(QApplication::translate("dialup_entry", "Manual", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("dialup_entry", "Ok", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("dialup_entry", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dialup_entry: public Ui_dialup_entry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALUP_ENTRY_H
