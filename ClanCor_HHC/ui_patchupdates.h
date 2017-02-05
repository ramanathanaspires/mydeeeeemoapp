/********************************************************************************
** Form generated from reading UI file 'patchupdates.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATCHUPDATES_H
#define UI_PATCHUPDATES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Patchupdates
{
public:
    QLabel *label_Ver_SDK;
    QPushButton *pushButton_Checkupdates;
    QLabel *label_Ver_Clancor;
    QLabel *label_Ver_Coprocessor;
    QCheckBox *checkBox_Clancor_HHC;
    QCheckBox *checkBox_CoProcessor;
    QCheckBox *checkBox_HHC_SDK;
    QPushButton *pushButton_updates;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *Patchupdates)
    {
        if (Patchupdates->objectName().isEmpty())
            Patchupdates->setObjectName(QString::fromUtf8("Patchupdates"));
        Patchupdates->resize(320, 480);
        Patchupdates->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_Ver_SDK = new QLabel(Patchupdates);
        label_Ver_SDK->setObjectName(QString::fromUtf8("label_Ver_SDK"));
        label_Ver_SDK->setGeometry(QRect(150, 187, 171, 20));
        QFont font;
        font.setPointSize(14);
        label_Ver_SDK->setFont(font);
        pushButton_Checkupdates = new QPushButton(Patchupdates);
        pushButton_Checkupdates->setObjectName(QString::fromUtf8("pushButton_Checkupdates"));
        pushButton_Checkupdates->setGeometry(QRect(100, 330, 101, 27));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_Checkupdates->setFont(font1);
        label_Ver_Clancor = new QLabel(Patchupdates);
        label_Ver_Clancor->setObjectName(QString::fromUtf8("label_Ver_Clancor"));
        label_Ver_Clancor->setGeometry(QRect(150, 147, 171, 20));
        label_Ver_Clancor->setFont(font);
        label_Ver_Coprocessor = new QLabel(Patchupdates);
        label_Ver_Coprocessor->setObjectName(QString::fromUtf8("label_Ver_Coprocessor"));
        label_Ver_Coprocessor->setGeometry(QRect(150, 227, 171, 20));
        label_Ver_Coprocessor->setFont(font);
        checkBox_Clancor_HHC = new QCheckBox(Patchupdates);
        checkBox_Clancor_HHC->setObjectName(QString::fromUtf8("checkBox_Clancor_HHC"));
        checkBox_Clancor_HHC->setGeometry(QRect(1, 147, 142, 22));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        checkBox_Clancor_HHC->setFont(font2);
        checkBox_CoProcessor = new QCheckBox(Patchupdates);
        checkBox_CoProcessor->setObjectName(QString::fromUtf8("checkBox_CoProcessor"));
        checkBox_CoProcessor->setGeometry(QRect(2, 227, 142, 22));
        checkBox_CoProcessor->setFont(font);
        checkBox_HHC_SDK = new QCheckBox(Patchupdates);
        checkBox_HHC_SDK->setObjectName(QString::fromUtf8("checkBox_HHC_SDK"));
        checkBox_HHC_SDK->setGeometry(QRect(2, 187, 141, 22));
        checkBox_HHC_SDK->setFont(font);
        pushButton_updates = new QPushButton(Patchupdates);
        pushButton_updates->setObjectName(QString::fromUtf8("pushButton_updates"));
        pushButton_updates->setGeometry(QRect(9, 330, 71, 27));
        pushButton_updates->setFont(font1);
        pushButton_Cancel = new QPushButton(Patchupdates);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(241, 330, 71, 27));
        pushButton_Cancel->setFont(font1);
        pushButton_Checkupdates->raise();
        checkBox_Clancor_HHC->raise();
        checkBox_CoProcessor->raise();
        checkBox_HHC_SDK->raise();
        pushButton_updates->raise();
        pushButton_Cancel->raise();
        label_Ver_Coprocessor->raise();
        label_Ver_Clancor->raise();
        label_Ver_SDK->raise();
        QWidget::setTabOrder(pushButton_Checkupdates, checkBox_Clancor_HHC);
        QWidget::setTabOrder(checkBox_Clancor_HHC, checkBox_HHC_SDK);
        QWidget::setTabOrder(checkBox_HHC_SDK, checkBox_CoProcessor);
        QWidget::setTabOrder(checkBox_CoProcessor, pushButton_updates);
        QWidget::setTabOrder(pushButton_updates, pushButton_Cancel);

        retranslateUi(Patchupdates);

        QMetaObject::connectSlotsByName(Patchupdates);
    } // setupUi

    void retranslateUi(QDialog *Patchupdates)
    {
        Patchupdates->setWindowTitle(QApplication::translate("Patchupdates", "Dialog", 0, QApplication::UnicodeUTF8));
        label_Ver_SDK->setText(QString());
        pushButton_Checkupdates->setText(QApplication::translate("Patchupdates", "Check updates", 0, QApplication::UnicodeUTF8));
        label_Ver_Clancor->setText(QString());
        label_Ver_Coprocessor->setText(QString());
        checkBox_Clancor_HHC->setText(QApplication::translate("Patchupdates", "Clancor_HHC [F1]   ", 0, QApplication::UnicodeUTF8));
        checkBox_CoProcessor->setText(QApplication::translate("Patchupdates", "Co-Processor [F3]   ", 0, QApplication::UnicodeUTF8));
        checkBox_HHC_SDK->setText(QApplication::translate("Patchupdates", "HHC_SDK [F2]   ", 0, QApplication::UnicodeUTF8));
        pushButton_updates->setText(QApplication::translate("Patchupdates", "Update", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("Patchupdates", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Patchupdates: public Ui_Patchupdates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATCHUPDATES_H
