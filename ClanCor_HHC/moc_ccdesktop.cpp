/****************************************************************************
** Meta object code from reading C++ file 'ccdesktop.h'
**
** Created: Sat May 8 17:37:44 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ccdesktop.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccdesktop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCDesktop[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      27,   25,   10,   10, 0x08,
      69,   10,   10,   10, 0x08,
      85,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CCDesktop[] = {
    "CCDesktop\0\0CloseSplash()\0,\0"
    "CloseApplicaton(int,QProcess::ExitStatus)\0"
    "DataAvailable()\0Error(QProcess::ProcessError)\0"
};

const QMetaObject CCDesktop::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CCDesktop,
      qt_meta_data_CCDesktop, 0 }
};

const QMetaObject *CCDesktop::metaObject() const
{
    return &staticMetaObject;
}

void *CCDesktop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCDesktop))
        return static_cast<void*>(const_cast< CCDesktop*>(this));
    return QObject::qt_metacast(_clname);
}

int CCDesktop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: CloseSplash(); break;
        case 1: CloseApplicaton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: DataAvailable(); break;
        case 3: Error((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
