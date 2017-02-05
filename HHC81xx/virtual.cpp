#include "virtual.h"
#include<QEventLoop>
#include<QKeyEvent>
//#include<virtualkeyget.h>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<cglobal.h>
#include <qdebug.h>
using namespace ClanCor;
using namespace Global;

Virtual::Virtual() :  QDialog()
//        (QWidget *parent)
//    :QWidget(parent)
{
    lReturnValue = new QLineEdit;
    btn_a = new QPushButton("a");
    btn_b = new QPushButton("b");
    btn_c = new QPushButton("c");
    btn_d = new QPushButton("d");
    btn_e = new QPushButton("e");
    btn_f = new QPushButton("f");
    btn_g = new QPushButton("g");
    btn_h = new QPushButton("h");
    btn_i = new QPushButton("i");
    btn_j = new QPushButton("j");
    btn_k = new QPushButton("k");
    btn_l = new QPushButton("l");
    btn_m = new QPushButton("m");
    btn_n = new QPushButton("n");
    btn_o = new QPushButton("o");
    btn_p = new QPushButton("p");
    btn_q = new QPushButton("q");
    btn_r = new QPushButton("r");
    btn_s = new QPushButton("s");
    btn_t = new QPushButton("t");
    btn_u = new QPushButton("u");
    btn_v = new QPushButton("v");
    btn_w = new QPushButton("w");
    btn_x = new QPushButton("x");
    btn_y = new QPushButton("y");
    btn_z = new QPushButton("z");
    btn_caps = new QPushButton("Caps");
    btn_clr = new QPushButton("Clr");
    btn_backspace = new QPushButton("Back\nspace");
    btn_123 = new QPushButton("?123");
    btn_space=new QPushButton("Space");
    btn_enter = new QPushButton("Enter");

//    m_labelBaloon= new QLabel;
//    m_labelBaloon->setStyleSheet("color: rgb(255, 255, 255);"
//                                 "font: 75 26pt \"Sans Serif\";"
//                                 "border-radius: 6px;:"
//                                 "qproperty-alignment: AlignCenter;"
//                                 "background-image: url(:/image/3.png);"
//                                 "border-radius: 10px;"
//                                 "background-color: rgb(235, 241, 234,0);"
//                                 "border-width: 3px;");
//    m_labelBaloon->move(10,50);
//    m_labelBaloon->setText("M");
//    m_labelBaloon->show();


    lReturnValue->setFixedSize(300,30);
    btn_a->setFixedSize(30,40);
    btn_b->setFixedSize(30,40);
    btn_c->setFixedSize(30,40);
    btn_d->setFixedSize(30,40);
    btn_e->setFixedSize(30,40);
    btn_f->setFixedSize(30,40);
    btn_g->setFixedSize(30,40);
    btn_h->setFixedSize(30,40);
    btn_i->setFixedSize(30,40);
    btn_j->setFixedSize(30,40);
    btn_k->setFixedSize(30,40);
    btn_l->setFixedSize(30,40);
    btn_m->setFixedSize(30,40);
    btn_n->setFixedSize(30,40);
    btn_o->setFixedSize(30,40);
    btn_p->setFixedSize(30,40);
    btn_q->setFixedSize(30,40);
    btn_r->setFixedSize(30,40);
    btn_s->setFixedSize(30,40);
    btn_t->setFixedSize(30,40);
    btn_u->setFixedSize(30,40);
    btn_v->setFixedSize(30,40);
    btn_w->setFixedSize(30,40);
    btn_x->setFixedSize(30,40);
    btn_y->setFixedSize(30,40);
    btn_z->setFixedSize(30,40);
    btn_123->setFixedSize(43,40);
    btn_space->setFixedSize(105,38);
    btn_enter->setFixedSize(80,38);
    btn_caps->setFixedSize(43,40);
    btn_clr->setFixedSize(50,38);
    btn_backspace->setFixedSize(55,38);
    QString strStylesheet= "color: black;"
                           "border : 2px ridge #339;"
                           "background-color: lightblue;"
                           "border-radius: 8;"
                           "padding: 3px;"
                           "font: 75 20pt \"DejaVu Serif\";";
    QString strStylesheet1="background-color: rgb(0, 170, 127);"
                           "color: black;"
                           "border : 2px ridge #339;"
                           "border-radius: 8;"
                           "padding: 3px;"
                           "font: 75 10pt \"DejaVu Serif\";";
    btn_a->setStyleSheet(strStylesheet);
    btn_b->setStyleSheet(strStylesheet);
    btn_c->setStyleSheet(strStylesheet);
    btn_d->setStyleSheet(strStylesheet);
    btn_e->setStyleSheet(strStylesheet);
    btn_f->setStyleSheet(strStylesheet);
    btn_g->setStyleSheet(strStylesheet);
    btn_h->setStyleSheet(strStylesheet);
    btn_i->setStyleSheet(strStylesheet);
    btn_j->setStyleSheet(strStylesheet);
    btn_k->setStyleSheet(strStylesheet);
    btn_l->setStyleSheet(strStylesheet);
    btn_m->setStyleSheet(strStylesheet);
    btn_n->setStyleSheet(strStylesheet);
    btn_o->setStyleSheet(strStylesheet);
    btn_p->setStyleSheet(strStylesheet);
    btn_q->setStyleSheet(strStylesheet);
    btn_r->setStyleSheet(strStylesheet);
    btn_s->setStyleSheet(strStylesheet);
    btn_t->setStyleSheet(strStylesheet);
    btn_u->setStyleSheet(strStylesheet);
    btn_v->setStyleSheet(strStylesheet);
    btn_w->setStyleSheet(strStylesheet);
    btn_x->setStyleSheet(strStylesheet);
    btn_y->setStyleSheet(strStylesheet);
    btn_z->setStyleSheet(strStylesheet);
    btn_backspace->setStyleSheet("color: black;"
                                 "border : 2px ridge #339;"
                                 "background-color: lightblue;"
                                 "border-radius: 8;"
                                 "padding: 3px;"
                                 "font: 75 10pt \"DejaVu Serif\";");
    btn_clr->setStyleSheet("color: black;"
                           "border : 2px ridge #339;"
                           "background-color: lightblue;"
                           "border-radius: 8;"
                           "padding: 3px;"
                           "font: 75 10pt \"DejaVu Serif\";");
    btn_space->setStyleSheet("color: black;"
                             "border : 2px ridge #339;"
                             "background-color: lightblue;"
                             "border-radius: 8;"
                             "padding: 3px;"
                             "font: 75 10pt \"DejaVu Serif\";");
    btn_enter->setStyleSheet("color: black;"
                             "border : 2px ridge #339;"
                             "background-color: lightblue;"
                             "border-radius: 8;"
                             "padding: 3px;"
                             "font: 75 10pt \"DejaVu Serif\";");
    btn_caps->setStyleSheet(strStylesheet1);
    btn_123->setStyleSheet(strStylesheet1);



    QHBoxLayout *hlayoutsub = new QHBoxLayout;
    hlayoutsub->setSpacing(1);
    hlayoutsub->addWidget(lReturnValue);

//    QHBoxLayout *hlayoutsub5 = new QHBoxLayout;
//    hlayoutsub5->setSpacing(1);
////    hlayoutsub5->addWidget(lReturnValue);
//    hlayoutsub5->addWidget(m_labelBaloon);

    QHBoxLayout *hlayoutsub1 = new QHBoxLayout;
    hlayoutsub1->setSpacing(1);
    hlayoutsub1->addWidget(btn_q);
    hlayoutsub1->addWidget(btn_w);
    hlayoutsub1->addWidget(btn_e);
    hlayoutsub1->addWidget(btn_r);
    hlayoutsub1->addWidget(btn_t);
    hlayoutsub1->addWidget(btn_y);
    hlayoutsub1->addWidget(btn_u);
    hlayoutsub1->addWidget(btn_i);
    hlayoutsub1->addWidget(btn_o);
    hlayoutsub1->addWidget(btn_p);

    QHBoxLayout *hlayoutsub2 = new QHBoxLayout;
    hlayoutsub2->setSpacing(1);
    hlayoutsub2->addWidget(btn_a);
    hlayoutsub2->addWidget(btn_s);
    hlayoutsub2->addWidget(btn_d);
    hlayoutsub2->addWidget(btn_f);
    hlayoutsub2->addWidget(btn_g);
    hlayoutsub2->addWidget(btn_h);
    hlayoutsub2->addWidget(btn_j);
    hlayoutsub2->addWidget(btn_k);
    hlayoutsub2->addWidget(btn_l);
    hlayoutsub2->setAlignment(Qt::AlignHCenter);

    QHBoxLayout *hlayoutsub3 = new QHBoxLayout;
    hlayoutsub3->setSpacing(0);
    hlayoutsub3->addWidget(btn_caps);
    hlayoutsub3->addWidget(btn_z);
    hlayoutsub3->addWidget(btn_x);
    hlayoutsub3->addWidget(btn_c);
    hlayoutsub3->addWidget(btn_v);
    hlayoutsub3->addWidget(btn_b);
    hlayoutsub3->addWidget(btn_n);
    hlayoutsub3->addWidget(btn_m);
    hlayoutsub3->addWidget(btn_123);

    QHBoxLayout *hlayoutsub4 = new QHBoxLayout;
    hlayoutsub4->setSpacing(1);
    hlayoutsub4->addWidget(btn_backspace);
    hlayoutsub4->addWidget(btn_space);
    hlayoutsub4->setSpacing(6);
    hlayoutsub4->addWidget(btn_clr);
    hlayoutsub4->setSpacing(3);
    hlayoutsub4->addWidget(btn_enter);

    QVBoxLayout *vlayoutmain = new QVBoxLayout;
//    vlayoutmain->addLayout(hlayoutsub5);
    vlayoutmain->addLayout(hlayoutsub);
    vlayoutmain->addLayout(hlayoutsub1);
    vlayoutmain->addLayout(hlayoutsub2);
    vlayoutmain->addLayout(hlayoutsub3);
    vlayoutmain->addLayout(hlayoutsub4);
    setLayout(vlayoutmain);
    connect(btn_a, SIGNAL(clicked()), this, SLOT(on_btn_a_clicked()));
    connect(btn_b, SIGNAL(clicked()), this, SLOT(on_btn_b_clicked()));
    connect(btn_c, SIGNAL(clicked()), this, SLOT(on_btn_c_clicked()));
    connect(btn_d, SIGNAL(clicked()), this, SLOT(on_btn_d_clicked()));
    connect(btn_e, SIGNAL(clicked()), this, SLOT(on_btn_e_clicked()));
    connect(btn_f, SIGNAL(clicked()), this, SLOT(on_btn_f_clicked()));
    connect(btn_g, SIGNAL(clicked()), this, SLOT(on_btn_g_clicked()));
    connect(btn_h, SIGNAL(clicked()), this, SLOT(on_btn_h_clicked()));
    connect(btn_i, SIGNAL(clicked()), this, SLOT(on_btn_i_clicked()));
    connect(btn_j, SIGNAL(clicked()), this, SLOT(on_btn_j_clicked()));
    connect(btn_k, SIGNAL(clicked()), this, SLOT(on_btn_k_clicked()));
    connect(btn_l, SIGNAL(clicked()), this, SLOT(on_btn_l_clicked()));
    connect(btn_m, SIGNAL(clicked()), this, SLOT(on_btn_m_clicked()));
    connect(btn_n, SIGNAL(clicked()), this, SLOT(on_btn_n_clicked()));
    connect(btn_o, SIGNAL(clicked()), this, SLOT(on_btn_o_clicked()));
    connect(btn_p, SIGNAL(clicked()), this, SLOT(on_btn_p_clicked()));
    connect(btn_q, SIGNAL(clicked()), this, SLOT(on_btn_q_clicked()));
    connect(btn_r, SIGNAL(clicked()), this, SLOT(on_btn_r_clicked()));
    connect(btn_s, SIGNAL(clicked()), this, SLOT(on_btn_s_clicked()));
    connect(btn_t, SIGNAL(clicked()), this, SLOT(on_btn_t_clicked()));
    connect(btn_u, SIGNAL(clicked()), this, SLOT(on_btn_u_clicked()));
    connect(btn_v, SIGNAL(clicked()), this, SLOT(on_btn_v_clicked()));
    connect(btn_w, SIGNAL(clicked()), this, SLOT(on_btn_w_clicked()));
    connect(btn_x, SIGNAL(clicked()), this, SLOT(on_btn_x_clicked()));
    connect(btn_y, SIGNAL(clicked()), this, SLOT(on_btn_y_clicked()));
    connect(btn_z, SIGNAL(clicked()), this, SLOT(on_btn_z_clicked()));
    connect(btn_caps, SIGNAL(clicked()), this, SLOT(on_btn_caps_clicked()));
    connect(btn_123, SIGNAL(clicked()), this, SLOT(on_btn_123_clicked()));
    connect(btn_enter, SIGNAL(clicked()), this, SLOT(on_btn_enter_clicked()));
    connect(btn_clr, SIGNAL(clicked()), this, SLOT(on_btn_clear_clicked()));
//    connect(btn_backspace, SIGNAL(clicked()), this, SLOT(on_btn_backspace_released()));
//    connect(btn_backspace, SIGNAL(clicked()), this, SLOT(on_btn_backspace_pressed()));
    connect(btn_backspace, SIGNAL(clicked()), this, SLOT(on_btn_backspace_clicked()));
    connect(btn_space, SIGNAL(clicked()), this, SLOT(on_btn_space_clicked()));
    setWindowTitle(tr("Virtual Keypad"));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    move(0,20);
    setFixedSize(320,220);
}
Virtual::~Virtual()
{
}
QString Virtual::VirtualString()
{
    return gstrVirtualkey;
}

