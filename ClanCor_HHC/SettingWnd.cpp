#include "SettingWnd.h"
#include "GlobalClass.h"
#include "newmenu.h"
#include "imageviewer.h"
#include "PrinterSetup.h"
//#include "dialup_conf.h"
#include "wifi_conf.h"
#include "useraccountwidget.h"
#include "gpssettings.h"
#include "pic32widget.h"
#include "SettingOptions.h"
#include "gadgets.h"
#include "patchupdates.h"
#include <unistd.h>
#include<csettingsfiles.h>
using namespace Globalclass;

// Default settings 9 items
const QString const_stringKeyLock_PwrSave = "KeyLock\nPowerSave";
const QString const_StringUsbgadgets = "UsbGadgets";
const QString const_stringTheme = "Themes";
const QString const_stringWallpaper = "Wallpaper";
const QString const_stringDateTime = "DateTime";
const QString const_stringAppLauncher = "App\nLauncher";
const QString const_stringPrinterSetup = "Printer";
const QString const_stringDropBear = "Restart\nSSH";
const QString const_stringFileipdates = "File\n Updates";

// Based on Configuration settings
const QString const_stringWifiSetting = "WIFI";
const QString const_stringEthernet = "Ethernet";
const QString const_stringGPRS = "GPRS";
const QString const_stringAgpsSetting = "AGPS";
const QString const_stringVolume = "Volume";
const QString const_stringTouchCalibrate = "Touch\nCalibration";
//const QString const_stringUserAccount = "Users";
//const QString const_stringDialupSetting = "Dial-up";
//const QString const_stringCoUpTest = "Co-up\nTest";        //Only to test Co-up
//const QString const_stringCoProcessorProg = "Co-up\nProgram";

SettingWnd::SettingWnd(QWidget *parent)
    : QMdiSubWindow(parent)
{
    listviewMenu = new QListWidget;
    scrollArea=new QScrollArea(this);

    i=0;
    j=0;
    int nDisplaySettings=9;

    //    bool bIsModel80 = !g_ccmainObj->deviceModel().contains("HHC-7");

    listviewMenu->setViewMode(QListWidget::IconMode);
    listviewMenu->setSpacing(13);
    listviewMenu->setUniformItemSizes(true);
    listviewMenu->setIconSize(QSize(35, 35));
    listviewMenu->setWordWrap(true);
    listviewMenu->setEditTriggers(QListWidget::NoEditTriggers);
    listviewMenu->setAutoScroll(false);
    listviewMenu->setDragDropMode(QListWidget::NoDragDrop);
    listviewMenu->setFixedSize(300, 460);

    CSettingsFiles setting("ClanCor","config.xml");
    setting.beginSettingsGroup("SDKConfiguration");

    E_GadgetMode Gadeget;
    E_MassStorage MassStorage;
    g_ccmainObj->serverMethod()->GadgetConfiguration(Gadeget,MassStorage);
    if(g_ccmainObj->serverMethod()->getUSBON_OFF() && Gadeget == 3 )
    {
        nDisplaySettings++;
        loadIcon(const_stringEthernet, ":/icons/lan.png");
        loadIcon(const_stringWifiSetting, ":/icons/wifi_icon.png");
    }
    gstrXMLConfig= setting.value("GPRS");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaySettings++;
        loadIcon(const_stringGPRS, ":/icons/gprs.png");
    }
    loadIcon(const_stringAppLauncher, ":/icons/app_settings.png");
    loadIcon(const_StringUsbgadgets,":/icons/usb.png");
    loadIcon(const_stringDateTime, ":/icons/datetime.png");
    loadIcon(const_stringKeyLock_PwrSave, ":/icons/keypad_power.png");
    loadIcon(const_stringTheme, ":/icons/themes.png");
    loadIcon(const_stringWallpaper, ":/icons/wallpaper.png");

    gstrXMLConfig= setting.value("Audio");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaySettings++;
        loadIcon(const_stringVolume, ":/icons/volume.png");
    }

    gstrXMLConfig= setting.value("Touch_Panel");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaySettings++;
        loadIcon(const_stringTouchCalibrate, ":/icons/calibrate.png");
    }

//    loadIcon(const_stringCoProcessorProg, ":/icons/prog_processor.png");

//    loadIcon(const_stringPrinterSetup, ":/icons/printer_setting.png");

//    loadIcon(const_stringUserAccount, ":/icons/user.png");
//    loadIcon(const_stringDialupSetting, ":/icons/dialup.jpg");

    gstrXMLConfig= setting.value("GPS");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaySettings++;
        loadIcon(const_stringAgpsSetting, ":/icons/GPS.png");
    }
    loadIcon(const_stringDropBear, ":/icons/dropBear.png");
    loadIcon(const_stringFileipdates,":/icons/ftp2.png");
    //    if(nDisplaySettings <= 9)
    //    {
    //        listviewMenu->setFixedSize(300, 270);
    //    }
    //    else if(nDisplaySettings > 9 && nDisplaySettings<=11)
    //    {
    //        listviewMenu->setFixedSize(300, 340);
    //    }
    //    else
    //    {
    //        listviewMenu->setFixedSize(300, 425);
    //    }
    connect(listviewMenu,SIGNAL(clicked(QModelIndex)), this, SLOT(slot_ItemCliked(QModelIndex)));
    connect(listviewMenu,SIGNAL(activated(QModelIndex)), this, SLOT(slot_ItemCliked(QModelIndex)));
    connect(listviewMenu,SIGNAL(itemSelectionChanged()), this, SLOT(slot_SetItemVisible()));

    scrollArea->setWidget(listviewMenu);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setFixedSize(320,460);
    scrollArea->setFocusPolicy(Qt::NoFocus);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setFocusPolicy(Qt::NoFocus);
    setFixedSize(320,460);
    setStyleSheet("background-color:black;color:white;selection-color: white;");//selection-background-color: gray;");
    listviewMenu->setStyleSheet("QListView{border: 0px}QListView::item:focus{border: 1px solid #6a6ea9;}"
                                "QListView {font-size:11px;font-style:bold;}"
                                "QListView::item:selected:!active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #ABAFE5, stop: 1 #8588B2);}"
                                "QListWidget::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #6a6ea9, stop: 1 #888dd9);}");
    setWindowTitle("setting menu window");
    listviewMenu->setFocusPolicy(Qt::StrongFocus);
    listviewMenu->setCurrentIndex(listviewMenu->model()->index(0,0));
    listviewMenu->setFocus();
}

void SettingWnd::loadIcon(QString stringCaption, QString stringFileName)
{
    QIcon icon;
    icon.addFile(stringFileName,QSize());

    QListWidgetItem *listwidgetitemMenu = new QListWidgetItem(icon, stringCaption);

    listwidgetitemMenu->setSizeHint(QSize(75, 70));
    listviewMenu->addItem(listwidgetitemMenu);
}

void SettingWnd::slot_SetItemVisible()
{
    scrollArea->ensureVisible(listviewMenu->visualRect(listviewMenu->currentIndex()).center().x(),
                              listviewMenu->visualRect(listviewMenu->currentIndex()).center().y());
}

void SettingWnd::slot_ItemCliked(QModelIndex modelindexSelected)
{
    QString stringCurrentItemText = listviewMenu->currentItem()->text();
    triggerItem(stringCurrentItemText);
}

void SettingWnd::slot_ItemEntered(QListWidgetItem *listwidgetitemSelected)
{
    QString stringCurrentItemText = listwidgetitemSelected->text();
    triggerItem(stringCurrentItemText);
}

