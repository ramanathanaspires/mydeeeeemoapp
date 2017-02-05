#ifndef NEWMENU_H
#define NEWMENU_H

#include <QMdiSubWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QProcess>
class newMenu : public QMdiSubWindow
{
    Q_OBJECT
    public:
        newMenu(QWidget *parent = 0);
        void setfocus(int menu);
    private:
        QPushButton *btnLeft, * btnRight, *btnMain;
        QLabel *lbl;
        QHBoxLayout *hbLyt;
        QVBoxLayout *vbLyt;
        QStringList strlst,strlst1;
        QGroupBox *tmpwgt;
        QProcess *myProcess;
        void virtual keyPressEvent(QKeyEvent *e);
        bool eventFilter();
        void keyclicked(int key);
    private slots:
        void leftclick();
        void rightclick();
        void mainclick();
        void Error(QProcess::ProcessError err);
        void CloseApplicaton(int,QProcess::ExitStatus);

};

#endif // NEWMENU_H
