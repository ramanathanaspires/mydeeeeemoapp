#ifndef CFP_MORPHO_H
#define CFP_MORPHO_H

#include <QObject>

#include <cFP_API_Morpho.h>
using namespace func_members;

namespace ClanCor
{
    /**
     * \class CFP_Morpho
     * \brief The CFP_Morpho class provides an interface for sagem MSO morpho optic fingerprint integrated inside ClanCor HHC7/8xxx Device.
     * It can support various fingerprint template type.
     * This class is used to perform the various finger print operations.
     */
    class CFP_Morpho : public QObject
    {
        Q_OBJECT
    public:
        /**
         * The enum describes the fingerprint standard
         */
        enum E_FPTemplateType
        {
            e_FPTemplate_SAGEM_PKCOMP             = 0,     /**< Sagem PKCOMP (Recommanded minutiae) */
            e_FPTemplate_SAGEM_PKMAT              = 1,     /**< Sagem PKMAT (minutiae) */
            e_FPTemplate_SAGEM_PKCOMP_NORM        = 2,     /**< Sagem PKCOMP Normal */
            e_FPTemplate_SAGEM_PKMAT_NORM         = 3,     /**< Sagem PKMAT Normal */
            e_FPTemplate_ISO_PK_DATA_ANSI_378     = 4,     /**< ISO ANSI INCITS 378 */
            e_FPTemplate_ISO_PK_DATA_ISO_FMR      = 5,     /**< ISO PK_DATA_ISO_FMR */
            e_FPTemplate_ISO_PK_DATA_ISO_FMC_CS   = 6,     /**< ISO 19794-2, FMC Compact Size*/
            e_FPTemplate_ISO_PK_DATA_ISO_FMC_NS   = 7,     /**< ISO 19794-2, FMC Normal Size*/
            e_FPTemplate_ISO_PK_DATA_MINEX_A      = 8,     /**< MINEX A*/
        };

        explicit CFP_Morpho(QObject *parent = 0);
        ~CFP_Morpho();

        /**
         * \fn bool setTimeout(int nTimeout_mSecs)
         * \brief This function is used to set timeout value for Bio-Metric coprocessor device.
         * \param[in] nTimeout_mSecs used to pass integer timeout value in milli seconds. Default value is 60000 milliseconds (60 seconds)
         * pass value 0 (zero) to set unlimited timeout.
         */
        void setTimeout(unsigned short nTimeout_mSecs = 0);
        /**
         * \fn void setFPTemplateType(E_FPTemplateType e_FPTemplateType = e_FPTemplate_SAGEM_PKCOMP )
         * \brief This function is used to set finger print template type to be used in Sagem MSO Morpho fingerprint coprocessor device.
         * \param[in] e_FPTemplateType used to pass template type to be used as enum value. By default SAGEM_PKCOMP template type will be used.
         *
         * \sa see also E_FPTemplateType.
         */
        void setFPTemplateType(E_FPTemplateType e_FPTemplateType = e_FPTemplate_SAGEM_PKCOMP );
        /**
         * \fn bool EnrollFinger(QByteArray &r_BAryFP_PK, QImage &r_Image_FP)
         * \brief This function is used get scanned fingerprint template & finger image (bmp format). It will scan the finger data and process it into a
         * fingerprint template based on selected template type.
         * It will scan a finger up to three times minimum to collect templates; Enrollment template will be constructed from a subset of collected templates
         * The collected fingerprint template & finger image will be stored in variables pass as reference arguments.
         * \param[out] r_BAryFP_PK used to store collected fingerprint template.
         * \param[out] r_Image_FP used to store collected fingerprint image.
         * \return It returns true, if enroll operation was successfull without any error; otherwise returns false.
         *
         */
        bool EnrollFinger(QByteArray &r_BAryFP_PK, QImage &r_Image_FP);
        /**
         * \fn bool Capture(QByteArray &r_BAryFP_PK = NULL, QImage &r_Image_FP = NULL)
         * \brief This function is used capture fingerprint template & finger image( bmp format). It will scan the finger data and process it into a
         * fingerprint template based on selected template type.
         * It will scan a finger only once to collect finger print template & image;
         * The collected fingerprint template & finger image will be stored in variables pass as reference arguments.
         * \param[out] r_BAryFP_PK used to store collected fingerprint template.
         * \param[out] r_Image_FP used to store collected fingerprint image.
         * \return It returns true, if capture operation was successfull without any error; otherwise returns false.
         *
         */
        bool Capture(QByteArray &r_BAryFP_PK, QImage &r_Image_FP);
        /**
         * \fn bool VerifyFinger(QByteArray &r_BAryPK_Ref, bool &r_bResult)
         * \brief This function is used verify fingerprint template passed as argument
         * with live fingerprint template scanned through sensor.
         * \param[in] r_BAryPK_Ref used to pass as reference variable stored with fingerprint template to be verified.
         * \param[out] r_bResult used to store the verify result, true if fingerprint template matches with live finger; Otherwise false.
         * \return It returns true, if verify operation was successfull without any error; otherwise returns false.
         *
         * \note Note - Ensure fingerprint template type of passed template is same as currently selected template type ( using setFPTemplateType() API ).
         */
        bool VerifyFinger(QByteArray &r_BAryPK_Ref, bool &r_bResult);

