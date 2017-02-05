#include "cnetwork.h"
#include "cglobal.h"
#include "QApplication"
#include "csettingsfile.h"

using namespace ClanCor;
using namespace Global;

const int const_nWAIT_FOR_RESPONSE                  = 3000; // 3 seconds
const int const_nWIFI_CONNECT_FAIL_TIMEOUT          = 50; // 1 mins

CNetwork::CNetwork():
    m_strError(""), m_bDefaultGprs(false), m_bDefaultEthernet(true), m_bWifiConnected(false), m_bWifiConnectedNetwork(false),
    m_bWifiDeviceFound(false), m_bWifiDisabled(false), m_nWifiEnableTryCount(4), m_nWifiDevSearchCount(0), m_nWifiConnectionTimeoutCount(0)
{
    initializeSocket();
    CSettingsFile settings1("ClanCor", "HHC80xxSDK1.xml");
    if(!settings1.contains("WIFISettings"))
    {
        ghhc80xxServerObj->setWIFION_OFF(false);
    }
    //if WIFI Module is ON Mode Check else dont check
    if(ghhc80xxServerObj->getWIFION_OFF())
    {
        /* To check if the Wifi device is available or not, the reason for this code in constructor was rtl modules were not found in run() */
        CheckWIFI();
    }
    else
    {
        //do nothing
    }
    if(gbFirsCall)
    {
        iffUp("eth0");
    }
}

void CNetwork::CheckWIFI()
{
    if(!m_bWifiDeviceFound )
    {
        int ncount = 0;
        QString stringWLanHWAddr;
        do
        {
            stringWLanHWAddr = hardwareAddress("wlan0");
            if(stringWLanHWAddr == "")
                msleep(500);
            ncount++;
        }while(stringWLanHWAddr == "" && ncount < 3);
        if(stringWLanHWAddr != "")
        {
            m_bWifiDeviceFound = true;
        }
        else
        {
            m_strError = "Wifi Device not found";
        }
    }
}

CNetwork::~CNetwork()
{
    /* stop the thread */
    stopThread();
    /* close the ethernet socket */
    closeSocket();
}

bool CNetwork::enableWifiModule()
{
    if(m_bWifiDeviceFound)
    {
        if ( ! m_bWifiConnected ) {
            /* enable the wifi*/
            //            gSysCommand("modprobe 8192cu");
            emit activeNetwork(eNetworkStatus_WIFI, -2);
            msleep(300);
            if(iffDown("wlan0"))
            {
                msleep(300);
                if(iffUp("wlan0"))
                {
                    msleep(1000);
                    if ( getWifiStatus(m_nWifiLevel) ) {
                        /* connect the wifi if failed, attach ethernet network interface */
                        m_bWifiConnectedNetwork = false;
                        if ( connectWifi() )
                        {
                            /* wifi connected */
                            m_bWifiConnected = true;
                            m_bWifiDisabled = false;
                        }
                        else
                        {
                            iffDown("wlan0");
                            if( m_bWifiDeviceFound && !m_bWifiConnected)
                                emit activeNetwork(eNetworkStatus_WIFI, -1);
                            msleep(200);
                            iffUp("eth0");
                            //                            gSysCommand("rmmod 8192cu");
                        }
                    }
                    else
                    {
                        iffDown("wlan0");
                        if( m_bWifiDeviceFound && !m_bWifiConnected)
                            emit activeNetwork(eNetworkStatus_WIFI, -1);
                    }
                }
                else
                {
                    m_strError = "Failed while interface up.. wlan0";
                    if( m_bWifiDeviceFound && !m_bWifiConnected)
                        emit activeNetwork(eNetworkStatus_WIFI, -1);
                }
            }
            else
            {
                m_strError = "Failed while interface down.. wlan0";
                if( m_bWifiDeviceFound && !m_bWifiConnected)
                    emit activeNetwork(eNetworkStatus_WIFI, -1);
            }
        }
    }else
    {
        CheckWIFI();
        enableWifiModule();
    }
    return m_bWifiConnected;
}

