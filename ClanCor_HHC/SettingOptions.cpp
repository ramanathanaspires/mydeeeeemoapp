#include "SettingOptions.h"

ThemeOption::ThemeOption(QWidget *parent) : QDialog(parent)
{
    comboStyle= new QComboBox;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QVBoxLayout *VLayout = new QVBoxLayout;
    QHBoxLayout *HLayout = new QHBoxLayout;

    buttonBox->button(QDialogButtonBox::Ok)->setText("Ok");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
    buttonBox->button(QDialogButtonBox::Ok)->setShortcut(Qt::Key_F2);
    buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(Qt::Key_F4);

    comboStyle->addItems(QStyleFactory::keys());
    connect(comboStyle,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_styleCombo_activated(QString)));

    HLayout->addWidget(comboStyle);
    VLayout->addLayout(HLayout);
    VLayout->addWidget(buttonBox);

    QSqlQuery *qry = new QSqlQuery;
    *qry = db->SelectQuery("select name from sqlite_master where name = 'themeSettings'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry->clear();
        return;
    }
    if(!qry->next())
    {
        if(db->DataBaseCommand("CREATE TABLE IF NOT EXISTS themeSettings(style varchar(50),stylesheet varchar(50))"))
        {
            qry->clear();
            delete qry;
            return;
        }
        if(db->DataBaseCommand("insert into themesettings(style,stylesheet) values ('" + getStyle() + "','Default')"))
        {
            qry->clear();
            delete qry;
            return;
        }
    }
    qry->clear();
    *qry = db->SelectQuery("select * from themeSettings");
    if(qry->next())
    {
        oldStyle = qry->value(0).toString();
        oldStylesheet = qry->value(1).toString();
        comboStyle->setCurrentIndex(comboStyle->findText(qry->value(0).toString(), Qt::MatchContains));

    }
    qry->clear();
    setLayout(VLayout);
    setWindowModality(Qt::ApplicationModal);

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    comboStyle->setFocus();
}


void ThemeOption::on_styleCombo_activated(const QString &styleName)
{
    setEnabled(false);
    style = styleName;
    qApp->setStyle(styleName);
    setEnabled(true);
    comboStyle->setFocus();
}

void ThemeOption::on_styleSheetCombo_activated(const QString &sheetName)
{
    stylesheet = sheetName;
    loadStyleSheet(sheetName);
}


/****************************Class to create Wallpaper setting window **************************/


WallpaperWnd::WallpaperWnd(QWidget *parent)
    : QDialog(parent)
{
    setParent(MdiArea,Qt::Dialog);
    setFocusPolicy(Qt::NoFocus);
}

