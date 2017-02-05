/****************************************************************************
** Meta object code from reading C++ file 'caudiomodule.h'
**
** Created: Fri Nov 29 15:24:06 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../caudiomodule.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'caudiomodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CAudioModule[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      31,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   22,   22,   22, 0x08,
      68,   22,   22,   22, 0x08,
      98,   22,   22,   22, 0x08,
     126,   22,   22,   22, 0x08,
     154,   22,   22,   22, 0x08,
     180,   22,   22,   22, 0x08,
     210,   22,   22,   22, 0x08,
     221,   22,   22,   22, 0x08,
     233,   22,   22,   22, 0x08,
     248,   22,   22,   22, 0x08,
     263,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CAudioModule[] = {
    "ClanCor::CAudioModule\0\0error()\0"
    "stopThread()\0on_timerClose_timeout()\0"
    "on_pushButtonRecord_clicked()\0"
    "on_pushButtonPlay_clicked()\0"
    "on_pushButtonStop_clicked()\0"
    "on_pushButtonOk_clicked()\0"
    "on_pushButtonCancel_clicked()\0playData()\0"
    "muteOnOff()\0updateVolume()\0displayError()\0"
    "stopProcess()\0"
};

const QMetaObject ClanCor::CAudioModule::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClanCor__CAudioModule,
      qt_meta_data_ClanCor__CAudioModule, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CAudioModule::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CAudioModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CAudioModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CAudioModule))
        return static_cast<void*>(const_cast< CAudioModule*>(this));
    return QThread::qt_metacast(_clname);
}

int ClanCor::CAudioModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: error(); break;
        case 1: stopThread(); break;
        case 2: on_timerClose_timeout(); break;
        case 3: on_pushButtonRecord_clicked(); break;
        case 4: on_pushButtonPlay_clicked(); break;
        case 5: on_pushButtonStop_clicked(); break;
        case 6: on_pushButtonOk_clicked(); break;
        case 7: on_pushButtonCancel_clicked(); break;
        case 8: playData(); break;
        case 9: muteOnOff(); break;
        case 10: updateVolume(); break;
        case 11: displayError(); break;
        case 12: stopProcess(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ClanCor::CAudioModule::error()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ClanCor::CAudioModule::stopThread()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