bool CNetwork::disableWifiModule(bool bIdleStanby)
{
    if(m_bWifiDeviceFound)
    {
        if ( m_bWifiConnected ) {
            /* disable wifi module if wifi is connected */
            m_bWifiConnected = false;
            m_bWifiConnectedNetwork = false;
            if(!bIdleStanby)
            {
                m_bWifiDisabled = true;
            }
            else
            {
                m_bWifiDisabled = false;
            }
            iffDown("wlan0");
            emit activeNetwork(eNetworkStatus_WIFI, -1);
            msleep(200);
            iffUp("eth0");
            //            gSysCommand("rmmod 8192cu");
            msleep(200);
            m_nWifiConnectionTimeoutCount = 0;
        }
    }else
    {
        m_strError = "Wifi Device not found.";
        return m_bWifiDeviceFound;
    }
    return true;
}


bool CNetwork::restart()
{
    if( !gbLanConnected )
    {
        if(m_bWifiDeviceFound)
        {
            if ( m_bWifiConnected ) {
                /* restart the wifi if config details are changed */
                pauseThread();
                emit activeNetwork(eNetworkStatus_WIFI, -1);
                iffDown("wlan0");
                msleep(200);
                iffUp("wlan0");
                m_bWifiConnectedNetwork = false;
                startThread();
            }
        }
        else
        {
            CheckWIFI();
            restart();
        }
    }
    return true;
}

void CNetwork::startThread()
{
    if ( ! isRunning() && gbFirsCall)
    {
        /* start the thread */
        m_bThreadRunning = true;
        start();
    }
    else
    {
        //        qDebug()<<"\r nw thread start failed-->"<<! isRunning() << gbFirsCall ;
    }
}

void CNetwork::startThreadWakeUp()
{
    if ( ! isRunning() && gbFirsCall) {
        /* start the thread */
        m_bThreadRunning = true;
        //        qDebug()<<"m_bWifiDisabled-->"<<m_bWifiDisabled;
        m_nWifiEnableTryCount = 4;
        m_nWifiDevSearchCount = 0;
        start();
    }
}

void  CNetwork::pauseThread()
{
    if ( isRunning() && gbFirsCall) {
        /* pause the thread */
        m_bThreadRunning = false;
        wait();
        qApp->processEvents();
    }
}

void  CNetwork::suspendNWThread()
{
    if ( isRunning() ) {
        /* pause the thread */
        m_bThreadRunning = false;
        wait();
        disableWifiModule(true);
    }
    if(!gbLanConnected && !gbGprsConnected )
        emit activeNetwork(eNetworkStatus_NONE, 0);
}

void CNetwork::stopThread()
{
    if ( isRunning() ) {
        /* stop the thread */
        m_bThreadRunning = false;
        wait();
        terminate();
        msleep(50);
    }
}

