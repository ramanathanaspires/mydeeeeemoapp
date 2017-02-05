#include "cenreg.h"
using namespace Globalclass;

#include "cenreg.h"
#include "MediaUpload.h"
censusMenu::censusMenu(QWidget *parent)
    : QMdiSubWindow(parent)
{
    MdiArea->addSubWindow(this);
    QScrollArea *scrollArea=new QScrollArea(this);
    QGroupBox *g=new QGroupBox;
    QLabel *title = new QLabel(this);
    title->setFixedSize(320,16);
    title->setStyleSheet("background-color:black;color:white;font:bold;");
    title->setAlignment(Qt::AlignHCenter);
    title->setText("Census Menu");
    title->move(0,0);
//    layout=new QVBoxLayout;
    scrollArea->setWidgetResizable(false);
    scrollArea->verticalScrollBar()->setStyleSheet("width: 20px;");
    scrollArea->setFocusPolicy(Qt::ClickFocus);
    scrollArea->setParent(this);
    scrollArea->setFixedSize(320,220);
    scrollArea->setAlignment(Qt::AlignCenter);
    this->setFixedSize(320,220);
    g->setFixedWidth(290);
    this->setWindowTitle("Census");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    PIC32->SetKeypad(ClanCor::Numeric);
    setButtonDefault(this);

    layout= new QVBoxLayout;
    layout->setAlignment(layout,Qt::AlignTop);
    regBtn=new QPushButton("Entry");
    uploadBtn = new QPushButton("Upload Data's");
    exitBtn=new QPushButton("Exit [F4]");
    exitBtn->setShortcut(Qt::Key_F4);
    layout->addWidget(regBtn);
    layout->addWidget(uploadBtn);
    //layout->addWidget(controlBtn);
    layout->addWidget(exitBtn);
    connect(regBtn,SIGNAL(clicked()),this,SLOT(regTrans()));
    connect(uploadBtn,SIGNAL(clicked()),this,SLOT(uploadTrans()));
    connect(exitBtn,SIGNAL(clicked()),this,SLOT(exitTrans()));
    g->setLayout(layout);
    scrollArea->setWidget(g);
//    setFixedSize(320,200);
    regBtn->setFixedWidth(280);
    uploadBtn->setFixedWidth(280);
    exitBtn->setFixedWidth(280);
    g->setFixedWidth(290);
//    QSpacerItem *itm=new QSpacerItem;
//    itm->setGeometry();

//    QLabel *lbl=new QLabel;
//    lbl->setPixmap(QPixmap(":/census-2011.jpg"));
//    lbl->setFixedHeight(200);
//    g->setStyleSheet("background-image:url(:/census.jpg);");
//    layout->addWidget(lbl,1,Qt::AlignBottom);
//    layout->setStretch(2,100);
    layout->setMargin(0);
    layout->setSpacing(1);
//    regBtn->setStyleSheet("background-image:url(:/2011.jpg);background-color:Transparent");
//    uploadBtn->setStyleSheet("background-image:url(:/2011.jpg);background-color:Transparent");
//    exitBtn->setStyleSheet("background-image:url(:/2011.jpg);background-color:Transparent");
//    g->setStyleSheet("background-image:url(:/2011.jpg)");

//    layout->set

    layout->setAlignment(layout,Qt::AlignTop);
    g->setFixedHeight(180);
    setButtonDefault;
    move(0,0);

}


void censusMenu::regTrans()
{
    cenReg *c=new cenReg;
    MdiArea->addSubWindow(c);
    c->show();
    this->close();
    delete this;
}

void censusMenu::uploadTrans()
{
    setEnabled(false);
    MediaUpload m;
    m.Upload_to_Web();
    setEnabled(true);
}

void censusMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        exitTrans();
    }
}

void censusMenu::exitTrans()
{
    loadForm(NEWMENU, 0);
    this->close();
    delete this;
}

/*****************************census class****************************************/