bool WallpaperWnd::show_WallpaperWnd()
{
    QFrame *frmlbl = new QFrame;
    lblImage = new QLabel(frmlbl);
    btnOk = new QPushButton;
    btnCancel = new QPushButton;
    btnBrowse = new QPushButton;
    lstWPitems = new QListWidget;

    lblImage->setFixedSize(155,95);
    lblImage->setGeometry(8,5,155,95);
    lblImage->setStyleSheet("background-color:black;color:white;font:bold;");

    frmlbl->setFixedSize(155,95);
    frmlbl->setFrameShape(QFrame::Panel);
    frmlbl->setFrameShadow(QFrame::Raised);
    frmlbl->setContentsMargins(3,3,3,3);
    frmlbl->setFocusPolicy(Qt::NoFocus);

    lstWPitems->setFixedSize(190,75);

    btnOk->setFixedSize(90,20);
    btnCancel->setFixedSize(90,20);
    btnBrowse->setFixedSize(80,50);
    btnOk->setText("Ok");
    btnCancel->setText("Cancel");
    btnOk->setShortcut(Qt::Key_F2);
    btnCancel->setShortcut(Qt::Key_F4);
    btnBrowse->setText("Browse");

    QVBoxLayout *vbxMain = new QVBoxLayout;
    QHBoxLayout *hbxListItems = new QHBoxLayout;
    QHBoxLayout *hbxButtonbox = new QHBoxLayout;
    QWidget *wgtMain = new QWidget(this);

    hbxButtonbox->setMargin(0);
    hbxListItems->setMargin(0);
    vbxMain->setMargin(0);
    vbxMain->setSpacing(0);
    hbxButtonbox->addWidget(btnOk);
    hbxButtonbox->addWidget(btnCancel);
    hbxListItems->addSpacing(15);
    hbxListItems->addWidget(lstWPitems,0,Qt::AlignHCenter);
    hbxListItems->addWidget(btnBrowse,0, Qt::AlignHCenter);
    vbxMain->addSpacing(0);
    vbxMain->addWidget(frmlbl,0,Qt::AlignHCenter);
    vbxMain->addLayout(hbxListItems);
    vbxMain->addLayout(hbxButtonbox);
    wgtMain->setFixedSize(318,225);
    wgtMain->setLayout(vbxMain);

    setFixedSize(320,460);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setStyleSheet("QDialog{background-color:#F5F5F5;}");

    connect(btnOk, SIGNAL(clicked()), this, SLOT(setWallpaperSlot()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnBrowse, SIGNAL(clicked()), this, SLOT(browseSlot()));
    connect(lstWPitems, SIGNAL(clicked(QModelIndex)), this, SLOT(setWallpaper(QModelIndex)));
    connect(lstWPitems, SIGNAL(currentRowChanged(int)), this, SLOT(selection_changed(int)));

    /*------------load files from location "<current path>/images"-----------------*/
    btnOk->setEnabled(false);
    QStringList filters;
    QDir dir = QDir::currentPath() + "/images";

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    filters << "*.png" << "*.xpm" << "*.jpg" << "*.jpeg" << "*.gif";
    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Unsorted);
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        lstWPitems->addItem(fileInfo.fileName());
        files.append(dir.absoluteFilePath(fileInfo.fileName()));
    }
    QSqlQuery qry = db->SelectQuery("select * from currentWallpaper");
    db->clearAll();
    if(db->IsLastError())
    {
        qry.clear();
        return false;
    }
    if(qry.next())
    {
        currentpath = qry.value(0).toString();
        bool exists = files.contains(currentpath,Qt::CaseInsensitive);
        if(!exists)
        {
            QStringList temp = currentpath.split(QChar('/'));
            if(dir.exists(currentpath))
            {
                lstWPitems->addItem(currentpath.section('/',temp.size()-1,temp.size()));
                files.append(currentpath);
            }
            else
            {
                lblImage->setText("No Image");
                lblImage->setAlignment(Qt::AlignCenter);
            }
            if(files.size()>0)
                lstWPitems->setCurrentRow(files.size()-1);
            qry.clear();
            show();
            lstWPitems->setFocus();
            return true;
        }

        int nLoopCount;
        for(nLoopCount = 0; nLoopCount < files.size(); nLoopCount++)
        {
            if(files.at(nLoopCount)==currentpath)
                break;
        }
        lstWPitems->setCurrentRow(nLoopCount);
        lstWPitems->setFocus();
    }
    qry.clear();

    return true;
}

void WallpaperWnd::setWallpaperSlot()
{
    bool b = db->DataBaseCommand("delete from currentWallpaper");
    if(!b)
    {
        return;
    }
    b = db->DataBaseCommand("insert into currentWallpaper(path) values('" + currentpath + "')");
    if(!b)
    {
        return;
    }
    QMessageBox::information(0,"Wallpaper Settings","Wallpaper applied successfully..");
    this->reject();
}

void WallpaperWnd::exitWndSlot()
{
    loadForm(SETTINGMENU, 5);
    this->close();
    delete this;
}

void WallpaperWnd::browseSlot()
{
    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->dir = "images";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        currentpath = f->path +"/" + f->txtFilename->text();
        if(!files.contains(currentpath, Qt::CaseInsensitive))
        {
            lstWPitems->addItem(f->txtFilename->text());
            files.append(currentpath);
        }


        QPixmap *p = new QPixmap;
        p->load(currentpath);
        lblImage->clear();
        lblImage->setPixmap(p->scaled(155,95,Qt::IgnoreAspectRatio,Qt::FastTransformation));
        update();
        lstWPitems->setCurrentRow(files.indexOf(currentpath));
        if(!btnOk->isEnabled())
            btnOk->setEnabled(true);
        lstWPitems->setFocus();
    }
    else
        btnBrowse->setFocus();
}

void WallpaperWnd::setWallpaper(QModelIndex index)
{
    selection_changed(index.row());
}

void WallpaperWnd::selection_changed(int row)
{
    if(currentpath != files.at(row))
        if(!btnOk->isEnabled())
            btnOk->setEnabled(true);
    currentpath = files.at(row);
    lblImage->clear();
    QPixmap *p = new QPixmap;
    p->load(currentpath);
    lblImage->setPixmap(p->scaled(155,95,Qt::IgnoreAspectRatio,Qt::FastTransformation));
    update();
}

void WallpaperWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        reject();
    }
}
