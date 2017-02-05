#ifndef GLOBALCLASS_H
#define GLOBALCLASS_H
#include <QMdiArea>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDriver>
#include <QObject>
#include "sqlite3.h"
#include "DBConnection.h"
#include <CPrinter>
#include <CWebCamera>
#include <CAudio>
//#include <CFingerPrint>
#include <CHHC80xx>

#include "myserver.h"
#include "mainwindow.h"
#include "config.h"

#define LOGIN 0
#define DESKTOP 1
#define MAINMENU 2
#define SETTINGMENU 3
#define NEWMENU 4
#define PIC_TESTING 5

#define MHGT 460
#define MWID 320

#define SHGT 200
#define SWID 320
#define GWID 310

using namespace ClanCor;

namespace Globalclass
{
    extern CHHC80xx *g_ccmainObj;
    extern MyServer *MyServerObj;
    extern MainWindow *mainobj;

    extern QMdiArea *MdiArea;
    extern DBConnection *db;
    extern QToolBar *titBar;
    extern QLabel *title;
    extern int brightnessvalue;
    extern int SCREENX1;
    extern int SCREENY1;
    extern bool LOGIN_MANAGEMENT;
    extern bool g_header;
    extern bool g_footer;
    extern bool g_loadImage;
    extern bool g_bFileCopyFlag;
    bool Initialize1();
    void titleBarInit();
    bool DatabaseConnect();
    QSqlQuery *sqlQuery(QString);
    void loadForm(int parentID, int focusMenu);
    void loadStyleSheet(const QString &);
    QString getStyle();
    void setButtonDefault(QWidget *qw);
    void clearAll(QWidget *qw);
    bool createDefault();
    bool GPRSEnable();
    void setDisable(QWidget *qw);
    void UpdateScreen(int msec=100);

    extern QPixmap *UserIcon;
    extern QString UserInfo;
    extern QString BootFileName;
    extern QString gstrSignFileName;
    extern QString LoginId;
    extern QString Password;
    extern QString gstrXMLConfig;
    extern bool typeUser;
    extern bool RunningApplication;
    extern bool DialupAutoGPRS_flag;
}


class TreeView_custom : public QListView
{
    Q_OBJECT
public:
    TreeView_custom(QWidget *parent = 0);
private:
    void virtual keyPressEvent(QKeyEvent *);
signals:
    void IndexChanged(QModelIndex);
};

/******************File Dialog class******************************/
class fileDialog : public QDialog
{
    Q_OBJECT
public:
    fileDialog(QWidget *parent = 0);
    static QString option,dir;
    QLineEdit *txtFilename, *txtFilepath;
    void opnsavDialog();
    QDialog *dia;
    QFileSystemModel *model;
    TreeView_custom *tree;
    QString path;
    QStringList filters;

private:
    QPushButton *btnOpnSav, *btnBack;
    void virtual keyPressEvent(QKeyEvent *);

private slots:
    void setfileName(QModelIndex);
    void openPath();
    void setfileName_text(QModelIndex);
    void setfileName_Focus(QModelIndex);
    void slotOpnSav();
    void openDir();
    void slotBack();


};

/******************File Browser class******************************/
class filebrowser : public QDialog
{
    Q_OBJECT
public:
    filebrowser(QWidget *parent = 0);
    static QString option,dir;
    QLineEdit *txtFilename, *txtFilepath;
    void opnsavDialog();
    QDialog *dia;
    QFileSystemModel *model;
    QListView *tree;
    QString path;

private:
    QPushButton *btnOpnSav, *btnBack;

protected:
    void keyPressEvent(QKeyEvent *keyevent);

private slots:
    void setfileName(QModelIndex);
    void slotOpnSav();
    void openDir();
    void openPath();
    void slotBack();
    void imageViewerSlot();


};


class Notepad : public QDialog
{
    Q_OBJECT
public:
    Notepad(QWidget *parent = 0);
    void openfile(QString filepath);

private:
    QTextEdit *edit;
    QMenu *menubar, *menubar1, *menubar2, *menubar3;
    QMenuBar *bar;
    QVBoxLayout *lay;
    QStatusBar *status;
    QAction *newfile1, *open, *save, *saveAs, *exi, *un, *re, *cutme, *copyme, *pasteme, *mystatus, *about;
    QString mFilePath;

    bool eventFilter(QEvent *event);

private slots:
    void loadme();
    bool saveme();
    bool saveFile(const QString &name);
    bool saveFileAs();
    bool mayDiscardDocument();
    void newfile();
    void undome();
    void redome();
    void Cut();
    void Copy();
    void Paste();
    void aboutme();
    void closeNotepad();
};

#endif // GLOBALCLASS_H
