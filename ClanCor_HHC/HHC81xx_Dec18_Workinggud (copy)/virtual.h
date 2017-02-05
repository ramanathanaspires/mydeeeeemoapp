#ifndef VIRTUAL_H
#define VIRTUAL_H
#include<QPushButton>
#include<QLineEdit>
#include <QWidget>
#include<QLabel>
#include<QDialog>
#include<QTimer>
//#include<global.h>
//using namespace Global;
class Virtual:public QDialog
{
    Q_OBJECT

public:
//    explicit
    Virtual();
//    QWidget *parent = 0);
    bool bCaps;
    bool bButtonPress;
    QString VirtualString();
//    { return strVirtualkey; }
    QLabel *m_labelBaloon;
    QTimer m_timerToolTip;
    QString strAlphanumeric;
    void addText(QString text);
    void keyPressEvent(QKeyEvent *event);
    void delay(int nMSec);

    ~Virtual();

public slots:
    void popUpMessage(const QString &r_const_strDISPLAYTEXT,int nXpos,int nYpos);

private:
    QPushButton *btn_a,*btn_b,*btn_c,*btn_d,*btn_e,*btn_f,*btn_g,*btn_h,*btn_i,*btn_j,*btn_k,*btn_l,*btn_m,*btn_n,*btn_o,*btn_p,*btn_q,*btn_r,*btn_s,*btn_t;
    QPushButton *btn_u,*btn_v,*btn_w,*btn_x,*btn_y,*btn_z,*btn_backspace,*btn_space,*btn_clr,*btn_enter,*btn_caps,*btn_123;
    QLineEdit *lReturnValue;

private slots:
//    void on_btn_backspace_released();
//    void on_btn_backspace_pressed();
    void on_btn_backspace_clicked();

    void closeBaloon();
    void on_btn_enter_clicked();
    void on_btn_space_clicked();
    void on_btn_clear_clicked();
    void on_btn_right_clicked();
    void on_btn_left_clicked();
    void on_btn_m_clicked();
    void on_btn_n_clicked();
    void on_btn_b_clicked();
    void on_btn_v_clicked();
    void on_btn_c_clicked();
    void on_btn_x_clicked();
    void on_btn_z_clicked();
    void on_btn_l_clicked();
    void on_btn_k_clicked();
    void on_btn_j_clicked();
    void on_btn_h_clicked();
    void on_btn_g_clicked();
    void on_btn_f_clicked();
    void on_btn_d_clicked();
    void on_btn_s_clicked();
    void on_btn_a_clicked();
    void on_btn_p_clicked();
    void on_btn_o_clicked();
    void on_btn_i_clicked();
    void on_btn_u_clicked();
    void on_btn_y_clicked();
    void on_btn_t_clicked();
    void on_btn_r_clicked();
    void on_btn_e_clicked();
    void on_btn_w_clicked();
    void on_btn_q_clicked();
    void on_btn_caps_clicked();
    void on_btn_123_clicked();


};

#endif // VIRTUAL_H
