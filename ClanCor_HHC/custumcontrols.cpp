#include "custumcontrols.h"
#include <QKeyEvent>
#include <QDebug>
#include <QApplication>
#include <unistd.h>

CToolButton::CToolButton(QWidget *parent)
    : QToolButton(parent)
{
//    setShortcut(Qt::Key_Enter);
}

//CToolButton::CToolButton(const QString title, QWidget* parent)
//        : QToolButton(parent)
//{
//    this->setTitle(title);
//}

void CToolButton::keyPressEvent(QKeyEvent *event)
{
//    qDebug()<<"in keypress event" <<Qt::Key_Return<<" "<<event->key() ;
//    if(event->key() == Qt::Key_Return)
//    {
//        qDebug()<<"\rbefore emit. "<<Qt::Key_Space;
//        QKeyEvent keyEvent(
//                QEvent::KeyPress,
//                Qt::Key_Space,
//                Qt::NoModifier,
//                " "
//                );

//        QToolButton::keyPressEvent(&keyEvent);
//        this->setFocus();
//        emit clicked();
//        return;
//    }
    QToolButton::keyPressEvent(event);
}
