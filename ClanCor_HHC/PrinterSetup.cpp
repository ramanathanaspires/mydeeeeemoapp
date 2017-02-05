#include "PrinterSetup.h"
#include "ui_PrinterSetup.h"
#include "GlobalClass.h"
using namespace Globalclass;

PrinterSetup::PrinterSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrinterSetup)
{
    ui->setupUi(this);
    setParent(MdiArea);
    setWindowTitle("Printer setup");
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::NoFocus);
    header = false;
    footer = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ok");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setShortcut(Qt::Key_F2);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setShortcut(Qt::Key_F4);
    QSqlQuery qry_printer_setup;
    qry_printer_setup = db->SelectQuery("select * from sqlite_master where name like 'printer_setup'");
    db->clearAll();
    if(db->IsLastError())
    {
        qry_printer_setup.clear();
        ui->btnHeader->setFocus();
        return;
    }
    if(qry_printer_setup.next())
    {
        qry_printer_setup.clear();
        qry_printer_setup = db->SelectQuery("select * from printer_setup");
        db->clearAll();
        if(db->IsLastError())
        {
            qry_printer_setup.clear();
            ui->btnHeader->setFocus();
            return;
        }
        if(db->Size(qry_printer_setup) > 0)
        {
            qry_printer_setup.seek(-1);
            while(qry_printer_setup.next())
            {
                if(qry_printer_setup.value(0).toString() == "header")
                {
                    QIcon icon;
                    imgbyte_header = qry_printer_setup.value(1).toByteArray();
                    icon.addPixmap(QPixmap::fromImage(QImage::fromData(imgbyte_header, qry_printer_setup.value(2).toString().toLatin1())));
                    ui->btnHeader->setIconSize(QSize(250, 50));
                    ui->btnHeader->setIcon(icon);
                    header = true;
                }
                else if(qry_printer_setup.value(0).toString() == "footer")
                {
                    QIcon icon;
                    imgbyte_footer = qry_printer_setup.value(1).toByteArray();
                    icon.addPixmap(QPixmap::fromImage(QImage::fromData(imgbyte_footer, qry_printer_setup.value(2).toString().toLatin1())));
                    ui->btnFooter->setIconSize(QSize(250, 50));
                    ui->btnFooter->setIcon(icon);
                    footer = true;
                }
            }
            if(!header)
                ui->btnHeader->setText("Header Image not Loaded..\n(Please click here to load)");
            if(!footer)
                ui->btnFooter->setText("Footer Image not Loaded..\n(Please click here to load)");
        }
        else
        {
            ui->btnHeader->setText("Header Image not Loaded..\n(Please click here to load)");
            ui->btnFooter->setText("Footer Image not Loaded..\n(Please click here to load)");
        }
    }
    else
    {
        QMessageBox::critical(0, "Printer", "Failed to Load default settings...");
        ui->btnHeader->setFocus();
        return;
    }
    ui->btnHeader->setFocus();
}

PrinterSetup::~PrinterSetup()
{
    delete ui;
}

