#include "ccdesktop.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    Q_INIT_RESOURCE(logo);
    CCDesktop w;
    return a.exec();
}
