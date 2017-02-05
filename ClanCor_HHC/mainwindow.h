#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define HGT 480
#define WDT 320

#include <QtGui/QMainWindow>
#include <QMdiSubWindow>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void DialupAutoGPRS();
private slots:
//    bool setGPRSAPN();
    bool EnableDialupAutoGPRS();
private:
    QTimer tmrDialupAutoFailTry;
};


class desktopWnd: public QMdiSubWindow
{
    Q_OBJECT
public:
    desktopWnd(QWidget *parent = 0);

private:

    QPushButton *button;
    QMenu *menu_Option;
    QAction *actionMenu;
    QAction *actionLogout;
    QAction *actionShutdown;
    QAction *actionAbout;
    void keyPressEvent(QKeyEvent *event);

private slots:
    void menu_option_selected(QAction*);
    void loadMenu();
};

#endif // MAINWINDOW_H
