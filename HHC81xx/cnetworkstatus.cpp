#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <sys/socket.h>

#include <sys/ioctl.h>
#include <sys/param.h>
#include <linux/sockios.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
//#include <net/if.h>
#include <net/if_arp.h>
#if defined(__GLIBC__) && __GLIBC__ >=2 && __GLIBC_MINOR__ >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/route.h>
#include <arpa/inet.h>
#else
#include <sys/types.h>
#include <netinet/if_ether.h>
#endif

//#include <unistd.h>
//#include <ctype.h>
//#include <fcntl.h>
//#include <getopt.h>
//#include <time.h>
#include <netdb.h>
#include "mii.h"
#include <linux/wireless.h>
#include "cglobal.h"
#include "csettingsfile.h"
//#include "QMutex"

using namespace ClanCor;
using namespace Global;
QMutex locker,lockerIsIffup,lockerIffDown, lockerIffUp;
/*--------------------------------------------------------------------*/

int skfd = -1;		/* AF_INET socket for ioctl() calls. */
struct ifreq ifr;
struct mii_data *mii = (struct mii_data *)&ifr.ifr_data;
/*--------------------------------------------------------------------*/
bool initializeSocket()
{
    /* Open a basic socket. */
    if ( (skfd = socket(AF_INET, SOCK_DGRAM,0)) < 0 ) {
        qDebug()<<"socket Error ";
        return false;
    }
    /* Get the vitals from the interface. */
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
    if ( ioctl(skfd, SIOCGMIIPHY, &ifr) < 0 ) {
        if ( errno != ENODEV ) {
            qDebug()<<"SIOCGMIIPHY failed ";
        }
        return false;
    }
    return true;
}

void closeSocket()
{
    close(skfd);
}

bool getEthernetLinkStatus()
{
    QMutex mutexLinkStatus;
    mutexLinkStatus.lock();
    int mii_val;
//    qDebug()<<"\r*********In getIFLinkStatus IF name-->"<<const_stringIface<<" "<<const_stringIface.toLatin1();

    if(isIffUp("eth0"))
    {
        mii->reg_num = 1;
        /* Some bits in the BMSR are latched, but we can't rely on being
       the only reader, so only the current values are meaningful */
        if (ioctl(skfd, SIOCGMIIREG, &ifr) < 0) {
            //qDebug()<<QString("SIOCGMIIREG on" + QString(ifr.ifr_name) + "failed " ));
            mutexLinkStatus.unlock();
            return false;
        }
        else {
            mii_val = mii->val_out;

            if ( mii_val == 0x0000) {
                /* No MII transceiver present!. */
            }
            else {
                if ( mii_val & MII_BMSR_LINK_VALID ) {
                    /* ethernet is connected */
                    mutexLinkStatus.unlock();
                    return true;
                }
                else {
                    /* ethernet is not connected */
                    mutexLinkStatus.unlock();
                    return false;
                }
            }
        }
    }
    mutexLinkStatus.unlock();
    return false;
}

bool  isGprsConnected()
{
    bool bResponse;

    if ( isIffUp("ppp0")) {
        bResponse = true;
    }
    else {
        bResponse = false;
    }
    return bResponse;
}

bool isIffUp(const QString const_stringIface)
{
    lockerIsIffup.lock();
    struct ifreq ifr_isifup;

    /* get interface name */
//    qDebug()<<"\rIF name-->"<<const_stringIface<<" "<<const_stringIface.toLatin1();
//    qDebug()<<"\rsocket val-->"<<skfd;
    strncpy(ifr_isifup.ifr_name, const_stringIface.toLatin1(), IFNAMSIZ);
    /* Read interface flags */
    int rv = 0;
    if ((rv = ioctl(skfd, SIOCGIFFLAGS, &ifr_isifup)) < 0) {
//        qDebug("isIffup: shutdown->returned...%d", rv);
        lockerIsIffup.unlock();
        return false;
    }
    if (ifr_isifup.ifr_flags & IFF_UP) {
        lockerIsIffup.unlock();
        return true;
    }
    lockerIsIffup.unlock();
    return false;
}

