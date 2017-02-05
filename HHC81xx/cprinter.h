/**
 * \file "cprinter.h"
 * \brief it provides an printer interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to format the data to ClanCor HHC80xx printer.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CPRINTER_H
#define CPRINTER_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QObject>
const QString const_StringNativeData_EOP                    = "^N";
const QString const_StringEndOfPrint                        = "^E";

namespace ClanCor
{
    /**
     * \class CPrinter
     * \brief The CPrinter class provides an interface for printing in the  ClanCor HHC80xx Device.
     *
     *  This class is used to construct the printing data and image.
     */
    class CPrinter: public QObject
    {
    /*****************************************************************************
                                    PUBLIC
    ******************************************************************************/
    public:

        /**
         * This enum type is used to specify the printing font size.
         */
        enum E_FontSize
        {
            eFontSize_SMALL = 1, /**< Small Font */
            eFontSize_MEDIUM = 2, /**< Medium Font */
            eFontSize_BIG = 3 /**< Big Font */
        };

        /**
         * This enum type is used to specify the printing font style.
         */
        enum E_FontStyle
        {
            eFontStyle_REGULAR = 1, /**< unstyled text. */
            eFontStyle_BOLD = 2, /**< boldness the text. */
            eFontStyle_ITALIC = 3, /**< representing italicized text. */
            eFontStyle_BOLDITALIC = 4 /**< combine with bold and italic text. */
        };

        /**
         * This enum type is used to specify the alignment of printing data.
         */
        enum E_Alignment
        {
            eAlignment_LEFT = 1, /**< Aligns with the left. */
            eAlignment_CENTER = 2, /**< Align with center. */
            eAlignment_RIGHT = 3 /**< Aligns with the right. */
        };

        /**
         * This enum type is used to specify the native language to be used.
         */
        enum E_NativeLanguage
        {
            e_NativeLanguage_NONE = 0,      /**< used to deselect the native language*/
            e_NativeLanguage_TAMIL = 1,     /**< used to set Tamil*/
            e_NativeLanguage_MALAYALAM = 2, /**< used to set Malayalam*/
            e_NativeLanguage_KANNADA = 3,   /**< used to set Kannada*/
            e_NativeLanguage_TELUGU = 4,    /**< used to set Telugu*/
            e_NativeLanguage_HINDI = 5,     /**< used to set hindi*/
            e_NativeLanguage_BENGALI = 6,   /**< used to set Bengali*/
            e_NativeLanguage_SINGALAM = 7   /**< used to set Singalam*/
        };
        /**
             * The enum describes theoptions to E_ImageBrightness.
             */
        enum E_ImageBrightness
        {
            eImagePrintLow   = 0,  /**< used to print image with low brihtness */
            eImagePrintHigh  = 1  /**< used to print image with high brightness */
        };
        /**
         * \fn CPrinter()
         * A constructor.
         * \brief Creates a new printer object for send data to printer.
         */
        CPrinter();

        /**
         * \fn ~CPrinter()
         * A destructor.
         * \brief Destroys the printer object and frees any allocated resources.
         */
        ~CPrinter();

        /**
         * \fn void setNativeLanguage(E_NativeLanguage e_NativeLanguage)
         * This function is used to set native language to be used to print.
         * \warning Ensure your ClanCor HHC80/70xx device having support for the selected native language.
         * \param[in] e_NativeLanguage used to pass the language to be selected.
         */
        void setNativeLanguage(E_NativeLanguage e_NativeLanguage);

        /**
         * \fn void paperFeed(int n_MM)
         * This function is used to feed the paper without print.
         * \param[in] n_MM used to set the paperfeed in millimeter.
         */
        void paperFeed(int n_MM);

        /**
         * \fn void addData(const QString &r_const_strDATA,
         *                  E_FontSize eFontSize = eFontSize_MEDIUM,
         *                  E_FontStyle eFontStyle = eFontStyle_REGULAR,
         *                  E_Alignment eAlign = eAlignment_LEFT,
         *                  bool bUnderLine = false)
         * \brief This function is used to add the data in printing buffer.
         * \param[in] r_const_strDATA used to specify the data to be printed.
         * \param[in] eFontSize used to set the fontsize of the data. font sizes are Small,Medium and Big. default font size is Medium.
         * \param[in] eFontStyle used to set the fontstyle of the data. fontstyles are Regular,Bold,Italic and BoldItalic. default fontstyle is Regular.
         * \param[in] eAlign used to align the printing data. alignments are Left,Center, and Right. default alignment is Left.
         * \param[in] bUnderLine used to underline the data. default value is false.
         *
         * \sa see also E_FontSize, E_FontStyle and E_Alignment.
         */
        void addData(const QString &r_const_strDATA,
                     E_FontSize eFontSize = eFontSize_MEDIUM,
                     E_FontStyle eFontStyle = eFontStyle_REGULAR,
                     E_Alignment eAlign = eAlignment_LEFT,
                     bool bUnderLine = false);

        /**
         * \fn void addNumber_bigFont(const QString &r_const_strDATA);
         * \brief This function is used to add numeric to print the bigfont .
         * \param[in] r_const_strDATA used to specify the data for print the numbers (max 12 numbers).
         */
        void addNumber_bigFont(const QString &r_const_strDATA);
        /**
         * \fn void addBarcode(const QString &r_const_strDATA, E_FontSize eFontSize=eFontSize_MEDIUM)
         * \brief This function is used to add the data to print the barcode .
         * \param[in] r_const_strDATA used to specify the data for print the barcode.
         * \param[in] eFontSize used to set the fontsize of the data. font sizes are Small,Medium and Big. default font size is Medium.
         *
         * \sa see also E_FontSize.
         */
        void addBarcode(const QString &r_const_strDATA,
                        E_FontSize eFontSize=eFontSize_MEDIUM);

        /**
         * \fn void addImage(const QImage &r_const_imagePRINT, bool bDithering = true,E_ImageBrightness e_ImageBrightness = eImagePrintLow)
         * \brief This function is used to add the image.
         * The maximum image width should be 384.
         * \param[in] r_const_imagePRINT used to specify the image which is to be printed.
         * \param[in] bDithering used to set dithering need to apply or not.
         * \param[in] e_ImageBrightness used to set image printing in dark or light quality.
         */
        void addImage(const QImage &r_const_imagePRINT, bool bDithering = true,E_ImageBrightness e_ImageBrightness = eImagePrintLow );

        /**
         * \fn void drawLine()
         * \brief This function is used to draw a single line in printing.
         */
        void drawLine();

        /**
         * \fn void clear()
         * \brief This function is used to clear the printer buffer.
         */
        void clear();

        /**
         * \fn bool print(bool bHeader=false,bool bFooter=false) const
         * \brief This function is used to print the data which was loaded in the printer buffer.
         * you can enable header & footer image with printing.
         * \param[in] bHeader used to Enable the header image.
         * \param[in] bFooter used to Enable the footer image.
         * \return It returns true, if the data is printed successfully; otherwise returns false.
         *
         * \sa see also loadHeaderImage() and loadFooterImage().
         */
        bool print(bool bHeader=false,bool bFooter=false) const;

        /**
         * \fn bool loadHeaderImage(const QImage &r_const_imageHEADER) const
         * \brief This function is used load the header image in the printer.
         * The maximum image width and hight should be 384*50.
         * loaded header image will be cleared after shutdown or restart the device.
         * \param[in] r_const_imageHEADER used to specify the image which is to be loaded in printer header.
         * \return It returns true, if the header image loaded successfully; otherwise returns false.
         */
        bool loadHeaderImage(const QImage &r_const_imageHEADER) const;

        /**
         * \fn bool loadFooterImage(const QImage &r_const_imageFOOTER) const
         * \brief This function is used load the footer image in the printer.
         * The maximum image width and hight should be 384*50.
         * loaded footer image will be cleared after shutdown or restart the device.
         * \param[in] r_const_imageFOOTER used to specify the image which is to be loaded in printer footer.
         * \return It returns true, if the footer image loaded successfully; otherwise returns false.
         */
        bool loadFooterImage(const QImage &r_const_imageFOOTER) const;

        /**
         * \fn bool testPrinter() const
         * \brief This function is used to test the printer.
         * now it has been removed in the co-processor.
         * \return It returns true, if the printer test is succeeded; otherwise returns false.
         */
        bool testPrinter() const;

        /**
         * \fn bool paperStatus(bool &r_const_bPaperAvailable) const
         * \brief This function is used to check the printer paper status.
         * \param[in] r_const_bPaperAvailable used to store paper sense result, true if paper is available on printer else false value will be stored.
         * \return It returns true, if the paper status command successfull; otherwise returns false.
         */
        bool paperStatus(bool &r_const_bPaperAvailable) const;

    private:
        /**
         * \var QList<QString> m_listDatas
         * \brief used to store the added data for printing.
         */
         QList<QString> m_listDatas;

         /**
          * \var QList<QImage> m_listImages
          * \brief used to store the added image for printing.
          */
         QList<QImage> m_listImages;

         /**
          * \var bool m_bNativeLanguage
          * \brief used to store flag value for native language selection.
          */
         bool m_bNativeLanguage;

         /**
          * \var QString m_stringNativeLanguage
          * \brief used to store the two digit code value for the selected native language, for example: Tamil-> "01".
          */
         QString m_stringNativeLanguage;

         /**
          * \var E_NativeLanguage m_eNativeLanguage
          * \brief used to store the currently selected native language enum value.
          */
         E_NativeLanguage m_eNativeLanguage;

         /**
          * \fn QString ToUtf16_Printable(const QString &r_const_strDATA)
          * This function is used to convert UTF-8 formatted data into UTF-16 printable format
          * ((ie) last one byte of UTF-16 hex value will be taken for printing. (eg) 0x08C5 will be taken as 0xC5
          * \param[in] r_const_strDATA used to pass the data to be printed (In Native format, UTF-8 Encoded).
          */
         QString ToUtf16_Printable(const QString &r_const_strDATA);
    };
}
#endif // CPRINTER_H
