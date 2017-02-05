#include "GlobalClass.h"
#include "MenuWindow.h"
#include "SettingWnd.h"
#include "newmenu.h"
#include "mainwindow.h"
#include "pictureflow.h"
#include "userloginwidget.h"
#include "pic32widget.h"

using namespace Globalclass;

CHHC80xx *Globalclass::g_ccmainObj=0;
MyServer * Globalclass::MyServerObj=0;
MainWindow *Globalclass::mainobj;
QMdiArea *Globalclass::MdiArea = 0;
DBConnection *Globalclass::db=0;
QToolBar * Globalclass::titBar=0;
QLabel * Globalclass::title=0;
QPixmap *Globalclass::UserIcon=0;

int Globalclass::brightnessvalue = -1;
int Globalclass::SCREENX1=0;
int Globalclass::SCREENY1=0;

QString Globalclass::UserInfo="";
QString Globalclass::BootFileName="";
QString Globalclass::gstrSignFileName="";
QString Globalclass::LoginId="";
QString Globalclass::Password="";
QString Globalclass::gstrXMLConfig="";

bool Globalclass::typeUser=false;
bool Globalclass::RunningApplication=false;
bool Globalclass::DialupAutoGPRS_flag = false;
bool Globalclass::LOGIN_MANAGEMENT=false;
bool Globalclass::g_header=false;
bool Globalclass::g_loadImage=false;
bool Globalclass::g_footer=false;
bool Globalclass::g_bFileCopyFlag = false;

bool Globalclass::Initialize1()
{
    MdiArea = new QMdiArea;
    db=new DBConnection;
    if(!createDefault())
    {
        QMessageBox::critical(0,"Error", "Error while making default setup");
        return false;
    }
    QSqlQuery *qryref = new QSqlQuery;

    *qryref = db->SelectQuery("select * from themeSettings");
    db->clearAll();
    if(db->IsLastError())
    {
        qryref->clear();
        delete qryref;
        return false;
    }
    if(qryref->next())
    {
        qApp->setStyle(qryref->value(0).toString());
        loadStyleSheet(qryref->value(1).toString());
    }
    qryref->clear();
    MdiArea->setFocusPolicy(Qt::NoFocus);
    return true;
}

void Globalclass::titleBarInit()
{
    title=new QLabel;
    title->setFixedSize(320,20);
    titBar->setFixedSize(320,20);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("text-align: center;font:Bold;background-color:black;color:white");
    title->setFont(QFont("Trebuchet", 10, QFont::Bold));
    title->setWindowFlags(Qt::FramelessWindowHint);
    title->setFocusPolicy(Qt::NoFocus);
    titBar->setMovable(false);
    titBar->setVisible(false);
}

void Globalclass::loadForm(int parentID, int focusMenu)
{    
    switch(parentID)
    {
    case LOGIN :
    {
        UserLoginWidget *loginWidget = new UserLoginWidget;
        loginWidget->setWindowFlags(Qt::FramelessWindowHint);
        loginWidget->setGeometry(0,20,320,460);
        loginWidget->stateStart();
        loginWidget->exec();
        return;
    }
    case DESKTOP :
    {
        desktopWnd *d = new desktopWnd;
        MdiArea->addSubWindow(d);
        d->show();
        break;
    }
    case MAINMENU :
    {
        MenuWindow *Mwnd = new MenuWindow;
        MdiArea->addSubWindow(Mwnd)->setFocusPolicy(Qt::NoFocus);
        Mwnd->show();
        break;
    }
    case SETTINGMENU:
    {
        SettingWnd *setting= new SettingWnd;
        MdiArea->addSubWindow(setting);
        setting->show();
        break;
    }
    case NEWMENU:
    {
        newMenu *nm = new newMenu;
        MdiArea->addSubWindow(nm)->setFocusPolicy(Qt::NoFocus);
        nm->show();
        nm->setfocus(focusMenu);
        break;
    }
    case PIC_TESTING:
    {
        Pic32Widget *pic32obj = new Pic32Widget;
        pic32obj->setWindowFlags(Qt::FramelessWindowHint);
        pic32obj->setGeometry(0,20,320,460);
        pic32obj->exec();
        break;
    }
    }
    qApp->processEvents();
}

