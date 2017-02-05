/****************************************************************************
** Meta object code from reading C++ file 'Fprint.h'
**
** Created: Tue Feb 11 18:11:00 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Fprint.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Fprint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fprint[] = {

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
       8,    7,    7,    7, 0x08,
      25,    7,    7,    7, 0x08,
      46,    7,    7,    7, 0x08,
      67,    7,    7,    7, 0x08,
      88,    7,    7,    7, 0x08,
     111,    7,    7,    7, 0x08,
     134,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Fprint[] = {
    "Fprint\0\0Getimage_Click()\0EnrollFinger_Click()\0"
    "VerifyFinger_Click()\0VerifyFinger_match()\0"
    "IdentifyFinger_Click()\0IdentifyFinger_match()\0"
    "slot_setTemplateType(int)\0"
};

const QMetaObject Fprint::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Fprint,
      qt_meta_data_Fprint, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fprint::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fprint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fprint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fprint))
        return static_cast<void*>(const_cast< Fprint*>(this));
    return QDialog::qt_metacast(_clname);
}

int Fprint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Getimage_Click(); break;
        case 1: EnrollFinger_Click(); break;
        case 2: VerifyFinger_Click(); break;
        case 3: VerifyFinger_match(); break;
        case 4: IdentifyFinger_Click(); break;
        case 5: IdentifyFinger_match(); break;
        case 6: slot_setTemplateType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
