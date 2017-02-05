/********************************************************************************
** Form generated from reading UI file 'gps_data.ui'
**
** Created: Tue Feb 11 18:04:02 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPS_DATA_H
#define UI_GPS_DATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GPS_data
{
public:
    QLabel *lblLatitude_val;
    QLabel *lblAltitude_val;
    QLabel *lblLongitude_val;
    QLabel *lblAltitude;
    QLabel *lblNo_sat_val;
    QLabel *lblGrndSpeed;
    QLabel *lblGrndSpeed_val;
    QLabel *lblLatitude;
    QLabel *lblLongitude;
    QLabel *lblNo_sat;
    QLabel *lblLatitude_2;
    QPushButton *btnRefresh;
    QPushButton *pushButton_Download;

    void setupUi(QDialog *GPS_data)
    {
        if (GPS_data->objectName().isEmpty())
            GPS_data->setObjectName(QString::fromUtf8("GPS_data"));
        GPS_data->setWindowModality(Qt::ApplicationModal);
        GPS_data->resize(320, 480);
        GPS_data->setFocusPolicy(Qt::StrongFocus);
        GPS_data->setStyleSheet(QString::fromUtf8("QDialog{background-image: url(:/icons/GPS_bgrnd2.jpg);}"));
        lblLatitude_val = new QLabel(GPS_data);
        lblLatitude_val->setObjectName(QString::fromUtf8("lblLatitude_val"));
        lblLatitude_val->setGeometry(QRect(130, 95, 180, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lblLatitude_val->setFont(font);
        lblAltitude_val = new QLabel(GPS_data);
        lblAltitude_val->setObjectName(QString::fromUtf8("lblAltitude_val"));
        lblAltitude_val->setGeometry(QRect(130, 188, 180, 21));
        lblAltitude_val->setFont(font);
        lblLongitude_val = new QLabel(GPS_data);
        lblLongitude_val->setObjectName(QString::fromUtf8("lblLongitude_val"));
        lblLongitude_val->setGeometry(QRect(130, 141, 180, 21));
        lblLongitude_val->setFont(font);
        lblAltitude = new QLabel(GPS_data);
        lblAltitude->setObjectName(QString::fromUtf8("lblAltitude"));
        lblAltitude->setGeometry(QRect(20, 188, 81, 20));
        lblAltitude->setFont(font);
        lblNo_sat_val = new QLabel(GPS_data);
        lblNo_sat_val->setObjectName(QString::fromUtf8("lblNo_sat_val"));
        lblNo_sat_val->setGeometry(QRect(170, 275, 130, 21));
        lblNo_sat_val->setFont(font);
        lblGrndSpeed = new QLabel(GPS_data);
        lblGrndSpeed->setObjectName(QString::fromUtf8("lblGrndSpeed"));
        lblGrndSpeed->setGeometry(QRect(20, 231, 100, 20));
        lblGrndSpeed->setFont(font);
        lblGrndSpeed_val = new QLabel(GPS_data);
        lblGrndSpeed_val->setObjectName(QString::fromUtf8("lblGrndSpeed_val"));
        lblGrndSpeed_val->setGeometry(QRect(170, 231, 130, 21));
        lblGrndSpeed_val->setFont(font);
        lblLatitude = new QLabel(GPS_data);
        lblLatitude->setObjectName(QString::fromUtf8("lblLatitude"));
        lblLatitude->setGeometry(QRect(20, 95, 81, 19));
        lblLatitude->setFont(font);
        lblLongitude = new QLabel(GPS_data);
        lblLongitude->setObjectName(QString::fromUtf8("lblLongitude"));
        lblLongitude->setGeometry(QRect(20, 141, 90, 20));
        lblLongitude->setFont(font);
        lblNo_sat = new QLabel(GPS_data);
        lblNo_sat->setObjectName(QString::fromUtf8("lblNo_sat"));
        lblNo_sat->setGeometry(QRect(18, 275, 130, 20));
        lblNo_sat->setFont(font);
        lblLatitude_2 = new QLabel(GPS_data);
        lblLatitude_2->setObjectName(QString::fromUtf8("lblLatitude_2"));
        lblLatitude_2->setGeometry(QRect(80, 30, 171, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        lblLatitude_2->setFont(font1);
        btnRefresh = new QPushButton(GPS_data);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setGeometry(QRect(180, 340, 120, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Serif"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(9);
        btnRefresh->setFont(font2);
        btnRefresh->setStyleSheet(QString::fromUtf8("color:rgb(106, 35, 35);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;font: 75 12pt \"Serif\"; \n"
"\n"
""));
        btnRefresh->setAutoDefault(true);
        btnRefresh->setFlat(true);
        pushButton_Download = new QPushButton(GPS_data);
        pushButton_Download->setObjectName(QString::fromUtf8("pushButton_Download"));
        pushButton_Download->setGeometry(QRect(0, 340, 141, 41));
        pushButton_Download->setFont(font2);
        pushButton_Download->setStyleSheet(QString::fromUtf8("color:rgb(106, 35, 35);border-width: 1px;border-color:rgb(0, 0, 0); border-style: solid;font: 75 12pt \"Serif\"; \n"
"\n"
""));
        pushButton_Download->setAutoDefault(true);
        pushButton_Download->setFlat(true);

        retranslateUi(GPS_data);

        QMetaObject::connectSlotsByName(GPS_data);
    } // setupUi

    void retranslateUi(QDialog *GPS_data)
    {
        GPS_data->setWindowTitle(QApplication::translate("GPS_data", "Dialog", 0, QApplication::UnicodeUTF8));
        lblLatitude_val->setText(QString());
        lblAltitude_val->setText(QString());
        lblLongitude_val->setText(QString());
        lblAltitude->setText(QApplication::translate("GPS_data", "Altitude : ", 0, QApplication::UnicodeUTF8));
        lblNo_sat_val->setText(QString());
        lblGrndSpeed->setText(QApplication::translate("GPS_data", "Speed km/h :", 0, QApplication::UnicodeUTF8));
        lblGrndSpeed_val->setText(QString());
        lblLatitude->setText(QApplication::translate("GPS_data", "Latitude : ", 0, QApplication::UnicodeUTF8));
        lblLongitude->setText(QApplication::translate("GPS_data", "Longitude : ", 0, QApplication::UnicodeUTF8));
        lblNo_sat->setText(QApplication::translate("GPS_data", "No of Satellites : ", 0, QApplication::UnicodeUTF8));
        lblLatitude_2->setText(QApplication::translate("GPS_data", "GPS Information", 0, QApplication::UnicodeUTF8));
        btnRefresh->setText(QApplication::translate("GPS_data", "Refresh", 0, QApplication::UnicodeUTF8));
        pushButton_Download->setText(QApplication::translate("GPS_data", "AGPSDownload", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GPS_data: public Ui_GPS_data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPS_DATA_H
