/****************************************************************************
** Meta object code from reading C++ file 'gps_data.h'
**
** Created: Tue Feb 11 18:10:37 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gps_data.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gps_data.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GPS_data[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,    9,    9,    9, 0x08,
      45,    9,    9,    9, 0x08,
      60,    9,    9,    9, 0x08,
      84,    9,    9,    9, 0x08,
     128,  117,    9,    9, 0x08,
     161,  156,    9,    9, 0x08,
     177,  172,    9,    9, 0x08,
     206,  197,    9,    9, 0x08,
     235,  232,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GPS_data[] = {
    "GPS_data\0\0flag\0showgpsicon(bool)\0"
    "close_dia()\0Receive_File()\0"
    "on_btnRefresh_clicked()\0"
    "on_pushButton_Download_clicked()\0"
    "done,total\0viewProgress(qint64,qint64)\0"
    "code\0reply(int)\0info\0listInfo2(QUrlInfo)\0"
    "id,error\0commandFinished(int,bool)\0"
    "id\0commandstarted(int)\0"
};

const QMetaObject GPS_data::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GPS_data,
      qt_meta_data_GPS_data, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GPS_data::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GPS_data::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GPS_data::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GPS_data))
        return static_cast<void*>(const_cast< GPS_data*>(this));
    return QDialog::qt_metacast(_clname);
}

int GPS_data::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showgpsicon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: close_dia(); break;
        case 2: Receive_File(); break;
        case 3: on_btnRefresh_clicked(); break;
        case 4: on_pushButton_Download_clicked(); break;
        case 5: viewProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: reply((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: listInfo2((*reinterpret_cast< QUrlInfo(*)>(_a[1]))); break;
        case 8: commandFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: commandstarted((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GPS_data::showgpsicon(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
