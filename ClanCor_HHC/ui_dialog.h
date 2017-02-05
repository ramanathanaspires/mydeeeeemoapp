/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton_Read;
    QLabel *label;
    QPushButton *pushButton_Clear;
    QLabel *label_4;
    QLabel *label_Name;
    QLabel *label_Valid;
    QLabel *label_2;
    QLabel *label_Card_No;
    QLabel *label_3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(320, 480);
        pushButton_Read = new QPushButton(Dialog);
        pushButton_Read->setObjectName(QString::fromUtf8("pushButton_Read"));
        pushButton_Read->setGeometry(QRect(30, 347, 111, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton_Read->setFont(font);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(12, 157, 61, 16));
        label->setFont(font);
        pushButton_Clear = new QPushButton(Dialog);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));
        pushButton_Clear->setGeometry(QRect(180, 347, 111, 31));
        pushButton_Clear->setFont(font);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(41, 60, 231, 24));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);
        label_Name = new QLabel(Dialog);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setGeometry(QRect(80, 214, 230, 27));
        label_Name->setFont(font);
        label_Name->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        label_Valid = new QLabel(Dialog);
        label_Valid->setObjectName(QString::fromUtf8("label_Valid"));
        label_Valid->setGeometry(QRect(156, 268, 140, 28));
        label_Valid->setFont(font);
        label_Valid->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(14, 219, 50, 16));
        label_2->setFont(font);
        label_Card_No = new QLabel(Dialog);
        label_Card_No->setObjectName(QString::fromUtf8("label_Card_No"));
        label_Card_No->setGeometry(QRect(81, 151, 230, 27));
        label_Card_No->setFont(font);
        label_Card_No->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 275, 140, 20));
        label_3->setFont(font);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_Read->setText(QApplication::translate("Dialog", "Read Card", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Card No.", 0, QApplication::UnicodeUTF8));
        pushButton_Clear->setText(QApplication::translate("Dialog", "Clear", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "Magnetic Card", 0, QApplication::UnicodeUTF8));
        label_Name->setText(QString());
        label_Valid->setText(QString());
        label_2->setText(QApplication::translate("Dialog", "Name", 0, QApplication::UnicodeUTF8));
        label_Card_No->setText(QString());
        label_3->setText(QApplication::translate("Dialog", "Valid Thru (MM/YY)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