void SettingWnd::triggerItem(QString stringItemSelected)
{
    if(const_stringEthernet == stringItemSelected)
    {
        slot_Ethernet();
    }
    else if(const_stringGPRS == stringItemSelected)
    {
        slot_GPRS();
    }
    else if(const_stringKeyLock_PwrSave == stringItemSelected)
    {
        slot_KeyLock_PwrSave();
    }
    else if(const_StringUsbgadgets == stringItemSelected)
    {
        slot_Usbgadget();
    }
    else if(const_stringTheme == stringItemSelected)
    {
        slot_Theme();
    }
    else if(const_stringVolume == stringItemSelected)
    {
        slot_VolumeControl();
    }
    else if(const_stringWallpaper == stringItemSelected)
    {
        slot_Wallpaper();
    }
    else if(const_stringDateTime == stringItemSelected)
    {
        slot_DateTime();
    }
    else if(const_stringAppLauncher == stringItemSelected)
    {
        slot_AppLauncher();
    }
    else if(const_stringTouchCalibrate == stringItemSelected)
    {
        slot_TouchCalibrate();
    }
    //    else if(const_stringCoProcessorProg == stringItemSelected)
    //    {
    //        slot_CoProcessorProg();
    //    }
    else if(const_stringPrinterSetup == stringItemSelected)
    {
        slot_PrinterSetup();
    }
    //    else if(const_stringUserAccount == stringItemSelected)
    //    {
    //        slot_UserAccount();
    //    }
    //    else if(const_stringDialupSetting == stringItemSelected)
    //    {
    ////        slot_DialupSetting();
    //    }
    else if(const_stringWifiSetting == stringItemSelected)
    {
        slot_WifiSetting();
    }
    else if(const_stringAgpsSetting == stringItemSelected)
    {
        slot_AgpsSetting();
    }
    else if(const_stringDropBear == stringItemSelected)
    {
        slot_ssh();
    }
    //    else if(const_stringCoUpTest == stringItemSelected)
    //    {
    //        slot_CoUpTest();
    //    }
    else if(const_stringFileipdates == stringItemSelected)
    {
        slot_fileUpdate_Ftp();
    }
}

void SettingWnd::setFocusOnLastItem()
{
    listviewMenu->setCurrentItem(listviewMenu->currentItem());
    listviewMenu->setFocus();
}

void SettingWnd::setMenuHidden(bool bHide)
{
    if(bHide)
    {
        setEnabled(false);
        qApp->processEvents();
        setVisible(false);
    }
    else
    {
        setMenuShown(true);
    }
}

void SettingWnd::setMenuShown(bool bShow)
{
    if(bShow)
    {
        setVisible(true);
        setEnabled(true);
        setFocusOnLastItem();
    }
    else
    {
        setMenuHidden(true);
    }
}

