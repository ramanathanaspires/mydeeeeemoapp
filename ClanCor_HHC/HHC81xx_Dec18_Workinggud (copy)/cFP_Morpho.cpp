#include <QDebug>
#include <QBuffer>
#include <QFile>
#include <QMessageBox>
#include <QtGui/QApplication>
#include "cFP_Morpho.h"
using namespace ClanCor;

MORPHO_HANDLE g_h_Mso100Handle;
I CommandCallback (PVOID i_pv_context, I i_i_command, PVOID i_pv_param)
{
        qApp->processEvents();
        T_MORPHO_CALLBACK_IMAGE_STATUS l_x_ImageStructure;
        PUC l_puc_EnrollmentCmd;
        C l_c_String[256];
        UC l_uc_quality;

        if (i_i_command == MORPHO_CALLBACK_COMMAND_CMD)
        {
                switch (*((PI) i_pv_param))
                {
                case MORPHO_REMOVE_FINGER:
                lbl_fingstat->setText("REMOVE FINGER");
//                qDebug()<<"REMOVE FINGER";
                break;
                case MORPHO_MOVE_NO_FINGER:
                lbl_fingstat->setText("NO FINGER");
//                qDebug()<<"NO FINGER";
                break;
                case MORPHO_LATENT:
                lbl_fingstat->setText("LATENT");
//                qDebug()<<"LATENT";
                break;
                case MORPHO_MOVE_FINGER_UP:
                lbl_fingstat->setText("MOVE UP");
//                qDebug()<<"MOVE UP";
                break;
                case MORPHO_MOVE_FINGER_DOWN:
                lbl_fingstat->setText("MOVE DOWN");
//                qDebug()<<"MOVE DOWN";
                break;
                case MORPHO_MOVE_FINGER_LEFT:
                lbl_fingstat->setText("MOVE LEFT");
//                qDebug()<<"MOVE LEFT";
                break;
                case MORPHO_MOVE_FINGER_RIGHT:
                lbl_fingstat->setText("MOVE RIGHT");
//                qDebug()<<"MOVE RIGHT";
                break;
                case MORPHO_PRESS_FINGER_HARDER:
                lbl_fingstat->setText("Press Harder");
//                qDebug()<<"Press Harder";
                break;
                case MORPHO_FINGER_OK:
                lbl_fingstat->setText("Acquisition ok");
//                qDebug()<<"Acquisition ok";
                break;
                default:
                sprintf(l_c_String, "Async message %d\n", *(PI) i_pv_param);
                lbl_fingstat->setText(l_c_String);
//                qDebug()<<l_c_String;
                break;
                }
        }

        if (i_i_command == MORPHO_CALLBACK_ENROLLMENT_CMD)
        {
            l_puc_EnrollmentCmd = (PUC) i_pv_param;
            switch (l_puc_EnrollmentCmd[0])
            {
                case 1:
                switch (l_puc_EnrollmentCmd[2])
                {
                    case 1:
                        sprintf (l_c_String,
                                "Place your finger on sensor -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                    break;

                    case 2:
                        sprintf (l_c_String,
                                "Place your finger on sensor -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                    break;

                    case 3:
                        sprintf (l_c_String,
                                "Place your finger on sensor -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                    break;
                }
                break;

            case 2:
                switch (l_puc_EnrollmentCmd[2])
                {
                    case 1:
                        sprintf (l_c_String,
                                "Place Left Forefinger -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                    break;

                    case 2:
                        sprintf (l_c_String,
                                "Left Forefinger Again -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                            break;

                    case 3:
                        sprintf (l_c_String,
                                "Left Forefinger Again -> Capture %d/%d",
                                l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
                        lbl_finginfo->setText(l_c_String);
//                        qDebug()<<l_c_String;
                    break;
                }
                break;
            }
        }

        if (i_i_command == MORPHO_CALLBACK_IMAGE_CMD)
        {
                memcpy (&l_x_ImageStructure.m_x_ImageHeader,
                        (T_MORPHO_IMAGE_HEADER *) i_pv_param,
                        sizeof (T_MORPHO_IMAGE_HEADER));
                l_x_ImageStructure.m_puc_Image =
                (PUC) i_pv_param + sizeof (T_MORPHO_IMAGE_HEADER);

                Display_Image (l_x_ImageStructure.m_puc_Image,
                        l_x_ImageStructure.m_x_ImageHeader.m_us_NbRow,
                        l_x_ImageStructure.m_x_ImageHeader.m_us_NbCol,
                        l_x_ImageStructure.m_x_ImageHeader.m_uc_NbBitsPerPixel);
                qApp->processEvents();
//                SDL_PollEvent (&event);
//                if (event.type == SDL_QUIT)
//                MSO_Cancel (g_h_Mso100Handle);

        }

        if (i_i_command == MORPHO_CALLBACK_CODEQUALITY)
        {
            l_uc_quality = *(PUC) i_pv_param;
            sprintf (l_c_String, "Code Quality : %d", l_uc_quality);
            lbl_finginfo->setText(lbl_finginfo->text() + " \n" + l_c_String);
//            qDebug()<<l_c_String;
        }

        if (i_i_command == MORPHO_CALLBACK_DETECTQUALITY)
        {
            l_uc_quality = *(PUC) i_pv_param;
            sprintf (l_c_String, "Detect Quality : %d", l_uc_quality);
            lbl_finginfo->setText(lbl_finginfo->text() + " \n" + l_c_String);
//            qDebug()<<l_c_String;
        }

        return 0;
}

CFP_Morpho::CFP_Morpho(QObject *parent) :
    QObject(parent)
{
//    I l_i_i;
    UC l_uc_ConnectionType;
    int l_i_IdProduct;
    I l_i_speed;
    C l_ac_Device[32];
    UC l_uc_loop;
    m_bIsError = false;

    /* Number of fingers to be used for each fingerprint operations, by default it has set to 1 finger */
    No_of_finger = 1;

    // Initialisation
    l_uc_ConnectionType = 0;
    g_h_Mso100Handle = NULL;
    l_i_speed = DEFAULT_BAUD_RATE;
    sprintf (l_ac_Device, "%s", DEFAULT_SERIAL_PORT);

    g_uc_ExportScore = 1;
    l_us_Timeout = 0;

    // main loop
    l_uc_loop = 1;

//    if (l_ul_AsynchronousEvnt > 0)
//    {
//        if (InitScreen () < 0)
//        {
//                MSO_UnregisterAllAsyncILV (g_h_Mso100Handle);
//                l_ul_AsynchronousEvnt = 0;
//        }
//    }
    l_ul_AsynchronousEvnt = MORPHO_CALLBACK_DETECTQUALITY |
            MORPHO_CALLBACK_CODEQUALITY |
            MORPHO_CALLBACK_IMAGE_CMD |
            MORPHO_CALLBACK_COMMAND_CMD | MORPHO_CALLBACK_ENROLLMENT_CMD;

//    T_MORPHO_IMAGE_HEADER l_x_ImgHdr;

    I l_i_Ret = MSO_Connect(&g_h_Mso100Handle,
                                l_uc_ConnectionType,
                                l_ac_Device,
                                l_i_speed,
                                &l_i_IdProduct);
    if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
    {
            strFPlastError = "Error connecting device --\n Ensure fingerprint module connected or not..!";
            m_bIsError = true;
            return;
    }
    // Register Asynchronous event Callback Function
    l_i_Ret = MSO_RegisterAsyncILV( g_h_Mso100Handle,
                                        l_ul_AsynchronousEvnt,
                                        (T_pFuncILV_Buffer) CommandCallback,
                                        NULL );
    if (l_i_Ret != 0)
    {
            strFPlastError = "Error connecting device --\nEnsure fingerprint module is connected or not..!";
            m_bIsError = true;
            return;
    }
    setFPTemplateType(e_FPTemplate_SAGEM_PKCOMP);
}

CFP_Morpho::~CFP_Morpho()
{
    // Disconnect to MSO
    I l_i_Ret = MSO_CloseCom (&g_h_Mso100Handle);
    if (l_i_Ret != RETURN_NO_ERROR)
    {
        qDebug("Error MSO_CloseCom\n");
    }
}

void CFP_Morpho::setTimeout(unsigned short nTimeout_mSecs)
{
    l_us_Timeout = nTimeout_mSecs;
}

void CFP_Morpho::setFPTemplateType(E_FPTemplateType e_FPTemplateType)
{
    switch ((int) e_FPTemplateType)
    {
    case e_FPTemplate_SAGEM_PKCOMP:         /**< Sagem PKCOMP (Recommanded minutiae) */
        m_PK_Type = ID_PKCOMP;
        break;

    case e_FPTemplate_SAGEM_PKMAT:          /**< Sagem PKMAT (minutiae) */
        m_PK_Type = ID_PKMAT;
        break;

    case e_FPTemplate_SAGEM_PKCOMP_NORM:    /**< Sagem PKCOMP Normal */
        m_PK_Type = ID_PKCOMP_NORM;
        break;

    case e_FPTemplate_SAGEM_PKMAT_NORM:     /**< Sagem PKMAT Normal */
        m_PK_Type = ID_PKMAT_NORM;
        break;

/*      Reader Not Supports below types */

//    case e_FPTemplate_SAGEM_PKBASE:         /**< Sagem PKBASE */
//        m_PK_Type = ID_PKBASE;
//        break;

//    case e_FPTemplate_SAGEM_PKMOC:          /**< Sagem PKMOC */
//        m_PK_Type = ID_PKMOC;
//        break;

//    case e_FPTemplate_ISO_PK:                 /**< ISO PK */
//        m_PK_Type = ID_ISO_PK;
//        break;

//    case e_FPTemplate_ISO_PK_PARAM:           /**< ISO PK_PARAM */
//        m_PK_Type = ID_ISO_PK_PARAM;
//        break;

//    case e_FPTemplate_ISO_PK_DATA_ILO_FMR:    /**< ISO PK_DATA_ILO_FMR */
//        m_PK_Type = ID_ISO_PK_DATA_ILO_FMR;
//        break;

    case e_FPTemplate_ISO_PK_DATA_ANSI_378:     /**< ISO ANSI INCITS 378 */
        m_PK_Type = ID_ISO_PK_DATA_ANSI_378;
        break;

    case e_FPTemplate_ISO_PK_DATA_ISO_FMR:      /**< ISO PK_DATA_ISO_FMR */
        m_PK_Type = ID_ISO_PK_DATA_ISO_FMR;
        break;

    case e_FPTemplate_ISO_PK_DATA_ISO_FMC_CS:   /**< ISO 19794-2, FMC Compact Size*/
        m_PK_Type = ID_ISO_PK_DATA_ISO_FMC_CS;
        break;

    case e_FPTemplate_ISO_PK_DATA_ISO_FMC_NS:   /**< ISO 19794-2, FMC Normal Size*/
        m_PK_Type = ID_ISO_PK_DATA_ISO_FMC_NS;
        break;

    case e_FPTemplate_ISO_PK_DATA_MINEX_A:      /**< MINEX A*/
        m_PK_Type = ID_ISO_PK_DATA_MINEX_A;
        break;
    }
}

bool CFP_Morpho::EnrollFinger(QByteArray &r_BAryFP_PK, QImage &r_Image_FP)
{
    CFP_API_Morpho w;
    w.show();
    qApp->processEvents();
    I l_i_i;
    T_EXPORT_PK l_x_ExportPk;
    PT_EXPORT_PK l_px_ExportPk;
    T_EXPORT_IMAGE l_x_ExportImage;
    PT_EXPORT_IMAGE l_px_ExportImage;
    T_MORPHO_IMAGE_HEADER l_x_ImgHdr;

    l_px_ExportPk = &l_x_ExportPk;
    l_px_ExportImage = &l_x_ExportImage;

    if (l_px_ExportPk != NULL)
    {
        l_x_ExportPk.io_px_BiometricData =(PT_BUF) malloc (No_of_finger * sizeof (T_BUF));
        l_x_ExportPk.i_uc_ExportMinutiae = 1;
        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
                l_x_ExportPk.io_px_BiometricData[l_i_i].m_ul_Size = 512;
                l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf = (unsigned char *) malloc (512);
                memset (l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf, 0, 512);
        }
    }

    if (l_px_ExportImage != NULL)
    {
        l_x_ExportImage.io_px_BufImage = (PT_BUF) malloc (No_of_finger * sizeof (T_BUF));
        l_x_ExportImage.i_uc_ExportImageType = 0;
        l_x_ExportImage.i_uc_CompressionType = ID_COMPRESSION_NULL;
        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
            l_x_ExportImage.io_px_BufImage[l_i_i].m_ul_Size = 416 * 416 + 12;
            l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf =
                    (unsigned char*) malloc (416 * 416 + 12);
            memset (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf,
                    0, 416 * 416 + 12);
        }
    }

    if(m_PK_Type == ID_PKCOMP)
    {
        m_PK_Type = 0;          // If i_uc_NormalizedPK_Type is ID_PKCOMP, we have to use normalisedpk as 0 (sagem default format). then only enrolled data verified & identified using ID_PKCOMP type otherwise returns error
    }

    m_bReturn = EnrollUser(g_h_Mso100Handle,
                            l_ul_AsynchronousEvnt,
                            l_us_Timeout,
                            l_px_ExportPk,
                            l_px_ExportImage,
                            m_PK_Type);
    if (m_bReturn)
    {
        qDebug()<<"Enroll status";
        T_BUF i_px_Buf;
        if (l_px_ExportPk != NULL)
        {

            r_BAryFP_PK.clear();
            QDataStream datastr(&r_BAryFP_PK, QIODevice::ReadWrite);
            i_px_Buf = *l_px_ExportPk->io_px_BiometricData;

            for(unsigned int tmpcount = 0; tmpcount<i_px_Buf.m_ul_Size; tmpcount++)
                datastr<<(unsigned char)i_px_Buf.m_puc_Buf[tmpcount];

            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                if (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf != NULL)
                        free (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf);
            }
            if (l_px_ExportPk->io_px_BiometricData != NULL)
                free (l_px_ExportPk->io_px_BiometricData);
        }

        if(l_px_ExportImage != NULL)
        {
            i_px_Buf = *l_px_ExportImage->io_px_BufImage;
            QByteArray imgData = Format_Image(i_px_Buf.m_puc_Buf, 256, 400, 12);

            r_Image_FP.loadFromData(imgData);
            memcpy ((PUC) & l_x_ImgHdr,
                    l_x_ExportImage.io_px_BufImage->m_puc_Buf,
                    sizeof (T_MORPHO_IMAGE_HEADER));
//            qDebug( "\n---- Image Header Information ----\n");
//            qDebug( "Header Revision:  %d\n",
//                    l_x_ImgHdr.m_uc_HeaderRevision);
//            qDebug( "Header size:      %d\n",
//                    l_x_ImgHdr.m_uc_HeaderSize);
//            qDebug( "Nb Row:           %d\n", l_x_ImgHdr.m_us_NbRow);
//            qDebug( "Nb Col:           %d\n", l_x_ImgHdr.m_us_NbCol);
//            qDebug( "Res X:            %d\n", l_x_ImgHdr.m_us_ResX);
//            qDebug( "Res Y:            %d\n", l_x_ImgHdr.m_us_ResY);
//            qDebug( "Compression Type: %d\n",
//                    l_x_ImgHdr.m_uc_CompressionType);
//            qDebug( "Compression Param:%d\n",
//                    l_x_ImgHdr.m_uc_NbBitsPerPixel);

            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                if (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf != NULL)
                        free (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf);
            }
            if (l_x_ExportImage.io_px_BufImage != NULL)
                free (l_x_ExportImage.io_px_BufImage);
        }
    }
    else
    {
        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
            if (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf != NULL)
                    free (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf);
        }
        if (l_px_ExportPk->io_px_BiometricData != NULL)
            free (l_px_ExportPk->io_px_BiometricData);

        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
            if (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf != NULL)
                    free (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf);
        }
        if (l_x_ExportImage.io_px_BufImage != NULL)
            free (l_x_ExportImage.io_px_BufImage);
        return false;
    }

    w.close();
    qApp->processEvents();
    return true;
}

