/****************************************************************************
** Meta object code from reading C++ file 'cvolume.h'
**
** Created: Fri Nov 29 15:23:41 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cvolume.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cvolume.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CVolume[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CVolume[] = {
    "ClanCor::CVolume\0"
};

const QMetaObject ClanCor::CVolume::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClanCor__CVolume,
      qt_meta_data_ClanCor__CVolume, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CVolume::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CVolume::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CVolume::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CVolume))
        return static_cast<void*>(const_cast< CVolume*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClanCor::CVolume::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ClanCor__CVolumeSetting[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      35,   24,   24,   24, 0x08,
      90,   53,   48,   24, 0x08,
     145,  120,   24,   24, 0x08,
     187,  168,   24,   24, 0x08,
     214,  207,   24,   24, 0x08,
     229,  207,   24,   24, 0x08,
     247,   24,   24,   24, 0x08,
     260,   24,   24,   24, 0x08,
     273,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CVolumeSetting[] = {
    "ClanCor::CVolumeSetting\0\0slotVol()\0"
    "slotVolmic()\0bool\0"
    "r_const_strELEMENT,r_nVolume,r_bMute\0"
    "getVolume(QString,int&,bool&)\0"
    "r_const_strELEMENT,bMute\0"
    "slotMute(QString,bool)\0r_const_strELEMENT\0"
    "muteUnMute(QString)\0nValue\0changeVal(int)\0"
    "changeValmic(int)\0slotBtnvol()\0"
    "slotBtnmic()\0setDefault()\0"
};

const QMetaObject ClanCor::CVolumeSetting::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClanCor__CVolumeSetting,
      qt_meta_data_ClanCor__CVolumeSetting, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CVolumeSetting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CVolumeSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CVolumeSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CVolumeSetting))
        return static_cast<void*>(const_cast< CVolumeSetting*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClanCor::CVolumeSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotVol(); break;
        case 1: slotVolmic(); break;
        case 2: { bool _r = getVolume((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: slotMute((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: muteUnMute((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: changeVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: changeValmic((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: slotBtnvol(); break;
        case 8: slotBtnmic(); break;
        case 9: setDefault(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
