/**  Class GPS_data is used to retrive GPS data from GPS module and display it on designed UI.
 *
 * #include "qextserialport.h"
 * -lHHC80xx
 *
 * Class GPS_data is used to retrive GPS data from GPS module and display
 * it on designed UI. The GPS device is loaded in file system as "/dev/ttyACM0"
 *
 * GPS device is a serial device, it is opened using qextserialport class.
 * class qextserialport is available in precompiled library called libHHC80xx.
 * GPS device is opened with baud rate 115200.
 *
 * *********** SAMPLE PROJECT FOR WORKING WITH GPS MODULE ON HHC80xx **********
 */

/*****************************************************************************
                                INCLUDES
******************************************************************************/

#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <iostream>
#include <QIcon>
#include <QVBoxLayout>
#include "gps_data.h"
#include <QVariant>
#include <QEventLoop>
#include <QTimer>
#include <cglobal.h>
#include<cpheripherals.h>

extern "C"
{
#include<uart.h>//Testing
}


using namespace std;
using namespace ClanCor;
using namespace Global;

GPS_data::GPS_data(const QString &r_const_strPORTNAME)
{
    gpsinit_error = false;
    m_dialogAgps = new QDialog;
    m_labelStatus = new QLabel("Please wait.... \n     It take Few Minutes to \n   Update Data to Module...");
    m_labelStatus->setFont(QFont("sans serif",16,2,false));
    m_labelStatus->setStyleSheet("background-color:#454d63;color:white");
    m_labelStatus->setAlignment(Qt::AlignCenter);
    m_dialogAgps->setGeometry(30,50,250,120);
    m_dialogAgps->setWindowTitle("AGPS");
    m_dialogAgps->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    m_dialogAgps->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    m_dialogAgps->setWindowModality(Qt::ApplicationModal);
    m_dialogAgps->setModal(true);
    m_dialogAgps->setEnabled(false);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(m_labelStatus);
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);
    //Testing
    bAGPSflag=false;
    m_dialogAgps->setLayout(vBoxLayout);
    /* initializing QextSerialPort object */
    ComPort_GPS = new QextSerialPort;
    /* calling SerialPort_init() function to open device "/dev/ttyS3"*/
    if(!SerialPort_init(r_const_strPORTNAME))
    {
        /* If device open failed return from constructor without doing further */
        QMessageBox::critical(0,"Error...","GPS Device not found!");
        gpsinit_error = true;
        return;
    }
    qDebug()<<"\r SDK GPS end design now wakeup go...>>";
    wakeupGPS();
    //    emit showgpsicon(false);
}
void GPS_data::CheckReceive_File()
{
    int nloop;
    QByteArray Received;
    numBytes = 0;
    for(nloop=0;nloop>=100;nloop++)
    {
        numBytes= ComPort_GPS->bytesAvailable();
        qDebug()<<"\r numbytes check from hardware tool"<<numBytes;
        if(numBytes>0)
        {
            i= ComPort_GPS->readData(readbuffer,numBytes);

            readbuffer[i] = '\0';
            if(i > 0)
            {
                Received=QByteArray::fromRawData(readbuffer,i);
                Received.clear();
            }
        }
        //        ComPort_GPS-flush();
    }
    return;

}
bool GPS_data::getGPSFixedvalues(QString &r_strLatitude, QString &r_strLongitude, QString &r_strAltitude, QString &r_strNo_of_sat, QString &r_strSpeed, QString &r_strTime)
{
    ComPort_GPS->flush();
    i = 0;
    numBytes = 0;
    strGroundspeed = "0";
    numBytes= ComPort_GPS->bytesAvailable();
    qDebug()<<"\r SDK GPS get ..>>"<<numBytes;
    if(!bAGPSflag)
    {
        if(numBytes >= 4000)
        {
            portFlush();//Testing
            delay(1000);
            numBytes= ComPort_GPS->bytesAvailable();
            qDebug()<<"\r SDK GPS flush ..>>"<<numBytes;
        }
        else
        {
            if(numBytes <= 0)
            {
                delay(1000);
                numBytes= ComPort_GPS->bytesAvailable();
                qDebug()<<"\r SDK GPS <=0 ..>>"<<numBytes;
            }
            else if(numBytes <= 500)//old data 250
            {
                delay(1000);
                numBytes= ComPort_GPS->bytesAvailable();
                qDebug()<<"\r SDK GPS  <= 250..>>"<<numBytes;
            }
            else
            {
                qDebug()<<"\r SDK GPS else  ..>>"<<numBytes;
            }
        }
    }

    if(numBytes > 0)
    {
        i= ComPort_GPS->readData(readbuffer,numBytes);
        readbuffer[i] = '\0';
        if(i > 0)
        {
            Received=QByteArray::fromRawData(readbuffer,i);
            Data = QString(Received);
            qDebug()<<"\r SDK GPS ..>>"<<Data;
            tstrm.setString(&Data);
            i = 0;
            /* clears the contents of labels from the form */
            while(!tstrm.atEnd())
            {
                tmp = tstrm.readLine();
                i++;
                //                if(tmp.contains("$GPGGA"))
                //                {
                if(tmp.mid(0,6) == "$GPGGA")
                {
                    strlstGGA = tmp.split(",",QString::KeepEmptyParts);
                    if(strlstGGA.size() > 9)
                    {
                        /* Checks, whether the GPS position have fixed or not */
                        if(strlstGGA.at(6).toInt() >= 1)
                        {
                            emit showgpsicon(true);
                            QString strhour,strminutes,strhourconvert,strSeconds,strsplit;
                            strsplit=strlstGGA.at(1);
                            strhour=strsplit.mid(0,2);
                            strminutes=strsplit.mid(2,2);
                            strSeconds=strsplit.mid(4,2);
                            int nMin,nHour,nMincal,nHourcal;
                            nMin = strminutes.toInt()+30;
                            nHour = strhour.toInt();
                            if(nMin >= 60)
                            {
                                nMincal =nMin-60;
                                nHourcal = nHour+6;
                            }
                            else
                            {
                                nMincal = nMin;
                                nHourcal= nHour+5;
                            }
                            strhourconvert =QString::number(nHourcal)+":"+QString::number(nMincal)+":"+strSeconds;
                            strUTCTime=QString::number(nHourcal)+":"+QString::number(nMincal)+":"+strSeconds;
                            r_strNo_of_sat = strlstGGA.at(7);
                            r_strLatitude = strlstGGA.at(2) + " " + strlstGGA.at(3);
                            r_strLongitude = strlstGGA.at(4) + " " + strlstGGA.at(5);
                            r_strAltitude = strlstGGA.at(9);
                            r_strSpeed = strGroundspeed;
                            r_strTime= strUTCTime;
                        }
                        else
                        {
                            r_strNo_of_sat = "";
                            r_strLatitude  = "";
                            r_strLongitude = "";
                            r_strAltitude = "";
                            r_strSpeed = "";
                        }
                    }
                    tmp.clear();
                    strlstGGA.clear();
                }
                else if(tmp.mid(0,6) == "$GPVTG")
                {
                    /* To get ground speed */
                    strlstGGA = tmp.split(",");
                    if(strlstGGA.size() > 7)
                    {
                        if(QString(strlstGGA.at(7)).toDouble() < 5)
                        {
                            strGroundspeed = "0";
                        }
                        else
                        {
                            strGroundspeed = strlstGGA.at(7);
                        }
                    }
                    tmp.clear();
                    strlstGGA.clear();
                }
                else if(tmp.mid(0,8) == "$PMTK707")
                {

                    strlstGGA = tmp.split(",");
                    EndDateTime=ConvertoUTC(QVariant(strlstGGA.at(4)).toInt(),QVariant(strlstGGA.at(5)).toInt());
                    qDebug()<<"\r SDK GPS fixed value receive...10>>"<<EndDateTime;
                    RESPONSE=true;
                }
                else
                {
                    continue;
                }
                //                }
                //                else
                //                {
                //                    continue;
                //                }
                if(r_strLatitude == "")
                {
                    qDebug()<<"\r SDK GPS fixed value lati empty continue..>>";

                    continue;
                }
                else
                {

                }
                ComPort_GPS->flush();
            }
            //            }//While loop
        }
    }
    else
    {
        ComPort_GPS->flush();
        return false;
    }
    strlstGGA.clear();
    tmp.clear();
    Data.clear();
    Received.clear();
    ComPort_GPS->flush();
    return true;
}

