/****************************************************************************
** Meta object code from reading C++ file 'csignature.h'
**
** Created: Fri Nov 29 15:23:47 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../csignature.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'csignature.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClanCor__CPaintPanel[] = {

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
      25,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CPaintPanel[] = {
    "ClanCor::CPaintPanel\0\0,,\0draw(int,int,ulong)\0"
};

const QMetaObject ClanCor::CPaintPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClanCor__CPaintPanel,
      qt_meta_data_ClanCor__CPaintPanel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CPaintPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CPaintPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CPaintPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CPaintPanel))
        return static_cast<void*>(const_cast< CPaintPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClanCor::CPaintPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: draw((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ClanCor__CThreadSignature[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CThreadSignature[] = {
    "ClanCor::CThreadSignature\0\0sigEnable(bool)\0"
    "refreshval()\0"
};

const QMetaObject ClanCor::CThreadSignature::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClanCor__CThreadSignature,
      qt_meta_data_ClanCor__CThreadSignature, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CThreadSignature::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CThreadSignature::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CThreadSignature::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CThreadSignature))
        return static_cast<void*>(const_cast< CThreadSignature*>(this));
    return QThread::qt_metacast(_clname);
}

int ClanCor::CThreadSignature::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: refreshval(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ClanCor::CThreadSignature::sigEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ClanCor__CSignature[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      34,   20,   20,   20, 0x08,
      41,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClanCor__CSignature[] = {
    "ClanCor::CSignature\0\0clearImage()\0"
    "save()\0exitSig()\0"
};

const QMetaObject ClanCor::CSignature::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClanCor__CSignature,
      qt_meta_data_ClanCor__CSignature, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClanCor::CSignature::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClanCor::CSignature::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClanCor::CSignature::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClanCor__CSignature))
        return static_cast<void*>(const_cast< CSignature*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClanCor::CSignature::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clearImage(); break;
        case 1: save(); break;
        case 2: exitSig(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
