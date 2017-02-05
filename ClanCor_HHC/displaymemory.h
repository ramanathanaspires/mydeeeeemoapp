#ifndef DISPLAYMEMORY_H
#define DISPLAYMEMORY_H

#include <QWidget>
#include<QDialog>
#include <QKeyEvent>

namespace Ui {
    class DisplayMemory;
}

class DisplayMemory : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayMemory(QWidget *parent = 0);
    ~DisplayMemory();

private:
    Ui::DisplayMemory *ui;
    void Memory_status();
    void keyPressEvent(QKeyEvent *keyevent);

};

#endif // DISPLAYMEMORY_H
