/********************************************************************************
** Form generated from reading UI file 'pic32widget.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIC32WIDGET_H
#define UI_PIC32WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pic32Widget
{
public:
    QPushButton *pushButton_testRTC;
    QPushButton *pushButton_testPrinter;
    QPushButton *pushButton_getMachineId;
    QComboBox *comboBox_Beep;
    QComboBox *comboBox_keypadMode;
    QSpinBox *spinBox_backLight;
    QLabel *label;
    QPushButton *pushButton_setBacklight;
    QLabel *label_2;
    QPushButton *pushButton_setBeep;
    QLabel *label_3;
    QPushButton *pushButton_setKeypadMode;
    QPushButton *pushButton_setkeypadBeep;
    QLabel *label_4;
    QComboBox *comboBox_keypadBeep;
    QTextEdit *textEdit;

    void setupUi(QWidget *Pic32Widget)
    {
        if (Pic32Widget->objectName().isEmpty())
            Pic32Widget->setObjectName(QString::fromUtf8("Pic32Widget"));
        Pic32Widget->resize(320, 220);
        pushButton_testRTC = new QPushButton(Pic32Widget);
        pushButton_testRTC->setObjectName(QString::fromUtf8("pushButton_testRTC"));
        pushButton_testRTC->setGeometry(QRect(130, 190, 91, 27));
        pushButton_testRTC->setDefault(true);
        pushButton_testPrinter = new QPushButton(Pic32Widget);
        pushButton_testPrinter->setObjectName(QString::fromUtf8("pushButton_testPrinter"));
        pushButton_testPrinter->setGeometry(QRect(230, 190, 90, 27));
        pushButton_testPrinter->setDefault(true);
        pushButton_getMachineId = new QPushButton(Pic32Widget);
        pushButton_getMachineId->setObjectName(QString::fromUtf8("pushButton_getMachineId"));
        pushButton_getMachineId->setGeometry(QRect(10, 190, 111, 27));
        pushButton_getMachineId->setDefault(true);
        comboBox_Beep = new QComboBox(Pic32Widget);
        comboBox_Beep->setObjectName(QString::fromUtf8("comboBox_Beep"));
        comboBox_Beep->setGeometry(QRect(120, 130, 111, 24));
        comboBox_keypadMode = new QComboBox(Pic32Widget);
        comboBox_keypadMode->setObjectName(QString::fromUtf8("comboBox_keypadMode"));
        comboBox_keypadMode->setGeometry(QRect(120, 100, 111, 24));
        spinBox_backLight = new QSpinBox(Pic32Widget);
        spinBox_backLight->setObjectName(QString::fromUtf8("spinBox_backLight"));
        spinBox_backLight->setGeometry(QRect(120, 67, 55, 24));
        spinBox_backLight->setMaximum(5);
        label = new QLabel(Pic32Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 110, 20));
        label->setLayoutDirection(Qt::RightToLeft);
        pushButton_setBacklight = new QPushButton(Pic32Widget);
        pushButton_setBacklight->setObjectName(QString::fromUtf8("pushButton_setBacklight"));
        pushButton_setBacklight->setGeometry(QRect(180, 66, 71, 27));
        pushButton_setBacklight->setDefault(true);
        label_2 = new QLabel(Pic32Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 130, 110, 20));
        label_2->setLayoutDirection(Qt::RightToLeft);
        pushButton_setBeep = new QPushButton(Pic32Widget);
        pushButton_setBeep->setObjectName(QString::fromUtf8("pushButton_setBeep"));
        pushButton_setBeep->setGeometry(QRect(240, 130, 71, 27));
        pushButton_setBeep->setDefault(true);
        label_3 = new QLabel(Pic32Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 100, 110, 20));
        label_3->setLayoutDirection(Qt::RightToLeft);
        pushButton_setKeypadMode = new QPushButton(Pic32Widget);
        pushButton_setKeypadMode->setObjectName(QString::fromUtf8("pushButton_setKeypadMode"));
        pushButton_setKeypadMode->setGeometry(QRect(240, 100, 71, 27));
        pushButton_setKeypadMode->setDefault(true);
        pushButton_setkeypadBeep = new QPushButton(Pic32Widget);
        pushButton_setkeypadBeep->setObjectName(QString::fromUtf8("pushButton_setkeypadBeep"));
        pushButton_setkeypadBeep->setGeometry(QRect(240, 160, 71, 27));
        pushButton_setkeypadBeep->setDefault(true);
        label_4 = new QLabel(Pic32Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 160, 110, 20));
        label_4->setLayoutDirection(Qt::RightToLeft);
        comboBox_keypadBeep = new QComboBox(Pic32Widget);
        comboBox_keypadBeep->setObjectName(QString::fromUtf8("comboBox_keypadBeep"));
        comboBox_keypadBeep->setGeometry(QRect(120, 160, 111, 24));
        textEdit = new QTextEdit(Pic32Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(3, 3, 315, 60));
        QFont font;
        font.setPointSize(14);
        textEdit->setFont(font);
        QWidget::setTabOrder(textEdit, spinBox_backLight);
        QWidget::setTabOrder(spinBox_backLight, pushButton_setBacklight);
        QWidget::setTabOrder(pushButton_setBacklight, comboBox_keypadMode);
        QWidget::setTabOrder(comboBox_keypadMode, pushButton_setKeypadMode);
        QWidget::setTabOrder(pushButton_setKeypadMode, comboBox_Beep);
        QWidget::setTabOrder(comboBox_Beep, pushButton_setBeep);
        QWidget::setTabOrder(pushButton_setBeep, comboBox_keypadBeep);
        QWidget::setTabOrder(comboBox_keypadBeep, pushButton_setkeypadBeep);
        QWidget::setTabOrder(pushButton_setkeypadBeep, pushButton_getMachineId);
        QWidget::setTabOrder(pushButton_getMachineId, pushButton_testRTC);
        QWidget::setTabOrder(pushButton_testRTC, pushButton_testPrinter);

        retranslateUi(Pic32Widget);

        QMetaObject::connectSlotsByName(Pic32Widget);
    } // setupUi

    void retranslateUi(QWidget *Pic32Widget)
    {
        Pic32Widget->setWindowTitle(QApplication::translate("Pic32Widget", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_testRTC->setText(QApplication::translate("Pic32Widget", "Test RTC", 0, QApplication::UnicodeUTF8));
        pushButton_testPrinter->setText(QApplication::translate("Pic32Widget", "Test Printer", 0, QApplication::UnicodeUTF8));
        pushButton_getMachineId->setText(QApplication::translate("Pic32Widget", "Get Machine ID", 0, QApplication::UnicodeUTF8));
        comboBox_Beep->clear();
        comboBox_Beep->insertItems(0, QStringList()
         << QApplication::translate("Pic32Widget", "Single Beep", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Pic32Widget", "Success Beep", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Pic32Widget", "Error Beep", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Pic32Widget", "Long Beep", 0, QApplication::UnicodeUTF8)
        );
        comboBox_keypadMode->clear();
        comboBox_keypadMode->insertItems(0, QStringList()
         << QApplication::translate("Pic32Widget", "Numeric", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Pic32Widget", "Alpha Numeric", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("Pic32Widget", "Backlight Level : ", 0, QApplication::UnicodeUTF8));
        pushButton_setBacklight->setText(QApplication::translate("Pic32Widget", "Set", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Pic32Widget", "Beep : ", 0, QApplication::UnicodeUTF8));
        pushButton_setBeep->setText(QApplication::translate("Pic32Widget", "Set", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Pic32Widget", "Keypad Mode : ", 0, QApplication::UnicodeUTF8));
        pushButton_setKeypadMode->setText(QApplication::translate("Pic32Widget", "Set", 0, QApplication::UnicodeUTF8));
        pushButton_setkeypadBeep->setText(QApplication::translate("Pic32Widget", "Set", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Pic32Widget", "keypad Beep : ", 0, QApplication::UnicodeUTF8));
        comboBox_keypadBeep->clear();
        comboBox_keypadBeep->insertItems(0, QStringList()
         << QApplication::translate("Pic32Widget", "ON", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Pic32Widget", "OFF", 0, QApplication::UnicodeUTF8)
        );
        textEdit->setHtml(QApplication::translate("Pic32Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Pic32Widget: public Ui_Pic32Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIC32WIDGET_H
