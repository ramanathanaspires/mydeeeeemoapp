/********************************************************************************
** Form generated from reading UI file 'hadware.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HADWARE_H
#define UI_HADWARE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hadware
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButtonPrint;

    void setupUi(QWidget *Hadware)
    {
        if (Hadware->objectName().isEmpty())
            Hadware->setObjectName(QString::fromUtf8("Hadware"));
        Hadware->resize(320, 460);
        Hadware->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        textEdit = new QTextEdit(Hadware);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 15, 301, 397));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        textEdit->setFont(font);
        pushButtonPrint = new QPushButton(Hadware);
        pushButtonPrint->setObjectName(QString::fromUtf8("pushButtonPrint"));
        pushButtonPrint->setGeometry(QRect(130, 420, 93, 30));
        pushButtonPrint->setFont(font);

        retranslateUi(Hadware);

        QMetaObject::connectSlotsByName(Hadware);
    } // setupUi

    void retranslateUi(QWidget *Hadware)
    {
        Hadware->setWindowTitle(QApplication::translate("Hadware", "Hadware", 0, QApplication::UnicodeUTF8));
        pushButtonPrint->setText(QApplication::translate("Hadware", "PRINT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Hadware: public Ui_Hadware {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HADWARE_H