cenReg::cenReg(QWidget *parent)
    : QMdiSubWindow(parent)
{
    scrollArea=new QScrollArea(this);
    g=new QGroupBox;
    layout=new QGridLayout;
    QLabel *title = new QLabel(this);
    title->setFixedSize(320,16);
    title->setStyleSheet("background-color:black;color:white;font:bold;");
    title->setAlignment(Qt::AlignHCenter);
    title->setText("Registeration");
    title->move(0,0);
    int i=-1;
    lbl=new QLabel("Census ID:");
    lblId=new QLabel;
    layout->addWidget(lbl,++i,0);
    layout->addWidget(lblId,i,1);
    lbl=new QLabel("Name:");
    txtName=new QLineEdit;
    txtName->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtName,i,1);
    lbl=new QLabel("Gender:");
    txtGen =new QComboBox;
    txtGen->addItem("Male");
    txtGen->addItem("Female");
    txtGen->setFixedWidth(90);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtGen,i,1);
    lbl=new QLabel("Dno:");
    txtDno=new QLineEdit;
    txtDno->setFixedWidth(90);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtDno,i,1);
    lbl=new QLabel("Address1:");
    txtAdd1=new QComboBox;
    txtAdd1->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtAdd1,i,1);
    lbl=new QLabel("Address2:");
    txtAdd2=new QComboBox;
    txtAdd2->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtAdd2,i,1);
    lbl=new QLabel("City:");
    txtCity=new QComboBox;
    txtCity->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtCity,i,1);
    lbl=new QLabel("Taluk:");
    txtTk=new QComboBox;
    txtTk->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtTk,i,1);
    lbl=new QLabel("District:");
    txtDt=new QComboBox;
    txtDt->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtDt,i,1);
    lbl=new QLabel("Age:");
    txtAge=new QLineEdit;
    txtAge->setFixedWidth(90);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtAge,i,1);
    lbl=new QLabel("Occupation:");
    txtOcc=new QComboBox;
    txtOcc->setFixedWidth(200);
    layout->addWidget(lbl,++i,0);
    layout->addWidget(txtOcc,i,1);
    btnPhoto=new QPushButton("Photo");
    layout->addWidget(btnPhoto,++i,0);
    lblPhoto=new QLabel;
//    lblPhoto->setPixmap(QPixmap(":/img.jpg"));
    lblPhoto->resize(128,96);
    QScrollArea *scrollImg1=new QScrollArea;
    scrollImg1->setFixedSize(160,90);
    scrollImg1->setBackgroundRole(QPalette::Dark);
    scrollImg1->setWidgetResizable(true);
    scrollImg1->setWidget(lblPhoto);
    layout->addWidget(scrollImg1,i,1);
//    lblPhoto->setFixedSize();
    btnPhoto->setFixedSize(70,90);
    btnFinger=new QPushButton("Finger");    
    btnFinger->setFixedSize(70,90);
    layout->addWidget(btnFinger,++i,0);
    lblFinger=new QLabel;
//    lblFinger->setPixmap(QPixmap(":/img.jpg"));
    lblFinger->resize(132,186);
    QScrollArea *scrollImg=new QScrollArea;
    scrollImg->setFixedSize(160,90);
    scrollImg->setBackgroundRole(QPalette::Dark);
    scrollImg->setWidget(lblFinger);
    layout->addWidget(scrollImg,i,1);

    btnSign = new QPushButton("Signature");
    layout->addWidget(btnSign,++i,0);
    lblSign=new QLabel;
//    lblPhoto->setPixmap(QPixmap(":/img.jpg"));
    lblSign->resize(128,96);
    QScrollArea *scrollImg2=new QScrollArea;
    scrollImg2->setFixedSize(160,90);
    scrollImg2->setBackgroundRole(QPalette::Dark);
    scrollImg2->setWidgetResizable(true);
    scrollImg2->setWidget(lblSign);
    layout->addWidget(scrollImg2,i,1);
//    lblPhoto->setFixedSize();
    btnSign->setFixedSize(70,90);

    QHBoxLayout *hb=new QHBoxLayout;
    btnSave=new QPushButton("&Save [F2]");
    btnCancel=new QPushButton("&Cancel [F4]");
    btnSave->setShortcut(Qt::Key_F2);
    btnCancel->setShortcut(Qt::Key_F4);

    hb->addSpacing(20);
    hb->addWidget(btnSave);
    hb->addWidget(btnCancel);
    hb->addSpacing(30);

    layout->addLayout(hb,++i,0,1,0);
    btnSave->setFixedWidth(80);
    btnCancel->setFixedWidth(80);
    layout->setMargin(0);
    setFixedSize(320,220);
    scrollArea->setFixedSize(320,220);
    setWindowFlags(Qt::FramelessWindowHint);
    g->setLayout(layout);
    scrollArea->setWidget(g);
