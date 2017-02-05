#include<uart.h>
#include<string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>


void portFlush()
{
//    printf("\n uartcccc port flush");
    int fd;
    fd = open("/dev/ttyS3", O_RDWR );
    if(fd < 0)
    {
//        printf("\n uartcccc port flush 1");
        perror(MODEMDEVICE);
    }
    else
    {
        int nFinddata;
        nFinddata=tcflush(fd, TCIOFLUSH);
//        printf("\n uartcccc port flush 112 %d",nFinddata);
    }
}
void serialPortFlush(const char *cFileName)
{
//    printf("\n uartcccc port flush Dynamic",cFileName);
    int fd;
    fd = open(cFileName, O_RDWR );
    if(fd < 0)
    {
//        printf("\n uartcccc port flush 1 dynamic");
        perror(MODEMDEVICE);
    }
    else
    {
        int nFinddata;
        nFinddata=tcflush(fd, TCIOFLUSH);
//        printf("\n uartcccc port flush dynamic 112 %d",nFinddata);
    }
}
