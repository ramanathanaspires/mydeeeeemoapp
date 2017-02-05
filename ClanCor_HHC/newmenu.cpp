#include "newmenu.h"
#include "cpkcs11.h"
#include "GlobalClass.h"
using namespace Globalclass;

newMenu::newMenu(QWidget *parent)
    : QMdiSubWindow(parent)
{
    btnLeft = new QPushButton;
    btnRight = new QPushButton;
    btnMain = new QPushButton;
    lbl = new QLabel;
    hbLyt = new QHBoxLayout;
    vbLyt = new QVBoxLayout;

    btnMain->setFlat(true);
    btnLeft->setFlat(true);
    btnRight->setFlat(true);
    //    btnMain->setFixedSize(130,130);//old size
    btnMain->setFixedSize(170,180);//alter by mahesh on oct 9 2013
    btnLeft->setFixedSize(60,60);
    btnRight->setFixedSize(60,60);
    hbLyt->addWidget(btnLeft,Qt::AlignVCenter);
    hbLyt->addWidget(btnMain,Qt::AlignVCenter);
    hbLyt->addWidget(btnRight,Qt::AlignVCenter);
    vbLyt->addLayout(hbLyt);
    vbLyt->addWidget(lbl,60, Qt::AlignHCenter);
    tmpwgt = new QGroupBox(this);
    tmpwgt->setFixedSize(320,460);
    tmpwgt->setLayout(vbLyt);
    tmpwgt->move(0,120);//alter by mahesh on Oct 9 2013
    tmpwgt->setStyleSheet("QPushButton:pressed{background-color:SpringGreen; border-width:5px; border-color:Magenta; border-style:groove;}");
    setStyleSheet("background-color:black;color:white;font:bold italic 17px;");
    setWindowTitle("new menu window");

    setFocusPolicy(Qt::NoFocus);
    btnMain->setFocusPolicy(Qt::StrongFocus);
    btnLeft->setFocusPolicy(Qt::NoFocus);
    btnRight->setFocusPolicy(Qt::NoFocus);
    lbl->setFocusPolicy(Qt::NoFocus);
    tmpwgt->setFocusPolicy(Qt::NoFocus);
    if(gstrSignFileName.simplified() == "")
    {
        strlst.append(":/icons/app_lncr.png");
        strlst1.append("Application Launcher");
    }
    else
    {
        strlst.append(":/icons/App_Signed.jpg");
        strlst1.append("Application Launcher\n(PKI Secured)");
    }
    strlst.append(":/icons/utility.png");
    strlst.append(":/icons/controlmenu.png");
    strlst.append(":/icons/filebrowser.png");
    strlst1.append("Utilities Menu");
    strlst1.append("Control Menu");
    strlst1.append("File Browser");

    QIcon icon1;
    icon1.addFile(":/icons/leftAR.png");
    btnLeft->setIcon(icon1);
    btnLeft->setIconSize(QSize(40,40));
    setfocus(1);
    QIcon icon;
    icon.addFile(":/icons/rightAR.png",QSize());
    btnRight->setIcon(icon);
    btnRight->setIconSize(QSize(40,40));
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(320,460);
    setButtonDefault(btnMain);
    btnMain->setFocus();
    btnLeft->setShortcut(Qt::Key_Left);
    btnRight->setShortcut(Qt::Key_Right);
    btnMain->setAutoDefault(true);
    connect(btnLeft,SIGNAL(clicked()),this,SLOT(leftclick()));
    connect(btnRight,SIGNAL(clicked()),this,SLOT(rightclick()));
    connect(btnMain,SIGNAL(clicked()), this, SLOT(mainclick()));

    myProcess = new QProcess;
    myProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    connect(myProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(CloseApplicaton(int,QProcess::ExitStatus)));
    connect(myProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(Error(QProcess::ProcessError)));
    installEventFilter(btnMain);
}

void newMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        loadForm(DESKTOP, 0);
        this->close();
        delete this;
        return;
    }
    else if(event->key() == Qt::Key_Space)
    {
        mainclick();
        event->ignore();
        return;
    }
}

void newMenu::setfocus(int menu)
{
    QIcon icon;
    if(menu == 0)
    {
        QIcon icon1;
        btnRight->setIcon(icon1);
        btnRight->setIconSize(QSize(40,40));
    }
    else if(menu == strlst.size()-1)
    {
        QIcon icon1;
        btnLeft->setIcon(icon1);
        btnLeft->setIconSize(QSize(40,40));
    }
    icon.addFile(strlst.at(menu));
    btnMain->setIcon(icon);
    btnMain->setObjectName(strlst1.at(menu));
    lbl->setText(strlst1.at(menu));
    btnMain->setIconSize(QSize(125,125));
}

