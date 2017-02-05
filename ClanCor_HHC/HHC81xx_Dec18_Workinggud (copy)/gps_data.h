#ifndef GPS_DATA_H
#define GPS_DATA_H

/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QLabel>
#include <QByteArray>
#include <QTextStream>
#include <QDateTime>
#include "qextserialport.h"


class GPS_data: public QObject
{   
   Q_OBJECT
public:
    GPS_data(const QString &r_const_strPORTNAME);
//    GPS_data(int i)
//    {
//        i = 0;
//    }
    bool gpsinit_error;
    bool RESPONSE;
    bool bAGPSflag;
    ~GPS_data();
//    bool getGPSFixedvalues(QString &r_strLongitude,QString &r_strLatitude,QString &r_strAltitude,QString &r_strNo_of_sat,QString &r_strSpeed);
    bool getGPSFixedvalues(QString &r_strLatitude,QString &r_strLongitude,QString &r_strAltitude,QString &r_strNo_of_sat,QString &r_strSpeed,QString &r_strTime);
    void setGPSStandby();
    void wakeupGPS();
    bool SendData(QString Data,int Timeout=1000);
    bool DownloadFile();
    bool GetExpiryDate();
    bool writeFile();
    QDateTime EndDateTime;
    QDateTime ConvertoUTC(int Gpsweek,int GpsTow);
    QString AlignNumber(int Value);
    QDialog *m_dialogAgps;
    /**
         * \var QLabel *m_labelStatus
         * \brief used to show the status in the gprs dialog.
         */
    QLabel *m_labelStatus;
signals:
    void showgpsicon(bool flag);
private:    
    QByteArray Received;
    QTextStream tstrm;
    QStringList strlstGGA;
    QString Data, tmp, strGroundspeed,str1,strUTCTime;
    QextSerialPort *ComPort_GPS;
    int i, numBytes;
    char readbuffer[10000] ;
    bool SerialPort_init(QString Port);
    void delay(int nMSec);
    void CheckReceive_File();


};

#endif // GPS_DATA_H
