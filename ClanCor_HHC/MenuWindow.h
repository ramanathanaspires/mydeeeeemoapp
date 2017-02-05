#ifndef MENUWINDOW_H
#define MENUWINDOW_H
#include <QMdiSubWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QGroupBox>
#include <GlobalClass.h>

using namespace Globalclass;

class MenuWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    MenuWindow(QWidget *parent = 0);

private:

    QGridLayout *grdLayout;
    QListWidget *listviewMenu;
    int i,j;
    QScrollArea *scrollArea;
    QGroupBox *g;
    QProcess process;
//    CFingerPrint *fpt;

    bool bIsModel8x;

    void keyPressEvent(QKeyEvent *event);
    void loadIcon(QString stringCaption, QString stringFileName);
    void triggerItem(QString);
    void setFocusOnLastItem();
    void setMenuHidden(bool bHide);
    void setMenuShown(bool bShow);
    bool ScreenSettings();

private slots:
    void slot_SetItemVisible();
    void slot_ItemCliked(QModelIndex);
    void slot_ItemEntered(QListWidgetItem* listwidgetitemSelected);
    void slot_SigCapture();
    void slot_PreviewAudio();
    void slot_SaveAudio(QByteArray);
    void slot_FingerDialogCall();
    void slot_PreviewCamera();
      void delay(int nMSec);
    void slot_ImageCaptured(QImage);
    void slot_ImageViewer();
    void slot_PrintClick();
    void slot_WebBrowser();
    void slot_Magneticcard();
    void slot_Rfid();
    void slot_SmartCard();
    void slot_GPS();
    void slot_Notepad();
    void slot_FileCopying();
    void slot_SystemInfo();
    void slot_TerminalEmulator();
    void slot_CloseApplicaton(int,QProcess::ExitStatus);
    void slot_MemoryStatus();
};

#endif // MENUWINDOW_H