bool iffDown(const QString const_stringIface)
{
    lockerIffDown.lock();
    if(const_stringIface == "")
    {
        lockerIffDown.unlock();
        return false;
    }
    if (isIffUp(const_stringIface)) {
        struct ifreq ifr_down;

        /* get interface name */
        strncpy(ifr_down.ifr_name, const_stringIface.toLatin1(), IFNAMSIZ);
        /* Read interface flags */
        if (isIffUp(const_stringIface)) {
            ifr_down.ifr_flags = 0x0;
            ifr_down.ifr_flags &= ~IFF_UP;
            if (ioctl(skfd, SIOCSIFFLAGS, &ifr_down) < 0) {
                qDebug("ifdown: failed ");
                lockerIffDown.unlock();
                return false;
            }
        }
    }
    lockerIffDown.unlock();
    return true;
}

bool iffUp(const QString const_stringIface)
{
    lockerIffUp.lock();
    if(const_stringIface == "")
    {
        lockerIffUp.unlock();
        return false;
    }

    /* Read interface flags */
    if (isIffUp(const_stringIface)) {
        lockerIffUp.unlock();
        return true;
    }
    else
    {
        struct ifreq ifr_up;
        struct sockaddr_in sin;

        QString stringIpAddr, stringSubnet, stringGateWay;
        CSettingsFile csettingsNetworkInfo;
        if(const_stringIface == "eth0")
        {
            if(csettingsNetworkInfo.contains("NetworkEthernetConfiguration") && csettingsNetworkInfo.contains("EthIpAddress"))
            {
                if(csettingsNetworkInfo.beginSettingsGroup("NetworkEthernetConfiguration"))
                {
                    stringIpAddr = csettingsNetworkInfo.value("EthIpAddress");
                    stringSubnet = csettingsNetworkInfo.value("EthSubnet");
                    stringGateWay = csettingsNetworkInfo.value("EthGateway");
                }
            }
        }
        else
        {
            if(csettingsNetworkInfo.contains("NetworkWifiConfiguration") && csettingsNetworkInfo.contains("Essid"))
            {
                if(csettingsNetworkInfo.beginSettingsGroup("NetworkWifiConfiguration"))
                {
                    stringIpAddr = csettingsNetworkInfo.value("IpAddress");
                    stringSubnet = csettingsNetworkInfo.value("Subnet");
                    stringGateWay = csettingsNetworkInfo.value("Gateway");
                }
            }
        }

        if((stringIpAddr == "") || (stringSubnet == "") || (stringGateWay == ""))
        {
            lockerIffUp.unlock();
            return false;
        }

        /* copy interface name */
        strncpy(ifr_up.ifr_name, const_stringIface.toLatin1(), IFNAMSIZ);

        ifr_up.ifr_flags = 0x0;
        ifr_up.ifr_flags |= IFF_UP | IFF_RUNNING | IFF_BROADCAST  | IFF_MULTICAST;
        if ( ioctl(skfd, SIOCSIFFLAGS, &ifr_up) < 0 ) {
            qDebug("ifup: failed ");
            lockerIffUp.unlock();
            return false;
        }
        sin.sin_family = AF_INET;

        // Convert IP from numbers and dots to binary notation
        inet_aton(stringIpAddr.toLatin1(),(in_addr*) &sin.sin_addr.s_addr);
        memcpy(&ifr_up.ifr_addr, &sin, sizeof(struct sockaddr));

        // Set interface address
        if (ioctl(skfd, SIOCSIFADDR, &ifr_up) < 0) {
            qDebug("Cannot set IP address. ");
            lockerIffUp.unlock();
            return false;
        }

        // Convert IP from numbers and dots to binary notation
        inet_aton(stringSubnet.toLatin1(),(in_addr*) &sin.sin_addr.s_addr);
        memcpy(&ifr_up.ifr_netmask, &sin, sizeof(struct sockaddr));
        // Set interface address
        if (ioctl(skfd, SIOCSIFNETMASK, &ifr_up) < 0) {
            qDebug("Cannot set netmask address. ");
            lockerIffUp.unlock();
            return false;
        }

        struct rtentry route;
        struct sockaddr_in *addr;
        int err = 0;

        memset(&route, 0, sizeof(route));
        addr = (struct sockaddr_in*) &route.rt_gateway;
        addr->sin_family = AF_INET;
        addr->sin_addr.s_addr = inet_addr(stringGateWay.toLatin1());
        addr = (struct sockaddr_in*) &route.rt_dst;
        addr->sin_family = AF_INET;
        addr->sin_addr.s_addr = inet_addr("0.0.0.0");
        addr = (struct sockaddr_in*) &route.rt_genmask;
        addr->sin_family = AF_INET;
        addr->sin_addr.s_addr = inet_addr("0.0.0.0");
        route.rt_flags = RTF_UP | RTF_GATEWAY;
        route.rt_metric = 0;
        char lcDevname[const_stringIface.size() + 1];

        strncpy(lcDevname, const_stringIface.simplified().toLatin1(), const_stringIface.simplified().size());
        lcDevname[const_stringIface.simplified().size() + 1] = '\0';
        route.rt_dev = lcDevname;
        if ((err = ioctl(skfd, SIOCADDRT, &route)) != 0) {
            qDebug("SIOCADDRT failed");
            lockerIffUp.unlock();
            return false;
        }
    }
    lockerIffUp.unlock();
    return true;
}