//    setTitle("Registeration");
    txtAdd1->setEditable(true);
    txtAdd2->setEditable(true);
    txtCity->setEditable(true);
    txtTk->setEditable(true);
    txtDt->setEditable(true);
    txtOcc->setEditable(true);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    setTabOrder(txtName,txtGen);
    setTabOrder(txtGen,txtDno);
    setTabOrder(txtDno,txtAdd1);
    setTabOrder(txtAdd1,txtAdd2);
    setTabOrder(txtAdd2,txtCity);
    setTabOrder(txtCity,txtTk);
    setTabOrder(txtTk,txtDt);
    setTabOrder(txtDt,txtAge);
    setTabOrder(txtAge,txtOcc);
    setTabOrder(txtOcc,btnPhoto);
    setTabOrder(btnPhoto,btnFinger);
    setTabOrder(btnFinger,btnSign);
    setTabOrder(btnSign,btnSave);
    setTabOrder(btnSave,btnCancel);
    connect(btnPhoto,SIGNAL(clicked()),this,SLOT(imgTrans()));
    connect(btnFinger,SIGNAL(clicked()),this,SLOT(fingerTrans()));
    connect(btnSign,SIGNAL(clicked()),this,SLOT(signTrans()));
    connect(btnSave,SIGNAL(clicked()),this,SLOT(saveTrans()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(cancelTrans()));
    QString reg="\\d?\\d?";
    txtAge->setValidator(new QRegExpValidator(QRegExp(reg),txtAge));
    imgFlag=false;
    fingFlag=false;
    signFlag=false;

    imgData.clear();
    fingerData.clear();

    PIC32->SetKeypad(ClanCor::Alphabets);

}

cenReg::~cenReg()
{

}

void cenReg::saveTrans()
{
    qDebug()<<"inside save";
    setEnabled(false);
    qDebug()<<"after disabled";
    QSqlQuery q;
    bool b;
    q=db->SelectQuery("select max(cenID)+1 from cenreg");
    if(db->IsLastError())
    {
        setEnabled(true);
        q.clear();
        return;
    }
    if(q.next())
    {
        if(q.value(0).isNull())
            ID = 1;
        else
            ID = q.value(0).toInt();
        if(fingFlag ||imgFlag || signFlag)
        {
            if(fingFlag && imgFlag && signFlag)
            {
                qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,photo,finger,sign, upload_flag)values("
                        + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,?,?,0)";
                q.prepare("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,photo,finger, sign, upload_flag)values("
                          + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,?,?,0)");
                q.addBindValue(imgData);
                q.addBindValue(fingerData);
                q.addBindValue(signData);

            }
            else
            {
                QString column, symbol;
                int cnt;
                if(fingFlag)
                {
                    column = column + ",finger";
                    cnt++;
                }
                if(imgFlag)
                {
                    column = column + ",photo";
                    cnt++;
                }
                if(signFlag)
                {
                    column = column + ",sign";
                    cnt++;
                }
                for(int i=0;i<cnt;i++)
                    symbol = symbol + ",?";
                qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ" + column + ",upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "'" + symbol + ",0)";
                q.prepare("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ" + column + ",upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "'" + symbol + ",0)");

                if(fingFlag)
                {
                    q.addBindValue(fingerData);
                }
                if(imgFlag)
                {
                    q.addBindValue(imgData);
                }
                if(signFlag)
                {
                    q.addBindValue(signData);
                }
            }
//            else if(fingFlag)
//            {
//                qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,finger, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)";
//                q.prepare("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,finger, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)");
//                q.addBindValue(fingerData);
//            }
//            else if(imgFlag)
//            {
//                qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,photo, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)";
//                q.prepare("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,photo, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)");
//                q.addBindValue(imgData);
//            }
//            else if(signFlag)
//            {
//                qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,sign, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)";
//                q.prepare("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ,sign, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',?,0)");
//                q.addBindValue(signData);
//            }
            if(!q.exec())
            {
                QMessageBox::critical(0,"Error","Error in saving \nID:"+ lblId->text() + "\n" + q.lastError().text());
                q.clear();
                btnSave->setEnabled(true);
                setEnabled(true);
                return;
            }
            QMessageBox::information(0,"Save","Saved Successfully");
        }
        else
        {
            qDebug()<<"insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',0)";
            b=db->DataBaseCommand("insert into cenreg (cenID,Name,Gender,Dno,address1,address2,city,taluk,district,Age,occ, upload_flag)values(" + QString::number(ID) + ",'" + txtName->text()  + "','" + txtGen->currentText() +"','" + txtDno->text() + "','" + txtAdd1->currentText() + "','" + txtAdd2->currentText() + "','" + txtCity->currentText() + "','" + txtTk->currentText() + "','" + txtDt->currentText() + "'," + txtAge->text() + ",'" + txtOcc->currentText() + "',0)");
            if(b)
            {
                QMessageBox::information(0,"Save","Saved Successfully");
            }
        }
        
    }
    q.clear();
    int res=QMessageBox::information(0,"80xx Demo","Do you need print?",QMessageBox::Yes,QMessageBox::No);
    if(res==QMessageBox::Yes)
    {
        printTrans();
    }
    setEnabled(true);
    cancelTrans();
}

void cenReg::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        cancelTrans();
    }
}

