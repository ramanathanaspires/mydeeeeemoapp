/********************************************************************************
** Form generated from reading UI file 'PrinterSetup.ui'
**
** Created: Tue Feb 11 18:04:02 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTERSETUP_H
#define UI_PRINTERSETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PrinterSetup
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QPushButton *btnHeader;
    QPushButton *btnFooter;
    QPushButton *btnTest_print;
    QPushButton *btnHeader_revert;
    QPushButton *btnFooter_revert;

    void setupUi(QDialog *PrinterSetup)
    {
        if (PrinterSetup->objectName().isEmpty())
            PrinterSetup->setObjectName(QString::fromUtf8("PrinterSetup"));
        PrinterSetup->resize(320, 460);
        PrinterSetup->setStyleSheet(QString::fromUtf8("QDialog{Background-color:rgb(238, 238, 238)};"));
        buttonBox = new QDialogButtonBox(PrinterSetup);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(100, 387, 210, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(PrinterSetup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(38, 180, 250, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Century Schoolbook L"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        btnHeader = new QPushButton(PrinterSetup);
        btnHeader->setObjectName(QString::fromUtf8("btnHeader"));
        btnHeader->setGeometry(QRect(15, 66, 250, 50));
        btnHeader->setStyleSheet(QString::fromUtf8("QLabel {\n"
"     border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;}"));
        btnHeader->setDefault(true);
        btnHeader->setFlat(true);
        btnFooter = new QPushButton(PrinterSetup);
        btnFooter->setObjectName(QString::fromUtf8("btnFooter"));
        btnFooter->setGeometry(QRect(15, 285, 250, 50));
        btnFooter->setStyleSheet(QString::fromUtf8("QLabel {\n"
"     border: 2px solid green;\n"
"     border-radius: 4px;\n"
"     padding: 2px;}"));
        btnFooter->setDefault(true);
        btnFooter->setFlat(true);
        btnTest_print = new QPushButton(PrinterSetup);
        btnTest_print->setObjectName(QString::fromUtf8("btnTest_print"));
        btnTest_print->setGeometry(QRect(10, 388, 82, 30));
        btnHeader_revert = new QPushButton(PrinterSetup);
        btnHeader_revert->setObjectName(QString::fromUtf8("btnHeader_revert"));
        btnHeader_revert->setGeometry(QRect(275, 71, 40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/revert1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnHeader_revert->setIcon(icon);
        btnHeader_revert->setIconSize(QSize(40, 40));
        btnHeader_revert->setFlat(true);
        btnFooter_revert = new QPushButton(PrinterSetup);
        btnFooter_revert->setObjectName(QString::fromUtf8("btnFooter_revert"));
        btnFooter_revert->setGeometry(QRect(275, 290, 40, 40));
        btnFooter_revert->setIcon(icon);
        btnFooter_revert->setIconSize(QSize(40, 40));
        btnFooter_revert->setFlat(true);
        QWidget::setTabOrder(btnHeader, btnHeader_revert);
        QWidget::setTabOrder(btnHeader_revert, btnFooter);
        QWidget::setTabOrder(btnFooter, btnFooter_revert);
        QWidget::setTabOrder(btnFooter_revert, btnTest_print);
        QWidget::setTabOrder(btnTest_print, buttonBox);

        retranslateUi(PrinterSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), PrinterSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PrinterSetup, SLOT(reject()));

        QMetaObject::connectSlotsByName(PrinterSetup);
    } // setupUi

    void retranslateUi(QDialog *PrinterSetup)
    {
        PrinterSetup->setWindowTitle(QApplication::translate("PrinterSetup", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PrinterSetup", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Century Schoolbook L'; font-size:14pt; font-weight:600; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:16pt;\">PRINTER </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans'; font-size:16pt;\">SETUP</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        btnHeader->setText(QString());
        btnFooter->setText(QString());
        btnTest_print->setText(QApplication::translate("PrinterSetup", "Test Print", 0, QApplication::UnicodeUTF8));
        btnHeader_revert->setText(QString());
        btnFooter_revert->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PrinterSetup: public Ui_PrinterSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTERSETUP_H