void SettingWnd::slot_Ethernet()
{    

    setMenuHidden(true);
    g_ccmainObj->setKeypadMode(ClanCor::eKeypadMode_NUMERIC);
    EthernetWnd *eth = new EthernetWnd(this);
    eth->showEthernet();

    QEventLoop e;
    connect(eth, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void SettingWnd::slot_GPRS()
{
    setMenuHidden(true);
    GPRSWnd *gprs = new GPRSWnd(this);
    gprs->showGPRS();

    QEventLoop e;
    connect(gprs, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void SettingWnd::slot_KeyLock_PwrSave()
{
    setMenuHidden(true);
    PowerOptions *objBacklight = new PowerOptions(this);
    objBacklight->show();

    QEventLoop e;
    connect(objBacklight, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void SettingWnd::slot_Usbgadget()
{
    setMenuHidden(true);
    GADGETS *objgadget = new GADGETS(this);
    objgadget->show();

    QEventLoop e;
    connect(objgadget, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void SettingWnd::slot_Theme()
{
    setDisable(this);
    ThemeOption *theme = new ThemeOption;
    theme->exec();
    if (theme->result() == QDialog::Accepted)
    {
        QSqlQuery *qry = new QSqlQuery;
        *qry = db->SelectQuery("select * from themeSettings");
        db->clearAll();
        if(db->IsLastError())
        {
            qry->clear();
            return;
        }
        if(!qry->next())
        {
            qry->clear();
            db->DataBaseCommand("insert into themeSettings(style,stylesheet) values ('" + theme->style + "','" + theme->stylesheet + "')");
        }
        else
        {
            qry->clear();
            db->DataBaseCommand("delete from themeSettings");
            db->DataBaseCommand("insert into themeSettings(style,stylesheet) values ('" + theme->style + "','" + theme->stylesheet + "')");
        }
    }
    else
    {
        theme->on_styleCombo_activated(theme->oldStyle);
        theme->on_styleSheetCombo_activated(theme->oldStylesheet);
    }
    delete theme;

    setEnabled(true);
    setFocusOnLastItem();
}

void SettingWnd::slot_VolumeControl()
{
    setDisable(this);
    g_ccmainObj->serverMethod()->volumeControlDialog();
    setEnabled(true);
    setFocusOnLastItem();
}

void SettingWnd::slot_Wallpaper()
{
    setMenuHidden(true);

    WallpaperWnd *wnd = new WallpaperWnd;
    if(wnd->show_WallpaperWnd())
        wnd->exec();
    delete wnd;

    setMenuShown(true);
}

void SettingWnd::slot_DateTime()
{
    setMenuHidden(true);

    DateTimeSetting *DateTimeSet = new DateTimeSetting;
    DateTimeSet->exec();
    if (DateTimeSet->result() == QDialog::Accepted){
        QString date = DateTimeSet->calender->selectedDate().toString("yyyy-MM-dd");
        date = date + " " + DateTimeSet->spinHour->text().rightJustified(2,'0') + ":" + DateTimeSet->spinMin->text().rightJustified(2,'0') + ":" + DateTimeSet->spinSec->text().rightJustified(2,'0');
        QDateTime Dt;
        Dt=QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
        if(!g_ccmainObj->setDateTime(Dt))
        {
            QMessageBox::critical(0,"Date Time Setting", "Failed to set date & time");
        }

        DateTimeSet->close();
    }
    else
    {
        DateTimeSet->close();
    }
    delete DateTimeSet;

    setMenuShown(true);
}


void SettingWnd::slot_AppLauncher()
{
    setMenuHidden(true);

    ApplicationLaunchWnd *objApp = new ApplicationLaunchWnd(this);
    objApp->show();

    QEventLoop e;
    connect(objApp, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void SettingWnd::slot_TouchCalibrate()
{
    setMenuHidden(true);

    g_ccmainObj->serverMethod()->touchCalibrateDialog();

    setMenuShown(true);
}

void SettingWnd::slot_CoProcessorProg()
{
    setDisable(this);

    g_ccmainObj->serverMethod()->programCoProcessor("/mnt/Programfile.hex");

    setEnabled(true);
    setFocusOnLastItem();
}

void SettingWnd::slot_PrinterSetup()
{
    setMenuHidden(true);

    PrinterSetup *prinobj = new PrinterSetup;
    prinobj->exec();

    setMenuShown(true);
}

void SettingWnd::slot_UserAccount()
{
    setMenuHidden(true);

    UserAccountWidget *wnd = new UserAccountWidget(this);
    wnd->setWindowFlags(Qt::FramelessWindowHint);
    wnd->show();
    wnd->stateStart();

    QEventLoop e;
    connect(wnd, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

//void SettingWnd::slot_DialupSetting()
//{
////    setMenuHidden(true);

////    dialup_conf *dialupobj = new dialup_conf;
////    dialupobj->show();

////    QEventLoop e;
////    connect(dialupobj, SIGNAL(finished(int)), &e, SLOT(quit()));
////    e.exec();

////    setMenuShown(true);
//}

void SettingWnd::slot_WifiSetting()
{
    setMenuHidden(true);

    WIFI_Conf *w = new WIFI_Conf;
    w->show();
    QEventLoop e;
    connect(w, SIGNAL(rejected()), &e, SLOT(quit()));
    e.exec();
    delete w;

    setMenuShown(true);
}

void SettingWnd::slot_AgpsSetting()
{
    setMenuHidden(true);

    GpsSettings *Agpsobj = new GpsSettings;
    Agpsobj->show();

    QEventLoop e;
    connect(Agpsobj, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}
void SettingWnd::slot_fileUpdate_Ftp()
{
    setMenuHidden(true);
    Patchupdates *fileupdates = new Patchupdates(MdiArea);
    fileupdates->show();

    QEventLoop e;
    connect(fileupdates, SIGNAL(finished(int)), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
    setFocusOnLastItem();
}

void SettingWnd::slot_ssh()
{
    setEnabled(false);
    QLabel *lblProcessing = new QLabel("Please wait...");
    lblProcessing->setStyleSheet("border-width: 4px;border-color:#174763; border-style: solid;background-color:#c1d7ee;color:black");
    lblProcessing->setFont(QFont("sans serif",14,1,false));
    lblProcessing->setAlignment(Qt::AlignCenter);
    lblProcessing->setWordWrap(true);
    lblProcessing->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    lblProcessing->setWindowModality(Qt::ApplicationModal);
    lblProcessing->setGeometry(30,60,260,120);
    lblProcessing->setFocusPolicy(Qt::NoFocus);
    lblProcessing->show();
    UpdateScreen();
    QProcess process;
    QString strOutput;
    process.start("/etc/init.d/S50sshd stop");
    strOutput.clear();
    while(process.state() == QProcess::Running || process.state() == QProcess::Starting)
    {
        if(process.waitForFinished(1000))
        {
            strOutput.append(process.readAllStandardError());
        }
    }

    if(system(QString("rm /etc/ssh*key").toLatin1()))
    {
        QMessageBox::critical(0,"Restart SSH","Restart Failed-E01");
        lblProcessing->close();
        setEnabled(true);
        return;
    }
    if(system(QString("rm /etc/ssh*pub").toLatin1()))
    {
        QMessageBox::critical(0,"Restart SSH","Restart Failed-E02");
        lblProcessing->close();
        setEnabled(true);
        return;
    }
    process.start("/etc/init.d/S50sshd start");
    strOutput.clear();
    while(process.state() == QProcess::Running || process.state() == QProcess::Starting)
    {
        if(process.waitForFinished(1000))
        {
            strOutput.append(process.readAllStandardError());
        }
    }

    lblProcessing->close();
    if( strOutput != "")
    {
        QMessageBox::about(0,"Restart SSH",strOutput);
    }
    else
    {
        QMessageBox::about(0,"Restart SSH","Dropbear sshd: Restarted successfully!");
    }
    process.close();
    delete lblProcessing;
    setEnabled(true);
    setMenuShown(true);
}

void SettingWnd::slot_CoUpTest()
{
    setMenuHidden(true);

    Pic32Widget *pic32obj = new Pic32Widget;
    pic32obj->exec();

    setMenuShown(true);
}

void SettingWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        loadForm(NEWMENU, 2);
        this->close();
        delete this;
    }
}

GroupBoxCustom::GroupBoxCustom(QWidget *parent)
    : QGroupBox(parent)
{
}

GroupBoxCustom::GroupBoxCustom(const QString title, QWidget* parent)
    : QGroupBox(parent)
{
    this->setTitle(title);
}

void GroupBoxCustom::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        if(this->isCheckable())
        {
            if(this->isChecked())
            {
                this->setChecked(false);
                emit toggled(false);
            }
            else
            {
                this->setChecked(true);
                emit toggled(true);
            }
        }
    }
    else
    {
        QGroupBox::keyPressEvent(event);
    }
}

EthernetWnd::EthernetWnd(QWidget *parent): QDialog(parent)
{
    setParent(MdiArea);
}

void EthernetWnd::showEthernet()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    QScrollArea *scrollarea = new QScrollArea(this);
    QGroupBox *grpbxNetConf = new QGroupBox("Network Properties(Ethernet)");
    QLabel *lblIPaddr = new QLabel("IP address:");
    QLabel *lblSubnet = new QLabel("Subnet mask:");
    QLabel *lblGateway = new QLabel("Gateway address:");
    txtIPaddr = new QLineEdit;
    txtSubnet = new QLineEdit;
    txtGateway = new QLineEdit;
    buttonOK = new QPushButton("Ok");
    buttonCANCEL = new QPushButton("Cancel");
    buttonOK->setShortcut(Qt::Key_F2);
    buttonCANCEL->setShortcut(Qt::Key_F4);
    QGridLayout *grdLayout=new QGridLayout;
    QHBoxLayout *hbxLayout = new QHBoxLayout;
    grdLayout->setMargin(15);
    grdLayout->addWidget(lblIPaddr,0,0,Qt::AlignLeft);
    grdLayout->addWidget(lblSubnet,1,0,Qt::AlignLeft);
    grdLayout->addWidget(lblGateway,2,0,Qt::AlignLeft);
    grdLayout->addWidget(txtIPaddr,0,1,Qt::AlignCenter);
    grdLayout->addWidget(txtSubnet,1,1,Qt::AlignCenter);
    grdLayout->addWidget(txtGateway,2,1,Qt::AlignCenter);
    hbxLayout->addWidget(buttonOK,2,Qt::AlignCenter);
    hbxLayout->addWidget(buttonCANCEL,2,Qt::AlignCenter);
    hbxLayout->setMargin(0);
    txtIPaddr->setValidator(new QIntValidator(txtIPaddr));
    txtIPaddr->setInputMask("000.000.000.000");
    txtSubnet->setValidator(new QIntValidator(txtSubnet));
    txtSubnet->setInputMask("000.000.000.000");
    txtGateway->setValidator(new QIntValidator(txtGateway));
    txtGateway->setInputMask("000.000.000.000");
    connect(buttonCANCEL,SIGNAL(clicked()),this,SLOT(NetworkexitTrans()));
    connect(buttonOK,SIGNAL(clicked()),this,SLOT(clickNetConfOK()));
    connect(txtIPaddr,SIGNAL(textChanged(QString)),this,SLOT(makeEnable()));
    connect(txtSubnet,SIGNAL(textChanged(QString)),this,SLOT(makeEnable()));
    connect(txtGateway,SIGNAL(textChanged(QString)),this,SLOT(makeEnable()));
    grpbxNetConf->setLayout(grdLayout);
    QVBoxLayout *vbxMainLayout = new QVBoxLayout;
    vbxMainLayout->addWidget(grpbxNetConf);
    vbxMainLayout->addLayout(hbxLayout);
    scrollarea->setWidgetResizable(false);
    scrollarea->verticalScrollBar()->setStyleSheet("width: 20px;");
    scrollarea->setFixedSize(SWID,460);
    setFixedSize(SWID,460);
    move(0,0);
    scrollarea->setLayout(vbxMainLayout);
    setButtonDefault(this);

    if(g_ccmainObj->serverMethod()->ethernetConfig(IPaddr,Subnet,Gateway))
    {
        txtIPaddr->setText(IPaddr);
        txtSubnet->setText(Subnet);
        txtGateway->setText(Gateway);
    }

    btnClear=new QPushButton;
    btnClear->setShortcut(Qt::Key_F1);
    connect(btnClear,SIGNAL(clicked()),this,SLOT(clearForm()));
    btnClear->setFixedSize(0,0);
    vbxMainLayout->addWidget(btnClear);

    buttonOK->setEnabled(false);
    show();//Error occured as "wrong type argument to unary minus" so i have comment
    txtIPaddr->setFocus(Qt::ShortcutFocusReason);
    txtIPaddr->setFocus();
}

void EthernetWnd::clickNetConfOK()
{
    this->setEnabled(false);
    IPaddr = txtIPaddr->text();
    Subnet = txtSubnet->text();
    Gateway = txtGateway->text();

    if(IPaddr == "...")
    {
        QMessageBox::information(0,"Ethernet Configuration","Enter IP Address...");
        this->setEnabled(true);
        txtIPaddr->setFocus();
        return;
    }
    else if(Subnet == "...")
    {
        QMessageBox::information(0,"Ethernet Configuration","Enter Subnet Mask...");
        this->setEnabled(true);
        txtSubnet->setFocus();
        return;
    }
    else if(Gateway == "...")
    {
        QMessageBox::information(0,"Ethernet Configuration","Enter Gateway...");
        this->setEnabled(true);
        txtGateway->setFocus();
        return;
    }
    if( g_ccmainObj->serverMethod()->setEthernetConfig(IPaddr, Subnet, Gateway))
    {
        QMessageBox::information(0,"Ethernet Configuration","Ethernet Configured Successfully");
        close();
        delete this;
        loadForm(SETTINGMENU, 0);
    }
    else
    {
        this->setEnabled(true);
        txtIPaddr->setFocus();
    }
}

void EthernetWnd::makeEnable()
{
    buttonOK->setEnabled(true);
}

void EthernetWnd::NetworkexitTrans()
{
    this->setEnabled(false);
    qApp->processEvents();
    this->close();
    delete this;
}

void EthernetWnd::clearForm()
{
    clearAll(this);
}

void EthernetWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        NetworkexitTrans();
    }
    else if (event->key() == Qt::Key_F1)
    {
        clearForm();
    }
    else
    {
        QDialog::keyPressEvent(event);
    }
}


GPRSWnd::GPRSWnd(QWidget *parent): QDialog(parent)
{
    setParent(MdiArea);
}

void GPRSWnd::showGPRS()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    scrollArea=NULL;
    //    HomeNetwork="";
    grpbxNetConf = new QGroupBox(this);
    grpbxNetConf->setFixedSize(320,460);
    grpbxNetConf->setStyleSheet("background-color:white;color:black");
    labelAPN = new QLabel("  Enter &APN  :");
    lableGprsAlways = new QLabel("GPRS");
    textAPN = new QLineEdit;
    buttonSearchNetworkManual = new QPushButton("Search Network\n  Manual");
    buttonSearchNetworkAuto = new QPushButton("Search Network\n Automatic");
    buttonGPRSAlwaysON_OFF = new QPushButton();
    //    labelNetworkStatus = new QLabel("Network Selected >>  "+ HomeNetwork);
    //    labelNetworkStatus->setStyleSheet("text-align: center;font size=3;font:Bold;color:red");
    //    labelNetworkStatus->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(9);
    buttonGPRSAlwaysON_OFF->setFont(font);
    buttonGPRSAlwaysON_OFF->setFixedSize(100,30);
    buttonGPRSAlwaysON_OFF->setAutoDefault(true);
    buttonGPRSAlwaysON_OFF->setStyleSheet("background-color:green");
    buttonSearchNetworkManual->setFont(font);
    buttonSearchNetworkManual->setAutoDefault(true);
    buttonSearchNetworkManual->setFixedSize(100,30);
    buttonSearchNetworkAuto->setFont(font);
    buttonSearchNetworkAuto->setAutoDefault(true);
    buttonSearchNetworkAuto->setFixedSize(100,30);
    buttonSearchNetworkManual->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    buttonSearchNetworkAuto->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    //    labelNetworkStatus->setFixedSize(320,25);
    font.setPointSize(14);
    font.setBold(true);
    lableGprsAlways->setFont(font);
    lableGprsAlways->setFixedSize(60,30);
    labelAPN->setFixedSize(60,25);
    textAPN->setFixedSize(145,25);
    textAPN->setEnabled(false);
    buttonOK = new QPushButton("Ok");
    buttonOK->setFixedSize(120,30);
    buttonCANCEL = new QPushButton("Cancel");
    buttonCANCEL->setFixedSize(120,30);
    buttonOK->setShortcut(Qt::Key_F2);
    buttonCANCEL->setShortcut(Qt::Key_F4);
    QGridLayout *grdLayout=new QGridLayout;
    grdLayout->setMargin(10);
    grdLayout->addWidget(lableGprsAlways,0,0,Qt::AlignRight);
    grdLayout->addWidget(buttonGPRSAlwaysON_OFF,0,1,Qt::AlignLeft);
    grdLayout->addWidget(buttonSearchNetworkManual,1,0,Qt::AlignHCenter);
    grdLayout->addWidget(buttonSearchNetworkAuto,1,1,Qt::AlignHCenter);
    //    grdLayout->addWidget(labelNetworkStatus,2,0,1,0,Qt::AlignHCenter);
    grdLayout->addWidget(labelAPN,2,0,1,0);
    grdLayout->addWidget(textAPN,2,1,1,1);
    grdLayout->addWidget(buttonOK,3,0,1,0);
    grdLayout->addWidget(buttonCANCEL,3,1,1,1);
    labelAPN->setBuddy(textAPN);
    buttonOK->setEnabled(false);
    grpbxNetConf->setLayout(grdLayout);
    setFixedSize(SWID,460);
    move(0,0);
    setButtonDefault(this);
    textAPN->setEnabled(true);

    connect(buttonGPRSAlwaysON_OFF,SIGNAL(clicked()),this,SLOT(on_clickedGPRSAlwaysON_OFF()));
    connect(buttonCANCEL,SIGNAL(clicked()),this,SLOT(GPRSexitTrans()));
    connect(buttonOK,SIGNAL(clicked()),this,SLOT(clickGPRSOK()));
    connect(textAPN,SIGNAL(textChanged(QString)),this,SLOT(makeEnable()));
    connect(buttonSearchNetworkManual,SIGNAL(clicked()),this,SLOT(NetworkSearchManual()));
    connect(buttonSearchNetworkAuto,SIGNAL(clicked()),this,SLOT(NetworkSearchAuto()));
    //    g_ccmainObj->gsmNetwork(HomeNetwork);
    //    if(HomeNetwork != "")
    //    {
    //        labelNetworkStatus->setStyleSheet("text-align:center;font size=3;font:Bold;color:green");
    //        labelNetworkStatus->setText("Selected Network >> "+ HomeNetwork);
    //Modified Boopathi set  APN Mannually
    //        textAPN->setText(g_ccmainObj->serverMethod()->getgprsApn());
    //    }
    //    else
    //    {
    //        labelNetworkStatus->setStyleSheet("text-align:center;font size=3;font:Bold;color:red");
    //        labelNetworkStatus->setText("No Network Selected");
    textAPN->setText(g_ccmainObj->serverMethod()->getgprsApn());
    //    }
    if(g_ccmainObj->serverMethod()->getgprsAlwaysON_OFF())
    {
        ButtonONOFF=false;
        lableGprsAlways->setText("GPRS");
        buttonGPRSAlwaysON_OFF->setText("ON");
        buttonGPRSAlwaysON_OFF->setStyleSheet("background-color:green");
        buttonSearchNetworkAuto->setEnabled(false);
        buttonSearchNetworkManual->setEnabled(false);
        buttonGPRSAlwaysON_OFF->setFocus();
    }
    else
    {
        ButtonONOFF=true;
        lableGprsAlways->setText("GPRS");
        buttonGPRSAlwaysON_OFF->setText("OFF");
        buttonGPRSAlwaysON_OFF->setStyleSheet("background-color:red");
        buttonSearchNetworkAuto->setEnabled(true);
        buttonSearchNetworkManual->setEnabled(true);
        buttonGPRSAlwaysON_OFF->setFocus();
    }
    show();
    setObjectName("GPRSConf");
}

void GPRSWnd::GPRSexitTrans()
{
    this->close();
}
void GPRSWnd::on_clickedGPRSAlwaysON_OFF()
{
//    qDebug()<<"\r clicked on / off key";
    if(ButtonONOFF)
    {
//        qDebug()<<"\r clicked on / off key 1";
        buttonGPRSAlwaysON_OFF->setText("ON");
        ButtonONOFF=false;
        g_ccmainObj->serverMethod()->setgprsAlwaysON_OFF(true);
        lableGprsAlways->setText("GPRS");
        buttonSearchNetworkAuto->setEnabled(false);
        buttonSearchNetworkManual->setEnabled(false);
        g_ccmainObj->EnableGSMMessageBox(false);
        buttonGPRSAlwaysON_OFF->setStyleSheet("background-color:green");
    }
    else
    {
//        qDebug()<<"\r clicked on / off key 2";
        buttonGPRSAlwaysON_OFF->setText("OFF");
        ButtonONOFF=true;
        g_ccmainObj->serverMethod()->setgprsAlwaysON_OFF(false);
        lableGprsAlways->setText("GPRS");
        buttonSearchNetworkAuto->setEnabled(true);
        buttonSearchNetworkManual->setEnabled(true);
        buttonGPRSAlwaysON_OFF->setStyleSheet("background-color:red");
        if(g_ccmainObj->isGprs())
        {
            g_ccmainObj->EnableGSMMessageBox(true);
            sleep(2);
            g_ccmainObj->disableGprs();
        }
    }
}

void GPRSWnd::clickGPRSOK()
{
    setEnabled(false);
    if(g_ccmainObj->serverMethod()->getgprsAlwaysON_OFF())
    {
        if(textAPN->text()=="")
        {
            QMessageBox::information(0,"GPRS Settings","Enter APN for the Inserted SIMCard");
            setEnabled(true);
            textAPN->setFocus();
            return;
        }
        g_ccmainObj->serverMethod()->setgprsAlwaysON_OFF(false);
        sleep(2);
        g_ccmainObj->disableGprs();
        sleep(5);
        if(g_ccmainObj->serverMethod()->setGprsApn(textAPN->text()))
        {
            QMessageBox::information(0, "GPRS Settings", "GPRS configured successfully ...!");
            qDebug()<<"\r Clancor.> configure success set gprsapn";
            this->close();
//            setEnabled(false);
        }
        sleep(3);
        g_ccmainObj->enableGprs();
        sleep(5);
        g_ccmainObj->serverMethod()->setgprsAlwaysON_OFF(true);
    }
    else
    {
        if(textAPN->text()=="")
        {
            QMessageBox::information(0,"GPRS Settings","Enter APN for the Inserted SIMCard");
            setEnabled(true);
            textAPN->setFocus();
            return;
        }
        if(g_ccmainObj->serverMethod()->setGprsApn(textAPN->text()))
        {
            qDebug()<<"\r Clancor.> configure success";
            QMessageBox::information(0, "GPRS Settings", "GPRS configured successfully ...!");
            this->close();
            qDebug()<<"\r Clancor.> configure success 1";
        }
    }
    qDebug()<<"\r Clancor.> configure success 2";
    this->close();
}

void GPRSWnd::NWSearchOperation()
{
    if(!g_ccmainObj->operatorList(NetworkList))
    {
        QMessageBox::critical(0,"GPRS Settings","Failed while searching available networks");
        setEnabled(true);
        return;
    }
    else
    {
        if(NetworkList.size()>0)
        {
            grpbxNetConf->hide();
            scrollArea = new QScrollArea(this);
            scrollArea->setFixedSize(320,460);
            scrollArea->setFocusPolicy(Qt::NoFocus);
            scrollArea->verticalScrollBar()->setStyleSheet("width: 20px;");
            scrollArea->setWidgetResizable(false);
            vernetworkList=new QVBoxLayout();
            qDebug()<<"\r Clancor network"<<networkLineedit;
            QWidget *widNetworklist=new QWidget();
            for(i=0;i<NetworkList.size();i++ )
            {
                if(i==25)
                    break;
                networkLineedit[i]=new QLineEdit();
                networkLineedit[i]->setText(NetworkList.at(i).mid(0,NetworkList.at(i).indexOf(",")));
                networkLineedit[i]->setObjectName(NetworkList.at(i).mid(NetworkList.at(i).indexOf(",")+1,NetworkList.at(i).length()));
                networkLineedit[i]->setReadOnly(true);
                networkLineedit[i]->setStyleSheet("text-align: center;font:Bold;background-color:gray;color:yellow");
                networkLineedit[i]->setFixedSize(280,25);
                qDebug()<<"\r Clancor network [i]"<<networkLineedit[i];
                connect(networkLineedit[i],SIGNAL(returnPressed()),this,SLOT(setNetworkManually()));
                vernetworkList->addWidget(networkLineedit[i]);
                vernetworkList->setAlignment(Qt::AlignCenter);
            }
            widNetworklist->setLayout(vernetworkList);
            scrollArea->setWidget(widNetworklist);
            scrollArea->show();
            networkLineedit[0]->setFocus();
            networkLineedit[0]->selectAll();
        }
        else
        {
            QMessageBox::critical(0,"GPRS Settings","No Networks available");
            setEnabled(true);
            return;
        }
    }
    setEnabled(true);
}

void GPRSWnd::NetworkSearchManual()
{
    setEnabled(false);
    NWSearchOperation();
}

void GPRSWnd::NetworkSearchAuto()
{
    setNetworkAuto();
}

void GPRSWnd::setNetworkManually()
{
    setEnabled(false);
    QString networkID;
    QLineEdit *bb= qobject_cast<QLineEdit*>(sender());
    if(bb)
        networkID = bb->objectName();
    networkMode=eNetworkMode_Manual;
    if(g_ccmainObj->setGsmNetworkManually(networkID,networkMode))
    {
        QMessageBox::information(0, "GPRS Settings", "Manual Network configured successfully ...!");
    }
    this->close();
}

void GPRSWnd::setNetworkAuto()
{
    setEnabled(false);
    networkMode=eNetworkMode_Auto;
    QString NoNetwork="";
    if(g_ccmainObj->setGsmNetworkManually(NoNetwork,networkMode))
    {
        QMessageBox::information(0, "GPRS Settings", "Automatic Network configured successfully ...!");
    }
    this->close();
}


void GPRSWnd::makeEnable()
{
    if(!buttonOK->isEnabled())
        buttonOK->setEnabled(true);
}

void GPRSWnd::clearForm()
{
    clearAll(this);
}

void GPRSWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        if(scrollArea==NULL)
        {
            this->close();
        }
        else
        {
            scrollArea->hide();
            scrollArea=NULL;
            grpbxNetConf->show();
            textAPN->setFocus();
        }
    }
    else if (event->key() == Qt::Key_F1)
    {
        clearForm();
    }
    else
    {
        QDialog::keyPressEvent(event);
    }
}

//*********************************************************************************/
//                       Class idle mode & Standby mode Settings                  //
/*********************************************************************************/

PowerOptions::PowerOptions(QWidget *parent)
    : QDialog(parent)
{
    setParent(MdiArea);
    IdlemodeOld = 0;
    StandBymodeOld = 0;

    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setFixedSize(320,480);

    lblIdlemode = new QLabel("Interval (in sec) ");
    lblStandBymode = new QLabel("Interval (in sec)");
    lblScreenlock = new QLabel("Interval (in sec)");
    spinIdlemode = new QSpinBox;
    spinStandBymode = new QSpinBox;
    spinScreenlockTime=new QSpinBox;
    groupBoxWindow = new GroupBoxCustom("Power Management Settings");
    groupBoxIdlemode = new GroupBoxCustom("Idle Mode");
    groupBoxStandBymode = new GroupBoxCustom("StandBy Mode");
    groupBoxScreenLock = new GroupBoxCustom("Screen Lock");
    buttonok = new QPushButton("Ok");
    buttoncancel = new QPushButton("Cancel");
    HBoxBtnLayout = new QHBoxLayout;
    VBoxMainLayout = new QVBoxLayout;
    QHBoxLayout *HBoxLytBacklight = new QHBoxLayout;
    QHBoxLayout *HBoxLytScreen = new QHBoxLayout;
    QHBoxLayout *HBoxLytStanby = new QHBoxLayout;
    spinIdlemode->setRange(0,600);
    spinIdlemode->setMinimum(30);
    spinIdlemode->setFixedSize(60,20);
    spinStandBymode->setRange(10,600);
    spinStandBymode->setMinimum(60);
    spinStandBymode->setFixedSize(60,20);
    spinScreenlockTime->setRange(10,600);
    spinScreenlockTime->setMinimum(10);
    spinScreenlockTime->setFixedSize(60,20);

    HBoxLytBacklight->addWidget(lblIdlemode);
    HBoxLytBacklight->addWidget(spinIdlemode);
    HBoxLytScreen->addWidget(lblScreenlock);
    HBoxLytScreen->addWidget(spinScreenlockTime);
    HBoxLytStanby->addWidget(lblStandBymode);
    HBoxLytStanby->addWidget(spinStandBymode);
    HBoxLytBacklight->setSpacing(0);
    HBoxLytStanby->setSpacing(0);
    groupBoxIdlemode->setCheckable(true);
    groupBoxScreenLock->setCheckable(true);
    groupBoxStandBymode->setCheckable(true);
    groupBoxIdlemode->setLayout(HBoxLytBacklight);
    groupBoxStandBymode->setLayout(HBoxLytStanby);
    groupBoxScreenLock->setLayout(HBoxLytScreen);

    buttonok->setShortcut(Qt::Key_F2);
    buttonok->setEnabled(false);

    HBoxBtnLayout->addWidget(buttonok,5,Qt::AlignRight);
    HBoxBtnLayout->addWidget(buttoncancel,5,Qt::AlignRight);


    VBoxMainLayout->addWidget(groupBoxIdlemode);
    VBoxMainLayout->addWidget(groupBoxStandBymode);
    VBoxMainLayout->addWidget(groupBoxScreenLock);
    VBoxMainLayout->addLayout(HBoxBtnLayout);
    VBoxMainLayout->setSpacing(0);
    VBoxMainLayout->setMargin(3);

    groupBoxWindow->setLayout(VBoxMainLayout);
    groupBoxWindow->setFixedSize(300,400);
    groupBoxWindow->setFocusPolicy(Qt::NoFocus);
    groupBoxWindow->move(20,20);

    scrollarea->setWidget(groupBoxWindow);
    scrollarea->setFocusPolicy(Qt::NoFocus);

    connect(buttonok,SIGNAL(clicked()),this, SLOT(PowerOptionsOkTrans()));
    connect(buttoncancel,SIGNAL(clicked()),this, SLOT(PowerOptionsCloseTrans()));

    ScreenlockOld=g_ccmainObj->serverMethod()->keypadLockTimeout();
    IdlemodeOld=g_ccmainObj->serverMethod()->idleModeTimeout();
    StandBymodeOld=g_ccmainObj->serverMethod()->standbyModeTimeout();
    if( ScreenlockOld == 0 ) {
        groupBoxScreenLock->setChecked(false);
    }
    if( IdlemodeOld == 0 ) {
        groupBoxIdlemode->setChecked(false);
    }
    if( StandBymodeOld == 0 ) {
        groupBoxStandBymode->setChecked(false);
    }
    spinScreenlockTime->setValue(ScreenlockOld);
    spinIdlemode->setValue(IdlemodeOld);
    spinStandBymode->setValue(StandBymodeOld);

    connect(spinIdlemode,SIGNAL(valueChanged(int)), this, SLOT(setButtonEnable(int)));
    connect(spinScreenlockTime, SIGNAL(valueChanged(int)), this, SLOT(setButtonEnable(int)));
    connect(spinStandBymode, SIGNAL(valueChanged(int)), this, SLOT(setButtonEnable(int)));
    connect(groupBoxIdlemode, SIGNAL(toggled(bool)),this , SLOT(IdlemodeToggle(bool)));
    connect(groupBoxStandBymode, SIGNAL(toggled(bool)),this , SLOT(StandBymodeToggle(bool)));
    connect(groupBoxScreenLock, SIGNAL(toggled(bool)),this , SLOT(ScreenlockToggle(bool)));

    setFocusPolicy(Qt::NoFocus);
    setFixedSize(320,480);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setButtonDefault(this);
    move(0,0);
    groupBoxIdlemode->setFocus();
}

void PowerOptions::PowerOptionsOkTrans()
{
    if(groupBoxIdlemode->isChecked())
        IdlemodeOld = spinIdlemode->value();
    else
        IdlemodeOld = 0;
    if(groupBoxStandBymode->isChecked())
        StandBymodeOld = spinStandBymode->value();
    else
        StandBymodeOld = 0;
    if(groupBoxScreenLock->isChecked())
        ScreenlockOld = spinScreenlockTime->value();
    else
        ScreenlockOld = 0;
    g_ccmainObj->serverMethod()->setKeypadLockTimeout(ScreenlockOld);
    g_ccmainObj->serverMethod()->setIdleModeTimeout(IdlemodeOld);
    g_ccmainObj->serverMethod()->setStandbyModeTimeout(StandBymodeOld);
    QMessageBox::information(0,"Screen Settings changed","Settings Changed Successfully..!");
    PowerOptionsCloseTrans();
}

void PowerOptions::setButtonEnable(int value)
{
    if(!buttonok->isEnabled())
        buttonok->setEnabled(true);
}

void PowerOptions::IdlemodeToggle(bool toggle)
{
    if(!buttonok->isEnabled())
        buttonok->setEnabled(true);
    if(toggle == true)
    {
        spinIdlemode->setValue(IdlemodeOld);
    }
    else
    {
        IdlemodeOld = spinIdlemode->value();
    }
}

void PowerOptions::StandBymodeToggle(bool toggle)
{
    if(!buttonok->isEnabled())
        buttonok->setEnabled(true);
    if(toggle == true)
    {
        spinStandBymode->setValue(StandBymodeOld);
    }
    else
    {
        StandBymodeOld = spinStandBymode->value();
    }
}

void PowerOptions::ScreenlockToggle(bool toggle)
{
    if(!buttonok->isEnabled())
        buttonok->setEnabled(true);
    if(toggle == true)
    {
        spinScreenlockTime->setValue(ScreenlockOld);
    }
    else
    {
        ScreenlockOld = spinScreenlockTime->value();
    }
}
void PowerOptions::PowerOptionsCloseTrans()
{
    this->setEnabled(false);
    qApp->processEvents();
    setButtonEnable(IdlemodeOld);
    setButtonEnable(StandBymodeOld);
    this->close();
    delete this;
}

void PowerOptions::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        PowerOptionsCloseTrans();
    }
    else
    {
        QDialog::keyPressEvent(event);
    }
}

timeset::timeset()
{
}

void timeset::run()
{
    while(1)
    {
        msleep(1000);
        time = QTime::currentTime();
        emit getTime(time);
        if(!isRunning())
        {
            break;
        }
    }
}

DateTimeSetting::DateTimeSetting() : QDialog()
{
    setParent(MdiArea);
    flag = false;
    timedate = new timeset;
    labelTime = new QLabel("Time:");
    labelDate = new QLabel("Date:");
    QLabel *labelcolon = new QLabel(":");
    QLabel *labelcolon1 = new QLabel(":");

    spinHour = new QSpinBox;
    spinMin = new QSpinBox;
    spinSec = new QSpinBox;
    calender = new QCalendarWidget;
    groupBox = new QGroupBox();
    buttonok = new QPushButton("Ok");
    buttoncancel = new QPushButton("Cancel");
    buttonbox = new QDialogButtonBox;
    vboxLayout = new QVBoxLayout;
    timeLayout = new QHBoxLayout;
    dateLayout = new QHBoxLayout;
    labelTime->setWordWrap(true);
    labelDate->setAlignment(Qt::AlignTop);
    calender->setGridVisible(true);
    calender->setNavigationBarVisible(false);
    calender->setFixedSize(255,125);
    timeLayout->setMargin(0);
    dateLayout->setMargin(0);
    vboxLayout->setMargin(0);
    timeLayout->setSpacing(0);
    dateLayout->setSpacing(0);
    vboxLayout->setSpacing(0);
    spinHour->setFixedWidth(75);
    spinMin->setFixedWidth(75);
    spinSec->setFixedWidth(75);
    spinHour->setFixedHeight(17);
    spinMin->setFixedHeight(17);
    spinSec->setFixedHeight(17);
    spinYear.setFixedHeight(17);
    comboMonth.setFixedHeight(17);
    for(int i = 1; i < 13 ; i++)
        comboMonth.addItem(calender->minimumDate().longMonthName(i));

    spinYear.setRange(calender->minimumDate().year(), calender->maximumDate().year());

    spinYear.setValue(calender->yearShown());
    comboMonth.setCurrentIndex(calender->monthShown()-1);
    timeLayout->addWidget(labelTime,0,Qt::AlignLeft);
    timeLayout->addSpacing(5);
    timeLayout->addWidget(spinHour,0,Qt::AlignLeft);
    timeLayout->addSpacing(5);
    timeLayout->addWidget(labelcolon);
    timeLayout->addSpacing(5);
    timeLayout->addWidget(spinMin,0,Qt::AlignRight);
    timeLayout->addSpacing(5);
    timeLayout->addWidget(labelcolon1);
    timeLayout->addSpacing(5);
    timeLayout->addWidget(spinSec,0,Qt::AlignRight);

    dateLayout->addWidget(labelDate);
    dateLayout->addSpacing(5);
    dateLayout->addWidget(&comboMonth);
    dateLayout->addSpacing(5);
    dateLayout->addWidget(&spinYear);

    QVBoxLayout *tempLayout = new QVBoxLayout;
    tempLayout->setMargin(0);
    tempLayout->setSpacing(0);
    tempLayout->addSpacing(4);
    tempLayout->addLayout(timeLayout,0);
    tempLayout->addSpacing(4);
    tempLayout->addLayout(dateLayout,0);
    tempLayout->addSpacing(4);
    tempLayout->addWidget(calender,35, Qt::AlignRight);

    buttonok->setShortcut(Qt::Key_F2);
    buttoncancel->setShortcut(Qt::Key_F4);
    buttonok->setEnabled(false);
    buttonbox->addButton(buttonok,QDialogButtonBox::AcceptRole);
    buttonbox->addButton(buttoncancel,QDialogButtonBox::RejectRole);

    groupBox->setLayout(tempLayout);
    groupBox->setFixedSize(300,440);//alter by mahesh on oct 9 2013
    connect(buttonbox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonbox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(spinHour,SIGNAL(editingFinished()),this,SLOT(timeChanged()));
    connect(spinMin,SIGNAL(editingFinished()),this,SLOT(timeChanged1()));
    connect(&spinYear,SIGNAL(editingFinished()),this,SLOT(setCalenderYear()));
    connect(&comboMonth,SIGNAL(currentIndexChanged(int)),this,SLOT(setCalenderMonth(int)));

    connect(timedate,SIGNAL(getTime(QTime)),this,SLOT(showtimedate(QTime)));
    connect(calender,SIGNAL(selectionChanged()),this,SLOT(enableslot()));
    timedate->start();

    vboxLayout->setMargin(3);
    vboxLayout->addWidget(groupBox,0,Qt::AlignCenter);
    vboxLayout->addSpacing(5);
    vboxLayout->addWidget(buttonbox);

    QGroupBox *g = new QGroupBox;
    g->move(15, 0);//old 5,0
    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setFixedSize(320,480);
    scrollarea->setFocusPolicy(Qt::NoFocus);
    g->setLayout(vboxLayout);
    g->setFixedSize(320,400);//alter by mahesh oct 9 2013
    g->setFocusPolicy(Qt::NoFocus);
    scrollarea->setWidget(g);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setFocusPolicy(Qt::NoFocus);
    setWindowTitle("Date dialog");
    setFixedSize(320,480);
    calender->setFocus();
}


void DateTimeSetting::showtimedate(QTime currentTime)
{
    if(flag == false)
    {
        spinHour->setValue(currentTime.toString("hh").toInt());
        spinMin->setValue(currentTime.toString("mm").toInt());
        spinSec->setValue(currentTime.toString("ss").toInt());
        flag = true;
    }
    else
    {
        spinSec->setValue(currentTime.toString("ss").toInt());
        val = currentTime.toString("ss").toInt();
        if(val==59)
        {
            minval = spinMin->value();
            minval++;
            if(minval == 59)
            {
                spinMin->setValue(00);
                minval=spinHour->value();
                minval++;
                if(minval==23)
                {
                    spinHour->setValue(00);
                    return;
                }
            }
            else
            {
                spinMin->setValue(minval);
            }
        }
    }
}

void DateTimeSetting::timeChanged()
{
    buttonok->setEnabled(true);
    if(timedate->isRunning())
    {
        timedate->terminate();
    }
}

void DateTimeSetting::timeChanged1()
{
    buttonok->setEnabled(true);
    if(timedate->isRunning())
    {
        timedate->terminate();
    }
}

void DateTimeSetting::setCalenderYear()
{
    calender->setSelectedDate(QDate(spinYear.value(), comboMonth.currentIndex() + 1, calender->selectedDate().day()));
}

void DateTimeSetting::setCalenderMonth(int month_index)
{
    calender->setSelectedDate(QDate(spinYear.value(), month_index + 1, calender->selectedDate().day()));
}

void DateTimeSetting::enableslot()
{
    if(comboMonth.currentIndex() != (calender->monthShown() - 1))
    {
        if(spinYear.value() != calender->yearShown())
        {
            spinYear.setValue(calender->yearShown());
        }
        comboMonth.setCurrentIndex(calender->monthShown() - 1);
    }
    buttonok->setEnabled(true);
}



ApplicationLaunchWnd::ApplicationLaunchWnd(QWidget *parent): QDialog(parent)
{
    setParent(MdiArea);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    QScrollArea *scrollarea = new QScrollArea(this);
    QGroupBox *grpbxNetConf = new QGroupBox("Application Launcher Configuration");
    QLabel *lblFile = new QLabel("File Name :");
    txtFilename = new QLineEdit;
    buttonBrowse=new QPushButton("Browse");
    chkBoot=new QCheckBox("Auto Boot-F1");
    chkBoot->setShortcut(Qt::Key_F1);
    groupboxCustomVerify = new GroupBoxCustom("Signature Verify");
    groupboxCustomVerify->setCheckable(true);
    QLabel *lblSignFile = new QLabel("Load Sign File: ");
    txtSignFile = new QLineEdit;;
    buttonBrowseSign = new QPushButton("Browse");
    buttonRunBinaryFile=new QPushButton("Run Binary File");

    QHBoxLayout *hbxSignatureLayout = new QHBoxLayout;
    hbxSignatureLayout->addWidget(lblSignFile);
    hbxSignatureLayout->addWidget(txtSignFile);
    hbxSignatureLayout->addWidget(buttonBrowseSign);
    groupboxCustomVerify->setLayout(hbxSignatureLayout);

    buttonOK = new QPushButton("Ok");
    buttonCANCEL = new QPushButton("Cancel");
    buttonOK->setShortcut(Qt::Key_F2);

    QGridLayout *grdLayout=new QGridLayout;
    QHBoxLayout *hbxBtnLayout = new QHBoxLayout;

    grdLayout->setMargin(15);
    grdLayout->addWidget(lblFile,0,0,Qt::AlignLeft);
    grdLayout->addWidget(txtFilename,0,1,Qt::AlignCenter);
    grdLayout->addWidget(buttonBrowse,0,2,Qt::AlignCenter);
    grdLayout->addWidget(chkBoot,1,1,Qt::AlignCenter);
    grdLayout->addWidget(buttonRunBinaryFile,1,2,Qt::AlignCenter);

    hbxBtnLayout ->addWidget(buttonOK,2,Qt::AlignCenter);
    hbxBtnLayout ->addWidget(buttonCANCEL,2,Qt::AlignCenter);
    hbxBtnLayout ->setMargin(0);

    connect(buttonCANCEL,SIGNAL(clicked()),this,SLOT(Cancel_Click()));
    connect(buttonOK,SIGNAL(clicked()),this,SLOT(Ok_Click()));
    connect(buttonBrowse,SIGNAL(clicked()),this,SLOT(browseSlot()));
    connect(buttonRunBinaryFile,SIGNAL(clicked()),this,SLOT(RunBinaryFile()));
    connect(buttonBrowseSign,SIGNAL(clicked()),this,SLOT(browseSignSlot()));
    connect(chkBoot,SIGNAL(toggled(bool)),this,SLOT(EnableButton()));
    connect(groupboxCustomVerify,SIGNAL(toggled(bool)),this,SLOT(EnableButton()));

    grpbxNetConf->setLayout(grdLayout);
    QVBoxLayout *vbxMainLayout = new QVBoxLayout;
    vbxMainLayout->addWidget(grpbxNetConf);
    vbxMainLayout->addWidget(groupboxCustomVerify);
    vbxMainLayout->addLayout(hbxBtnLayout );
    scrollarea->setWidgetResizable(false);
    scrollarea->verticalScrollBar()->setStyleSheet("width: 20px;");
    scrollarea->setFixedSize(SWID,460);
    setFixedSize(320,460);
    move(0,0);
    scrollarea->setLayout(vbxMainLayout);
    setButtonDefault(this);
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
            qryBoot = db->SelectQuery("select Filename/*, Autoboot*/ from BootConfig");
            db->clearAll();
            if(db->IsLastError())
            {
                qryBoot.clear();
            }else
            {
                if(qryBoot.next())
                {
                    txtFilename->setText(qryBoot.value(0).toString());
                    if(g_ccmainObj->getAutoboot()/*qryBoot.value(1).toBool()==true*/) chkBoot->setCheckState(Qt::Checked); else chkBoot->setCheckState(Qt::Unchecked);
                    qryBoot.clear();
                }
            }
        }
    }
    qryBoot.clear();
    qryBoot = db->SelectQuery("select SignFile from PKISignatureConf");
    db->clearAll();
    if(db->IsLastError())
    {
        qryBoot.clear();
    }else
    {
        if(qryBoot.next())
        {
            groupboxCustomVerify->setChecked(true);;
            txtSignFile->setText(qryBoot.value(0).toString());
        }
        else
        {
            groupboxCustomVerify->setChecked(false);;
            txtSignFile->setText("");
        }
    }
    qryBoot.clear();
    scrollarea->setFocusPolicy(Qt::NoFocus);
    grpbxNetConf->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    buttonOK->setEnabled(false);
    myProcess = new QProcess;
    myProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    connect(myProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(CloseApplicaton(int,QProcess::ExitStatus)));
    connect(myProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(Error(QProcess::ProcessError)));
    buttonBrowse->setFocus();
}

void ApplicationLaunchWnd::browseSlot()
{
    setEnabled(false);
    QString strFilePath = getFilePath();
    setEnabled(true);
    if(strFilePath != "")
    {
        txtFilename->setText(strFilePath);
        if(!buttonOK->isEnabled())
            buttonOK->setEnabled(true);
        buttonOK->setFocus();
    }
    else
    {
        buttonBrowse->setFocus();
    }
}

void ApplicationLaunchWnd::RunBinaryFile()
{
    this->setEnabled(false);
    BootFileName=txtFilename->text();
    if(BootFileName =="")
    {
        QMessageBox::critical(0,"Application Launcher","Please Configure the Application...!");
        this->setEnabled(true);
        return;
    }
    if(!QFile::exists(BootFileName))
    {
        QMessageBox::critical(0,"Application Launcher","File Not Found...!");
        this->setEnabled(true);
        return;
    }
    if(!BootFileName.contains("ClanCor_HHC"))
    {
        myProcess->start(BootFileName);
        myProcess->waitForStarted();
        if(myProcess->state()==QProcess::Running)
        {
            //            RunningApplication=true;
        }
        this->close();
        delete this;
    }
    else
    {
        QMessageBox::about(0,"ApplicationLauncher","Application already Running");
        this->setEnabled(true);
        return;
    }
}

void ApplicationLaunchWnd::browseSignSlot()
{
    setEnabled(false);
    QString strFilePath = getFilePath();
    setEnabled(true);
    if(strFilePath != "")
    {
        txtSignFile->setText(strFilePath);
        if(!buttonOK->isEnabled())
            buttonOK->setEnabled(true);
    }
}

QString ApplicationLaunchWnd::getFilePath()
{
    QString strFilePath = "";
    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->dir = "";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        strFilePath = QString(f->path +"/" + f->txtFilename->text());
    }
    delete f;
    return strFilePath;
}