bool CFP_Morpho::Capture(QByteArray &r_BAryFP_PK, QImage &r_Image_FP)
//bool CFP_Morpho::Capture(QByteArray *FP_PK, QImage *FP_image)
{
    CFP_API_Morpho w;
    w.show();
    qApp->processEvents();
    I l_i_i;
    T_EXPORT_PK l_x_ExportPk;
    PT_EXPORT_PK l_px_ExportPk;
    T_EXPORT_IMAGE l_x_ExportImage;
    PT_EXPORT_IMAGE l_px_ExportImage;
    T_MORPHO_IMAGE_HEADER l_x_ImgHdr;

//    if(r_BAryFP_PK.isNull())
//        l_px_ExportPk = NULL;
//    else
        l_px_ExportPk = &l_x_ExportPk;
//    if(r_Image_FP.isNull())
//        l_px_ExportImage = NULL;
//    else
        l_px_ExportImage = &l_x_ExportImage;

    if (l_px_ExportPk != NULL)
    {
            l_x_ExportPk.io_px_BiometricData =(PT_BUF) malloc (No_of_finger * sizeof (T_BUF));
            l_x_ExportPk.i_uc_ExportMinutiae = 1;
            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                    l_x_ExportPk.io_px_BiometricData[l_i_i].m_ul_Size = 512;
                    l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf = (unsigned char *) malloc (512);
                    memset (l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf, 0, 512);
            }
    }

    if (l_px_ExportImage != NULL)
    {
            l_x_ExportImage.io_px_BufImage = (PT_BUF) malloc (No_of_finger * sizeof (T_BUF));
            l_x_ExportImage.i_uc_ExportImageType = 0;
            l_x_ExportImage.i_uc_CompressionType = ID_COMPRESSION_NULL;
            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                    l_x_ExportImage.io_px_BufImage[l_i_i].m_ul_Size = 416 * 416 + 12;
                    l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf =
                            (unsigned char*) malloc (416 * 416 + 12);
                    memset (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf,
                            0, 416 * 416 + 12);
            }
    }
    m_bReturn = capture(g_h_Mso100Handle,
                            l_ul_AsynchronousEvnt,
                            l_us_Timeout,
                            l_px_ExportPk,
                            l_px_ExportImage);
    if (m_bReturn)
    {
        T_BUF i_px_Buf;
        if (l_px_ExportPk != NULL)
        {

            r_BAryFP_PK.clear();
            QDataStream datastr(&r_BAryFP_PK, QIODevice::ReadWrite);
            i_px_Buf = *l_px_ExportPk->io_px_BiometricData;

            for(unsigned int tmpcount = 0; tmpcount<i_px_Buf.m_ul_Size; tmpcount++)
                datastr<<(unsigned char)i_px_Buf.m_puc_Buf[tmpcount];

            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                    if (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf != NULL)
                            free (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf);
            }
            if (l_px_ExportPk->io_px_BiometricData != NULL)
                    free (l_px_ExportPk->io_px_BiometricData);
        }

        if(l_px_ExportImage != NULL)
        {
            i_px_Buf = *l_px_ExportImage->io_px_BufImage;
            QByteArray imgData = Format_Image(i_px_Buf.m_puc_Buf, 256, 400, 12);

            r_Image_FP.loadFromData(imgData);
            memcpy ((PUC) & l_x_ImgHdr,
                    l_x_ExportImage.io_px_BufImage->m_puc_Buf,
                    sizeof (T_MORPHO_IMAGE_HEADER));
//            qDebug( "\n---- Image Header Information ----\n");
//            qDebug( "Header Revision:  %d\n",
//                    l_x_ImgHdr.m_uc_HeaderRevision);
//            qDebug( "Header size:      %d\n",
//                    l_x_ImgHdr.m_uc_HeaderSize);
//            qDebug( "Nb Row:           %d\n", l_x_ImgHdr.m_us_NbRow);
//            qDebug( "Nb Col:           %d\n", l_x_ImgHdr.m_us_NbCol);
//            qDebug( "Res X:            %d\n", l_x_ImgHdr.m_us_ResX);
//            qDebug( "Res Y:            %d\n", l_x_ImgHdr.m_us_ResY);
//            qDebug( "Compression Type: %d\n",
//                    l_x_ImgHdr.m_uc_CompressionType);
//            qDebug( "Compression Param:%d\n",
//                    l_x_ImgHdr.m_uc_NbBitsPerPixel);

            for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
            {
                    if (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf != NULL)
                            free (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf);
            }
            if (l_x_ExportImage.io_px_BufImage != NULL)
                    free (l_x_ExportImage.io_px_BufImage);
        }

    }
    else
    {
        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
                if (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf != NULL)
                        free (l_px_ExportPk->io_px_BiometricData[l_i_i].m_puc_Buf);
        }
        if (l_px_ExportPk->io_px_BiometricData != NULL)
                free (l_px_ExportPk->io_px_BiometricData);

        for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
        {
                if (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf != NULL)
                        free (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf);
        }
        if (l_x_ExportImage.io_px_BufImage != NULL)
                free (l_x_ExportImage.io_px_BufImage);
        w.close();
        qApp->processEvents();
        return false;
    }
    w.close();
    qApp->processEvents();
    return true;
}

