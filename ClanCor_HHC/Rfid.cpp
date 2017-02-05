#include "Rfid.h"
#include "ccrfid.h"

Rfid::Rfid(QWidget *parent)
    : QDialog(parent)
{
    btnReadUid= new QPushButton("Read Uid");
    connect(btnReadUid,SIGNAL(clicked()),this,SLOT(ReadUid_Click()));
    btnRead= new QPushButton("Read Data");
    connect(btnRead,SIGNAL(clicked()),this,SLOT(ReadData_Click()));
    btnWrite=new QPushButton("Write Data");
    connect(btnWrite,SIGNAL(clicked()),this,SLOT(WriteData_Click()));

    QLabel *lblSector=new QLabel("Sector : ");
    QLabel *lblBlock=new QLabel("Block  : ");
    QLabel *lblData=new QLabel("Data : ");
    txt_Sector=new QSpinBox;
    txt_Sector->setRange(0,99);
    txt_block=new QSpinBox;
    txt_block->setRange(0,2);
    txt_Data=new QLineEdit;

    QVBoxLayout *l = new QVBoxLayout;
    QHBoxLayout *h = new QHBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    h->addWidget(lblSector);
    h->addWidget(txt_Sector);
    h->addWidget(lblBlock);
    h->addWidget(txt_block);
    h1->addWidget(lblData);
    h1->addWidget(txt_Data);
    h2->addWidget(btnRead);
    h2->addWidget(btnWrite);
    l->addLayout(h);
    l->addLayout(h1);
    l->addLayout(h2);
    l->addWidget(btnReadUid);
    l->setMargin(2);
    l->setSpacing(0);
    this->setFixedSize(320,220);
    setLayout(l);
}

void Rfid::ReadUid_Click()
{
    CCRFID *rf=new CCRFID;
    QString UId;
    rf->OpenDevice();
    if(rf->ReadUId(UId,20000))
    {
        QMessageBox::information(0,"Card UId",UId);
    }
    rf->CloseDevice();
    delete rf;
}

void Rfid::ReadData_Click()
{
    CCRFID *rf=new CCRFID;
    QString UId;
    QStringList Data;
    rf->OpenDevice();
    if(rf->ReadData(txt_Sector->value(),Data, UId,20000))
    {
        QMessageBox::information(0,"Card Data","Block 0: " + Data.at(0) +"\r\nBlock 1: " + Data.at(1) +"\r\nBlock 2: " + Data.at(2) );
    }
    rf->CloseDevice();
    delete rf;
}

void Rfid::WriteData_Click()
{
    CCRFID *rf=new CCRFID;
    QString UId;
    QStringList Data;
    rf->OpenDevice();
    if(rf->WriteData(txt_Sector->value(),txt_block->value(),txt_Data->text(),UId,20000))
    {
        QMessageBox::information(0,"Write Data","Success" );
    }
    rf->CloseDevice();
    delete rf;

}
