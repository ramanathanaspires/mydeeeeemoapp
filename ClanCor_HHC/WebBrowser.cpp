#include <QtGui>
#include <QtWebKit>
#include "WebBrowser.h"
#include "GlobalClass.h"
using namespace Globalclass;

WebBrowser::WebBrowser()
{
    progress = 0;
    view = new QWebView(this);

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    QToolBar *toolBar = new QToolBar(tr("Navigation"));//addToolBar(tr("Navigation"));
    toolBar->setFixedSize(320,25);
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    QPushButton *quitbutton = new QPushButton("X");
    quitbutton->setFlat(true);
    quitbutton->setFocusPolicy(Qt::NoFocus);
    quitbutton->setFixedSize(20,20);
    toolBar->addWidget(quitbutton);
    toolBar->addWidget(locationEdit);
    toolBar->setMovable(false);
//menuBar()->setFixedSize(320,15);
//    QMenu *effectMenu = menuBar()->addMenu(tr("&Effect"));
//    effectMenu->addAction("Highlight all links", this, SLOT(highlightAllLinks()));
//
//    rotateAction = new QAction(this);
//    //rotateAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogDetailedView));
//    //rotateAction->setCheckable(true);
//    rotateAction->setText(tr("Turn images upside down"));
//    connect(rotateAction, SIGNAL(toggled(bool)), this, SLOT(rotateImages(bool)));
//    effectMenu->addAction(rotateAction);
//
//    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
//    toolsMenu->addAction(tr("Remove GIF images"), this, SLOT(removeGifImages()));
//    toolsMenu->addAction(tr("Remove all inline frames"), this, SLOT(removeInlineFrames()));
//    toolsMenu->addAction(tr("Remove all object elements"), this, SLOT(removeObjectElements()));
//    toolsMenu->addAction(tr("Remove all embedded elements"), this, SLOT(removeEmbeddedElements()));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(const QString&)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
    connect(quitbutton,SIGNAL(clicked()),SLOT(WndExitTrans()));
    //quitbutton->setShortcut(Qt::Key_Escape);
   setFixedSize(320,240);
    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(toolBar);
    v->addWidget(view);
    v->setMargin(0);
    v->setSpacing(0);
    setLayout(v);
//    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    setUnifiedTitleAndToolBarOnMac(true);
    setWindowModality(Qt::ApplicationModal);
}

bool WebBrowser::showBrowser()
{
    if(!GPRSEnable())
    {
        return false;
    }
//    show();
//    qApp->processEvents();
    view->load(QUrl("http://m.google.com"));
    return true;
}


void WebBrowser::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void WebBrowser::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->setEnabled(false);
    locationEdit->setEnabled(false);
    view->load(url);
    view->setFocus();
}

void WebBrowser::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void WebBrowser::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

void WebBrowser::finishLoading(bool)
{
    view->show();
    view->setEnabled(true);
    locationEdit->setEnabled(true);
    progress = 100;
    adjustTitle();
}

void WebBrowser::WndExitTrans()
{
    GPRS->DisableGPRS();
    view->stop();
    view->close();
    this->close();
}


