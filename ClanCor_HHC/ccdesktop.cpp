#include "ccdesktop.h"
#include <QMessageBox>
#include <QDateTime>
#include <stdio.h>
#include <QThread>
#include <sys/vfs.h>
#include <sys/statfs.h>

CCDesktop::CCDesktop()
    :Mutex(QMutex::Recursive)
{    

    g_ccmainObj = new CHHC80xx;
    MyServerObj = new MyServer;
    g_ccmainObj->setServerMethod(MyServerObj);
    // initalize database
    if(!Initialize1())
        return;

    MyServerObj->myTopbar->show();
    qApp->processEvents();

    mainobj=new MainWindow;
    connect(MyServerObj,SIGNAL(EnableGPRS()),mainobj,SLOT(DialupAutoGPRS()));

    mainobj->show();
    mainobj->move(0,20);

    QSqlQuery qry = db->SelectQuery("SELECT IsNeedLogin from userAccount where Type='A'");
    db->clearAll();
    if(qry.next())
    {
        if(qry.value(0).toBool()==false)
            LOGIN_MANAGEMENT = false;
        else
            LOGIN_MANAGEMENT = true;
    }
    qry.clear();
#ifdef APP_70xx
    loadForm(PIC_TESTING, 0);
#else
    if (LOGIN_MANAGEMENT ==  true)
        loadForm(LOGIN, 0);
    else
        loadForm(DESKTOP, 0);
#endif
    // Initial Call of GPRS Module
    g_ccmainObj->initializeGSMModule();
//      UpdateScreen(1000);
    myProcess = new QProcess;
    myProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    connect(myProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(CloseApplicaton(int,QProcess::ExitStatus)));
    connect(myProcess,SIGNAL(error(QProcess::ProcessError)), this, SLOT(Error(QProcess::ProcessError)));
    Execute();
}

void CCDesktop::Execute()
{     
    bool Autoboot=false;
    QSqlQuery qryBoot(db->cn);
    qryBoot = db->SelectQuery("SELECT name FROM sqlite_master WHERE name='BootConfig'");
    db->clearAll();
    if(db->IsLastError())
    {
        qryBoot.clear();
    }else
    {
        if(db->Size(qryBoot)>0)
        {
            qryBoot.clear();
//            qryBoot = db->SelectQuery("select Filename /*, Autoboot*/ from BootConfig");
            qryBoot = db->SelectQuery("select Filename from BootConfig");
            db->clearAll();
            if(db->IsLastError())
            {
                qryBoot.clear();
            }else
            {
                if(qryBoot.next())
                {
                    BootFileName=qryBoot.value(0).toString();
                    if(g_ccmainObj->getAutoboot()/*qryBoot.value(1).toBool()==true*/) Autoboot=true; else Autoboot=false;
                    qryBoot.clear();
                    qryBoot = db->SelectQuery("select SignFile from PKISignatureConf");
                    db->clearAll();
                    if(db->IsLastError())
                    {
                        qryBoot.clear();
                    }
                    else
                    {
                        if(qryBoot.next())
                        {
                            gstrSignFileName = qryBoot.value(0).toString();
                        }
                    }
                }
            }
            qryBoot.clear();
        }
    }
    QString filename;
    filename= BootFileName.mid(BootFileName.lastIndexOf("/")+1,BootFileName.length());
    system(QString("killall " +filename ).toLatin1());
    UpdateScreen(200);
    if(Autoboot==true && BootFileName!="")
    {
        if(!QFile::exists(BootFileName))
        {
            QMessageBox::critical(0,"Application Launcher","File Not Found...!");
            return;
        }
        if(gstrSignFileName != "")
        {
            if(!QFile::exists(gstrSignFileName))
            {
                QMessageBox::critical(0,"Application Launcher","Sign File Not Found...!");
                return;
            }

        }
        system(QString("chmod 777 " + BootFileName ).toLatin1());// Change Permisssion of file
        UpdateScreen(200);
        printf("Start the Appliaction\r\n");
        myProcess->start(BootFileName,QProcess::ReadWrite); //myProcess->start("./Test-Hardware-Interface",QProcess::ReadWrite);
        myProcess->waitForStarted();
        if(myProcess->state()==QProcess::Running)
        {   mainobj->hide();
            RunningApplication=true;
        }
        Loop = new QEventLoop;
        Loop->exec();
    }
    else
    {
        mainobj->show();
        RunningApplication=false;
    }
}

void CCDesktop::CloseApplicaton(int id,QProcess::ExitStatus status)
{
    Q_UNUSED(id);
    Q_UNUSED(status);
    //#ifdef Q_WS_QWS
    //    if(server!=NULL) server->refresh();
    //#endif
    Loop->quit();
    delete Loop;
    RunningApplication=false;
    //    if(status==QProcess::CrashExit)
    //    {
    //        QMessageBox::critical(0,"Error..","An Exception Error Occured!\n Restart the Application");
    //    }else
    //    {
    //        QMessageBox::critical(0,"Error..","An Application Exit!\n Restart the Application");
    //    }
    Execute();
}

void CCDesktop::Error(QProcess::ProcessError err)
{    
    RunningApplication=false;
    if(err==QProcess::FailedToStart)
    {
        QMessageBox::critical(0,"Application Launcher","Failed to start!");
    }
    else if(err==QProcess::Crashed)
    {
        //QMessageBox::critical(0,"Application Launcher","Application Crashed!");
    }
    else if(err==QProcess::Timedout)
    {
        QMessageBox::critical(0,"Application Launcher","Process Timeout!");
    }
    else if(err==QProcess::WriteError)
    {
        QMessageBox::critical(0,"Application Launcher","Process write Failed!");
    }
    else if(err==QProcess::ReadError)
    {
        QMessageBox::critical(0,"Application Launcher","Process read Failed!");
    }else
    {
        QMessageBox::critical(0,"Application Launcher","Unknown process Failed!");
    }
}
