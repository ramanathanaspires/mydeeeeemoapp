#include "cgsmmodule.h"
#include "cglobal.h"
#include "csettingsfile.h"
#include <QDateTime>

using namespace ClanCor;
using namespace Global;
//AT#GPPPCFG="",25,2
//AT+CGDCONT?

const QString const_strMODEM_INTIATE                = "~^M~AT S7=45 S0=0 L1 V1 X4 &c1 E1 Q0^M";
const QString const_strENTER                        = "\x0D";
const QString const_strRESPONSE_OK                  = "OK";
const QString const_strAT_HANDSHAKING               = "AT";
const QString const_strAT_ECHO_OFF                  = "ATE0";
const QString const_strAT_DISPLAY_ERROR             = "AT+CMEE=2";
const QString const_strAT_SIM_STATUS                = "AT+CPIN?";
const QString const_strAT_GET_IMINUMBER             = "AT+CIMI";
const QString const_strAT_ENABLE_NETWORK_REG        = "AT+CREG=1";
const QString const_strAT_GET_NETWORK_REG           = "AT+CREG?";
const QString const_strAT_ENABLE_CELL_INFO          = "AT+CNMI=2,2,2,1,0";
const QString const_strAT_SET_SMS_TXT_MOD_PARAM     = "AT+CSMP=49,167,0,0";
const QString const_strAT_ENABLE_CELL_NETWORK       = "AT+CGREG=2";
const QString const_strAT_CELL_BROADCAST_SMS        = "AT+CSCB=0,\"80\"";
const QString const_strAT_GET_SMS_MODE              = "AT+CMGF?";
const QString const_strAT_SMS_TEXTMODE              = "AT+CMGF=1";
const QString const_strAT_STORE_PARAMETERS          = "AT&W";
const QString const_strAT_NT_NAME                   = "AT+COPS?";
const QString const_strAT_LIST_OPERATORS            = "AT+COPS=?";
const QString const_strAT_SIGNAL_QUALITY            = "AT+CSQ";
const QString const_strAT_LIST_SMS                  = "AT+CMGL=";
const QString const_strAT_WRITE_SMS                 = "AT+CMGS=";
const QString const_strAT_DELETE_SMS                = "AT+CMGD=";
const QString const_strAT_DELETE_ALL_SMS            = "AT+CMGDA=";
const QString const_strAT_DETACH_GPRS               = "AT+CGATT=0";
const QString const_strAT_DETACH_NETWORK            = "AT+CFUN=0";//Implement on Nov 4 2013
const QString const_strAT_MANUFACTURER_NAME         = "AT+GMI";
const QString const_strAT_ATTACH_NETWORK            = "AT+CFUN=1";
const QString const_strAT_MODULE_SOFTWRE_RESET      = "ATZ";
const QString const_strAT_SET_APNNAME               = "AT+CGDCONT=1,\"IP\",";
const QString const_strAT_SET_NETWORK_MODE          = "AT+COPS=";
const QString const_strRESPONSE_SIGNAL_QUALITY      = "+CSQ:";
const QString const_strRESPOSNE_LIST_SMS            = "+CMGL:";
const QString const_strRESPOSNE_SMS_SENT_INDEX      = "+CMGS:";
const QString const_strRESPOSNE_NT_NAME             = "+COPS:";
const QString const_strRESPOSNE_NETWORK_REG         = "+CREG:";
const QString const_strRESPOSNE_SMS_MODE            = "+CMGF:";
const QString const_strRESPOSNE_SIM_PIN             = "+CPIN:";
const QString const_strRESPOSNE_SMS_DELIVERY_STATUS = "+CDS:";
const QString const_strRESPOSNE_CME_ERROR           = "+CME ERROR:";
const QString const_strREC_UNREAD                   = "REC UNREAD";
const QString const_strREC_READ                     = "REC READ";
const QString const_strSTO_UNSENT                   = "STO UNSENT";
const QString const_strSTO_SENT                     = "STO SENT";
const QString const_strALL                          = "ALL";
const QString const_strSMSSENT                      = "SENT";
const QString const_strSMSDELIVERED                 = "DELIVERED";
const QString const_strPPPIPADDRESS                 = "AT#CGPADDR = 1";//Implement on Nov 4 2013
const QString const_strRESPONSEPPPIPADDRESS                 = "#CGPADDR: 1";
const QString const_strPPPIPADDRESSSECONDSOCKET     = "AT#CGPADDR = 2";
const QString const_strSOCKET2IPRESPONSE                 = "#CGPADDR: 2";
//Testing
const QString const_strM2MLOCATE                    = "AT#HTTPCFG=2,\"m2mlocate.telit.com\",9978,0,,,0,120,2";
const QString const_strSOCKET2APNSET                = "at+cgdcont=2,\"IP\",\"airtelgprs.com" ;
const QString  const_strSOCKET2IPGET                = "AT#SGACT=2,1";
const QString const_strCACHEDNS                    = "AT#CACHEDNS=1";
const QString const_strGPSPOSITION                 = "AT#AGPSSND";
const QString const_strGPSPOSITIONRESPONSE          = "#AGPSRING:";
const QString const_strSOCKETAVAILABLE              = "AT#SGACT?";
const QString const_strSOCKETAVAILABLERESPONSE      = "#SGACT";

const QString const_strDOUBLE_QUOTE                 = "\"";
const int const_nCTRL_PLUS_Z                        = 26;
const int const_nWAIT_FOR_RESPONSE                  = 100;

CGsmModule::CGsmModule(const QString &r_const_strPORTNAME):
    m_Mutex(QMutex::Recursive), m_bResponse(false), m_bThreadRunning(false),
    m_bThreadPause(false), m_bModuleInitiated(false),m_nRegStatus(0), m_nCSQValue(-1), m_nSMSSentIndex(-1), m_nSMSDeliveredIndex(-1), m_strApnName("")
{
    /* create a dialog screen for showing when gprs is enabled */
    m_dialogGprs = new QDialog;
    m_labelStatus = new QLabel("Try to Enabling GPRS and\nConnecting to Server...");
    m_labelStatus->setFont(QFont("sans serif",16,2,false));
    m_labelStatus->setStyleSheet("background-color:#454d63;color:white");
    m_labelStatus->setAlignment(Qt::AlignCenter);
    m_dialogGprs->setGeometry(30,50,250,120);
    m_dialogGprs->setWindowTitle("Please Wait...");
    m_dialogGprs->setWindowIcon(QIcon(":/icons-png/logo.ico"));
    m_dialogGprs->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    m_dialogGprs->setWindowModality(Qt::ApplicationModal);
    m_dialogGprs->setModal(true);
    m_dialogGprs->setEnabled(false);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(m_labelStatus);
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);
    m_dialogGprs->setLayout(vBoxLayout);

    /* disable the gprs connectivity in first library call for connect the module */
    if ( gbFirsCall && isGprsConnected() ) {
        gbGprsConnected = false;
        DEBUGMESSAGE("GPRS is going to Disabled");

        system(QString("route del default  ppp0").toLatin1());
        system(QString("sh /etc/ppp/peers/ppp-off").toLatin1());
    }
    if( gbFirsCall)
    {
        deleteDeliveryStatus();
    }
    else
    {
        QString strData;
        if ( gLoadFromSharedGSM(strData) )
        {
            if ( strData.contains(const_strERROR) )
            {
                m_strError = strData;
            }
        }
    }
    //  qDebug()<<"\r gnGPRS 2..>>";
    /* Initialize the gsm port */
    portInitialize(r_const_strPORTNAME);

    /* connect the slot for check the gprs connectivity & disconnect the gprs connectivity */
    //    connect(&m_timerGprsDisconnected, SIGNAL(timeout()), this, SLOT(on_timerGprsDisconnect_timeout()));
    connect(&m_timerGprsConnect, SIGNAL(timeout()), this, SLOT(on_timerClose_timeout()));
}

CGsmModule::~CGsmModule()
{
    /* stop the thread and close the port */
    stopThread();
    m_serialportSimCom->flush();
    m_serialportSimCom->close();

    /* free the allocated resources */
    delete m_dialogGprs;
    delete m_serialportSimCom;
}

