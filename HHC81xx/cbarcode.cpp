#include "cbarcode.h"
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

CBarCode::CBarCode(const QString &r_const_strPORTNAME) :
    m_bThreadRunning(false), m_bInitiated(false)
{
#if ENABLE_BARCODE
    if ( portInitialize(r_const_strPORTNAME) ) {
        m_bInitiated = true;
        startThread();
    }
#endif
}

CBarCode::~CBarCode()
{
    stopThread();
    delete m_serialportBarCode;
}

bool CBarCode::portInitialize(const QString &r_const_strPORTNAME)
{
    /* initialize the port for sending and receiving data */
    m_serialportBarCode = new QextSerialPort();
    DEBUGMESSAGE("Barcode module port name : " + r_const_strPORTNAME);
    m_serialportBarCode->setPortName(r_const_strPORTNAME);
    m_serialportBarCode->setDataBits(DATA_8);
    m_serialportBarCode->setParity(PAR_NONE);
    m_serialportBarCode->setFlowControl(FLOW_OFF);
    m_serialportBarCode->setStopBits(STOP_1);
    m_serialportBarCode->setBaudRate(BAUD9600);
    if ( m_serialportBarCode->open() ) {
        return true;
    }
    else {
        qDebug()<<"Failed to open barcode port.. !";
        return false;
    }
 }

void CBarCode::run()
{
    while ( m_bThreadRunning ) {
        arrivedData();
        msleep(100);
    }
}

void CBarCode::startThread()
{
    if ( ! isRunning() && m_bInitiated ) {
        /* start the thread */
        m_bThreadRunning = true;
#ifdef Q_WS_QWS
        start();
#endif
    }
}

void CBarCode::stopThread()
{
    if ( isRunning() ) {
        /* stop the thread */
        m_bThreadRunning = false;
        wait();
        terminate();
        msleep(50);
    }
}

void CBarCode::arrivedData()
{
    /* read the data from the buffer */
    char arr_cReadBuffer[1024] ;
    int nBytesAvailable = m_serialportBarCode->bytesAvailable();
    if ( nBytesAvailable > 0 ) {
        /* read the available bytes */
        int nBytesReceived = m_serialportBarCode->readData(arr_cReadBuffer, nBytesAvailable);
        if ( nBytesReceived > 0 ) {
            /* received buffer data */
            arr_cReadBuffer[nBytesReceived] = '\0';
            QString strData(arr_cReadBuffer);
            if ( strData != "") {
                /* emit the barcode data for dislpay the focued widget */
                emit barcodeData(strData);
            }
        }
    }
}
