#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QString cat,monkey,kangaroo,lamb,sheep;
    QString c="அரிசி";
    QString m="சக்கரை";
    QString k="kangaroo";
    QString l="lamb";
    QString s="sheep";
    QString kg1="2";
    QString price1="20";
    QString kg2="23";
    QString price2="157890";
    QString monkey=m.leftJustified(20,' ');
    QString cat=kg2.rightJustified(4,' ');
    QString lamb=price2.rightJustified(10,' ');
    qDebug()<<"\r data is"<<monkey<<cat<<lamb<<m.length();
    QString monkey1=c.leftJustified(20,' ');
    QString cat1=kg1.rightJustified(4,' ');
    QString lamb1=price1.rightJustified(10,' ');
    qDebug()<<"\r data is"<<monkey1<<cat1<<lamb1<<c.length();
}

MainWindow::~MainWindow()
{
    delete ui;
}
