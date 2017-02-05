#include "cwebcam.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <linux/videodev2.h>
#ifdef USE_UVCVIDEO
#include <uvcvideo.h>
#endif //USE_UVCVIDEO

#include <QPainter>
#include <QImage>
#include <QSize>
#include <QSocketNotifier>
#include <QDebug>
#include <stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define YUV2RGB(y,u,v,value) \
        (r) = ( ( (y) << 8 ) 			   + 359 * ( (v) - 128 ) ) >> 8; \
        (g) = ( ( (y) << 8 ) -  88 * ( (u) - 128 ) - 183 * ( (v) - 128 ) ) >> 8; \
        (b) = ( ( (y) << 8 ) + 456 * ( (u) - 128 ) 			 ) >> 8; \
        r  = MAX(0, MIN(255, (r))); \
        g  = MAX(0, MIN(255, (g))); \
        b  = MAX(0, MIN(255, (b))); \
        value=(0xffu << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)  //24 bit color
        //value=((r >> (8 - 5)) << 11) | ((g >> (8 - 6)) << 5) | ((b >> (8 - 5)) << 0) //16 bit color

#define MEAN(a,b) \
        (a + b) / 2

using namespace ClanCor;
unsigned char arr_cJpeg[0x1a4] = {
    0xff, 0xc4, 0x01, 0xa2,

    0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,

    0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,

    0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d,
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
    0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa,0x11,

    0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77,
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
    0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
    0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
    0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa
};

CWebcam::CWebcam() :
        m_imageCaptured(320, 240, QImage::Format_RGB32)
{
    m_bStreaming = false;
    dev = 0;
    m_bOpened = false;
    socketNotifierImage = 0;
    m_bAllocated = false;

    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoBackground);
    setAutoFillBackground(false);
}

void CWebcam::clear()
{
    m_bClear = true;
    m_imageCaptured.fill(qRgb(255,255,255));
}

void CWebcam::close()
{
    stopStreaming();
    ::close(dev);
    mem[0] = '\0';
    socketNotifierImage = 0;
    delete socketNotifierImage;
    delete fmt;
    delete buf;
    delete rb;
    m_bOpened = false;
    m_bAllocated = false;
}

