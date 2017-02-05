/****************************************************************************
** Meta object code from reading C++ file 'smartcard_contactless.h'
**
** Created: Tue Feb 11 18:10:58 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../smartcard_contactless.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smartcard_contactless.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_smartcard_contactless[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      43,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_smartcard_contactless[] = {
    "smartcard_contactless\0\0slot_stateChanged()\0"
    "slotclose()\0"
};

const QMetaObject smartcard_contactless::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_smartcard_contactless,
      qt_meta_data_smartcard_contactless, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &smartcard_contactless::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *smartcard_contactless::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *smartcard_contactless::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_smartcard_contactless))
        return static_cast<void*>(const_cast< smartcard_contactless*>(this));
    return QDialog::qt_metacast(_clname);
}

int smartcard_contactless::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_stateChanged(); break;
        case 1: slotclose(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_SC_CLthread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      29,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SC_CLthread[] = {
    "SC_CLthread\0\0state_changed()\0error_close()\0"
    "thread_terminate()\0"
};

const QMetaObject SC_CLthread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SC_CLthread,
      qt_meta_data_SC_CLthread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SC_CLthread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SC_CLthread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SC_CLthread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SC_CLthread))
        return static_cast<void*>(const_cast< SC_CLthread*>(this));
    return QThread::qt_metacast(_clname);
}

int SC_CLthread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: state_changed(); break;
        case 1: error_close(); break;
        case 2: thread_terminate(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SC_CLthread::state_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SC_CLthread::error_close()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
