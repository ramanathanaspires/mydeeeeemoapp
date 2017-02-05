#ifndef EMULATOR_H
#define EMULATOR_H

#include <QDialog>
#include<QProcess>
#include <QKeyEvent>

namespace Ui {
class Emulator;
}

class Emulator : public QDialog
{
    Q_OBJECT
    
public:
    explicit Emulator(QWidget *parent = 0);
    QString commandexe;
    QProcess *process;
    ~Emulator();
    void keyPressEvent(QKeyEvent *e);
    
private slots:
    void on_lineEdit_returnPressed();

private:
    Ui::Emulator *ui;
};

#endif // EMULATOR_H
