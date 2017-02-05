#include "Fprint.h"

Fprint::Fprint(QWidget *parent)
    : QDialog(parent)
{
//    imageLabel = new QLabel;
//    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    imageLabel->setPalette(QPalette(QColor(Qt::white)));
//    imageLabel->setAutoFillBackground(true);
//    imageLabel->setScaledContents(true);
//    imageLabel->setFixedSize(120,160);
    txtUser=new QLineEdit;
    txtUser->setFixedWidth(180);
    cmbUsers=new QComboBox;

    cmbTemplateType = new QComboBox;
    cmbTemplateType->setFixedSize(180, 20);
    cmbTemplateType->addItem("SAGEM_PKCOMP");
    cmbTemplateType->addItem("SAGEM_PKMAT");
    cmbTemplateType->addItem("SAGEM_PKCOMP_NORM");
    cmbTemplateType->addItem("SAGEM_PKMAT_NORM");
//    cmbTemplateType->addItem("SAGEM_PKBASE");
//    cmbTemplateType->addItem("SAGEM_PKMOC");
    cmbTemplateType->addItem("ISO_PK_DATA_ANSI_378");
//    cmbTemplateType->addItem("ISO_PK");
//    cmbTemplateType->addItem("ISO_PK_PARAM");
//    cmbTemplateType->addItem("ISO_PK_DATA_ILO_FMR");
    cmbTemplateType->addItem("ISO_PK_DATA_ISO_FMR");
    cmbTemplateType->addItem("ISO_PK_DATA_ISO_FMC_CS");
    cmbTemplateType->addItem("ISO_PK_DATA_ISO_FMC_NS");
    cmbTemplateType->addItem("ISO_PK_DATA_MINEX_A");
    cmbTemplateType->setCurrentIndex(0);
    connect(cmbTemplateType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_setTemplateType(int)));

    cmbUsers->setFixedWidth(120);
    btnGetimage=new QPushButton("Press to \nScan \nFinger Image");
    btnGetimage->setFixedSize(100,160);
    btnGetimage->setPalette(QPalette(QColor(Qt::white)));
    btnGetimage->setAutoFillBackground(true);
    connect(btnGetimage,SIGNAL(clicked()),this,SLOT(Getimage_Click()));
    btnEnroll=new QPushButton("Enroll Finger");
    connect(btnEnroll,SIGNAL(clicked()),this,SLOT(EnrollFinger_Click()));
    btnVerify=new QPushButton("Verify");
    connect(btnVerify,SIGNAL(clicked()),this,SLOT(VerifyFinger_Click()));
    btnIdentify=new QPushButton("Identify");
    connect(btnIdentify,SIGNAL(clicked()),this,SLOT(IdentifyFinger_Click()));

    QVBoxLayout *vBoxTemplateType = new QVBoxLayout;
    QVBoxLayout *l = new QVBoxLayout;
    QHBoxLayout *h = new QHBoxLayout;
    QVBoxLayout *h1 = new QVBoxLayout;
    QVBoxLayout *hnew = new QVBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    btnIdentify->setFixedSize(80,40);
    btnVerify->setFixedSize(80,30);
    btnEnroll->setFixedSize(80,30);

    vBoxTemplateType->addWidget(cmbTemplateType);
    vBoxTemplateType->setAlignment(Qt::AlignCenter);
    h->addWidget(txtUser);
    h->addWidget(btnEnroll);
    h1->addWidget(cmbUsers);
    h1->addWidget(btnVerify);
    h1->setAlignment(Qt::AlignCenter);