/* Destructor */
GPS_data::~GPS_data()
{
}

void GPS_data ::wakeupGPS()
{
    qDebug()<<"\r GPS wakeup start";
    QString Data;
    Data ="$PMTK225,0*2B\r\n";  //Always locate standby to  normal mode
    ComPort_GPS->writeData(Data.toAscii(),Data.length());
    delay(500);
    Data ="$PMTK286,1*23\r\n";//Enter into AIC mode
    ComPort_GPS->writeData(Data.toAscii(),Data.length());
    delay(500);
    Data ="$PMTK869,1,1*35\r\n";//Enter into EASY mode
    ComPort_GPS->writeData(Data.toAscii(),Data.length());
    delay(500);
}


//    Data="$PMTK185,0*22\r\n";//start log
//    ComPort_GPS->writeData(Data.toAscii(),Data.length());
//    delay(500);
//    Data ="$PMTK187,1,15*38\r\n";//set 15sec to take log
//    ComPort_GPS->writeData(Data.toAscii(),Data.length());
//    delay(500);


void GPS_data::delay(int nMSec)
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
/*
   Function SerialPort_init(QString Port) is used open GPS device
   Returns true, if device opened success fully, otherwise returns false
*/
bool GPS_data::SerialPort_init(QString Port)
{
    if(ComPort_GPS->isOpen())
    {
        ComPort_GPS->close();
    }
    ComPort_GPS->setPortName(Port);
    ComPort_GPS->setDataBits(DATA_8);
    ComPort_GPS->setParity(PAR_NONE);
    ComPort_GPS->setFlowControl(FLOW_OFF);
    ComPort_GPS->setStopBits(STOP_1);
    ComPort_GPS->setBaudRate(BAUD9600);
    ComPort_GPS->open(QIODevice::ReadOnly);
    bool Comopen2=ComPort_GPS->isOpen(); // check whether serialport is opened or not, if opened return true otherwise return false
    if(Comopen2==true)
    {
        ComPort_GPS->flush();
        return true;
    }
    else
    {
        QMessageBox::critical(0,"GPS","Port not open");
    }
    return false;
}

