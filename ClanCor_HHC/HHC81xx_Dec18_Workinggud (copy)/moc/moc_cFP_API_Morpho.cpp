/****************************************************************************
** Meta object code from reading C++ file 'cFP_API_Morpho.h'
**
** Created: Fri Nov 29 15:24:15 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cFP_API_Morpho.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cFP_API_Morpho.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CFP_API_Morpho[] = {

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
      16,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CFP_API_Morpho[] = {
    "CFP_API_Morpho\0\0on_pushButton_clicked()\0"
};

const QMetaObject CFP_API_Morpho::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CFP_API_Morpho,
      qt_meta_data_CFP_API_Morpho, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CFP_API_Morpho::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CFP_API_Morpho::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CFP_API_Morpho::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CFP_API_Morpho))
        return static_cast<void*>(const_cast< CFP_API_Morpho*>(this));
    return QWidget::qt_metacast(_clname);
}

int CFP_API_Morpho::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
