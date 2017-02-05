#include "cglobal.h"
#include <csettingsfile.h>
using namespace ClanCor;
using namespace Global;

CPheripherals *Global::gpheripheralsPIC =  NULL;
CGsmModule *Global::ggsmModuleSimCom =  NULL;
GPS_data *Global::objGps =  NULL;
//QextSerialPort * Global::gserialportDebug = NULL;
#ifdef Q_WS_QWS
QWSServer *Global::gserverObj =  NULL;
#endif
CNetwork *Global::gnetworkActive =  NULL;
CInputMethod *Global::ginputMethodObj =  NULL;
CHHC80xxServer *Global::ghhc80xxServerObj =  NULL;
ClanCor::E_KeypadMode Global::gekeypadModeCurrent = eKeypadMode_ALPHABETS;
QSplashScreen *Global::gsplash =  NULL;
QLabel *Global::glabelStatus =  NULL;
QMutex Global::gmutex(QMutex::Recursive);

QSharedMemory Global::gsharedMemPIC("HHC8xxPIC32");
//QSharedMemory Global::gsharedMemKey("HHC8xxKEY");
QSharedMemory Global::gsharedMemGSM("HHC8xxGPRS");
QSharedMemory Global::gsharedMemNetwork("HHC8xxNW");

QString Global::gstrDeviceModel = "";
QString Global::gstrVirtualkey = "";
QString Global::gstrCheckgpsConfiguration="";
QString Global::gstrCheckGPRSConfiguration="";

//Testing
QString Global::gm_strGPRSGPSLatitude="";
QString Global::gm_strGPRSGPSLongitude="";
QString Global::gstrImageBrightness="";


bool Global::gbFirsCall = false;
bool Global::gbProcessRunning = false;
bool Global::gbIdleStatus = false;
bool Global::gbLanConnected = false;
bool Global::gbGprsConnected = false;
bool Global::gbAudioRunning = false;
bool Global::gbEnableMessageBoxGSM = true;
bool Global::gbEnableMessageBoxPrinter=true;
bool Global::gbGprsAlwaysOn = false;

int Global::gnGPRSModuleType = 0;

void Global::gInitialize()
{
    glabelStatus = new QLabel;
    glabelStatus->setStyleSheet("border-width: 2px;border-color:#2b396a; border-style: solid;background-color:white;color:black");
    glabelStatus->setFont(QFont("sans serif",14,1,false));
    glabelStatus->setAlignment(Qt::AlignCenter);
    glabelStatus->setWordWrap(true);
    glabelStatus->setWindowFlags(Qt::Dialog |  Qt::FramelessWindowHint);
    glabelStatus->setWindowModality(Qt::ApplicationModal);
    glabelStatus->setGeometry(30,60,260,120);
    glabelStatus->setFocusPolicy(Qt::NoFocus);
    //#if SERIAL_DEBUG_FLAG
    //    gPortInitialize(DEBUG_PORTNAME);
    //    gWriteDataToComport("Loading ClanCor HHC81xx SDK......");
    //#endif
    if (!gsharedMemPIC.attach() )
    {
        /* in first application call, shared memory is attach to failed */
        DEBUGMESSAGE("Unable to attach to shared memory segment.\n");
        gbFirsCall = true;
        gLoadIntoSharedPIC(const_strRUNNING);
        gLoadIntoSharedGSM(const_strRUNNING);
        gLoadIntoSharedNetwork(const_strRUNNING);
//        gLoadIntoSharedKey(const_strKEYPAD_ALPHABETS);
    }
    else
    {
        /* do the process for not first application call */
        gbFirsCall = false;
        gLoadIntoSharedPIC(const_strSTARTED);
        QString strData;
        if(gsharedMemGSM.attach())
        {
            if ( gLoadFromSharedGSM(strData) )
            {
                if ( ! strData.contains(const_strERROR) )
                {
                    gLoadIntoSharedGSM(const_strSTARTED);
                }
            }
        }
        if(gsharedMemNetwork.attach())
        {
            gLoadIntoSharedNetwork(const_strSTARTED);
        }
//        if(gsharedMemKey.attach())
//        {
//            gLoadIntoSharedKey(const_strKEYPAD_ALPHABETS);
//        }
    }
    gpheripheralsPIC = new CPheripherals(COPROCESSOR_PORTNAME);
//    qDebug()<<"\r gnGPRSModuleType..>>"<<gnGPRSModuleType;
    CSettingsFile settings("ClanCor","config.xml");
    settings.beginSettingsGroup("SDKConfiguration");
    gstrCheckGPRSConfiguration=settings.value("GPRS");
    if(gstrCheckGPRSConfiguration.toLower() == "yes")
    {
        if(gnGPRSModuleType == 2)
        {
//              qDebug()<<"\r gnGPRS  if..>>";
            system(QString("cmuxt -p /dev/ttyS1 -b 115200 -d").toLatin1());
            sleep(3);
            ggsmModuleSimCom = new CGsmModule(GSM_CMUX1PORTNAME);
        }
        else
        {
//             qDebug()<<"\r gnGPRS else ..>>";
            ggsmModuleSimCom = new CGsmModule(GSM_PORTNAME);
        }
    }
    gstrCheckgpsConfiguration=settings.value("GPS");
    if(gstrCheckgpsConfiguration.toLower() == "yes")
    {
        objGps = new GPS_data(GPS_PORTNAME);
//        qDebug()<<"\r Clancor sdfsd";
    }
}

