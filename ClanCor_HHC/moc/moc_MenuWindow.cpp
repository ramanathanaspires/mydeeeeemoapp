/****************************************************************************
** Meta object code from reading C++ file 'MenuWindow.h'
**
** Created: Tue Feb 11 18:10:08 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MenuWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MenuWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      86,   63,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     159,   11,   11,   11, 0x08,
     186,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     237,  231,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     275,   11,   11,   11, 0x08,
     294,   11,   11,   11, 0x08,
     312,   11,   11,   11, 0x08,
     330,   11,   11,   11, 0x08,
     350,   11,   11,   11, 0x08,
     362,   11,   11,   11, 0x08,
     379,   11,   11,   11, 0x08,
     390,   11,   11,   11, 0x08,
     405,   11,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,
     442,   11,   11,   11, 0x08,
     468,  466,   11,   11, 0x08,
     515,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MenuWindow[] = {
    "MenuWindow\0\0slot_SetItemVisible()\0"
    "slot_ItemCliked(QModelIndex)\0"
    "listwidgetitemSelected\0"
    "slot_ItemEntered(QListWidgetItem*)\0"
    "slot_SigCapture()\0slot_PreviewAudio()\0"
    "slot_SaveAudio(QByteArray)\0"
    "slot_FingerDialogCall()\0slot_PreviewCamera()\0"
    "nMSec\0delay(int)\0slot_ImageCaptured(QImage)\0"
    "slot_ImageViewer()\0slot_PrintClick()\0"
    "slot_WebBrowser()\0slot_Magneticcard()\0"
    "slot_Rfid()\0slot_SmartCard()\0slot_GPS()\0"
    "slot_Notepad()\0slot_FileCopying()\0"
    "slot_SystemInfo()\0slot_TerminalEmulator()\0"
    ",\0slot_CloseApplicaton(int,QProcess::ExitStatus)\0"
    "slot_MemoryStatus()\0"
};

const QMetaObject MenuWindow::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_MenuWindow,
      qt_meta_data_MenuWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MenuWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MenuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MenuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWindow))
        return static_cast<void*>(const_cast< MenuWindow*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int MenuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_SetItemVisible(); break;
        case 1: slot_ItemCliked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: slot_ItemEntered((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: slot_SigCapture(); break;
        case 4: slot_PreviewAudio(); break;
        case 5: slot_SaveAudio((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: slot_FingerDialogCall(); break;
        case 7: slot_PreviewCamera(); break;
        case 8: delay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: slot_ImageCaptured((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 10: slot_ImageViewer(); break;
        case 11: slot_PrintClick(); break;
        case 12: slot_WebBrowser(); break;
        case 13: slot_Magneticcard(); break;
        case 14: slot_Rfid(); break;
        case 15: slot_SmartCard(); break;
        case 16: slot_GPS(); break;
        case 17: slot_Notepad(); break;
        case 18: slot_FileCopying(); break;
        case 19: slot_SystemInfo(); break;
        case 20: slot_TerminalEmulator(); break;
        case 21: slot_CloseApplicaton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 22: slot_MemoryStatus(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