bool CFP_Morpho::VerifyFinger(QByteArray &r_BAryPK_Ref, bool &r_bResult)
//bool CFP_Morpho::VerifyFinger(QByteArray *PK_Ref, bool *Result)
{
    CFP_API_Morpho w;
    w.show();
    qApp->processEvents();
    I l_i_i;
    UC l_uc_ConnectionType;
    I l_i_speed;
    C l_ac_Device[32];

    T_BUF_PK l_x_Buf_Pk[No_of_finger];


    // Initialisation
    l_uc_ConnectionType = 0;
    l_i_speed = DEFAULT_BAUD_RATE;
    sprintf (l_ac_Device, "%s", DEFAULT_SERIAL_PORT);

    g_uc_ExportScore = 1;

    for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
    {
            l_x_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = 512;
            l_x_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf =(PUC) malloc (512);
            memset (l_x_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf, 0, 512);
    }

    l_x_Buf_Pk[0].m_uc_IdPk = m_PK_Type;
    l_x_Buf_Pk[0].m_uc_Index = 0;

//    for(int cnt_no_data = 0; cnt_no_data<No_of_finger; cnt_no_data++)
//    {
        for(int tmpcount = 0 ; tmpcount<r_BAryPK_Ref.size(); tmpcount++)
            l_x_Buf_Pk[0].m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)r_BAryPK_Ref.at(tmpcount);
        l_x_Buf_Pk[0].m_x_Buf.m_ul_Size = (UL) r_BAryPK_Ref.size();