void Globalclass::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/qss/" + sheetName.toLower() + ".qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(styleSheet);
}

QString Globalclass::getStyle()
{
    QRegExp regExp(".(.*)\\+?Style");
    QString defaultStyle = QApplication::style()->metaObject()->className();

    if (regExp.exactMatch(defaultStyle))
        defaultStyle = regExp.cap(1);
    return defaultStyle;
}

void Globalclass::setButtonDefault(QWidget *qw)
{
    foreach(QPushButton* qpb, (qw->findChildren<QPushButton*>()))
    {
        qpb->setAutoDefault(true);
    }
}

void Globalclass::clearAll(QWidget *qw)
{
    int res=QMessageBox::information(0,"Confirmation","Do you want to Clear?",QMessageBox::Yes,QMessageBox::No);
    if(res==QMessageBox::Yes)
    {
        foreach(QLineEdit* le1,qw->findChildren<QLineEdit*>())
        {
            if(le1->property("MA").toString()!="A" && le1->property("MA").toString()!="B"&& le1->property("MA").toString()!="S" && le1->property("MA").toString()!="E" )
            {
                le1->clear();
            }
        }

        foreach(QComboBox* cb1,qw->findChildren<QComboBox*>())
        {
            cb1->setCurrentIndex(-1);
        }
    }
}

void Globalclass::setDisable(QWidget *qw)
{
    qw->setEnabled(false);
    qApp->processEvents();
}

void Globalclass::UpdateScreen(int msec)
{
    QEventLoop *Loop = new QEventLoop;
    QTimer *t = new QTimer;
    t->setInterval(msec);
    t->setSingleShot(true);
    QObject::connect(t,SIGNAL(timeout()),Loop,SLOT(quit()));
    t->start();
    Loop->exec();
    delete t;
    delete Loop;
}
bool Globalclass::createDefault()
{
    bool b;
    QSqlQuery qryref;
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS TFTContrast(value number)");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS BootConfig(Filename varchar(100),Autoboot Boolean, Signfile varchar)");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS PKISignatureConf (SignFile varchar(500))");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS SCREEN_SETTING(backlight numeric, screenlock numeric,standby numeric)");
    if(!b)
    {
        return false;
    }
    qryref = db->SelectQuery("select name from sqlite_master where name = 'themeSettings'");
    db->clearAll();
    if(db->IsLastError())
    {
        qryref.clear();
        return false;
    }
    if(!qryref.next())
    {
        if(!db->DataBaseCommand("CREATE TABLE IF NOT EXISTS themeSettings(style varchar(50),stylesheet varchar(50))"))
        {
            qryref.clear();
            return false;
        }
        if(!db->DataBaseCommand("insert into themesettings(style,stylesheet) values ('" + getStyle() + "','Default')"))
        {
            qryref.clear();
            return false;
        }
    }
    qryref.clear();
    qryref = db->SelectQuery("select name from sqlite_master where name = 'currentWallpaper'");
    db->clearAll();
    if(db->IsLastError())
    {
        qryref.clear();
        return false;
    }
    if(!qryref.next())
    {
        b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS currentWallpaper(path varchar(300))");
        if(!b)
        {
            return false;
        }
        b = db->DataBaseCommand("insert into currentWallpaper(path) values('/root/images/main_page.jpg')");
        if(!b)
        {
            return false;
        }
    }
    qryref.clear();
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS printer_setup(Image_type varchar(10), Image blob, Image_format varchar(10))");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS dialup_settings(Connection_name varchar(50), Network varchar(50), Connection_type varchar(50), Active_status bool)");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS agps_settings(FtpPath varchar(50),Username varchar(30),Password varchar(30),Automatic bool)");
    if(!b)
    {
        return false;
    }
    b = db->DataBaseCommand("CREATE TABLE IF NOT EXISTS userAccount(UserID INTEGER PRIMARY KEY, Name TEXT,Password TEXT,Type char,IsFprint INTEGER,FingerData BLOB,FingerImage BLOB,IsNeedLogin bool)");
    if(!b)
    {
        return false;
    }
    QSqlQuery qry = db->SelectQuery("SELECT * from userAccount");
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
        return false;
    }
    if(!qry.next())
    {
        b = db->DataBaseCommand("insert into userAccount(Name,Password,Type,IsFprint,FingerData,FingerImage,IsNeedLogin) values('admin','123','A',0,NULL,NULL,0)");
        if(!b)
        {
            qry.clear();
            return false;
        }
    }
    qry.clear();
    return true;
}

