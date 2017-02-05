/****************************************************************************
** Meta object code from reading C++ file 'GlobalClass.h'
**
** Created: Tue Feb 11 18:10:19 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GlobalClass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GlobalClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeView_custom[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TreeView_custom[] = {
    "TreeView_custom\0\0IndexChanged(QModelIndex)\0"
};

const QMetaObject TreeView_custom::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_TreeView_custom,
      qt_meta_data_TreeView_custom, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeView_custom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeView_custom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeView_custom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeView_custom))
        return static_cast<void*>(const_cast< TreeView_custom*>(this));
    return QListView::qt_metacast(_clname);
}

int TreeView_custom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: IndexChanged((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TreeView_custom::IndexChanged(QModelIndex _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_fileDialog[] = {

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
      12,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      48,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     122,   11,   11,   11, 0x08,
     132,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_fileDialog[] = {
    "fileDialog\0\0setfileName(QModelIndex)\0"
    "openPath()\0setfileName_text(QModelIndex)\0"
    "setfileName_Focus(QModelIndex)\0"
    "slotOpnSav()\0openDir()\0slotBack()\0"
};

const QMetaObject fileDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_fileDialog,
      qt_meta_data_fileDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fileDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fileDialog))
        return static_cast<void*>(const_cast< fileDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int fileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setfileName((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: openPath(); break;
        case 2: setfileName_text((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: setfileName_Focus((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: slotOpnSav(); break;
        case 5: openDir(); break;
        case 6: slotBack(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_filebrowser[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      38,   12,   12,   12, 0x08,
      51,   12,   12,   12, 0x08,
      61,   12,   12,   12, 0x08,
      72,   12,   12,   12, 0x08,
      83,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_filebrowser[] = {
    "filebrowser\0\0setfileName(QModelIndex)\0"
    "slotOpnSav()\0openDir()\0openPath()\0"
    "slotBack()\0imageViewerSlot()\0"
};

const QMetaObject filebrowser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_filebrowser,
      qt_meta_data_filebrowser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &filebrowser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *filebrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *filebrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_filebrowser))
        return static_cast<void*>(const_cast< filebrowser*>(this));
    return QDialog::qt_metacast(_clname);
}

int filebrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setfileName((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: slotOpnSav(); break;
        case 2: openDir(); break;
        case 3: openPath(); break;
        case 4: slotBack(); break;
        case 5: imageViewerSlot(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_Notepad[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      23,    8,   18,    8, 0x08,
      37,   32,   18,    8, 0x08,
      55,    8,   18,    8, 0x08,
      68,    8,   18,    8, 0x08,
      89,    8,    8,    8, 0x08,
      99,    8,    8,    8, 0x08,
     108,    8,    8,    8, 0x08,
     117,    8,    8,    8, 0x08,
     123,    8,    8,    8, 0x08,
     130,    8,    8,    8, 0x08,
     138,    8,    8,    8, 0x08,
     148,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Notepad[] = {
    "Notepad\0\0loadme()\0bool\0saveme()\0name\0"
    "saveFile(QString)\0saveFileAs()\0"
    "mayDiscardDocument()\0newfile()\0undome()\0"
    "redome()\0Cut()\0Copy()\0Paste()\0aboutme()\0"
    "closeNotepad()\0"
};

const QMetaObject Notepad::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Notepad,
      qt_meta_data_Notepad, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Notepad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Notepad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Notepad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Notepad))
        return static_cast<void*>(const_cast< Notepad*>(this));
    return QDialog::qt_metacast(_clname);
}

int Notepad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadme(); break;
        case 1: { bool _r = saveme();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = saveFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveFileAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = mayDiscardDocument();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: newfile(); break;
        case 6: undome(); break;
        case 7: redome(); break;
        case 8: Cut(); break;
        case 9: Copy(); break;
        case 10: Paste(); break;
        case 11: aboutme(); break;
        case 12: closeNotepad(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