void ApplicationLaunchWnd::EnableButton()
{
    if(!buttonOK->isEnabled())
        buttonOK->setEnabled(true);
}

void ApplicationLaunchWnd::Ok_Click()
{
    setEnabled(false);
    bool autoboot;
    if(chkBoot->checkState()==Qt::Checked) autoboot=true; else autoboot=false;
    if(txtFilename->text()=="")
    {
        QMessageBox::critical(0,"Application Launcher","Please select the File!");
        setEnabled(true);
        buttonBrowse->setFocus();
        return;
    }
    if(!QFile::exists(txtFilename->text()))
    {
        QMessageBox::critical(0,"Application Launcher","File Not Found...!");
        setEnabled(true);
        buttonBrowse->setFocus();
        return;
    }
    if(groupboxCustomVerify->isChecked())
    {
        if(!QFile::exists(txtSignFile->text()))
        {
            QMessageBox::critical(0,"Application Launcher","Sign File Not Found...!");
            setEnabled(true);
            buttonBrowseSign->setFocus();
            return;
        }
        db->DataBaseCommand( "delete from PKISignatureConf" );
        if(!db->DataBaseCommand("insert into PKISignatureConf (SignFile) values('" + txtSignFile->text().simplified() + "')"))
        {
            QMessageBox::critical(0,"Application Launcher","Failed to save sign file..");
            buttonOK->setFocus();
            setEnabled(true);
            return;
        }
        gstrSignFileName = txtSignFile->text().simplified();
    }
    else
    {
        gstrSignFileName = "";
        db->DataBaseCommand( "delete from PKISignatureConf" );
    }
    db->DataBaseCommand( "delete from BootConfig" );
    //    if(db->DataBaseCommand("insert into BootConfig (Filename /*, Autoboot*/) values('" + txtFilename->text().simplified() + "','" + autoboot +"'*/)"))
    if(db->DataBaseCommand("insert into BootConfig (Filename) values('" + txtFilename->text().simplified() + "')"))
    {
        g_ccmainObj->setAutoboot(autoboot);
        BootFileName=txtFilename->text();
        QMessageBox::information(0,"Application Launcher","Application configured successfully..");
        Cancel_Click();
    }
}