bool Globalclass::GPRSEnable()
{
    if (!g_ccmainObj->isEthernet())
    {
        if(g_ccmainObj->isWifi())
        {
            return true;
        }
        else
        {
            qDebug()<<"\r Enter into gprs";
            if(!g_ccmainObj->isGprs())
            {
                qDebug()<<"\r Enter into gprs12";
                if(g_ccmainObj->enableGprs())
                {
                    qDebug()<<"\r Enter into enable";
                    return true;
                }
                else
                {
                    QMessageBox::critical(0,"GPRS Enable",g_ccmainObj->lastError());
                    return false;
                }
            }
        }
    }
    return true;
}

TreeView_custom::TreeView_custom(QWidget *parent) : QListView(parent)
{

}

void TreeView_custom::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Up || e->key()==Qt::Key_Down)
    {
        QListView::keyPressEvent(e);
        emit IndexChanged(currentIndex());
    }
    else
    {
        QListView::keyPressEvent(e);
    }
}

/*********************************File dialog class*************************************/

QString fileDialog::option;
QString fileDialog::dir;
fileDialog::fileDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    move(0,20);
}

void fileDialog::opnsavDialog()
{
    model = new QFileSystemModel(this);
    QComboBox *format = new QComboBox;
    txtFilename = new QLineEdit;
    txtFilepath = new QLineEdit;
    btnOpnSav = new QPushButton;
    btnBack = new QPushButton;
    QPushButton *btnCancel = new QPushButton;
    QLabel *lblfilepath= new QLabel("Path:");
    QLabel *lblfilename = new QLabel;
    QLabel *lblfileType = new QLabel;
    QGridLayout *grdLayout = new QGridLayout;
    QVBoxLayout *vboxMainlayout,*vboxbtnLayout;

    vboxMainlayout = new QVBoxLayout;
    vboxbtnLayout = new QVBoxLayout;
    tree = new TreeView_custom;
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    QHBoxLayout *hboxpth= new QHBoxLayout;
    lblfilepath->setFixedHeight(20);
    txtFilepath->setFixedSize(460,20);
    btnBack->setFixedSize(20,20);
    format->setFixedHeight(20);
    txtFilename->setFixedHeight(20);
    lblfilename->setFixedHeight(20);
    lblfileType->setFixedHeight(20);
    btnOpnSav->setFixedSize(90,20);
    btnCancel->setFixedSize(90,20);
    QIcon icon;
    icon.addFile(":/icons/new_back.png",QSize());
    btnBack->setIcon(icon);
    btnBack->setIconSize(QSize(20,20));
    btnOpnSav->setText(option);
    btnCancel->setText("Cancel");
    btnBack->setShortcut(Qt::ALT + Qt::Key_Up);
    lblfilename->setText("FileName:");
    lblfileType->setText("FileType:");
    tree->setModel(model);

    if(dir != "")
    {
        if(!QDir(dir).exists())
        {
            QDir().mkdir(dir);
        }
        path = QDir::currentPath() + "/" + dir;
    }
    else
        path = QDir::currentPath();

    // Demonstrating look and feel features
    connect(btnBack,SIGNAL(clicked()),this,SLOT(slotBack()));
    connect(tree,SIGNAL(IndexChanged(QModelIndex)),this,SLOT(setfileName_text(QModelIndex)));
    connect(tree,SIGNAL(activated(QModelIndex)),this,SLOT(setfileName_Focus(QModelIndex)));
    connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(setfileName(QModelIndex)));
    connect(txtFilepath, SIGNAL(returnPressed()), this, SLOT(openPath()));
    connect(txtFilename, SIGNAL(returnPressed()), this, SLOT(slotOpnSav()));
    connect(btnOpnSav,SIGNAL(clicked()),this,SLOT(slotOpnSav()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));
    model->setRootPath(path );
    tree->setRootIndex(model->index(path));

    hboxpth->addWidget(lblfilepath);
    hboxpth->addWidget(txtFilepath);
    hboxpth->addWidget(btnBack);
    grdLayout->addWidget(lblfilename,0,0);
    grdLayout->addWidget(txtFilename,0,1);
    grdLayout->addWidget(lblfileType,1,0);
    grdLayout->addWidget(format,1,1);
    vboxbtnLayout->addWidget(btnOpnSav);
    vboxbtnLayout->addWidget(btnCancel);
    hboxLayout->addLayout(grdLayout);
    hboxLayout->addLayout(vboxbtnLayout);

    vboxMainlayout->addLayout(hboxpth);
    vboxMainlayout->addWidget(tree);
    vboxMainlayout->addLayout(hboxLayout);

    setFixedSize(310,460);
    setLayout(vboxMainlayout);
    setWindowTitle("Open/Save Dialog");
    if(option == "Save")
    {
        txtFilename->setText("untitiled");
    }
    else
    {
        txtFilename->setText(model->data(tree->currentIndex(),Qt::DisplayRole).toString());
        if(filters.size() > 0)
        {
            model->setNameFilters(filters);
            txtFilename->setReadOnly(true);
            QString strfilter;
            for(int i = 0 ; i<filters.size(); i++)
            {
                strfilter = strfilter + filters.at(i) + ",";
                strfilter = strfilter.left(strfilter.size() - 1);
            }
            format->insertItem(0, strfilter);
        }
    }

    if(g_bFileCopyFlag)
    {
        path = "/";
        txtFilepath->setText(path);
        tree->setRootIndex(model->index(path));
    }
    else
    {
        txtFilepath->setText(path);
    }
    exec();
}