int CWebcam::open(const char *devFile)
{
    struct v4l2_capability cap;
    int ret;
    char str[256];
    m_bPause = false;
    m_bReady = false;
    if ( m_bOpened ) {
        close();
    }
    dev = ::open(devFile, O_RDWR);
    if ( dev < 0 ) {
        strcpy(str, "Error Opening ");
        kError(strcat(str, devFile), errno);
        return EXIT_FAILURE;
    }
    memset(&cap, 0, sizeof cap);
    ret = ioctl(dev, VIDIOC_QUERYCAP, &cap);
    if ( ret < 0 ) {
        strcpy(str, "Error querying capabilities for ");
        kError(strcat(str, devFile), errno);
        return EXIT_FAILURE;
    }
    if ( (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0 ) {
        strcpy(str, "Error checking caps for ");
        kError(strcat(str, devFile), errno);
        return -EINVAL;
    }
    m_bOpened = true;
    buf = new v4l2_buffer;
    rb = new v4l2_requestbuffers;
    fmt = new v4l2_format;
    socketNotifierImage = new QSocketNotifier(dev, QSocketNotifier::Read);
    socketNotifierImage->setEnabled(false);
    connect(socketNotifierImage, SIGNAL(activated(int)), this, SLOT(getFrame()));
    return EXIT_SUCCESS;
}

QList<int> CWebcam::getFormatList(QList<QString> &description) const
{
    QList<int> formatList;
    int ret;
    struct v4l2_fmtdesc fmtList;
    memset(&fmtList, 0, sizeof fmtList);
    fmtList.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int i = 0;
    do {
        fmtList.index = i;
        if ( (ret = ioctl(dev, VIDIOC_ENUM_FMT, &fmtList)) < 0 ) {
            break;
        }
        else {
            formatList.append((int)fmtList.pixelformat);
            description.append((char*)fmtList.description);
        }
        i++;
    } while ( ret != EINVAL ) ;
    return formatList;
}

QList<QSize> CWebcam::getSizesList() const
{
#ifdef USE_UVCVIDEO
    int i = 0;
    QList<QSize> rSizes;
    QSize tmp;
    struct v4l2_frmsizeenum sizes;
    memset(&sizes, 0, sizeof sizes);
    sizes.pixel_format = currentPixelFormat();
    sizes.index = i;
    while ( ioctl(dev, VIDIOC_ENUM_FRAMESIZES, &sizes) != -1 ) {
        tmp.setWidth((int)sizes.discrete.width);
        tmp.setHeight((int)sizes.discrete.height);
        rSizes.append(tmp);
        i++;
        sizes.index = i;
    }
    return rSizes;
#else
    QList<QSize> rSizes;
    QSize tmp;

    tmp.setWidth(320);
    tmp.setHeight(240);

    rSizes << tmp;

    return rSizes;
#endif
}


int CWebcam::setFormat(unsigned int width, unsigned int height, int pixelformat)
{
    int i = 0;

    if ( m_bStreaming ) {
        return -1;
    }

    struct v4l2_frmivalenum parm1;
    memset(&parm1, 0, sizeof parm1);
    //parm1.type= V4L2_FRMIVAL_TYPE_DISCRETE;
    parm1.width = width;
    parm1.height = height;
    parm1.pixel_format = pixelformat;
//    parm1.discrete.numerator = 1;
//    parm1.discrete.denominator = 30;
    i=0;
    parm1.index = i;
    while ( ioctl(dev, VIDIOC_ENUM_FRAMEINTERVALS, &parm1) != -1 ) {
        printf("index: %d types: %d \n",i,parm1.type);
        printf("denometer: %d\r\n\n",parm1.discrete.denominator);
        i++;
        parm1.index = i;
    }

    memset(fmt, 0, sizeof fmt);
    fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt->fmt.pix.width = width;
    fmt->fmt.pix.height = height;
    fmt->fmt.pix.field = V4L2_FIELD_ANY;
    fmt->fmt.pix.pixelformat = pixelformat;

    if ( ioctl(dev, VIDIOC_S_FMT, fmt) < 0 ) {
        kError(const_cast<char *>("Error while setting format"), errno);
        i++;
        return EXIT_FAILURE;
    }

    struct v4l2_streamparm parm;
    memset(&parm, 0, sizeof parm);
    struct v4l2_captureparm *cp = &parm.parm.capture;
    struct v4l2_fract *tpf = &cp->timeperframe;
    parm.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    cp->capability = V4L2_CAP_TIMEPERFRAME;

    tpf->numerator=1;
    tpf->denominator=30;
    if ( ioctl(dev, VIDIOC_S_PARM,&parm) < 0 ) {
        kError(const_cast<char *>("Error while setting Frame"), errno);
    }
    printf("\r\nGet value: %d", tpf->denominator);

    return EXIT_SUCCESS;
}

int CWebcam::streamOff()
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret;

    if ( ! m_bStreaming ) {
        return -1;
    }

    ret = ioctl(dev, VIDIOC_STREAMOFF, &type);
    if ( ret < 0 ) {
        kError(const_cast<char *>("Unable to stop capture"), errno);
        return EXIT_FAILURE;
    }
    m_bStreaming = false;
    return EXIT_SUCCESS;
}

