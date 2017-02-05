/****************************************************************************
** Meta object code from reading C++ file 'qmaps.h'
**
** Created: Tue Feb 11 18:11:15 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qmaps.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmaps.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Maps[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      15,    5,    5,    5, 0x0a,
      25,    5,    5,    5, 0x0a,
      32,    5,    5,    5, 0x0a,
      41,    5,    5,    5, 0x0a,
      50,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Maps[] = {
    "Maps\0\0goLeft()\0goRight()\0goUp()\0"
    "goDown()\0goHome()\0btnExitClicked()\0"
};

const QMetaObject Maps::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Maps,
      qt_meta_data_Maps, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Maps::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Maps::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Maps::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Maps))
        return static_cast<void*>(const_cast< Maps*>(this));
    return QDialog::qt_metacast(_clname);
}

int Maps::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: goLeft(); break;
        case 1: goRight(); break;
        case 2: goUp(); break;
        case 3: goDown(); break;
        case 4: goHome(); break;
        case 5: btnExitClicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