void PrinterSetup::on_buttonBox_accepted()
{
    setEnabled(false);
    if(!db->DataBaseCommand("delete from printer_setup"))
    {
        QMessageBox::critical(0,"Printer","Failed to save settings");
        imgbyte_header.clear();
        imgbyte_footer.clear();
        str_imgformat_header.clear();
        str_imgformat_footer.clear();
        setEnabled(true);
        return;
    }
    if(header)
    {
        QSqlQuery rs(db->cn);
        rs.prepare("INSERT INTO printer_setup(Image_type , Image , Image_format)VALUES('header',?, '" + str_imgformat_header + "')");
        rs.addBindValue(imgbyte_header);
        if(!rs.exec())
        {
            QMessageBox::critical(0,"Printer","Failed to save settings");
            imgbyte_header.clear();
            imgbyte_footer.clear();
            str_imgformat_header.clear();
            str_imgformat_footer.clear();
            setEnabled(true);
            return;
        }
        rs.clear();
        QImage img = QImage::fromData( imgbyte_header, str_imgformat_header.toLatin1());
        objPrinter.loadHeaderImage( img );
        g_header=true;
    }
    else
    {
        g_header=false;
    }
    if(footer)
    {
        QSqlQuery rs(db->cn);
        rs.prepare("INSERT INTO printer_setup(Image_type , Image , Image_format)VALUES('footer',?, '" + str_imgformat_footer + "')");
        rs.addBindValue(imgbyte_footer);
        if(!rs.exec())
        {
           QMessageBox::critical(0,"Printer","Failed to save settings");
            imgbyte_header.clear();
            imgbyte_footer.clear();
            str_imgformat_header.clear();
            str_imgformat_footer.clear();
            setEnabled(true);
            return;
        }
        rs.clear();
        QImage img = QImage::fromData( imgbyte_footer, str_imgformat_footer.toLatin1());
        objPrinter.loadFooterImage( img );
        g_footer=true;
    }
    else
    {
        g_footer=false;
    }
    imgbyte_header.clear();
    imgbyte_footer.clear();
    str_imgformat_header.clear();
    str_imgformat_footer.clear();
    setEnabled(true);
}

void PrinterSetup::on_buttonBox_rejected()
{
    setEnabled(false);
    imgbyte_header.clear();
    imgbyte_footer.clear();
    str_imgformat_header.clear();
    str_imgformat_footer.clear();
    setEnabled(true);
}

void PrinterSetup::on_btnTest_print_clicked()
{
    setEnabled(false);
    if(header)
    {
        QImage img = QImage::fromData( imgbyte_header, str_imgformat_header.toLatin1());
        objPrinter.loadHeaderImage( img );
    }
    if(footer)
    {
        QImage img = QImage::fromData( imgbyte_footer, str_imgformat_footer.toLatin1());
        objPrinter.loadFooterImage( img );
    }
    if(!g_ccmainObj->EnablePRINTERModule(true))
    {
        QMessageBox::critical(0,"Printer", "Failed to enable Printer Module..!");
        return;
    }
    CPrinter *prn=new CPrinter();
    prn->drawLine();
    prn->addData("***Test Print***",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD);
    prn->drawLine();
    prn->addData("Font Small",CPrinter::eFontSize_SMALL);
    prn->addData("Font Small",CPrinter::eFontSize_SMALL);
    prn->addData("Font Small-BoldItalic",CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_BOLDITALIC);
    prn->addData("Font Small-Bold",CPrinter::eFontSize_SMALL,CPrinter::eFontStyle_BOLD);
    prn->addData("Font Med",CPrinter::eFontSize_MEDIUM);
    prn->addData("Font Med-BoldItalic",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_BOLDITALIC);prn->addData("Font Med",CPrinter::eFontSize_MEDIUM);
    prn->addData("Font Med-Italic-center",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn->addData("Font Big",CPrinter::eFontSize_BIG);
    prn->addData("Font Big-BoldItalic-Center",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLDITALIC,CPrinter::eAlignment_CENTER);
    prn->addData("Font Big-Bold",CPrinter::eFontSize_BIG,CPrinter::eFontStyle_BOLD);
    prn->drawLine();
    prn->addBarcode("1234567890",CPrinter::eFontSize_MEDIUM);
    prn->drawLine();
    prn->addData("Vaaraahi Embedded",CPrinter::eFontSize_MEDIUM,CPrinter::eFontStyle_ITALIC,CPrinter::eAlignment_CENTER);
    prn->drawLine();

    prn->print(header,footer);
    delete prn;
    setEnabled(true);
    ui->buttonBox->button(ui->buttonBox->Ok)->setFocus();
}

void PrinterSetup::on_btnHeader_clicked()
{
    setEnabled(false);
    QString filename;
    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->filters<< "*.png" << "*.jpg" << "*.jpeg" <<  "*.bmp";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        filename = f->path + "/" + f->txtFilename->text() ;

        if(!QFile::exists(filename))
        {
            QMessageBox::critical(0, "FileOpen", "Failed to open file..\n Unable to load header image");
            setEnabled(true);
            return;
        }

        str_imgformat_header = QFileInfo(filename).completeSuffix();

        QImage image(filename, str_imgformat_header.toLatin1());
        if(image.width() > 384 && image.height() > 50)
        {
            QImage imgtmp;
            imgtmp = image.copy(0, 0, 384, 50);
            image = imgtmp;
        }
        else if(image.width() > 384 || image.height() > 50)
        {
            if(image.width() > 384)
            {
                QImage imgtmp;
                imgtmp = image.copy(0, 0, 384, image.height());
                image = imgtmp;
            }
            else if(image.height() > 50)
            {
                QImage imgtmp;
                imgtmp = image.copy(0, 0, image.width(), 50);
                image = imgtmp;
            }
        }
        ui->btnHeader->setText("");
        QIcon icon;
        icon.addPixmap(QPixmap::fromImage(image));
        ui->btnHeader->setIcon(icon);
        ui->btnHeader->setIconSize(QSize(250, 50));
        QBuffer buffer(&imgbyte_header);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, str_imgformat_header.toLatin1());
        header = true;
    }
    f->filters.clear();
    delete f;
    setEnabled(true);
    ui->btnFooter->setFocus();
}