void GPS_data::setGPSStandby()
{
    if(!ghhc80xxServerObj->gpsiconflag)
    {
        QString Data;
        //Data ="$PMTK161,0*28\r\n";//Enter into standby mode
        Data ="$PMTK225,8*23\r\n";//Enter into Always LOcate standby mode
        ComPort_GPS->writeData(Data.toAscii(),Data.length());
        delay(1000);
    }
    else
    {
        emit showgpsicon(false);
    }
}

bool GPS_data::SendData(QString Data,int wait)
{
    RESPONSE=false;
    int n=(Data.length()/2)+3;
    char Buffer[n];
    int j=0;
    int Checksum=0;
    int value;
    for(int i=0 ;i<Data.length()-1;i=i+2)
    {
        value=Data.mid(i,2).toInt(0,16);
        Buffer[j]=value;
        if(j>1)
        {
            Checksum = Checksum ^ value;
        }
        j++;
    }
    Buffer[j]=QString::number(Checksum, 16).toUpper().right(2).toInt(0,16);
    Buffer[j+1]=0x0D;
    Buffer[j+2]=0x0A;
    Data+=QString::number(Checksum, 16).toUpper().right(2) + "0D0A";
    //    qDebug()<<"\r GPS SEND DATA"<<Data;
    ComPort_GPS->writeData(Buffer,n);
    n=wait/5;
    for(int i=1;i<=5;i++)
    {
        if(RESPONSE==true ) break;  else  usleep(n*1000);
    }
    return RESPONSE;
}