//    hnew->addWidget(btnIdentify);
//    h1->addWidget(btnIdentify);

    QGroupBox *grpBoxSelectTemplate = new QGroupBox("Select Template Type");
    grpBoxSelectTemplate->setFixedHeight(50);
    grpBoxSelectTemplate->setLayout(vBoxTemplateType);
    QGroupBox *g = new QGroupBox("Enroll");
    g->setFixedHeight(50);
    g->setLayout(h);
    QGroupBox *g1 = new QGroupBox("Verify");
    g1->setFixedHeight(60);
    g1->setLayout(h1);
    QGroupBox *g2 = new QGroupBox("Identify");
    g2->setFixedHeight(50);
    btnIdentify->setParent(g2);
    btnIdentify->move(35,20);
    hnew->addWidget(grpBoxSelectTemplate);
    hnew->addWidget(g1);
    hnew->addWidget(g2);
    h2->addWidget(btnGetimage);
    h2->addLayout(hnew);
    l->addWidget(g);
    l->addLayout(h2);
    h->setMargin(0);
    h1->setMargin(0);
    h2->setMargin(0);
    h->setSpacing(0);
    h1->setSpacing(0);
    h2->setSpacing(0);
    l->setMargin(0);
    l->setSpacing(0);
    this->setFixedSize(320,220);

    setLayout(l);
    OpenDatabase("FingerDB");
    QSqlQuery *Retusers=new QSqlQuery(cn);
    if(ExecuteQuery("SELECT USER_NAME FROM USER_MASTER",Retusers))
    {
        while(Retusers->next())
        {
            cmbUsers->addItem(Retusers->value(0).toString());
        }
    }
    m_nTemplateTypeIndex = 0;       // To set default template type SAGEM_PK_COMP
    slot_setTemplateType(0);
    Retusers->clear();
    delete Retusers;
    setWindowFlags(Qt::FramelessWindowHint);
    move(0,20);
}

bool Fprint::OpenDatabase(QString DBName)
{
      cn= QSqlDatabase::addDatabase("QSQLITE","fprint");
      try
      {        
        cn.setDatabaseName(DBName);        
        if ( ! cn.open() ) {            
            QMessageBox::critical(0,"FingerPrint", "Cannot open database:"+ cn.lastError().text());
            return false;
        }                
        ExecuteQuery("CREATE TABLE IF NOT EXISTS USER_MASTER(USER_NAME VARCHAR(30),FINGER_DATA BLOB)");
        return true;
      }
    catch(...)
    {         
         QMessageBox::critical(0,"FingerPrint", "Query Execution Failed" );
         return false;
    }
}

bool Fprint::ExecuteQuery(QString strQuery)
{
        QSqlQuery q(cn);
        if(cn.isOpen())
        {
            q.clear();
            if(!(q.exec(strQuery)))
            {
               qDebug()<<"Execute Query Failed";
               if(q.lastError().number()!=19)
               {
                   QMessageBox::critical(0,"FingerPrint",   q.lastError().text());
                   q.clear();
                   return false;
               }
            }
              return false;
        }
        else
        {            
            QMessageBox::critical(0,"FingerPrint", "Connection is Closed" );
            return false;
        }
        q.clear();
        return true;
}
bool Fprint::ExecuteQuery(QString Query,QSqlQuery *Result)
{
    if(cn.isOpen())
    {
        if(!(Result->exec(Query)))
        {
            QMessageBox::critical(0,"FingerPrint",Result->lastError().text());
            return false;
        }
        size=0;
        while(Result->next())
        {
            size++;
        }
        Result->seek(-1);
    }
    else
    {
        QMessageBox::critical(0,"FingerPrint", "Connection is Closed" );
    }    
    return true;
}

void Fprint::Getimage_Click()
{
    setEnabled(false);
    if(btnGetimage->text()!="")
        btnGetimage->setText("");

   QImage Output;
   CFP_Morpho *Fpt = new CFP_Morpho();
   Fpt->setFPTemplateType(m_eFPTemplate);

   if(!Fpt->isError())
   {
       if(Fpt->Capture(sample, Output))
       {
           QIcon icon;
           icon.addPixmap(QPixmap::fromImage(Output.scaled(100,160)));
           btnGetimage->setIcon(icon);
           btnGetimage->setIconSize(QSize(100,160));
       }
       else
       {
           QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
           setEnabled(true);
           delete Fpt;
           return;
       }
   }else
   {
       QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
       setEnabled(true);
       delete Fpt;
       return;
   }
   delete Fpt;
   setEnabled(true);
   btnGetimage->setFocus();


}

