
#ifndef CSIGNATURE_H
#define CSIGNATURE_H

#include <QDir>
#include <QDialog>
#include <QStringList>
#include <QThread>
#include <QColor>
#include <QImage>
#include <QPainterPath>
#include <QWidget>
#include <QMutexLocker>
#include <QComboBox>
#include <QListView>
#include <QTreeView>
#include <QFileSystemModel>

extern "C"
{
    #include "tslib.h"
//    #include "fbutils.h"
}
QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QScrollArea;
QT_END_NAMESPACE

namespace ClanCor
{
    class CPaintPanel: public QWidget
    {
        Q_OBJECT

    public:
        CPaintPanel(QWidget *parent = 0);

        QImage image() const { return theImage; }
        QColor brushColor() const { return color; }
        int brushWidth() const { return thickness; }
        QSize sizeHint() const;
        QImage theImage;

        static int oldx,oldy;

    protected:
        void paintEvent(QPaintEvent *event);

    private:

        QColor color;
        int thickness;


        QPoint lastPos;
        QMutex *mutex;

    public slots:
        void draw(int,int,unsigned long);
    };

    class CThreadSignature : public QThread
    {
        Q_OBJECT
    public:
        CThreadSignature();
        void run();

        bool active,sigenable;
    signals:
        void sigEnable(bool);
    private:
        struct tsdev *ts;

        int ti,x,y,tmp,dx,dy,x1,y1,x2,y2;
        QTimer *timer;
        unsigned int mode;
        int flag,ret;
        QMutex mutex;

        void line1(int,int,int,int,unsigned);

    private slots:
        void refreshval();
    };

    class CSignature : public QDialog
    {
        Q_OBJECT

    public:
        CSignature();
        CPaintPanel *paintpanel;
        bool Saved;
        QImage Image;
    private slots:
        void clearImage();
        void save();
    public slots:
        void exitSig();
    private:
        QTimer *timer;
        CThreadSignature *t;
        QPushButton *pSave;

        QDir pluginsDir;

    };
}
#endif
