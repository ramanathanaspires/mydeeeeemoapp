#ifndef FILECOPY_H
#define FILECOPY_H

//#include <QWidget>
#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class FileCopy;
}

class FileCopy : public QDialog
{
    Q_OBJECT
    
public:
    explicit FileCopy(QWidget *parent = 0);
    ~FileCopy();
     void keyPressEvent(QKeyEvent *keyevent);
     QString SourcePath,DestinationPath;
    
private slots:
    void on_pushButtonSource_clicked();

    void on_pushButtonDestination_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonRemove_clicked();

private:
    Ui::FileCopy *ui;
};

#endif // FILECOPY_H
