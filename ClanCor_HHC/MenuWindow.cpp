#include "MenuWindow.h"
#include "newmenu.h"
#include "pictureflow.h"
#include <QMdiSubWindow>
#include "GlobalClass.h"
#include "Fprint.h"
#include "gps_data.h"
#include "SmartCard.h"
#include "filecopy.h"
#include "smartcard_contactless.h"
#include "PrinterSetup.h"
#include <hadware.h>
#include <dialog.h>
#include <emulator.h>
#include <csettingsfiles.h>
#include <displaymemory.h>
using namespace Globalclass;

//Default utlitity 7
const QString const_stringPrintUtil = "Printer\nTest";
const QString const_stringNotepad =  "\nNotepad";
const QString const_stringFileCopying = "File\nCopying";
const QString const_stringSystemInfo = "System\nInformation";
//const QString const_stringTerminalEmulator = "Terminal\n Emulator";
const QString const_stringMemoryStatus = "Memory\nStatus";
const QString const_stringImageVwr = "Image\nViewer";


const QString const_stringSigCapture  = "Signature\nCapture";
const QString const_stringVoiceRec  = "Voice\nRecorder";
const QString const_stringFingerPrnt  = "\nBiometric";
const QString const_stringCamera  = "\nCamera";
const QString const_stringMagneticCard = "Magnetic\nCard";
const QString const_stringWebBrwsr = "Web\nBrowser";
const QString const_stringRfid = "\nRFID";
const QString const_stringSmartCard = "Contact\nSmartCard";
const QString const_stringGPS = "\nGPS";


MenuWindow::MenuWindow(QWidget *parent)
    : QMdiSubWindow(parent)
{
    listviewMenu = new QListWidget;
    scrollArea=new QScrollArea(this);
    // bIsModel8x = !g_ccmainObj->deviceModel().contains("HHC-7");

    i=0;
    j=0;
    int nDisplaycount = 7;
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
    loadIcon(const_stringSystemInfo, ":/icons/sys.png");
//    loadIcon(const_stringTerminalEmulator,":/icons/Terminal-icon1.png");
    loadIcon(const_stringMemoryStatus,":/icons/memory.png");
  //  loadIcon(const_stringNotepad, ":/icons/notepad.png");
    loadIcon(const_stringFileCopying, ":/icons/copy2.png");
    loadIcon(const_stringPrintUtil, ":/icons/printer.png");

    gstrXMLConfig= setting.value("Camera");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringCamera, ":/icons/camera.png");
    }
    gstrXMLConfig= setting.value("Touch_Panel");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringSigCapture, ":/icons/signature.png");
    }
    gstrXMLConfig= setting.value("RFID");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringRfid, ":/icons/nfc.png");
    }
    gstrXMLConfig= setting.value("Smart_Card");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringSmartCard, ":/icons/smartcard.png");
    }
    gstrXMLConfig= setting.value("Audio");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringVoiceRec, ":/icons/voice.png");
    }
    gstrXMLConfig= setting.value("FingerPrint");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringFingerPrnt, ":/icons/thumb.png");
    }
    gstrXMLConfig= setting.value("GPS");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringGPS, ":/icons/GPS.png");
    }
    gstrXMLConfig= setting.value("GPRS");
    if(gstrXMLConfig.toLower() == "yes")
    {
        nDisplaycount++;
        loadIcon(const_stringWebBrwsr, ":/icons/web.png");
    }
    loadIcon(const_stringImageVwr, ":/icons/image.png");

    //    if(nDisplaycount <= 9)
    //        listviewMenu->setFixedSize(300, 270);
    //    else if(nDisplaycount > 9 && nDisplaycount <= 12)
    //        listviewMenu->setFixedSize(300, 345);
    //    else
    //        listviewMenu->setFixedSize(300, 450);

    //    connect(listviewMenu,SIGNAL(itemEntered(QListWidgetItem*)),this, SLOT(slot_ItemEntered(QListWidgetItem*)));
    connect(listviewMenu,SIGNAL(clicked(QModelIndex)), this, SLOT(slot_ItemCliked(QModelIndex)));
    connect(listviewMenu,SIGNAL(activated(QModelIndex)), this, SLOT(slot_ItemCliked(QModelIndex)));
    connect(listviewMenu,SIGNAL(itemSelectionChanged()), this, SLOT(slot_SetItemVisible()));
    connect(&process,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slot_CloseApplicaton(int,QProcess::ExitStatus)));

    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(listviewMenu);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setFixedSize(320,460);
    setFocusPolicy(Qt::NoFocus);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(320,460);
    setStyleSheet("background-color:black;color:white;selection-color: white;");//selection-background-color: gray;");
    listviewMenu->setStyleSheet("QListView{border: 0px}QListView::item:focus{border: 1px solid #6a6ea9;}"
                                "QListView::item:focus:size{width:100;height:100;}"
                                "QListView {show-decoration-selected: 1;font-size:11px;font-style:bold;}"
                                "QListView::item:selected:!active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #ABAFE5, stop: 1 #8588B2);}"
                                "QListWidget::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #6a6ea9, stop: 1 #888dd9);}");

    setWindowTitle("menu window");
    listviewMenu->setFocusPolicy(Qt::StrongFocus);
    listviewMenu->setCurrentIndex(listviewMenu->model()->index(0,0));
