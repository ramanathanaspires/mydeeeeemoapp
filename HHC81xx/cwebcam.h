/**
 * \file "cwebcam.h"
 * \brief it provides the web camera interface and show the preview.
 *
 * This file is used to capture the photo from webcamera.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CWEBCAM_H
#define CWEBCAM_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QWidget>
#include <QImage>
#include <QSocketNotifier>
#include <QMutex>
#include <QPainter>
#include <linux/videodev2.h>

namespace ClanCor
{
    /**
     * \class CWebcam
     * \brief The CWebcam class is used to access the webcamera and update the preview.
     */
    class CWebcam : public QWidget
    {
        Q_OBJECT
/*****************************************************************************
                                PUBLIC
******************************************************************************/
    public:

        /**
         * This enum type is used to control of the camera.
         */
        enum Control {Saturation = 0,
                      PowerLineFreq,
                      Brightness,
                      Contrast,
                      Sharpness,
                      PanTiltReset};

        /**
         * \fn CWebcam()
         * A constructor.
         * \brief initialize the object for preview.
         */
        CWebcam();

        /**
         * \fn QImage captured() const
         * \brief This function is used to get the captured frame.
         * \return it return the captured photo image.
         */
        QImage captured() const { return m_imageCaptured; }

        /**
         * \fn void setPause(bool bState)
         * \brief This function is used to pass the updating in display.
         */
        void setPause(bool bState) { m_bPause = bState; }

        /**
         * \fn int  open(const char *devFile)
         * \brief This function is used to open the webcamera and allocate the allocated resources.
         * \return It return 0 if webcamera opened and initialized successfully. otherwise failure.
         */
        int  open(const char *devFile);

        /**
         * \fn void close()
         * \brief This function is used to close the device and delete the allocated resources.
         */
        void close();

        /**
         * \fn void clear()
         * \brief This function is used to clear the window & fill with white color.
         */
        void clear();

        QList<int>   getFormatList(QList<QString> &description) const;
        QList<QSize> getSizesList() const;

        /**
         * \fn int setFormat(unsigned int width, unsigned int height, int pixelformat = V4L2_PIX_FMT_MJPEG)
         * \brief This function is used to set the format by width, height and pixel format.
         * \arg[in] width used to set the width of image.
         * \arg[in] height used to set the height of image.
         * \arg[in] pixelformat used to set the pixel format.
         * \return It returns 0, if the format set successfully; otherwise false.
         */
        int setFormat(unsigned int width, unsigned int height, int pixelformat = V4L2_PIX_FMT_MJPEG);

        /**
         * \fn int streamOff()
         * \brief This function is used off the stream.
         * \return It returns 0, if executed successfully; otherwise false.
         */
        int streamOff();

        /**
         * \fn int stopStreaming()
         * \brief This function is used to stop the streaming.
         * \return It returns 0, if executed successfully; otherwise false.
         */
        int stopStreaming();

        /**
         * \fn int currentWidth() const
         * \brief This function is used to get the image width.
         * \return It returns the image width.
         */
        int currentWidth() const;

        /**
         * \fn int currentHeight() const
         * \brief This function is used to get the image height.
         * \return It returns the image height.
         */
        int currentHeight() const;

        /**
         * \fn int currentPixelFormat() const
         * \brief This function is used to get the pixel format.
         * \return It returns the current pixel format.
         */
        int currentPixelFormat() const;

        /**
         * \fn int changeCtrl(int ctrl, int value = 0)
         * \brief This function is used to change the control value.
         * \arg[in] ctrl used to set the control.
         * \arg[in] value used to set the value of the control.
         * \return It returns 0, if executed successfully; otherwise false.
         */
        int changeCtrl(int ctrl, int value = 0);

        /**
         * \fn int defaultCtrlVal(unsigned int control, int &defaultValue)
         * \brief This function is used to get the default control value of the webcamera.
         * \arg[in] ctrl used to set the control.
         * \arg[out] defaultValue used to get the default value of the given control.
         * \return It returns 0, if executed successfully; otherwise false.
         */
        int defaultCtrlVal(unsigned int control, int &defaultValue);

        /**
         * \fn bool isStreaming() const
         * \brief This function is used to check webcamera is streaming or not.
         * \return It returns true, if webcamera is streaming; otherwise return false.
         */
        bool isStreaming() const {return m_bStreaming;}

        /**
         * \fn bool isOpened() const
         * \brief This function is used to check webcamera is opened or not.
         * \return It returns true, if webcamera is opened; otherwise return false.
         */
        bool isOpened() const {return m_bOpened;}

        /**
         * \fn bool panTiltSupported() const
         * \brief This function is used to check patill is supported or not.
         * \return It returns true, if patill is supported; otherwise return false.
         */
        bool panTiltSupported();

        /**
         * \fn int startStreaming()
         * \brief This function is used to start the streaming.
         * \return It returns 0, if streaming started successfully; otherwise false.
         */
        int startStreaming();

    public slots:
//        void turnRight();
//        void turnLeft();
//        void turnUp();
//        void turnDown();

    signals:    /** Signals */
        /*\@{*/

        /**
         * \fn void ready()
         * \brief This signal is emitted when received the first frame from webcamera.
         */
        void ready();

        /**
         * \fn void disconnected()
         * \brief This signal is emitted when webcamera is disconnected.
         */
        void disconnected();

        /*\@}*/


    private:
        int dev;
        v4l2_format *fmt;
        v4l2_buffer *buf;
        v4l2_requestbuffers *rb;
        uchar *mem[2];
        size_t bufLength;
        QPainter m_painter;
        QSocketNotifier *socketNotifierImage;
        QMutex m;
        bool m_bReady;
        bool m_bPause;
        bool m_bClear;
        bool m_bStreaming;
        bool m_bOpened;
        bool m_bMaped;
        bool m_bAllocated;
        QImage m_imageCaptured;

        /**
         * \fn  virtual void paintEvent(QPaintEvent *paintEvent)
         * \brief This function is used to repaint the captured photo.
         * \arg[in] paintEvent used draw the image in widget
         */
        virtual void paintEvent(QPaintEvent *paintEvent);

        /**
         * \fn int mjpegToJpeg(unsigned char *inFrame, unsigned char *outFrame, unsigned int bufSize)
         * \brief This function is used to convert mjpeg data to jpeg data.
         * \arg[in] inFrame used to set the mjpeg data.
         * \arg[out] outFrame used to get the converted jpeg data.
         * \arg[in] bufSize used to set the buffer size of data.
         */
        int mjpegToJpeg(unsigned char *inFrame, unsigned char *outFrame, unsigned int bufSize);

        /**
         * \fn void yuvToJpeg(unsigned char *inFrame, int width, int height)
         * \brief This function is used to convert yuv data to image data.
         * \arg[in] inFrame used to set the yuv data.
         * \arg[in] width used to set the width.
         * \arg[in] height used to set the height.
         */
        void yuvToJpeg(unsigned char *inFrame, int width, int height);

        /**
         * \fn void kError(char* error, int errorno)
         * \brief This function is used to print the error information.
         * \arg[in] error used to set the error string.
         * \arg[in] errorno used to set error number.
         */
        void kError(char* error, int errorno);

    private slots:
        /**
         * \fn void getFrame()
         * \brief This function is used to read the data from buffer.
         */
        void getFrame();

    };
}
#endif