void Virtual::popUpMessage(const QString &r_const_strDISPLAYTEXT, int nXpos, int nYpos)
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
////    if(bCaps)
////       m_labelBaloon->setText(""+r_const_strDISPLAYTEXT);
////    else
//       m_labelBaloon->setText(r_const_strDISPLAYTEXT);
//   m_labelBaloon->show();
//   m_labelBaloon->move(nXpos+5,nYpos+10);
   lReturnValue->setFocus();
    m_timerToolTip.start(200);
}

void Virtual::closeBaloon()
{
//   m_labelBaloon->close();
   lReturnValue->setFocus();
    m_timerToolTip.stop();
//    qApp->processEvents();
}

void Virtual::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        this->hide();
        //        strVirtualkey=lReturnValue->text();
//        VirtualKeyGet *v = new VirtualKeyGet;
//        v->show();
    }
}
void Virtual::on_btn_123_clicked()
{
    if(btn_123->text()=="?123")
    {
       btn_caps->setEnabled(false);
        btn_q->setText("1");
        btn_w->setText("2");
        btn_e->setText("3");
        btn_r->setText("4");
        btn_t->setText("5");
        btn_y->setText("6");
        btn_u->setText("7");
        btn_i->setText("8");
        btn_o->setText("9");
        btn_p->setText("0");
        btn_a->setText("@");
        btn_s->setText("#");
        btn_d->setText("$");
        btn_f->setText("%");
        btn_g->setText("&&");
        btn_h->setText("*");
        btn_j->setText("-");
        btn_k->setText(",");
        btn_l->setText("(");
        btn_z->setText(")");
        btn_x->setText("!");
        btn_c->setText("_");
        btn_v->setText("'");
        btn_b->setText(":");
        btn_n->setText(".");
        btn_m->setText("/");
        bCaps=true;
        btn_123->setText("abc");
    }
    else if(btn_123->text()=="abc")
    {
        btn_caps->setEnabled(true);
        btn_a->setText("a");
        btn_b->setText("b");
        btn_c->setText("c");
        btn_d->setText("d");
        btn_e->setText("e");
        btn_f->setText("f");
        btn_g->setText("g");
        btn_h->setText("h");
        btn_i->setText("i");
        btn_j->setText("j");
        btn_k->setText("k");
        btn_l->setText("l");
        btn_m->setText("m");
        btn_n->setText("n");
        btn_o->setText("o");
        btn_p->setText("p");
        btn_q->setText("q");
        btn_r->setText("r");
        btn_s->setText("s");
        btn_t->setText("t");
        btn_u->setText("u");
        btn_v->setText("v");
        btn_w->setText("w");
        btn_x->setText("x");
        btn_y->setText("y");
        btn_z->setText("z");
        btn_123->setText("?123");
        bCaps=false;
    }
}

