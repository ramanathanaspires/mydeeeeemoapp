#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QTcpServer>
#include <QTcpSocket>
class Widget : public QWidget
{
    Q_OBJECT

    private:
        QTcpServer *tcpServer;
        QTcpSocket *clientConnection;
        QTcpSocket *tcpSocket;
        QPushButton *btn_Send;
        QPushButton *btn_Receive;
        QProgressBar *progress;
        QByteArray FileData;        
        QByteArray Temp;
        qint64 No_of_Packets;
        qint64 No_of_Bytes;
        qint64 Total_Bytes;
        int Pid;
        bool RESPONSE;
        bool CONNECTED;
        QString File;
        QString AlignNumber(qint64 Value,int Width);
    bool SerialPort_init(QString Port);
    bool SendData(QByteArray Data,long wait);
    void Receive_Status();
    void msleep(int msec);
private slots:    
    void BytesWritten(qint64 Bytes);
    void readyRead();
    void ListenServer();
    void ClientConnect();    
    void Send_Click();
    void Receive_Click();
    void Receive_File();
public:
    Widget();
};

#endif // WIDGET_H