void Global::gTerminate()
{
    /* release the allocated resources */
    if ( ! gbFirsCall )
    {
        gsharedMemPIC.detach();
        gsharedMemGSM.detach();
//        gsharedMemKey.detach();
    }
    //#if SERIAL_DEBUG_FLAG
    //    if ( gserialportDebug->isOpen() ) {
    //        //        /* close the debug port */
    //        gserialportDebug->close();
    //    }
    //    delete gserialportDebug;
    //#endif

    delete gpheripheralsPIC;
    delete ggsmModuleSimCom;
    delete glabelStatus;
    delete objGps;
}

bool Global::gLoadIntoSharedPIC(const QString &r_const_strDATA)
{
    if ( gbFirsCall )
    {
        /* there is no need to start or complete in first application call */
        if ( r_const_strDATA.trimmed() == const_strSTARTED) {
            return true;
        }
        else if ( r_const_strDATA.trimmed() == const_strCOMPLETED) {
            return true;
        }
    }

    /* prepare the data for write into shared memory */
    QString strData;
    strData = r_const_strDATA.leftJustified(const_nSHAREDM_MEMORY_MAXSIZE,' ',true);
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << strData;

    int size = buffer.size();
    if ( gbFirsCall ) {
        if  ( ! gsharedMemPIC.isAttached() ) {
            /* create the shared memory if not attached in first applcaition */
            if ( ! gsharedMemPIC.create(size) ) {
                DEBUGMESSAGE("Unable to create shared memory segment.");
                return false;
            }
        }
    }

    /* load data into shared memory */
    gsharedMemPIC.lock();
    char *pcTo = (char*)gsharedMemPIC.data();
    const char *pcFrom = buffer.data().data();
    memcpy(pcTo, pcFrom, qMin(gsharedMemPIC.size(), size));
    gsharedMemPIC.unlock();

    buffer.close();
    //qDebug()<<"Address loaded into Shared Memory"<<Data;
    if ( strData.trimmed() == const_strSTARTED ) {
        /* if second application is started, then wait until first application is paused or timeout */
        int nCount = 0;
        strData = "";
        do {
            /* read the data after wait 50 milli seconds to check paused */
            usleep(50000);
            nCount ++;
            gLoadFromSharedPIC(strData);
        } while ( strData.trimmed() != const_strPAUSED && nCount < 50 );
    }
    return true;
}

