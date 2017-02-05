/****************************************************************************
** Meta object code from reading C++ file 'patchupdates.h'
**
** Created: Tue Feb 11 18:11:24 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../patchupdates.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patchupdates.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Patchupdates[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      31,   13,   13,   13, 0x08,
      68,   13,   13,   13, 0x08,
     100,   13,   13,   13, 0x08,
     142,  131,   13,   13, 0x08,
     175,  170,   13,   13, 0x08,
     204,  195,   13,   13, 0x08,
     233,  230,   13,   13, 0x08,
     253,   13,   13,   13, 0x08,
     287,   13,   13,   13, 0x08,
     317,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Patchupdates[] = {
    "Patchupdates\0\0cancelDownload()\0"
    "on_pushButton_Checkupdates_clicked()\0"
    "on_pushButton_updates_clicked()\0"
    "on_pushButton_Cancel_clicked()\0"
    "done,total\0viewProgress(qint64,qint64)\0"
    "info\0listInfo2(QUrlInfo)\0id,error\0"
    "commandFinished(int,bool)\0id\0"
    "commandstarted(int)\0"
    "on_checkBox_Clancor_HHC_clicked()\0"
    "on_checkBox_HHC_SDK_clicked()\0"
    "on_checkBox_CoProcessor_clicked()\0"
};

const QMetaObject Patchupdates::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Patchupdates,
      qt_meta_data_Patchupdates, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Patchupdates::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Patchupdates::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Patchupdates::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Patchupdates))
        return static_cast<void*>(const_cast< Patchupdates*>(this));
    return QDialog::qt_metacast(_clname);
}

int Patchupdates::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cancelDownload(); break;
        case 1: on_pushButton_Checkupdates_clicked(); break;
        case 2: on_pushButton_updates_clicked(); break;
        case 3: on_pushButton_Cancel_clicked(); break;
        case 4: viewProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: listInfo2((*reinterpret_cast< QUrlInfo(*)>(_a[1]))); break;
        case 6: commandFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: commandstarted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: on_checkBox_Clancor_HHC_clicked(); break;
        case 9: on_checkBox_HHC_SDK_clicked(); break;
        case 10: on_checkBox_CoProcessor_clicked(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
