/**
 * \file "cnetworkstatus.h"
 * \brief it provides an interface for get the status of network interfaces.
 *
 * This file is used to get the network status using ioctl() calls.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CNETWORKSTATUS_H
#define CNETWORKSTATUS_H

/**
 * \fn bool initializeSocket()
 * \brief This function is used to initialize the ethernet socket.
 * \return It returns true, if socket initialized successfully; otherwise returns false.
 */
bool initializeSocket();

/**
 * \fn void closeSocket()
 * \brief This function is used to close the ethernet socket.
 */
void closeSocket();

/**
 * \fn bool getEthernetLinkStatus()
 * \brief This function is used to check whether ethernet interface's link status is active or not(ie connected or not).
 * \return It returns true, if given ethernet interface's link active; otherwise returns false.
 */
bool getEthernetLinkStatus();

/**
 * \fn bool isGprsConnected()
 * \brief This function is used to check whether gprs is connected or not.
 * \return It returns true, if gprs is connected; otherwise returns false.
 */
bool isGprsConnected();

/**
 * \fn bool isIffUp(const QString const_stringIface)
 * \brief This function is used to check whether the given network interface is active or not.
 * \arg[in] const_stringIface is used to pass the network interface name.
 * \return It returns true, if the given network interface is active & link up; otherwise returns false.
 */
bool isIffUp(const QString const_stringIface);

/**
 * \fn bool iffdown(const QString const_stringIface)
 * \brief This function is used to link down the given network interface.
 * \arg[in] const_stringIface is used to pass the network interface name.
 * \return It returns true, if the given network interface has made link down; otherwise returns false.
 */
bool iffDown(const QString const_stringIface);

/**
 * \fn bool iffUp(const QString const_stringIface)
 * \brief This function is used to link up the given network interface.
 * \arg[in] const_stringIface is used to pass the network interface name.
 * \return It returns true, if the given network interface has made link up; otherwise returns false.
 */
bool iffUp(const QString const_stringIface);

/**
 * \fn QString ipAddress(const QString const_stringIface)
 * \brief This function is used to get the ip address of the given network interface.
 * \arg[in] const_stringIface is used to pass the network interface name.
 * \return It returns ip address of the given interface, if the interface is valid and active; otherwise returns NULL string.
 */
QString ipAddress(const QString const_stringIface);

/**
 * \fn QString hardwareAddress(const QString const_stringIface)
 * \brief This function is used to get the Hardware (MAC) address of the given network interface.
 * \arg[in] const_stringIface is used to pass the network interface name.
 * \return It returns hardware address of the given interface, if the device is available; otherwise returns NULL string.
 */
QString hardwareAddress(const QString const_stringIface);

/**
 * \fn QString APMacAddress()
 * \brief This function is used to get the Hardware (MAC) address of the WIFI Access point, if it is connected.
 * \return It returns hardware address of the WIFI Access point, if WIFI connected, otherwise returns NULL string.
 */
QString APMacAddress();

/**
 * \fn bool isGprsConnected()
 * \brief This function is used to get the wifi status & signal level.
 * \arg[out] nLevel used to get the wifi signal level.
 * \return It returns true, if wifi is connected; otherwise returns false.
 */
bool getWifiStatus(int &nLevel);

/**
 * \fn bool ping(QString host)
 * \brief This function is used to ping the given host ip address.
 * \arg[out] nLevel used to get the wifi signal level.
 * \return It returns true, if wifi is connected; otherwise returns false.
 */
bool ping(QString host);

#endif // CNETWORKSTATUS_H
