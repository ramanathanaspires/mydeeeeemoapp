/****************************************************************************
** Meta object code from reading C++ file 'virtual.h'
**
** Created: Fri Nov 29 15:24:18 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../virtual.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtual.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Virtual[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      44,    9,    8,    8, 0x0a,
      74,    8,    8,    8, 0x08,
     101,    8,    8,    8, 0x08,
     115,    8,    8,    8, 0x08,
     138,    8,    8,    8, 0x08,
     161,    8,    8,    8, 0x08,
     184,    8,    8,    8, 0x08,
     207,    8,    8,    8, 0x08,
     229,    8,    8,    8, 0x08,
     248,    8,    8,    8, 0x08,
     267,    8,    8,    8, 0x08,
     286,    8,    8,    8, 0x08,
     305,    8,    8,    8, 0x08,
     324,    8,    8,    8, 0x08,
     343,    8,    8,    8, 0x08,
     362,    8,    8,    8, 0x08,
     381,    8,    8,    8, 0x08,
     400,    8,    8,    8, 0x08,
     419,    8,    8,    8, 0x08,
     438,    8,    8,    8, 0x08,
     457,    8,    8,    8, 0x08,
     476,    8,    8,    8, 0x08,
     495,    8,    8,    8, 0x08,
     514,    8,    8,    8, 0x08,
     533,    8,    8,    8, 0x08,
     552,    8,    8,    8, 0x08,
     571,    8,    8,    8, 0x08,
     590,    8,    8,    8, 0x08,
     609,    8,    8,    8, 0x08,
     628,    8,    8,    8, 0x08,
     647,    8,    8,    8, 0x08,
     666,    8,    8,    8, 0x08,
     685,    8,    8,    8, 0x08,
     704,    8,    8,    8, 0x08,
     723,    8,    8,    8, 0x08,
     745,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Virtual[] = {
    "Virtual\0\0r_const_strDISPLAYTEXT,nXpos,nYpos\0"
    "popUpMessage(QString,int,int)\0"
    "on_btn_backspace_clicked()\0closeBaloon()\0"
    "on_btn_enter_clicked()\0on_btn_space_clicked()\0"
    "on_btn_clear_clicked()\0on_btn_right_clicked()\0"
    "on_btn_left_clicked()\0on_btn_m_clicked()\0"
    "on_btn_n_clicked()\0on_btn_b_clicked()\0"
    "on_btn_v_clicked()\0on_btn_c_clicked()\0"
    "on_btn_x_clicked()\0on_btn_z_clicked()\0"
    "on_btn_l_clicked()\0on_btn_k_clicked()\0"
    "on_btn_j_clicked()\0on_btn_h_clicked()\0"
    "on_btn_g_clicked()\0on_btn_f_clicked()\0"
    "on_btn_d_clicked()\0on_btn_s_clicked()\0"
    "on_btn_a_clicked()\0on_btn_p_clicked()\0"
    "on_btn_o_clicked()\0on_btn_i_clicked()\0"
    "on_btn_u_clicked()\0on_btn_y_clicked()\0"
    "on_btn_t_clicked()\0on_btn_r_clicked()\0"
    "on_btn_e_clicked()\0on_btn_w_clicked()\0"
    "on_btn_q_clicked()\0on_btn_caps_clicked()\0"
    "on_btn_123_clicked()\0"
};

const QMetaObject Virtual::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Virtual,
      qt_meta_data_Virtual, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Virtual::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Virtual::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Virtual::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Virtual))
        return static_cast<void*>(const_cast< Virtual*>(this));
    return QDialog::qt_metacast(_clname);
}

int Virtual::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: popUpMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: on_btn_backspace_clicked(); break;
        case 2: closeBaloon(); break;
        case 3: on_btn_enter_clicked(); break;
        case 4: on_btn_space_clicked(); break;
        case 5: on_btn_clear_clicked(); break;
        case 6: on_btn_right_clicked(); break;
        case 7: on_btn_left_clicked(); break;
        case 8: on_btn_m_clicked(); break;
        case 9: on_btn_n_clicked(); break;
        case 10: on_btn_b_clicked(); break;
        case 11: on_btn_v_clicked(); break;
        case 12: on_btn_c_clicked(); break;
        case 13: on_btn_x_clicked(); break;
        case 14: on_btn_z_clicked(); break;
        case 15: on_btn_l_clicked(); break;
        case 16: on_btn_k_clicked(); break;
        case 17: on_btn_j_clicked(); break;
        case 18: on_btn_h_clicked(); break;
        case 19: on_btn_g_clicked(); break;
        case 20: on_btn_f_clicked(); break;
        case 21: on_btn_d_clicked(); break;
        case 22: on_btn_s_clicked(); break;
        case 23: on_btn_a_clicked(); break;
        case 24: on_btn_p_clicked(); break;
        case 25: on_btn_o_clicked(); break;
        case 26: on_btn_i_clicked(); break;
        case 27: on_btn_u_clicked(); break;
        case 28: on_btn_y_clicked(); break;
        case 29: on_btn_t_clicked(); break;
        case 30: on_btn_r_clicked(); break;
        case 31: on_btn_e_clicked(); break;
        case 32: on_btn_w_clicked(); break;
        case 33: on_btn_q_clicked(); break;
        case 34: on_btn_caps_clicked(); break;
        case 35: on_btn_123_clicked(); break;
        default: ;
        }
        _id -= 36;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
