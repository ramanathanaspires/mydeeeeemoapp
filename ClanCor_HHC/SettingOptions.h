#ifndef SETTINGOPTIONS_H
#define SETTINGOPTIONS_H
#include <QDialog>
#include <QGroupBox>
#include "GlobalClass.h"
using namespace Globalclass;

class ThemeOption : public QDialog
{
    Q_OBJECT

public:
    ThemeOption(QWidget *parent = 0);
    QString style,stylesheet,oldStyle,oldStylesheet;

public slots:
    void on_styleCombo_activated(const QString &);
    void on_styleSheetCombo_activated(const QString &);

private:
    QDialogButtonBox *buttonBox;
    QComboBox *comboStyle;
    QComboBox *listviewstyleSheet;

private slots:

};

class WallpaperWnd : public QDialog
{
    Q_OBJECT

    public:
        WallpaperWnd(QWidget *parent = 0);
        bool show_WallpaperWnd();

    private:
        void keyPressEvent(QKeyEvent *event);
        QLabel *lblImage;
        QPushButton *btnOk, *btnCancel, *btnBrowse;
        QListWidget *lstWPitems;
        QStringList files;
        QString currentpath;


    private slots:
        void exitWndSlot();
        void setWallpaperSlot();
        void browseSlot();
        void setWallpaper(QModelIndex);
        void selection_changed(int row);
};

#endif // SETTINGOPTIONS_H