void fileDialog::keyPressEvent(QKeyEvent *keyevent)
{
     qDebug()<<"\r Clancor filedialog key";
    //    if(keyevent->key()==Qt::Key_Up || keyevent->key()==Qt::Key_Down)
    //    {
    //        txtFilename->setText(model->data((QModelIndex) (tree->currentIndex().row() +1 ),Qt::DisplayRole).toString());
    //        keyevent->ignore();
    //    }
    if(keyevent->key() == Qt::Key_Escape || keyevent->key() == Qt::Key_F4)
    {
        reject();
    }
}

void fileDialog::slotBack()
{

    if(g_bFileCopyFlag)
    {

    }
    else
    {
        QString tmpstr = path;
        QStringList temp = tmpstr.split(QChar('/'));
        tmpstr = tmpstr.section('/',0,temp.size()-2);
        if((temp.size()-2) == 0)
            tmpstr = "/";
        path = tmpstr;
        tree->setRootIndex(model->index(path));
        QModelIndex ind = model->index(-1, 0, QModelIndex());
        tree->selectionModel()->setCurrentIndex(ind, QItemSelectionModel::SelectCurrent);
        txtFilepath->setText(path);
    }
}

void fileDialog::setfileName(QModelIndex index)
{
    if(model->isDir(index))
    {
        openDir();
        return;
    }
    txtFilename->setText(model->data(index,Qt::DisplayRole).toString());
}

void fileDialog::openPath()
{
    path = txtFilepath->text();
    model->setRootPath(path);
    tree->setRootIndex(model->index(path));
    txtFilepath->setText(path);
}

void fileDialog::setfileName_Focus(QModelIndex index)
{
    if(model->isDir(index))
    {
        openDir();
        return;
    }
    txtFilename->setText(model->data(index,Qt::DisplayRole).toString());
    txtFilename->setFocus();
}

void fileDialog::setfileName_text(QModelIndex index)
{
    txtFilename->setText(model->data(index,Qt::DisplayRole).toString());
}

