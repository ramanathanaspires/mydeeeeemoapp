/****************************************************************************
** Meta object code from reading C++ file 'newmenu.h'
**
** Created: Tue Feb 11 18:10:05 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_newMenu[] = {

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
       9,    8,    8,    8, 0x08,
      21,    8,    8,    8, 0x08,
      34,    8,    8,    8, 0x08,
      50,   46,    8,    8, 0x08,
      82,   80,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_newMenu[] = {
    "newMenu\0\0leftclick()\0rightclick()\0"
    "mainclick()\0err\0Error(QProcess::ProcessError)\0"
    ",\0CloseApplicaton(int,QProcess::ExitStatus)\0"
};

const QMetaObject newMenu::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_newMenu,
      qt_meta_data_newMenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &newMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *newMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *newMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_newMenu))
        return static_cast<void*>(const_cast< newMenu*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int newMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: leftclick(); break;
        case 1: rightclick(); break;
        case 2: mainclick(); break;
        case 3: Error((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 4: CloseApplicaton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
