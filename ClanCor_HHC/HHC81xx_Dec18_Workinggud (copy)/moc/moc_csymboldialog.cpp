/****************************************************************************
** Meta object code from reading C++ file 'csymboldialog.h'
**
** Created: Fri Nov 29 15:24:13 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../csymboldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'csymboldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSymbolDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CSymbolDialog[] = {
    "CSymbolDialog\0\0on_pushButton_clicked()\0"
};

const QMetaObject CSymbolDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSymbolDialog,
      qt_meta_data_CSymbolDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSymbolDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSymbolDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSymbolDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSymbolDialog))
        return static_cast<void*>(const_cast< CSymbolDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSymbolDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_clicked(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