void fileDialog::openDir()
{
    if(model->data(tree->currentIndex(),Qt::DisplayRole).toString() != "")
    {
        if(path == "/")
        {
            path = path + model->data(tree->currentIndex(),Qt::DisplayRole).toString();
            tree->setRootIndex(model->index(path));
            QModelIndex ind = model->index(-1, 0, QModelIndex());
            tree->selectionModel()->setCurrentIndex(ind, QItemSelectionModel::SelectCurrent);
            txtFilepath->setText(path);
        }
        else
        {
            path = path + "/" + model->data(tree->currentIndex(),Qt::DisplayRole).toString();
            tree->setRootIndex(model->index(path));
            QModelIndex ind = model->index(-1, 0, QModelIndex());
            tree->selectionModel()->setCurrentIndex(ind, QItemSelectionModel::SelectCurrent);
            txtFilepath->setText(path);
        }
    }
}

void fileDialog::slotOpnSav()
{
    if(model->data(tree->currentIndex(),Qt::DisplayRole).toString() != "")
    {
        if(model->isDir(tree->currentIndex()))
        {
            openDir();
            return;
        }
    }

    if(option == "Save")
    {
        if(QDir(model->rootPath() + "/" + txtFilename->text()).exists())
        {
            QMessageBox msgbox;
            msgbox.setText("File already exists with the given name...");
            msgbox.setInformativeText("Do u want to replace it ?");
            msgbox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
            msgbox.setDefaultButton(QMessageBox::Yes);
            int ret = msgbox.exec();
            switch (ret)
            {
            case QMessageBox::Yes:
                accept();
                break;

            case QMessageBox::No:
                break;
            }
            return;
        }
        else
        {
            accept();
        }
    }
    else
    {
        if(txtFilename->text() != "")
        {
            QFileInfo f(path  + "/" + txtFilename->text());
            if(!f.isFile())
            {
                QMessageBox::critical(0, "File open", "select a file to open..");
                return;
            }
        }
        else
        {
            QMessageBox::critical(0, "File open", "select a file to open..");
            return;
        }
        accept();
    }
}



/*******************File Browser Class**********************/
QString filebrowser::option;
QString filebrowser::dir;
filebrowser::filebrowser(QWidget *parent)
    : QDialog(parent)
{
    setParent(MdiArea);
    setWindowFlags(Qt::FramelessWindowHint);
}

void filebrowser::opnsavDialog()
{
    model = new QFileSystemModel;
    txtFilepath = new QLineEdit;
    btnOpnSav = new QPushButton("Open");
    btnBack = new QPushButton;
    QPushButton *btnCancel = new QPushButton;
    QLabel *lblfilepath= new QLabel("Path:");
    QVBoxLayout *vboxMainlayout,*vboxbtnLayout;

    vboxMainlayout = new QVBoxLayout;
    vboxbtnLayout = new QVBoxLayout;
    tree = new QListView;
    QHBoxLayout *hboxpth = new QHBoxLayout;
    lblfilepath->setFixedHeight(20);
    txtFilepath->setFixedSize(460,20);
    btnBack->setFixedSize(20,20);
    btnOpnSav->setFixedSize(60,20);
    btnCancel->setFixedSize(60,20);
    QIcon icon;
    icon.addFile(":/icons/new_back.png",QSize());
    btnBack->setIcon(icon);
    btnBack->setIconSize(QSize(20,20));
    btnBack->setShortcut(Qt::ALT + Qt::Key_Up);
    btnBack->setAutoDefault(true);
    tree->setModel(model);

    if(dir != "")
    {
        if(!QDir(dir).exists())
        {
            QDir().mkdir(dir);
        }
        path = QDir::currentPath() + "/" + dir;
    }
    else
        path = QDir::currentPath();

    connect(btnBack,SIGNAL(clicked()),this,SLOT(slotBack()));
    connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(setfileName(QModelIndex)));
    connect(btnOpnSav,SIGNAL(clicked()),this,SLOT(slotOpnSav()));
    connect(txtFilepath, SIGNAL(returnPressed()), this, SLOT(openPath()));
    connect(tree,SIGNAL(activated(QModelIndex)),this,SLOT(setfileName(QModelIndex)));
    model->setRootPath(path );
    tree->setRootIndex(model->index(path));
    hboxpth->addWidget(lblfilepath);
    hboxpth->addWidget(txtFilepath);
    hboxpth->addWidget(btnBack);

    vboxMainlayout->addLayout(hboxpth);
    vboxMainlayout->addWidget(tree);
    vboxMainlayout->setMargin(0);

    if(option == "Save")
    {
    }
    else
    {
    }
    txtFilepath->setText(path);

    QGroupBox *g = new QGroupBox(this);
    g->setFixedSize(320,460);
    g->setFocusPolicy(Qt::NoFocus);
    g->setLayout(vboxMainlayout);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(320,460);
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet("QDialog{background-color:#B9D3EE;}");
    move(0,0);
    show();
    txtFilepath->setObjectName("txtFilePath");
    txtFilepath->setFocus();
    installEventFilter(this);
}