//    g_ccmainObj->EnableCAMERAModule(true);
    listviewMenu->setFocus();
}

void MenuWindow::loadIcon(QString stringCaption, QString stringFileName)
{
    QIcon icon;
    icon.addFile(stringFileName,QSize());

    QListWidgetItem *listwidgetitemMenu = new QListWidgetItem(icon, stringCaption);
    //    listwidgetitemMenu->setSizeHint(QSize(75, 65));
    listwidgetitemMenu->setSizeHint(QSize(75, 75));
    listviewMenu->addItem(listwidgetitemMenu);
}

void MenuWindow::triggerItem(QString stringItemSelected)
{
    if(const_stringSigCapture == stringItemSelected)
    {
        slot_SigCapture();
    }
    else if(const_stringVoiceRec == stringItemSelected)
    {
        slot_PreviewAudio();
    }
    else if(const_stringFingerPrnt == stringItemSelected)
    {
        slot_FingerDialogCall();
    }
    else if(const_stringCamera == stringItemSelected)
    {
        slot_PreviewCamera();
    }
    else if(const_stringImageVwr == stringItemSelected)
    {
        slot_ImageViewer();
    }
    else if(const_stringPrintUtil == stringItemSelected)
    {
        slot_PrintClick();
    }
    else if(const_stringWebBrwsr == stringItemSelected)
    {
        slot_WebBrowser();
    }
    else if(const_stringMagneticCard == stringItemSelected)
    {
        slot_Magneticcard();
    }
    else if(const_stringRfid == stringItemSelected)
    {
        slot_Rfid();
    }
    else if(const_stringSmartCard == stringItemSelected)
    {
        slot_SmartCard();
    }
    else if(const_stringGPS == stringItemSelected)
    {
        slot_GPS();
    }
    else if(const_stringNotepad == stringItemSelected)
    {
        slot_Notepad();
    }
    else if(const_stringFileCopying == stringItemSelected)
    {
        slot_FileCopying();
    }
    else if(const_stringSystemInfo == stringItemSelected)
    {
        slot_SystemInfo();
    }
//    else if(const_stringTerminalEmulator == stringItemSelected)
//    {
//        slot_TerminalEmulator();
//    }
    else if(const_stringMemoryStatus == stringItemSelected)
    {
        slot_MemoryStatus();
    }
}

void MenuWindow::setFocusOnLastItem()
{
    listviewMenu->setCurrentItem(listviewMenu->currentItem());
    listviewMenu->setFocus();
}

void MenuWindow::setMenuHidden(bool bHide)
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

void MenuWindow::setMenuShown(bool bShow)
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

void MenuWindow::slot_SetItemVisible()
{
    //scrollArea->ensureVisible(listviewMenu->visualRect(listviewMenu->currentIndex()).center().x(),
    //                        listviewMenu->visualRect(listviewMenu->currentIndex()).center().y());
    scrollArea->ensureVisible(listviewMenu->visualRect(listviewMenu->currentIndex()).center().x(),
                              listviewMenu->visualRect(listviewMenu->currentIndex()).bottom()+10);
}

void MenuWindow::slot_ItemCliked(QModelIndex)
{
    QString stringCurrentItemText = listviewMenu->currentItem()->text();
    triggerItem(stringCurrentItemText);
}

void MenuWindow::slot_ItemEntered(QListWidgetItem *listwidgetitemSelected)
{
    QString stringCurrentItemText = listwidgetitemSelected->text();
    triggerItem(stringCurrentItemText);
}