bool Global::gLoadFromSharedPIC(QString &r_strData)
{
    QBuffer buffer;
    QDataStream in(&buffer);

    /* read data from shared memory */
    gsharedMemPIC.lock();
    buffer.setData((char*)gsharedMemPIC.constData(), gsharedMemPIC.size());
    gsharedMemPIC.unlock();

    /* convert buffer data to string */
    buffer.open(QBuffer::ReadOnly);
    in >> r_strData;
    r_strData = r_strData.trimmed();
    buffer.close();
    //qDebug()<<"load from Shared Memory"<<r_strData;
    return true;
}

//bool Global::gLoadIntoSharedKey(const QString &r_const_strDATA)
//{

//    /* prepare the data for write into shared memory */
//    QString strData;
//    strData = r_const_strDATA.leftJustified(const_nSHAREDM_MEMORY_MAXSIZE,' ',true);
//    QBuffer buffer;
//    buffer.open(QBuffer::ReadWrite);
//    QDataStream out(&buffer);
//    out << strData;

//    int size = buffer.size();
//    if  ( ! gsharedMemKey.isAttached() ) {
//        /* create the shared memory if not attached in first applcaition */
//        if ( ! gsharedMemKey.create(size) ) {
//            DEBUGMESSAGE("Unable to create shared memory segment.");
//            return false;
//        }
//    }

//    /* load data into shared memory */
//    gsharedMemKey.lock();
//    char *pcTo = (char*)gsharedMemKey.data();
//    const char *pcFrom = buffer.data().data();
//    memcpy(pcTo, pcFrom, qMin(gsharedMemKey.size(), size));
//    gsharedMemKey.unlock();
//    buffer.close();
//    return true;
//}

//bool Global::gLoadFromSharedKey(QString &r_strData)
//{
//    QBuffer buffer;
//    QDataStream in(&buffer);

//    /* read data from shared memory */
//    gsharedMemKey.lock();
//    buffer.setData((char*)gsharedMemKey.constData(), gsharedMemKey.size());
//    gsharedMemKey.unlock();

//    /* convert buffer data to string */
//    buffer.open(QBuffer::ReadOnly);
//    in >> r_strData;
//    r_strData = r_strData.trimmed();
//    buffer.close();
//    return true;
//}

bool Global::gLoadIntoSharedGSM(const QString &r_const_strDATA)
{
    if ( gbFirsCall == true ) {
        /* there is no need to started or completed in first application call */
        if ( r_const_strDATA.trimmed()==const_strSTARTED) {
            return true;
        }
        else if ( r_const_strDATA.trimmed()==const_strCOMPLETED) {
            return true;
        }
    }

    /* prepare the data for write into shared memory */
    QString strData;
    strData = r_const_strDATA.leftJustified(50,' ',true);
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << strData;
    int size = buffer.size();
    if ( gbFirsCall ) {
        if ( ! gsharedMemGSM.isAttached() ) {
            /* create the shared memory if not attached in first applcaition */
            if (!gsharedMemGSM.create(size)) {
                DEBUGMESSAGE("Unable to create shared memory segment.");
                return false;
            }
        }
    }
    if ( ! gsharedMemGSM.isAttached() ) {
        return false;
    }
    // load into shared memory
    gsharedMemGSM.lock();
    char *pcTo = (char*)gsharedMemGSM.data();
    const char *pcFrom = buffer.data().data();
    memcpy(pcTo, pcFrom, qMin(gsharedMemGSM.size(), size));
    gsharedMemGSM.unlock();
    buffer.close();
    if ( strData.trimmed() == const_strSTARTED ) {
        /* if second application is started, then wait until first application is paused or timeout */
        int nCount = 0;
        strData = "";
        do {
            /* read the data after wait 50 milli seconds to check paused */
            usleep(50000);
            nCount ++;
            gLoadFromSharedGSM(strData);
        } while ( strData.trimmed() != const_strPAUSED && nCount < 50 );
    }
    return true;
}