void filebrowser::keyPressEvent(QKeyEvent *keyevent)
{
    qDebug()<<"\r File browser"<<keyevent->key()<<"event.."<<keyevent;
    if(keyevent->key()==Qt::Key_Up || keyevent->key()==Qt::Key_Down)
    {
        qDebug()<<"\r File browser inside updown"<<keyevent->key()<<"event.."<<keyevent;
    }
    else if(keyevent->key() == Qt::Key_Escape || keyevent->key() == Qt::Key_F4)
    {
        loadForm(NEWMENU,3);
        this->close();
        delete this;
    }
    else if(keyevent->key() == Qt::Key_Backspace)
    {
        if(model->data(tree->currentIndex(),Qt::DisplayRole).toString() != "")
        {
            if(!model->isDir(tree->currentIndex()))
            {
                int res=QMessageBox::information(0,"Confirmation : Delete file","Are you sure?, Do you want to delete this file?",QMessageBox::Yes,QMessageBox::No);
                if(res==QMessageBox::Yes)
                {
                    qDebug()<<qApp->applicationFilePath();
                    if(qApp->applicationFilePath() == path + "/" + model->data(tree->currentIndex(),Qt::DisplayRole).toString())
                    {
                        QMessageBox::critical(0, "Delete File", "File cannot be deleted... Currently it is running..");
                        return;
                    }
                    if(!model->remove(tree->currentIndex()))
                    {
                        QMessageBox::critical(0, "Delete File", "Unable to Delete file...!" + model->data(tree->currentIndex(),Qt::DisplayRole).toString());
                    }
                }
            }
        }
    }
    else
    {
        keyevent->ignore();
    }
}

void filebrowser::slotBack()
{

    QString tmpstr = path;//model->data(tree->currentIndex(),Qt::DisplayRole).toString();
    QStringList temp = tmpstr.split(QChar('/'));
    tmpstr = tmpstr.section('/',0,temp.size()-2);
    if((temp.size()-2) == 0)
        tmpstr = "/";
    path = tmpstr;
    tree->setRootIndex(model->index(path));
    txtFilepath->setText(path);
}

void filebrowser::openPath()
{
    path = txtFilepath->text();
    model->setRootPath(path);
    tree->setRootIndex(model->index(path));
    txtFilepath->setText(path);
}

void filebrowser::setfileName(QModelIndex index)
{
    if(model->isDir(index))
    {
        openDir();
        return;
    }
    slotOpnSav();
}

void filebrowser::openDir()
{
    if(model->data(tree->currentIndex(),Qt::DisplayRole).toString() != "")
    {
        if(path == "/")
        {
            path = path + model->data(tree->currentIndex(),Qt::DisplayRole).toString();
            tree->setRootIndex(model->index(path));
            txtFilepath->setText(path);
        }
        else
        {
            path = path + "/" + model->data(tree->currentIndex(),Qt::DisplayRole).toString();
            tree->setRootIndex(model->index(path));
            txtFilepath->setText(path);
        }
    }
}