void PrinterSetup::on_btnFooter_clicked()
{
    setEnabled(false);
    QString filename;
    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->filters<< "*.png" << "*.jpg" << "*.jpeg" <<  "*.bmp";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        filename = f->path +"/" + f->txtFilename->text() ;

        if(!QFile::exists(filename))
        {
            QMessageBox::critical(0, "File open", "Failed to open file..\n Unable to load header image");
            setEnabled(true);
            return;
        }

        str_imgformat_footer = QFileInfo(filename).completeSuffix();

        QImage image(filename, str_imgformat_footer.toLatin1());
        if(image.width() > 384 && image.height() > 50)
        {
            QImage imgtmp;
            imgtmp = image.copy(0, 0, 384, 50);
            image = imgtmp;
        }
        else if(image.width() > 384 || image.height() > 50)
        {
            if(image.width() > 384)
            {
                QImage imgtmp;
                imgtmp = image.copy(0, 0, 384, image.height());
                image = imgtmp;
            }
            else if(image.height() > 50)
            {
                QImage imgtmp;
                imgtmp = image.copy(0, 0, image.width(), 50);
                image = imgtmp;
            }
        }
        ui->btnFooter->setText("");
        QIcon icon;
        icon.addPixmap(QPixmap::fromImage(image));
        ui->btnFooter->setIcon(icon);
        ui->btnFooter->setIconSize(QSize(250, 50));
        QBuffer buffer(&imgbyte_footer);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, str_imgformat_footer.toLatin1());
        footer = true;
    }
    f->filters.clear();
    delete f;
    setEnabled(true);
    ui->btnTest_print->setFocus();
}

void PrinterSetup::on_btnHeader_revert_clicked()
{
    setEnabled(false);
    QImage img_empty;
    QIcon icon;
    ui->btnHeader->setIcon(icon);
    ui->btnHeader->setIconSize(QSize(250, 50));
    ui->btnHeader->setText("Header Image not Loaded..\n(Please click here to load)");
    header = false;
    setEnabled(true);
    ui->btnHeader->setFocus();
}

void PrinterSetup::on_btnFooter_revert_clicked()
{
    setEnabled(false);
    QIcon icon;
    ui->btnFooter->setIcon(icon);
    ui->btnFooter->setIconSize(QSize(250, 50));
    ui->btnFooter->setText("Footer Image not Loaded..\n(Please click here to load)");
    footer = false;
    setEnabled(true);
    ui->btnFooter->setFocus();
}
