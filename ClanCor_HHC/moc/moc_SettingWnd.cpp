/****************************************************************************
** Meta object code from reading C++ file 'SettingWnd.h'
**
** Created: Tue Feb 11 18:10:27 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SettingWnd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingWnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingWnd[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   12,   11,   11, 0x08,
      89,   70,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     208,   11,   11,   11, 0x08,
     221,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     259,   11,   11,   11, 0x08,
     275,   11,   11,   11, 0x08,
     294,   11,   11,   11, 0x08,
     316,   11,   11,   11, 0x08,
     339,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     378,   11,   11,   11, 0x08,
     397,   11,   11,   11, 0x08,
     416,   11,   11,   11, 0x08,
     427,   11,   11,   11, 0x08,
     449,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingWnd[] = {
    "SettingWnd\0\0listwidgetitemSelected\0"
    "slot_ItemEntered(QListWidgetItem*)\0"
    "modelindexSelected\0slot_ItemCliked(QModelIndex)\0"
    "slot_SetItemVisible()\0slot_Ethernet()\0"
    "slot_GPRS()\0slot_KeyLock_PwrSave()\0"
    "slot_Usbgadget()\0slot_Theme()\0"
    "slot_VolumeControl()\0slot_Wallpaper()\0"
    "slot_DateTime()\0slot_AppLauncher()\0"
    "slot_TouchCalibrate()\0slot_CoProcessorProg()\0"
    "slot_PrinterSetup()\0slot_UserAccount()\0"
    "slot_WifiSetting()\0slot_AgpsSetting()\0"
    "slot_ssh()\0slot_fileUpdate_Ftp()\0"
    "slot_CoUpTest()\0"
};

const QMetaObject SettingWnd::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_SettingWnd,
      qt_meta_data_SettingWnd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingWnd))
        return static_cast<void*>(const_cast< SettingWnd*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int SettingWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slot_ItemEntered((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: slot_ItemCliked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: slot_SetItemVisible(); break;
        case 3: slot_Ethernet(); break;
        case 4: slot_GPRS(); break;
        case 5: slot_KeyLock_PwrSave(); break;
        case 6: slot_Usbgadget(); break;
        case 7: slot_Theme(); break;
        case 8: slot_VolumeControl(); break;
        case 9: slot_Wallpaper(); break;
        case 10: slot_DateTime(); break;
        case 11: slot_AppLauncher(); break;
        case 12: slot_TouchCalibrate(); break;
        case 13: slot_CoProcessorProg(); break;
        case 14: slot_PrinterSetup(); break;
        case 15: slot_UserAccount(); break;
        case 16: slot_WifiSetting(); break;
        case 17: slot_AgpsSetting(); break;
        case 18: slot_ssh(); break;
        case 19: slot_fileUpdate_Ftp(); break;
        case 20: slot_CoUpTest(); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}
static const uint qt_meta_data_GroupBoxCustom[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GroupBoxCustom[] = {
    "GroupBoxCustom\0"
};

const QMetaObject GroupBoxCustom::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_GroupBoxCustom,
      qt_meta_data_GroupBoxCustom, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GroupBoxCustom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GroupBoxCustom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GroupBoxCustom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GroupBoxCustom))
        return static_cast<void*>(const_cast< GroupBoxCustom*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int GroupBoxCustom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_EthernetWnd[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x08,
      45,   12,   12,   12, 0x08,
      64,   12,   12,   12, 0x08,
      76,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EthernetWnd[] = {
    "EthernetWnd\0\0showEthernet()\0"
    "clickNetConfOK()\0NetworkexitTrans()\0"
    "clearForm()\0makeEnable()\0"
};

const QMetaObject EthernetWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EthernetWnd,
      qt_meta_data_EthernetWnd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EthernetWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EthernetWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EthernetWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EthernetWnd))
        return static_cast<void*>(const_cast< EthernetWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int EthernetWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showEthernet(); break;
        case 1: clickNetConfOK(); break;
        case 2: NetworkexitTrans(); break;
        case 3: clearForm(); break;
        case 4: makeEnable(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_GPRSWnd[] = {

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
       9,    8,    8,    8, 0x0a,
      20,    8,    8,    8, 0x0a,
      41,    8,    8,    8, 0x0a,
      58,    8,    8,    8, 0x08,
      78,    8,    8,    8, 0x08,
     100,    8,    8,    8, 0x08,
     120,    8,    8,    8, 0x08,
     136,    8,    8,    8, 0x08,
     150,    8,    8,    8, 0x08,
     162,    8,    8,    8, 0x08,
     175,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GPRSWnd[] = {
    "GPRSWnd\0\0showGPRS()\0setNetworkManually()\0"
    "setNetworkAuto()\0NWSearchOperation()\0"
    "NetworkSearchManual()\0NetworkSearchAuto()\0"
    "GPRSexitTrans()\0clickGPRSOK()\0clearForm()\0"
    "makeEnable()\0on_clickedGPRSAlwaysON_OFF()\0"
};

const QMetaObject GPRSWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GPRSWnd,
      qt_meta_data_GPRSWnd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GPRSWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GPRSWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GPRSWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GPRSWnd))
        return static_cast<void*>(const_cast< GPRSWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int GPRSWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showGPRS(); break;
        case 1: setNetworkManually(); break;
        case 2: setNetworkAuto(); break;
        case 3: NWSearchOperation(); break;
        case 4: NetworkSearchManual(); break;
        case 5: NetworkSearchAuto(); break;
        case 6: GPRSexitTrans(); break;
        case 7: clickGPRSOK(); break;
        case 8: clearForm(); break;
        case 9: makeEnable(); break;
        case 10: on_clickedGPRSAlwaysON_OFF(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
static const uint qt_meta_data_PowerOptions[] = {

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
      14,   13,   13,   13, 0x08,
      36,   13,   13,   13, 0x08,
      61,   13,   13,   13, 0x08,
      82,   13,   13,   13, 0x08,
     103,   13,   13,   13, 0x08,
     134,  127,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PowerOptions[] = {
    "PowerOptions\0\0PowerOptionsOkTrans()\0"
    "PowerOptionsCloseTrans()\0setButtonEnable(int)\0"
    "IdlemodeToggle(bool)\0StandBymodeToggle(bool)\0"
    "toggle\0ScreenlockToggle(bool)\0"
};

const QMetaObject PowerOptions::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PowerOptions,
      qt_meta_data_PowerOptions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PowerOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PowerOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PowerOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PowerOptions))
        return static_cast<void*>(const_cast< PowerOptions*>(this));
    return QDialog::qt_metacast(_clname);
}

int PowerOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PowerOptionsOkTrans(); break;
        case 1: PowerOptionsCloseTrans(); break;
        case 2: setButtonEnable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: IdlemodeToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: StandBymodeToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: ScreenlockToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_timeset[] = {

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
       9,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_timeset[] = {
    "timeset\0\0getTime(QTime)\0"
};

const QMetaObject timeset::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_timeset,
      qt_meta_data_timeset, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &timeset::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *timeset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *timeset::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_timeset))
        return static_cast<void*>(const_cast< timeset*>(this));
    return QThread::qt_metacast(_clname);
}

int timeset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getTime((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void timeset::getTime(QTime _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_DateTimeSetting[] = {

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
      17,   16,   16,   16, 0x08,
      37,   16,   16,   16, 0x08,
      51,   16,   16,   16, 0x08,
      66,   16,   16,   16, 0x08,
      96,   84,   16,   16, 0x08,
     118,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DateTimeSetting[] = {
    "DateTimeSetting\0\0showtimedate(QTime)\0"
    "timeChanged()\0timeChanged1()\0"
    "setCalenderYear()\0month_index\0"
    "setCalenderMonth(int)\0enableslot()\0"
};

const QMetaObject DateTimeSetting::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DateTimeSetting,
      qt_meta_data_DateTimeSetting, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DateTimeSetting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DateTimeSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DateTimeSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DateTimeSetting))
        return static_cast<void*>(const_cast< DateTimeSetting*>(this));
    return QDialog::qt_metacast(_clname);
}

int DateTimeSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showtimedate((*reinterpret_cast< QTime(*)>(_a[1]))); break;
        case 1: timeChanged(); break;
        case 2: timeChanged1(); break;
        case 3: setCalenderYear(); break;
        case 4: setCalenderMonth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: enableslot(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_ApplicationLaunchWnd[] = {

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
      22,   21,   21,   21, 0x08,
      33,   21,   21,   21, 0x08,
      48,   21,   21,   21, 0x08,
      61,   21,   21,   21, 0x08,
      78,   21,   21,   21, 0x08,
      93,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ApplicationLaunchWnd[] = {
    "ApplicationLaunchWnd\0\0Ok_Click()\0"
    "Cancel_Click()\0browseSlot()\0"
    "browseSignSlot()\0EnableButton()\0"
    "RunBinaryFile()\0"
};

const QMetaObject ApplicationLaunchWnd::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ApplicationLaunchWnd,
      qt_meta_data_ApplicationLaunchWnd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApplicationLaunchWnd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApplicationLaunchWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApplicationLaunchWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApplicationLaunchWnd))
        return static_cast<void*>(const_cast< ApplicationLaunchWnd*>(this));
    return QDialog::qt_metacast(_clname);
}

int ApplicationLaunchWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Ok_Click(); break;
        case 1: Cancel_Click(); break;
        case 2: browseSlot(); break;
        case 3: browseSignSlot(); break;
        case 4: EnableButton(); break;
        case 5: RunBinaryFile(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_TFTSettingdialog[] = {

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
      18,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TFTSettingdialog[] = {
    "TFTSettingdialog\0\0setBrightness(int)\0"
};

const QMetaObject TFTSettingdialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TFTSettingdialog,
      qt_meta_data_TFTSettingdialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TFTSettingdialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TFTSettingdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TFTSettingdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TFTSettingdialog))
        return static_cast<void*>(const_cast< TFTSettingdialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TFTSettingdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
