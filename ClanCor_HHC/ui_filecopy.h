/********************************************************************************
** Form generated from reading UI file 'filecopy.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECOPY_H
#define UI_FILECOPY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileCopy
{
public:
    QGroupBox *groupBox;
    QLabel *labelSource;
    QLabel *labelDestination;
    QLineEdit *lineEditSource;
    QLineEdit *lineEditDestination;
    QPushButton *pushButtonSource;
    QPushButton *pushButtonDestination;
    QPushButton *pushButtonCopy;
    QPushButton *pushButtonRemove;

    void setupUi(QWidget *FileCopy)
    {
        if (FileCopy->objectName().isEmpty())
            FileCopy->setObjectName(QString::fromUtf8("FileCopy"));
        FileCopy->resize(320, 480);
        groupBox = new QGroupBox(FileCopy);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 321, 471));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        labelSource = new QLabel(groupBox);
        labelSource->setObjectName(QString::fromUtf8("labelSource"));
        labelSource->setGeometry(QRect(10, 121, 61, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelSource->setFont(font);
        labelDestination = new QLabel(groupBox);
        labelDestination->setObjectName(QString::fromUtf8("labelDestination"));
        labelDestination->setGeometry(QRect(10, 195, 81, 31));
        labelDestination->setFont(font);
        lineEditSource = new QLineEdit(groupBox);
        lineEditSource->setObjectName(QString::fromUtf8("lineEditSource"));
        lineEditSource->setGeometry(QRect(94, 121, 161, 27));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font1.setPointSize(12);
        lineEditSource->setFont(font1);
        lineEditDestination = new QLineEdit(groupBox);
        lineEditDestination->setObjectName(QString::fromUtf8("lineEditDestination"));
        lineEditDestination->setGeometry(QRect(92, 195, 161, 27));
        lineEditDestination->setFont(font1);
        pushButtonSource = new QPushButton(groupBox);
        pushButtonSource->setObjectName(QString::fromUtf8("pushButtonSource"));
        pushButtonSource->setGeometry(QRect(270, 121, 40, 27));
        pushButtonDestination = new QPushButton(groupBox);
        pushButtonDestination->setObjectName(QString::fromUtf8("pushButtonDestination"));
        pushButtonDestination->setGeometry(QRect(270, 195, 40, 27));
        pushButtonCopy = new QPushButton(groupBox);
        pushButtonCopy->setObjectName(QString::fromUtf8("pushButtonCopy"));
        pushButtonCopy->setGeometry(QRect(50, 264, 71, 27));
        pushButtonCopy->setFont(font);
        pushButtonRemove = new QPushButton(groupBox);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));
        pushButtonRemove->setGeometry(QRect(170, 264, 71, 27));
        pushButtonRemove->setFont(font);

        retranslateUi(FileCopy);

        QMetaObject::connectSlotsByName(FileCopy);
    } // setupUi

    void retranslateUi(QWidget *FileCopy)
    {
        FileCopy->setWindowTitle(QApplication::translate("FileCopy", "FileCopy", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        labelSource->setText(QApplication::translate("FileCopy", "Source\n"
"Path:", 0, QApplication::UnicodeUTF8));
        labelDestination->setText(QApplication::translate("FileCopy", "Destination\n"
"Path:", 0, QApplication::UnicodeUTF8));
        pushButtonSource->setText(QString());
        pushButtonDestination->setText(QString());
        pushButtonCopy->setText(QApplication::translate("FileCopy", "Copy", 0, QApplication::UnicodeUTF8));
        pushButtonRemove->setText(QApplication::translate("FileCopy", "Remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FileCopy: public Ui_FileCopy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECOPY_H
