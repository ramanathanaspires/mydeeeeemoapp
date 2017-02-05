#include "widget.h"
#include "qextserialport.h"
#include <QDebug>
QextSerialPort *ComPort_SimCom;

Widget::Widget()
{

    QVBoxLayout *l=new QVBoxLayout;
    btn_Send=new QPushButton("Send");
    btn_Receive=new QPushButton("Receive");
    progress = new QProgressBar;
    progress->setRange(0,100);
    progress->setValue(0);
    progress->setFixedWidth(270);
    connect(btn_Send,SIGNAL(clicked()),this,SLOT(Send_Click()));
    //connect(btn_Receive,SIGNAL(clicked()),this,SLOT(Receive_Click()));
    connect(btn_Receive,SIGNAL(clicked()),this,SLOT(ListenServer()));
    l->addWidget(btn_Send);
    l->addWidget(btn_Receive);
    l->addWidget(progress);
    setLayout(l);
    setFixedSize(320,240);

    SerialPort_init("/dev/ttyUSB0");
}
void Widget::msleep(int msec)
{
    QEventLoop *Loop = new QEventLoop;
    QTimer *t = new QTimer;
    t->setInterval(msec);
    t->setSingleShot(true);
    QObject::connect(t,SIGNAL(timeout()),Loop,SLOT(quit()));
    t->start(msec);
    Loop->exec();
    delete t;
    delete Loop;

}
void Widget::ListenServer()
{
   tcpServer = new QTcpServer(this);
   connect(tcpServer, SIGNAL(newConnection()), this, SLOT(ClientConnect()));
    if (!tcpServer->listen(QHostAddress("0.0.0.0"),30000)) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
        return;
    }    
}

void Widget::ClientConnect()
{
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));      
    Receive_Click();
}

void Widget::readyRead()
{    
    if(CONNECTED)
    {
        progress->setValue((int)(100.0 * clientConnection->bytesAvailable()/No_of_Packets));
        if(clientConnection->bytesAvailable()==No_of_Packets)
        {
            FileData=clientConnection->readAll()            ;
            clientConnection->write("OK",2);
            QString dir = QFileDialog::getExistingDirectory(this, tr("Save Directory"), QDir::homePath() );
            qDebug()<<"Save Directory:"<<dir;
            if (!dir.isEmpty())
            {
                File=dir +"/"+File;
                QFile *Outfile=new QFile(File );
                if ( Outfile->open(QIODevice::WriteOnly))
                {
                     Outfile->setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
                     Outfile->write(FileData);
                     Outfile->close();
                     QMessageBox::information(0,"ClanCor","File Saved");
                }
                delete Outfile;
            }
        }
    }
}

void Widget::BytesWritten(qint64 Bytes)
{
  if(CONNECTED)
  {
      Total_Bytes+=Bytes;      
      progress->setValue((int)(100.0 * Total_Bytes/No_of_Packets));
  }
}
void Widget::Send_Click()
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(BytesWritten(qint64)));
    QString IpAddress;
    IpAddress="192.168.0.14";
    tcpSocket->connectToHost(QHostAddress(IpAddress),30000);
    tcpSocket->waitForConnected(3000);
    if(tcpSocket->state()!=QAbstractSocket::ConnectedState)
    {
        QMessageBox::critical(0,"File Transfer",IpAddress +" Ip is Not Connected");
        return;
    }
    Total_Bytes=0;
    QString FileName;
    //FileName="/mnt/Mahindra";
    FileName="8xx-Interface.zip";
    QFile *file=new QFile(FileName);
    for (int i=0;i<5;i++)
    {
        if(SendData(QString("REQUEST:" + FileName+"^").toAscii() ,2000)) break;
    }
    if(RESPONSE)
    {
        QByteArray Data;
        CONNECTED=false;
        if (file->open(QIODevice::ReadOnly) )
        {
            qDebug()<<"file opened successfully:"<<file->size();
            Data.clear();                        
            //Data=file->readAll();
            No_of_Packets=file->size();
            qDebug()<<"Data is Arrived"<<(No_of_Packets/1024) <<" KB";
            int n=No_of_Packets /1048576;
            if((No_of_Packets %1048576)!=0) n++;
            if(SendData(QString("SENDING:" + AlignNumber(No_of_Packets,10)).toAscii() ,3000))
            {
                CONNECTED=true;                                                
                //SendData(Data,10000);
                qint64 i;
                for(i=0;i<n;i++)
                {                                        
                    tcpSocket->write(file->read(1048576));
                    for(int j=0;j<10;j++)
                    {
                        if(tcpSocket->bytesToWrite()==0) break; else  msleep(100);
                    }
                }
                if((No_of_Packets %1048576) !=0)
                {                     
                     tcpSocket->write(file->read(No_of_Packets %1048576));
                }                
                if(!RESPONSE)
                {
                    QMessageBox::critical(0,"ClanCor","Communication Error");
                }else
                {                    
                    QMessageBox::information(0,"Clancor","File Send Successfully");
                }
            }
        }else
        {
            qDebug()<<"couldn't open  file";
        }
    }else
    {
        QMessageBox::critical(0,"Clancor","Device Not Connected");
    }

