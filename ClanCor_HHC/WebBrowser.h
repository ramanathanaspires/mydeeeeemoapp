
#include <QtGui>

class QWebView;
QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class WebBrowser : public QDialog
{
    Q_OBJECT

public:
    WebBrowser();
    bool showBrowser();

protected slots:

    void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);
    void WndExitTrans();

private:
    QString jQuery;
    QWebView *view;
    QLineEdit *locationEdit;
    int progress;
};
