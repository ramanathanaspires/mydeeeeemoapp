/********************************************************************************
** Form generated from reading UI file 'combobox.ui'
**
** Created: Tue Jun 18 09:44:38 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBOBOX_H
#define UI_COMBOBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Combobox
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Combobox)
    {
        if (Combobox->objectName().isEmpty())
            Combobox->setObjectName(QString::fromUtf8("Combobox"));
        Combobox->resize(320, 240);
        textEdit = new QTextEdit(Combobox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 40, 301, 187));
        lineEdit = new QLineEdit(Combobox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 301, 26));

        retranslateUi(Combobox);

        QMetaObject::connectSlotsByName(Combobox);
    } // setupUi

    void retranslateUi(QWidget *Combobox)
    {
        Combobox->setWindowTitle(QApplication::translate("Combobox", "Combobox", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Combobox: public Ui_Combobox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBOBOX_H