void Virtual::on_btn_caps_clicked()
{
    if(bCaps== false)
    {
        btn_a->setText("A");
        btn_b->setText("B");
        btn_c->setText("C");
        btn_d->setText("D");
        btn_e->setText("E");
        btn_f->setText("F");
        btn_g->setText("G");
        btn_h->setText("H");
        btn_i->setText("I");
        btn_j->setText("J");
        btn_k->setText("K");
        btn_l->setText("L");
        btn_m->setText("M");
        btn_n->setText("N");
        btn_o->setText("O");
        btn_p->setText("P");
        btn_q->setText("Q");
        btn_r->setText("R");
        btn_s->setText("S");
        btn_t->setText("T");
        btn_u->setText("U");
        btn_v->setText("V");
        btn_w->setText("W");
        btn_x->setText("X");
        btn_y->setText("Y");
        btn_z->setText("Z");
        bCaps=true;
    }
    else
    {
        btn_a->setText("a");
        btn_b->setText("b");
        btn_c->setText("c");
        btn_d->setText("d");
        btn_e->setText("e");
        btn_f->setText("f");
        btn_g->setText("g");
        btn_h->setText("h");
        btn_i->setText("i");
        btn_j->setText("j");
        btn_k->setText("k");
        btn_l->setText("l");
        btn_m->setText("m");
        btn_n->setText("n");
        btn_o->setText("o");
        btn_p->setText("p");
        btn_q->setText("q");
        btn_r->setText("r");
        btn_s->setText("s");
        btn_t->setText("t");
        btn_u->setText("u");
        btn_v->setText("v");
        btn_w->setText("w");
        btn_x->setText("x");
        btn_y->setText("y");
        btn_z->setText("z");
        bCaps=false;
    }
}
void Virtual::addText(QString text)
{
    QString tmpStr;
    int tmpPos;
    tmpStr=lReturnValue->text();
    tmpPos=lReturnValue->cursorPosition();
    tmpStr.insert(tmpPos,text);
    lReturnValue->setText(tmpStr);
    lReturnValue->setCursorPosition(tmpPos+1);
}
void Virtual::on_btn_backspace_clicked()
{
//    ui->lineEdit->backspace();
     lReturnValue->backspace();
}

