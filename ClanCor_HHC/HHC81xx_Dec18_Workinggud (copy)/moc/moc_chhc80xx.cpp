/****************************************************************************
** Meta object code from reading C++ file 'chhc80xx.h'
**
** Created: Fri Nov 29 15:23:58 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chhc80xx.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chhc80xx.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CHHC80xx[] = {

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
      26,   19,   18,   18, 0x08,
      47,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CHHC80xx[] = {
    "ClanCor::CHHC80xx\0\0bState\0"
    "volumeIncrease(bool)\0volumeGui_timeout()\0"
};

const QMetaObject ClanCor::CHHC80xx::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClanCor__CHHC80xx,
      qt_meta_data_ClanCor__CHHC80xx, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CHHC80xx::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CHHC80xx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CHHC80xx::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CHHC80xx))
        return static_cast<void*>(const_cast< CHHC80xx*>(this));
    return QObject::qt_metacast(_clname);
}

int ClanCor::CHHC80xx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: volumeIncrease((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: volumeGui_timeout(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
