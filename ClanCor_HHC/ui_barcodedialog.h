/********************************************************************************
** Form generated from reading UI file 'barcodedialog.ui'
**
** Created: Thu Jul 7 10:26:18 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARCODEDIALOG_H
#define UI_BARCODEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_BarCodeDialog
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton_Clear;

    void setupUi(QDialog *BarCodeDialog)
    {
        if (BarCodeDialog->objectName().isEmpty())
            BarCodeDialog->setObjectName(QString::fromUtf8("BarCodeDialog"));
        BarCodeDialog->resize(320, 220);
        textEdit = new QTextEdit(BarCodeDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(5, 6, 310, 169));
        QFont font;
        font.setPointSize(12);
        textEdit->setFont(font);
        pushButton_Clear = new QPushButton(BarCodeDialog);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));
        pushButton_Clear->setGeometry(QRect(200, 180, 115, 38));
        QFont font1;
        font1.setPointSize(14);
        pushButton_Clear->setFont(font1);

        retranslateUi(BarCodeDialog);

        QMetaObject::connectSlotsByName(BarCodeDialog);
    } // setupUi

    void retranslateUi(QDialog *BarCodeDialog)
    {
        BarCodeDialog->setWindowTitle(QApplication::translate("BarCodeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("BarCodeDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_Clear->setText(QApplication::translate("BarCodeDialog", "Clear", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BarCodeDialog: public Ui_BarCodeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARCODEDIALOG_H