bool CGsmModule::initModule()
{
    //    qDebug()<<"\r init modle GSM";
    /* it initialize the gsm module */
    int nErrorCount = 0;
    emit gsmNetworkSignal(0);
    m_labelStatus->setText("Initializing Module...");
    m_dialogGprs->show();
    gUpdateScreen();
    /* open the port if port is not opened */
    if ( ! m_serialportSimCom->isOpen() )
    {
        //        qDebug()<<"\r init modle GSM1";
        if ( ! m_serialportSimCom->open() )
        {
            //            qDebug()<<"\r init modle GSM 2";
            m_strError = "Gsm port not opened!";
            m_bModuleInitiated = false;
            return false;
        }
        //        qDebug()<<"\r init modle GSM 3";
    }
    //    qDebug()<<"\r init modle GSM 4";
    m_nTowerLevel = -1;

    do {
        //        qDebug()<<"\r init modle GSM 5";
        /* it initailize the modem */
        //        sendCommand(const_strMODEM_INTIATE,2000);
        /* send hanshaking for check module is available */
        if ( sendCommand(const_strAT_HANDSHAKING, 300) || m_bModuleInitiated )
        {
            //            qDebug()<<"\r init modle GSM 6";
            //Enable Network Register Creg=1
            sendCommand(const_strAT_ENABLE_NETWORK_REG,200);
            /* It sends the default commands to the module */
            sendCommand(const_strAT_ECHO_OFF,200);
            sendCommand(const_strAT_DISPLAY_ERROR,300);
            if ( m_bModuleInitiated )
            {
                //                qDebug()<<"\r init modle GSM 7";
                // Set APN for module;
                if ( m_strApnName != "" )
                    sendCommand(const_strAT_SET_APNNAME + const_strDOUBLE_QUOTE + m_strApnName + const_strDOUBLE_QUOTE,500);
                m_dialogGprs->close();
            }
            else
            {
                //                qDebug()<<"\r init modle GSM 8";
                /* send the following commands only once, when the application bootup */
                if ( sendCommand(const_strAT_SIM_STATUS,1000) )
                {
                    //                    qDebug()<<"\r init modle GSM 9";
                    sendCommand(const_strAT_GET_IMINUMBER,300);
                    //                    if ( sendCommand(const_strAT_GET_NETWORK_REG,1000) )
                    //                    {
                    //                        if ( m_nRegStatus == 0 )
                    //                        {
                    //                            /* if Network Mode is in Manual Mode Change To Automatic Mode  */
                    //                            m_bOperatorList=true;
                    sendCommand(const_strAT_NT_NAME,300);
                    //                            sleep(1);
                    //                            if(m_bNetworkMode)
                    //                                sendCommand(const_strAT_SET_NETWORK_MODE +"0,0",200);
                    //                            nErrorCount ++;
                    //                            sleep(1);
                    //                            /* sim not registered with the network */
                    //                            if(nErrorCount==5)
                    //                            {
                    //                                if(gbEnableMessageBoxGSM)
                    //                                    QMessageBox::information(0, "GSM", m_strError);
                    //                                break;
                    //                            }
                    //                            else if(nErrorCount==3 )
                    //                            {
                    //                                sendCommand(const_strAT_MODULE_SOFTWRE_RESET,300);
                    //                            }
                    //                            continue;
                    //                        }
                    //                    }
                    //Check Network Registration Status
                    m_labelStatus->setText("Trying to Register Network...");
                    gUpdateScreen();
                    if(!checkNetwork())
                    {
                        //                        qDebug()<<"\r init modle GSM 9";
                        m_dialogGprs->close();
                        m_bModuleInitiated = false;
                        return false;
                    }

                    /* these command is used to get the cell information */
                    sendCommand(const_strAT_ENABLE_CELL_INFO,200);
                    sendCommand(const_strAT_SET_SMS_TXT_MOD_PARAM,200);
                    sendCommand(const_strAT_ENABLE_CELL_NETWORK,300);
                    sendCommand(const_strAT_CELL_BROADCAST_SMS,200);
                    //Always Set to text Mode Initally
                    sendCommand(const_strAT_SMS_TEXTMODE,200);
                    sendCommand(const_strAT_STORE_PARAMETERS,300);
                    DEBUGMESSAGE("GSM Module Initiated Successfully");
                    //                    if ( m_nRegStatus != 2)
                    //                    {
                    //                        m_bModuleInitiated = true;
                    //                        emit modReady();
                    //                    }
                    //                    else
                    //                    {
                    //                        nErrorCount ++;
                    //                        //                        sleep(1);
                    //                        if(nErrorCount==5)
                    //                        {
                    //                            if(gbEnableMessageBoxGSM)
                    //                                QMessageBox::information(0, "GSM", m_strError);
                    //                            break;
                    //                        }
                    //                        else if(nErrorCount==3 )
                    //                        {
                    //                            sendCommand(const_strAT_MODULE_SOFTWRE_RESET,300);
                    //                        }
                    //                    }
                }
                else
                {
                    /* sim is not inserted */
                    m_dialogGprs->close();
                    if(gbEnableMessageBoxGSM)
                    {
                        qDebug()<<"\r SIM is not inserted";
                        QMessageBox::information(0,"GSM",m_strError);
                    }
                    break;
                }
                //                qDebug()<<"\r init modle GSM 10";
            }
            //            qDebug()<<"\r init modle GSM 11";
        }
        else {
            //            qDebug()<<"\r init modle GSM 12";
            /* try once again, if no response with handshaking, switch off & on the module */
            nErrorCount ++;
            m_strError = " Gsm module commuication Failed!";
            if(gbEnableMessageBoxGSM && nErrorCount == 5)
                QMessageBox::information(0,"GSM",m_strError);
            if(nErrorCount== 3 )
                sendCommand(const_strAT_MODULE_SOFTWRE_RESET,300);
        }
        //        qDebug()<<"\r init modle GSM 13"<<m_bModuleInitiated<<nErrorCount;
    } while ( ! m_bModuleInitiated  && nErrorCount < 5 );
    m_dialogGprs->close();
    return m_bModuleInitiated;
}

bool CGsmModule::checkNetwork()
{
    bool bResponse;
    int nErrorCount=0;
    do
    {
        if ( sendCommand(const_strAT_GET_NETWORK_REG,1000) )
        {
            if ( m_nRegStatus == 0 )
            {
                /* if Network Mode is in Manual Mode Change To Automatic Mode  */
                m_bOperatorList=true;
                sendCommand(const_strAT_NT_NAME,300);
                sleep(1);
                if(m_bNetworkMode)
                    sendCommand(const_strAT_SET_NETWORK_MODE +"0,0",200);
                nErrorCount ++;
                sleep(1);
                /* sim not registered with the network */
                if(nErrorCount==25)
                {
                    if(gbEnableMessageBoxGSM)
                        QMessageBox::information(0, "GSM", m_strError);
                    bResponse=false;
                    break;
                }
            }
            else if(m_nRegStatus ==1 || m_nRegStatus==5)//Need to change in Handle for Roaming
            {
                m_bModuleInitiated = true;
                emit modReady();
                bResponse=true;
                break;
            }
            else
            {
                nErrorCount ++;
                sleep(3);
                if(nErrorCount==25)
                {
                    if(gbEnableMessageBoxGSM)
                        QMessageBox::information(0, "GSM", m_strError);
                    bResponse=false;
                    break;
                }
            }
        }
        else
        {
            nErrorCount ++;
        }
    }
    while(nErrorCount<=25);
    return bResponse;
}

bool CGsmModule::initiatedModule()
{
    /* It intialize default command in gsm module for second applciation call */
    QString strData;
    if ( gLoadFromSharedGSM(strData) )
    {
        /* read the shared memory data for check it contains any error
           when initializing gsm module */
        if ( strData.contains(const_strERROR) )
        {
            /* read the error information from the data */
            m_bModuleInitiated = false;
            m_strError = strData.mid(const_strERROR.length()) ;
            DEBUGMESSAGE(m_strError);
            if ( m_serialportSimCom->isOpen() )
            {
                /* close the port if the port is opened */
                m_serialportSimCom->close();
            }
            return false;
        }
        else
        {
            /* Gsm module is initiated successfully with first application
               so execute the default commands */
            m_bModuleInitiated = true;
            sendCommand(const_strAT_HANDSHAKING, 300);
            sendCommand(const_strAT_ECHO_OFF, 200);
            sendCommand(const_strAT_DISPLAY_ERROR, 300);
            sendCommand(const_strAT_GET_IMINUMBER, 200);
            return m_bModuleInitiated;
        }
    }
    else
    {
        return false;
    }
}

bool CGsmModule::getNetwork(QString &r_NetworkName)
{
    /* get the network operator name */
    if ( m_bModuleInitiated )
    {
        if ( m_nRegStatus == 2)
            return false;
        if ( m_strNetwork != "" )
        {
            /* return the network name if already available */
            r_NetworkName = m_strNetwork;
            return true;
        }
        else
        {
            qDebug()<<"\r Network Name Not Selected";
        }
    }
}

bool CGsmModule::getOperatorList(QList<QString> &r_listOperators)
{
    /* search the list of operators available in that area */
    bool bResponse = false;
    if ( m_bModuleInitiated )
    {
        m_strNetwork = "";
        pauseThread();
        m_listOperators.clear();
        /* show the dialog when searching operators, because it will take more time */
        /* Minimum to get the Network information from module is about 43 seconds */
        m_labelStatus->setText("Searching Networks...");
        m_dialogGprs->show();
        gUpdateScreen();
        m_bOperatorList=false;
        bResponse=sendCommand(const_strAT_MANUFACTURER_NAME,300);
        sleep(1);
        bResponse = sendCommand(const_strAT_LIST_OPERATORS,50000);
        r_listOperators = m_listOperators;
        m_listOperators.clear();
        m_dialogGprs->close();
        if ( m_bThreadPause )
        {
            startThread();
        }
    }
    return bResponse;
}

bool CGsmModule::setGprsApn(const QString &r_const_strAPNNAME)
{
    /* set the gprs apn name for current network */
    bool bResponse = false;
    m_strApnName = r_const_strAPNNAME;
    if ( m_bModuleInitiated && r_const_strAPNNAME != "" )
    {
        pauseThread();
        //        qDebug()<<"\r Set GPRS APN  "<<r_const_strAPNNAME;
        bResponse = sendCommand(const_strAT_SET_APNNAME + const_strDOUBLE_QUOTE + r_const_strAPNNAME + const_strDOUBLE_QUOTE,1000);
        if ( m_bThreadPause )
        {
            startThread();
        }
    }
    return bResponse;
}

bool CGsmModule::setGprsNetwork(const QString &r_const_strNetworkID,const E_NetworkMode &r_const_enumNetworkMode)
{
    /* set the gprs Network Manually for current Selected Network ID */
    bool bResponse = false;
    if ( r_const_strNetworkID != "" )
    {
        if( r_const_enumNetworkMode == eNetworkMode_Manual)
        {
            pauseThread();
            m_strError="";
            /* show the dialog when Setting operators,Manually because it will take more time */
            m_labelStatus->setText("Setting Network Manually...");
            m_dialogGprs->show();
            gUpdateScreen();
            bResponse = sendCommand(const_strAT_SET_NETWORK_MODE +  QString::number(r_const_enumNetworkMode) + ",2," + const_strDOUBLE_QUOTE + r_const_strNetworkID + const_strDOUBLE_QUOTE,50000);
            sleep(3);
            m_dialogGprs->close();
            m_strNetwork="";
            if(!bResponse && gbEnableMessageBoxGSM)
            {
                if(m_strError=="")
                    QMessageBox::information(0, "GPRS Settings", "Automatic Network configured successfully ...!");
                else
                    QMessageBox::information(0, "GSM", m_strError);
            }
            if ( m_bThreadPause )
            {
                startThread();
            }
        }
    }
    else
    {
        pauseThread();
        m_strError="";
        /* show the dialog when Setting operators,Manually because it will take more time */
        m_labelStatus->setText("Setting Network Automatically...");
        m_dialogGprs->show();
        gUpdateScreen();
        bResponse = sendCommand(const_strAT_SET_NETWORK_MODE +  QString::number(r_const_enumNetworkMode) + ",0",23000);
        sleep(2);
        m_dialogGprs->close();
        m_strNetwork="";
        if(!bResponse && gbEnableMessageBoxGSM)
        {
            if(m_strError=="")
                QMessageBox::information(0, "GPRS Settings", "Automatic Network configured successfully ...!");
            else
                QMessageBox::information(0, "GSM", m_strError);
        }
        if ( m_bThreadPause )
            startThread();
    }
    return bResponse;
}

