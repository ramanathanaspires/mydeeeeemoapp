#include "cfiletransfer.h"
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

CFileTransfer::CFileTransfer()
{    
    m_labelStatus = new QLabel("File:",this);
    m_labelStatus->setWordWrap(true);
    m_labelStatus->setFont(QFont("sans serif",12,2,false));
    m_labelStatus->setAlignment(Qt::AlignCenter);
    m_checkBoxViaLan = new QCheckBox("via LAN",this);
    QLabel *labelIpAddress = new QLabel("Ip Address:",this);
    m_lineEditIpAddress = new QLineEdit(this);    
    m_lineEditIpAddress->setValidator(new QIntValidator(m_lineEditIpAddress));
    m_lineEditIpAddress->setInputMask("000.000.000.000");
    m_lineEditIpAddress->setEnabled(false);
    m_pushButtonOk = new QPushButton("[F2] Upload",this);
    m_pushButtonCancel = new QPushButton("[F4] Cancel",this);
    m_pushButtonOk->setShortcut(Qt::Key_F2);
    m_pushButtonCancel->setShortcut(Qt::Key_F4);
    m_progressbarSend = new QProgressBar(this);
    m_progressbarSend->setRange(0,100);
    m_progressbarSend->setValue(0);
    m_progressbarSend->setFixedWidth(280);
    connect(m_checkBoxViaLan, SIGNAL(stateChanged(int)), this, SLOT(on_checkBoxViaLanChk_stateChanged(int)));
    connect(m_pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));
    connect(m_pushButtonOk, SIGNAL(clicked()), this, SLOT(on_pushButtonon_pushButtonOk_clicked()));
    this->setGeometry(20,40,280,180);
    this->setWindowTitle("Upload File to System");
    this->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    this->setModal(true);
    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout;
    vBoxLayoutMain->addWidget(m_labelStatus);
    vBoxLayoutMain->addWidget(m_checkBoxViaLan);
    QHBoxLayout *hBoxLayoutIp = new QHBoxLayout;
    hBoxLayoutIp->addWidget(labelIpAddress);
    hBoxLayoutIp->addWidget(m_lineEditIpAddress);
    vBoxLayoutMain->addLayout(hBoxLayoutIp);
    vBoxLayoutMain->addWidget(m_progressbarSend,0,Qt::AlignCenter);
    QHBoxLayout *hBoxLayoutOption = new QHBoxLayout;
    hBoxLayoutOption->addWidget(m_pushButtonOk);
    hBoxLayoutOption->addWidget(m_pushButtonCancel);
    vBoxLayoutMain->addLayout(hBoxLayoutOption);
    vBoxLayoutMain->setSpacing(2);
    vBoxLayoutMain->setMargin(2);
    this->setLayout(vBoxLayoutMain);
}

CFileTransfer::~CFileTransfer()
{

}