void Fprint::EnrollFinger_Click()
{

    setEnabled(false);
    if(txtUser->text() == "")
    {
        QMessageBox::critical(0,"FingerPrint","Enter your name before enroll");
        setEnabled(true);
        txtUser->setFocus();
        return;
    }
    QSqlQuery *Retusers=new QSqlQuery(cn);
    if(ExecuteQuery("SELECT USER_NAME,FINGER_DATA FROM USER_MASTER",Retusers))
    {
        QByteArray SavedData;
        while(Retusers->next())
        {
            SavedData.clear();
            if(Retusers->value(0).toString() == txtUser->text())
            {
                QMessageBox::critical(0,"FingerPrint","Already enrolled with this name..! \nplease use different name..");
                setEnabled(true);
                txtUser->setFocus();
                return;
            }
        }
    }
    delete Retusers;

    QImage image;
    CFP_Morpho *Fpt = new CFP_Morpho;
    Fpt->setFPTemplateType(m_eFPTemplate);


   if(!Fpt->isError())
   {

       QByteArray EnrolledFinger;

       if(Fpt->EnrollFinger(EnrolledFinger, image)==true)
       {
           qDebug()<<"in Process";
           QByteArray SavedData;
           QSqlQuery rs(cn);
           rs.prepare("INSERT INTO USER_MASTER VALUES('" + txtUser->text() +"',?)");
           rs.addBindValue(EnrolledFinger);
           if(!rs.exec())
           {
              QMessageBox::critical(0,"FingerPrint","Failed to save");
           }
           else
           {
                cmbUsers->addItem(txtUser->text());
                QMessageBox::information(0,"FingerPrint", "Enrolled Successfully...");
           }
           rs.clear();
       }
       else
       {
           QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
           setEnabled(true);
           delete Fpt;
           return;
       }
   }
   else
   {
       QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
       setEnabled(true);
       delete Fpt;
       return;
   }
   delete Fpt;
   if(btnGetimage->text()!="")
        btnGetimage->setText("");

   QIcon icon;
   icon.addPixmap(QPixmap::fromImage(image.scaled(100,160)));
   btnGetimage->setIcon(icon);
   btnGetimage->setIconSize(QSize(100,160));

//    QIcon icon;
//    icon.addPixmap(QPixmap::fromImage(image));
//    btnGetimage->setIcon(icon);
//    btnGetimage->setIconSize(QSize(120,160));

    txtUser->clear();
    setEnabled(true);
    btnEnroll->setFocus();
}

void Fprint::VerifyFinger_Click()
{    
    setEnabled(false);
    if(cmbUsers->currentIndex()!=-1)
    {
        CFP_Morpho *Fpt=new CFP_Morpho;
        Fpt->setFPTemplateType(m_eFPTemplate);

        if(!Fpt->isError())
        {
            QSqlQuery *Retusers=new QSqlQuery(cn);
            if(ExecuteQuery("SELECT FINGER_DATA FROM USER_MASTER WHERE USER_NAME='" +cmbUsers->currentText() +"'", Retusers))
            {
                if(Retusers->next())
                {
                    QByteArray SavedData;
                    bool result;
                    SavedData=Retusers->value(0).toByteArray();
                    if(Fpt->VerifyFinger(SavedData, result))
                    {
                       if(result==true)
                            QMessageBox::information(0,"FingerPrint","Successfully Matched with " +cmbUsers->currentText() );
                       else
                            QMessageBox::critical(0,"FingerPrint","Not Match with "+cmbUsers->currentText() );
                    }
                    else
                    {
                        setEnabled(true);
                        delete Retusers;
                        delete Fpt;
                        return;
                    }
                    SavedData.clear();
                }
            }
            Retusers->clear();
            delete Retusers;
        }
        else
        {
            QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
            delete Fpt;
            setEnabled(true);
            return;
        }
        delete Fpt;
    }
    setEnabled(true);
    btnVerify->setFocus();
}

