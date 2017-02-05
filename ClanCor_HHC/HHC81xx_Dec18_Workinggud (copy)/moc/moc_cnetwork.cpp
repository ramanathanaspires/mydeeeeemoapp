/****************************************************************************
** Meta object code from reading C++ file 'cnetwork.h'
**
** Created: Fri Nov 29 15:24:11 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cnetwork.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CNetwork[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      42,   19,   18,   18, 0x05,
      79,   64,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     114,   18,   18,   18, 0x0a,
     128,   18,   18,   18, 0x0a,
     148,   18,   18,   18, 0x0a,
     162,   18,   18,   18, 0x0a,
     180,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CNetwork[] = {
    "ClanCor::CNetwork\0\0r_const_strDISPLAYTEXT\0"
    "popUpMessage(QString)\0nStatus,nLevel\0"
    "activeNetwork(E_NetworkStatus,int)\0"
    "startThread()\0startThreadWakeUp()\0"
    "pauseThread()\0suspendNWThread()\0"
    "stopThread()\0"
};

const QMetaObject ClanCor::CNetwork::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClanCor__CNetwork,
      qt_meta_data_ClanCor__CNetwork, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CNetwork::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CNetwork))
        return static_cast<void*>(const_cast< CNetwork*>(this));
    return QThread::qt_metacast(_clname);
}

int ClanCor::CNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: popUpMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: activeNetwork((*reinterpret_cast< E_NetworkStatus(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: startThread(); break;
        case 3: startThreadWakeUp(); break;
        case 4: pauseThread(); break;
        case 5: suspendNWThread(); break;
        case 6: stopThread(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClanCor::CNetwork::popUpMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClanCor::CNetwork::activeNetwork(E_NetworkStatus _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