//    }

    m_bReturn = Verify( g_h_Mso100Handle,
                    (PT_BUF_PK) & l_x_Buf_Pk,
                    No_of_finger,
                    l_ul_AsynchronousEvnt,
                    l_us_Timeout );

    for (l_i_i = 0; l_i_i < No_of_finger; l_i_i++)
    {
        if (l_x_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf != NULL)
        free (l_x_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf);
    }
    if(!m_bReturn)
    {
        QMessageBox::critical(0, "Error: Finger Print Identify", strFPlastError);
        w.close();
        return false;
    }
    if(FingerMatch == 0)
        r_bResult = true;
    else if(FingerMatch == 1)
        r_bResult = false;
    w.close();
    return true;
}

bool CFP_Morpho::Verify_Match(QByteArray &r_BAryPK_Src, QByteArray &r_BAryPK_Ref, bool &r_bResult)
//bool CFP_Morpho::Verify_Match(QByteArray *PK_Src, QByteArray *PK_Ref, bool *Result)
{
    qApp->processEvents();

    g_uc_ExportScore = 1;

    T_BUF_PK l_x_Buf_Pk_Ref, l_x_Buf_Pk_Src;

    l_x_Buf_Pk_Src.m_x_Buf.m_ul_Size = 512;
    l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf =(PUC) malloc (512);
    memset (l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf, 0, 512);

    l_x_Buf_Pk_Src.m_uc_IdPk = m_PK_Type;
    l_x_Buf_Pk_Src.m_uc_Index = 0;

    for(int tmpcount = 0 ; tmpcount<r_BAryPK_Src.size(); tmpcount++)
        l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)r_BAryPK_Src.at(tmpcount);
    l_x_Buf_Pk_Src.m_x_Buf.m_ul_Size = (UL) r_BAryPK_Src.size();

    l_x_Buf_Pk_Ref.m_x_Buf.m_ul_Size = 512;
    l_x_Buf_Pk_Ref.m_x_Buf.m_puc_Buf =(PUC) malloc (512);
    memset (l_x_Buf_Pk_Ref.m_x_Buf.m_puc_Buf, 0, 512);

    l_x_Buf_Pk_Ref.m_uc_IdPk = m_PK_Type;
    l_x_Buf_Pk_Ref.m_uc_Index = 0;

    for(int tmpcount = 0 ; tmpcount<r_BAryPK_Ref.size(); tmpcount++)
        l_x_Buf_Pk_Ref.m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)r_BAryPK_Ref.at(tmpcount);
    l_x_Buf_Pk_Ref.m_x_Buf.m_ul_Size = (UL) r_BAryPK_Ref.size();

    m_bReturn = VerifyMatch(g_h_Mso100Handle,
                    (PT_BUF_PK) & l_x_Buf_Pk_Src,
                    (PT_BUF_PK) & l_x_Buf_Pk_Ref,
                    No_of_finger);

    if (l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf != NULL)
        free (l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf);

    if (l_x_Buf_Pk_Ref.m_x_Buf.m_puc_Buf != NULL)
        free (l_x_Buf_Pk_Ref.m_x_Buf.m_puc_Buf);

    if(!m_bReturn)
    {
        QMessageBox::critical(0, "Error: Finger Print Identify", strFPlastError);
        return false;
    }
    if(FingerMatch == 0)
        r_bResult = true;
    else if(FingerMatch == 1)
        r_bResult = false;
    return true;
}

