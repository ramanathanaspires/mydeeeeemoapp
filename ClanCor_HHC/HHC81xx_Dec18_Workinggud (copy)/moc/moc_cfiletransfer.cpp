/****************************************************************************
** Meta object code from reading C++ file 'cfiletransfer.h'
**
** Created: Fri Nov 29 15:24:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cfiletransfer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cfiletransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CFileTransfer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   24,   23,   23, 0x08,
      59,   52,   23,   23, 0x08,
      98,   23,   23,   23, 0x08,
     124,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CFileTransfer[] = {
    "ClanCor::CFileTransfer\0\0nBytes\0"
    "bytesWritten(qint64)\0nstate\0"
    "on_checkBoxViaLanChk_stateChanged(int)\0"
    "on_pushButtonOk_clicked()\0"
    "on_pushButtonCancel_clicked()\0"
};

const QMetaObject ClanCor::CFileTransfer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClanCor__CFileTransfer,
      qt_meta_data_ClanCor__CFileTransfer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CFileTransfer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CFileTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CFileTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CFileTransfer))
        return static_cast<void*>(const_cast< CFileTransfer*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClanCor::CFileTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: on_checkBoxViaLanChk_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_pushButtonOk_clicked(); break;
        case 3: on_pushButtonCancel_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
