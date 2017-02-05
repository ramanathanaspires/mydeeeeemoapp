/****************************************************************************
** Meta object code from reading C++ file 'wifi_conf.h'
**
** Created: Tue Feb 11 18:10:47 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wifi_conf.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wifi_conf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WIFI_Conf[] = {

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
      17,   11,   10,   10, 0x08,
      59,   10,   10,   10, 0x08,
      82,   10,   10,   10, 0x08,
     101,   10,   10,   10, 0x08,
     114,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WIFI_Conf[] = {
    "WIFI_Conf\0\0index\0"
    "on_cmbEncryption_currentIndexChanged(int)\0"
    "on_BtnCancel_clicked()\0on_BtnOk_clicked()\0"
    "makeEnable()\0on_BtnON_OFF_clicked()\0"
};

const QMetaObject WIFI_Conf::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WIFI_Conf,
      qt_meta_data_WIFI_Conf, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WIFI_Conf::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WIFI_Conf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WIFI_Conf::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WIFI_Conf))
        return static_cast<void*>(const_cast< WIFI_Conf*>(this));
    return QDialog::qt_metacast(_clname);
}

int WIFI_Conf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cmbEncryption_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_BtnCancel_clicked(); break;
        case 2: on_BtnOk_clicked(); break;
        case 3: makeEnable(); break;
        case 4: on_BtnON_OFF_clicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