bool GPS_data::GetExpiryDate()
{
    //Testing
    portFlush();
    QString strLatitude,strLongitude,strAltitude,strNo_of_sat,strSpeed,strTime;
    SendData("04240E00FD000000000000",1000);// change binary mode to  NMEA mode
    delay(1000);
    numBytes=ComPort_GPS->bytesAvailable();
    qDebug()<<"\r numBytes..>>expiry"<<numBytes;

    Data="$PMTK607*33\r\n"; // EPO data status
    ComPort_GPS->writeData(Data.toAscii(),Data.length());
    delay(500);
    RESPONSE=false;
    int Errorcount=0;
    qDebug()<<"GPS expiry error..>>"<<Errorcount<<RESPONSE;
    do
    {
        sleep(3);//old 2
        getGPSFixedvalues(strLatitude,strLongitude,strAltitude,strNo_of_sat,strSpeed,strTime);
        Errorcount++;
        qDebug()<<"GPS expiry error. 11.>>"<<Errorcount<<RESPONSE;
    }while(RESPONSE==false && Errorcount<6);
    qDebug()<<"GPS expiry error.12.>>"<<Errorcount<<RESPONSE;
    if(RESPONSE==false)
    {
        QMessageBox::critical(0,"GPS...","Fail to read expiry date of AGPS...");
        return false;
    }
    //    qDebug()<<"\r\n EnddateTime"<<EndDateTime.toString("dd-MM-yyyy hh:mm:ss");
    return true;
}

QString GPS_data::AlignNumber(int Value)
{
    return QString::number(Value, 16).toUpper().rightJustified(2,'0');
}

QDateTime GPS_data::ConvertoUTC(int Gpsweek,int GpsTow)
{
    QDateTime  Dt(QDate(1980,1,6));
    Dt=Dt.addDays(Gpsweek*7);
    Dt=Dt.addSecs(GpsTow);
    return Dt;
}

bool GPS_data::writeFile()
{
    // code for G-Top module
    bAGPSflag = true;
    if( GetExpiryDate()==true)
    {
         bAGPSflag = false;
        if(QDateTime::currentDateTime().daysTo(EndDateTime) < 2)
        {

            if(QFile::exists("/root/MTK7d.EPO"))
            {
                Data="$PMTK253,1,0*37\r\n";// change NMEA mode to binary mode
                ComPort_GPS->writeData(Data.toAscii(),Data.length());
                sleep(2);
                QString fileName = "/root/MTK7d.EPO";
                QFile file(fileName);
                if(!file.open(QIODevice::ReadOnly))
                {
                    QMessageBox::critical(0,"File Error...","file opening error!");
                }
                else
                {
                    QByteArray data= file.readAll();
                    QString Hexdata="";
                    QString SNO;
                    int SequenceNo=0;
                    m_dialogAgps->show();
                    delay(50);
                    for(int i=0;i<data.length();i++)
                    {
                        Hexdata += AlignNumber((uchar)data.at(i));
                        if((i+1)%180==0)
                        {
                            SNO=QString::number(SequenceNo, 16).toUpper().rightJustified(4,'0');
                            Hexdata="0424BF00D202"+ SNO.right(2)+ SNO.left(2) + Hexdata ;
                            SendData(Hexdata);
                            Hexdata="";
                            SequenceNo++;
                        }
                    }
                    if(Hexdata!="")
                    {
                        SNO=QString::number(SequenceNo, 16).toUpper().rightJustified(4,'0');
                        Hexdata="0424BF00D202"+ SNO.right(2)+ SNO.left(2) + Hexdata.leftJustified(360,'0') ;
                        SendData(Hexdata);
                    }
                }
                SendData("04240E00FD000000000000",1000);// change binary mode to  NMEA mode
            }
            m_dialogAgps->hide();
            //            delay(500);
            //            GetExpiryDate();
            return true;
        }
        else
        {
            QMessageBox::about(0,"GPS"," AGPS already updated till "+EndDateTime.toString("dd-MM-yyyy hh:mm:ss"));
            return true;
        }
    }
    else
    {
         bAGPSflag = false;
    }
}