bool CFP_Morpho::IdentifyFinger(QList<QByteArray> &listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index)
//bool CFP_Morpho::IdentifyFinger(QList<QByteArray> *list_PK_Ref, bool *Result, int *match_index)
{
    CFP_API_Morpho w;
    w.show();
    qApp->processEvents();
    g_uc_ExportScore = 1;

    if(m_PK_Type == ID_PKCOMP)
    {
        m_PK_Type = 0 ;
    }

    m_bReturn = Identify_custom(g_h_Mso100Handle,
                    &listBAry_PK_Ref,
                    l_ul_AsynchronousEvnt,
                    l_us_Timeout,
                    &r_nmatch_index,
                    m_PK_Type);

    if(!m_bReturn)
    {
        QMessageBox::critical(0, "Error: Finger Print Verify", strFPlastError);
        w.close();
        return false;
    }
    if(r_nmatch_index == -1)
        r_bResult = false;
    else
        r_bResult = true;
    w.close();
    return true;
}

bool CFP_Morpho::Identify_Match(QByteArray &r_BAryPK_Src, QList<QByteArray> &r_listBAry_PK_Ref, bool &r_bResult, int &r_nmatch_index)
//bool CFP_Morpho::Identify_Match(QByteArray *PK_Src, QList<QByteArray> *list_PK_Ref, bool *Result, int *match_index)
{
    qApp->processEvents();
    g_uc_ExportScore = 1;

    T_BUF_PK l_x_Buf_Pk_Src;

    l_x_Buf_Pk_Src.m_x_Buf.m_ul_Size = 512;
    l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf =(PUC) malloc (512);
    memset (l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf, 0, 512);

//    l_x_Buf_Pk_Src.m_uc_IdPk = ID_PKCOMP;
    l_x_Buf_Pk_Src.m_uc_IdPk = m_PK_Type;
    l_x_Buf_Pk_Src.m_uc_Index = 0;

    for(int tmpcount = 0 ; tmpcount<r_BAryPK_Src.size(); tmpcount++)
        l_x_Buf_Pk_Src.m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)r_BAryPK_Src.at(tmpcount);
    l_x_Buf_Pk_Src.m_x_Buf.m_ul_Size = (UL) r_BAryPK_Src.size();

    m_bReturn = identify_mat(g_h_Mso100Handle,
                           &l_x_Buf_Pk_Src,
                           &r_listBAry_PK_Ref,
                           &r_nmatch_index,
                           m_PK_Type);

    if(!m_bReturn)
    {
        QMessageBox::critical(0, "Error: Finger Print Verify", strFPlastError);
        return false;
    }
    if(r_nmatch_index == -1)
        r_bResult = false;
    else
        r_bResult = true;
    return true;
}
