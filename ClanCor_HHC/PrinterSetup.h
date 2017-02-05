#ifndef PRINTERSETUP_H
#define PRINTERSETUP_H

#include <QDialog>
#include <CPrinter>

using namespace ClanCor;

namespace Ui {
    class PrinterSetup;
}

class PrinterSetup : public QDialog
{
    Q_OBJECT

public:
    explicit PrinterSetup(QWidget *parent = 0);
    ~PrinterSetup();

private:
    Ui::PrinterSetup *ui;
    CPrinter objPrinter;
    bool header, footer;
    QByteArray imgbyte_header, imgbyte_footer;
    QString str_imgformat_header, str_imgformat_footer;

private slots:
    void on_btnFooter_revert_clicked();
    void on_btnHeader_revert_clicked();
    void on_btnFooter_clicked();
    void on_btnHeader_clicked();
    void on_buttonBox_rejected();
    void on_btnTest_print_clicked();
    void on_buttonBox_accepted();
};

#endif // PRINTERSETUP_H