void cenReg::cancelTrans()
{
    censusMenu *cenmenu = new censusMenu;
    cenmenu->show();
    this->close();
    delete this;
}

void cenReg::imgTrans()
{
    Preview=new WebCamera();
    QImage image;
    if(Preview->ShowCamera(image))
    {
        QImage pic=image.scaled(128,96);//110,130;
        tmp = image;
        lblPhoto->setPixmap(QPixmap::fromImage(pic));
        pic.save(QDir::currentPath() +"/image1.jpg");
        lblPhoto->adjustSize();

        imgData.clear();
        QFile fileIn("image1.jpg");
        if (fileIn.open (QIODevice::ReadOnly))
        {
            imgData.append(fileIn.readAll());
            fileIn.close();
        }
        else
        {
            QMessageBox::critical(this,"Error.","Image Saving Error");
        }
        QFile::remove("image1.jpg");
        imgFlag=true;
    }
    delete Preview;

}

void cenReg::fingerTrans()
{
    fpt=new FingerPrint;
    QByteArray Data;
    QImage *grab=new QImage;
    if(fpt->EnrollFinger(Data,*grab))
    {
        fingerData=Data;
        grab->save("image1.jpg");
        QFile fileIn("image1.jpg");
        if (fileIn.open (QIODevice::ReadOnly))
        {
            fingerImage.append(fileIn.readAll());
            fileIn.close();
        }
        else
        {
            QMessageBox::critical(this,"Error.","Image Saving Error");
        }
        QFile::remove("image1.jpg");
       *grab=grab->scaled(132,186);
       lblFinger->setPixmap(QPixmap::fromImage(*grab));
       lblFinger->setScaledContents(true);
       grab->save("finger.jpg");
       fingFlag=true;
        //PIC32->GrayScalePrinting(*grab,false);
   }

    if(!fingFlag)
    {
        fingFlag=false;
        fingerData.clear();
        fingerImage.clear();
        lblFinger->clear();
    }
    delete fpt;
}

void cenReg::signTrans()
{
    setEnabled(false);

    QImage sig;
    if(!PIC32->GetSignature(sig))
    {
        setEnabled(true);
        return;
    }
    lblSign->setPixmap(QPixmap::fromImage(sig.scaled(154,52)));
    lblSign->setScaledContents(true);
    QBuffer buffer( &signData );
    buffer.open( QIODevice::WriteOnly);
    sig.save( &buffer, "PNG" ); // writes image into ba in PNG format
    signFlag = true;

    if(!signFlag)
    {
        signFlag=false;
    }
    qDebug()<<signFlag;
    setEnabled(true);
}

void cenReg::printTrans()
{
    setEnabled(false);
    Printer *prn=new Printer();
    prn->DrawLine();
    prn->DrawLine();
    prn->Add("***Census Demo Print***",Printer::FONTBIG,Printer::BOLD,Printer::ALIGNCENTER);
    prn->DrawLine();
    prn->DrawLine();
    prn->Add("Census ID:  " + QString::number(ID) ,Printer::FONTSMALL,Printer::BOLD);
    prn->Add("Name:  " + txtName->text() ,Printer::FONTSMALL,Printer::BOLD);
    prn->Add("Gender:  " + txtGen->currentText(),Printer::FONTSMALL,Printer::BOLD);
    prn->Add("Age:  " + txtAge->text(),Printer::FONTSMALL,Printer::BOLD);
    prn->Add("Occupation:  " + txtOcc->currentText(),Printer::FONTSMALL,Printer::BOLD);
    prn->Add("City:  " + txtCity->currentText(),Printer::FONTSMALL,Printer::BOLD);
    prn->Add("District-Taluk:  " + txtDt->currentText() + "-" + txtDt->currentText(),Printer::FONTSMALL,Printer::BOLD);
    prn->DrawLine();
    prn->Add("Photo",Printer::FONTSMALL,Printer::BOLDITALIC,Printer::ALIGNLEFT,true);
    if(!PIC32->GrayScalePrinting(tmp.scaled(132,132),true))
    {
        QMessageBox::critical(0,"80xx Demo", "Error while printing");
    }
    prn->Add("");
    prn->Add("Finger print",Printer::FONTSMALL,Printer::BOLDITALIC,Printer::ALIGNLEFT,true);
//    if(!PIC32->GrayScalePrinting(Finger))
//    {
//        QMessageBox::critical(0,"80xx Demo", "Error while printing");
//    }


    prn->AddBarcode("000" + QString::number(ID),Printer::FONTMEDIUM);
    prn->DrawLine();
    prn->DrawLine();
    if(!PIC32->SendData(true,*prn,true))
        delete prn;
    else
        delete prn;
    setEnabled(true);
}
