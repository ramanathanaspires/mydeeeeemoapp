#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QPrinter>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QCheckBox;
class QHBoxLayout;
class QToolButton;
class QVBoxLayout;
class QPushButton;

QT_END_NAMESPACE


class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer();

private slots:
    void open();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();
    void nextclick();
    void prevclick();

private:
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void showimages(int);
    void buttonstatus();

    QMovie *movie;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QPushButton *openButton;
    QToolButton *prevButton,*nextButton,*zoomInButton,*zoomOutButton;
    QCheckBox *fitCheckBox;

    QStatusBar *buttonsLayout;
    QStringList *files;
    QString *fileName;
    double scaleFactor;
    int pathsize,i;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
};

#endif
