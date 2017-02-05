/****************************************************************************
** Meta object code from reading C++ file 'gadgets.h'
**
** Created: Tue Feb 11 18:11:09 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gadgets.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gadgets.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GADGETS[] = {

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
       9,    8,    8,    8, 0x08,
      35,    8,    8,    8, 0x08,
      64,    8,    8,    8, 0x08,
      88,    8,    8,    8, 0x08,
     119,    8,    8,    8, 0x08,
     150,    8,    8,    8, 0x08,
     182,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GADGETS[] = {
    "GADGETS\0\0on_pushButtonOk_clicked()\0"
    "on_pushButtonUsbIp_clicked()\0"
    "on_pushButton_clicked()\0"
    "on_pushButtonusbExit_clicked()\0"
    "on_lineEditUsb_returnPressed()\0"
    "on_lineEditHost_returnPressed()\0"
    "on_pushButtonUSBONOFF_clicked()\0"
};

const QMetaObject GADGETS::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GADGETS,
      qt_meta_data_GADGETS, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GADGETS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GADGETS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GADGETS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GADGETS))
        return static_cast<void*>(const_cast< GADGETS*>(this));
    return QDialog::qt_metacast(_clname);
}

int GADGETS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButtonOk_clicked(); break;
        case 1: on_pushButtonUsbIp_clicked(); break;
        case 2: on_pushButton_clicked(); break;
        case 3: on_pushButtonusbExit_clicked(); break;
        case 4: on_lineEditUsb_returnPressed(); break;
        case 5: on_lineEditHost_returnPressed(); break;
        case 6: on_pushButtonUSBONOFF_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