bool Global::gLoadFromSharedGSM(QString &r_strData)
{
    QBuffer buffer;
    QDataStream in(&buffer);

    /* read data from shared memory */
    gsharedMemGSM.lock();
    buffer.setData((char*)gsharedMemGSM.constData(), gsharedMemGSM.size());
    gsharedMemGSM.unlock();

    /* convert buffer data to string */
    buffer.open(QBuffer::ReadOnly);
    in >> r_strData;
    r_strData = r_strData.trimmed();
    buffer.close();
    return true;
}

bool Global::gLoadIntoSharedNetwork(const QString &r_const_strDATA)
{
    if ( gbFirsCall == true ) {
        /* there is no need to started or completed in first application call */
        if ( r_const_strDATA.trimmed()==const_strSTARTED) {
            return true;
        }
        else if ( r_const_strDATA.trimmed()==const_strCOMPLETED) {
            return true;
        }
    }

    /* prepare the data for write into shared memory */
    QString strData;
    strData = r_const_strDATA.leftJustified(50,' ',true);
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << strData;
    int size = buffer.size();
    if ( gbFirsCall ) {
        if ( ! gsharedMemNetwork.isAttached() ) {
            /* create the shared memory if not attached in first applcaition */
            if (!gsharedMemNetwork.create(size)) {
                DEBUGMESSAGE("Unable to create shared memory segment.");
                return false;
            }
        }
    }
    if ( ! gsharedMemNetwork.isAttached() ) {
        return false;
    }
    // load into shared memory
    gsharedMemNetwork.lock();
    char *pcTo = (char*)gsharedMemNetwork.data();
    const char *pcFrom = buffer.data().data();
    memcpy(pcTo, pcFrom, qMin(gsharedMemNetwork.size(), size));
    gsharedMemNetwork.unlock();
    buffer.close();
    if ( strData.trimmed() == const_strSTARTED ) {
        /* if second application is started, then wait until first application is paused or timeout */
        int nCount = 0;
        strData = "";
        do {
            /* read the data after wait 50 milli seconds to check paused */
            usleep(50000);
            nCount ++;
            gLoadFromSharedNetwork(strData);
        } while ( strData.trimmed() != const_strPAUSED && nCount < 50 );
        //        qDebug()<<"\rNetwork thread paused..";
    }
    return true;
}

bool Global::gLoadFromSharedNetwork(QString &r_strData)
{
    QBuffer buffer;
    QDataStream in(&buffer);

    /* read data from shared memory */
    gsharedMemNetwork.lock();
    buffer.setData((char*)gsharedMemNetwork.constData(), gsharedMemNetwork.size());
    gsharedMemNetwork.unlock();

    /* convert buffer data to string */
    buffer.open(QBuffer::ReadOnly);
    in >> r_strData;
    r_strData = r_strData.trimmed();
    buffer.close();
    //qDebug()<<"load from Network Shared Memory"<<r_strData;
    return true;
}

void Global::gUpdateScreen(int nMsec)
{
    /* using event loop to update the pending process */
    gmutex.lock();
    QEventLoop eventLoop;
    QTimer timer;
    timer.setInterval(nMsec);
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    timer.start();
    eventLoop.exec();
    gmutex.unlock();
}

