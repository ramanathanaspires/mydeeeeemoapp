/********************************************************************************
** Form generated from reading UI file 'gpssettings.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPSSETTINGS_H
#define UI_GPSSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GpsSettings
{
public:
    QGroupBox *groupBox;
    QLabel *lblLatitude;
    QLineEdit *lineEdit_ftp_url;
    QLabel *lblLatitude_2;
    QLabel *lblLatitude_3;
    QLineEdit *lineEdit_userName;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QCheckBox *checkBox;

    void setupUi(QDialog *GpsSettings)
    {
        if (GpsSettings->objectName().isEmpty())
            GpsSettings->setObjectName(QString::fromUtf8("GpsSettings"));
        GpsSettings->resize(320, 480);
        groupBox = new QGroupBox(GpsSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 320, 480));
        groupBox->setAutoFillBackground(true);
        lblLatitude = new QLabel(groupBox);
        lblLatitude->setObjectName(QString::fromUtf8("lblLatitude"));
        lblLatitude->setGeometry(QRect(20, 137, 71, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setBold(true);
        font.setWeight(75);
        lblLatitude->setFont(font);
        lblLatitude->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ftp_url = new QLineEdit(groupBox);
        lineEdit_ftp_url->setObjectName(QString::fromUtf8("lineEdit_ftp_url"));
        lineEdit_ftp_url->setGeometry(QRect(93, 135, 220, 24));
        lblLatitude_2 = new QLabel(groupBox);
        lblLatitude_2->setObjectName(QString::fromUtf8("lblLatitude_2"));
        lblLatitude_2->setGeometry(QRect(20, 190, 91, 20));
        lblLatitude_2->setFont(font);
        lblLatitude_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblLatitude_3 = new QLabel(groupBox);
        lblLatitude_3->setObjectName(QString::fromUtf8("lblLatitude_3"));
        lblLatitude_3->setGeometry(QRect(20, 250, 81, 20));
        lblLatitude_3->setFont(font);
        lblLatitude_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_userName = new QLineEdit(groupBox);
        lineEdit_userName->setObjectName(QString::fromUtf8("lineEdit_userName"));
        lineEdit_userName->setGeometry(QRect(120, 190, 130, 24));
        lineEdit_password = new QLineEdit(groupBox);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(120, 240, 130, 24));
        pushButton_save = new QPushButton(groupBox);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(194, 384, 100, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons-lib/screen/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_save->setIcon(icon);
        pushButton_save->setIconSize(QSize(24, 24));
        pushButton_save->setAutoDefault(true);
        pushButton_cancel = new QPushButton(groupBox);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(53, 384, 100, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons-lib/screen/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cancel->setIcon(icon1);
        pushButton_cancel->setIconSize(QSize(24, 24));
        pushButton_cancel->setAutoDefault(true);
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 320, 261, 20));
        checkBox->setFont(font);
        QWidget::setTabOrder(lineEdit_ftp_url, lineEdit_userName);
        QWidget::setTabOrder(lineEdit_userName, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, checkBox);
        QWidget::setTabOrder(checkBox, pushButton_save);
        QWidget::setTabOrder(pushButton_save, pushButton_cancel);

        retranslateUi(GpsSettings);

        QMetaObject::connectSlotsByName(GpsSettings);
    } // setupUi

    void retranslateUi(QDialog *GpsSettings)
    {
        GpsSettings->setWindowTitle(QApplication::translate("GpsSettings", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        lblLatitude->setText(QApplication::translate("GpsSettings", "Ftp URL :", 0, QApplication::UnicodeUTF8));
        lblLatitude_2->setText(QApplication::translate("GpsSettings", "User Name :", 0, QApplication::UnicodeUTF8));
        lblLatitude_3->setText(QApplication::translate("GpsSettings", "Password :", 0, QApplication::UnicodeUTF8));
        pushButton_save->setText(QApplication::translate("GpsSettings", "Save ", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("GpsSettings", "Cancel ", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("GpsSettings", "AGPS Automatic Download", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GpsSettings: public Ui_GpsSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPSSETTINGS_H
