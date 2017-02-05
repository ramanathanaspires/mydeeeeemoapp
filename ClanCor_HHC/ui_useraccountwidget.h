/********************************************************************************
** Form generated from reading UI file 'useraccountwidget.ui'
**
** Created: Tue Feb 11 18:04:03 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERACCOUNTWIDGET_H
#define UI_USERACCOUNTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserAccountWidget
{
public:
    QGroupBox *title_groupBox;
    QLabel *label;
    QCheckBox *checkBox;
    QLabel *label_2;
    QLabel *label_Background;
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
    QPushButton *pushButton_add;
    QTableView *tableView_users;
    QPushButton *pushButton_modify;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_close;

    void setupUi(QWidget *UserAccountWidget)
    {
        if (UserAccountWidget->objectName().isEmpty())
            UserAccountWidget->setObjectName(QString::fromUtf8("UserAccountWidget"));
        UserAccountWidget->resize(320, 220);
        title_groupBox = new QGroupBox(UserAccountWidget);
        title_groupBox->setObjectName(QString::fromUtf8("title_groupBox"));
        title_groupBox->setGeometry(QRect(0, 0, 320, 40));
        title_groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{border:none; border-image: url(:/icons-lib/screen/topbar_long.png);}\n"
""));
        label = new QLabel(title_groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 280, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLineWidth(1);
        label->setAlignment(Qt::AlignCenter);
        checkBox = new QCheckBox(title_groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(46, 8, 25, 25));
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator{width: 25px;height: 25px;}                                               \n"
"QCheckBox::indicator:checked {image: url(:/icons-lib/checked_box.png);}\n"
"QCheckBox::indicator:unchecked {image: url(:/icons-lib/check_box.png);}"));
        checkBox->setCheckable(true);
        checkBox->setChecked(false);
        label_2 = new QLabel(UserAccountWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(3, 7, 20, 25));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/icons-lib/screen/records_icon.png);"));
        label_2->setLineWidth(1);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/topbar/images/topbar/patients_icon.png")));
        label_Background = new QLabel(UserAccountWidget);
        label_Background->setObjectName(QString::fromUtf8("label_Background"));
        label_Background->setGeometry(QRect(0, 0, 320, 220));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_Background->sizePolicy().hasHeightForWidth());
        label_Background->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("DejaVu Sans"));
        font1.setPointSize(22);
        label_Background->setFont(font1);
        label_Background->setStyleSheet(QString::fromUtf8("background-image: url(:/icons-lib/screen/background.png);"));
        label_Background->setAlignment(Qt::AlignCenter);
        groupBox_Login = new QGroupBox(UserAccountWidget);
        groupBox_Login->setObjectName(QString::fromUtf8("groupBox_Login"));
        groupBox_Login->setGeometry(QRect(4, 40, 311, 175));
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
        pushButton_add = new QPushButton(groupBox_Login_1);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setGeometry(QRect(4, 120, 70, 30));
        pushButton_add->setAutoDefault(true);
        tableView_users = new QTableView(groupBox_Login_1);
        tableView_users->setObjectName(QString::fromUtf8("tableView_users"));
        tableView_users->setGeometry(QRect(0, 0, 287, 110));
        QFont font2;
        font2.setFamily(QString::fromUtf8("DejaVu Sans"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        tableView_users->setFont(font2);
        tableView_users->setFocusPolicy(Qt::TabFocus);
        tableView_users->setStyleSheet(QString::fromUtf8(""));
        tableView_users->setFrameShadow(QFrame::Plain);
        tableView_users->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_users->setTabKeyNavigation(false);
        tableView_users->setAlternatingRowColors(true);
        tableView_users->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView_users->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_users->setShowGrid(true);
        tableView_users->setGridStyle(Qt::SolidLine);
        tableView_users->horizontalHeader()->setCascadingSectionResizes(false);
        tableView_users->horizontalHeader()->setDefaultSectionSize(50);
        tableView_users->horizontalHeader()->setHighlightSections(false);
        tableView_users->horizontalHeader()->setMinimumSectionSize(15);
        tableView_users->verticalHeader()->setVisible(false);
        tableView_users->verticalHeader()->setHighlightSections(false);
        pushButton_modify = new QPushButton(groupBox_Login_1);
        pushButton_modify->setObjectName(QString::fromUtf8("pushButton_modify"));
        pushButton_modify->setGeometry(QRect(74, 120, 70, 30));
        pushButton_modify->setAutoDefault(true);
        pushButton_delete = new QPushButton(groupBox_Login_1);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(144, 120, 70, 30));
        pushButton_delete->setAutoDefault(true);
        pushButton_close = new QPushButton(groupBox_Login_1);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(214, 120, 70, 30));
        pushButton_close->setAutoDefault(true);

        gridLayout->addWidget(groupBox_Login_1, 1, 2, 1, 1);

        label_Background->raise();
        title_groupBox->raise();
        label_2->raise();
        groupBox_Login->raise();
        QWidget::setTabOrder(checkBox, tableView_users);
        QWidget::setTabOrder(tableView_users, pushButton_add);
        QWidget::setTabOrder(pushButton_add, pushButton_modify);
        QWidget::setTabOrder(pushButton_modify, pushButton_delete);
        QWidget::setTabOrder(pushButton_delete, pushButton_close);

        retranslateUi(UserAccountWidget);

        QMetaObject::connectSlotsByName(UserAccountWidget);
    } // setupUi

    void retranslateUi(QWidget *UserAccountWidget)
    {
        UserAccountWidget->setWindowTitle(QApplication::translate("UserAccountWidget", "Form", 0, QApplication::UnicodeUTF8));
        title_groupBox->setTitle(QString());
        label->setText(QApplication::translate("UserAccountWidget", "User Accounts", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QString());
        label_2->setText(QString());
        label_Background->setText(QString());
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
        pushButton_add->setText(QApplication::translate("UserAccountWidget", "Add", 0, QApplication::UnicodeUTF8));
        pushButton_modify->setText(QApplication::translate("UserAccountWidget", "Modify", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("UserAccountWidget", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_close->setText(QApplication::translate("UserAccountWidget", "[F4] Close", 0, QApplication::UnicodeUTF8));
        pushButton_close->setShortcut(QApplication::translate("UserAccountWidget", "F4", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserAccountWidget: public Ui_UserAccountWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERACCOUNTWIDGET_H
