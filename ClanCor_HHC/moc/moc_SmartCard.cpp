/****************************************************************************
** Meta object code from reading C++ file 'SmartCard.h'
**
** Created: Tue Feb 11 18:10:35 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartCard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SmartCard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SmartCard[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      32,   10,   10,   10, 0x08,
      54,   10,   10,   10, 0x08,
      86,   10,   10,   10, 0x08,
     120,   10,   10,   10, 0x08,
     149,   10,   10,   10, 0x08,
     189,  183,   10,   10, 0x08,
     232,   10,   10,   10, 0x08,
     254,  183,   10,   10, 0x08,
     277,   10,   10,   10, 0x08,
     301,  294,  289,   10, 0x08,
     325,  294,  289,   10, 0x08,
     354,  350,  289,   10, 0x08,
     419,   10,   10,   10, 0x08,
     446,   10,   10,   10, 0x08,
     480,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SmartCard[] = {
    "SmartCard\0\0on_btnSave_clicked()\0"
    "on_btnClose_clicked()\0"
    "txt_UserID_textChanged(QString)\0"
    "txt_UserName_textChanged(QString)\0"
    "txtCity_textChanged(QString)\0"
    "txt_MobileNo_textChanged(QString)\0"
    "index\0on_cmb_ReaderName_currentIndexChanged(int)\0"
    "on_btn_Read_clicked()\0slot_stateChanged(int)\0"
    "slotclose()\0bool\0Reader\0Read_SmartCard(QString)\0"
    "Write_SmartCard(QString)\0,,,\0"
    "PerformTransmitAPDU(SCARDHANDLE,LPCSCARD_IO_REQUEST,BYTE*,ulong)\0"
    "on_pushButtonSam_clicked()\0"
    "on_pushButtonSmartcard1_clicked()\0"
    "on_pushButtonSmartcard2_clicked()\0"
};

const QMetaObject SmartCard::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SmartCard,
      qt_meta_data_SmartCard, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SmartCard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SmartCard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SmartCard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SmartCard))
        return static_cast<void*>(const_cast< SmartCard*>(this));
    return QDialog::qt_metacast(_clname);
}

int SmartCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_btnSave_clicked(); break;
        case 1: on_btnClose_clicked(); break;
        case 2: txt_UserID_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: txt_UserName_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: txtCity_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: txt_MobileNo_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: on_cmb_ReaderName_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: on_btn_Read_clicked(); break;
        case 8: slot_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: slotclose(); break;
        case 10: { bool _r = Read_SmartCard((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = Write_SmartCard((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = PerformTransmitAPDU((*reinterpret_cast< SCARDHANDLE(*)>(_a[1])),(*reinterpret_cast< LPCSCARD_IO_REQUEST(*)>(_a[2])),(*reinterpret_cast< BYTE*(*)>(_a[3])),(*reinterpret_cast< ulong(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: on_pushButtonSam_clicked(); break;
        case 14: on_pushButtonSmartcard1_clicked(); break;
        case 15: on_pushButtonSmartcard2_clicked(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
static const uint qt_meta_data_SC_thread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,
      36,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   10,   10,   10, 0x0a,
      65,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SC_thread[] = {
    "SC_thread\0\0index\0state_changed(int)\0"
    "error_close()\0thread_start()\0"
    "thread_terminate()\0"
};

const QMetaObject SC_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SC_thread,
      qt_meta_data_SC_thread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SC_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SC_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SC_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SC_thread))
        return static_cast<void*>(const_cast< SC_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int SC_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: state_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: error_close(); break;
        case 2: thread_start(); break;
        case 3: thread_terminate(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SC_thread::state_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SC_thread::error_close()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
