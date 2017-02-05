#ifndef SETTINGWND_H
#define SETTINGWND_H
#include <QtGui>
#include <CPrinter>
//#include <CFingerPrint>
#include <CWebCamera>
#include <CAudio>
#include<CHHC80xx>
#include<CHHC80xxServer>

using namespace ClanCor;
class SettingWnd : public QMdiSubWindow
{
    Q_OBJECT
public:
    SettingWnd(QWidget *parent = 0);

    private:
        QGridLayout *grdLayout;
        QListWidget *listviewMenu;
        int i,j;
        QScrollArea *scrollArea;
        QGroupBox *g;

        void keyPressEvent(QKeyEvent *event);
        void loadIcon(QString stringCaption, QString stringFileName);
        void triggerItem(QString stringItemSelected);
        void setFocusOnLastItem();
        void setMenuHidden(bool bHide);
        void setMenuShown(bool bShow);

    private slots:
        void slot_ItemEntered(QListWidgetItem *listwidgetitemSelected);
        void slot_ItemCliked(QModelIndex modelindexSelected);
        void slot_SetItemVisible();
        void slot_Ethernet();
        void slot_GPRS();
        void slot_KeyLock_PwrSave();
        void slot_Usbgadget();
        void slot_Theme();
        void slot_VolumeControl();
        void slot_Wallpaper();
        void slot_DateTime();
        void slot_AppLauncher();
        void slot_TouchCalibrate();
        void slot_CoProcessorProg();
        void slot_PrinterSetup();
        void slot_UserAccount();
//        void slot_DialupSetting();
        void slot_WifiSetting();
        void slot_AgpsSetting();
        void slot_ssh();
        void slot_fileUpdate_Ftp();
        void slot_CoUpTest();
};

class GroupBoxCustom : public QGroupBox
{
    Q_OBJECT
public:
    explicit GroupBoxCustom(QWidget *parent = 0);
    explicit GroupBoxCustom(const QString title, QWidget* parent=0);
    ~GroupBoxCustom(){};
private:
    void keyPressEvent(QKeyEvent *event);
};

class EthernetWnd : public QDialog
{
    Q_OBJECT
public:
    EthernetWnd(QWidget *parent = 0);
private:
    QLineEdit *txtIPaddr,*txtSubnet,*txtGateway;
    QPushButton *buttonOK, *buttonCANCEL,*btnClear;
    QString IPaddr,Subnet,Gateway;
    QTimer t;
    int i,j;

    void keyPressEvent(QKeyEvent *event);
    void CreateMenu(QPushButton *,QString);


public slots:
    void showEthernet();


private slots:
    void clickNetConfOK();
    void NetworkexitTrans();
    void clearForm();
    void makeEnable();
};

class GPRSWnd : public QDialog
{
    Q_OBJECT
public:
    GPRSWnd(QWidget *parent = 0);
private:
    QLabel *labelAPN,*lableGprsAlways;
//    *labelNetworkStatus,;
    QLineEdit *textAPN , *networkLineedit[25];
    QVBoxLayout *vernetworkList;
    QPushButton *buttonOK, *buttonCANCEL,*buttonSearchNetworkManual,*buttonSearchNetworkAuto,*buttonGPRSAlwaysON_OFF;
    QStringList NetworkList;
//    QString HomeNetwork;
    QScrollArea *scrollArea;
    QGroupBox *grpbxNetConf;
    E_NetworkMode networkMode;
    bool ButtonONOFF;

    int homeNetworkIndex, wFlag;

    int i,j;

    void CreateMenu(QPushButton *,QString);
    void keyPressEvent(QKeyEvent *event);


public slots:
    void showGPRS();
    void setNetworkManually();
    void setNetworkAuto();

private slots:
    void NWSearchOperation();
    void NetworkSearchManual();
    void NetworkSearchAuto();
    void GPRSexitTrans();
    void clickGPRSOK();
    void clearForm();
    void makeEnable();
    void on_clickedGPRSAlwaysON_OFF();
};

class PowerOptions : public QDialog
{
    Q_OBJECT
private:
    QLabel *lblIdlemode, * lblStandBymode,*lblScreenlock;
    QSpinBox *spinIdlemode,*spinStandBymode,*spinScreenlockTime;
    GroupBoxCustom *groupBoxIdlemode, *groupBoxStandBymode,*groupBoxScreenLock,*groupBoxWindow;
    QPushButton *buttonok,*buttoncancel;
    QHBoxLayout *HBoxBtnLayout;
    QVBoxLayout *VBoxMainLayout;
    int IdlemodeOld,StandBymodeOld,ScreenlockOld;

    void keyPressEvent(QKeyEvent *event);

public:
    PowerOptions(QWidget *parent = 0);

private slots:
    void PowerOptionsOkTrans();
    void PowerOptionsCloseTrans();
    void setButtonEnable(int);
    void IdlemodeToggle(bool);
    void StandBymodeToggle(bool);
    void ScreenlockToggle(bool toggle);
};

class timeset : public QThread
{
    Q_OBJECT
public:
    timeset();
signals:
    void getTime(QTime);
private:
    QTime time;
    void run();
};

class DateTimeSetting: public QDialog
{
   Q_OBJECT

public:
    DateTimeSetting();
    QLabel *labelTime,*labelDate;
    QSpinBox *spinHour,*spinMin,*spinSec;
    QSpinBox spinYear;
    QComboBox comboMonth;
    QCalendarWidget *calender;
    QGroupBox *groupBox;
    QPushButton *buttonok,*buttoncancel;
    QDialogButtonBox *buttonbox;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *timeLayout,*dateLayout;
    timeset *timedate;
    int val,minval;
    bool flag;

private slots:
    void showtimedate(QTime);
    void timeChanged();
    void timeChanged1();
    void setCalenderYear();
    void setCalenderMonth(int month_index);
    void enableslot();
};


class ApplicationLaunchWnd : public QDialog
{
    Q_OBJECT
public:
    ApplicationLaunchWnd(QWidget *parent = 0);
private:
    QLineEdit *txtFilename,*txtSignFile;
    QScrollArea *scrollarea;
    QPushButton *buttonOK, *buttonCANCEL,*buttonBrowse, *buttonBrowseSign,*buttonRunBinaryFile;
    QProcess *myProcess;
    QGridLayout *grdLayout;
    QScrollArea *scrollArea;
    QGroupBox *g;
    QCheckBox *chkBoot;
    GroupBoxCustom *groupboxCustomVerify;
    void keyPressEvent(QKeyEvent *event);
    QString getFilePath();

private slots:
    void Ok_Click();
    void Cancel_Click();
    void browseSlot();
    void browseSignSlot();
    void EnableButton();
    void RunBinaryFile();
};

class TFTSettingdialog : public QDialog
{
   Q_OBJECT

public:
    TFTSettingdialog();
    QLabel*labelbrightness;
    QSlider *brightnessSlider;
    QGroupBox *groupBox;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *brightnessLayout;

private slots:
    void setBrightness(int);

};
#endif // CONFIGMENU_H