void Virtual::on_btn_q_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_q->text();
//    popUpMessage(strAlphanumeric,0,0);
    addText(strAlphanumeric);
}
void Virtual::on_btn_w_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_w->text();
//    popUpMessage(strAlphanumeric,20,0);
    addText(strAlphanumeric);
}
void Virtual::on_btn_e_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_e->text();
//    popUpMessage(strAlphanumeric,50,0);
    addText(strAlphanumeric);
}
void Virtual::on_btn_r_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_r->text();
//    popUpMessage(strAlphanumeric,80,0);
    addText(strAlphanumeric);
}
void Virtual::on_btn_t_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_t->text();
//    popUpMessage(strAlphanumeric,120,0);
    addText(strAlphanumeric);
}
void Virtual::on_btn_y_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_y->text();
//    popUpMessage(strAlphanumeric,150,0);
    addText(strAlphanumeric);
}

void Virtual::on_btn_u_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_u->text();
//    popUpMessage(strAlphanumeric,180,0);
    addText(strAlphanumeric);
}

void Virtual::on_btn_i_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_i->text();
//    popUpMessage(strAlphanumeric,220,0);
    addText(strAlphanumeric);
}

void Virtual::on_btn_o_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_o->text();
//    popUpMessage(strAlphanumeric,240,0);
    addText(strAlphanumeric);
}