void filebrowser::slotOpnSav()
{
    if(model->isDir(tree->currentIndex()))
    {
        openDir();
        return;
    }

    QStringList filters;
    filters << "png" << "xpm" << "jpg" << "jpeg" << "gif" << "bmp";

    int filetype_cnt;
    for(filetype_cnt=0; filetype_cnt < filters.size() ; filetype_cnt++)
    {
        if(model->fileInfo(tree->currentIndex()).completeSuffix() == filters.at(filetype_cnt))
        {
            imageViewerSlot();
            return;
            break;
        }
    }
    setVisible(false);
    Notepad *n = new Notepad(MdiArea);
    n->openfile(path + "/" + model->data(tree->currentIndex(),Qt::DisplayRole).toString());
    n->exec();
    delete n;
    setVisible(true);
    setEnabled(true);
    tree->setFocus();
    return;
}

void filebrowser::imageViewerSlot()
{
    setVisible(false);
    Browser *w = new Browser;

    w->setFixedSize(320,460);
    w->setWindowModality(Qt::ApplicationModal);
    int ww = w->width();
    int wh = w->height();
    int dim = (ww > wh) ? wh : ww;
    dim = dim * 3 / 4;
    w->setSlideSize(QSize(3*dim/5, dim));

    QStringList files, filters;
    QDir dir = path;

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    filters << "*.png" << "*.xpm" << "*.jpg" << "*.jpeg" << "*.gif" << "*.bmp";
    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Unsorted);
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        files.append(dir.absoluteFilePath(fileInfo.fileName()));
    }

    QImage img;
    for(int i = 0; i < (int)files.count(); i++)
        if(img.load(files[i]))
            w->addSlide(img);

    w->setCenterIndex(w->slideCount()/2);
    w->setBackgroundColor(Qt::white);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->move(QPoint(0,20));
    w->show();
}


Notepad::Notepad(QWidget *parent)
    : QDialog(parent)
{
    edit=new QTextEdit(this);
    menubar=new QMenu(this);
    menubar1=new QMenu(this);
    menubar2=new QMenu(this);
    menubar3=new QMenu(this);
    bar= new QMenuBar(this);

    bar->setMinimumWidth(2);
    lay=new QVBoxLayout(this);
    status=new QStatusBar(this);
    newfile1=new QAction(("&New"),this);
    connect(newfile1,SIGNAL(triggered()),this,SLOT(newfile()));
    open=new QAction(("&Open"),this);
    connect(open,SIGNAL(triggered()),this,SLOT(loadme()));
    save=new QAction(("&Save"),this);
    connect(save,SIGNAL(triggered()),this,SLOT(saveme()));
    saveAs=new QAction(("SaveAs"),this);
    connect(saveAs,SIGNAL(triggered()),this,SLOT(closeNotepad()));
    exi=new QAction(("&Exit"),this);
    connect(exi,SIGNAL(triggered()),this,SLOT(close()));
    un=new QAction(("&Undo"),this);
    connect(un,SIGNAL(triggered()),this,SLOT(undome()));
    re=new QAction(("&redo"),this);
    connect(re,SIGNAL(triggered()),this,SLOT(redome()));
    cutme=new QAction(("&Cut"),this);
    connect(cutme,SIGNAL(triggered()),this,SLOT(Cut()));
    copyme=new QAction(("&Copy"),this);
    connect(copyme,SIGNAL(triggered()),this,SLOT(Copy()));
    pasteme=new QAction(("&Paste"),this);
    connect(pasteme,SIGNAL(triggered()),this,SLOT(Paste()));
    mystatus=new QAction(("&Status Bar"),this);
    mystatus->setCheckable(1);
    mystatus->setChecked(true);
    connect(mystatus,SIGNAL(toggled(bool)),status,SLOT(setVisible(bool)));
    about=new QAction(("About App"),this);
    connect(about,SIGNAL(triggered()),this,SLOT(aboutme()));
    menubar=bar->addMenu(tr("&File"));

    menubar1=bar->addMenu(tr("&Edit"));//Adding new menu to menubar

    menubar2=bar->addMenu(tr("&View"));

    menubar3=bar->addMenu(tr("&About"));

    menubar->addAction(newfile1);
    menubar->addSeparator();
    menubar->addAction(open);
    menubar->addSeparator();//Adding separator between to menu items
    menubar->addAction(save);
    menubar->addAction(saveAs);
    menubar->addSeparator();
    menubar->addAction(exi);

    menubar1->addAction(un);
    menubar1->addAction(re);
    menubar1->addSeparator();
    menubar1->addAction(cutme);//Merging Action in menubar
    menubar1->addSeparator();
    menubar1->addAction(copyme);
    menubar1->addSeparator();
    menubar1->addAction(pasteme);

    menubar2->addAction(mystatus);

    menubar3->addAction(about);
    lay->addWidget(bar);

    lay->addWidget(edit);
    lay->addWidget(status);
    setLayout(lay);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("QDialog{background-color:#D6D6D6;}");
    setFixedSize(320, 460);
    installEventFilter(this);
    edit->setFocus();
}