void CFileTransfer::msleep(int msec)
{
    QEventLoop eventLoop;
    QTimer timerTimeout;
    timerTimeout.setInterval(msec);
    timerTimeout.setSingleShot(true);
    QObject::connect(&timerTimeout, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timerTimeout.start(msec);
    eventLoop.exec();
    timerTimeout.stop();
}

void CFileTransfer::on_checkBoxViaLanChk_stateChanged(int nstate)
{
    if ( nstate == Qt::Checked ) {
        m_lineEditIpAddress->setEnabled(true);
    }
    else {
        m_lineEditIpAddress->setEnabled(false);
    }
}

void CFileTransfer::bytesWritten(qint64 nBytes)
{
    if ( m_bConnected ) {
        m_nTotalBytes += nBytes;
        m_progressbarSend->setValue((int)(100.0 * m_nTotalBytes / m_nNoOfPackets));
    }
}

void CFileTransfer::on_pushButtonOk_clicked()
{    
    if ( m_checkBoxViaLan->checkState() == Qt::Checked && m_lineEditIpAddress->text() == "...") {
        QMessageBox::information(0, "File Transfer", "Enter IP Address...");
        return;
    }
    this->setDisabled(true);
    if ( m_checkBoxViaLan->checkState() == Qt::Checked ) {
        m_tcpSocket = new QTcpSocket(this);
        connect(m_tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
        m_tcpSocket->connectToHost(QHostAddress(m_lineEditIpAddress->text()),30000);
        m_tcpSocket->waitForConnected(3000);
        if ( m_tcpSocket->state() != QAbstractSocket::ConnectedState ) {
            QMessageBox::critical(0, "File Transfer", m_lineEditIpAddress->text() +" Ip is Not m_bConnected");
        }
        else {
            m_nTotalBytes = 0;
            QFile fileIn(m_strFileName);
            for ( int nCount = 0; nCount < 5; nCount ++) {
                if(sendData(QString("REQUEST:" + m_strFileName +"^").toAscii() ,2000))
                    break;
            }
            if ( m_bResponse ) {
                QByteArray Data;
                m_bConnected = false;
                if ( fileIn.open(QIODevice::ReadOnly) ) {
                    Data.clear();
                    m_nNoOfPackets = fileIn.size();
                    /*Split & send the file content by 1mb at a time */
                    int n = m_nNoOfPackets /1048576;        // 1Mb = 1048576 bytes
                    if ((m_nNoOfPackets % 1048576) != 0 ) { // To send remaining bytes
                        n++;
                    }
                    if ( sendData(QString("SENDING:" + gAlignNumber(m_nNoOfPackets,10)).toAscii() ,3000) ) {
                        m_bConnected = true;
                        qint64 i;
                        for ( i = 0; i < n; i ++ ) {
                            m_tcpSocket->write(fileIn.read(1048576));
                            for ( int j = 0; j < 10; j ++ ) {
                                if ( m_tcpSocket->bytesToWrite() == 0 ) {
                                    break;
                                }
                                else {
                                    msleep(100);
                                }
                            }
                        }
                        if ( ! m_bResponse ) {
                            QMessageBox::critical(0, "ClanCor", "Communication Error");
                        }
                        else {
                            QMessageBox::information(0,"Clancor","File Send Successfully");
                        }
                    }
                }
                else {
                    qDebug()<<"couldn't open  file";
                }
            }
            else {
                QMessageBox::critical(0,"Clancor","Device Not Connected");
            }
        }
    }
    else {
        QFile fileIn(m_strFileName);
        for ( int i = 0; i < 10; i ++ ) {
            if ( sendData(QString("REQUEST:" + m_strFileName+"^").toAscii() ,1000) ) {
                break;
            }
        }
        if ( m_bResponse ) {
            QByteArray Data;
            int i;
            int ErrorCount;
            if ( fileIn.open(QIODevice::ReadOnly) ) {
                Data = fileIn.readAll();
                int n = Data.length() / 8192;
                m_nNoOfPackets = n;
                if ( (Data.length() % 8192) != 0 ) {
                    m_nNoOfPackets++;
                }
                if ( sendData(QString("SENDING:" + gAlignNumber(m_nNoOfPackets,5)).toAscii() ,3000) ) {
                    for ( i = 0; i < n; i ++ ) {
                        ErrorCount = 0;
                        aa:
                        if ( ! sendData(gAlignNumber(i+1,5).toAscii()+
                                        gAlignNumber(8192+10,5).toAscii() +
                                        Data.mid(i*8192,8192),3000)) {
                            ErrorCount ++;
                            if ( ErrorCount == 3 ) {
                                break;
                            }
                            else {
                                goto aa;
                            }
                        }
                        m_progressbarSend->setValue((int) (100.0*i/m_nNoOfPackets));
                        qApp->processEvents();
                    }
                    if ( (Data.length() % 8192) != 0 && m_bResponse ) {
                        Data = Data.mid(i * 8192);
                        sendData(gAlignNumber(i+1,5).toAscii()+ gAlignNumber(Data.length()+10,5).toAscii() +Data,3000);
                    }
                    if ( ! m_bResponse ) {
                        QMessageBox::critical(0,"File Transfer","Communication Failed");
                    }
                    else {
                        m_progressbarSend->setValue(100);
                        QMessageBox::information(0,"File Transfer","File Send Successfully");
                        this->close();
                    }
                }
            }
            else {
                QMessageBox::critical(0,"File Transfer","Couldn't open file");
            }
        }
        else {
            QMessageBox::critical(0,"File Transfer","Device Not m_bConnected");
        }
    }
    this->setDisabled(false);
}

void CFileTransfer::on_pushButtonCancel_clicked()
{
    this->close();
}

bool CFileTransfer::sendFile(const QString r_const_strFILENAME)
{
    m_labelStatus->setText("File Name: " + r_const_strFILENAME);
    m_strFileName = r_const_strFILENAME;
    if ( ! QFile::exists(r_const_strFILENAME) ) {
        QMessageBox::critical(0,"File Transfer","File not exist");
        return false;
    }
    this->exec();
    return m_bResponse;
}

bool CFileTransfer::sendData(const QByteArray r_const_byteArrayDATA, long nWait)
{
    m_bResponse = false;
    if ( m_checkBoxViaLan->checkState() == Qt::Checked ) {
        m_tcpSocket->write(r_const_byteArrayDATA.data(),r_const_byteArrayDATA.length());
    }
    else
    {
//#ifdef SERIAL_DEBUG_FLAG
//        gserialportDebug->writeData(r_const_byteArrayDATA.data(),r_const_byteArrayDATA.length());
//#endif
    }
    int n = nWait / 5;
    for ( int nCount = 0; nCount < 5; nCount ++ ) {
        if ( m_bResponse ) {
            break;
        }
        else {
            msleep(n);
        }
        arrivedData();
    }
    return m_bResponse;
}

void CFileTransfer::arrivedData()
{
    char arr_cReadbuffer[1024] ;
    int numBytes=0;
    if ( m_checkBoxViaLan->checkState() == Qt::Checked ) {
        numBytes = m_tcpSocket->bytesAvailable();
    }
    else {
//        #ifdef SERIAL_DEBUG_FLAG
//        numBytes = gserialportDebug->bytesAvailable();
//#endif
    }
    if ( numBytes > 0 ) {
        int nBytesReceived=0;
        if ( m_checkBoxViaLan->checkState() == Qt::Checked ) {
            nBytesReceived = m_tcpSocket->read(arr_cReadbuffer,numBytes);
        }
        else {
//            #ifdef SERIAL_DEBUG_FLAG
//            nBytesReceived= gserialportDebug->readData(arr_cReadbuffer,numBytes);
//#endif
        }
        arr_cReadbuffer[nBytesReceived] = '\0';
        if ( nBytesReceived > 0 ) {
            QString Data(arr_cReadbuffer);
            if ( Data.contains("K") ) {
                m_bResponse = true;
            }
        }
    }
}