void Virtual::on_btn_p_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_p->text();
//    popUpMessage(strAlphanumeric,270,0);
    addText(strAlphanumeric);
}

void Virtual::on_btn_a_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_a->text();
//    popUpMessage(strAlphanumeric,5,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_s_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_s->text();
//    popUpMessage(strAlphanumeric,40,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_d_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_d->text();
//    popUpMessage(strAlphanumeric,70,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_f_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_f->text();
//    popUpMessage(strAlphanumeric,100,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_g_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_g->text();
    if(strAlphanumeric=="&&")
    {
        strAlphanumeric="&";
//        popUpMessage(strAlphanumeric,130,40);
        addText(strAlphanumeric);
    }
    else
    {
//        popUpMessage(strAlphanumeric,130,40);
        addText(strAlphanumeric);
    }
}

void Virtual::on_btn_h_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_h->text();
//    popUpMessage(strAlphanumeric,165,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_j_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_j->text();
//    popUpMessage(strAlphanumeric,190,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_k_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_k->text();
//    popUpMessage(strAlphanumeric,230,40);
    addText(strAlphanumeric);
}

void Virtual::on_btn_l_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_l->text();
//    popUpMessage(strAlphanumeric,265,40);

    addText(strAlphanumeric);
}

void Virtual::on_btn_z_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_z->text();
//    popUpMessage(strAlphanumeric,40,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_x_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_x->text();
//    popUpMessage(strAlphanumeric,70,80);

    addText(strAlphanumeric);
}