int CWebcam::startStreaming()
{
    int i, ret;
    if ( ! m_bOpened ) {
        return -1;
    }
    if ( (ret = setFormat(currentWidth(), currentHeight(), currentPixelFormat())) != 0 ) {
        printf("set format error : %d\n", ret);
        return EXIT_FAILURE;
    }

    //Allocate buffers
    if ( ! m_bAllocated ) {
        memset(rb, 0, sizeof rb);
        rb->count = 2;
        rb->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        rb->memory = V4L2_MEMORY_MMAP;
        ret = ioctl(dev, VIDIOC_REQBUFS, rb);
        if ( ret < 0 ) {
            kError(const_cast<char *>("Unable to allocate buffers"), errno);
            return EXIT_FAILURE;
        }
        m_bAllocated = true;
    }


    // Map the buffers. /
    memset(buf, 0, sizeof buf);
    buf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf->memory = V4L2_MEMORY_MMAP;
    for ( i = 0; i < 2; i ++ ) {
        buf->index = i;
        ret = ioctl(dev, VIDIOC_QUERYBUF, buf);
        if ( ret < 0 ) {
            kError(const_cast<char *>("Unable to query buffer"), errno);
            return EXIT_FAILURE;
        }
        mem[i] = (uchar *) mmap(0, buf->length, PROT_READ, MAP_SHARED, dev, buf->m.offset);
        if ( mem[i] == MAP_FAILED ) {
            kError(const_cast<char *>("Unable to map buffer"), errno);
            return EXIT_FAILURE;
        }
        bufLength = buf->length;
        m_bMaped = true;
    }

    // Queue the buffers. /
    for ( i = 0; i < 2; i ++ ) {
        buf->index = i;
        ret = ioctl(dev, VIDIOC_QBUF, buf);
        if ( ret < 0 ) {
            kError(const_cast<char *>("Unable to queue buffer"), errno);
            return EXIT_FAILURE;
        }
    }

    // Start Streaming.
    ret = ioctl(dev, VIDIOC_STREAMON, &buf->type);
    if ( ret < 0 ) {
        kError(const_cast<char *>("Unable to start capture"), errno);
        return EXIT_FAILURE;
    }

    socketNotifierImage->setEnabled(true);
    m_bStreaming = true;
    return EXIT_SUCCESS;
}

int CWebcam::stopStreaming()
{
    if ( ! m_bStreaming ) {
        return -1;
    }
    socketNotifierImage->setEnabled(false);

    if ( munmap(mem[0], bufLength) == -1 ) {
        printf("CWebcam::stopStreaming : munmap 0 failed. errno = %d\n", errno);
    }

    if ( munmap(mem[1], bufLength) == -1 ) {
        printf("CWebcam::stopStreaming : munmap 1 failed. errno = %d\n", errno);
    }
    else {
        m_bMaped = false;
    }

    if ( streamOff() == 0 ) {
        m_bStreaming = false;
        printf("* Succesful Stopped\n");
    }
    else {
        socketNotifierImage->setEnabled(true);
    }
    return EXIT_SUCCESS;
}

void CWebcam::getFrame()
{
    int ret = 0;
    m.lock();
    // Dequeue a buffer.
    ret = ioctl(dev, VIDIOC_DQBUF, buf);
    if ( ret < 0 ) {
        kError(const_cast<char *>("Unable to dequeue buffer"), errno);
        socketNotifierImage->setEnabled(false);
        emit disconnected();
        m.unlock();
        return ;
    }
    // Save the image.
    if ( fmt->fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG ) {
        uchar jpegBuf1[buf->bytesused + 420];
        if ( mjpegToJpeg(mem[buf->index], jpegBuf1, (int) buf->bytesused) == EXIT_SUCCESS && ! m_bPause ) {
             m_imageCaptured.loadFromData(jpegBuf1, buf->bytesused+420);
             update();
        }
        jpegBuf1[0]= '\0';
    }
    if ( fmt->fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV ) {
        if ( ! m_bPause ) {
            yuvToJpeg(mem[buf->index],currentWidth(), currentHeight());
        }
    }
    // Requeue the buffer.
    ret = ioctl(dev, VIDIOC_QBUF, buf);
    if ( ret < 0 ) {
        kError(const_cast<char *>("Unable to requeue buffer"), errno);
        socketNotifierImage->setEnabled(false);
        emit disconnected();
        m.unlock();
        return ;
    }
    m.unlock();
    if ( ! m_bReady ) {
        m_bReady = true;
        emit ready();
    }
    if ( ! socketNotifierImage->isEnabled() ) {
        socketNotifierImage->setEnabled(true);
    }
}