void CNetwork::run()
{
    if ( ! isEthernet() )
    {
        /* working with wifi, ethernet network will be detached.
           so, when wakeup from idle or standby attach the ethernet network */
        iffDown("eth0");
        iffUp("eth0");
    }

    int nWifiLoopCount = 0;
//    qDebug()<<"\r Network run gbGprsConnected..>>"<<gbGprsConnected;
    while ( m_bThreadRunning )
    {
        /* get the active network status by every 1 second */
        msleep(1000);

        /* To check if the Wifi device is available or not, the reason for this code in run() was asus modules were not found in constructor */
        if((!m_bWifiDeviceFound) && ghhc80xxServerObj->getWIFION_OFF())
        {
            int nCount = 0;
            QString stringWLanHWAddr;
            do
            {
                stringWLanHWAddr = hardwareAddress("wlan0");
                if(stringWLanHWAddr != "")
                {
                    m_bWifiDeviceFound = true;
                }
                else
                    m_nWifiDevSearchCount = 6;
                if(stringWLanHWAddr != "")
                {
                    m_bWifiDeviceFound = true;
                }
                else
                {
                    m_strError = "Wifi Device not found";
                    msleep(500);
                    nCount++;
                }
            }
            while(stringWLanHWAddr == "" && nCount < 3);
        }

        QString strSharedMemory;
        QString strSharedMemorygsm;
        /* read the data from shared memory */
        gLoadFromSharedNetwork(strSharedMemory);
        gLoadFromSharedGSM(strSharedMemorygsm);
        if ( const_strRUNNING == strSharedMemory )
        {
            /* ethernet device is found */
            if ( isEthernet() )
            {
                /* ethernet is connected */
                continue;
            }
            else
            {
                /* ethernet is not connected */
                if ( gbLanConnected )
                {
                    /* ethernet is disconnected */
                    gbLanConnected = false;
                    if( m_bWifiDeviceFound && !m_bWifiConnected)
                        emit activeNetwork(eNetworkStatus_WIFI, -1);
                    else
                        emit activeNetwork(eNetworkStatus_NONE, 0);
                    emit popUpMessage("Ethernet Disconnected");
                }
            }

            if((!m_bWifiDisabled) && (!gbLanConnected) && m_bWifiDeviceFound)
            {
                nWifiLoopCount++;
                /* To try Enable Wifi once for a 4 thread loop*/
                if(0 != m_nWifiEnableTryCount)
                {
                    /* To try Enable Wifi for maximum 4 times*/
                    if(4 == nWifiLoopCount)
                    {
                        if(enableWifiModule())
                        {
                            m_nWifiEnableTryCount = 0;
                        }
                        else
                        {
                            m_nWifiEnableTryCount--;
                            if( m_bWifiDeviceFound && (!m_bWifiConnected))
                                emit activeNetwork(eNetworkStatus_WIFI, -1);
                        }
                        nWifiLoopCount = 0;
                    }
                }
                else
                {
                    if(4 == nWifiLoopCount)
                        nWifiLoopCount = 0;
                }
            }
            if ( m_bWifiConnected && (!m_bWifiDisabled))
            {
                /* to process Wifi if connected, ie update signal level*/
                processWifi();
            }

            else if ( const_strGPRS_CONNECTEDCMUX == strSharedMemorygsm || gbGprsConnected  )
            {
                //                qDebug()<<"\r gbGprsConnected 1..>>"<<m_bDefaultEthernet<<"lan"<<gbLanConnected;
                /* gprs is connected */
                if ( m_bDefaultEthernet && ( ! gbLanConnected ) )
                {
                    //                    qDebug()<<"\r gbGprsConnected 2..>>"<<m_bDefaultEthernet<<"lan"<<gbLanConnected;
                    /* default route is gprs */
                    system(QString("route add default ppp0").toLatin1());
                    m_bDefaultEthernet = false;
                }
                //                qDebug()<<"\r gbGprsConnected 3..>>"<<m_bDefaultGprs;
                if ( ! m_bDefaultGprs )
                {
                    //                    qDebug()<<"\r gbGprsConnected 31..>>"<<m_bDefaultGprs;
                    /* gprs is active */
                    m_bDefaultGprs = true;
                    emit activeNetwork(eNetworkStatus_GPRS, 0);
                }
                //                qDebug()<<"\r gbGprsConnected 32..>>"<<m_bDefaultGprs;
                //                if(ggsmModuleSimCom->isInitiated())
                //                //Testing GPRS
                if(isGprsConnected())
                {
//                    qDebug()<<"\r gbGprsConnected 4..>>";
                    emit activeNetwork(eNetworkStatus_GPRS, 0);
                }
                else
                {
//                    qDebug()<<"\r gbGprsConnected 41..>>";
                    emit activeNetwork(eNetworkStatus_NONE, 0);
                    ggsmModuleSimCom->disableGprs();
                    ggsmModuleSimCom->wakeup();
                }

            }
            else
            {
                /* process if there is no active network */
                processNoNetwork();
            }
        }
        else if( const_strENABLEWIFI == strSharedMemory )
        {
            /*if Disable Wifi call from second Application8*/
            gbProcessRunning = true;
            if(gnetworkActive->enableWifiModule())
                gLoadIntoSharedNetwork(const_strRUNNING);
            else
                gLoadIntoSharedNetwork(const_strWIFIPROCESS_FAILED);
            gbProcessRunning = false;
        }
        else if( const_strDISABLEWIFI == strSharedMemory ) {
            /*if Disable Wifi call from second Application*/
            gbProcessRunning = true;
            if(gnetworkActive->disableWifiModule(false))
                gLoadIntoSharedNetwork(const_strRUNNING);
            else
                gLoadIntoSharedNetwork(const_strWIFIPROCESS_FAILED);
            gbProcessRunning = false;
        }
        else if ( const_strCOMPLETED == strSharedMemory ) {
            /* after sending data from second application, start sending data in thread */
            gLoadIntoSharedNetwork(const_strRUNNING);
            gbProcessRunning = false;
        }
        else if(isGprsConnected())       //Testing GPRS
        {
//            qDebug()<<"\r gbGprsConnected 444..>>";
            emit activeNetwork(eNetworkStatus_GPRS, 0);
        }
        else
        {
//            qDebug()<<"\r gbGprsConnected 4441..>>";
            emit activeNetwork(eNetworkStatus_NONE, 0);
            ggsmModuleSimCom->disableGprs();
            ggsmModuleSimCom->wakeup();
        }
    }
}