void MenuWindow::slot_SigCapture()
{
    setDisable(this);
   QImage sig;
    g_ccmainObj->EnablePRINTERModule(true);
    if(g_ccmainObj->signature(sig))
    {
        int res=QMessageBox::information(0,"Signature","Do you want to print this signature?",QMessageBox::Yes,QMessageBox::No);
        if(res==QMessageBox::Yes)
        {
            CPrinter prn;
            prn.addImage(sig.scaledToWidth(308),false,CPrinter::eImagePrintHigh);
            prn.print();
        }
        bool ok;
        QString tempStr = QInputDialog::getText(this,"Signature","Enter file name to save",QLineEdit::Normal,"",&ok);
        if(ok)
        {
            if(!QDir("images").exists())
            {
                QDir().mkdir("images");
            }
            sig.save(QDir::currentPath() +"/images/" + tempStr.simplified() + ".png");
        }
        else
        {
            sig.save(QDir::currentPath() +"/images/signature_untitled.png");
        }
    }
    g_ccmainObj->EnablePRINTERModule(false);
    setEnabled(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_PreviewAudio()
{
//    g_ccmainObj->EnableCAMERAModule(true);
    g_ccmainObj->EnableExternalUSB(true);
    setDisable(this);
    CAudio *VoiceDlg =new CAudio();
    QByteArray voice;
    VoiceDlg->setMaxRecording(60);
//    QByteArray line;
//    QFile file("/root/welcome.wav");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    while (!file.atEnd()) {
//        line = file.readLine();
//    }
//    //        qDebug()<<"byteArray size"<<line.size();
//    if(VoiceDlg->play(line,"TESTAUDIO"))
//    {
//        QMessageBox::about(0,"Audio","Play successfully");
//    }
    //Testing
    if(VoiceDlg->record(voice, CAudio::eAudioQuality_HIGH,"Voice Recorder...."))
    {
        slot_SaveAudio(voice);
    }
    delete VoiceDlg;
    //    voice.clear();
    setEnabled(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_SaveAudio(QByteArray Data)
{
    qDebug()<<"Data Arrived"<<Data.length();
}

void MenuWindow::slot_FingerDialogCall()
{
    setDisable(this);
    Fprint *fprint=new Fprint;
    setButtonDefault(fprint);
    QMdiSubWindow *temp = MdiArea->addSubWindow(fprint,Qt::FramelessWindowHint);
    fprint->exec();
    temp->close();
    delete fprint;
    delete temp;
    setEnabled(true);
    setFocusOnLastItem();
}
void MenuWindow::delay(int nMSec)
{
    QEventLoop eventLoop;
    QTimer timerTimeout;
    timerTimeout.setInterval(nMSec);
    timerTimeout.setSingleShot(true);
    QObject::connect(&timerTimeout, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timerTimeout.start(nMSec);
    eventLoop.exec();
    timerTimeout.stop();
}
void MenuWindow::slot_PreviewCamera()
{
    setDisable(this);
    g_ccmainObj->EnableCAMERAModule(true);
    delay(100);
    /*  if(!bIsModel8x)
    {*/   /* To switch ON Camera device through Controller if device is 70/71 model*/
    g_ccmainObj->EnablePRINTERModule(true);
    if(!g_ccmainObj->EnableCAMERAModule(true))
    {
        QMessageBox::critical(0,"Camera", "Failed to switch ON CAMERA device through controller..!");
        g_ccmainObj->enableIdleMode(true);
        setEnabled(true);
        setFocusOnLastItem();
        return;
    }
    //    }
    CWebCamera *Preview=new CWebCamera();
    QImage image;
    if(Preview->previewCamera(image))
    {
        slot_ImageCaptured(image);
    }
    //    if(!bIsModel8x)
    //    {/* To switch OFF Camera device through Controller if device is 70/71 model*/
    g_ccmainObj->EnableCAMERAModule(false);
    g_ccmainObj->EnablePRINTERModule(false);
    //    }
    delete Preview;
    setEnabled(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_ImageCaptured(QImage image)
{
    bool ok;
    QTransform matrix;
    matrix.rotate(-90);

    QImage pic=image.transformed(matrix);
    int res=QMessageBox::information(0,"Image","Do you want to print this photo?",QMessageBox::Yes,QMessageBox::No);
    if(res==QMessageBox::Yes)
    {
        CPrinter prn;
        prn.addImage(pic,true,CPrinter::eImagePrintLow);
        if(!prn.print())
        {
            QMessageBox::critical(0, "Image", "Failed to print");
        }
    }
    pic=image;
    QString tempStr = QInputDialog::getText(this,"Image","Enter file name to save",QLineEdit::Normal,"",&ok);
    if(ok)
    {
        if(!QDir("images").exists())
        {
            QDir().mkdir("images");
        }
        pic.save(QDir::currentPath() +"/images/" + tempStr + ".jpg");
    }
    else
    {
        pic.save(QDir::currentPath() +"/images/camera_untitiled.jpg");
    }
}

void MenuWindow::slot_ImageViewer()
{
    setMenuHidden(true);
    Browser *w = new Browser;
    w->setFixedSize(320,460);
    w->setWindowModality(Qt::ApplicationModal);
    int ww = w->width();
    int wh = w->height();
    int dim = (ww > wh) ? wh : ww;
    dim = dim * 3 / 4;
    w->setSlideSize(QSize(3*dim/5, dim));

    QStringList files, filters;
    QDir dir = QDir::currentPath() + "/images";

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    filters << "*.png" << "*.xpm" << "*.jpg" << "*.jpeg" << "*.gif" << "*.bmp";
    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Unsorted);
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        files.append(dir.absoluteFilePath(fileInfo.fileName()));
    }

    QImage img;
    if(files.size() > 0)
    {
        for(int i = 0; i < (int)files.count(); i++)
            if(img.load(files[i]))
                w->addSlide(img);
    }
    else
    {
        img.load(":/icons/No_image.jpeg", "JPG");
        w->addSlide(img);
    }

    w->setCenterIndex(w->slideCount()/2);
    w->setBackgroundColor(Qt::white);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setWindowFlags(Qt::FramelessWindowHint);
    w->move(QPoint(0,20));
    w->show();

    QEventLoop e;
    connect(w, SIGNAL(destroyed()), &e, SLOT(quit()));
    e.exec();

    setMenuShown(true);
}

void MenuWindow::slot_PrintClick()
{
    setDisable(this);
    if(!g_loadImage)
        if (!ScreenSettings())
        {
            setEnabled(true);
            setFocusOnLastItem();
        }
    CPrinter prn;
    prn.addData("***Test Print***",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_CENTER);
    // prn.setNativeLanguage(CPrinter::e_NativeLanguage_HINDI);
    // prn.addData(QString::fromUtf8("हिंन्दी").toUtf8(),CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_LEFT);
    //prn.setNativeLanguage(CPrinter::e_NativeLanguage_KANNADA);
    // prn.addData(QString::fromUtf8("ಕನ್ನಡ").toUtf8(),CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_LEFT);
    //prn.setNativeLanguage(CPrinter::e_NativeLanguage_TAMIL);
    //prn.addData(QString::fromUtf8("தமிழ்").toUtf8(),CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_LEFT);
    //prn.setNativeLanguage(CPrinter::e_NativeLanguage_MALAYALAM);
    // prn.addData(QString::fromUtf8("മലയാളം").toUtf8(),CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_LEFT);
    prn.setNativeLanguage(CPrinter::e_NativeLanguage_NONE);
    prn.addData("--FontSmall-abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_SMALL);
    prn.addData("--FontSmall-abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn.addData("--FontSmall-abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_RIGHT);
    prn.addData("--FontSmall-abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_BOLDITALIC);
    prn.addData("--Font Med--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_MEDIUM);
    prn.addData("--Font Med--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn.addData("--Font Med--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_RIGHT);
    prn.addData("--Font Med--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_BOLDITALIC);
    prn.addData("--Font Big--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_BIG);
    prn.addData("--Font Big--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn.addData("--Font Big--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD,CPrinter::eAlignment_RIGHT);
    prn.addData("--Font Big--abcdefghijklmnopqrstuvwxyz1234567890",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLDITALIC);
    prn.addBarcode("1234567890",CPrinter::eFontSize_MEDIUM);
    prn.addData("1234567890",CPrinter::eFontSize_SMALL);
    prn.addBarcode("abcdefghijklmnopqrst",CPrinter::eFontSize_BIG);
    prn.addData("abcdefghijklmnopqrst",CPrinter::eFontSize_SMALL);
    prn.addData("ClancorTechnovates",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn.paperFeed(10);
    // if(!bIsModel8x)
    //    {   /* To switch ON Printer device through Controller if device is 70/71 model*/
    if(!g_ccmainObj->EnablePRINTERModule(true))
    {
        QMessageBox::critical(0,"Printer", "Failed to switch ON PRINTER device through controller..!");
        setEnabled(true);
        setFocusOnLastItem();
        return;
    }
    //    }
    prn.print(g_header,g_footer);
    prn.clear();
    //    if(!bIsModel8x)
    //    {/* To switch OFF Printer device through Controller if device is 70/71 model*/
    g_ccmainObj->EnablePRINTERModule(false);
    //    }
    setEnabled(true);
    setFocusOnLastItem();
}

// used to load image from Database
bool MenuWindow::ScreenSettings()
{
    QSqlQuery qrySettings(db->cn);
    //To load header & footer logo's if available
    qrySettings = db->SelectQuery("SELECT name FROM sqlite_master WHERE name='printer_setup'");
    db->clearAll();
    if(db->IsLastError())
    {
        qrySettings.clear();
        return false;
    }
    else
    {
        if(db->Size(qrySettings)>0)
        {
            qrySettings.clear();
            qrySettings = db->SelectQuery("SELECT Image_type, Image, Image_format from printer_setup");
            db->clearAll();
            if(db->IsLastError())
            {
                qrySettings.clear();
                return false;
            }
            else
            {
                CPrinter prn;
                while(qrySettings.next())
                {
                    if(qrySettings.value(0).toString() == "header")
                    {
                        QImage image;
                        if(image.loadFromData(qrySettings.value(1).toByteArray(), qrySettings.value(2).toString().toLatin1()))
                        {
                            if(!prn.loadHeaderImage(image))
                            {
                                QMessageBox::critical(0, "Load Header", "Failed to load header image to printer...");
                                return false;
                            }
                        }
                        g_header=true;
                    }
                    else if(qrySettings.value(0).toString() == "footer")
                    {
                        QImage image;
                        if(image.loadFromData(qrySettings.value(1).toByteArray(), qrySettings.value(2).toString().toLatin1()))
                        {
                            if(!prn.loadFooterImage(image))
                            {
                                QMessageBox::critical(0, "Load Footer", "Failed to load Footer image to printer...");
                                return false;
                            }
                        }
                        g_footer=true;
                    }
                }
                qrySettings.clear();
            }
        }
        else
        {
            qrySettings.clear();
            QMessageBox::critical(0, "Default Settings", "Failed to load default settings.....");
            return false;
        }
    }
    qrySettings.clear();
    g_loadImage=true;
    return true;
}

void MenuWindow::slot_WebBrowser()
{
    setDisable(this);
    setEnabled(false);
    if(!GPRSEnable())
    {
        setEnabled(true);
        setFocusOnLastItem();
        return;
    }
    qDebug()<<"Dooble start";
    process.start("Dooble",QProcess::ReadWrite);
    if(process.waitForStarted()==false)
    {
        QMessageBox::critical(0,"Browser", "Cannot start Browser");
        setEnabled(true);
        setFocusOnLastItem();
    }
    setEnabled(true);
    setFocusOnLastItem();
}
void MenuWindow::slot_Magneticcard()
{
    setMenuHidden(true);

    Dialog *magobj = new Dialog(MdiArea);
    magobj->exec();
    delete magobj;

    setMenuShown(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_Rfid()
{
    g_ccmainObj->enableIdleMode(false);
    if(!bIsModel8x)
    {   /* To switch ON RFID device through Controller if device is 70/71 model*/
        if(!g_ccmainObj->EnableRFIDModule(true))
        {
            QMessageBox::critical(0,"RFID", "Failed to switch ON RFID device through controller..!");
            g_ccmainObj->enableIdleMode(true);
            setMenuShown(true);
            setFocusOnLastItem();
            return;
        }
    }
    setMenuHidden(true);
    if(!system(QString("/etc/init.d/pcscd start").toLatin1()))
    {
        smartcard_contactless *objSCCL = new smartcard_contactless;
        objSCCL->exec();
        delete objSCCL;
        system(QString("/etc/init.d/pcscd stop").toLatin1());
        system(QString("killall pcscd").toLatin1());

    }else
    {
        system(QString("/etc/init.d/pcscd stop").toLatin1());
        QMessageBox::critical(0,"RFID", "PC/SC daemon not ready...");
    }
    if(!bIsModel8x)
    {/* To switch OFF RFID device through Controller if device is 70/71 model*/
        g_ccmainObj->EnableRFIDModule(false);
    }
    setMenuShown(true);
    g_ccmainObj->enableIdleMode(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_SmartCard()
{
    g_ccmainObj->enableIdleMode(false);
    setMenuHidden(true);
    //For testing comment below
    //    if(!bIsModel8x)
    //    {   /* To switch ON SAM device through Controller if device is 70/71 model*/
    //        if(!g_ccmainObj->EnableSAMModule(true))
    //        {
    //            QMessageBox::critical(0,"SAM/SmartCard", "Failed to switch ON SAM/SmartCard device through controller..!");
    //            g_ccmainObj->enableIdleMode(true);
    //            setMenuShown(true);
    //            setFocusOnLastItem();
    //            return;
    //        }
    //    }
    system(QString("killall pcscd").toLatin1());
    if(!system(QString("/etc/init.d/pcscd start").toLatin1()))
    {
        SmartCard *s = new SmartCard(this);
        s->exec();
        delete  s;
        system(QString("/etc/init.d/pcscd stop").toLatin1());
        system(QString("killall pcscd").toLatin1());
    }else
    {
        system(QString("/etc/init.d/pcscd stop").toLatin1());
        QMessageBox::critical(0,"SAM/SmartCard", "PC/SC daemon not ready...");
    }
    if(!bIsModel8x)
    {/* To switch OFF SAM device through Controller if device is 70/71 model*/
        g_ccmainObj->EnableSAMModule(false);
        g_ccmainObj->EnableSMARTCARDdModule(false);
    }
    g_ccmainObj->enableIdleMode(true);
    setMenuShown(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_GPS()
{
    setEnabled(false);
    g_ccmainObj->enableIdleMode(false);
    //For testing comment below
    //    if(!bIsModel8x)
    //    {   /* To switch ON GPS device through Controller if device is 70/71 model*/
    if(!g_ccmainObj->EnableGPSModule(true))
    {
        QMessageBox::critical(0,"GPS", "Failed to switch ON GPS device through controller..!");
        g_ccmainObj->enableIdleMode(true);
        setEnabled(true);
        setFocusOnLastItem();
        return;
    }
    //    }
    GPS_data *objgps = new GPS_data;
    QEventLoop e;
    connect(objgps, SIGNAL(rejected()), &e, SLOT(quit()));
    e.exec();

//    if(!bIsModel8x)
//    {/* To switch OFF GPS device through Controller if device is 70/71 model*/
//        g_ccmainObj->EnableGPSModule(false);
//    }
    g_ccmainObj->enableIdleMode(true);
    setEnabled(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_Notepad()
{
    setMenuHidden(true);
    Notepad *notepad = new Notepad(MdiArea);
    notepad->exec();
    delete notepad;

    setMenuShown(true);
    setFocusOnLastItem();
}
void MenuWindow::slot_FileCopying()
{
    setMenuHidden(true);

    FileCopy *filecopyobj = new FileCopy(MdiArea);
    filecopyobj->exec();
    delete filecopyobj;

    setMenuShown(true);
    setFocusOnLastItem();
}
void MenuWindow::slot_SystemInfo()
{
    setMenuHidden(true);

    Hadware *sysobj = new Hadware(MdiArea);
    sysobj->exec();
    delete sysobj;

    setMenuShown(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_TerminalEmulator()
{
    setMenuHidden(true);

    Emulator *sysobj = new Emulator(MdiArea);
    sysobj->exec();
    delete sysobj;

    setMenuShown(true);
    setFocusOnLastItem();
}

void MenuWindow::keyPressEvent(QKeyEvent *event)
{
//    qDebug()<<"\r Clancor menuwindow key"<<event->key()<<"keyevent"<<event;
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_F4)
    {
        g_ccmainObj->EnableExternalUSB(true);
        loadForm(NEWMENU,1);
        this->close();
        delete this;
    }
}

void MenuWindow::slot_CloseApplicaton(int,QProcess::ExitStatus)
{
    if(!DialupAutoGPRS_flag)
        g_ccmainObj->disableGprs();
    setEnabled(true);
    setFocusOnLastItem();
}

void MenuWindow::slot_MemoryStatus()
{
    setMenuHidden(true);

    DisplayMemory *sysobj = new DisplayMemory(MdiArea);
    sysobj->exec();
    delete sysobj;

    setMenuShown(true);
    setFocusOnLastItem();
}