void ApplicationLaunchWnd::Cancel_Click()
{
    this->setEnabled(false);
    qApp->processEvents();
    this->close();
    delete this;
}

void ApplicationLaunchWnd::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        Cancel_Click();
    }
    else
    {
        QDialog::keyPressEvent(event);
    }
}

TFTSettingdialog::TFTSettingdialog() : QDialog()
{
    labelbrightness = new QLabel("Brightness");
    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setRange(0,5);
    brightnessSlider->setTickPosition(QSlider::TicksBelow);
    brightnessSlider->setValue(brightnessvalue);
    brightnessSlider->setFixedWidth(130);

    groupBox = new QGroupBox("TFT Brightness");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    vboxLayout = new QVBoxLayout;
    brightnessLayout = new QHBoxLayout;

    brightnessLayout->addWidget(labelbrightness);
    brightnessLayout->addWidget(brightnessSlider);

    groupBox->setLayout(brightnessLayout);

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(brightnessSlider, SIGNAL(valueChanged(int)), SLOT(setBrightness(int)));

    vboxLayout->addWidget(groupBox);
    vboxLayout->addSpacing(25);
    vboxLayout->addWidget(buttonBox);
    vboxLayout->setMargin(0);

    QGroupBox *g = new QGroupBox;
    g->setLayout(vboxLayout);
    g->setFocusPolicy(Qt::NoFocus);

    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setFixedSize(250,150);
    scrollarea->setFocusPolicy(Qt::NoFocus);
    scrollarea->setWidget(g);

    setFixedSize(250,150);
    setLayout(vboxLayout);
    setWindowTitle("TFT Dialog");
    setWindowModality(Qt::ApplicationModal);
    setFocusPolicy(Qt::NoFocus);

    brightnessSlider->setFocus();
}

void TFTSettingdialog::setBrightness(int value)
{
    setDisable(this);

    if(value == 0)
    {
        int res=QMessageBox::information(0,"Display","Do you want to set Brightness value zero?",QMessageBox::Yes,QMessageBox::No);
        if(res==QMessageBox::Yes)
        {
            g_ccmainObj->setBacklight(value);
        }
    }
    else
        g_ccmainObj->setBacklight(value);

    setDisabled(false);
    qApp->processEvents();
    brightnessSlider->setFocus();
}
