/****************************************************************************
** Meta object code from reading C++ file 'SettingOptions.h'
**
** Created: Tue Feb 11 18:09:56 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SettingOptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingOptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThemeOption[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      46,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ThemeOption[] = {
    "ThemeOption\0\0on_styleCombo_activated(QString)\0"
    "on_styleSheetCombo_activated(QString)\0"
};

const QMetaObject ThemeOption::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ThemeOption,
      qt_meta_data_ThemeOption, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ThemeOption::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ThemeOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ThemeOption::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThemeOption))
        return static_cast<void*>(const_cast< ThemeOption*>(this));
    return QDialog::qt_metacast(_clname);
}

int ThemeOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_styleCombo_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: on_styleSheetCombo_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_WallpaperWnd[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      28,   13,   13,   13, 0x08,
      47,   13,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,
      90,   86,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WallpaperWnd[] = {
    "WallpaperWnd\0\0exitWndSlot()\0"
    "setWallpaperSlot()\0browseSlot()\0"
    "setWallpaper(QModelIndex)\0row\0"
    "selection_changed(int)\0"
};

const QMetaObject WallpaperWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WallpaperWnd,
      qt_meta_data_WallpaperWnd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WallpaperWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WallpaperWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WallpaperWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WallpaperWnd))
        return static_cast<void*>(const_cast< WallpaperWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int WallpaperWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: exitWndSlot(); break;
        case 1: setWallpaperSlot(); break;
        case 2: browseSlot(); break;
        case 3: setWallpaper((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: selection_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
