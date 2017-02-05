/********************************************************************************
** Form generated from reading UI file 'emulator.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATOR_H
#define UI_EMULATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Emulator
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Emulator)
    {
        if (Emulator->objectName().isEmpty())
            Emulator->setObjectName(QString::fromUtf8("Emulator"));
        Emulator->resize(320, 460);
        Emulator->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        textEdit = new QTextEdit(Emulator);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 42, 301, 410));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        textEdit->setFont(font);
        lineEdit = new QLineEdit(Emulator);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 6, 301, 31));
        lineEdit->setFont(font);

        retranslateUi(Emulator);

        QMetaObject::connectSlotsByName(Emulator);
    } // setupUi

    void retranslateUi(QDialog *Emulator)
    {
        Emulator->setWindowTitle(QApplication::translate("Emulator", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Emulator: public Ui_Emulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATOR_H
