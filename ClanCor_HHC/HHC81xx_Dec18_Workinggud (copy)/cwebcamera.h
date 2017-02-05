/**
 * \file "cwebcamera.h"
 * \brief it provides the camera interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to capture the photo from webcamera.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CWEBCAMERA_H
#define CWEBCAMERA_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QTimer>

namespace ClanCor
{
    /**
     * \class CWebCamera
     * \brief The CWebCamera class is used to access the webcamera from the application.
     */
    class CWebCamera:public QObject
    {
         Q_OBJECT
/*****************************************************************************
                                PUBLIC
******************************************************************************/
    public:
        /**
         * \fn CWebCamera()
         * A constructor.
         * \brief Creates & allocates the resources of camera object.
         */
        CWebCamera();

        /**
         * \fn ~CWebCamera()
         * A destructor.
         * \brief Destroys the camera object and frees any allocated resources.
         */
        ~CWebCamera();

        /**
         * This function is used to show the camera dialog for capture the image.
         * It initializes the device and displays the live preview window with capture & cancel buttons.
         * camera dialog will be shown only if the webcamera is found.
         * \param[out] r_imageCaptured used to get the capture image.
         * \return It returns true, if image captured successfully; otherwise returns false.
         */
        bool previewCamera(QImage &r_imageCaptured);

    private:

        /**
         * \var QTimer m_timerFoundCamera
         * \brief used to check the camera is found.
         */
        QTimer m_timerFoundCamera;
        /**
         * \var QTimer m_timerClose
         * \brief used to process for close dialog in 60 seconds if not used.
         */
        QTimer m_timerClose;
        /**
         * \var QString m_strDeviceName
         * \brief used to set the camera device name.
         */
        QString m_strDeviceName;
        /**
         * \var QDialog *m_dialogCamera
         * \brief used to display the camera dialog for capture the photo.
         */
        QDialog *m_dialogCamera;
        /**
         * \var QLabel *m_labelStatus
         * \brief used to display the information when loading or error when occured.
         */
        QLabel *m_labelStatus;
        /**
         * \var QPushButton *m_pushButtonCapture
         * \brief used to press user to capture the photo.
         */
        QPushButton *m_pushButtonCapture;
        /**
         * \var QPushButton *m_pushButtonCapture
         * \brief used to press user to cancel preview.
         */
        QPushButton *m_pushButtonCancel;
        /**
         * \var bool m_bSavedImage
         * \brief used to store photo is captured or not.
         */
        bool m_bSavedImage;
        /**
         * \var bool m_bFoundCamera
         * \brief used to store camera is found or not.
         */
        bool m_bFoundCamera;

    private slots:
        /**
         * \fn void initVolumeDetails()
         * \brief This function is used to intimate close the camera dialog.
         */
        void on_timerClose_timeout();

        /**
         * \fn void getDeviceCapabilities()
         * \brief This function is used to get the device capablities for initialize it.
         */
        void getDeviceCapabilities();

        /**
         * \fn void startStopVideo()
         * \brief This function is used to stop/start the stream.
         * stop the stream if already streaming else start the stream.
         */
        void startStopVideo();

        /**
         * \fn void on_pushButtonCapture_clicked()
         * \brief This function is used to capture the current stream if streaming otherwise close the dialog.
         */
        void on_pushButtonCapture_clicked();

        /**
         * \fn void on_pushButtonCancel_clicked()
         * \brief This function is used to cancel the captured frame or exit the dialog.
         */
        void on_pushButtonCancel_clicked();

        /**
         * \fn void started()
         * \brief This function is used to enable button when streaming is started.
         */
        void started();

        /**
         * \fn void deviceDisconnected()
         * \brief This function is used to show error when device is disconnected.
         */
        void deviceDisconnected();

    };
}
#endif // CWEBCAMERA_H