QString ipAddress(const QString const_stringIface)
{
    struct ifreq ifr_ipaddr;
    struct sockaddr_in sin;

    QString stringIpAddr;
    if(isIffUp(const_stringIface))
    {
        /* get interface name */
        strncpy(ifr_ipaddr.ifr_name,  const_stringIface.toLatin1(), IFNAMSIZ);

        if (ioctl(skfd, SIOCGIFADDR, &ifr_ipaddr) < 0) {
                qDebug("Cannot get ip address. ");
                return "";
        }
        sin.sin_family = AF_INET;

        // Convert IP from numbers and dots to binary notation
        memcpy(&sin, &ifr_ipaddr.ifr_addr, sizeof(struct sockaddr));
        stringIpAddr = QString((const char*)inet_ntoa(sin.sin_addr));
    }
    else
    {
        stringIpAddr = "";
    }
    return stringIpAddr;

}

QString hardwareAddress(const QString const_stringIface)
{
    struct ifreq ifr_hw;

    char hwaddr[20];
    strcpy(hwaddr, "");
    if(iffUp(const_stringIface))
    {
        /* get interface name */
        strncpy(ifr_hw.ifr_name,  const_stringIface.toLatin1(), IFNAMSIZ);

        if (ioctl(skfd, SIOCGIFHWADDR, &ifr_hw) < 0) {
            qDebug("\rCannot get hw address. ");
            iffDown("wlan0");
            return "";
        }
        sprintf( hwaddr, "%02x:%02x:%02x:%02x:%02x:%02x",
                 (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[0], (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[1], (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[2], (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[3], (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[4], (int) ((unsigned char *) &ifr_hw.ifr_hwaddr.sa_data)[5] );
    }
    else
    {
        iffDown("wlan0");
        qDebug()<<"\rError while iffup wlan0";
        return "";
    }
    iffDown("wlan0");
    if(QString((const char *)hwaddr) != "")
        return QString((const char *) hwaddr);
    else
        return "";
}

QString APMacAddress()
{
    struct iwreq wreq;

    char hwaddr[20];
    bool bFoundAP = false;
    int nFailCount = 0;
    strcpy(hwaddr, "");
    if(isIffUp("wlan0"))
    {
        /* get interface name */
        strncpy(wreq.ifr_name, "wlan0", IFNAMSIZ);
        do
        {
            if (ioctl(skfd, SIOCGIWAP, &wreq) < 0) {
                qDebug("Cannot get AP address. ");
                nFailCount++;
                continue;
            }
            sprintf( hwaddr, "%02x:%02x:%02x:%02x:%02x:%02x",
                     (int) ((unsigned char *) &wreq.u.ap_addr)[2], (int) ((unsigned char *) &wreq.u.ap_addr)[3], (int) ((unsigned char *) &wreq.u.ap_addr)[4], (int) ((unsigned char *) &wreq.u.ap_addr)[5], (int) ((unsigned char *) &wreq.u.ap_addr)[6], (int) ((unsigned char *) &wreq.u.ap_addr)[7] );
            qDebug()<<QString((const char *) hwaddr);
            if(QString((const char *) hwaddr) == "00:00:00:00:00:00")
            {
                bFoundAP = false;
            }
            else
            {
                bFoundAP = true;
            }
            nFailCount++;
        }while (bFoundAP == false && nFailCount < 3);
        if(!bFoundAP)
        {
            return "";
        }
    }
    return QString((const char *) hwaddr);
}

bool getWifiStatus(int &nLevel)
{
    locker.lock();
    bool bResponse;

    if ( isIffUp("wlan0")) {
        /* wifi is connected */
        bResponse = true;
    }
    else {
        /* wifi is not connected */
        bResponse = false;
    }
    if ( bResponse ) {
        /* get rssi vakue using ioctl() call */
        struct iwreq wreq;
        struct iw_statistics stats;
        int rssi, noise;
        wreq.u.data.pointer = (caddr_t) &stats;
        wreq.u.data.length = sizeof(stats);
        wreq.u.data.flags = 1; /* Clear updated flag */
        strncpy(wreq.ifr_name, "wlan0", IFNAMSIZ);
        if ( ioctl(skfd, SIOCGIWSTATS, &wreq) < 0 ) {
           qDebug()<<"SIOCGIWSTATS error";
        }
        else {
            if ( stats.qual.updated & IW_QUAL_DBM ) {
                /* Values in dBm, stored in u8 with range 63 : -192 */
                rssi = ( stats.qual.level > 63 ) ?
                stats.qual.level - 0x100 :
                stats.qual.level;
                noise = ( stats.qual.noise > 63 ) ?
                stats.qual.noise - 0x100 :
                stats.qual.noise;
            }
            else {
                rssi = stats.qual.level;
                noise = stats.qual.noise;
            }
            /* calculate signal level using given rssi value */

            if ( rssi < 20 ) {
                nLevel = 0;
            }
            else if ( rssi >= 20 && rssi < 35 ) {
                nLevel = 1;
            }
            else if ( rssi >= 35 && rssi < 50 ) {
                nLevel = 2;
            }
            else if ( rssi >= 50 && rssi < 65 ) {
                nLevel = 3;
            }
            else if ( rssi >= 65 && rssi < 80 ) {
                nLevel = 4;
            }
            else {
                nLevel = 5;
            }
            DEBUGMESSAGE("Rssi:" + gConvertToString(rssi ) +" Level:" + gConvertToString(nLevel));
        }
    }
    /* close the wifi socket */
    locker.unlock();
    return bResponse;
}

/***************************************Code for ping operation****************/

#define	ICMP_MINLEN	8				/* abs minimum */
#define DEFDATALEN      56
#define	MAXIPLEN	60
#define	MAXICMPLEN	76
#define	MAXPACKET	65468
#define	MAX_DUP_CHK	(8 * 128)
#define MAXWAIT         10
#define PINGINTERVAL    1		/* second */

#define O_QUIET         (1 << 0)

static char rcvd_tbl[MAX_DUP_CHK / 8];

#define	A(bit)		rcvd_tbl[(bit)>>3]	/* identify byte in array */
#define	B(bit)		(1 << ((bit) & 0x07))	/* identify bit in byte */
#define	SET(bit)	(A(bit) |= B(bit))
#define	CLR(bit)	(A(bit) &= (~B(bit)))
#define	TST(bit)	(A(bit) & B(bit))


static char *hostname = NULL;
static struct sockaddr_in pingaddr;
static int pingsock = -1;
static int datalen = DEFDATALEN;

static int myid = 0, options = 0;
static char *icmp_type_name (int id)
{
        switch (id) {
        case ICMP_ECHOREPLY: 		return (char*)"Echo Reply";
        case ICMP_DEST_UNREACH: 	return (char*)"Destination Unreachable";
        case ICMP_SOURCE_QUENCH: 	return (char*)"Source Quench";
        case ICMP_REDIRECT: 		return (char*)"Redirect (change route)";
        case ICMP_ECHO:                 return (char*)"Echo Request";
        case ICMP_TIME_EXCEEDED: 	return (char*)"Time Exceeded";
        case ICMP_PARAMETERPROB: 	return (char*)"Parameter Problem";
        case ICMP_TIMESTAMP: 		return (char*)"Timestamp Request";
        case ICMP_TIMESTAMPREPLY: 	return (char*)"Timestamp Reply";
        case ICMP_INFO_REQUEST: 	return (char*)"Information Request";
        case ICMP_INFO_REPLY:           return (char*)"Information Reply";
        case ICMP_ADDRESS:              return (char*)"Address Mask Request";
        case ICMP_ADDRESSREPLY: 	return (char*)"Address Mask Reply";
        default: 			return (char*)"unknown ICMP type";
        }
}

unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)
    {
          sum += *w++;
          nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1)
    {
          *(u_char *) (&answer) = *(u_char *) w;
          sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);		/* add hi 16 to low 16 */
    sum += (sum >> 16);				/* add carry */
    answer = ~sum;				/* truncate to 16 bits */
    return (answer);
}

bool ping(QString host)
{
    struct protoent *proto;
    struct hostent *h;
    char buf[MAXHOSTNAMELEN];
    char packet[datalen + MAXIPLEN + MAXICMPLEN];
    int sockopt;

    proto = getprotobyname("icmp");
    /* if getprotobyname failed, just silently force
     * proto->p_proto to have the correct value for "icmp" */
    if ((pingsock = socket(AF_INET, SOCK_RAW,
                           (proto ? proto->p_proto : 1))) < 0) {	/* 1 == ICMP */
        if (errno == EPERM) {
            qDebug("ping: permission denied. (are you root?)\n");
        } else {
            qWarning("ping: creating a raw socket");
        }
        return false;
    }

    /* drop root privs if running setuid */
    setuid(getuid());

    memset(&pingaddr, 0, sizeof(struct sockaddr_in));

//    pingaddr.sin_family = AF_INET;
//    if (!(h = gethostbyname(host.toLatin1()))) {
//        qDebug()<<"ping: unknown host " <<host;
//        return false;
//    }

//    if (h->h_addrtype != AF_INET) {
//        qDebug("ping: unknown address type; only AF_INET is currently supported.");
//        return false;
//    }

    pingaddr.sin_family = AF_INET;	/* h->h_addrtype */

    pingaddr.sin_addr.s_addr = inet_addr(host.toLatin1());
//    memcpy(&pingaddr.sin_addr, h->h_addr, sizeof(pingaddr.sin_addr));
//    strncpy(buf, h->h_name, sizeof(buf) - 1);
//    hostname = buf;

    /* enable broadcast pings */
    sockopt = 1;
    setsockopt(pingsock, SOL_SOCKET, SO_BROADCAST, (char *) &sockopt,
               sizeof(sockopt));

    /* set recv buf for broadcast pings */
    sockopt = 48 * 1024;
    setsockopt(pingsock, SOL_SOCKET, SO_RCVBUF, (char *) &sockopt,
               sizeof(sockopt));

    qDebug("\rPING %s (%s): %d data bytes\n",hostname,
           inet_ntoa(*(struct in_addr *) &pingaddr.sin_addr.s_addr),
           datalen);

    struct icmp *pkt;
    int i;
    char packet1[datalen + 8];

    pkt = (struct icmp *) packet1;

    pkt->icmp_type = ICMP_ECHO;
    pkt->icmp_code = 0;
    pkt->icmp_cksum = 0;
    pkt->icmp_seq = 0;
    pkt->icmp_id = myid;
    CLR(pkt->icmp_seq % MAX_DUP_CHK);

    gettimeofday((struct timeval *) &packet1[8], NULL);
    pkt->icmp_cksum = in_cksum((unsigned short *) pkt, sizeof(packet1));

    i = sendto(pingsock, packet1, sizeof(packet1), 0,
               (struct sockaddr *) &pingaddr, sizeof(struct sockaddr_in));

    if (i < 0)
        qDebug("ping: sendto: %s\n", strerror(errno));
    else if ((unsigned)i != sizeof(packet1))
        qDebug("ping wrote %d chars; %d expected\n", i,
               (int)sizeof(packet1));

    struct sockaddr_in from;
    socklen_t fromlen = (socklen_t) sizeof(from);
    int c;

    if ((c = recvfrom(pingsock, packet, sizeof(packet), 0,
                      (struct sockaddr *) &from, &fromlen)) < 0) {
        if (errno == EINTR)
        {
            //                    continue;
        }
        qWarning("ping: recvfrom");
        //            continue;
    }
    char *buffer;
    buffer = packet;
    struct icmp *icmppkt;
    struct iphdr *iphdr;
    struct timeval tv, *tp;
    int hlen, dupflag;
    unsigned long triptime;

    gettimeofday(&tv, NULL);

    /* check IP header */
    iphdr = (struct iphdr *) buffer;
    hlen = iphdr->ihl << 2;
    /* discard if too short */

    if (c < (datalen + ICMP_MINLEN))
    {
        return false;
    }

    c -= hlen;
    icmppkt = (struct icmp *) (buffer + hlen);

    if (icmppkt->icmp_id != myid)
    {
        return false;				/* not our ping */
    }


    if (icmppkt->icmp_type == ICMP_ECHOREPLY) {
        //            ++nreceived;
        tp = (struct timeval *) icmppkt->icmp_data;

        if ((tv.tv_usec -= tp->tv_usec) < 0) {
            --tv.tv_sec;
            tv.tv_usec += 1000000;
        }
        tv.tv_sec -= tp->tv_sec;

        triptime = tv.tv_sec * 10000 + (tv.tv_usec / 100);

        if (TST(icmppkt->icmp_seq % MAX_DUP_CHK)) {
            dupflag = 1;
        } else {
            SET(icmppkt->icmp_seq % MAX_DUP_CHK);
            dupflag = 0;
        }

        if (options & O_QUIET)
            return false;

        qDebug("\r%d bytes from %s: icmp_seq=%u ttl=%d time=%lu.%lu ms", c ,
               inet_ntoa(*(struct in_addr *) &from.sin_addr.s_addr),
               icmppkt->icmp_seq, iphdr->ttl, triptime / 10, triptime % 10);
        if (dupflag)
            qDebug(" (DUP!)");
    } else
    {
        if (icmppkt->icmp_type != ICMP_ECHO)
            qDebug("Warning: Got ICMP %d (%s)\n",
                   icmppkt->icmp_type, icmp_type_name (icmppkt->icmp_type));
        qDebug("failed");
        return false;
    }
    return true;
}