bool CNetwork::isEthernet()
{
    if ( getEthernetLinkStatus() ) {
        if ( ! gbLanConnected ) {
            /* ethernet is connected */
            emit activeNetwork(eNetworkStatus_ETHERNET, 0);
            emit popUpMessage("Ethernet Connected");
            if ( gstrDeviceModel.contains("HHC-7") ) {
                iffDown("eth0");
                iffUp("eth0");
            }
            if ( m_bWifiConnected ) {
                iffDown("wlan0");
            }
        }
        if ( ! m_bDefaultEthernet ) {
            /* Default Route is Ethernet */
            system(QString("route del default ppp0").toLatin1());
            emit activeNetwork(eNetworkStatus_ETHERNET, 0);
            m_bDefaultEthernet = true;
        }
        m_bDefaultGprs = false;
        gbLanConnected = true;
        return true;
    }
    else {
        /* ethernet is not connected */
        return false;
    }
}

bool CNetwork::connectWifi()
{
    /* get the gateway for ping the network  */
    QString strGateway;
    CHHC80xxServer::SWifiNetwork wifiNetworkConfig;
    if ( ghhc80xxServerObj->wifiConfig(wifiNetworkConfig) ) {
        strGateway = wifiNetworkConfig.m_strGateway;
    }
    else {
        strGateway = "";
    }

    /* detach the ethernet and connect wifi */
    iffDown("eth0");
    gSysCommand("sh /etc/wireless_script.sh");
    msleep(2500);
    if(APMacAddress() != "")
    {
        m_bWifiConnected = true;
        if ( strGateway != "" ) {
            /*Below ping process is used to ensure that network is reacheable*/
            if ( ping(strGateway) ) {
                emit activeNetwork(eNetworkStatus_WIFI, 0);
                emit popUpMessage("Wifi Connected");
                m_bWifiConnectedNetwork = true;
            }
            else
            {
                m_strError = "Please ensure WIFI gateway address is valid and it is active..";
                m_bWifiConnected = false;
                return m_bWifiConnected;
            }
        }
        else
        {
            m_strError = "Please configure WIFI..";
            m_bWifiConnected = false;
            return m_bWifiConnected;
        }
    }
    else
    {
        m_strError = "Failed to connect WIFI access point";
    }
    return m_bWifiConnectedNetwork;
}