void Fprint::IdentifyFinger_Click()
{
    setEnabled(false);
    if(cmbUsers->currentIndex()!=-1)
    {
        CFP_Morpho *Fpt=new CFP_Morpho;
        Fpt->setFPTemplateType(m_eFPTemplate);
        if(!Fpt->isError())
        {
            QSqlQuery *Retusers=new QSqlQuery(cn);
            if(ExecuteQuery("SELECT USER_NAME, FINGER_DATA FROM USER_MASTER", Retusers))
            {
                if(size > 0)
                {
                    QList <QByteArray> lstByt_SavedData;
                    bool result;
                    while(Retusers->next())
                    {
                        lstByt_SavedData.append(Retusers->value(1).toByteArray());
                    }
                    int match_index;
                    if(Fpt->IdentifyFinger(lstByt_SavedData,result, match_index ))
                    {
                       if(result==true)
                            QMessageBox::information(0,"FingerPrint","Successfully Matched with " + cmbUsers->itemText(match_index));
                       else
                            QMessageBox::critical(0,"FingerPrint","Finger print not matched with the available user's");
                    }
                    else
                    {
                        setEnabled(true);
                        delete Retusers;
                        delete Fpt;
                        return;
                    }
                    lstByt_SavedData.clear();
                }
            }
            Retusers->clear();
            delete Retusers;
        }
        else
        {
            QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
            delete Fpt;
            setEnabled(true);
            return;
        }
        delete Fpt;
    }
    setEnabled(true);
    btnIdentify->setFocus();

//    setEnabled(false);
////   Fpt=new FingerPrint();
//   QByteArray EnrolledFinger;
//   bool Found=false;
//   QString UserName;
//   if(Fpt->CaptureFinger(EnrolledFinger))
//   {
//       qDebug()<<"Identify started"<<QDateTime::currentDateTime().time().currentTime();
//        QSqlQuery *Retusers=new QSqlQuery(cn);
//        if(ExecuteQuery("SELECT USER_NAME,FINGER_DATA FROM USER_MASTER",Retusers))
//        {
//            QByteArray SavedData;
//            bool result;
//            while(Retusers->next())
//            {
//                SavedData=Retusers->value(1).toByteArray();
//                //if(Fpt->SvrVerifyFinger(EnrolledFinger,SavedData,result))
//                if(Fpt->VerifyFinger(EnrolledFinger,SavedData,result))
//                {
//                   if(result==true)
//                   {
//                        Found=true;
//                        UserName=Retusers->value(0).toString();
//                        qDebug()<<"Found:"<<UserName;
//                        break;
//                    }
//                }
//                else
//                {
//                    setEnabled(true);
//                    return;
//                }
//            }
//            SavedData.clear();;
//        }
//        qDebug()<<"Identify completed"<<QDateTime::currentDateTime().time().currentTime();
//        if(Found==true)
//            QMessageBox::information(0,"Finger Print","Found User " +UserName );
//        else
//            QMessageBox::information(0,"Finger Print","Not Found " );
//        Retusers->clear();
//        delete Retusers;
//    }
//    EnrolledFinger.clear();
//    delete Fpt;
//    setEnabled(true);
}

Fprint::~Fprint()
{
    cn.close();
}

