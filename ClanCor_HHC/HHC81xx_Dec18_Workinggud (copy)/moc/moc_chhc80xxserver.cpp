/****************************************************************************
** Meta object code from reading C++ file 'chhc80xxserver.h'
**
** Created: Fri Nov 29 15:23:56 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chhc80xxserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chhc80xxserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CHHC80xxServer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      48,   25,   24,   24, 0x0a,
      70,   25,   24,   24, 0x0a,
     107,   92,   24,   24, 0x09,
     161,  142,   24,   24, 0x09,
     191,  183,   24,   24, 0x09,
     241,  227,   24,   24, 0x09,
     283,  271,   24,   24, 0x09,
     313,  306,   24,   24, 0x09,
     343,  335,   24,   24, 0x09,
     366,   24,   24,   24, 0x09,
     380,   24,   24,   24, 0x09,
     401,   24,   24,   24, 0x09,
     430,   24,  425,   24, 0x09,
     447,   24,  425,   24, 0x09,
     468,  463,   24,   24, 0x09,
     482,   24,   24,   24, 0x08,
     503,   24,   24,   24, 0x08,
     517,   24,   24,   24, 0x08,
     536,   24,   24,   24, 0x08,
     553,   24,   24,   24, 0x08,
     570,   24,   24,   24, 0x08,
     596,  587,   24,   24, 0x08,
     611,   24,   24,   24, 0x08,
     627,   24,   24,   24, 0x08,
     643,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CHHC80xxServer[] = {
    "ClanCor::CHHC80xxServer\0\0"
    "r_const_strDISPLAYTEXT\0flashMessage(QString)\0"
    "popUpMessage(QString)\0eStatus,nLevel\0"
    "activeNetwork(E_NetworkStatus,int)\0"
    "nLevel,nPercentage\0batteryLevel(int,int)\0"
    "eStatus\0batteryChargeStatus(E_ChargeStatus)\0"
    "eMode,bCapsOn\0keypadMode(E_KeypadMode,bool)\0"
    "bModeLocked\0keypadModeLocked(bool)\0"
    "nLevel\0gsmNetworkSignal(int)\0bLocked\0"
    "keypadLockStatus(bool)\0showDesktop()\0"
    "wakeupFromIdleMode()\0wakeupFromStandbyMode()\0"
    "bool\0acceptIdleMode()\0acceptStandby()\0"
    "flag\0showgps(bool)\0timerFlash_timeout()\0"
    "closeBaloon()\0dateTime_clicked()\0"
    "showPercentage()\0updateCharging()\0"
    "updateDateTime()\0bMessage\0shutDown(bool)\0"
    "setNetworkApn()\0standby_click()\0"
    "idleMode_timeout()\0"
};

const QMetaObject ClanCor::CHHC80xxServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClanCor__CHHC80xxServer,
      qt_meta_data_ClanCor__CHHC80xxServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CHHC80xxServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CHHC80xxServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CHHC80xxServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CHHC80xxServer))
        return static_cast<void*>(const_cast< CHHC80xxServer*>(this));
    return QObject::qt_metacast(_clname);
}

int ClanCor::CHHC80xxServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: flashMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: popUpMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: activeNetwork((*reinterpret_cast< E_NetworkStatus(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: batteryLevel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: batteryChargeStatus((*reinterpret_cast< E_ChargeStatus(*)>(_a[1]))); break;
        case 5: keypadMode((*reinterpret_cast< E_KeypadMode(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: keypadModeLocked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: gsmNetworkSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: keypadLockStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: showDesktop(); break;
        case 10: wakeupFromIdleMode(); break;
        case 11: wakeupFromStandbyMode(); break;
        case 12: { bool _r = acceptIdleMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = acceptStandby();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: showgps((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: timerFlash_timeout(); break;
        case 16: closeBaloon(); break;
        case 17: dateTime_clicked(); break;
        case 18: showPercentage(); break;
        case 19: updateCharging(); break;
        case 20: updateDateTime(); break;
        case 21: shutDown((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: setNetworkApn(); break;
        case 23: standby_click(); break;
        case 24: idleMode_timeout(); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
