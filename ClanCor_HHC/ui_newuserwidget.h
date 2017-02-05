/********************************************************************************
** Form generated from reading UI file 'newuserwidget.ui'
**
** Created: Thu May 24 17:13:25 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSERWIDGET_H
#define UI_NEWUSERWIDGET_H

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

class Ui_NewUserWidget
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
    QGroupBox *groupBox_lineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_right_2;
    QLineEdit *lineEdit_LoginID;
    QLabel *label_right;
    QGroupBox *groupBox_lineEdit_1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_right_7;
    QLineEdit *lineEdit_Password;
    QLabel *label_right_8;
    QPushButton *pushButton_fingerPrint;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QLabel *label_Password_2;
    QComboBox *comboBox;
    QLabel *label_Background;
    QGroupBox *title_groupBox;
    QLabel *label_title;
    QLabel *label_2;

    void setupUi(QWidget *NewUserWidget)
    {
        if (NewUserWidget->objectName().isEmpty())
            NewUserWidget->setObjectName(QString::fromUtf8("NewUserWidget"));
        NewUserWidget->resize(320, 220);
        groupBox_Login = new QGroupBox(NewUserWidget);
        groupBox_Login->setObjectName(QString::fromUtf8("groupBox_Login"));
        groupBox_Login->setGeometry(QRect(4, 40, 311, 175));
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
        groupBox_lineEdit = new QGroupBox(groupBox_Login_1);
        groupBox_lineEdit->setObjectName(QString::fromUtf8("groupBox_lineEdit"));
        groupBox_lineEdit->setGeometry(QRect(90, 2, 198, 37));
        sizePolicy.setHeightForWidth(groupBox_lineEdit->sizePolicy().hasHeightForWidth());
        groupBox_lineEdit->setSizePolicy(sizePolicy);
        groupBox_lineEdit->setLayoutDirection(Qt::LeftToRight);
        groupBox_lineEdit->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{\n"
"border:none;\n"
"}"));
        horizontalLayout = new QHBoxLayout(groupBox_lineEdit);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_right_2 = new QLabel(groupBox_lineEdit);
        label_right_2->setObjectName(QString::fromUtf8("label_right_2"));
        label_right_2->setMaximumSize(QSize(15, 16777215));
        label_right_2->setStyleSheet(QString::fromUtf8(""));
        label_right_2->setLineWidth(1);
        label_right_2->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/textfield_left.png")));

        horizontalLayout->addWidget(label_right_2);

        lineEdit_LoginID = new QLineEdit(groupBox_lineEdit);
        lineEdit_LoginID->setObjectName(QString::fromUtf8("lineEdit_LoginID"));
        lineEdit_LoginID->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_LoginID->sizePolicy().hasHeightForWidth());
        lineEdit_LoginID->setSizePolicy(sizePolicy2);
        lineEdit_LoginID->setFont(font);
        lineEdit_LoginID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"    border:none;\n"
"	background-image:  url(:/icons-lib/screen/textfield_middle.png);\n"
"\n"
"}"));
        lineEdit_LoginID->setMaxLength(30);

        horizontalLayout->addWidget(lineEdit_LoginID);

        label_right = new QLabel(groupBox_lineEdit);
        label_right->setObjectName(QString::fromUtf8("label_right"));
        label_right->setMaximumSize(QSize(15, 16777215));
        label_right->setLineWidth(1);
        label_right->setPixmap(QPixmap(QString::fromUtf8(":/icons-lib/screen/textfield_right.png")));
        label_right->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_right);

        groupBox_lineEdit_1 = new QGroupBox(groupBox_Login_1);
        groupBox_lineEdit_1->setObjectName(QString::fromUtf8("groupBox_lineEdit_1"));
        groupBox_lineEdit_1->setGeometry(QRect(90, 42, 198, 37));
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

        pushButton_fingerPrint = new QPushButton(groupBox_Login_1);
        pushButton_fingerPrint->setObjectName(QString::fromUtf8("pushButton_fingerPrint"));
        pushButton_fingerPrint->setGeometry(QRect(2, 81, 80, 70));
        pushButton_fingerPrint->setIconSize(QSize(80, 70));
        pushButton_fingerPrint->setAutoDefault(true);
        pushButton_save = new QPushButton(groupBox_Login_1);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(186, 120, 100, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons-lib/screen/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_save->setIcon(icon);
        pushButton_save->setIconSize(QSize(24, 24));
        pushButton_save->setAutoDefault(true);
        pushButton_cancel = new QPushButton(groupBox_Login_1);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(86, 120, 100, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons-lib/screen/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cancel->setIcon(icon1);
        pushButton_cancel->setIconSize(QSize(24, 24));
        pushButton_cancel->setAutoDefault(true);
        label_Password_2 = new QLabel(groupBox_Login_1);
        label_Password_2->setObjectName(QString::fromUtf8("label_Password_2"));
        label_Password_2->setGeometry(QRect(84, 84, 60, 32));
        sizePolicy1.setHeightForWidth(label_Password_2->sizePolicy().hasHeightForWidth());
        label_Password_2->setSizePolicy(sizePolicy1);
        label_Password_2->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label_Password_2->setFont(font2);
        label_Password_2->setLayoutDirection(Qt::RightToLeft);
        comboBox = new QComboBox(groupBox_Login_1);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(146, 90, 140, 24));

        gridLayout->addWidget(groupBox_Login_1, 1, 2, 1, 1);

        label_Background = new QLabel(NewUserWidget);
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
        title_groupBox = new QGroupBox(NewUserWidget);
        title_groupBox->setObjectName(QString::fromUtf8("title_groupBox"));
        title_groupBox->setGeometry(QRect(0, 0, 320, 40));
        title_groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{border:none; border-image: url(:/icons-lib/screen/topbar_long.png);}\n"
""));
        label_title = new QLabel(title_groupBox);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(30, 10, 280, 20));
        QFont font4;
        font4.setFamily(QString::fromUtf8("DejaVu Sans"));
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setWeight(75);
        label_title->setFont(font4);
        label_title->setLineWidth(1);
        label_title->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(NewUserWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(3, 7, 20, 25));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/icons-lib/screen/login.png);"));
        label_2->setLineWidth(1);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/topbar/images/topbar/patients_icon.png")));
        label_Background->raise();
        groupBox_Login->raise();
        title_groupBox->raise();
        label_2->raise();
        QWidget::setTabOrder(lineEdit_LoginID, lineEdit_Password);
        QWidget::setTabOrder(lineEdit_Password, comboBox);
        QWidget::setTabOrder(comboBox, pushButton_fingerPrint);
        QWidget::setTabOrder(pushButton_fingerPrint, pushButton_save);
        QWidget::setTabOrder(pushButton_save, pushButton_cancel);

        retranslateUi(NewUserWidget);

        QMetaObject::connectSlotsByName(NewUserWidget);
    } // setupUi

    void retranslateUi(QWidget *NewUserWidget)
    {
        NewUserWidget->setWindowTitle(QApplication::translate("NewUserWidget", "Form", 0, QApplication::UnicodeUTF8));
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
        label_userId->setText(QApplication::translate("NewUserWidget", "User ID", 0, QApplication::UnicodeUTF8));
        label_Password->setText(QApplication::translate("NewUserWidget", "Password", 0, QApplication::UnicodeUTF8));
        groupBox_lineEdit->setTitle(QString());
        label_right_2->setText(QString());
        lineEdit_LoginID->setText(QString());
        label_right->setText(QString());
        groupBox_lineEdit_1->setTitle(QString());
        label_right_7->setText(QString());
        label_right_8->setText(QString());
        pushButton_fingerPrint->setText(QApplication::translate("NewUserWidget", "Finger Print", 0, QApplication::UnicodeUTF8));
        pushButton_save->setText(QApplication::translate("NewUserWidget", "Save [F2]", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("NewUserWidget", "Cancel [F4]", 0, QApplication::UnicodeUTF8));
        label_Password_2->setText(QApplication::translate("NewUserWidget", "security", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("NewUserWidget", "Password only", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewUserWidget", "Fingerprint only", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewUserWidget", "Both", 0, QApplication::UnicodeUTF8)
        );
        label_Background->setText(QString());
        title_groupBox->setTitle(QString());
        label_title->setText(QApplication::translate("NewUserWidget", "NEW USER ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NewUserWidget: public Ui_NewUserWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSERWIDGET_H
