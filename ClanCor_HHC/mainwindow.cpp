#include "mainwindow.h"
#include "newmenu.h"
#include "aboutdialog.h"
#include <QTextCharFormat>
#include "GlobalClass.h"
using namespace Globalclass;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(MWID,MHGT);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);

    setCentralWidget(MdiArea);
    titBar=addToolBar("titleBar");
    titleBarInit();
    titBar->setFocusPolicy(Qt::NoFocus);
    titBar->addWidget(title);
    QString tmp1, tmp;
    tmp = "password";
    tmp1="";
}

MainWindow::~MainWindow()
{
}

//bool MainWindow::setGPRSAPN()                   // Implemented this alternative logic to handle application hang while initializing GPRS module...
//{
//    QSqlQuery query;
//    QString network;
//    bool apnFlag=false;
//    if (g_ccmainObj->gsmNetwork(network))              //To get Home Network Name
//    {
//        if(network != "")
//        {
//            query = db->SelectQuery("select name from SQLITE_MASTER where name like 'APN_MASTER'");
//            db->clearAll();
//            if(db->IsLastError())
//            {
//                query.clear();
//                return false;
//            }
//            if(query.next())
//            {
//                query.clear();
//                query = db->SelectQuery("select APN_VALUE,0 FROM APN_MASTER where upper(APN_NAME) = '" + network.toUpper() + "' and length(APN_VALUE) >0 UNION select APN,1 from NETWORKAPN where upper(Network) like '" + network.toUpper() + "' and length(APN)> 0 ORDER BY 2 ");
//                db->clearAll();
//                if(db->IsLastError())
//                {
//                    query.clear();
//                    return false;
//                }
//                if(query.next())
//                {
//                    if(g_ccmainObj->serverMethod()->setGprsApn(network,query.value(0).toString()))        //Setting APN Value in GPRS Module
//                    {
//                        apnFlag=true;
//                    }
//                }
//            }
//            else
//            {
//                query.clear();
//                query = db->SelectQuery("SELECT APN from NetworkAPN where upper(Network) like '" + network.toUpper() + "' and length(apn) >0");
//                db->clearAll();
//                if(db->IsLastError())
//                {
//                    query.clear();
//                    return false;
//                }
//                if(query.next())
//                {
//                    if(g_ccmainObj->serverMethod()->setGprsApn(network, query.value(0).toString()))
//                    {
//                        apnFlag=true;
//                    }
//                }
//            }
//            query.clear();
//            if(apnFlag==false)
//            {
//                QMessageBox::critical(0,"Error APN","Please configure the APN for currently installed SIMCard..!       Network:" +network.toUpper());
//            }
//        }
//        else
//        {
//            QMessageBox::critical(0,"Error: GPRS network","No Network Service available..!");
//        }
//    }
//    else
//    {
//        QMessageBox::critical(0,"Error : GPRS Initialization", g_ccmainObj->lastError());
//    }
//    if(apnFlag)
//        DialupAutoGPRS();
//    return true;
//}

void MainWindow::DialupAutoGPRS()
{
    if(!EnableDialupAutoGPRS())
    {
        tmrDialupAutoFailTry.setInterval(300000);
        tmrDialupAutoFailTry.setSingleShot(false);
        connect(&tmrDialupAutoFailTry, SIGNAL(timeout()), this, SLOT(EnableDialupAutoGPRS()));
        tmrDialupAutoFailTry.start();
    }
}

bool MainWindow::EnableDialupAutoGPRS()
{
    QSqlQuery qry_dialupentry;

    qry_dialupentry = db->SelectQuery("select * from dialup_settings where Active_status like 'true'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry_dialupentry.clear();
        return false;
    }
    if(qry_dialupentry.next())
    {
        if(qry_dialupentry.value(1).toString() == "GPRS" && qry_dialupentry.value(2).toString() == "Always_On")
        {
            if(!g_ccmainObj->isEthernet())
            {
                if(g_ccmainObj->enableGprs())
                {
                    if(tmrDialupAutoFailTry.isActive())
                    {
                        tmrDialupAutoFailTry.stop();
                    }
                    DialupAutoGPRS_flag = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

desktopWnd::desktopWnd(QWidget *parent): QMdiSubWindow(parent)
{
    menu_Option=new QMenu;
    QFont font;
    font.setPointSize(16);

    actionMenu =new QAction("Menu",this);
    actionMenu->setFont(font);
    menu_Option->addAction(actionMenu);

    actionLogout =new QAction("Log out",this);
    actionLogout->setFont(font);
    if (LOGIN_MANAGEMENT ==  true)
        actionLogout->setEnabled(true);
    else
        actionLogout->setEnabled(false);
    menu_Option->addAction(actionLogout);

    actionShutdown =new QAction("Shut down",this);
    actionShutdown->setFont(font);
    menu_Option->addAction(actionShutdown);

    actionAbout =new QAction("About",this);
    actionAbout->setFont(font);
    menu_Option->addSeparator();
    menu_Option->addAction(actionAbout);



    connect(menu_Option,SIGNAL(triggered(QAction*)),this,SLOT(menu_option_selected(QAction*)));

    QWidget *widget = new QWidget;
    widget->setFixedSize(320,460);
    QLabel *lbl = new QLabel(widget);
    lbl->setFixedSize(320,460);
    QPixmap *p = new QPixmap;
    QSqlQuery qry = db->SelectQuery("select * from currentWallpaper");
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
    }
    if(qry.next())
    {
        p->load(qry.value(0).toString());
        lbl->setPixmap(p->scaled(320,460,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    }
    QFont font1;
    button = new QPushButton;
    button->setText("Start");
    button->setIcon(QIcon(":/icons-lib/logo.ico"));
    font1.setBold(true);
    font1.setPointSize(16);
    // font1.setFamily("Courier 10 pitch");
    button->setFont(font1);
    button->setFixedSize(100,40);
    button->setAutoDefault(true);
    QVBoxLayout *vbx =new QVBoxLayout;
    vbx->addSpacing(200);
    vbx->addWidget(button,140,Qt::AlignHCenter);
    widget->setLayout(vbx);
    widget->setFocusPolicy(Qt::NoFocus);
    this->layout()->addWidget(widget);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    setFixedSize(320,460);

    connect(button, SIGNAL(clicked()),this, SLOT(loadMenu()));
    button->setFocus();
}

void desktopWnd::menu_option_selected(QAction *action)
{
    if(action->text()=="Menu")
    {
        loadForm(NEWMENU, 1);
        this->close();
        delete this;
    }
    else if(action->text()=="Log out")
    {
        this->close();
        delete this;
        LoginId="";
        loadForm(LOGIN, 0);
    }
    else if(action->text()=="Shut down")
    {
        g_ccmainObj->serverMethod()->shutdownDialog();
    }
    else if(action->text()=="About")
    {
        AboutDialog *about =new AboutDialog;
        about->exec();
        delete about;
    }
}

void desktopWnd::loadMenu()
{
    if(menu_Option->isVisible()==false)
    {
        menu_Option->popup(QPoint(100,button->y() - menu_Option->height() -20));
        menu_Option->move(110,button->y() - menu_Option->height() +20);

        // menu_Option->popup(QPoint(110,button->y() - menu_Option->height() -20));
        // menu_Option->move(115,button->y() - menu_Option->height() +20);
        menu_Option->setActiveAction(actionMenu);
        menu_Option->setStyleSheet("font-size:12px;font-style:bold;");
    }
    else
    {
        menu_Option->setVisible(false);
    }
}
void desktopWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        loadMenu();
    }
}