//    QString FileName;
//    FileName="Mahindra";
//    QFile *file=new QFile(FileName);
//    for (int i=0;i<5;i++)
//    {
//        if(SendData(QString("REQUEST:" + FileName+"^").toAscii() ,1000)) break;
//    }
//    RESPONSE=true;
//    if(RESPONSE)
//    {
//        QByteArray Data;
//        int i;
//        int ErrorCount;
//        if (file->open(QIODevice::ReadOnly) )
//        {
//            qDebug()<<"file opened successfully";
//            Data= file->readAll();
//            qDebug()<<"Data is Arrived"<<(Data.length()/1024) <<" KB";
//            qDebug()<<"lenght:"<<Data.length();
//            int n=Data.length() /8192;
//            No_of_Packets=n;
//            if((Data.length() %8192)!=0) No_of_Packets++;
//
//            if(SendData(QString("SENDING:" + AlignNumber(No_of_Packets,5)).toAscii() ,3000))
//            {
//                for(i=0;i<n;i++)
//                {
//                    ErrorCount=0;
//                    aa:
//                    if(!SendData(AlignNumber(i+1,5).toAscii()+ AlignNumber(8192+10,5).toAscii() + Data.mid(i*8192,8192),3000))
//                    {
//                        ErrorCount++;
//                        if(ErrorCount==3) break; else goto aa;
//                    }
//                    progress->setValue((int) (100.0*i/No_of_Packets));
//                }
//                if((Data.length() %8192) !=0 && RESPONSE==true)
//                {
//                    Data=Data.mid(i*8192);
//                    SendData(AlignNumber(i+1,5).toAscii()+ AlignNumber(Data.length()+10,5).toAscii() +Data,3000);
//                }
//                if(!RESPONSE)
//                {
//                    QMessageBox::critical(0,"ClanCor","Communication Error");
//                }else
//                {
//                    progress->setValue(100);
//                    QMessageBox::information(0,"Clancor","File Send Successfully");
//                }
//            }
//        }else
//        {
//            qDebug()<<"couldn't open  file";
//        }
//    }else
//    {
//        QMessageBox::critical(0,"Clancor","Device Not Connected");
//    }
}

QString Widget::AlignNumber(qint64 Value,int Width)
{
 QString Data=QVariant(Value).toString();
 return (Data.rightJustified(Width,'0',true));
}

bool Widget::SendData(QByteArray Data,long wait)
{
    RESPONSE=false;
    int i;
    //ComPort_SimCom->writeData(Data.data(),Data.length());
    //Data=Data +"\r\n";
    qDebug()<< tcpSocket->write(Data.data(),Data.length());
    int n=wait/5;
    for(i=1;i<=5;i++)
    {
     if(RESPONSE==true ) break;  else  msleep(n);
     Receive_Status();
    }    
    return RESPONSE;
}

void Widget::Receive_Status()
{
    char readbuffer[1024] ;
    //int numBytes = ComPort_SimCom->bytesAvailable();
    int numBytes = tcpSocket->bytesAvailable();

    if(numBytes>0)
    {
        //int i= ComPort_SimCom->readData(readbuffer,numBytes);
        int i= tcpSocket->read(readbuffer,numBytes);
        readbuffer[i] = '\0';
        if(i >0)
        {
            QString Data(readbuffer);
            qDebug()<<"Received:"<<Data;
            if(Data.contains("K"))
            {
                RESPONSE=true;
            }
        }
    }
}

