#include <QtGui>
#include "imageviewer.h"
#include "GlobalClass.h"

ImageViewer::ImageViewer()
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    imageLabel = new QLabel;
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);

    createMenus();
    setStatusBar(buttonsLayout);

    setWindowTitle(tr("Image Viewer"));
    resize(320, 240);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
}

void ImageViewer::open()
{
    files = new QStringList;
    fileName = new QString;

    fileDialog *f = new fileDialog();
    f->option = "Open";
    f->dir = "images";
    f->opnsavDialog();
    if(f->result() == QDialog::Accepted)
    {
        *fileName = f->model->rootPath() +"/" + f->txtFilename->text() ;
    }
    delete f;

    if (!fileName->isEmpty()) {
        QStringList nameFilter;
        pathsize = fileName->split("/").size();
        pathsize = pathsize -2;
        QDir dir(fileName->section("/",0,pathsize));
        nameFilter<<"*.png" << "*.xpm" << "*.jpg" << "*.jpeg" << "*.gif";

        *files = dir.entryList(nameFilter,QDir::Files,QDir::Unsorted);
        if(files->size()>1)
        {
            for(i=0;i<files->size();i++)
            {
                if(fileName->section("/",0,pathsize) + "/" + files->at(i) == fileName)
                {
                    showimages(i);
                    break;
                }
            }
        }
        buttonstatus();
    }
}

void ImageViewer::print()
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitCheckBox->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void ImageViewer::about()
{

}

void ImageViewer::createActions()
{
    connect(zoomInButton, SIGNAL(clicked()),this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()),this, SLOT(zoomIn()));
    connect(fitCheckBox, SIGNAL(clicked()), this, SLOT(fitToWindow()));
}

void ImageViewer::createMenus()
{

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QSize iconSize(20, 20);

    openButton = new QPushButton;
    openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    openButton->setIconSize(iconSize);
    openButton->setFixedSize(iconSize);
    openButton->setToolTip(tr("Open File"));
    openButton->setMenu(fileMenu);

    prevButton = new QToolButton;
    prevButton->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    prevButton->setIconSize(iconSize);
    prevButton->setFixedSize(iconSize);
    prevButton->setEnabled(false);
    prevButton->setToolTip(tr("Open File"));


    nextButton = new QToolButton;
    nextButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    nextButton->setIconSize(iconSize);
    nextButton->setFixedSize(iconSize);
    nextButton->setEnabled(false);
    nextButton->setToolTip(tr("Open File"));

    QIcon icon;
    zoomInButton = new QToolButton;
    icon.addFile(":/icons/zoomin.jpeg",iconSize);
    zoomInButton->setIcon(icon);
    zoomInButton->setEnabled(false);
    zoomInButton->setFixedSize(iconSize);
    zoomInButton->setToolTip(tr("Open File"));

    zoomOutButton = new QToolButton;
    icon.addFile(":/icons/zoomout.jpeg",iconSize);
    zoomOutButton->setIcon(icon);
    zoomOutButton->setEnabled(false);
    zoomOutButton->setFixedSize(iconSize);
    zoomOutButton->setToolTip(tr("Open File"));

    fitCheckBox = new QCheckBox(tr("Fit to Window"));
    fitCheckBox->setEnabled(false);

    buttonsLayout = new QStatusBar;
    buttonsLayout->addWidget(openButton);
    buttonsLayout->addWidget(prevButton);
    buttonsLayout->addWidget(nextButton);
    buttonsLayout->addWidget(zoomInButton);
    buttonsLayout->addWidget(zoomOutButton);
    buttonsLayout->addWidget(fitCheckBox);
    buttonsLayout->setSizeGripEnabled(false);


    connect(zoomInButton, SIGNAL(clicked()),this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()),this, SLOT(zoomOut()));
    connect(prevButton, SIGNAL(clicked()),this, SLOT(prevclick()));
    connect(nextButton, SIGNAL(clicked()),this, SLOT(nextclick()));
    connect(fitCheckBox, SIGNAL(clicked()), this, SLOT(fitToWindow()));
}

void ImageViewer::updateActions()
{
    zoomInButton->setEnabled(!fitCheckBox->isChecked());
    zoomOutButton->setEnabled(!fitCheckBox->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->movie());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->movie()->currentPixmap().size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInButton->setEnabled(scaleFactor < 3.0);
    zoomOutButton->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageViewer::nextclick()
{
    i++;
    buttonstatus();
    showimages(i);
}

void ImageViewer::prevclick()
{
    i--;
    buttonstatus();
    showimages(i);
}

void ImageViewer::showimages(int curr)
{
    movie->stop();
    imageLabel->setMovie(movie);
    movie->setFileName(fileName->section("/",0,pathsize) + "/" + files->at(curr));
    movie->start();
    scaleFactor = 1.0;

    fitCheckBox->setEnabled(true);
    updateActions();

    if (!fitCheckBox->isChecked())
        imageLabel->adjustSize();
}

void ImageViewer::buttonstatus()
{
    if (i==0 && files->size()-1==0)
    {
        prevButton->setEnabled(false);
        nextButton->setEnabled(false);
    }
    else if (i<files->size()-1 && i>0 )
    {
        prevButton->setEnabled(true);
        nextButton->setEnabled(true);
    }
    else if (i>0 && i==files->size()-1)
    {
        prevButton->setEnabled(true);
        nextButton->setEnabled(false);
    }
    else if(i==0 && i<files->size()-1)
    {
        prevButton->setEnabled(false);
        nextButton->setEnabled(true);
    }
}
