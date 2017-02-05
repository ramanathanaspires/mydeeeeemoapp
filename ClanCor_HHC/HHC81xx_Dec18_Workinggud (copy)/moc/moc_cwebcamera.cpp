/****************************************************************************
** Meta object code from reading C++ file 'cwebcamera.h'
**
** Created: Fri Nov 29 15:23:38 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cwebcamera.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cwebcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CWebCamera[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      45,   20,   20,   20, 0x08,
      69,   20,   20,   20, 0x08,
      86,   20,   20,   20, 0x08,
     117,   20,   20,   20, 0x08,
     147,   20,   20,   20, 0x08,
     157,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CWebCamera[] = {
    "ClanCor::CWebCamera\0\0on_timerClose_timeout()\0"
    "getDeviceCapabilities()\0startStopVideo()\0"
    "on_pushButtonCapture_clicked()\0"
    "on_pushButtonCancel_clicked()\0started()\0"
    "deviceDisconnected()\0"
};

const QMetaObject ClanCor::CWebCamera::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClanCor__CWebCamera,
      qt_meta_data_ClanCor__CWebCamera, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CWebCamera::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CWebCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CWebCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CWebCamera))
        return static_cast<void*>(const_cast< CWebCamera*>(this));
    return QObject::qt_metacast(_clname);
}

int ClanCor::CWebCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_timerClose_timeout(); break;
        case 1: getDeviceCapabilities(); break;
        case 2: startStopVideo(); break;
        case 3: on_pushButtonCapture_clicked(); break;
        case 4: on_pushButtonCancel_clicked(); break;
        case 5: started(); break;
        case 6: deviceDisconnected(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