void Widget::Receive_File()
{    
    char readbuffer[10000] ;
    //int numBytes = ComPort_SimCom->bytesAvailable();
    int numBytes = clientConnection->bytesAvailable();    
    if(numBytes>0)
    {                
        //int i= ComPort_SimCom->readData(readbuffer,numBytes);        
        int i= clientConnection->read(readbuffer,numBytes);
        readbuffer[i] = '\0';
        if(i >0)
        {
            QByteArray Received=QByteArray::fromRawData(readbuffer,i);                        
            Temp.append(Received);            
            if(CONNECTED)
            {                
                if(Temp.length()>=10)
                {
                    QString packet(Temp.left(10));
                    No_of_Bytes=packet.right(5).toInt();                    
                    if(No_of_Bytes==Temp.length())
                    {
                        if(packet.left(5).toInt()!=Pid)
                        {
                            Pid=packet.left(5).toInt();
                            progress->setValue((int) (100.0*Pid/No_of_Packets));
                            qApp->processEvents();
                            qDebug()<<"Data is Receiving"<<Temp.left(10);
                            FileData.append(Temp.mid(10,No_of_Bytes-10));
                            //ComPort_SimCom->writeData("OK",2);
                            clientConnection->write("OK",2);
                            Temp.clear();
                            RESPONSE=true;
                        }
                    }
                }
            }else
            {
                QString Data(readbuffer);
                qDebug()<<"Data Received:"<<Data;
                if(Data.contains("REQUEST:"))
                {
                    int pos=Data.indexOf("REQUEST:")+8;
                    int end=Data.indexOf("^");
                    File=Data.mid(pos,end-pos);
                    pos=File.lastIndexOf("/");
                    if(pos>=0)   File=File.mid(pos+1);
                    qDebug()<<"File:"<<File;
                    //ComPort_SimCom->writeData("OK",2);
                    clientConnection->write("OK",2);
                }else if(Data.contains("SENDING:"))
                {
                    No_of_Packets=Data.mid(8,10).toInt();
                    qDebug()<<"No of Packets:"<<No_of_Packets;                    
                    //ComPort_SimCom->writeData("OK",2);
                    clientConnection->write("OK",2);
                    CONNECTED=true;
                    Temp.clear();
                }
            }
        }
    }
}

void Widget::Receive_Click()
{
    CONNECTED=false;
    for (int i=0;i<10;i++)
    {
        msleep(1000);
        Receive_File();
        if(CONNECTED) break;
    }
    FileData.clear();
    if(CONNECTED)
    {
//            qDebug()<<"lenght:"<<FileData.length();
//            qDebug()<<"Data is Arrived"<<(FileData.length()/1024) <<" KB";
//            if(Pid!=No_of_Packets)
//            {
//                QMessageBox::critical(0,"ClanCor","Communication Error");
//                return;
//            }
//            QFile *Outfile=new QFile(File);
//            if ( Outfile->open(QIODevice::WriteOnly))
//            {
//                 Outfile->setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
//                 Outfile->write(FileData);
//                 Outfile->close();
//                 QMessageBox::information(0,"ClanCor","File Saved");
//            }
//            delete Outfile;
    }else
    {
        QMessageBox::critical(0,"Clancor","Device Not Connected");
    }
//    CONNECTED=false;
//    for (int i=0;i<5;i++)
//    {
//        msleep(1000);
//        Receive_File();
//        if(CONNECTED) break;
//    }
//    FileData.clear();
//    if(CONNECTED)
//    {
//        int ErrorCount;
//        do
//        {
//            ErrorCount=0;
//     aa:
//         Temp.clear();
//         RESPONSE=false;
//         for(int i=0;i<30;i++)
//         {
//             msleep(100);
//             Receive_File();
//             if(RESPONSE) break;
//             if(i==15 && Temp.count()==0 && ErrorCount<2)
//             {
//                 ErrorCount++;
//                 //ComPort_SimCom->writeData("OK",2);
//                 clientConnection->write("OK",2);
//                 goto aa;
//             }
//         }
//         if(!RESPONSE && Temp.count()!=0 && ErrorCount<2)
//         {
//             ErrorCount++;
//             goto aa;
//         }
//        }while(RESPONSE==true);
//            qDebug()<<"lenght:"<<FileData.length();
//            qDebug()<<"Data is Arrived"<<(FileData.length()/1024) <<" KB";
//            if(Pid!=No_of_Packets)
//            {
//                QMessageBox::critical(0,"ClanCor","Communication Error");
//                return;
//            }
//            QFile *Outfile=new QFile(File);
//            if ( Outfile->open(QIODevice::WriteOnly))
//            {
//                 Outfile->setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
//                 Outfile->write(FileData);
//                 Outfile->close();
//                 QMessageBox::information(0,"ClanCor","File Saved");
//            }
//            delete Outfile;
//    }else
//    {
//        QMessageBox::critical(0,"Clancor","Device Not Connected");
//    }
}

bool Widget::SerialPort_init(QString Port)
{
        ComPort_SimCom = new QextSerialPort();
        bool open=ComPort_SimCom->isOpen();
        if(open==true)
        {
            qDebug("Port is Already Open ");
            return true;
        }
        qDebug()<<"Creating QextSerialPort instance"<< Port;
        ComPort_SimCom->setPortName(Port);
        ComPort_SimCom->setDataBits(DATA_8);
        ComPort_SimCom->setParity(PAR_NONE);
        ComPort_SimCom->setFlowControl(FLOW_OFF);
        ComPort_SimCom->setStopBits(STOP_1);
        ComPort_SimCom->setBaudRate(BAUD256000);
        ComPort_SimCom->open();        
        bool Comopen2=ComPort_SimCom->isOpen(); // check whether serialport opened or not if open return true or return false
        if(Comopen2==true)
        {
            qDebug()<<"Port Open ";
            return true;
        }
        else
        {
            qDebug()<<"Port not Open ";
            return false;
        }
 }