bool Notepad::eventFilter(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if(e->key()==Qt::Key_Escape)
        {
            closeNotepad();
            return true;
        }
    }
    return false;
}

void Notepad::openfile(QString filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        edit->setPlainText(QString::fromUtf8(file.readAll()));
        mFilePath = filepath;
        status->showMessage(tr("File successfully loaded."), 3000);
    }
}

void Notepad::loadme()
{
    QString filename;

    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        filename = f->model->rootPath() +"/" + f->txtFilename->text() ;
    }
    delete f;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        edit->setPlainText(QString::fromUtf8(file.readAll()));
        mFilePath = filename;
        status->showMessage(tr("File successfully loaded."), 3000);
    }
}

bool Notepad::saveme()
{
    if(mFilePath.isEmpty())
    {
        if(!saveFileAs())
            return false;
    }
    else
    {
        if(saveFile(mFilePath))
            return false;
    }
    return true;
}

bool Notepad::saveFile(const QString &name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        if(edit->toPlainText().size() != file.write(edit->toPlainText().toUtf8()))
            return false;
    }
    else
    {
        QMessageBox::critical(0, "Save Error", "Error while saving file");
        return false;
    }
    status->showMessage(tr("File successfully Saved."), 3000);
    return true;
}

bool Notepad::saveFileAs()
{
    fileDialog *f = new fileDialog();
    f->option = "Save";
    f->dir = "Text_files";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        mFilePath = f->model->rootPath() +"/" + f->txtFilename->text() ;
    }
    else
    {
        delete f;
        return false;
    }
    delete f;
    if(mFilePath.isEmpty())
        return false;
    if(saveFile(mFilePath))
    {
        status->showMessage(tr("File Saved"), 3000);
    }
    else
    {
        return false;
    }
    return true;
}

bool Notepad::mayDiscardDocument()
{
    if (edit->document()->isModified())
    {
        QString filename = mFilePath;
        if (filename.isEmpty()) filename = tr("Unnamed");
        if (QMessageBox::question(this, tr("Save Document?"),tr("You want to create a new document, but the ""changes in the current document ’%1’ have not ""been saved. How do you want to proceed?"),tr("Save Document"), tr("Cancel")))
        {
            return false;
        }
        else
        {
            saveme();
        }
    }
    return true;
}

void Notepad::newfile()
{
    if (!mayDiscardDocument()) return;
    edit->setPlainText("");
    mFilePath = "";
    status->showMessage(tr("New File created"),3000);
}

void Notepad::undome()
{
    edit->document()->undo();
}

void Notepad::redome()
{
    edit->document()->redo();
}

void Notepad::Cut()
{
    edit->cut();
    status->showMessage(tr("Text Cut"),3000);
}

void Notepad::Copy()
{
    edit->copy();
    status->showMessage(tr("Text Copied"),3000);
}

void Notepad::Paste()
{
    edit->paste();
    status->showMessage(tr("Text pasted"),3000);
}

void Notepad::aboutme()
{
    QMessageBox::about(this, tr("About Notepad"), "Notepad 1.0\n A Qt application\n");
}

void Notepad::closeNotepad()
{
    if(edit->toPlainText().length()>0)
    {
        int res = QMessageBox::information(this, tr("Save As"), "Do you want to save changes..?", QMessageBox::Yes, QMessageBox::No);
        if(res == QMessageBox::Yes)
        {
            if(saveme())
                close();
            else
                return;
        }
    }
    close();
}
