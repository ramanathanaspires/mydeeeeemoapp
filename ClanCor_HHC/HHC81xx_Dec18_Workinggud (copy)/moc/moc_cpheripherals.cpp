/****************************************************************************
** Meta object code from reading C++ file 'cpheripherals.h'
**
** Created: Fri Nov 29 15:23:49 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cpheripherals.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cpheripherals.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CPheripherals[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   24,   23,   23, 0x05,
      73,   65,   23,   23, 0x05,
     123,  109,   23,   23, 0x05,
     165,  153,   23,   23, 0x05,
     197,  188,   23,   23, 0x05,
     219,  212,   23,   23, 0x05,
     253,  240,   23,   23, 0x05,
     266,   23,   23,   23, 0x05,
     279,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
     293,   23,   23,   23, 0x0a,
     307,   23,   23,   23, 0x0a,
     321,   23,   23,   23, 0x0a,
     334,   23,   23,   23, 0x08,
     353,   23,   23,   23, 0x08,
     382,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CPheripherals[] = {
    "ClanCor::CPheripherals\0\0nLevel,nPercentage\0"
    "batteryLevel(int,int)\0eStatus\0"
    "batteryChargeStatus(E_ChargeStatus)\0"
    "eMode,bCapsOn\0keypadMode(E_KeypadMode,bool)\0"
    "bModeLocked\0keypadModeLocked(bool)\0"
    "bMessage\0shutdown(bool)\0bState\0"
    "volumeIncrease(bool)\0bflagStandby\0"
    "wakeup(bool)\0resetTimer()\0showDesktop()\0"
    "startThread()\0pauseThread()\0stopThread()\0"
    "updateBrightness()\0on_pushButtonPrint_clicked()\0"
    "on_pushButtonCancel_clicked()\0"
};

const QMetaObject ClanCor::CPheripherals::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClanCor__CPheripherals,
      qt_meta_data_ClanCor__CPheripherals, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CPheripherals::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CPheripherals::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CPheripherals::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CPheripherals))
        return static_cast<void*>(const_cast< CPheripherals*>(this));
    return QThread::qt_metacast(_clname);
}

int ClanCor::CPheripherals::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: batteryLevel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: batteryChargeStatus((*reinterpret_cast< E_ChargeStatus(*)>(_a[1]))); break;
        case 2: keypadMode((*reinterpret_cast< E_KeypadMode(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: keypadModeLocked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: shutdown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: volumeIncrease((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: wakeup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: resetTimer(); break;
        case 8: showDesktop(); break;
        case 9: startThread(); break;
        case 10: pauseThread(); break;
        case 11: stopThread(); break;
        case 12: updateBrightness(); break;
        case 13: on_pushButtonPrint_clicked(); break;
        case 14: on_pushButtonCancel_clicked(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ClanCor::CPheripherals::batteryLevel(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClanCor::CPheripherals::batteryChargeStatus(E_ChargeStatus _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClanCor::CPheripherals::keypadMode(E_KeypadMode _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClanCor::CPheripherals::keypadModeLocked(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClanCor::CPheripherals::shutdown(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClanCor::CPheripherals::volumeIncrease(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClanCor::CPheripherals::wakeup(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClanCor::CPheripherals::resetTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void ClanCor::CPheripherals::showDesktop()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