void newMenu::keyclicked(int key)
{
    if(key == Qt::Key_Right)
    {
        for(int i=0;i<4;i++)
        {
            if(btnMain->objectName() == strlst1.at(i))
            {
                if(i>0)
                {
                    QIcon icon;
                    icon.addFile(strlst.at(i-1));
                    btnMain->setIcon(icon);
                    btnMain->setIconSize(QSize(125,125));
                    btnMain->setObjectName(strlst1.at(i-1));
                    lbl->setText(strlst1.at(i-1));
                    icon.addFile(":/icons/rightAR.png",QSize());
                    btnRight->setIcon(icon);
                    btnRight->setIconSize(QSize(40,40));
                    if(!((i-2)<0))
                    {
                        icon.addFile(":/icons/leftAR.png");
                        btnLeft->setIcon(icon);
                        btnLeft->setIconSize(QSize(40,40));
                    }
                    else
                    {
                        QIcon icon1;
                        btnRight->setIcon(icon1);
                        btnRight->setIconSize(QSize(40,40));
                    }
                    update();
                }
                else
                {
                    QIcon icon1;
                    btnRight->setIcon(icon1);
                    btnRight->setIconSize(QSize(40,40));
                }
                break;
            }
        }
    }
    else if(key == Qt::Key_Left)
    {
        for(int i=0;i<4;i++)
        {
            if(btnMain->objectName() == strlst1.at(i))
            {
                if(i<3)
                {
                    QIcon icon;
                    icon.addFile(strlst.at(i+1));
                    btnMain->setIcon(icon);
                    btnMain->setIconSize(QSize(125,125));
                    btnMain->setObjectName(strlst1.at(i+1));
                    lbl->setText(strlst1.at(i+1));
                    icon.addFile(":/icons/leftAR.png");
                    btnLeft->setIcon(icon);
                    btnLeft->setIconSize(QSize(40,40));
                    if(!((i+2)>3))
                    {
                        icon.addFile(":/icons/rightAR.png",QSize());
                        btnRight->setIcon(icon);
                        btnRight->setIconSize(QSize(40,40));
                    }
                    else
                    {
                        QIcon icon1;
                        btnLeft->setIcon(icon1);
                        btnLeft->setIconSize(QSize(40,40));
                    }
                    update();
                }
                else
                {
                    QIcon icon1;
                    btnLeft->setIcon(icon1);
                    btnLeft->setIconSize(QSize(40,40));
                }
                break;
            }
        }
    }
    btnMain->setFocus();
}

void newMenu::leftclick()
{
    int tmp = (int)Qt::Key_Left;
    keyclicked(tmp);
}

void newMenu::rightclick()
{
    int tmp = (int)Qt::Key_Right;
    keyclicked(tmp);
}

void newMenu::Error(QProcess::ProcessError err)
{
    RunningApplication=false;
    mainobj->show();
    if(err==QProcess::FailedToStart)
    {
        QMessageBox::critical(0,"Error..","Failed to start\r\n");
    }
    else if(err==QProcess::Crashed)
    {
        //QMessageBox::critical(0,"Error..","Application Crashed\r\n");
    }
    else if(err==QProcess::Timedout)
    {
        QMessageBox::critical(0,"Error..","Process Timeout\r\n");
    }
    else if(err==QProcess::WriteError)
    {
        QMessageBox::critical(0,"Error..","Process write Failed\r\n");
    }
    else if(err==QProcess::ReadError)
    {
        QMessageBox::critical(0,"Error..","Process read Failed\r\n");
    }else
    {
        QMessageBox::critical(0,"Error..","Unknown process Failed\r\n");
    }
}

void newMenu::mainclick()
{
    setDisable(this);
    if((btnMain->objectName() == "Application Launcher") || (btnMain->objectName() == "Application Launcher\n(PKI Secured)"))
    {
        if(RunningApplication)
        {
            QMessageBox::critical(0,"Application Launcher","Application Already Running...!");
            //            system(QString("/etc/init.d/pcscd start").toLatin1());
            setEnabled(true);
            mainobj->hide();
            return;
        }
        if(BootFileName=="")
        {
            QMessageBox::critical(0,"Application Launcher","Please Configure the Application...!");
            setEnabled(true);
            btnMain->setFocus();
            return;
        }
        if(!QFile::exists(BootFileName))
        {
            QMessageBox::critical(0,"Application Launcher","File Not Found...!");
            setEnabled(true);
            btnMain->setFocus();
            return;
        }
        /* Verify Signature */
        if(gstrSignFileName.simplified() != "")
        {
            if(!system(QString("/etc/init.d/pcscd start").toLatin1()))
            {
                CPKCS11 c;
                c.setPin("12345678");
                c.selectKey("A67C1673-A70F-4F8A-B909-BACAE1ADEFF31", CPKCS11::eKeyIdentifierType_KEY_ID);
                if(!c.verifyData(BootFileName, gstrSignFileName))
                {
                    system(QString("/etc/init.d/pcscd stop").toLatin1());
                    QMessageBox::critical(0, "PKI verify failed", "Verify failed\n " + c.lastError());
                    setEnabled(true);
                    btnMain->setFocus();
                    return;
                }
                system(QString("/etc/init.d/pcscd stop").toLatin1());
            }else
            {
                system(QString("/etc/init.d/pcscd stop").toLatin1());
                QMessageBox::critical(0,"Error", "PC/SC daemon not ready...\n Please try after few seconds...");
                setEnabled(true);
                btnMain->setFocus();
                return;
            }
        }
        system(QString("chmod 777 " + BootFileName ).toLatin1());// Change Permisssion of file
        UpdateScreen(200);
        RunningApplication=true;
        myProcess->start(BootFileName);
        myProcess->waitForStarted();
        if(myProcess->state()==QProcess::Running)
        {
            RunningApplication=true;
            mainobj->hide();
            setEnabled(true);
        }
    }
    else if(btnMain->objectName() == "Utilities Menu")
    {
        loadForm(MAINMENU,0);
        this->close();
        delete this;
        return;
    }
    else if (btnMain->objectName() == "Control Menu")
    {
        if(typeUser==true)
        {
            QMessageBox::critical(0,"User","Admin can only do this. You don't have rights!");
            setEnabled(true);
        }
        else
        {
            loadForm(SETTINGMENU,0);
            this->close();
            delete this;
            return;
        }
    }
    else
    {
        setEnabled(false);
        filebrowser *f = new filebrowser;
        f->opnsavDialog();
        this->close();
        delete this;
        return;
    }
}

void newMenu::CloseApplicaton(int,QProcess::ExitStatus)
{    
    RunningApplication=false;
    mainobj->show();
}


bool newMenu::eventFilter()
{
    return false;
}
