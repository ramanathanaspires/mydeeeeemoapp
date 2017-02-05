/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created: Tue Jul 13 16:43:43 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x08,
      35,    7,    7,    7, 0x08,
      47,    7,    7,    7, 0x08,
      62,    7,    7,    7, 0x08,
      78,    7,    7,    7, 0x08,
      91,    7,    7,    7, 0x08,
     107,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Widget[] = {
    "Widget\0\0Bytes\0BytesWritten(qint64)\0"
    "readyRead()\0ListenServer()\0ClientConnect()\0"
    "Send_Click()\0Receive_Click()\0"
    "Receive_File()\0"
};

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget,
      qt_meta_data_Widget, 0 }
};

const QMetaObject *Widget::metaObject() const
{
    return &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: BytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: readyRead(); break;
        case 2: ListenServer(); break;
        case 3: ClientConnect(); break;
        case 4: Send_Click(); break;
        case 5: Receive_Click(); break;
        case 6: Receive_File(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
