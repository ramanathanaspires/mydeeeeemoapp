#ifndef CUSTUMCONTROLS_H
#define CUSTUMCONTROLS_H
#include <QToolButton>

class CToolButton: public QToolButton
{
    Q_OBJECT
public:
    explicit CToolButton(QWidget *parent = 0);
//    explicit CToolButton(const QString title, QWidget* parent=0);
    ~CToolButton(){};
private:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CUSTUMCONTROLS_H
