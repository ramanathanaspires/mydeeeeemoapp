/****************************************************************************
** Meta object code from reading C++ file 'PrinterSetup.h'
**
** Created: Tue Feb 11 18:10:39 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PrinterSetup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrinterSetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PrinterSetup[] = {

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
      14,   13,   13,   13, 0x08,
      44,   13,   13,   13, 0x08,
      74,   13,   13,   13, 0x08,
      97,   13,   13,   13, 0x08,
     120,   13,   13,   13, 0x08,
     144,   13,   13,   13, 0x08,
     171,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PrinterSetup[] = {
    "PrinterSetup\0\0on_btnFooter_revert_clicked()\0"
    "on_btnHeader_revert_clicked()\0"
    "on_btnFooter_clicked()\0on_btnHeader_clicked()\0"
    "on_buttonBox_rejected()\0"
    "on_btnTest_print_clicked()\0"
    "on_buttonBox_accepted()\0"
};

const QMetaObject PrinterSetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PrinterSetup,
      qt_meta_data_PrinterSetup, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PrinterSetup::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PrinterSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PrinterSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PrinterSetup))
        return static_cast<void*>(const_cast< PrinterSetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int PrinterSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_btnFooter_revert_clicked(); break;
        case 1: on_btnHeader_revert_clicked(); break;
        case 2: on_btnFooter_clicked(); break;
        case 3: on_btnHeader_clicked(); break;
        case 4: on_buttonBox_rejected(); break;
        case 5: on_btnTest_print_clicked(); break;
        case 6: on_buttonBox_accepted(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
