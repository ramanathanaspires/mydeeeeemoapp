#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "GlobalClass.h"
#include <strings.h>
using namespace Globalclass;

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QString htmlstring;
    QString stringModel;
    QString Pic32Version;
    QString Pic32DT;
    QString BUILDVERSION;
    QString BUILDDATE;
    QString GSMMODULE_VERSION;
    GSMMODULE_VERSION=g_ccmainObj->gsm_ModuleVersion();
    CHHC80xx::version(BUILDVERSION,BUILDDATE);
    g_ccmainObj->coProcessorVersion(Pic32Version,Pic32DT);

    stringModel = g_ccmainObj->deviceModel();
    htmlstring="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
            "p, li { white-space: pre-wrap; }"
            "</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">"
            "<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">"
            "<tr>"
            "<td style=\"border: none;\">"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Device Model : </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + g_ccmainObj->deviceModel()  + "</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Machine Id : </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + g_ccmainObj->machineId() + "</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">==========================</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">ClanCor_HHC Version </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + RELEASEVERSION + "</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Build Date : </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + RELEASEDATE + "</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">==========================</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">" + stringModel + " SDK Version </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + BUILDVERSION + "</span><span style=\" font-size:9pt; color:#0055ff;\"> </span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Build Date : </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + BUILDDATE + "</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">==========================</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Co-processor Version </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + Pic32Version + "</span><span style=\" font-size:9pt; color:#0055ff;\"> </span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">Build Date : </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + Pic32DT + "</span></p></td></tr></table></body></html>";
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#000000;\">==========================</span></p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; color:#0055ff;\">GSM Module Version </span><span style=\" font-size:9pt; font-weight:600; color:#000000;\">" + GSMMODULE_VERSION + "</span><span style=\" font-size:9pt; color:#0055ff;\"> </span></p>";
    ui->textEdit->setHtml(htmlstring);
    ui->textEdit->setReadOnly(true);
    setWindowFlags(Qt::FramelessWindowHint);
    move(0,20);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    close();
}