void Fprint::VerifyFinger_match()
{
    setEnabled(false);
    if(cmbUsers->currentIndex()!=-1)
    {
        CFP_Morpho *Fpt=new CFP_Morpho;
        Fpt->setFPTemplateType(m_eFPTemplate);

        if(!Fpt->isError())
        {
            QSqlQuery *Retusers=new QSqlQuery(cn);
            if(ExecuteQuery("SELECT FINGER_DATA FROM USER_MASTER WHERE USER_NAME='" +cmbUsers->currentText() +"'", Retusers))
            {
                if(Retusers->next())
                {
                    QByteArray SavedData;
                    bool result;
                    SavedData=Retusers->value(0).toByteArray();
                    if(Fpt->Verify_Match(sample, SavedData,result))
                    {
                       if(result==true)
                            QMessageBox::information(0,"FingerPrint","Successfully Matched with " +cmbUsers->currentText() );
                       else
                           QMessageBox::critical(0,"FingerPrint","Finger Not Matches with "+cmbUsers->currentText() );
                    }
                    else
                    {
                        setEnabled(true);
                        delete Retusers;
                        delete Fpt;
                        return;
                    }
                    SavedData.clear();
                }
            }
            Retusers->clear();
            delete Retusers;
        }
        else
        {
            QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
            delete Fpt;
            setEnabled(true);
            return;
        }
        delete Fpt;
    }
    setEnabled(true);
    btnVerify->setFocus();
}

void Fprint::IdentifyFinger_match()
{
    setEnabled(false);
    if(cmbUsers->currentIndex()!=-1)
    {
        CFP_Morpho *Fpt=new CFP_Morpho;
        Fpt->setFPTemplateType(m_eFPTemplate);

        if(!Fpt->isError())
        {
            QSqlQuery *Retusers=new QSqlQuery(cn);
            if(ExecuteQuery("SELECT USER_NAME, FINGER_DATA FROM USER_MASTER", Retusers))
            {
                if(size > 0)
                {
                    QList <QByteArray> lstByt_SavedData;
                    bool result;
                    while(Retusers->next())
                    {
                        lstByt_SavedData.append(Retusers->value(1).toByteArray());
                    }
                    int match_index;
                    if(Fpt->Identify_Match(sample, lstByt_SavedData, result, match_index ))
                    {
                       if(result==true)
                            QMessageBox::information(0,"FingerPrint","Successfully Matched with " + cmbUsers->itemText(match_index));
                       else
                            QMessageBox::critical(0,"FingerPrint","Finger print not matched with the available user's");
                    }
                    else
                    {
                        setEnabled(true);
                        delete Retusers;
                        delete Fpt;
                        return;
                    }
                    lstByt_SavedData.clear();
                }
            }
            Retusers->clear();
            delete Retusers;
        }
        else
        {
            QMessageBox::information(0,"FingerPrint", Fpt->getLastErrorString());
            delete Fpt;
            setEnabled(true);
            return;
        }
        delete Fpt;
    }
    setEnabled(true);
    btnIdentify->setFocus();
}

void Fprint::slot_setTemplateType(int nCurrentIndex)
{
    switch (nCurrentIndex)
    {
    case 0:
        m_eFPTemplate = CFP_Morpho::e_FPTemplate_SAGEM_PKCOMP;
        break;

    case 1:
        m_eFPTemplate = CFP_Morpho::e_FPTemplate_SAGEM_PKMAT;
        break;

    case 2:
        m_eFPTemplate = CFP_Morpho::e_FPTemplate_SAGEM_PKCOMP_NORM;
        break;

    case 3:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_SAGEM_PKMAT_NORM;
        break;

//    case 4:
//        m_eFPTemplate= CFP_Morpho::e_FPTemplate_SAGEM_PKBASE;
//        break;

//    case 5:
//        m_eFPTemplate= CFP_Morpho::e_FPTemplate_SAGEM_PKMOC;
//        break;

    case 4:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_ANSI_378;
        break;

//    case 7:
//        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK;
//        break;

//    case 8:
//        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_PARAM;
//        break;

//    case 9:
//        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_ILO_FMR;
//        break;

    case 5:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_ISO_FMR;
        break;

    case 6:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_ISO_FMC_CS;
        break;

    case 7:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_ISO_FMC_NS;
        break;

    case 8:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_ISO_PK_DATA_MINEX_A;
        break;

    default:
        m_eFPTemplate= CFP_Morpho::e_FPTemplate_SAGEM_PKCOMP;
        break;
    }
}
