/********************************************************************************
** Form generated from reading UI file 'dialup_conf.ui'
**
** Created: Sat May 4 15:49:27 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALUP_CONF_H
#define UI_DIALUP_CONF_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dialup_conf
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *btnAdd_new;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QListView *listView;

    void setupUi(QDialog *dialup_conf)
    {
        if (dialup_conf->objectName().isEmpty())
            dialup_conf->setObjectName(QString::fromUtf8("dialup_conf"));
        dialup_conf->resize(320, 220);
        dialup_conf->setStyleSheet(QString::fromUtf8("QDialog{background-color: rgb(135, 135, 104);}"));
        buttonBox = new QDialogButtonBox(dialup_conf);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-30, 182, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(dialup_conf);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(5, 4, 310, 210));
        groupBox->setStyleSheet(QString::fromUtf8("QPushButton:pressed{background-color: rgb(255, 186, 181);border-width: 5px;border-color:Magenta;border-style: solid;}"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(205, 18, 100, 155));
        btnAdd_new = new QPushButton(groupBox_2);
        btnAdd_new->setObjectName(QString::fromUtf8("btnAdd_new"));
        btnAdd_new->setGeometry(QRect(10, 10, 80, 35));
        btnEdit = new QPushButton(groupBox_2);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setGeometry(QRect(10, 60, 80, 35));
        btnDelete = new QPushButton(groupBox_2);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setGeometry(QRect(10, 110, 80, 35));
        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 18, 191, 155));
        groupBox->raise();
        buttonBox->raise();
        QWidget::setTabOrder(btnAdd_new, btnEdit);
        QWidget::setTabOrder(btnEdit, btnDelete);
        QWidget::setTabOrder(btnDelete, buttonBox);

        retranslateUi(dialup_conf);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialup_conf, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialup_conf, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialup_conf);
    } // setupUi

    void retranslateUi(QDialog *dialup_conf)
    {
        dialup_conf->setWindowTitle(QApplication::translate("dialup_conf", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("dialup_conf", "Dial-up Settings", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        btnAdd_new->setText(QApplication::translate("dialup_conf", "Add New", 0, QApplication::UnicodeUTF8));
        btnEdit->setText(QApplication::translate("dialup_conf", "Edit", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("dialup_conf", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dialup_conf: public Ui_dialup_conf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALUP_CONF_H