bool Global::gNetworkIPDetails(const QString const_stringIface, SNetworkIP &r_NetworkIP)
{
    /* read the ethernet configuration from network interface file */
    QString strData;
    QFile fileNetwork("/etc/network/interfaces");
    r_NetworkIP.m_strInterface = const_stringIface;
    if ( fileNetwork.open(QIODevice::ReadOnly) ) {
        strData = fileNetwork.readAll();
        fileNetwork.close();
        int nPos = strData.indexOf("iface " + const_stringIface.simplified());
        int nStart = 0;
        int nEnd = 0;
        if ( nPos >= 0 ) {
            nStart = strData.indexOf("address", nPos);
            if ( nStart >= 0 ) {
                nEnd = strData.indexOf("\n", nStart);
                if ( nEnd>= 0) {
                    r_NetworkIP.m_strIpAddress = strData.mid(nStart + 8, nEnd - nStart - 8);
                }
            }
            nStart = strData.indexOf("netmask", nPos);
            if ( nStart >= 0 ) {
                nEnd = strData.indexOf("\n", nStart);
                if ( nEnd>= 0 ) {
                    r_NetworkIP.m_strSubnetMask = strData.mid(nStart + 8, nEnd - nStart -8);
                }
            }
            nStart = strData.indexOf("gateway", nPos);
            if ( nStart >= 0 ) {
                nEnd = strData.indexOf("\n", nStart);
                if ( nEnd >= 0 ) {
                    r_NetworkIP.m_strGateway = strData.mid(nStart + 8, nEnd - nStart - 8);
                }
            }
            strData.clear();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

QString Global::gAlignNumber(qint64 nNumber, int nDigit)
{
    return gConvertToString(nNumber).rightJustified(nDigit,'0',true);
}

QString Global::gConvertToString(const QVariant &r_const_variantDATA)
{
    return QVariant(r_const_variantDATA).toString();
}

int Global::gConvertToInt(const QString &r_const_strDATA)
{
    return QString(r_const_strDATA.trimmed()).toInt();
}

void Global::gPicDebugging(const QString &r_const_strDATA)
{
    if ( r_const_strDATA.contains("^D") ) {
        int pos = r_const_strDATA.indexOf(QString("^D"),0);
        QString strDebug = r_const_strDATA.mid(pos);
        QList<QString> listData = strDebug.split('!');
        QString strData;
        foreach ( strData, listData ) {
            if ( strData != "" ) {
                if ( ! strData.contains("^DH") ) {
                    qDebug()<<"Pic32 Debug-> "<<strData.mid(6,strData.length()-3);
                }
                else {
                    qDebug()<<"Pic32 Debug KeyPad-> "<<strData.mid(6,strData.length()-3);
                }
            }
        }
        listData.clear();
        strData.clear();
        strDebug.clear();
    }
}

bool Global::gSysCommand(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput)
{    
    QEventLoop loop;
    QProcess process;
    bool bResponse = false;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QObject::connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)),&loop,SLOT(quit()));
    QObject::connect(&process, SIGNAL(finished(int)),&loop,SLOT(quit()));
    QObject::connect(&process,SIGNAL(error(QProcess::ProcessError)),&loop,SLOT(quit()));
    if ( r_const_strARGS == "" ) {
        process.start(r_const_strCOMMAND);
    }
    else {
        process.start(r_const_strCOMMAND,r_const_strARGS.split(" "));
    }
    if ( r_const_strCOMMAND.contains("ifconfig") || r_const_strCOMMAND.contains("iwconfig") ) {
        /* 2 second timeout to process these command */
        if(process.waitForFinished(5000))
        {
            //            qDebug()<<"***-----syscmd exec'ed";
        }
        else
        {
            //            qDebug()<<"***-----syscmd failed";
        }
    }
    else {
        loop.exec();
    }
    if ( process.state() == QProcess::Running ) {
        process.kill();
    }
    else {
        r_strOutput = process.readAllStandardOutput();
        DEBUGMESSAGE("output:" + r_strOutput);
        if ( r_strOutput == "" ) {
            r_strOutput = process.readAllStandardError();
            if ( r_strOutput != "Unknown error" ) {
                DEBUGMESSAGE("telnet: " + r_strOutput);
            }
        }
        else {
            bResponse = true;
        }
    }
    process.reset();
    process.close();
    return bResponse;
}
bool Global::gLoadFromSharedKey(QString &r_strData)
{
    QBuffer buffer;
    QDataStream in(&buffer);

    /* read data from shared memory */
    gsharedMemKey.lock();
    buffer.setData((char*)gsharedMemKey.constData(), gsharedMemKey.size());
    gsharedMemKey.unlock();

    /* convert buffer data to string */
    buffer.open(QBuffer::ReadOnly);
    in >> r_strData;
    r_strData = r_strData.trimmed();
    buffer.close();
    return true;
}

