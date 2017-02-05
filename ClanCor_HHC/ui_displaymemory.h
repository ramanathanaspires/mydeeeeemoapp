/********************************************************************************
** Form generated from reading UI file 'displaymemory.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYMEMORY_H
#define UI_DISPLAYMEMORY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayMemory
{
public:
    QLabel *labelTitle;
    QProgressBar *progressBarRAMUsedMemory;
    QProgressBar *progressBarFlashUsedMemory;
    QLabel *labelRAMtitle;
    QLabel *labelFlashtitle;
    QLabel *labelSDtitle;
    QProgressBar *progressBarSDUsedMemory;
    QLabel *labelPendrivetitle;
    QProgressBar *progressBarThumbdriveUsedMemory;
    QLabel *labelRAMMem;
    QLabel *labelFlashMem;
    QLabel *labelSDMem;
    QLabel *labelPendriveMem;

    void setupUi(QWidget *DisplayMemory)
    {
        if (DisplayMemory->objectName().isEmpty())
            DisplayMemory->setObjectName(QString::fromUtf8("DisplayMemory"));
        DisplayMemory->resize(320, 480);
        DisplayMemory->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        labelTitle = new QLabel(DisplayMemory);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setGeometry(QRect(117, 31, 161, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelTitle->setStyleSheet(QString::fromUtf8("color: rgb(0, 85, 127);"));
        labelTitle->setAlignment(Qt::AlignCenter);
        progressBarRAMUsedMemory = new QProgressBar(DisplayMemory);
        progressBarRAMUsedMemory->setObjectName(QString::fromUtf8("progressBarRAMUsedMemory"));
        progressBarRAMUsedMemory->setGeometry(QRect(134, 99, 170, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        progressBarRAMUsedMemory->setFont(font1);
        progressBarRAMUsedMemory->setMaximum(100);
        progressBarRAMUsedMemory->setValue(0);
        progressBarFlashUsedMemory = new QProgressBar(DisplayMemory);
        progressBarFlashUsedMemory->setObjectName(QString::fromUtf8("progressBarFlashUsedMemory"));
        progressBarFlashUsedMemory->setGeometry(QRect(134, 170, 170, 23));
        progressBarFlashUsedMemory->setFont(font1);
        progressBarFlashUsedMemory->setMaximum(100);
        progressBarFlashUsedMemory->setValue(0);
        labelRAMtitle = new QLabel(DisplayMemory);
        labelRAMtitle->setObjectName(QString::fromUtf8("labelRAMtitle"));
        labelRAMtitle->setGeometry(QRect(10, 100, 91, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        labelRAMtitle->setFont(font2);
        labelFlashtitle = new QLabel(DisplayMemory);
        labelFlashtitle->setObjectName(QString::fromUtf8("labelFlashtitle"));
        labelFlashtitle->setGeometry(QRect(10, 170, 111, 30));
        labelFlashtitle->setFont(font2);
        labelSDtitle = new QLabel(DisplayMemory);
        labelSDtitle->setObjectName(QString::fromUtf8("labelSDtitle"));
        labelSDtitle->setGeometry(QRect(10, 240, 121, 30));
        labelSDtitle->setFont(font2);
        progressBarSDUsedMemory = new QProgressBar(DisplayMemory);
        progressBarSDUsedMemory->setObjectName(QString::fromUtf8("progressBarSDUsedMemory"));
        progressBarSDUsedMemory->setGeometry(QRect(134, 240, 170, 23));
        progressBarSDUsedMemory->setFont(font1);
        progressBarSDUsedMemory->setMaximum(100);
        progressBarSDUsedMemory->setValue(0);
        labelPendrivetitle = new QLabel(DisplayMemory);
        labelPendrivetitle->setObjectName(QString::fromUtf8("labelPendrivetitle"));
        labelPendrivetitle->setGeometry(QRect(10, 310, 131, 30));
        labelPendrivetitle->setFont(font2);
        progressBarThumbdriveUsedMemory = new QProgressBar(DisplayMemory);
        progressBarThumbdriveUsedMemory->setObjectName(QString::fromUtf8("progressBarThumbdriveUsedMemory"));
        progressBarThumbdriveUsedMemory->setGeometry(QRect(134, 310, 170, 23));
        progressBarThumbdriveUsedMemory->setFont(font1);
        progressBarThumbdriveUsedMemory->setMaximum(100);
        progressBarThumbdriveUsedMemory->setValue(0);
        labelRAMMem = new QLabel(DisplayMemory);
        labelRAMMem->setObjectName(QString::fromUtf8("labelRAMMem"));
        labelRAMMem->setGeometry(QRect(146, 80, 164, 16));
        labelRAMMem->setFont(font2);
        labelRAMMem->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 127);"));
        labelRAMMem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelFlashMem = new QLabel(DisplayMemory);
        labelFlashMem->setObjectName(QString::fromUtf8("labelFlashMem"));
        labelFlashMem->setGeometry(QRect(144, 150, 164, 16));
        labelFlashMem->setFont(font2);
        labelFlashMem->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 127);"));
        labelFlashMem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelSDMem = new QLabel(DisplayMemory);
        labelSDMem->setObjectName(QString::fromUtf8("labelSDMem"));
        labelSDMem->setGeometry(QRect(144, 220, 164, 16));
        labelSDMem->setFont(font2);
        labelSDMem->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 127);"));
        labelSDMem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelPendriveMem = new QLabel(DisplayMemory);
        labelPendriveMem->setObjectName(QString::fromUtf8("labelPendriveMem"));
        labelPendriveMem->setGeometry(QRect(144, 290, 164, 16));
        labelPendriveMem->setFont(font2);
        labelPendriveMem->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 127);"));
        labelPendriveMem->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(DisplayMemory);

        QMetaObject::connectSlotsByName(DisplayMemory);
    } // setupUi

    void retranslateUi(QWidget *DisplayMemory)
    {
        DisplayMemory->setWindowTitle(QApplication::translate("DisplayMemory", "DisplayMemory", 0, QApplication::UnicodeUTF8));
        labelTitle->setText(QApplication::translate("DisplayMemory", "Memory Status ", 0, QApplication::UnicodeUTF8));
        labelRAMtitle->setText(QApplication::translate("DisplayMemory", "RAM Used:", 0, QApplication::UnicodeUTF8));
        labelFlashtitle->setText(QApplication::translate("DisplayMemory", "FLASH Used:", 0, QApplication::UnicodeUTF8));
        labelSDtitle->setText(QApplication::translate("DisplayMemory", "SD Card Used:", 0, QApplication::UnicodeUTF8));
        labelPendrivetitle->setText(QApplication::translate("DisplayMemory", "Thumb Drive Used :", 0, QApplication::UnicodeUTF8));
        labelRAMMem->setText(QString());
        labelFlashMem->setText(QString());
        labelSDMem->setText(QString());
        labelPendriveMem->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DisplayMemory: public Ui_DisplayMemory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYMEMORY_H
