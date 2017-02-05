/**
 * \file "cfingerprint.h"
 * \brief it provides an fingerprint interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to access Fingerprint module to perform various operations like
 * enroll,capture,verify fingerprint,..,etc.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CFINGERPRINT_H
#define CFINGERPRINT_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QObject>
#include <QImage>
#include <QByteArray>

namespace ClanCor
{
    /**
     * \class CFingerPrint
     * \brief The CFingerPrint class provides an interface for fingerprint in the  ClanCor HHC80xx Device.
     *
     * This class is used to perform the various finger print operations.
     * Fingerprint template will be in PTAPI format (one of the standard used in Finger print scanning).
     */
    class CFingerPrint: public QObject
    {
        Q_OBJECT
    public:
        /**
         * \fn CFingerPrint()
         * A constructor.
         * \brief creates a fingerprint object for allocate the resources.
         */
        CFingerPrint();

        /**
         * \fn ~CFingerPrint()
         * A destructor.
         * \brief Destroys the fingerprint object and frees any allocated resources.
         */
        ~CFingerPrint();

        /**
         * \fn bool setTimeout(int nTimeout_mSecs) const
         * \brief This function is used to set timeout value for Bio-Metric coprocessor device.
         * \param[in] nTimeout_mSecs used to pass integer timeout value in milli seconds. Default value is 60000 milliseconds (60 seconds)
         * pass value -2 (minus two) to set unlimited timeout.
         */
        void setTimeout(int nTimeout_mSecs = 60000) const;

        /**
         * \fn bool getFingerImage(QImage &r_imageFinger)
         * \brief This function is used to capture fingerprint image from the device.
         * \param[out] r_imageFinger used to get the captured fingerprint image.
         * \return It returns true, if fingerprint image is captured successfully; otherwise returns false.
         */
        bool getFingerImage(QImage &r_imageFinger) const;

        /**
         * \fn  enrollFinger(QByteArray &r_byteArrayTemplate)
         * \brief This function is used to scan the finger data and process it into a Fingerprint Template.
         * It will scan up to five times minimum to collect templates; based on the scanned templates quality it may collect few more templates.
         * Enrollment template will be constructed from a subset of collected templates. Same finger has to be used for all acquisitions.
         * \param[out] r_byteArrayTemplate used to get the captured fingerprint image.
         * \return It returns true, if enrolled successfully; otherwise returns false.
         */
        bool enrollFinger(QByteArray &r_byteArrayTemplate) const;

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
        bool enrollFinger(QByteArray &r_byteArrayTemplate,QImage &r_imageFinger) const;

        /**
         * \fn captureFinger(QByteArray &r_byteArrayTemplate)
         * \brief This function is used to capture the fingerprint template data for Verification.
         * Template data will be constructed from a single scan.
         * \param[out] r_byteArrayTemplate used to get the enrolled template.
         * \return It returns true, if template captured successfully; otherwise returns false.
         */
        bool captureFinger(QByteArray &r_byteArrayTemplate) const;

        /**
         * \fn bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE,bool &r_bMatch)
         * \brief This function is used to verify the template data with the live finger data scanned by the device.
         * \param[in] r_const_byteArrayTEMPLATE used for pass the template data.
         * \param[out] r_bMatch used to get the compare result of given template with live finger.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE,bool &r_bMatch) const;

        /**
         * \fn bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1,const QByteArray &r_const_byteArrayTEMPLATE2,bool &r_bMatch)
         * \brief This is an overloaded function.
         * This function is used to compare two templates data one against another.
         * \param[in] r_const_byteArrayTEMPLATE1 used for pass the template data.
         * \param[in] r_const_byteArrayTEMPLATE2 used for pass the template data to compare with first template.
         * \param[out] r_bMatch used to get the compare result of two template data.
         * \return It returns true, if the process completed successfully; otherwise returns false.
         */
        bool verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1,const QByteArray &r_const_byteArrayTEMPLATE2,bool &r_bMatch) const;

    };
}
#endif // CFINGERPRINT_H
