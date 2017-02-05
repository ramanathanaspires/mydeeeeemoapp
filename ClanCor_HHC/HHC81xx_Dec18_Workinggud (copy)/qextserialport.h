
#ifndef _QEXTSERIALPORT_H_
#define _QEXTSERIALPORT_H_

/*POSIX CODE
#ifdef _TTY_POSIX_*/
#include "posix_qextserialport.h"

#include <stdio.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>

//Testing
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define QextBaseType Posix_QextSerialPort

/*MS WINDOWS CODE
#else
#include "win_qextserialport.h"
#define QextBaseType Win_QextSerialPort
#endif
*/
class QextSerialPort: public QextBaseType {
public:
    QextSerialPort();
    QextSerialPort(const QString & name);
    QextSerialPort(PortSettings const& s);
    QextSerialPort(const QString & name, PortSettings const& s);
    QextSerialPort(const QextSerialPort& s);
    QextSerialPort& operator=(const QextSerialPort&);

    virtual ~QextSerialPort();
};

#endif