int CWebcam::changeCtrl(int ctrl, int value) // an enum for formats and reorganisation would be great...
{
    struct v4l2_queryctrl queryctrl;
    struct v4l2_control control;

    if ( ! m_bOpened ) { // At the begining of the function.
        return -1;
    }
/*
* ctrl values :
* 	0 : Saturation
* 	1 : Power line Frequency (néons)
* 	2 : Brightness
* 	3 : Contrast
* 	4 : Sharpness
* 	5 : Reset Pan/Tilt
*/
    __u32 CTRL;
    switch ( ctrl ) {
        case Saturation:
            CTRL = V4L2_CID_SATURATION;
            break;
        case Brightness:
            CTRL = V4L2_CID_BRIGHTNESS;
            break;
        case Contrast:
            CTRL = V4L2_CID_CONTRAST;
            break;
        case Sharpness:
            CTRL = V4L2_CID_SHARPNESS;
            break;
#ifdef USE_UVCVIDEO
        case PowerLineFreq:
            CTRL = V4L2_CID_POWER_LINE_FREQUENCY;
            break;
        case PanTiltReset:
            CTRL = V4L2_CID_PANTILT_RESET;
            value = 3;
            break;
#endif
        default:
                CTRL = 0;
    }

    memset (&queryctrl, 0, sizeof queryctrl);
    memset (&control, 0, sizeof control);
    queryctrl.id = CTRL;
    if ( -1 == ioctl (dev, VIDIOC_QUERYCTRL, &queryctrl) ) {
        if ( errno != EINVAL ) {
#ifdef DEBUG
            perror ("VIDIOC_QUERYCTRL");
#endif
            return EXIT_FAILURE;
        }
    }
    else {
        control.id = CTRL;
        control.value = value;
        if ( -1 == ioctl (dev, VIDIOC_S_CTRL, &control) ) {
#ifdef DEBUG
        perror("VIDIOC_S_CTRL");
        printf(" * Error while setting control\n");
#endif
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int CWebcam::currentWidth() const
{
    return (int) fmt->fmt.pix.width;
}

int CWebcam::currentHeight() const
{
    return (int) fmt->fmt.pix.height;
}

int CWebcam::currentPixelFormat() const
{
    return (int) fmt->fmt.pix.pixelformat;
}


int CWebcam::defaultCtrlVal(unsigned int control, int &defaultvalue)
{
    struct v4l2_queryctrl queryctrl;
    char *ctrl;

    if(!m_bOpened)
    {
            return false;
    }

    memset(&queryctrl, 0, sizeof queryctrl);
    switch(control)
    {
            case Saturation :
            {
                    ctrl =const_cast<char *>("Saturation");
                    queryctrl.id = V4L2_CID_SATURATION;
                    break;
            }
            case Brightness :
            {
                    ctrl = const_cast<char *>("Brightness");
                    queryctrl.id = V4L2_CID_BRIGHTNESS;
                    break;
            }
            case Contrast :
            {
                    ctrl = const_cast<char *>("Contrast");
                    queryctrl.id = V4L2_CID_CONTRAST;
                    break;
            }
            case Sharpness :
            {
                    ctrl = const_cast<char *>("Sharpness");
                    queryctrl.id = V4L2_CID_SHARPNESS;
                    break;
            }
#ifdef USE_UVCVIDEO
            case PowerLineFreq :
            {
                    ctrl = const_cast<char *>("Powerline Frequecy");
                    queryctrl.id = V4L2_CID_POWER_LINE_FREQUENCY;
                    break;
            }
#endif
            default :
                    ctrl =const_cast<char *>("ERROR");
    }

    char str[128];
    if (-1 == ioctl(dev, VIDIOC_QUERYCTRL, &queryctrl))
    {
            strcpy(str, "Unable to set control ");
            printf("ERROR\n");
            kError(strcat(str, ctrl), errno);
            return false;
    }

    defaultvalue = (int)queryctrl.default_value;

    return true;
}

bool CWebcam::panTiltSupported()
{
#ifdef USE_UVCVIDEO
    struct v4l2_queryctrl queryctrl;

    if ( ! m_bOpened ) {
        return false;
    }

    memset(&queryctrl, 0, sizeof queryctrl);
    queryctrl.id = V4L2_CID_TILT_RELATIVE; // Could be V4L2_CID_PAN_RELATIVE.

    if ( -1 == ioctl(dev, VIDIOC_QUERYCTRL, &queryctrl) ) {
        kError("Unable to check wether Pan Tilt is supported.", errno);
        return false;
    }

    if ( queryctrl.flags & V4L2_CTRL_FLAG_DISABLED ) {
        printf ("Pan & Tilt not supported.\n");
        return false; //FLAG_NOT_SUPPORTED;
    }
    return true;
#else
    return false;
#endif
}

//
//void CWebcam::turnRight()
//{
//#ifdef USE_UVCVIDEO
//	struct v4l2_queryctrl queryctrl;
//	struct v4l2_control control;
//
//	memset (&queryctrl, 0, sizeof queryctrl);
//	memset (&control, 0, sizeof control);
//	queryctrl.id = V4L2_CID_PAN_RELATIVE;
//	if (-1 == ioctl (dev, VIDIOC_QUERYCTRL, &queryctrl))
//	{
//	        if (errno != EINVAL)
//		{
//			perror ("VIDIOC_QUERYCTRL");
//			return;
//		}
//	} else
//	{
//		control.id = V4L2_CID_PAN_RELATIVE;
//		control.value = -320;
//		if (-1 == ioctl (dev, VIDIOC_S_CTRL, &control)) {
//			perror("VIDIOC_S_CTRL");
//			return;
//        	}
//	}
//#endif
//}
//
//void CWebcam::turnLeft()
//{
//#ifdef USE_UVCVIDEO
//	struct v4l2_queryctrl queryctrl;
//	struct v4l2_control control;
//
//	memset (&queryctrl, 0, sizeof queryctrl);
//	memset (&control, 0, sizeof control);
//	queryctrl.id = V4L2_CID_PAN_RELATIVE;
//	if (-1 == ioctl (dev, VIDIOC_QUERYCTRL, &queryctrl))
//	{
//	        if (errno != EINVAL)
//		{
//			perror ("VIDIOC_QUERYCTRL");
//			return;
//		}
//	} else
//	{
//		control.id = V4L2_CID_PAN_RELATIVE;
//		control.value = 320;
//		if (-1 == ioctl (dev, VIDIOC_S_CTRL, &control)) {
//			perror("VIDIOC_S_CTRL");
//			return;
//        	}
//	}
//#endif
//}
//
//void CWebcam::turnUp()
//{
//#ifdef USE_UVCVIDEO
//	struct v4l2_queryctrl queryctrl;
//	struct v4l2_control control;
//
//	memset (&queryctrl, 0, sizeof queryctrl);
//	memset (&control, 0, sizeof control);
//	queryctrl.id = V4L2_CID_TILT_RELATIVE;
//	if (-1 == ioctl (dev, VIDIOC_QUERYCTRL, &queryctrl))
//	{
//	        if (errno != EINVAL)
//		{
//			perror ("VIDIOC_QUERYCTRL");
//			return;
//		}
//	} else
//	{
//		control.id = V4L2_CID_TILT_RELATIVE;
//		control.value = -320;
//		if (-1 == ioctl (dev, VIDIOC_S_CTRL, &control)) {
//			perror("VIDIOC_S_CTRL");
//			return;
//        	}
//	}
//#endif
//}
//
//void CWebcam::turnDown()
//{
//#ifdef USE_UVCVIDEO
//	struct v4l2_queryctrl queryctrl;
//	struct v4l2_control control;
//
//	memset (&queryctrl, 0, sizeof queryctrl);
//	memset (&control, 0, sizeof control);
//	queryctrl.id = V4L2_CID_TILT_RELATIVE;
//	if (-1 == ioctl (dev, VIDIOC_QUERYCTRL, &queryctrl))
//	{
//	        if (errno != EINVAL)
//		{
//			perror ("VIDIOC_QUERYCTRL");
//			return;
//		}
//	} else
//	{
//		control.id = V4L2_CID_TILT_RELATIVE;
//		control.value = 320;
//		if (-1 == ioctl (dev, VIDIOC_S_CTRL, &control)) {
//			perror("VIDIOC_S_CTRL");
//			return;
//        	}
//	}
//#endif
//}


int CWebcam::mjpegToJpeg(unsigned char *inFrame, unsigned char *outData, unsigned int bufSize)
{
    unsigned int j = 0, has_dht = 0;

    outData[0] = inFrame[0];
    outData[1] = inFrame[1];

    if ( (inFrame[0] != 0xff) && (inFrame[1] != 0xd8) ) {
        printf("Not a JPEG nor MJPEG file \nExiting.\n");
        return EXIT_FAILURE;
    }

    unsigned int pos = 2, size = 0; // move into the image's table

    while ( has_dht == 0 ) {
        if ( inFrame[pos] != 0xff ) {
            printf("This isn't a valid JPEG file.\n");
            return EXIT_FAILURE;
        }
        if ( inFrame[pos+1] == 0xc4 ) {
            has_dht = 1;
        }
        else if ( inFrame[pos+1] == 0xda ) { // Add the huffman tables here...
            has_dht = 0;
            break;
        }

        // Skip to the next marker
        size = (inFrame[pos+2] << 8) + inFrame[pos+3];
        for ( j = 0; j < size + 2; j++ ) {
            outData[pos + j] = inFrame[pos + j];
        }
        pos = pos + size + 2;
    }

    j = 0;

    if ( has_dht == 0 ) {
        for ( ; j < 420 ; j ++ ) {
            outData[pos + j] = arr_cJpeg[j];
        }

        for ( ; pos < bufSize ; pos ++ ) {
            outData[pos + 420] = inFrame[pos];
        }
    }
    else {
        for ( ; pos < bufSize ; pos ++ ) {
            outData[pos] = inFrame[pos];
        }
    }
    m_bClear = false;
    return EXIT_SUCCESS;
}

void CWebcam::yuvToJpeg(unsigned char *inFrame, int width, int height)
{
    const int size = width*height;
    int y, u, v, y2, u2, v2, r, g, b,pos;
    int i = 2;
    int j = 4;
    int w = 1, h = 0;

    y = inFrame[0];
    u = inFrame[1];
    y2 = inFrame[2];
    v = inFrame[3];
    unsigned int value;
    unsigned char *Data;
    Data = m_imageCaptured.bits();
    YUV2RGB(y, u, v,value);
    //outFrame->setPixel(w, h, qRgb(r, g, b));  //Data[h*width+w]=qRgb(r, g, b);
    pos = (h * width + w) * 4;
    memcpy(&Data[pos], &value, 4);
//                Data[pos]=value & 255;
//                Data[pos+1]=value >>8;
//                Data[pos+2]=value >>16;
//                Data[pos+3]=value >>24;
    int n = size / 2;
    while ( i <= n ) {
        u2 = inFrame[j + 1];
        v2 = inFrame[j + 3];
        YUV2RGB(y2, MEAN(u, u2), MEAN(v, v2), value);
        if ( w == width ) {
            w = 0;
            h++;
        }
        //outFrame->setPixel(w, h, qRgb(r, g, b));
        pos = (h * width + w) * 4;
        memcpy(&Data[pos], &value, 4);
        w ++;

        y  = inFrame[j + 0];
        y2 = inFrame[j + 2];
        u = u2;
        v = v2;

        YUV2RGB(y, u, v,value);

        if ( w == width ) {
            w = 0;
            h ++;
        }
        //outFrame->setPixel(w, h, qRgb(r, g, b));
        pos = (h * width + w) * 4;
        memcpy(&Data[pos], &value, 4);

        w ++;

        i ++;
        j += 4;
    }
    m_bClear = false;

    update();
}

void CWebcam::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);
    m.lock();
    m_painter.begin(this);
    m_painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //m_painter.setCompositionMode(QPainter::CompositionMode_Source);
    m_painter.drawImage(QPoint(0, 0), m_imageCaptured);
    if ( m_bClear ) {
        m_painter.drawText(QPoint(100,100),"Please Wait...");
        m_painter.drawText(QPoint(90,120),"Initializing Camera");
    }
    m_painter.end();
    m.unlock();
}

void CWebcam::kError(char* error, int errorno)
{
    Q_UNUSED(errorno);
    printf(error);
}
