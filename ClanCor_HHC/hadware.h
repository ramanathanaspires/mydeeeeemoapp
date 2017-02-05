#ifndef HADWARE_H
#define HADWARE_H

#include <QDialog>
#include <QKeyEvent>
namespace Ui {
class Hadware;
}

class Hadware : public QDialog
{
    Q_OBJECT
    
public:
    explicit Hadware(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyevent);
    ~Hadware();
    
private slots:
    void on_pushButtonPrint_clicked();
private:
    Ui::Hadware *ui;
};

#endif // HADWARE_H