void Virtual::on_btn_c_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_c->text();
//    popUpMessage(strAlphanumeric,100,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_v_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_v->text();
//    popUpMessage(strAlphanumeric,130,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_b_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_b->text();
//    popUpMessage(strAlphanumeric,165,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_n_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_n->text();
//    popUpMessage(strAlphanumeric,190,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_m_clicked()
{
//    if (m_labelBaloon->isVisible() ) {
//        closeBaloon();
//    }
    strAlphanumeric=btn_m->text();
//    popUpMessage(strAlphanumeric,230,80);
    addText(strAlphanumeric);
}

void Virtual::on_btn_left_clicked()
{
    lReturnValue->cursorBackward(false);
}

void Virtual::on_btn_right_clicked()
{
    lReturnValue->cursorForward(false);
}

void Virtual::on_btn_clear_clicked()
{
    lReturnValue->clear();
    lReturnValue->setFocus();
}

void Virtual::on_btn_space_clicked()
{
    addText(" ");
}

void Virtual::on_btn_enter_clicked()
{
    this->hide();
    gstrVirtualkey=lReturnValue->text();
//    VirtualKeyGet *v = new VirtualKeyGet;
//    v->show();
    VirtualString();
}

//void Virtual::on_btn_backspace_pressed()
//{
//    m_timerToolTip.start(1000);
////    bButtonPress=true;
//    int textlength = lReturnValue->text().length();
//    for(int i=0;i<=textlength;i++)
//    {
//        if(bButtonPress)
//        {
//            qDebug()<<"\rEnter2" <<bButtonPress;
//            lReturnValue->backspace();
//            delay(100);
//        }
//        else
//        {
//            return;
//        }
//    }
//}

//void Virtual::on_btn_backspace_released()
//{
//    qDebug()<<"\rEnter" <<bButtonPress;
//    bButtonPress=false;
//    qDebug()<<"\rEnter1" <<bButtonPress;
//    m_timerToolTip.stop();
//}
//void Virtual::on_btn_clear_clicked()
//{
//    ui->lineEdit->clear();
//}
void Virtual::delay(int nMSec)
{
    QEventLoop eventLoop;
    QTimer timerTimeout;
    timerTimeout.setInterval(nMSec);
    timerTimeout.setSingleShot(true);
    QObject::connect(&timerTimeout, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timerTimeout.start(nMSec);
    eventLoop.exec();
    timerTimeout.stop();

}

