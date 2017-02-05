#ifndef UART_H
#define UART_H
#include<fcntl.h>
#include<termios.h>
#include<uart.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#define MODEMDEVICE ("/dev/ttyS3")


extern void portFlush();
extern void serialPortFlush(const char *cFileName);


#endif // UART_H
