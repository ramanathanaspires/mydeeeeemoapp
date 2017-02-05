/********************************************************************************
** Form generated from reading UI file 'userloginwidget.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLOGINWIDGET_H
#define UI_USERLOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserLoginWidget
{
public:
    QGroupBox *groupBox_Login;
    QGridLayout *gridLayout;
    QLabel *label_top;
    QLabel *label_topLeft;
    QLabel *label_left;
    QLabel *label_bottomLeft;
    QLabel *label_Bottom;
    QLabel *label_topRight;
    QLabel *label_right_3;
    QLabel *label_bottomRight;
    QGroupBox *groupBox_Login_1;
    QLabel *label_userId;
    QLabel *label_Password;
    QGroupBox *groupBox_lineEdit_1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_right_7;
    QLineEdit *lineEdit_Password;
    QLabel *label_right_8;
    QComboBox *comboBox_LoginID;
    QGroupBox *title_groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_Background;
    QPushButton *toolButton_login;

    void setupUi(QWidget *UserLoginWidget)
    {
        if (UserLoginWidget->objectName().isEmpty())
            UserLoginWidget->setObjectName(QString::fromUtf8("UserLoginWidget"));
        UserLoginWidget->resize(320, 220);
        groupBox_Login = new QGroupBox(UserLoginWidget);
        groupBox_Login->setObjectName(QString::fromUtf8("groupBox_Login"));
        groupBox_Login->setGeometry(QRect(4, 50, 311, 111));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_Login->sizePolicy().hasHeightForWidth());
        groupBox_Login->setSizePolicy(sizePolicy);
        groupBox_Login->setLayoutDirection(Qt::LeftToRight);
        groupBox_Login->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border:none;\n"
"}"));
        gridLayout = new QGridLayout(groupBox_Login);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_top = new QLabel(groupBox_Login);
        label_top->setObjectName(QString::fromUtf8("label_top"));
        label_top->setMaximumSize(QSize(16777215, 12));
        label_top->setStyleSheet(QString::fromUtf8("border-image:  url(:/icons-lib/screen/screensection_top.png);"));

        gridLayout->addWidget(label_top, 0, 2, 1, 1);

        label_topLeft = new QLabel(groupBox_Login);
        label_topLeft->setObjectName(QString::fromUtf8("label_topLeft"));
        label_topLeft->setMaximumSize(QSize(12, 12));
        label_topLeft->setStyleSheet(QString::fromUtf8(""));
        label_topLeft->setLineWidth(1);
        label_topLeft->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/screensection_topleft.png")));

        gridLayout->addWidget(label_topLeft, 0, 1, 1, 1);

        label_left = new QLabel(groupBox_Login);
        label_left->setObjectName(QString::fromUtf8("label_left"));
        label_left->setMaximumSize(QSize(12, 16777215));
        label_left->setStyleSheet(QString::fromUtf8("border-image:  url(:/icons-lib/screen/screensection_left.png);\n"
""));

        gridLayout->addWidget(label_left, 1, 1, 1, 1);

        label_bottomLeft = new QLabel(groupBox_Login);
        label_bottomLeft->setObjectName(QString::fromUtf8("label_bottomLeft"));
        label_bottomLeft->setMaximumSize(QSize(12, 12));
        label_bottomLeft->setStyleSheet(QString::fromUtf8(""));
        label_bottomLeft->setLineWidth(1);
        label_bottomLeft->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/screensection_bottomleft.png")));

        gridLayout->addWidget(label_bottomLeft, 2, 1, 1, 1);

        label_Bottom = new QLabel(groupBox_Login);
        label_Bottom->setObjectName(QString::fromUtf8("label_Bottom"));
        label_Bottom->setMaximumSize(QSize(16777215, 12));
        label_Bottom->setStyleSheet(QString::fromUtf8("border-image:  url(:/icons-lib/screen/screensection_bottom.png);"));

        gridLayout->addWidget(label_Bottom, 2, 2, 1, 1);

        label_topRight = new QLabel(groupBox_Login);
        label_topRight->setObjectName(QString::fromUtf8("label_topRight"));
        label_topRight->setMaximumSize(QSize(12, 12));
        label_topRight->setLineWidth(1);
        label_topRight->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/screensection_topright.png")));
        label_topRight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_topRight, 0, 3, 1, 1);

        label_right_3 = new QLabel(groupBox_Login);
        label_right_3->setObjectName(QString::fromUtf8("label_right_3"));
        label_right_3->setMaximumSize(QSize(12, 16777215));
        label_right_3->setStyleSheet(QString::fromUtf8("border-image:  url(:/icons-lib/screen/screensection_right.png);\n"
""));

        gridLayout->addWidget(label_right_3, 1, 3, 1, 1);

        label_bottomRight = new QLabel(groupBox_Login);
        label_bottomRight->setObjectName(QString::fromUtf8("label_bottomRight"));
        label_bottomRight->setMaximumSize(QSize(12, 12));
        label_bottomRight->setLineWidth(1);
        label_bottomRight->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/screensection_bottomright.png")));
        label_bottomRight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_bottomRight, 2, 3, 1, 1);

        groupBox_Login_1 = new QGroupBox(groupBox_Login);
        groupBox_Login_1->setObjectName(QString::fromUtf8("groupBox_Login_1"));
        groupBox_Login_1->setStyleSheet(QString::fromUtf8("QGroupBox{border:none;\n"
"background-image:  url(:/icons-lib/screen/screensection_middle.png);\n"
"}\n"
""));
        label_userId = new QLabel(groupBox_Login_1);
        label_userId->setObjectName(QString::fromUtf8("label_userId"));
        label_userId->setGeometry(QRect(0, 3, 80, 32));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_userId->sizePolicy().hasHeightForWidth());
        label_userId->setSizePolicy(sizePolicy1);
        label_userId->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label_userId->setFont(font);
        label_userId->setLayoutDirection(Qt::RightToLeft);
        label_Password = new QLabel(groupBox_Login_1);
        label_Password->setObjectName(QString::fromUtf8("label_Password"));
        label_Password->setGeometry(QRect(0, 43, 80, 32));
        sizePolicy1.setHeightForWidth(label_Password->sizePolicy().hasHeightForWidth());
        label_Password->setSizePolicy(sizePolicy1);
        label_Password->setMinimumSize(QSize(0, 0));
        label_Password->setFont(font);
        label_Password->setLayoutDirection(Qt::RightToLeft);
        groupBox_lineEdit_1 = new QGroupBox(groupBox_Login_1);
        groupBox_lineEdit_1->setObjectName(QString::fromUtf8("groupBox_lineEdit_1"));
        groupBox_lineEdit_1->setGeometry(QRect(90, 42, 190, 37));
        sizePolicy.setHeightForWidth(groupBox_lineEdit_1->sizePolicy().hasHeightForWidth());
        groupBox_lineEdit_1->setSizePolicy(sizePolicy);
        groupBox_lineEdit_1->setLayoutDirection(Qt::LeftToRight);
        groupBox_lineEdit_1->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border:none;\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_lineEdit_1);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_right_7 = new QLabel(groupBox_lineEdit_1);
        label_right_7->setObjectName(QString::fromUtf8("label_right_7"));
        label_right_7->setMaximumSize(QSize(15, 16777215));
        label_right_7->setStyleSheet(QString::fromUtf8(""));
        label_right_7->setLineWidth(1);
        label_right_7->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/textfield_left.png")));

        horizontalLayout_4->addWidget(label_right_7);

        lineEdit_Password = new QLineEdit(groupBox_lineEdit_1);
        lineEdit_Password->setObjectName(QString::fromUtf8("lineEdit_Password"));
        lineEdit_Password->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_Password->sizePolicy().hasHeightForWidth());
        lineEdit_Password->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans"));
        font1.setPointSize(14);
        lineEdit_Password->setFont(font1);
        lineEdit_Password->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border:none;\n"
"	background-image:  url(:/icons-lib/screen/textfield_middle.png);\n"
"\n"
"}"));
        lineEdit_Password->setMaxLength(30);
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(lineEdit_Password);

        label_right_8 = new QLabel(groupBox_lineEdit_1);
        label_right_8->setObjectName(QString::fromUtf8("label_right_8"));
        label_right_8->setMaximumSize(QSize(15, 16777215));
        label_right_8->setLineWidth(1);
        label_right_8->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/textfield_right.png")));
        label_right_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_right_8);

        comboBox_LoginID = new QComboBox(groupBox_Login_1);
        comboBox_LoginID->setObjectName(QString::fromUtf8("comboBox_LoginID"));
        comboBox_LoginID->setGeometry(QRect(91, 0, 190, 31));
        comboBox_LoginID->setMinimumSize(QSize(15, 0));
        comboBox_LoginID->setFont(font1);
        comboBox_LoginID->setEditable(true);

        gridLayout->addWidget(groupBox_Login_1, 1, 2, 1, 1);

        title_groupBox = new QGroupBox(UserLoginWidget);
        title_groupBox->setObjectName(QString::fromUtf8("title_groupBox"));
        title_groupBox->setGeometry(QRect(0, 0, 320, 40));
        title_groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{border:none; border-image: url(:/icons-lib/screen/topbar_long.png);}\n"
""));
        label = new QLabel(title_groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 280, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setLineWidth(1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(UserLoginWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(4, 7, 20, 25));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/icons-lib/screen/login.png);"));
        label_2->setLineWidth(1);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/topbar/images/topbar/patients_icon.png")));
        label_Background = new QLabel(UserLoginWidget);
        label_Background->setObjectName(QString::fromUtf8("label_Background"));
        label_Background->setGeometry(QRect(0, 0, 320, 220));
        sizePolicy.setHeightForWidth(label_Background->sizePolicy().hasHeightForWidth());
        label_Background->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamily(QString::fromUtf8("DejaVu Sans"));
        font3.setPointSize(22);
        label_Background->setFont(font3);
        label_Background->setStyleSheet(QString::fromUtf8("background-image: url(:/icons-lib/screen/background.png);"));
        label_Background->setAlignment(Qt::AlignCenter);
        toolButton_login = new QPushButton(UserLoginWidget);
        toolButton_login->setObjectName(QString::fromUtf8("toolButton_login"));
        toolButton_login->setGeometry(QRect(212, 167, 101, 50));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DejaVu Sans"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        toolButton_login->setFont(font4);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons-lib/screen/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_login->setIcon(icon);
        toolButton_login->setIconSize(QSize(48, 48));
        toolButton_login->setAutoDefault(true);
        label_Background->raise();
        groupBox_Login->raise();
        title_groupBox->raise();
        label_2->raise();
        toolButton_login->raise();
        QWidget::setTabOrder(comboBox_LoginID, toolButton_login);

        retranslateUi(UserLoginWidget);

        QMetaObject::connectSlotsByName(UserLoginWidget);
    } // setupUi

    void retranslateUi(QWidget *UserLoginWidget)
    {
        UserLoginWidget->setWindowTitle(QApplication::translate("UserLoginWidget", "Form", 0, QApplication::UnicodeUTF8));
        UserLoginWidget->setWindowFilePath(QString());
        groupBox_Login->setTitle(QString());
        label_top->setText(QString());
        label_topLeft->setText(QString());
        label_left->setText(QString());
        label_bottomLeft->setText(QString());
        label_Bottom->setText(QString());
        label_topRight->setText(QString());
        label_right_3->setText(QString());
        label_bottomRight->setText(QString());
        groupBox_Login_1->setTitle(QString());
        label_userId->setText(QApplication::translate("UserLoginWidget", "User ID", 0, QApplication::UnicodeUTF8));
        label_Password->setText(QApplication::translate("UserLoginWidget", "Password", 0, QApplication::UnicodeUTF8));
        groupBox_lineEdit_1->setTitle(QString());
        label_right_7->setText(QString());
        label_right_8->setText(QString());
        title_groupBox->setTitle(QString());
        label->setText(QApplication::translate("UserLoginWidget", "LOG IN", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label_Background->setText(QString());
        toolButton_login->setText(QApplication::translate("UserLoginWidget", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserLoginWidget: public Ui_UserLoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLOGINWIDGET_H