void CNetwork::processWifi()
{
    if ( ! m_bWifiConnectedNetwork ) {
        /* check wifi is exist. if not exist, attach ethernet network interface */
        if ( getWifiStatus(m_nWifiLevel) ) {
            /* connect the wifi if failed, attach ethernet network interface */
            if ( ! connectWifi() ) {
                emit activeNetwork(eNetworkStatus_WIFI, -1);
                iffUp("eth0");
                msleep(200);
                isEthernet();
                m_nWifiConnectionTimeoutCount++;                //Fail timeout count increment
                if(m_nWifiConnectionTimeoutCount == const_nWIFI_CONNECT_FAIL_TIMEOUT)
                {
                    disableWifiModule(true);
                }
            }
            else
            {
                if(m_nWifiConnectionTimeoutCount != 0)
                    m_nWifiConnectionTimeoutCount = 0;
            }
        }
        else {
            /* wifi is disconnected */
            emit activeNetwork(eNetworkStatus_NONE,0);
            m_bWifiConnected = false;
            iffUp("eth0");
        }
    }
    if ( m_bWifiConnectedNetwork ) {
        /* read the wifi signal level because wifi is connected with network */
        if ( getWifiStatus(m_nWifiLevel) ) {
            emit activeNetwork(eNetworkStatus_WIFI, m_nWifiLevel);
            if ( m_nWifiLevel == 0 ) {
                /* no signal */
                processCommand("sh /etc/wireless_script.sh");
                m_nWifiConnectionTimeoutCount++;
                if(m_nWifiConnectionTimeoutCount == const_nWIFI_CONNECT_FAIL_TIMEOUT)
                {
                    disableWifiModule(true);
                    emit activeNetwork(eNetworkStatus_WIFI, -1);
                }
            }
            else
            {
                if(m_nWifiConnectionTimeoutCount != 0)
                    m_nWifiConnectionTimeoutCount = 0;
            }
        }
        else {
            /* wifi is disconnected */
            emit popUpMessage("Wifi DisConnected");
            iffUp("eth0");
            m_bWifiConnectedNetwork = false;
            m_bWifiConnected = false;
            if( m_bWifiDeviceFound && !m_bWifiConnected)
                emit activeNetwork(eNetworkStatus_WIFI, -1);
            else
                emit activeNetwork(eNetworkStatus_NONE, 0);
            msleep(500);
            m_nWifiEnableTryCount = 3;                     //To retry WIFI connectivity two times, when WIFI disconnected unexpectedly
        }
    }
}

void CNetwork::processNoNetwork()
{
    //    qDebug()<<"\r gbGprsConnected process network..>>"<<m_bDefaultGprs;
    if ( m_bDefaultGprs ) {
        //        qDebug()<<"\r gbGprsConnected process network.1.>>"<<m_bDefaultGprs;
        /* gprs is disconnected */
        m_bDefaultGprs = false;
        m_bDefaultEthernet = true;
        if( m_bWifiDeviceFound && !m_bWifiConnected)
            emit activeNetwork(eNetworkStatus_WIFI, -1);
        else
            emit activeNetwork(eNetworkStatus_NONE, 0);
    }
}

bool CNetwork::processCommand(const QString &r_const_COMMAND)
{
    if ( (! m_bThreadRunning) && (!m_bWifiDisabled)) {
        /* stop the process because thread may be stopped for goto standby or idle mode */
        return false;
    }
    else {
        QProcess process;
        bool bResponse = false;
        int nCount = 0;
        int Max = const_nWAIT_FOR_RESPONSE / 500;
        QEventLoop eventloopCmdExec;
        QTimer timerCmdExec;
        process.start(r_const_COMMAND);
        timerCmdExec.singleShot(500, &eventloopCmdExec, SLOT(quit()));
        connect(&process, SIGNAL(finished(int)), &eventloopCmdExec, SLOT(quit()));
        while ( QProcess::Running == process.state() ||
                QProcess::Starting == process.state() ) {
            nCount++;
            eventloopCmdExec.exec();
            /* process completed */
            if(!process.exitCode())
            {
                bResponse=true;
                break;
            }
            if ( nCount == Max || ( ! m_bThreadRunning ) ) {
                /* reach the timeout or thread may be passed */
                process.kill();
                break;
            }
        }
        process.reset();
        return bResponse;
    }
}