        /**
         * \fn bool Verify_Match(QByteArray &r_BAryPK_Src, QByteArray &r_BAryPK_Ref, bool &r_bResult)
         * \brief This function is used verify match for the source & reference fingerprint templates passed as arguments.
         * \param[in] r_BAryPK_Src used to pass as reference variable stored with source fingerprint template.
         * \param[in] r_BAryPK_Ref used to pass as reference variable stored with reference fingerprint template.
         * \param[out] r_bResult used to store the verify match result, true if source & reference fingerprint templates matches successfully; Otherwise false.
         * \return It returns true, if verified match operation was successfull without any error; otherwise returns false.
         *
         * \note Note - Ensure fingerprint template type of passed templates is same as currently selected template type ( using setFPTemplateType() API ).
         */
        bool Verify_Match(QByteArray &r_BAryPK_Src, QByteArray &r_BAryPK_Ref, bool &r_bResult);
        /**
         * \fn bool IdentifyFinger(QList<QByteArray> &listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index)
         * \brief This function is used identify matched fingerprint template with live finger, from the passed list of fingerprint templates.
         * \param[in] listBAry_PK_Ref used to pass as reference variable stored with list of fingerprint templates.
         * \param[out] r_bResult used to store the identify match result, true if a fingerprint template from the list matches with live finger; Otherwise false.
         * \param[out] r_nmatch_index used to store matched index value of fingerprint template from list.
         * \return It returns true, if identify operation was successfull without any error; otherwise returns false.
         *
         * \note Note - Ensure fingerprint template type of passed templates is same as currently selected template type ( using setFPTemplateType() API ).
         */
        bool IdentifyFinger(QList<QByteArray> &listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index);
        /**
         * \fn bool Identify_Match(QByteArray &r_BAryPK_Src, QList<QByteArray> &r_listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index)
         * \brief This function is used identify matched fingerprint template with the source template passed as reference, from the passed list of fingerprint templates.
         * \param[in] r_BAryPK_Src used to pass as reference variable stored with source fingerprint template.
         * \param[in] r_listBAry_PK_Ref used to pass as reference variable stored with list of fingerprint templates.
         * \param[out] r_bResult used to store the identify match result, true if a fingerprint template from the list matches with live finger; Otherwise false.
         * \param[out] r_nmatch_index used to store matched index value of fingerprint template from list.
         * \return It returns true, if identify operation was successfull without any error; otherwise returns false.
         *
         * \note Note - Ensure fingerprint template type of passed templates is same as currently selected template type ( using setFPTemplateType() API ).
         */
        bool Identify_Match(QByteArray &r_BAryPK_Src, QList<QByteArray> &r_listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index);

        /**
         * \fn bool isError()
         * \brief This function is used to get error status if occured during initialization process of finger print.
         * \return Returns true if error occured in last finger print operation.
         */
        bool isError() { return m_bIsError; }

        /**
         * \fn QString getLastErrorString()
         * \brief This function is used to get the error information about the last error (if any) that occurred with this class function.
         * if any function of this class returns false, use this function to get the error information.
         * \return It returns the last error information.
         */
        QString getLastErrorString() const { return strFPlastError; }

    signals:

    public slots:

    private:
        /**
         * \var bool m_bIsError
         * \brief used to store the last error status.
         */
        bool m_bIsError;
        /**
         * \var bool m_bIsError
         * \brief used to store the status of called API.
         */
        bool m_bReturn;
        /**
         * \var bool l_us_Timeout
         * \brief used to set store timeout value.
         */
        US l_us_Timeout;
        /**
         * \var bool l_us_Timeout
         * \brief used to set store asynchronous event value.
         */
        UL l_ul_AsynchronousEvnt;
        /**
         * \var bool l_us_Timeout
         * \brief used to set store number of fingers to be used with each fingerprint operation.
         */
        int No_of_finger;
        /**
         * \var bool l_us_Timeout
         * \brief used to set store fingerprint template type.
         */
        unsigned char m_PK_Type;
    };
}

#endif // CFP_MORPHO_H
