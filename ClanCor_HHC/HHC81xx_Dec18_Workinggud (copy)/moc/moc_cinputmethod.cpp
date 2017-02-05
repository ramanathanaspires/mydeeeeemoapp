/****************************************************************************
** Meta object code from reading C++ file 'cinputmethod.h'
**
** Created: Fri Nov 29 15:23:51 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cinputmethod.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cinputmethod.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CInputMethod[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   23,   22,   22, 0x05,
      54,   22,   22,   22, 0x05,
      75,   22,   22,   22, 0x05,
      99,   22,   22,   22, 0x05,
     116,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     134,   22,   22,   22, 0x0a,
     147,   22,   22,   22, 0x0a,
     179,   22,   22,   22, 0x0a,
     223,  210,   22,   22, 0x0a,
     236,   22,   22,   22, 0x0a,
     252,   22,   22,   22, 0x0a,
     268,   22,   22,   22, 0x0a,
     279,   22,   22,   22, 0x0a,
     309,  293,   22,   22, 0x0a,
     334,   22,   22,   22, 0x08,
     365,   22,   22,   22, 0x08,
     395,   22,   22,   22, 0x08,
     418,   22,   22,   22, 0x08,
     448,   22,   22,   22, 0x08,
     473,   22,   22,   22, 0x08,
     488,   22,   22,   22, 0x08,
     505,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CInputMethod[] = {
    "ClanCor::CInputMethod\0\0bLocked\0"
    "keypadLockStatus(bool)\0wakeupFromIdleMode()\0"
    "wakeupFromStandbyMode()\0standbyTimeout()\0"
    "idleModeTimeout()\0resetTimer()\0"
    "on_pushButtonShutDown_clicked()\0"
    "on_pushButtonRestart_clicked()\0"
    "bFlagStandby\0wakeup(bool)\0resetKeyboard()\0"
    "closeKeyboard()\0idleMode()\0standbyMode()\0"
    "r_const_strDATA\0sendBarcodeData(QString)\0"
    "on_pushButtonStandby_clicked()\0"
    "on_pushButtonCancel_clicked()\0"
    "on_timerIdle_timeout()\0"
    "on_timerScreenUnock_timeout()\0"
    "on_timerKeypad_timeout()\0keypadLocked()\0"
    "keypadUnLocked()\0autoPowerControl()\0"
};

const QMetaObject ClanCor::CInputMethod::staticMetaObject = {
    { &QWSInputMethod::staticMetaObject, qt_meta_stringdata_ClanCor__CInputMethod,
      qt_meta_data_ClanCor__CInputMethod, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CInputMethod::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CInputMethod::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CInputMethod::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CInputMethod))
        return static_cast<void*>(const_cast< CInputMethod*>(this));
    return QWSInputMethod::qt_metacast(_clname);
}

int ClanCor::CInputMethod::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWSInputMethod::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keypadLockStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: wakeupFromIdleMode(); break;
        case 2: wakeupFromStandbyMode(); break;
        case 3: standbyTimeout(); break;
        case 4: idleModeTimeout(); break;
        case 5: resetTimer(); break;
        case 6: on_pushButtonShutDown_clicked(); break;
        case 7: on_pushButtonRestart_clicked(); break;
        case 8: wakeup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: resetKeyboard(); break;
        case 10: closeKeyboard(); break;
        case 11: idleMode(); break;
        case 12: standbyMode(); break;
        case 13: sendBarcodeData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: on_pushButtonStandby_clicked(); break;
        case 15: on_pushButtonCancel_clicked(); break;
        case 16: on_timerIdle_timeout(); break;
        case 17: on_timerScreenUnock_timeout(); break;
        case 18: on_timerKeypad_timeout(); break;
        case 19: keypadLocked(); break;
        case 20: keypadUnLocked(); break;
        case 21: autoPowerControl(); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void ClanCor::CInputMethod::keypadLockStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClanCor::CInputMethod::wakeupFromIdleMode()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ClanCor::CInputMethod::wakeupFromStandbyMode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ClanCor::CInputMethod::standbyTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ClanCor::CInputMethod::idleModeTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