int CGsmModule::writeSms(const QString &r_const_strDESTINATION,
                         const QString &r_const_strMESSAGE)
{
    /* send the sms */
    bool bResponse = false, bHangUpCheck = false;
    int nCount = 0;
    do
    {
        bHangUpCheck = sendCommand(const_strAT_SIGNAL_QUALITY,500);
        if(bHangUpCheck)
        {
            int nLenght = r_const_strMESSAGE.length();
            nCount = nLenght / 160;
            if ( ( nLenght % 160 ) != 0 ) {
                nCount ++;
            }
            m_nSMSSentIndex = -1;

            if ( m_bModuleInitiated ) {
                /* first write the destination details, then give the message */
                pauseThread();
                msleep(300);
                sendCommand(const_strAT_WRITE_SMS + const_strDOUBLE_QUOTE + r_const_strDESTINATION + const_strDOUBLE_QUOTE , 350);
                msleep(100);
                bResponse = sendCommand(r_const_strMESSAGE + QChar(const_nCTRL_PLUS_Z), nCount * 8000);
                if(!bResponse)
                {
                    qDebug()<<"\rfailed..";
                }
            }
            if(!bResponse)
            {
                if ( m_serialportSimCom->isOpen() ) {
                    m_serialportSimCom->close();
                }
                if ( m_bThreadPause ) {
                    startThread();
                }
                return m_nSMSSentIndex;
            }
            CSettingsFile settings("ClanCor", "HHC80xxSMS.xml");
            settings.beginSettingsGroup("SMSDeliveryStatus");
            settings.setValue(QString::number(m_nSMSSentIndex), QString(r_const_strDESTINATION + "-|-" + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") + "-|-" + const_strSMSSENT));
            processPrevData();                  //To process delivery status, if CDS is received immediately
            if ( m_bThreadPause ) {
                startThread();
            }
        }
        else
        {
            if ( m_serialportSimCom->isOpen() ) {
                m_serialportSimCom->close();
            }
            nCount++;
        }

    }while(!bHangUpCheck && (nCount<3));
    if ( m_serialportSimCom->isOpen() ) {
        m_serialportSimCom->close();
    }
    return m_nSMSSentIndex;
}
bool CGsmModule::readSms(QList<CHHC80xx::SSmsDetail> &r_listMessages, CHHC80xx::E_MessageState eState)
{
    /* read the sms */

    bool bResponse = false;
    r_listMessages.clear();
    if ( m_bModuleInitiated )
    {
        QString Status;
        switch ( (int) eState )
        {
        /* get the string for the enum message state */
        case CHHC80xx::eMessageState_UNREAD:
            Status = const_strREC_UNREAD;
            break;
        case CHHC80xx::eMessageState_READ:
            Status = const_strREC_READ;
            break;
        case CHHC80xx::eMessageState_STORED_UNSENT:
            Status = const_strSTO_UNSENT;
            break;
        case CHHC80xx::eMessageState_STORED_SENT:
            Status = const_strSTO_SENT;
            break;
        default:
            Status = const_strALL;
        }
        pauseThread();
        /* write data to read the sms */
        bResponse = sendCommand(const_strAT_LIST_SMS + const_strDOUBLE_QUOTE + Status + const_strDOUBLE_QUOTE ,5000);
        if ( bResponse )
        {
            /* return the data if sms read sucessfully */
            r_listMessages = m_listSmsDetails;
        }
        r_listMessages.clear();
        if ( m_bThreadPause )
        {
            startThread();
        }
    }
    return bResponse;
}

bool CGsmModule::deleteSms(int nIndex)
{
    /* delete the sms of given memory index */
    bool bResponse = false;
    if ( m_bModuleInitiated )
    {
        pauseThread();
        bResponse = sendCommand(const_strAT_DELETE_SMS + gConvertToString(nIndex) ,2000);
        if ( m_bThreadPause )
        {
            startThread();
        }
    }
    return bResponse;
}

bool CGsmModule::smsDeliveryStatus(const int const_nSMSIndex)
{
    CSettingsFile settings("ClanCor", "HHC80xxSMS.xml");
    settings.beginSettingsGroup("SMSDeliveryStatus");
    if(settings.contains(QString::number(const_nSMSIndex)))
    {
        QStringList stringlistSMSStatus = settings.value(QString::number(const_nSMSIndex)).split("-|-");
        if(stringlistSMSStatus.size() > 2)
        {
            if(QString(stringlistSMSStatus.at(2)) == "DELIVERED")
            {
                stringlistSMSStatus.clear();
                return true;
            }
        }
        else
        {
            stringlistSMSStatus.clear();
            m_strError = "Failed to decode status from SMS delivery queue..!";
        }

    }
    else
    {
        m_strError = "Invalid SMS index..!";
    }
    return false;
}
bool CGsmModule::testGPS()
{
    qDebug()<<"\r test gps entered";
//    /* check if gprs is already connected */
//    if ( isGprsConnected())
//        return true;

    if(m_bModuleInitiated)
    {
        disableGprs();
        int l_iCount = 0;
        bool l_bResponse = false;
        if(!gbGprsAlwaysOn)
        {
            pauseThread();
        }
        do
        {
            l_bResponse = sendCommand(const_strAT_SIGNAL_QUALITY,500);
            if(l_bResponse)
            {
                if ( m_nCSQValue == 0 )
                {
                    m_strError = "No tower Signal";
                    DEBUGMESSAGE("No tower Signal");
                    return false;
                }
            }
            else
            {
                if ( m_serialportSimCom->isOpen() )
                {
                    /* close the port if the port is opened */
                    m_serialportSimCom->flush();
                    m_serialportSimCom->close();
                }
                l_iCount++;
                m_strError = "GSM module not ready..";
                DEBUGMESSAGE("GSM module not ready..");
            }
        }while(l_iCount != 2 && !l_bResponse);

        if(!l_bResponse)
        {
            if ( m_bThreadPause )
                startThread();
            return false;
        }

        DEBUGMESSAGE("CSQ Values is: " + m_nCSQValue );

        if ( m_nCSQValue < 10 && gbEnableMessageBoxGSM)
        {
            if ( QMessageBox::No == QMessageBox::warning(0,"GPRS","Tower Signal is Low!\n"
                                                         "Do you want to Establish the Connection?",
                                                         QMessageBox::No,QMessageBox::Yes))
            {
                m_strError = "Connection has been cancelled for low Tower Signal";
                return false;
            }
        }


        /* enable the gprs connectivity */
        m_labelStatus->setText("Trying to Enable GPRS and\nConnecting to Server...");
        if(gnGPRSModuleType == 2)
        {
            qDebug()<<"\r Enter testGps cmux3";
            //            system(QString("pppd call gprscmux").toLatin1());
            system(QString("pppd call gprscmux3").toLatin1());//Testing have implement
        }
        else
        {
            system(QString("pppd call gprs").toLatin1());
        }
        qDebug()<<"\r Enabling GPRS";
        gbProcessRunning = true;
        m_nCount = 0;
        sleep(2);
        /* for every second, check whether gprs is enabled or not */
        if(gbEnableMessageBoxGSM)
        {
            m_timerGprsConnect.start(1000);
            m_dialogGprs->exec();
        }
        else
        {
            on_timerClose_timeout();
        }
        m_timerGprsConnect.stop();
        gbProcessRunning = false;
        if (isGprsConnected() )
        {
            qDebug()<<"\r GPRS Enabled Successfully";
            gbGprsConnected = true;
            gLoadIntoSharedGSM(const_strGPRS_CONNECTED);
            if (m_bThreadPause)
            {
                /* write gprs connected status to shared memory for intimate the first application */
                if(gnGPRSModuleType == 2) // telit module mean start the thread
                    startThread();
                else
                {
                    /* close the port if the port is opened */
                    if ( m_serialportSimCom->isOpen() )
                        m_serialportSimCom->close();
                }
            }
            sleep(1);
            return true;
        }
        else
        {
            m_strError = "GPRS Enable Failed";
            qDebug()<<"\r GPRS Enabled Failed";
            system(QString("sh /etc/ppp/peers/ppp-off").toLatin1());
            sleep(1);
            system(QString("killall pppd").toLatin1());
            sleep(1);
            /* close the port if the port is opened */
            if ( m_serialportSimCom->isOpen() )
                m_serialportSimCom->close();
            sleep(1);
            for(int i=1; i<=5 ;i++)
                sendCommand("+++", 200);
            sendCommand("ATH0",500); // Detach GPRS
            sendCommand("AT+CGATT=0",500); // Detach GPRS
            disableGprs();
            return false;
        }
        if(isGprsConnected())
        {
            qDebug()<<"\r test gps end goes ";
        }
        else
        {
            qDebug()<<"\r test gps end goes 1";
            system(QString("pppd call gprscmux3").toLatin1());
        }
    }
}

bool CGsmModule::enableGprs()
{
    /* check if gprs is already connected */
    if ( isGprsConnected())
        return true;

    int l_iCount = 0;
    bool l_bResponse = false;
    if(!gbGprsAlwaysOn)
    {
        pauseThread();
    }
    do
    {
        l_bResponse = sendCommand(const_strAT_SIGNAL_QUALITY,500);
        if(l_bResponse)
        {
            if ( m_nCSQValue == 0 )
            {
                m_strError = "No tower Signal";
                DEBUGMESSAGE("No tower Signal");
                return false;
            }
        }
        else
        {
            if ( m_serialportSimCom->isOpen() )
            {
                /* close the port if the port is opened */
                m_serialportSimCom->flush();
                m_serialportSimCom->close();
            }
            l_iCount++;
            m_strError = "GSM module not ready..";
            DEBUGMESSAGE("GSM module not ready..");
        }
    }while(l_iCount != 2 && !l_bResponse);

    if(!l_bResponse)
    {
        if ( m_bThreadPause )
            startThread();
        return false;
    }

    DEBUGMESSAGE("CSQ Values is: " + m_nCSQValue );

    if ( m_nCSQValue < 10 && gbEnableMessageBoxGSM)
    {
        if ( QMessageBox::No == QMessageBox::warning(0,"GPRS","Tower Signal is Low!\n"
                                                     "Do you want to Establish the Connection?",
                                                     QMessageBox::No,QMessageBox::Yes))
        {
            m_strError = "Connection has been cancelled for low Tower Signal";
            return false;
        }
    }


    /* enable the gprs connectivity */
    m_labelStatus->setText("Trying to Enable GPRS and\nConnecting to Server...");
    if(gnGPRSModuleType == 2)
    {
        system(QString("pppd call gprscmux").toLatin1());
        //        system(QString("pppd call gprscmux3").toLatin1());//Testing have implement
    }
    else
    {
        system(QString("pppd call gprs").toLatin1());
    }
    qDebug()<<"\r Enabling GPRS";
    gbProcessRunning = true;
    m_nCount = 0;
    sleep(2);
    /* for every second, check whether gprs is enabled or not */
    if(gbEnableMessageBoxGSM)
    {
        m_timerGprsConnect.start(1000);
        m_dialogGprs->exec();
    }
    else
    {
        on_timerClose_timeout();
    }
    m_timerGprsConnect.stop();
    gbProcessRunning = false;
    if (isGprsConnected() )
    {
        qDebug()<<"\r GPRS Enabled Successfully";
        gbGprsConnected = true;
        gLoadIntoSharedGSM(const_strGPRS_CONNECTED);
        if (m_bThreadPause)
        {
            /* write gprs connected status to shared memory for intimate the first application */
            if(gnGPRSModuleType == 2) // telit module mean start the thread
                startThread();
            else
            {
                /* close the port if the port is opened */
                if ( m_serialportSimCom->isOpen() )
                    m_serialportSimCom->close();
            }
        }
        sleep(1);
        return true;
    }
    else
    {
        m_strError = "GPRS Enable Failed";
        qDebug()<<"\r GPRS Enabled Failed";
        system(QString("sh /etc/ppp/peers/ppp-off").toLatin1());
        sleep(1);
        system(QString("killall pppd").toLatin1());
        sleep(1);
        /* close the port if the port is opened */
        if ( m_serialportSimCom->isOpen() )
            m_serialportSimCom->close();
        sleep(1);
        for(int i=1; i<=5 ;i++)
            sendCommand("+++", 200);
        sendCommand("ATH0",500); // Detach GPRS
        sendCommand("AT+CGATT=0",500); // Detach GPRS
        disableGprs();
        return false;
    }
}

bool CGsmModule::disableGprs()
{
    /* diable the gprs connectivity */
    if ( m_bModuleInitiated )
    {
        QString strData;
        if(gbGprsConnected)
        {
            //            qDebug()<<"\r GPRS Disabled";
            gSysCommandtimeout(QString("route del default ppp0"), "",strData);
            //            qDebug()<<"\r GPRS Disabled 1"<<strData;
            strData.clear();
            //            qDebug()<<"\r GPRS Disabled 2";
            if ( gSysCommandtimeout(QString("sh /etc/ppp/peers/ppp-off"), "",strData))
            {
                //                qDebug()<<"\r GPRS Disabled 3";
                strData.clear();
                gLoadIntoSharedGSM(const_strGPRS_DISCONNECTED);
            }
            else
            {
                //                qDebug()<<"\r GPRS Disabled 4";
                gSysCommandtimeout(QString("killall pppd"), "",strData);
                gLoadIntoSharedGSM(const_strGPRS_DISCONNECTED);
                //                initModule();
            }
            gbGprsConnected = false;
        }
        //        qDebug()<<"\r GPRS Disabled 5";
        msleep(300);
        QString strSharedMemory;
        if(m_bThreadPause)
        {
            msleep(200);
            gLoadFromSharedGSM(strSharedMemory);
            if(strSharedMemory.contains(const_strSTARTED) || strSharedMemory.contains(const_strGPRS_CONNECTED) || strSharedMemory.contains(const_strGPRS_DISCONNECTED) || strSharedMemory.contains(const_strGPRS_CONNECTEDCMUX))
            {
                gbGprsConnected = false;
                gLoadIntoSharedGSM(const_strRUNNING);
            }
            startThread();
            int nCount = 0;
            bool bCompleted = false;
            do
            {
                gLoadFromSharedGSM(strSharedMemory);
                msleep(200);
                /* read the data after wait 200 milli seconds to check paused */
                if( strSharedMemory.contains(const_strGPRS_DISCONNECTED) && (!gbGprsConnected))
                {
                    gLoadIntoSharedGSM(const_strCOMPLETED);
                    bCompleted = true;
                    continue;
                }
                nCount ++;
            }
            while ( nCount < 5 && (!bCompleted));
        }
        //        qDebug()<<"\r GPRS Disabled 6";
        //        else
        //        {
        //            if ( m_bThreadPause )
        //            {
        //                msleep(200);
        //                gLoadFromSharedGSM(strSharedMemory);
        //                if(strSharedMemory.contains(const_strSTARTED) || strSharedMemory.contains(const_strGPRS_CONNECTED) || strSharedMemory.contains(const_strGPRS_DISCONNECTED) || strSharedMemory.contains(const_strGPRS_CONNECTEDCMUX))
        //                {
        //                    gbGprsConnected = false;
        //                    gLoadIntoSharedGSM(const_strRUNNING);
        //                }
        //                startThread();
        //            }
        ////            else
        ////            {
        ////                int nCount = 0;
        ////                bool bCompleted = false;
        ////                do
        ////                {
        ////                    gLoadFromSharedGSM(strSharedMemory);
        ////                    qDebug()<<"\r Enter else case in disable GPRS"<<strSharedMemory;
        ////                    msleep(200);
        ////                    /* read the data after wait 200 milli seconds to check paused */
        ////                    if( strSharedMemory.contains(const_strGPRS_DISCONNECTED) && (!gbGprsConnected))
        ////                    {
        ////                        gLoadIntoSharedGSM(const_strCOMPLETED);
        ////                        bCompleted = true;
        ////                        continue;
        ////                    }
        ////                    nCount ++;
        ////                }
        ////                while ( nCount < 5 && (!bCompleted));
        ////            }
        //        }
        return true;
    }
    else
    {
        //        qDebug()<<"\r GPRS Disabled 7";
        return false;
    }
}

bool CGsmModule::testModule()
{
    m_bResponse = false;
    if ( m_bModuleInitiated )
    {
        QString strInfo;
        if(sendCommand(const_strAT_SIGNAL_QUALITY,500))
        {
            if( (m_strNetwork == "") && (m_nTowerLevel > 0))
            {
                m_bOperatorList=true;
                m_bResponse = sendCommand(const_strAT_NT_NAME,500);
            }
            else
            {
                m_strError = "GSM test module failed..";
            }
        }
        else
        {
            m_strError = "GSM test module failed..";
        }

        if(m_bResponse)
        {
            strInfo="\nNetwork       : " + m_strNetwork +
                    "\nIMI Number   : " + m_strIMINo  +
                    "\nTower towerSignal : " + gConvertToString(m_nTowerLevel) +
                    "\nCSQ value    : " + QVariant(m_nCSQValue).toString();
            if ( isGprsConnected() && gbEnableMessageBoxGSM )
            {
                QMessageBox::information(0,"GPRS Module", "GPRS Connected" + strInfo );
            }
            else
            {
                if ( enableGprs() && gbEnableMessageBoxGSM)
                {
                    QMessageBox::information(0,"GPRS Module", "GPRS Connected" + strInfo );
                }
                else if(gbEnableMessageBoxGSM)
                {
                    QMessageBox::information(0,"GPRS Module", "Unable to Connect GPRS" + strInfo );
                }
                disableGprs();
            }
        }
    }
    else if(gbEnableMessageBoxGSM)
    {
        QMessageBox::critical(0,"GPRS Module", m_strError);
    }
    return m_bResponse;
}

bool CGsmModule::gsmNetworkInfo(QString &r_strNetwork, QString &r_strIMINumber, QString &r_strCSQValue, QString &r_strTowerlevel)
{
    qDebug()<<"\r CGSM if inside"<<m_bModuleInitiated;
    m_bResponse = false;
    if ( m_bModuleInitiated ) {
        qDebug()<<"\r CGSM if inside 1"<<m_bModuleInitiated;
        if(sendCommand(const_strAT_SIGNAL_QUALITY,500))
        {
            if( (m_strNetwork == "") && (m_nTowerLevel > 0))
            {
                m_bOperatorList=true;
                m_bResponse = sendCommand(const_strAT_NT_NAME,500);
            }
            else
            {
                m_strError = "Failed while retrieving GSM module info";
            }
        }
        else
        {
            m_strError = "Failed while retrieving GSM module info..";
        }
        //        qDebug()<<"\r CGSM if inside m_bResponse..>>"<<m_bResponse;
        if(m_bResponse)
        {
            r_strNetwork = m_strNetwork;
            r_strIMINumber = m_strIMINo;
            r_strCSQValue = QVariant(m_nCSQValue).toString();
            r_strTowerlevel = gConvertToString(m_nTowerLevel);
        }
    }
    //    qDebug()<<"\r CGSMMODUEL..>>"<<r_strCSQValue;
    return m_bResponse;
}

void CGsmModule::idle()
{
    //    qDebug()<<"\r idle..>>"<<m_bModuleInitiated<<"gprs"<<gbGprsConnected;
    /* pause the thread  & detach from the network */
    if ( m_bModuleInitiated && ( ! gbGprsConnected ) ) {
        //        qDebug()<<"\r idle 1..>>"<<m_bModuleInitiated<<"gprs"<<gbGprsConnected;
        disableGprs();//Testing have implemented
        sendCommand(const_strAT_DETACH_NETWORK,100);
        pauseThread();
    }
    else
    {
        //        disableGprs();//Testing have implemented
        system(QString("killall pppd").toLatin1());
        gLoadIntoSharedGSM(const_strGPRS_DISCONNECTED);
    }
}

void CGsmModule::wakeup()
{
    /* attach with network & start the thread */
    if ( m_bModuleInitiated && ( ! gbGprsConnected ) ) {
        sendCommand(const_strAT_ATTACH_NETWORK,100);

        if ( m_bThreadPause ) {
            startThread();
        }
    }
}

void CGsmModule::startThread()
{
    /* start the thread */
    //    qDebug()<<"\r GPRS PAUSE5"<<isRunning()<<""<<m_bModuleInitiated;
    if ( ( ! isRunning() ) && m_bModuleInitiated )
    {
        m_bThreadRunning = true;
        gbProcessRunning = false;
#ifdef Q_WS_QWS
        start();
#endif
    }
}

void CGsmModule::pauseThread()                                 // thread Pause function
{
    /* pause the thread */
    if ( m_bThreadRunning && isRunning() ) {
        m_bThreadRunning = false;
        m_bThreadPause = true;
        gbProcessRunning = true;
        m_nTowerLevel = -1;
        wait();
    }
}

void CGsmModule::stopThread()
{
    /* stop the thread */
    if ( isRunning() ) {
        m_bThreadRunning = false;
        m_bThreadPause = false;
        wait();
        terminate();
        msleep(50);
    }
}

void CGsmModule::switchDatamode()
{
    bool l_bCommandMode = false;
    sleep(1);
    if(!sendCommand("+++", 1000))
    {
        //            msleep(500);
        //            if(!sendCommand("AT+CSQ", 1000))
        //            {
        //                if(!sendCommand("+++", 500))
        //                {
        ////                msleep(500);
        //                    if(!sendCommand("AT+CSQ", 1000))
        //                    {
        //                        if(!sendCommand("+++", 500))
        //                        {
        //                            l_bCommandMode = false;
        //                            l_iCount++;
        //                        }
        //                        else
        //                        {
        //                            l_bCommandMode = true;
        //                        }
        //                    }
        //                }
        //                else
        //                {
        //                    l_bCommandMode = true;
        //                }
        //            }
        //            l_bCommandMode = true;
    }
    else
    {
        l_bCommandMode = true;
    }

    if(!m_serialportSimCom->isOpen())
    {
        msleep(500);
        m_serialportSimCom->close();
    }
    sendCommand("ATH", 1000);
    sendCommand("AT+CGATT=0", 1000);
}

void CGsmModule::run()
{
    /* thread for get the signal level of the network */
    QString strSharedMemory;
    int nErrorCount = 0;
    while ( m_bThreadRunning )
    {
        /* read the gprs shared memory data */
        gLoadFromSharedGSM(strSharedMemory);
        //        qDebug()<<"\r Enter GSM SHARED"<<strSharedMemory;
        if ( const_strRUNNING == strSharedMemory || const_strGPRS_CONNECTEDCMUX ==strSharedMemory )
        {
            /* get the signal strength if module is registered ,
               otherwise wait for register the module until get the
               current network name */
            if ( m_bModuleInitiated &&  m_nRegStatus == 2 )
            {
                /* get the network name */
                m_bOperatorList=true;
                if ( sendCommand(const_strAT_NT_NAME,500) )
                {
                    //                    qDebug()<<"\r gnGPRS 5..>>";
                    /* module is registered if network name is available */
                    if ( m_strNetwork != "" )
                    {
                        //                        qDebug()<<"\r gnGPRS 6..>>";
                        /*To store sim module parameters, once if the home network selected in roaming mode */
                        sendCommand(const_strAT_STORE_PARAMETERS,500);
                        m_nRegStatus = 1;
                        emit modReady();
                    }
                }
                /* try after 4 seconds to get the network name */
                if ( m_bThreadRunning )
                {
                    sleep(4);
                }
            }
            else
            {
                //                qDebug()<<"\r gnGPRS 7..>>";
                /* request the signal strenght command to module */
                if(!(gbGprsAlwaysOn = ghhc80xxServerObj->getgprsAlwaysON_OFF() ))
                {
                    if(isGprsConnected() && gnGPRSModuleType == 1) //Simcom
                    {
                        gbEnableMessageBoxGSM = true;
                        disableGprs();
                        msleep(200);
                    }
                    if(!sendCommand(const_strAT_SIGNAL_QUALITY,500))
                    {
                        if(nErrorCount == 5)
                        {
                            if ( m_serialportSimCom->isOpen() )
                            {
                                /* close the port if the port is opened */
                                m_serialportSimCom->flush();
                                m_serialportSimCom->close();
                            }
                            m_strError = " Gsm module commuication Failed!";
                        }
                        else
                        {
                            nErrorCount++;
                        }
                    }
                }
                else if(gbGprsConnected && gnGPRSModuleType== 2) //telit tower update
                {
                    if(!sendCommand(const_strAT_SIGNAL_QUALITY,500))
                    {
                        if(nErrorCount == 5)
                        {
                            if ( m_serialportSimCom->isOpen() )
                            {
                                /* close the port if the port is opened */
                                m_serialportSimCom->flush();
                                m_serialportSimCom->close();
                            }
                            m_strError = " Gsm module commuication Failed!";
                        }
                        else
                        {
                            nErrorCount++;
                        }
                    }
                }
                else
                {
                    //                    qDebug()<<"\r Enter ALWAYS ON";
                    gbEnableMessageBoxGSM = false;
                    sleep(2);
                    if(!isGprsConnected())
                        enableGprs();
                    nErrorCount = 0;
                }
                /* wait 500 milli seconds */
                if ( m_bThreadRunning )
                {
                    sleep(1);
                }
            }
            //            qDebug()<<"\r run ppp ip";
            sendCommand(const_strPPPIPADDRESS,200);
        }
        else if (const_strSTARTED == strSharedMemory )
        {
            /* change Paused in shared memory and close the port when receive Started */
            if ( m_serialportSimCom->isOpen() )
            {
                /* close the port if the port is opened */
                //                m_serialportSimCom->flush();
                m_serialportSimCom->close();
            }
            gLoadIntoSharedGSM(const_strPAUSED);
            gbProcessRunning = true;
        }
        else if (const_strCOMPLETED == strSharedMemory )
        {
            /* change Running in shared memory and open the port when receive Completed */
            if(!m_serialportSimCom->isOpen())
            {
                msleep(200);
                m_serialportSimCom->open();
            }
            gLoadIntoSharedGSM(const_strRUNNING);
            gbProcessRunning = false;
        }
        else if((const_strGPRS_CONNECTED == strSharedMemory || const_strGPRS_CONNECTEDCMUX== strSharedMemory ))
        {
            /* if Gprs is enabled in second application used to intimate the first application call */
            gbGprsConnected = true;
            if(gnGPRSModuleType == 2) //telit
            {
                gLoadIntoSharedGSM(const_strGPRS_CONNECTEDCMUX);
            }
            if(gbGprsAlwaysOn = ghhc80xxServerObj->getgprsAlwaysON_OFF() )
            {
                if(!isGprsConnected())
                    enableGprs();
            }
            else
            {
                //                if(isGprsConnected() && gnGPRSModuleType == 1) //simcom
                //                {
                //                    disableGprs();
                //                }
                //                else
                //                {
                //                }
            }
            msleep(300);
        }
        else if (const_strGPRS_DISCONNECTED == strSharedMemory )
        {
            /* if Gprs is disabled in second application used to intimate the first application call */
            gbGprsConnected = false;
            if(isGprsConnected())
            {
                disableGprs();
            }
            msleep(500);
            gLoadIntoSharedGSM(const_strRUNNING);
        }
        else if ("RESET" == strSharedMemory )
        {
            if ( m_serialportSimCom->isOpen() )
            {
                /* close the port if the port is opened */
                m_serialportSimCom->flush();
                m_serialportSimCom->close();
            }
            msleep(500);
            if(!m_serialportSimCom->open())
            {
                qDebug()<<"\rError while opening port"<<m_serialportSimCom->lastError();
            }
            sendCommand(const_strAT_DETACH_NETWORK,1000);
            sleep(2);
            sendCommand(const_strAT_ATTACH_NETWORK,1000);
        }
        else
        {
            /* wait 200 millsecond to check the data in shared memory */
            msleep(500);
        }
        //        qDebug()<<"\r Get GPS position";
        //        sendCommand(const_strPPPIPADDRESS,200);
        //        getGPSPosition();
    }
}

bool CGsmModule::getGPSPosition(QString &r_strLatitude, QString &r_strLongitude)
{
    qDebug()<<"\r GPS position entered";
    pauseThread();
//    testGPS();
     sendCommand(const_strSOCKETAVAILABLE,1000);
    sleep(2);
    if(m_str2SocketIP.contains("#SGACT: 2,1"))
    {
          qDebug()<<"\r 2,1..>>";
         sendCommand(const_strPPPIPADDRESSSECONDSOCKET,1000);
         sleep(2);
    }
    else if((m_str2SocketIP.contains("#SGACT: 2,0"))||(m_str2SocketIP.contains("#SGACT: 1")))
    {
        qDebug()<<"\r 2,0 or 1..>>";
        sendCommand(const_strSOCKET2IPGET,1000);
        sleep(2);
        if(m_str2SocketIP.contains("#SGACT: 2,1"))
        {
            qDebug()<<"\r 2,0 or 1  cme..>>";
             sendCommand(const_strPPPIPADDRESSSECONDSOCKET,1000);
             sleep(2);
        }
        else
        {
            qDebug()<<"\r 2,0 or 1  cme..>>"<<m_str2SocketIP;
            sendCommand(const_strSOCKET2APNSET,1000);
            sleep(2);
            sendCommand(const_strSOCKET2IPGET,1000);
            sleep(2);
            sendCommand(const_strPPPIPADDRESSSECONDSOCKET,1000);
            sleep(2);
        }
    }


    if(m_str2SocketIP!="")
    {
        qDebug()<<"\r 2,0 or 1  !=..>>";
        sendCommand(const_strCACHEDNS,1000);
        sleep(2);
        qDebug()<<"\r 2,0 or 1  !=  vdsfs..>>";
        sendCommand(const_strGPSPOSITION,1000);
        sleep(5);

    }
////    sendCommand(const_strM2MLOCATE,1000);
//    sendCommand(const_strSOCKET2APNSET,1000);
//    sleep(2);
//    sendCommand(const_strSOCKET2IPGET,1000);
//    sleep(2);
////    sendCommand(const_strCACHEDNS,1000);
////    sleep(2);
//    sendCommand(const_strGPSPOSITION,1000);
//    sleep(5);

    r_strLatitude=gm_strGPRSGPSLatitude;
    r_strLongitude=gm_strGPRSGPSLongitude;

    if(r_strLatitude=="")
    {
        int nAGPScount=0;
        for(;nAGPScount <= 2; nAGPScount++)
        {
            sendCommand(const_strGPSPOSITION,1000);
            sleep(5);

            r_strLatitude=gm_strGPRSGPSLatitude;
            r_strLongitude=gm_strGPRSGPSLongitude;
            if(r_strLatitude!="")
            {
                nAGPScount=3;
            }
            else
            {
                qDebug()<<"\r nAGPScount if count..>>"<<nAGPScount;
            }
        }
    }

//    r_strLatitude=m_strGPRSGPSLatitude;
//    r_strLongitude=m_strGPRSGPSLongitude;

    //    disableGprs();
//    qDebug()<<"\r vfgxvcg"<<r_strLatitude<<"\n dskfskdf"<<r_strLongitude;
//    sleep(10);
    qDebug()<<"\r gm_strGPRSGPSLatitude"<<gm_strGPRSGPSLatitude<<"\n gm_strGPRSGPSLongitude"<<gm_strGPRSGPSLongitude;
//    disableGprs();
    sleep(2);
    startThread();
    return true;
}

bool CGsmModule::portInitialize(const QString &r_const_strPORTNAME)
{
    //    qDebug()<<"\r gnGPRS 3..>>";
    /* initialize the port for sending and receiving data */
    m_serialportSimCom = new QextSerialPort();
    DEBUGMESSAGE("Gsm module port name : " + r_const_strPORTNAME);
    m_serialportSimCom->setPortName(r_const_strPORTNAME);
    m_serialportSimCom->setDataBits(DATA_8);
    m_serialportSimCom->setParity(PAR_NONE);
    m_serialportSimCom->setFlowControl(FLOW_OFF);
    m_serialportSimCom->setStopBits(STOP_1);
    m_serialportSimCom->setBaudRate(BAUD115200);
    if(!m_serialportSimCom->isOpen())
    {
        if ( !m_serialportSimCom->open() ) {
            qDebug()<<"Failed to open Gsm port..!";
            return false;
        }
    }
    //    qDebug()<<"\r gnGPRS 4..>>";
    return true;
}

int CGsmModule::readSerialData(QString &r_const_strReadBuffer)
{
    /* read the data from the buffer */
    char arr_cReadBuffer[1024] ;
    r_const_strReadBuffer.clear();
    int nBytesReceived=0, nBytesAvailable;
    nBytesAvailable = m_serialportSimCom->bytesAvailable();
    if ( nBytesAvailable > 0 )
    {
        /* read the available bytes */
        nBytesReceived = m_serialportSimCom->readData(arr_cReadBuffer, nBytesAvailable);
        if ( nBytesReceived > 0 )
        {
            /* received buffer data */
            arr_cReadBuffer[nBytesReceived] = '\0';
            r_const_strReadBuffer.append(arr_cReadBuffer);
        }
    }
    return nBytesReceived;
}

int CGsmModule::writeSerialData(const QString &r_const_strDataToWrite)
{
    int nBytesWritten = m_serialportSimCom->writeData(r_const_strDataToWrite.toAscii(), r_const_strDataToWrite.length());
    return nBytesWritten;
}

bool CGsmModule::sendCommand(const QString &r_const_strCOMMAND, long nWait)
{
    /* QMutex lock is to protect the section of code so that only one thread
       can access it at a time. successor call will wait until m_Mutex unlocked. */
    m_Mutex.lock();
    QString strData;

    /* check the port is not open wait 1 second, then open the port */
    if ( ! m_serialportSimCom->isOpen() )
    {
        msleep(500);
        m_serialportSimCom->open();
    }
    /* read the data if already exist, it might be the network information or SMS Delivery status*/
    arrivedData();
    /* process the received data, it might be the network information or SMS Delivery status*/
    processPrevData();

    m_bCMEError = false;
    m_bResponse = false;
    strData = r_const_strCOMMAND + const_strENTER;
    /* write the command to module if port is opened */
    if ( m_serialportSimCom->isOpen() )
    {
        int nBytesWritten = writeSerialData(strData);
        qDebug()<<"\r CGSM transmit Data"<<strData;
        if(nBytesWritten == strData.length())
        {
            int nMaxCount = nWait / const_nWAIT_FOR_RESPONSE;
            /* wait n milli seconds for an acknowlegment after sending the data. */
            for ( int nCount = 1; nCount <= nMaxCount; nCount ++ )
            {
                if ( m_bResponse || m_bCMEError )
                {
                    /* break the loop if succesfull response or error */
                    break;
                }
                else
                {
                    /* read the data after waiting for 100 milli seconds for response from co-processor */
                    msleep(const_nWAIT_FOR_RESPONSE);
                    arrivedData();
                }
            }
        }
        else
        {
            m_strError = "Error while sending command..!";
        }
    }
    else
    {
        m_strError = "Gsm port not opened!";
    }
    //    if(!m_bResponse)
    //    {
    //        if ( m_serialportSimCom->isOpen() )
    //        {
    //            m_serialportSimCom->close();
    //            sleep(1);
    //            m_serialportSimCom->open();
    //        }
    //    }
    m_Mutex.unlock();
    return m_bResponse;
}

bool CGsmModule::gsmATCommand(const QString const_strCOMMAND, QString &r_const_strRESPONSE, long nTimeout_mSec)
{
    m_Mutex.lock();
    QString strData;

    /* check the port is not open wait 1 second, then open the port */
    if ( ! m_serialportSimCom->isOpen() )
    {
        sleep(1);
        m_serialportSimCom->open();
    }

    /* read the data if already exist, it might be the network information or SMS Delivery status*/
    //    arrivedData();
    /* process the received data, it might be the network information or SMS Delivery status*/
    //    processPrevData();

    m_bCMEError = false;
    m_bResponse = false;
    strData = const_strCOMMAND + const_strENTER;
    /* write the command to module if port is opened */
    QString strReadData;
    if ( m_serialportSimCom->isOpen() )
    {
        int nBytesWritten = writeSerialData(strData);
        if(nBytesWritten == strData.length())
        {
            int nMaxCount = nTimeout_mSec / const_nWAIT_FOR_RESPONSE;
            /* wait 'n' milli seconds for an acknowlegment after sending the data. */
            for ( int nCount = 1; nCount <= nMaxCount; nCount ++ )
            {
                /* read the data after waiting for 100 milli seconds for response from co-processor */
                msleep(const_nWAIT_FOR_RESPONSE);
                int nBytesReceived = readSerialData(strReadData);
                if ( nBytesReceived > 0 )
                {
                    /* received buffer data */
                    QString strReceivedBuffer;
                    strReceivedBuffer = strReadData.left(nBytesReceived);
                    strReceivedBuffer = m_strPreviousData.append(strReceivedBuffer);
                    if ( strReceivedBuffer.contains(const_strRESPONSE_OK) || strReceivedBuffer.contains(const_strRESPOSNE_CME_ERROR) )
                    {
                        /* break the loop if succesfull response or error */
                        r_const_strRESPONSE = strReceivedBuffer;
                        m_bResponse = true;
                        break;
                    }
                    strReceivedBuffer.clear();
                }
                strReadData.clear();
            }
        }
        else
        {
            m_strError = "Failed while sending command..!";
        }
    }
    else
    {
        m_strError = "Gsm port not opened!";
        //        qDebug()<<"\r m_serialportSimCom"<<m_strError;
    }
    //    if(!m_bResponse)
    //    {
    //        sendCommand(QString("") + QChar(const_nCTRL_PLUS_Z), 500);
    //        sendCommand("+++", 200);
    //        if ( m_serialportSimCom->isOpen() ) {
    //            m_serialportSimCom->close();
    //        }
    //    }
    m_Mutex.unlock();
    return m_bResponse;
}

void CGsmModule::arrivedData()
{
    QString strData;
    int nBytesReceived = readSerialData(strData);
    if ( nBytesReceived > 0 )
    {
        /* received buffer data */
        QString strReceivedBuffer;
        strReceivedBuffer = strData.left(nBytesReceived);
        strReceivedBuffer = m_strPreviousData.append(strReceivedBuffer);
        //        qDebug()<<"\r CGSM  Received..>>"<<strReceivedBuffer;
        if ( strReceivedBuffer.contains(const_strRESPONSE_OK) || strReceivedBuffer.contains(const_strRESPOSNE_CME_ERROR) )
        {
            /* handle message if success or error */
            handleMessage(strReceivedBuffer);

            /* data is not fully arrived, so keep it in previous data */
            m_strPreviousData = strReceivedBuffer;
        }
        strReceivedBuffer.clear();
    }
}

void CGsmModule::handleMessage(const QString &r_const_strDATA)
{
    /* handle the received data from module */
    DEBUGMESSAGE("Received:"<<r_const_strDATA);
    qDebug()<<"\r CGSM handle msg ..>>>"<<r_const_strDATA;
    //Testing below
    if (r_const_strDATA.contains(const_strGPSPOSITIONRESPONSE))
    {
        pauseThread();
        qDebug()<<"\r 1st if 1234567.>>"<<r_const_strDATA<<"\r Length..>>"<<r_const_strDATA.length();

        QString strGetGPS;
        strGetGPS=r_const_strDATA.mid(r_const_strDATA.indexOf("#AGPSRING:"),r_const_strDATA.length());
        //        m_strlistGPS=r_const_strDATA.split(",");//OLD done on Nov 9 2013
        m_strlistGPS=strGetGPS.split(",");//New done on Nov 11 2013
        m_strGPRSGPSLatitude=m_strlistGPS.at(1);
        m_strGPRSGPSLongitude=m_strlistGPS.at(2);

        gm_strGPRSGPSLatitude=m_strlistGPS.at(1);
        gm_strGPRSGPSLongitude=m_strlistGPS.at(2);


        qDebug()<<"\r GPS GPRS POSITION. 1234.>>"<<gm_strGPRSGPSLatitude<<gm_strGPRSGPSLongitude;
        startThread();
//        sleep(10);
    }
    //Testing above

   else if ( r_const_strDATA.contains(const_strRESPONSE_OK) )
    {
//        qDebug()<<"\r CGSM handle msg 1 ..>>>"<<r_const_strDATA;
        /* successful response for the last requested command */
        m_bResponse = true;
        if ( r_const_strDATA.contains(const_strRESPONSE_SIGNAL_QUALITY) )
        {
            /* read the CSQ value and Ber for calculate the tower level */
            int nCurrentTower;
            int nBer;
            QString strData = r_const_strDATA.mid(r_const_strDATA.indexOf(const_strRESPONSE_SIGNAL_QUALITY)+6);
            QStringList listData = strData.split(",");
            m_nCSQValue = QVariant(listData.at(0)).toInt();
            //            qDebug()<<"\r CGSM if inside m_nCSQValue..>>"<<m_nCSQValue;
            nBer = QVariant(listData.at(1)).toInt();
            listData.clear();
            nCurrentTower = towerLevel(m_nCSQValue,nBer);
            //            qDebug()<<"\r m_nTowerLevel..>>"<<m_nTowerLevel<<" "<<nCurrentTower;
            if ( m_nTowerLevel != nCurrentTower )
            {
                /* emit the network tower level if changed with previous level */
                m_nTowerLevel = nCurrentTower;
                //                qDebug()<<"\r m_nTowerLevel 1..>>"<<m_nTowerLevel;
                usleep(100);
                emit gsmNetworkSignal(m_nTowerLevel);
                gUpdateScreen(200);
            }
        }
        else if(r_const_strDATA.contains(const_strRESPONSEPPPIPADDRESS))
        {
//            qDebug()<<"\r 1st if 2.>>";
            QString strPPPip,strPPPipget;
            strPPPip = r_const_strDATA;
            strPPPipget=strPPPip.mid(strPPPip.indexOf(",")+2,16);
            if(strPPPipget!="")
            {
                //                qDebug()<<"\r PPP ip is exits";
            }
            else
            {
                disableGprs();
            }
        }
        else if(r_const_strDATA.contains(const_strSOCKET2IPRESPONSE))
        {
            qDebug()<<"\r 1st if 2.>>"<<r_const_strDATA;
            QString strPPPip;
            strPPPip = r_const_strDATA;
            m_str2SocketIP=strPPPip.mid(strPPPip.indexOf(",")+2,16);
            qDebug()<<"\r 1st if 2 weeee.>>"<<m_str2SocketIP;
            if(m_str2SocketIP!="")
            {
                qDebug()<<"\r PPP ip is exits 2 nd";
            }
            else
            {
                disableGprs();
            }
        }
        else if(r_const_strDATA.contains("#SGACT"))
        {
            m_str2SocketIP=r_const_strDATA;
            qDebug()<<"\r 2 Socketip"<<m_str2SocketIP;
//            if(m_str2SocketIP.contains("#SGACT: 2,0"))
//            {
//                m_str2SocketIP="";
//    //            qDebug()<<"\r 2 Socketip if condition"<<m_str2SocketIP;
//            }
//            else
//            {
//                QString strPPPip;
//                strPPPip = r_const_strDATA;
//                m_str2SocketIP =strPPPip.mid(strPPPip.indexOf(",")+2,16);
//    //            qDebug()<<"\r 2 Socketip 121212"<<m_str2SocketIP;
//            }
        }
        else if ( r_const_strDATA.contains(const_strRESPOSNE_NT_NAME) )
        {
//            qDebug()<<"\r 1st if 3.>>";
            /* process for receive the network name */
            int spos=0;
            if(!m_bOperatorList)
            {
                spos = r_const_strDATA.indexOf(": (");
                QString strNetwork=r_const_strDATA.mid(spos+2,r_const_strDATA.length()-spos-9).toUpper();
                /* process for search list of operators */
                QList<QString> listOperatorData;
                listOperatorData = strNetwork.split("\")");
                handleOperators(listOperatorData);
                listOperatorData.clear();
            }
            else
            {
//                qDebug()<<"\r 1st if 4.>>";
                if(r_const_strDATA.mid(9,1).toInt()==1)
                    m_bNetworkMode=true;
                else
                    m_bNetworkMode=false;
                if ( r_const_strDATA.contains(",\"") )
                {
                    int spos = r_const_strDATA.indexOf(const_strRESPOSNE_NT_NAME)+12;
                    m_strNetwork=r_const_strDATA.mid(spos,r_const_strDATA.length()-spos-9).toUpper();
                    m_strNetwork.simplified();
                    m_strNetwork.trimmed();
                    /* add "IND" before operator name if first digit is numeric */
                    if ( m_strNetwork.length() > 0 )
                        if ( m_strNetwork.at(0).isNumber() )
                            m_strNetwork = "IND" + m_strNetwork;
                }
                else
                {
                    /* network name is emty */
                    m_strNetwork = "";
                }
            }
        }
        else if ( r_const_strDATA.contains(const_strRESPOSNE_SIM_PIN) && !r_const_strDATA.contains("READY") )
        {
//            qDebug()<<"\r 1st if 5.>>";
            /* process for receive the SIM Pin State */
            m_strError=r_const_strDATA.right(r_const_strDATA.indexOf(":",1));
        }
        else if ( r_const_strDATA.contains(const_strRESPOSNE_SMS_SENT_INDEX) )
        {
//            qDebug()<<"\r 1st if 6.>>";
            QString stringSMSIndexTemp = r_const_strDATA.simplified().section(" ",1,1).simplified();
            m_nSMSSentIndex = QVariant(stringSMSIndexTemp.simplified()).toInt();
        }
        else if ( r_const_strDATA.contains(const_strAT_LIST_SMS) )
        {
//            qDebug()<<"\r 1st if 7.>>";
            /* process the listed sms details */
            QList<QString> listSmsData;
            listSmsData = r_const_strDATA.mid(0,r_const_strDATA.length() - 4).split(const_strAT_LIST_SMS);
            handleSmsDetails(listSmsData);
            listSmsData.clear();
        }
//        else if (r_const_strDATA.contains(const_strGPSPOSITIONRESPONSE))
//        {
//            pauseThread();
//            qDebug()<<"\r 1st if 12.>>"<<r_const_strDATA<<"\r Length..>>"<<r_const_strDATA.length();
////            QString str;
////            str = r_const_strDATA.mid(23,20);
////            QStringList strlst;
////            QString str1,str2,str3;
////            strlst=str.split(",");
////            str2= strlst.at(0);
////            str3= strlst.at(1);

//            m_strlistGPS=r_const_strDATA.split(",");
//            m_strGPRSGPSLatitude=m_strlistGPS.at(1);
//            m_strGPRSGPSLongitude=m_strlistGPS.at(2);


////            m_strGPRSGPSPosition =r_const_strDATA.mid(23,20);
////            m_strlistGPS=m_strGPRSGPSPosition.split(",");
////            m_strGPRSGPSLatitude=m_strlistGPS.at(0);
////            m_strGPRSGPSLongitude=m_strlistGPS.at(1);



////            gm_strGPRSGPSLatitude=m_strlistGPS.at(0);
////            gm_strGPRSGPSLongitude=m_strlistGPS.at(1);


//            gm_strGPRSGPSLatitude=m_strlistGPS.at(1);
//            gm_strGPRSGPSLongitude=m_strlistGPS.at(2);


//            qDebug()<<"\r GPS GPRS POSITION. 123.>>"<<gm_strGPRSGPSLatitude<<gm_strGPRSGPSLongitude;
////            qDebug()<<"\r GPS GPRS POSITION..>>"<<str<<"\n str1"<<strlst<<"\nstr2"<<str2<<"\rstr3"<<str3;
////            startThread();
//            sleep(10);
//        }
        else if ( r_const_strDATA.contains(const_strRESPOSNE_NETWORK_REG) )
        {
//            qDebug()<<"\r 1st if 8.>>";
            /* get the sim registration status */
            QString strRegResponse = r_const_strDATA.section(",", 1, 1).simplified().section(" ",0,0).simplified();
            switch ( strRegResponse.toInt() ) {
            case 0:
                //Not Registered
                m_strError = "Network Registration Failed-E00";
                m_nRegStatus = 0;
                emit gsmNetworkSignal(0);
                break;
            case 1:
                //Registered Home Network
                m_strError = "Network Registered, home network";
                m_nRegStatus = 1;
                break;
            case 2:
                //Not registered, but MT is currently searching a new operator to register to
                //m_strError = "sim not registered, but module is currently searching a new operator to register to";
                m_strError = "Network Registration Failed-E02";
                m_nRegStatus = 2;
                emit gsmNetworkSignal(0);
                break;
            case 3:
                //Registration denied
                m_strError = "Network Registration Failed-E03";
                m_nRegStatus = 0;
                emit gsmNetworkSignal(0);
                break;
            case 4:
                //unkonwn
                /* Some times sim module goes to this state in few machine while wakeup from idle/standby mode,
                So Changed logic to get reg status until it registered with network like case 2 -- By askar on 13/06/2012*/
                m_strError = "Network Registration Failed-E04";
                m_nRegStatus = 2;
                emit gsmNetworkSignal(0);
                break;
            case 5:
                //Registered Roming
                m_strError = "Network Registered, roaming";
                m_nRegStatus = 1;
                break;
            }
        }
        else if(!m_bOperatorList && (r_const_strDATA.contains("SIMCOM_Ltd")||r_const_strDATA.contains("Telit")))
        {
//            qDebug()<<"\r 1st if 9.>>";
            m_strManufacturer_Name=r_const_strDATA.mid(0,r_const_strDATA.length()-2);
            m_strManufacturer_Name=m_strManufacturer_Name.simplified();
        }
        else if ( ( ! r_const_strDATA.contains("+") )  && ( r_const_strDATA.length() > 15 ) )
        {
//            qDebug()<<"\r 1st if 10.>>";
            /* receive the IMI Number */
            m_strIMINo = r_const_strDATA.mid(2, r_const_strDATA.indexOf("\n",5)-2);
            DEBUGMESSAGE("IMI Number:" + m_strIMINo );
        }
        else if ( r_const_strDATA.contains(const_strRESPOSNE_SMS_MODE) )
        {
//            qDebug()<<"\r 1st if 11.>>";
            /* receive the current sms mode */
            m_nCurrentSmsMode = gConvertToInt(r_const_strDATA.mid(r_const_strDATA.indexOf(const_strRESPOSNE_SMS_MODE) + 7, 1));
        }
//        else if (r_const_strDATA.contains(const_strGPSPOSITIONRESPONSE))
//        {
//            qDebug()<<"\r 1st if 12.>>";
//            QString str;
//            str = r_const_strDATA.indexOf("#AGPSRING:");
//            qDebug()<<"\r GPS GPRS POSITION..>>"<<str;
//        }
//        qDebug()<<"\r 1st if.>>";
    }
    else if ( r_const_strDATA.contains(const_strRESPOSNE_SMS_DELIVERY_STATUS) )
    {
//        qDebug()<<"\r 3st if.>>";
        /* Process the SMS Delivery status given by module */

        int nCDSCount = 0, nLoopCount = 0;
        nCDSCount = r_const_strDATA.count(const_strRESPOSNE_SMS_DELIVERY_STATUS);
        QByteArray bytearrayTemp;
        bytearrayTemp.append(r_const_strDATA);
        QBuffer bufferTemp(&bytearrayTemp);
        bufferTemp.open(QIODevice::ReadOnly);

        while(nCDSCount > nLoopCount)
        {
            QStringList stringlistDeliveryStatus = QString(bytearrayTemp.mid(bytearrayTemp.indexOf(const_strRESPOSNE_SMS_DELIVERY_STATUS) + 6)).split(",");
            bufferTemp.seek(bytearrayTemp.indexOf(const_strRESPOSNE_SMS_DELIVERY_STATUS) + 6);
            bytearrayTemp = bufferTemp.readAll();
            m_nSMSDeliveredIndex = QVariant(stringlistDeliveryStatus.at(1)).toInt();
            stringlistDeliveryStatus.clear();
            handleSmsDeliveryStatus(m_nSMSDeliveredIndex);
            DEBUGMESSAGE("Delivered SMS Index:" + m_nSMSDeliveredIndex );
            nLoopCount++;
        }
        bufferTemp.close();
    }
    else if ( r_const_strDATA.contains(const_strRESPOSNE_CME_ERROR) )
    {
//        qDebug()<<"\r 4st if.>>";
        /* receive the error given by module */
        m_bCMEError = true;
        m_strError = r_const_strDATA.mid(r_const_strDATA.indexOf(const_strRESPOSNE_CME_ERROR)+11,r_const_strDATA.length()-14);
        DEBUGMESSAGE(" GPRS Error: " + m_strError );
    }

    else
    {
//        qDebug()<<"\r 5st if.>>";
        if(gLoadIntoSharedGSM("RESET"))
        {
            qDebug()<<"Failed while load reset command in shared mem";
        }
    }
}

void CGsmModule::handleOperators(const QList<QString> &r_const_listOperators)
{
    /* it handle the list of operators */
    QString strNetworkName;
    foreach ( strNetworkName, r_const_listOperators )
    {
        /* read the operator details one by one */
        QList<QString> listRecord;
        listRecord = strNetworkName.split(const_strDOUBLE_QUOTE);
        if(gnGPRSModuleType== 1) //simcom
        {
            if ( (listRecord.count() > 3 ) )
            {
                /* add "IND" before operator name if first digit is numeric */
                if ( listRecord.at(1).length() > 0 )
                {
                    if ( listRecord.at(1).at(0).isNumber() )
                    {
                        m_listOperators.append("IND"+listRecord.at(1)+","+listRecord.at(3));
                    }
                    else
                    {
                        if(listRecord.at(1)!="")
                            m_listOperators.append(listRecord.at(1)+","+listRecord.at(5));
                    }
                }
            }
        }
        else if(gnGPRSModuleType== 2) //telit
        {
            if ( (listRecord.count() > 3 ) )
            {
                /* add "IND" before operator name if first digit is numeric */
                if ( listRecord.at(1).length() > 0 )
                {
                    if ( listRecord.at(1).at(0).isNumber() )
                    {
                        m_listOperators.append("IND"+listRecord.at(1)+","+listRecord.at(3));
                    }
                    else
                    {
                        if(listRecord.at(1)!="")
                            m_listOperators.append(listRecord.at(1)+","+listRecord.at(3));
                    }
                }
            }
        }
        listRecord.clear();
        strNetworkName.clear();
    }
}


void CGsmModule::processPrevData()
{
    if ( m_strPreviousData.contains("+CBM:") )
    {
        int nStart = m_strPreviousData.indexOf("\n");
        int nEnd;
        if ( nStart > 0 ) {
            nEnd = m_strPreviousData.indexOf("\n", nStart + 1);
            if ( nEnd < 0 ) {
                nEnd = m_strPreviousData.length();
            }
            else {
                nEnd --;
            }
            m_strPreviousData = m_strPreviousData.mid(nStart + 1, nEnd - nStart - 3);
            m_strNetworkInfo = m_strCellinfo + m_strPreviousData;
            m_strCellinfo = m_strPreviousData + " || ";
            DEBUGMESSAGE("cellinfo: " + m_strNetworkInfo) ;
        }
    }
    else if ( m_strPreviousData.contains(const_strRESPOSNE_SMS_DELIVERY_STATUS) )
    {
        /* Process the SMS Delivery status given by module */
        int nCDSCount = 0, nLoopCount = 0;
        nCDSCount = m_strPreviousData.count(const_strRESPOSNE_SMS_DELIVERY_STATUS);
        QByteArray bytearrayTemp;
        bytearrayTemp.append(m_strPreviousData);
        QBuffer bufferTemp(&bytearrayTemp);
        bufferTemp.open(QIODevice::ReadOnly);

        while(nCDSCount > nLoopCount)
        {
            QStringList stringlistDeliveryStatus = QString(bytearrayTemp.mid(bytearrayTemp.indexOf(const_strRESPOSNE_SMS_DELIVERY_STATUS) + 6)).split(",");
            bufferTemp.seek(bytearrayTemp.indexOf(const_strRESPOSNE_SMS_DELIVERY_STATUS) + 6);
            bytearrayTemp = bufferTemp.readAll();
            QString stringSMSIndexTemp = stringlistDeliveryStatus.at(1);
            stringlistDeliveryStatus.clear();
            m_nSMSDeliveredIndex = QVariant(stringSMSIndexTemp.simplified()).toInt();
            handleSmsDeliveryStatus(m_nSMSDeliveredIndex);
            DEBUGMESSAGE("Delivered SMS Index:" + m_nSMSDeliveredIndex );
            nLoopCount++;
        }
        bufferTemp.close();
    }
    m_strPreviousData.clear();
}

int CGsmModule::towerLevel(int nCsqValue,int nBer)
{
    /* calculate the tower level using CSQ value and ber */
    int nTowerLevel = 0;
    if ( nCsqValue > 31 || nBer == 99|| nCsqValue ==0 ) {
        m_strNetworkInfo = "";
        m_strCellinfo = "";
        nTowerLevel = 0;
    }
    else if ( nCsqValue >= 1 && nCsqValue <= 6 ) {
        nTowerLevel = 1;
    }
    else if ( nCsqValue >= 7 && nCsqValue <= 12 ) {
        nTowerLevel = 2;
    }
    else if ( nCsqValue >= 13 && nCsqValue <= 18) {
        nTowerLevel = 3;
    }
    else if ( nCsqValue >= 19 && nCsqValue <= 24 ) {
        nTowerLevel = 4;
    }
    else if ( nCsqValue >= 24 && nCsqValue <= 31) {
        nTowerLevel = 5;
    }
    return nTowerLevel;
}

void CGsmModule::handleSmsDetails(const QList<QString> &r_const_listSMSDATA)
{
    /* handle the sms details and conver the data into sms structured list */
    QString strData;
    foreach ( strData, r_const_listSMSDATA ) {
        /* read the sms one by one */
        if ( strData.trimmed() != "" ) {
            /* read the sms header info & message,
            first line is the header info and remaning lines are message data */
            QList<QString> listRecord;
            QList<QString> listHeaderInfo;
            QString strMessage = "";
            CHHC80xx::SSmsDetail smsDetailMessage;
            listRecord = strData.split("\n");
            listHeaderInfo = listRecord.at(0).split(",");
            for ( int nIndex = 1; nIndex < listRecord.count(); nIndex ++ ) {
                /* concatenate the message data */
                strMessage += listRecord.at(nIndex) +"\n";
            }
            strMessage = strMessage.left(strMessage.length() - 2);
            if ( listHeaderInfo.count() > 3 ) {
                /* read the sms state & convert into messagestate enum */
                CHHC80xx::E_MessageState eState;
                QString strStatus = listHeaderInfo.at(1);
                strStatus = strStatus.mid(1, strStatus.length()-2);
                if ( const_strREC_UNREAD ==  strStatus ) {
                    eState = CHHC80xx::eMessageState_UNREAD;
                }
                else if ( const_strREC_READ ==  strStatus ) {
                    eState = CHHC80xx::eMessageState_READ;
                }
                else if ( const_strSTO_UNSENT ==  strStatus ) {
                    eState = CHHC80xx::eMessageState_STORED_UNSENT;
                }
                else if ( const_strSTO_SENT ==  strStatus ) {
                    eState = CHHC80xx::eMessageState_STORED_SENT;
                }
                else {
                    eState = CHHC80xx::eMessageState_ALL;
                }

                /* read the from address of the message */
                QString strFrom = listHeaderInfo.at(2);
                strFrom = strFrom.mid(1,strFrom.length()-2);

                /* read the date & time of the message */
                int nYear, nMonth, nDay, nHour, nMinutes, nSeconds;
                nYear = gConvertToInt(listHeaderInfo.at(4).mid(1,2));
                nMonth = gConvertToInt(listHeaderInfo.at(4).mid(4,2));
                nDay = gConvertToInt(listHeaderInfo.at(4).mid(7,2));
                nHour = gConvertToInt(listHeaderInfo.at(5).mid(0,2));
                nMinutes = gConvertToInt(listHeaderInfo.at(5).mid(3,2));
                nSeconds = gConvertToInt(listHeaderInfo.at(5).mid(6,2));

                /* load the message details into sms structure */
                smsDetailMessage.m_strMessage   = strMessage;
                smsDetailMessage.m_MessageIndex = gConvertToInt(listHeaderInfo.at(0));
                smsDetailMessage.m_eState       = eState;
                smsDetailMessage.m_strFrom      = strFrom;
                smsDetailMessage.m_dateTime = QDateTime(QDate(nYear,nMonth,nDay),
                                                        QTime(nHour,nMinutes,nSeconds));
                /* load the sms structure into list */
                m_listSmsDetails.append(smsDetailMessage);
            }
            listRecord.clear();
            listHeaderInfo.clear();
        }
        strData.clear();
    }
}

void CGsmModule::handleSmsDeliveryStatus(const int const_nSMSIndex)
{
    CSettingsFile settings("ClanCor", "HHC80xxSMS.xml");
    settings.beginSettingsGroup("SMSDeliveryStatus");
    if(settings.contains(QString::number(const_nSMSIndex)))
    {
        QStringList stringlistSMSStatus = settings.value(QString::number(const_nSMSIndex)).split("-|-");
        /* Change SMS status to DELIVERED */
        if(stringlistSMSStatus.size() > 0)
            settings.setValue(QString::number(const_nSMSIndex), QString(stringlistSMSStatus.at(0) + "-|-" + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm") + "-|-" + const_strSMSDELIVERED));
        stringlistSMSStatus.clear();
    }
}

void CGsmModule::deleteDeliveryStatus()
{
    CSettingsFile settings("ClanCor", "HHC80xxSMS.xml");
    settings.beginSettingsGroup("SMSDeliveryStatus");
    int nLoopCount = 0;
    QStringList stringlistDelCheck = settings.keyList();
    if(stringlistDelCheck.size() > 0)
    {
        while(nLoopCount < stringlistDelCheck.size())
        {
            QStringList stringlistSplitted = settings.value(QString(stringlistDelCheck.at(nLoopCount))).simplified().split("-|-");
            if(stringlistSplitted.size() > 2)
            {
                QDateTime datetimeCheckTime, datetimeTempCompare;
                QString stringTempDate = QString(stringlistSplitted.at(1));
                /* extract SMS datetime from list */
                datetimeCheckTime = datetimeCheckTime.fromString(stringTempDate, "dd/MM/yyyy hh:mm");

                /* Add 12 hours (43200 secs) with datetime of sms  stored */
                datetimeCheckTime = datetimeCheckTime.addSecs(43200);
                datetimeTempCompare = QDateTime::currentDateTime();

                /* Compare to check SMS datetime is 12 hours old */
                if(datetimeCheckTime.operator <(datetimeTempCompare))
                {
                    /* delete 12 hours old SMS from the list */
                    settings.deleteKey(QString(stringlistDelCheck.at(nLoopCount)));
                }
                else
                {
                    //                    qDebug()<<"not deleted key..." +QString(stringlistDelCheck.at(nLoopCount));
                }
            }
            stringlistSplitted.clear();
            nLoopCount++;
        }
    }
}

void CGsmModule::on_timerClose_timeout()
{
    do
    {
        if ( isGprsConnected() || m_nCount == 10 )
        {
            /* close the gprs dialog if gprs is connected or timeout */
            if(gbEnableMessageBoxGSM)
            {
                m_timerGprsConnect.stop();
                m_dialogGprs->close();
            }
            break;
        }
        else
        {
            sleep(1);
            m_nCount++;
        }
    }while(m_nCount <= 10);
}

void CGsmModule::on_timerGprsDisconnect_timeout()
{
    //    /* open the port after 3 seconds */
    //    m_timerGprsDisconnected.stop();
    //    DEBUGMESSAGE("After 3 second opening the port");

    //    m_bGprsDisabled = false;
    //    if ( m_bThreadPause ) {
    //        startThread();
    //    }
    //    else {
    //    }
    //    QString strSharedMemory;
    //    gLoadFromSharedGSM(strSharedMemory);
    //    if(strSharedMemory.contains(const_strSTARTED) || strSharedMemory.contains(const_strGPRS_CONNECTED) || strSharedMemory.contains(const_strGPRS_DISCONNECTED))
    //    {
    //        gLoadIntoSharedGSM(const_strCOMPLETED);
    //    }
}
