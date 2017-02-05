#ifndef CCDESKTOP_H
#define CCDESKTOP_H

#include "GlobalClass.h"
using namespace Globalclass;

class CCDesktop : public QObject
{
    Q_OBJECT
private:
    QTimer timer;
    QTimer VolumeTimer;
    QProcess *myProcess;
    QEventLoop *Loop;
    QString Data;
    QMutex Mutex;
    QTimer *Timer;
    QPushButton *lblBattery;
    QLabel *lblTower;
    QLabel *lbl_Keypad;
    QPushButton *btnDT;
    QTimer t;
    QTimer *BootTimer;

    int Current;
    int Last_Batval;
    int Percentage;
    void Execute();
public:
    CCDesktop();        
private slots:
    void CloseApplicaton(int,QProcess::ExitStatus);
    void Error(QProcess::ProcessError);

};

#endif // CCDESKTOP_H