/* Temperarily implemented to fix hang while Disable GPRS, during GPRS not accessible  by askar in jul17*/
bool Global::gSysCommandtimeout(const QString &r_const_strCOMMAND, const QString &r_const_strARGS, QString &r_strOutput)
{
    QEventLoop loop;
    QProcess process;
    bool bResponse = false;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QObject::connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)),&loop,SLOT(quit()));
    QObject::connect(&process, SIGNAL(finished(int)),&loop,SLOT(quit()));
    QObject::connect(&process,SIGNAL(error(QProcess::ProcessError)),&loop,SLOT(quit()));
    if ( r_const_strARGS == "" ) {
        process.start(r_const_strCOMMAND);
    }
    else {
        process.start(r_const_strCOMMAND,r_const_strARGS.split(" "));
    }
    /* 2 second timeout to process these command */ //modify askar in jul 14
    if(process.waitForFinished(2000))
    {
        //            qDebug()<<"\r***-----syscmd exec'ed";
    }
    else
    {
        //            qDebug()<<"\r***-----syscmd failed";
    }
    if ( process.state() == QProcess::Running )
    {
        process.kill();
    }
    else
    {
        r_strOutput = process.readAllStandardOutput();
        DEBUGMESSAGE("output:" + r_strOutput);
        if ( r_strOutput == "" )
        {
            r_strOutput = process.readAllStandardError();
            if ( r_strOutput != "Unknown error" ) {
                DEBUGMESSAGE("telnet: " + r_strOutput);
            }
        }
        else {
            bResponse = true;
        }
    }
    process.reset();
    process.close();
    return bResponse;
}

bool Global::gSysCommand(const QString &r_const_strCOMMAND)
{
    QString strData;
    bool bResponse;
    bResponse = gSysCommand(r_const_strCOMMAND,"",strData);
    strData.clear();
    return bResponse;
}

bool Global::gPlayWav(const QString &r_const_strFILENAME)
{
    QFile fileIn(r_const_strFILENAME);
    QFile fileOut("/root/Dummy.wav");
    if ( fileIn.open(QIODevice::ReadOnly) ) {
        if ( fileOut.open(QIODevice::WriteOnly) ) {
            fileOut.write(fileIn.readAll());
            fileIn.close();
            fileOut.close();
            gSysCommand("/usr/bin/mplayer /root/Dummy.wav");//gSysCommand("aplay -Dplughw:0 Dummy.wav");
            QFile::remove("/root/Dummy.wav");
            return true;
        }
        fileIn.close();
    }
    return false;
}

void Global::gFreeCacheMemory()
{
#ifdef Q_WS_QWS
    system(QString("echo 3 > /proc/sys/vm/drop_caches").toLatin1());  //force to free cache memory
#endif
}

void Global::gWriteDataToComport(const QString &r_const_strDATA)
{
    QString strData;
    strData = r_const_strDATA;
//    if ( gserialportDebug->isOpen() ) {
//        /* write the data into debug port directly */
//        //        qDebug()<<"\r Port write Data"<<strData;
//        strData += "\r\n";
//        gserialportDebug->writeData(strData.toLatin1().constData(), strData.length());
//    }
    strData.clear();
}

bool Global::gPortInitialize(const QString &r_const_strPORTNAME)
{
//    /* initialize the port for write the debug data */
//    gserialportDebug = new QextSerialPort();
//    DEBUGMESSAGE("Creating QextSerialPort instance " + r_const_strPORTNAME);
//    gserialportDebug->setPortName(r_const_strPORTNAME);
//    gserialportDebug->setDataBits(DATA_8);
//    gserialportDebug->setParity(PAR_NONE);
//    gserialportDebug->setFlowControl(FLOW_OFF);
//    gserialportDebug->setStopBits(STOP_1);
//    if(r_const_strPORTNAME.contains("ttyS3"))
//    {
//        gserialportDebug->setBaudRate(BAUD9600);
//    }
//    else
//    {
//        gserialportDebug->setBaudRate(BAUD115200);
//    }
//    if ( gserialportDebug->open() )
//    {
//        return true;
//    }
//    else {
//        qDebug()<<" Failed to open Debug port.. ! ";
//        return false;
//    }
}
