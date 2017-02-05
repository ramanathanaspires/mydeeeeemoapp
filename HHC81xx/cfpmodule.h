/**
 * \file "cfpmodule.h"
 * \brief it provides an fingerprint interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to access Fingerprint module to perform various operations like
 * enroll,capture,verify fingerprint,..,etc.
 *
 * For more details about fingerprint tfm library you can refer "PTAPI Standard Functions.pdf" document.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CFPMODULE_H
#define CFPMODULE_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QImage>
#include <QByteArray>
#include <QDialog>
#include <QPushButton>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tfmerror.h"

#define ANSI_ISO_SPECIFICATION_IMAGE_VERSION  0x30313000
#define CBEFF_ID_UPEK  0x12

extern "C"
{
    #include "tfmapi.h"
}

namespace ClanCor
{
    /**
     * \class CFpModule
     * \brief The CFpModule class provides an interface for UPEK fingerprint in the  ClanCor HHC80xx Device.
     *
     * This class is used to perform the various finger print operations.
     * Fingerprint template will be in PTAPI format (one of the standard used in Finger print scanning).
     */
    class CFpModule: public QObject
    {
        Q_OBJECT

    public:
        /**
         * \fn CFpModule()
         * A constructor.
         * \brief creates a fingerprint object for allocate the resources.
         */
        CFpModule();

        /**
         * \fn ~CFpModule()
         * A destructor.
         * \brief Destroys the fingerprint object and frees any allocated resources.
         */
        ~CFpModule();

        /**
         * \fn bool getFingerImage(QImage &r_imageFinger)
         * \brief This function is used to capture fingerprint image from the device.
         * \param[out] r_imageFinger used to get the captured fingerprint image.
         * \return It returns true, if fingerprint image is captured successfully; otherwise returns false.
         */
        bool getFingerImage(QImage &r_imageFinger);

        /**
         * \fn bool enrollFinger(QByteArray &r_byteArrayTemplate)
         * \brief This function is used to scan the finger data and process it into a Fingerprint Template.
         * It will scan up to five times minimum to collect templates; based on the scanned templates quality it may collect few more templates.
         * Enrollment template will be constructed from a subset of collected templates. Same finger has to be used for all acquisitions.
         * \param[out] r_byteArrayTemplate used to get the captured fingerprint image.
         * \return It returns true, if enrolled successfully; otherwise returns false.
         */
        bool enrollFinger(QByteArray &r_byteArrayTemplate);


        /**
         * \fn bool enrollFinger(QByteArray &r_byteArrayTemplate,QImage &r_imageFinger)
         * \brief This is an overloaded function.
         * This function is used to scan the finger data & image and process it into a Fingerprint Template.
         * It will scan up to five times minimum to collect templates; based on the scanned templates quality it may collect few more templates.
         * Enrollment template will be constructed from a subset of collected templates. Same finger has to be used for all acquisitions.
         * \param[out] r_byteArrayTemplate used to get the enrolled template.
         * \param[out] r_imageFinger used to get the captured fingerprint image.
         * \return It returns true, if enrolled successfully; otherwise returns false.
         */
        bool enrollFinger(QByteArray &r_byteArrayTemplate,QImage &r_imageFinger);

        /**
         * \fn bool captureFinger(QByteArray &r_byteArrayTemplate)
         * \brief This function is used to capture the fingerprint template data for Verification.
         * Template data will be constructed from a single scan.
         * \param[out] r_byteArrayTemplate used to get the enrolled template.
         * \return It returns true, if template captured successfully; otherwise returns false.
         */
        bool captureFinger(QByteArray &r_byteArrayTemplate);

        /**
         * \fn bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE,bool &r_bMatch)
         * \brief This function is used to verify the template data with the live finger data scanned by the device.
         * \param[in] r_const_byteArrayTEMPLATE used for pass the template data.
         * \param[out] r_bMatch used to get the compare result of given template with live finger.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE,bool &r_bMatch);

        /**
         * \fn bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1,const QByteArray &r_const_byteArrayTEMPLATE2,bool &r_bMatch)
         * \brief This is an overloaded function.
         * This function is used to compare two templates data one against another.
         * \param[in] r_const_byteArrayTEMPLATE1 used for pass the template data.
         * \param[in] r_const_byteArrayTEMPLATE2 used for pass the template data to compare with first template.
         * \param[out] r_bMatch used to get the compare result of two template data.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1,const QByteArray &r_const_byteArrayTEMPLATE2,bool &r_bMatch);

    private:

        /**
         * \struct SBMPHeader
         * \brief The SBMPHeader structure provides an interface for bitmap header.
         */
        struct SBMPHeader{
          int m_nSize;
          int m_nReserved;
          int m_nOffset;
          int m_nheader_sz;
          int m_nWidth;
          int m_nHeight;
          short m_nplanes;
          short m_nBitspp;
          int m_ncompress_type;
          int m_nBmp_bytesz;
          int m_nHres;
          int m_nVres;
          int m_ncolors;
          int nimpcolors;
        } ;

        /**
         * \var PT_STATUS m_PStatus
         * \brief used to store the result of the fingerprint command.
         */
        PT_STATUS m_PStatus;
        /**
         * \var QDialog *m_dialogFingerPrint
         * \brief used to display the fingerprint dialog for showing the status when enrollment.
         */
        QDialog *m_dialogFingerPrint;
        /**
         * \var QPushButton *m_pushButtonCancel
         * \brief used for display the cancel operation in fingerprint dialog.
         */
        QPushButton *m_pushButtonCancel;

        /**
         * \fn bool init(bool bShowDialog = true)
         * \brief This function is used initialize the fingerprint library & open the device.
         * \arg[in] bShowDialog used to set false for not show the fingerprint dialog. default value is true.
         * \return It returns true, if the fingerprint device opened successfully; otherwise returns false.
         */
        bool init(bool bShowDialog = true);

        /**
         * \fn bool terminate()
         * \brief This function is used terminate the fingerprint device and close the fingerprint dialog.
         * \return It returns true, if the fingerprint device opened successfully; otherwise returns false.
         */
        bool terminate();

        /**
         * \fn bool enroll(QByteArray &r_byteArrayTemplate)
         * \brief This function is used to scan the live finger data several times and process it into a Fingerprint Template.
         * \param[out] r_byteArrayTemplate used to get the captured fingerprint image.
         * \return It returns true, if enrolled successfully; otherwise returns false.
         */
        bool enroll(QByteArray &r_byteArrayTemplate);

        /**
         * \fn QString reverse(const QString &r_const_strDATA)
         * \brief This function is used to reverse the hex string by big endian format.
         * \param[in] r_const_strDATA used to set the hex string which to be reversed.
         * \return It returns the reversed Bigendian string.
         */
        QString reverse(const QString &r_const_strDATA);

        /**
         * \fn bool createTemplate(const QByteArray &r_const_byteArrayTEMPLATE,PT_INPUT_BIR ** ppAdaptedTemplate)
         * \brief This function is used to convert bytearray data into PT input bir template.
         * \param[in] r_const_byteArrayTEMPLATE used to set the fingerprint template data in bytearray .
         * \param[out] ppAdaptedTemplate used to get the converted input bir template.
         * \return It returns true, if template created successfully; otherwise return false.
         */
        bool createTemplate(const QByteArray &r_const_byteArrayTEMPLATE,PT_INPUT_BIR ** ppAdaptedTemplate);

        /**
         * \fn int absSampleToAnsiIso(const PT_DATA *pImage,PT_BYTE *pOutputImage, PT_DWORD *pLenOutput )
         * \brief This function is used to convert grabbed image into Ansii/ISO format data.
         * \param[in] pImage used to set the grabbed image .
         * \param[out] pOutputImage used to get the converted ISO data.
         * \param[in] pLenOutput used to set the image data length.
         * \return It returns true, if successfully converted to ISO format data ; otherwise return false.
         */
        int absSampleToAnsiIso(const PT_DATA *pImage,PT_BYTE *pOutputImage, PT_DWORD *pLenOutput );

        /**
         * \fn void putUintBigEndian( PT_BYTE **ppData, PT_DWORD value, PT_DWORD cntBytes )
         * \brief This function is used for writing unsigned values in big endian format.
         * \param[out] ppData used to set & get the changed big endian data.
         * \param[in] value used to set the mask value.
         * \param[in] cntBytes used to set the no of bytes.
         */
        void putUintBigEndian( PT_BYTE **ppData, PT_DWORD value, PT_DWORD cntBytes );

        /**
         * \fn void putUintBigEndian( PT_BYTE **ppData, PT_DWORD value, PT_DWORD cntBytes )
         * \brief This function is used to conver the grabbed image into QImage.
         * \param[in] pImage used to set the grabbed Image.
         * \param[out] r_imageFinger used to get the image in QImage.
         */
        void drawImage(PT_DATA * pImage,QImage &r_imageFinger);

    private slots:
        /**
         * \fn void on_pushButtonCancel_clicked()
         * \brief This function is used to intimate cancel fingerprint operation.
         */
        void on_pushButtonCancel_clicked();

    };
}
#endif // CFPMODULE_H
