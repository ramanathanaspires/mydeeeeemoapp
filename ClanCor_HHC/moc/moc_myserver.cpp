/****************************************************************************
** Meta object code from reading C++ file 'myserver.h'
**
** Created: Tue Feb 11 18:10:51 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../myserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyServer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,    9,    9,    9, 0x08,
      40,    9,    9,    9, 0x08,
      57,    9,    9,    9, 0x08,
      74,    9,    9,    9, 0x08,
      91,    9,    9,    9, 0x08,
     111,  104,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyServer[] = {
    "MyServer\0\0EnableGPRS()\0DateTime_Click()\0"
    "showPercentage()\0updateCharging()\0"
    "updateDateTime()\0GPRS_Click()\0action\0"
    "menu_option_selected(QAction*)\0"
};

const QMetaObject MyServer::staticMetaObject = {
    { &CHHC80xxServer::staticMetaObject, qt_meta_stringdata_MyServer,
      qt_meta_data_MyServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyServer))
        return static_cast<void*>(const_cast< MyServer*>(this));
    return CHHC80xxServer::qt_metacast(_clname);
}

int MyServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CHHC80xxServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: EnableGPRS(); break;
        case 1: DateTime_Click(); break;
        case 2: showPercentage(); break;
        case 3: updateCharging(); break;
        case 4: updateDateTime(); break;
        case 5: GPRS_Click(); break;
        case 6: menu_option_selected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MyServer::EnableGPRS()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
