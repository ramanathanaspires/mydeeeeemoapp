#include "cFP_API_Morpho.h"
#include <QMessageBox>
using namespace func_members;

#include <QFile>
#include <QKeyEvent>
#include <QDir>
#include <usb.h>
#include "MSO100.h"

UC func_members::g_uc_ExportScore = 0;

QLabel *func_members::lbl_fingstat = 0;
QLabel *func_members::lbl_finginfo = 0;
QLabel *func_members::lbl_image = 0;
QString func_members::strFPlastError = 0;
int func_members::FingerMatch = -1;


typedef struct {
  int Size;
  int Reserved;
  int Offset;
  int header_sz;
  int width;
  int height;
  short nplanes;
  short bitspp;
  int compress_type;
  int bmp_bytesz;
  int hres;
  int vres;
  int ncolors;
  int nimpcolors;
} BMPHeader;



CFP_API_Morpho::CFP_API_Morpho(QWidget *parent) :
    QWidget(parent)
{

    lbl_fingerinfo.setParent(this);
    lbl_fingerstat.setParent(this);
    lbl_fingerimage.setParent(this);
    pBtn_close.setParent(this);

    lbl_finginfo = &lbl_fingerinfo;
    lbl_fingstat = &lbl_fingerstat;
    lbl_image = &lbl_fingerimage;

    lbl_fingerimage.setGeometry(84,0,156,240);

    lbl_fingerstat.setGeometry(0,190,320,20);
    lbl_fingerstat.setStyleSheet("background-color: qlineargradient(spread:repeat, x1:1, y1:1, x2:1, y2:0, stop:0.669903 rgba(209, 186, 171, 255), stop:1 rgba(255, 255, 255, 255));");
    lbl_fingerstat.setAlignment(Qt::AlignCenter);

    lbl_fingerinfo.setGeometry(0,210,321,30);
    lbl_fingerinfo.setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.145631 rgba(236, 240, 205, 206), stop:0.354369 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:0.529126 rgba(255, 162, 162, 80), stop:0.699029 rgba(255, 132, 132, 156), stop:1 rgba(255, 255, 255, 0));");
    lbl_fingerinfo.setAlignment(Qt::AlignCenter);

    pBtn_close.setGeometry(274,5,40,40);
    connect(&pBtn_close, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    QIcon iconCancel;
    iconCancel.addFile(":/icons-png/cancel.png");
    pBtn_close.setIcon(iconCancel);
    setStyleSheet("QWidget{background-color: rgb(255, 255, 255);};");
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(320, 240);
    pBtn_close.setFocusPolicy(Qt::StrongFocus);
    raise();
    pBtn_close.setFocus();
}

CFP_API_Morpho::~CFP_API_Morpho()
{
}

void CFP_API_Morpho::on_pushButton_clicked()
{
    extern MORPHO_HANDLE g_h_Mso100Handle;
    MSO_Cancel(g_h_Mso100Handle);
}

void CFP_API_Morpho::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F4 || event->key() == Qt::Key_Escape)
    {
        on_pushButton_clicked();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

/*****************************************************************************/
/*****************************************************************************/
void usage (void)
{
        fprintf (stdout, "---------------- MSO_TestBio Options------------------ \n");
        fprintf (stdout, "Connection mode         : -c (Default: USB) \n");
        fprintf (stdout, "---->  -c USB           : Usb Connection \n");
        fprintf (stdout, "---->  -c RS232         : Serial Connection:  Port /dev/ttyS0  \n");
        fprintf (stdout, "Speed (RS232)           : -s (Default: 115200) \n");
        fprintf (stdout, "---->  -s <speed>       : Set baud rate to <speed> \n");
        fprintf (stdout, "Device Name (RS232)     : -d (Default: /dev/ttyS0) \n");
        fprintf (stdout, "---->  -d <device>      : Set device name to device \n");
        fprintf (stdout, "Timeout                 : -t Timeout for acquisition function (Default: Infinite)\n");
        fprintf (stdout, "---->  -t <timeout>     : Set Timeout to <timeout> second, 0=> infinite timeout\n");
        fprintf (stdout, "Asynchronous event      : -e (Default: on)\n");
        fprintf (stdout, "---->  -e EVENT_OFF     : Set asynchronous event off\n");
        fprintf (stdout, "---->  -e EVENT_ON      : Set asynchronous event on\n");
        fprintf (stdout, "Export Score            : -x (Default: SCORE_ON)\n");
        fprintf (stdout, "---->  -x SCORE_OFF     : Export score off\n");
        fprintf (stdout, "---->  -x SCORE_ON      : Export score on\n");
        fprintf (stdout, "Export PK (Enroll)      : -p (Default: EXPORT_PK_OFF)\n");
        fprintf (stdout, "---->  -p EXPORT_PK_OFF : Export PK off\n");
        fprintf (stdout, "---->  -p EXPORT_PK_ON  : Export PK on\n");
        fprintf (stdout, "Export Image (Enroll)   : -i (Default: EXPORT_IMG_OFF)\n");
        fprintf (stdout, "---->  -i EXPORT_IMG_OFF: Export Image off\n");
        fprintf (stdout, "---->  -i EXPORT_IMG_ON : Export Image on\n");
        fprintf (stdout, "\n");
        fprintf (stdout, "Examples :\n");
        fprintf (stdout, "----> MSO_TestBio -c USB -p EXPORT_PK_ON \n");
        fprintf (stdout, "----> MSO_TestBio -c RS232 -s 57600 -e off \n");
        fprintf (stdout, "\n");
        fprintf (stdout, "In order to test verify, verify match and identify match function\n");
        fprintf (stdout, "you can create a pkcomp file with EXPORT_PK_ON option in Enroll function\n");
        fprintf (stdout, "\n");

}

/*****************************************************************************/
/*****************************************************************************/
I func_members::ConvertImage(	PUC i_puc_Img,
                                US i_us_NbRow,
                                US i_us_NbCol,
                                UC i_uc_NbBitsPerPixel,
                                PUC o_puc_Img8BitsPerPixel)
{
        I l_i_ImageSize;
        PUC l_puc_image8bits;
        I l_i_Cnt;

        l_puc_image8bits = o_puc_Img8BitsPerPixel;

        l_i_ImageSize = i_us_NbRow * i_us_NbCol;
        switch (i_uc_NbBitsPerPixel)
        {
        case 8:
                memcpy (o_puc_Img8BitsPerPixel, i_puc_Img, l_i_ImageSize);
                break;
        case 4:
                for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize / 2; l_i_Cnt++)
                {
                        l_puc_image8bits[2 * l_i_Cnt] = (i_puc_Img[l_i_Cnt] & 0xF0) + 0x08;
                        l_puc_image8bits[2 * l_i_Cnt + 1] =((i_puc_Img[l_i_Cnt] & 0x0F) << 4) + 0x08;
                }
                break;
        case 2:
                for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize / 4; l_i_Cnt++)
                {
                        l_puc_image8bits[4 * l_i_Cnt] = (i_puc_Img[l_i_Cnt] & 0xC0);
                        l_puc_image8bits[4 * l_i_Cnt + 1] = ((i_puc_Img[l_i_Cnt] & 0x30) << 2);
                        l_puc_image8bits[4 * l_i_Cnt + 2] = ((i_puc_Img[l_i_Cnt] & 0x0C) << 4);
                        l_puc_image8bits[4 * l_i_Cnt + 3] = ((i_puc_Img[l_i_Cnt] & 0x03) << 6);
                        CORRECT_LEVEL2 (l_puc_image8bits[4 * l_i_Cnt])
                        CORRECT_LEVEL2 (l_puc_image8bits[4 * l_i_Cnt + 1])
                        CORRECT_LEVEL2 (l_puc_image8bits[4 * l_i_Cnt + 2])
                        CORRECT_LEVEL2 (l_puc_image8bits[4 * l_i_Cnt + 3])
                }
                break;
        case 1:
                for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize / 8; l_i_Cnt++)
                {
                        l_puc_image8bits[8 * l_i_Cnt] = (UC) (i_puc_Img[l_i_Cnt] & 0x80);
                        l_puc_image8bits[8 * l_i_Cnt + 1] = (UC) ((i_puc_Img[l_i_Cnt] & 0x40) << 1);
                        l_puc_image8bits[8 * l_i_Cnt + 2] = (UC) ((i_puc_Img[l_i_Cnt] & 0x20) << 2);
                        l_puc_image8bits[8 * l_i_Cnt + 3] = (UC) ((i_puc_Img[l_i_Cnt] & 0x10) << 3);
                        l_puc_image8bits[8 * l_i_Cnt + 4] = (UC) ((i_puc_Img[l_i_Cnt] & 0x08) << 4);
                        l_puc_image8bits[8 * l_i_Cnt + 5] = (UC) ((i_puc_Img[l_i_Cnt] & 0x04) << 5);
                        l_puc_image8bits[8 * l_i_Cnt + 6] = (UC) ((i_puc_Img[l_i_Cnt] & 0x02) << 6);
                        l_puc_image8bits[8 * l_i_Cnt + 7] = (UC) ((i_puc_Img[l_i_Cnt] & 0x01) << 7);
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 1])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 2])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 3])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 4])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 5])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 6])
                        CORRECT_LEVEL1 (l_puc_image8bits[8 * l_i_Cnt + 7])
                }
                break;
        default:
                char l_c_string[50];
                sprintf (l_c_string,
                        "Invalid value i_uc_NbBitsPerPixel: %d",
                        i_uc_NbBitsPerPixel);
                strFPlastError = QString(l_c_string);
                return -1;
        }

        return 0;
}

QString Reverse(QString Data)
{
    QString Output;
    for(int i=0;i<Data.length();i=i+2) Output=Data.mid(i,2)+Output;
    Data.clear();
    return Output;
}

/*****************************************************************************/
/*****************************************************************************/

I func_members::Display_Image (PUC i_puc_Img, US i_us_NbRow, US i_us_NbCol,
                UC i_uc_NbBitsPerPixel)
{
        I l_i_Ret;
//	SDL_Rect coords;
//	SDL_Rect Rect;
        PUC l_puc_image8bits;

        if ((i_uc_NbBitsPerPixel <= 0) || (i_us_NbRow <= 0) || (i_us_NbCol <= 0))
                return -1;

        l_puc_image8bits = (unsigned char*) malloc (648 * 488);
        l_i_Ret =
                ConvertImage (i_puc_Img, i_us_NbRow, i_us_NbCol,
                        i_uc_NbBitsPerPixel, l_puc_image8bits);
        if (l_i_Ret < 0)
                return -1;

        QByteArray data = Format_Image(l_puc_image8bits, i_us_NbCol, i_us_NbRow, 0);

        QImage img;
        img.loadFromData(data);

        if(img.width() > 150)
        {
            img = img.scaled(154,240);
            lbl_image->raise();
        }
        else
        {
            if(lbl_image->Raised)
                lbl_image->lower();
        }

        lbl_image->setPixmap(QPixmap::fromImage(img, Qt::AutoColor));

        if (l_puc_image8bits != NULL)
                free (l_puc_image8bits);

        return 0;
}

/*****************************************************************************/
/*****************************************************************************/

I func_members::SaveImgBufInFile(PT_BUF i_px_Buf, int width, int height, int header)
{
    QFile fp;
    C l_ac_String[256];
    I l_i_Ret = 0;

    sprintf(l_ac_String, "test");
    fp.setFileName(QString(l_ac_String));

    QByteArray imgData = Format_Image(i_px_Buf->m_puc_Buf, width, height, header);

    if(fp.open (QIODevice::ReadWrite))
    {
            fp.write(imgData);
            fp.close();
            imgData.clear();

            fprintf (stdout, "--> Save %d bytes in %s\n", l_i_Ret, l_ac_String);
    }
    else
    {
            fprintf (stdout, "Can't open file %s for writing\n", l_ac_String);
    }

    return 0;
}
/*****************************************************************************/
/*****************************************************************************/
I func_members::SaveBufInFile (PT_BUF i_px_Buf, PC i_pc_Ext)
{
        FILE *fp;
        C l_ac_String[256];
        I l_i_Ret;

//        fprintf (stdout, "%s", i_pc_String);
//        fprintf (stdout, "Enter File name : -> ");
       sprintf(l_ac_String, "test");
//        fgets (l_ac_String, 256, stdin);
        l_ac_String[strlen (l_ac_String) - 1] = 0;	// Suppress '\n'
        if (strstr (l_ac_String, i_pc_Ext) == NULL)
                strcat (l_ac_String, i_pc_Ext);

        fp = fopen (l_ac_String, "wb");
        if (fp != NULL)
        {
                l_i_Ret = fwrite (i_px_Buf->m_puc_Buf, 1, i_px_Buf->m_ul_Size, fp);
                fclose (fp);

                fprintf (stdout, "--> Save %d bytes in %s\n", l_i_Ret, l_ac_String);
        }
        else
        {
                fprintf (stdout, "Can't open file %s for writing\n", l_ac_String);
        }

        return 0;
}

/*****************************************************************************/
/*****************************************************************************/
I func_members::OpenPkFile (PT_BUF_PK i_px_Buf_Pk, PC i_pc_String)
{
        FILE *fp;
        C l_ac_String[256];
        I l_i_Ret;

        fprintf (stdout, "---Open PkComp V2 file: %s -----\n", i_pc_String);
//        fprintf (stdout, "Enter File name (*.pkc): -> ");
//        fgets (l_ac_String, 256, stdin);
        sprintf(l_ac_String, "tes.pkc ");
        l_ac_String[strlen (l_ac_String) - 1] = 0;	// Suppress '\n'

        fp = fopen (l_ac_String, "rb");
        if (fp != NULL)
        {
                i_px_Buf_Pk->m_uc_IdPk = ID_PKCOMP;
                i_px_Buf_Pk->m_uc_Index = 0;
                l_i_Ret = fread (i_px_Buf_Pk->m_x_Buf.m_puc_Buf, 1, 512, fp);
                if(l_i_Ret == 512)
                {
                    i_px_Buf_Pk->m_x_Buf.m_ul_Size = (UL) l_i_Ret;
                }
                else
                {
                    /* File might have less than 512 bytes, Check if End of file reached */
                    if(feof(fp))
                    {
                        i_px_Buf_Pk->m_x_Buf.m_ul_Size = (UL) l_i_Ret;
                    }
                    else
                    {
                        l_i_Ret = -1;
                        fprintf (stdout, "Error reading file %s ..!", l_ac_String);
                    }
                }
                fclose (fp);
                fprintf (stdout, "--> Read %d bytes in %s\n", l_i_Ret, l_ac_String);
        }
        else
        {
                l_i_Ret = -1;
                fprintf (stdout, "Can't open file %s for reading\n", l_ac_String);
        }

        return l_i_Ret;
}

/*****************************************************************************/
/*****************************************************************************/
I func_members::OpenImgFile (PUC i_puc_Img, I i_i_SizeBuf)
{
        FILE *fp;
        C l_ac_String[256];
        I l_i_Ret;

        fprintf (stdout, "---Open Image Raw file:  -----\n");
        fprintf (stdout, "Enter File name: -> ");
        fgets (l_ac_String, 256, stdin);
        l_ac_String[strlen (l_ac_String) - 1] = 0;	// Suppress '\n'

        fp = fopen (l_ac_String, "rb");
        if (fp != NULL)
        {
                l_i_Ret = fread (i_puc_Img, 1, i_i_SizeBuf, fp);
                fclose (fp);

                fprintf (stdout, "--> Read %d bytes in %s\n", l_i_Ret, l_ac_String);
        }
        else
        {
                l_i_Ret = -1;
                fprintf (stdout, "Can't open file %s for reading\n", l_ac_String);
        }

        return l_i_Ret;
}




/****************************************from command.c*******************/


// Database function
/***************************************************************************/
/**
* Delete user of index i_ul_IndexUser in database of index 0
*
*/
int func_members::DeleteUserIndex(MORPHO_HANDLE i_h_Mso100Handle)
{
    I   l_i_Ret;
    UC	l_uc_Status;
    UL  l_ul_EmbeddedError;
    UL	l_ul_IndexUser;
    C	l_ac_String[32];

    qDebug( "Enter Index of User to delete:\n->");
    fgets(l_ac_String, 32, stdin);
    sscanf(l_ac_String, "%ld", &l_ul_IndexUser);

    l_i_Ret = MSO_BioDB_DeleteUser( i_h_Mso100Handle,
                                    0,                   //UC              i_uc_IndexDB,
                                    l_ul_IndexUser,      //UL              i_ul_IndexUser,
                                    &l_uc_Status,        //PUC             o_puc_ILV_Status,
                                    &l_ul_EmbeddedError  //PUL             o_pul_EmbeddedError
                                  );
    if(l_i_Ret==0 && l_uc_Status==0 && l_ul_EmbeddedError==0)
    {
        qDebug( "Delete user with index %ld in Base index 0 -----> OK\n", l_ul_IndexUser);
        l_i_Ret = 0;
    }
    else
    {
        qDebug( "MSO_BioDB_DeleteUser ret=%d status=0x%02X EmbeddedError=%ld\n",
                                                       l_i_Ret, l_uc_Status, l_ul_EmbeddedError);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}


/***************************************************************************/
/**
* Delete all user in database of index 0
*
*/
int func_members::DeleteAllUser(MORPHO_HANDLE i_h_Mso100Handle)
{
    I   l_i_Ret;
    UC	l_uc_Status;
    UL  l_ul_EmbeddedError;

    l_i_Ret = MSO_BioDB_EraseDb( i_h_Mso100Handle,
                                 0,                         //UC   i_uc_IndexDB,
                                 &l_uc_Status,              //PUC  o_puc_ILV_Status,
                                 &l_ul_EmbeddedError        //PUL  o_pul_EmbeddedError
                               );
    if(l_i_Ret==0 && l_uc_Status==0 && l_ul_EmbeddedError==0)
    {
        qDebug( "Erase all user in Base index 0 -----> OK\n");
        l_i_Ret = 0;
    }
    else
    {
        qDebug( "MSO_BioDB_EraseDb ret=%d status=0x%02X EmbeddedError=%ld\n",
                                                      l_i_Ret, l_uc_Status, l_ul_EmbeddedError);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/***************************************************************************/
/**
* Destroy database of index 0
*
*/
int func_members::DestroyDatabase(MORPHO_HANDLE i_h_Mso100Handle)
{
    I   l_i_Ret;
    UC	l_uc_Status;
    UL  l_ul_EmbeddedError;

    l_i_Ret = MSO_BioDB_DestroyDb( i_h_Mso100Handle,
                                   0,
                                   &l_uc_Status,              //PUC  o_puc_ILV_Status,
                                   &l_ul_EmbeddedError        //PUL  o_pul_EmbeddedError
                                 );
    if(l_i_Ret == 0 && l_uc_Status==0 && l_ul_EmbeddedError ==0)
    {
        qDebug( "Destroy Base index 0 -----> OK\n");
        l_i_Ret = 0;
    }
    else
    {
        qDebug( "MSO_BioDB_DestroyDb ret=%d status=0x%02X EmbeddedError=%ld\n",
                                                        l_i_Ret, l_uc_Status, l_ul_EmbeddedError);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/***************************************************************************/
/**
* Create database of index 0
* - 2 Additionnal fields
* - Max User 100
* - 2 fingers per user
* - Standard PK
*/
int func_members::CreateDataBase(MORPHO_HANDLE i_h_Mso100Handle)
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    T_FIELD     l_x_BaseAddField[2];

    memset((PC)&l_x_BaseAddField, 0, sizeof(l_x_BaseAddField));
    // Add Field 1
    l_x_BaseAddField[0].m_us_FieldMaxSize = 15;
    sprintf((PC)l_x_BaseAddField[0].m_auc_FieldName, "Field1");
    l_x_BaseAddField[0].m_uc_Right = PUBLIC;

    // Add Field 2
    l_x_BaseAddField[1].m_us_FieldMaxSize = 15;
    sprintf((PC)l_x_BaseAddField[1].m_auc_FieldName, "Field2");
    l_x_BaseAddField[1].m_uc_Right = PUBLIC;

    l_i_Ret = MSO_BioDB_CreateDb( i_h_Mso100Handle,
                                  0,                             //UC       i_uc_IndexDB,
                                  100,                           //US       i_us_UserMax,
                                  2,                             //UC       i_uc_NbFinger,
                                  0,                             //UC       i_uc_NormalizedPK_Type,
                                  2,                             //UC       i_uc_NbAddField,
                                  (PT_FIELD)&l_x_BaseAddField,   //PT_FIELD i_px_AddField,
                                  &l_uc_Status                   //PUC      o_puc_ILV_Status
                                );
    if(l_i_Ret == 0 && l_uc_Status==0)
    {
        qDebug( "Create Base index 0 -----> OK\n");
    }
    else
    {
        qDebug( "MSO_BioDB_CreateDb ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/***************************************************************************/
/**
* Get Base Configuration
*
*/
int func_members::GetBaseConfig(MORPHO_HANDLE i_h_Mso100Handle)
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UL  	l_ul_EmbeddedError;
    I		l_i_i;
    T_FIELD     l_x_BaseAddField[2];
    UL 		l_ul_AddFieldNb;
    UC		l_uc_FingerNb;
    UL		l_ul_CurrentRecord;
    UC		l_uc_NormalizedPK_Type;
    UL		l_ul_MaxRecord;

    memset((PC)&l_x_BaseAddField, 0, sizeof(l_x_BaseAddField));
    l_ul_AddFieldNb = 2;
    l_uc_FingerNb = 0;
    l_ul_CurrentRecord = 0;
    l_i_Ret = MSO_BioDB_GetBaseConfig( i_h_Mso100Handle,
                                       0,                           //UC              i_uc_IndexDB,
                                       &l_uc_FingerNb,              //PUC             o_puc_FingerNb,
                                       &l_ul_MaxRecord,             //PUL             o_pul_MaxRecord,
                                       &l_ul_CurrentRecord,         //PUL             o_pul_CurrentRecord,
                                       &l_ul_AddFieldNb,    	    //PUL             io_pul_AddFieldNb,
                                       (PT_FIELD)&l_x_BaseAddField, //PT_FIELD        o_px_AddField,
                                       &l_uc_NormalizedPK_Type,     //PUC             o_puc_NormalizedPK_Type,
                                       &l_uc_Status,                //PUC             o_puc_ILV_Status,
                                       &l_ul_EmbeddedError          //PUL             o_pul_EmbeddedError
                                     );
    if(l_i_Ret==0 && l_uc_Status==0 && l_ul_EmbeddedError==0)
    {
        qDebug( "Get Base Config -----> OK\n");
        qDebug( "\tNormalized PK:         %d\n", l_uc_NormalizedPK_Type);
        qDebug( "\tFinger Number:         %d\n", l_uc_FingerNb);
        qDebug( "\tMax record number:     %ld\n", l_ul_MaxRecord);
        qDebug( "\tCurrent Record number: %ld\n", l_ul_CurrentRecord);
        qDebug( "\tAdd field Number:      %ld\n", l_ul_AddFieldNb);
        for(l_i_i=0;(unsigned) l_i_i<l_ul_AddFieldNb; l_i_i++)
            qDebug( "\t-->%s\n", l_x_BaseAddField[l_i_i].m_auc_FieldName);
    }
    else
    {
        qDebug( "MSO_BioDB_GetBaseConfig ret=%d status=0x%02X EmbeddedError=%ld\n",
                                                        l_i_Ret, l_uc_Status, l_ul_EmbeddedError);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

// Bio Function
/***************************************************************************/
/**
* Enroll User.
* Captures and enrolls live fingers
* - 1 User ID and 2 additionnal fields
* - 2 fingers per user
* - 3 acquisitions per finger
* - Standard PK
*/
bool func_members::EnrollUser( MORPHO_HANDLE   i_h_Mso100Handle,
                UL		i_ul_AsynchronousEvnt,
                US		i_us_Timeout,
                PT_EXPORT_PK    io_px_ExportPk,      //can be NULL
                PT_EXPORT_IMAGE io_px_ExportImage,    //can be NULL
                UC i_uc_NormalizedPK_Type)
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_EnrollStatus;
    UL		l_ul_UserDBIndex;

//    fprintf(stdout,"---Captures and enrolls live fingers---\n");

    l_i_Ret = MSO_Bio_Enroll( i_h_Mso100Handle,
                              0,                        //UC            i_uc_IndexDB,
                              i_us_Timeout,             //US            i_us_Timeout,
                              0,                        //UC            i_uc_EnrollmentType,
                              1,                        //UC            i_uc_NbFinger,
                              0,                        //UC            i_uc_SaveRecord,
                              i_uc_NormalizedPK_Type,                        //UC            i_uc_NormalizedPK_Type,
                              0,                        //UC            i_uc_NbAddField,
                              NULL,    //PT_BUF        i_px_AddField,
                              i_ul_AsynchronousEvnt,    //UL 		i_ul_AsynchronousEvnt,
                              io_px_ExportPk,     	//PT_EXPORT_PK  io_px_ExportPk,      //can be NULL
                              io_px_ExportImage,        //PT_EXPORT_IMAGE io_px_ExportImage, //can be NULL
                              &l_uc_EnrollStatus,       //PUC           o_puc_EnrollStatus,
                              &l_ul_UserDBIndex,        //PUL           o_pul_UserDBIndex,
                              &l_uc_Status              //PUC           o_puc_ILV_Status
                             );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Enroll -----> OK\n");
//        qDebug( "Enroll Status: %d\n", l_uc_EnrollStatus);
//        qDebug( "User Database Index: %ld\n", l_ul_UserDBIndex);
    }
    else
    {
        qDebug( "MSO_Bio_Enroll ret=%d status=0x%02X EnrollStatus=%d\n",
                                               l_i_Ret, l_uc_Status, l_uc_EnrollStatus);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return false;
    }
    return true;
}

/***************************************************************************/
/**
* identify a user.
* Identifies a live finger against the local database
*/
int func_members::Identify( MORPHO_HANDLE   i_h_Mso100Handle,
              UL              i_ul_AsynchronousEvnt,
              US              i_us_Timeout)
{
    I  		l_i_Ret;
    I  		l_i_i;
    UC		l_uc_Status;
    UL		l_ul_UserDBIndex;
    UC		l_uc_MatchingResult;
    UL		l_ul_AddFieldNb;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score;

    T_BUF       l_x_UserID;
    UC		l_auc_UserID[25];
    T_BUF       l_x_addField[2];
    UC		l_auc_AddField1[25];
    UC		l_auc_AddField2[25];

//    fprintf(stdout,"---Identifies a live finger against the local database---\n");

    if(g_uc_ExportScore)
        l_pul_Score = &l_ul_Score;
    else
        l_pul_Score = NULL;

    memset(l_auc_UserID, 0, sizeof(l_auc_UserID));
    memset(l_auc_AddField1, 0, sizeof(l_auc_AddField1));
    memset(l_auc_AddField2, 0, sizeof(l_auc_AddField2));
    memset(&l_x_UserID, 0, sizeof(l_x_UserID));
    memset(&l_x_addField, 0, sizeof(l_x_addField));

    l_x_UserID.m_puc_Buf = l_auc_UserID;
    l_x_addField[0].m_puc_Buf = l_auc_AddField1;
    l_x_addField[1].m_puc_Buf = l_auc_AddField2;
    l_ul_AddFieldNb = 2;

    l_i_Ret = MSO_Bio_Identify( i_h_Mso100Handle,
                                0,                     //UC                      i_uc_UidDB,
                                i_us_Timeout,          //US                      i_us_Timeout,
                                5,                     //US                      i_us_MatchingTreshold,
                                i_ul_AsynchronousEvnt, //UL                      i_ul_AsynchronousEvent,
                                &l_uc_MatchingResult,  //PUC                     o_puc_MatchingResult,
                                &l_ul_UserDBIndex,     //PUL                     o_pul_UserDBIndex,
                                (PT_BUF)&l_x_UserID,   //PT_BUF                  o_px_UserID,
                                &l_ul_AddFieldNb,      //PUL                     io_pul_AddFieldNb,
                                (PT_BUF)&l_x_addField, //PT_BUF                  o_px_AddFieldValue,
                                l_pul_Score,           //PUL                     o_pul_score,
                                &l_uc_Status           //PUC                     o_puc_ILV_Status
                             );

    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Identify -----> OK\n");
//        qDebug( "MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);
        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
//            qDebug( "User Identified--> index: %ld\n", l_ul_UserDBIndex);
//            qDebug( "\tUser ID: %s\n", l_x_UserID.m_puc_Buf);
            for(l_i_i = 0;(unsigned) l_i_i < l_ul_AddFieldNb; l_i_i++)
                qDebug( "\tAdd Field %d: %s\n", l_i_i, l_x_addField[l_i_i].m_puc_Buf);
        }
        else
            qDebug( "User Not Identified !! \n");
    }
    else
    {
        qDebug( "MSO_Bio_Identify ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/***************************************************************************/
/**
* Verify function.
* Captures a live finger and checks if it matches with one of input Pks
*/
bool func_members::Verify( MORPHO_HANDLE   i_h_Mso100Handle,
            PT_BUF_PK       i_x_Buf_Pk,
            UC		    i_uc_NbFinger,
            UL              i_ul_AsynchronousEvnt,
            US              i_us_Timeout)
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_MatchingResult;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score = 0;

//    fprintf(stdout,"---Captures a live finger and checks if it matches with one of input Pks---\n");

    if(g_uc_ExportScore)
        l_pul_Score = &l_ul_Score;
    else
        l_pul_Score = NULL;

    l_uc_MatchingResult = 0;
    l_ul_Score = 0;
    l_uc_Status = 0;

    l_i_Ret = MSO_Bio_Verify( i_h_Mso100Handle,
                              i_us_Timeout,           //US          i_us_Timeout,
                              5,                      //US          i_us_MatchingTreshold,
                              i_uc_NbFinger,          //UC          i_uc_NbFinger,
                              i_x_Buf_Pk, 	      //PT_BUF_PK   i_x_Buf_Pk
                              i_ul_AsynchronousEvnt,  //UL          i_ul_AsynchronousEvent,
                              &l_uc_MatchingResult,   //PUC         o_puc_MatchingResult,
                              l_pul_Score,            //PUL         o_pul_score,
                              &l_uc_Status            //PUC         o_puc_ILV_Status
                            );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
//        qDebug("MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);
        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
//            qDebug("Verify-->  Verify OK\n");
            FingerMatch = 0;
        }
        else
        {
//            qDebug("Verify-->  Verify NOT OK\n");
            FingerMatch = 1;
        }
    }
    else
    {
//        qDebug("MSO_Bio_Verify ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return false;
    }

    return true;
}

/***************************************************************************/
/**
* Identify match function.
* Identifies biometric data sent against the local database
*
*/
int func_members::IdentifyMatch( MORPHO_HANDLE   i_h_Mso100Handle,
                   PT_BUF_PK       i_px_Buf_Pk
                 )
{

    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_MatchingResult;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score;
    UL		l_ul_UserDBIndex;
    UC		l_auc_UserID[25];
    T_BUF       l_x_UserID;

//    fprintf(stdout,"---Identifies biometric data sent against the local database---\n");

    if(g_uc_ExportScore)
        l_pul_Score = &l_ul_Score;
    else
        l_pul_Score = NULL;

    memset(&l_x_UserID, 0, sizeof(l_x_UserID));
    memset(l_auc_UserID, 0, sizeof(l_auc_UserID));
    l_x_UserID.m_puc_Buf = l_auc_UserID;

    l_i_Ret = MSO_Bio_IdentifyMatch( i_h_Mso100Handle,
                                     0,                         //UC        i_uc_UidDB,
                                     5,                         //US        i_us_MatchingTreshold,
                                     1,                 	//UC        i_uc_NbPk, (Must be set to 1)
                                     i_px_Buf_Pk,    		//PT_BUF_PK i_px_Pk,
                                     &l_uc_MatchingResult,      //PUC       o_puc_MatchingResult,
                                     &l_ul_UserDBIndex,         //PUL       o_pul_UserDBIndex,
                                     (PT_BUF)&l_x_UserID,       //PT_BUF    o_px_UserID,
                                     l_pul_Score,               //PUL       o_pul_score,
                                     &l_uc_Status               //PUC       o_puc_ILV_Status
                                   );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
//        qDebug( "Identify Match -----> OK\n");
//        qDebug( "MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);
        if(l_uc_MatchingResult == ILVSTS_HIT)
            qDebug( "Identify Match--> name: %s index: %ld\n", l_x_UserID.m_puc_Buf, l_ul_UserDBIndex);
        else
            qDebug( "Identify Match KO: Not Identified !! \n");
    }
    else
    {
        qDebug( "MSO_Bio_Identify Match ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/***************************************************************************/
/*
* Verify Match function.
* Verifies if the input PkSrc matches against list of input PkRef
*/
bool func_members::VerifyMatch( MORPHO_HANDLE   i_h_Mso100Handle,
                 PT_BUF_PK       i_px_Buf_PkSrc,
                 PT_BUF_PK       i_px_Buf_PkRef,
                 UC		 i_uc_NbPkRef
               )
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_MatchingResult;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score;
    UC		l_uc_ListRefIndex;

//    fprintf(stdout,"---Verifies if the input PkSrc matches against list of input PkRef---\n");

    if(g_uc_ExportScore)
        l_pul_Score = &l_ul_Score;
    else
        l_pul_Score = NULL;

    l_i_Ret = MSO_Bio_VerifyMatch( i_h_Mso100Handle,
                                   1,                       //UC        i_uc_NbPkSrc (must be set to 1)
                                   i_px_Buf_PkSrc,          //PT_BUF_PK i_px_PkSrc
                                   i_uc_NbPkRef,            //UC        i_uc_NbPkRef
                                   i_px_Buf_PkRef,  	    //PT_BUF_PK i_px_PkRef
                                   5,                       //US        i_us_MatchingTreshold,
                                   &l_uc_MatchingResult,    //PUC       o_puc_MatchingResult,
                                   &l_uc_ListRefIndex,      //PUC       o_puc_ListRefIndex,
                                   l_pul_Score,             //PUL       o_pul_score,
                                   &l_uc_Status             //PUC       o_puc_ILV_Status
                                 );

    if(l_i_Ret==0 && l_uc_Status==0)
    {
//        qDebug( "Verify Match -----> OK\n");
//        qDebug( "MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);
        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
//            qDebug("Verify-->  Verify Match OK\n");
            FingerMatch = 0;
        }
        else
        {
//            qDebug("Verify-->  Verify Match NOT OK\n");
            FingerMatch = 1;
        }
    }
    else
    {
        qDebug( "MSO_Bio_VerifyMatch ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return false;
    }
    return true;
}

/***************************************************************************/
/*
* Identify Match function.
* identifies the input finger matches against list of input PkRef
*/
bool func_members::Identify_custom(MORPHO_HANDLE i_h_Mso100Handle,
                                  QList<QByteArray> *lstbyt_PkRef,
                                  UL i_ul_AsynchronousEvnt,
                                  US i_us_Timeout,
                                  int *match_index,
                                   UC i_uc_NormalizedPK_Type)
{
    *match_index = -1;
    I           l_i_i;
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_EnrollStatus;
    UL		l_ul_UserDBIndex;
    T_EXPORT_PK l_x_ExportPk;
    PT_EXPORT_PK l_px_ExportPk;
    T_BUF_PK i_px_Buf_PkSrc;
    l_px_ExportPk = &l_x_ExportPk;

    if (l_px_ExportPk != NULL)
    {
            l_x_ExportPk.io_px_BiometricData =(PT_BUF) malloc (1 * sizeof (T_BUF));
            l_x_ExportPk.i_uc_ExportMinutiae = 1;
            for (l_i_i = 0; l_i_i < 1; l_i_i++)
            {
                l_x_ExportPk.io_px_BiometricData[l_i_i].m_ul_Size = 512;
                l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf = (unsigned char *) malloc (512);
                memset (l_x_ExportPk.io_px_BiometricData[l_i_i].m_puc_Buf, 0, 512);
            }
    }


    i_px_Buf_PkSrc.m_x_Buf.m_ul_Size = 512;
    i_px_Buf_PkSrc.m_x_Buf.m_puc_Buf =(PUC) malloc (512);
    memset (i_px_Buf_PkSrc.m_x_Buf.m_puc_Buf, 0, 512);


    if(i_uc_NormalizedPK_Type == ID_PKCOMP)
    {
        i_uc_NormalizedPK_Type = 0;         // If i_uc_NormalizedPK_Type is ID_PKCOMP, we have to use normalisedpk as 0 (sagem default format). then only enrolled data verified & identified using ID_PKCOMP type otherwise returns error
    }

    l_i_Ret = MSO_Bio_Enroll( i_h_Mso100Handle,
                              0,                        //UC            i_uc_IndexDB,
                              i_us_Timeout,             //US            i_us_Timeout,
                              1,                        //UC            i_uc_EnrollmentType,
                              1,                        //UC            i_uc_NbFinger,
                              0,                        //UC            i_uc_SaveRecord,
                              i_uc_NormalizedPK_Type,   //UC            i_uc_NormalizedPK_Type,
                              0,                        //UC            i_uc_NbAddField,
                              NULL,    //PT_BUF        i_px_AddField,
                              i_ul_AsynchronousEvnt,    //UL 		i_ul_AsynchronousEvnt,
                              &l_x_ExportPk,            //PT_EXPORT_PK  io_px_ExportPk,      //can be NULL
                              NULL,                     //PT_EXPORT_IMAGE io_px_ExportImage, //can be NULL
                              &l_uc_EnrollStatus,       //PUC           o_puc_EnrollStatus,
                              &l_ul_UserDBIndex,        //PUL           o_pul_UserDBIndex,
                              &l_uc_Status              //PUC           o_puc_ILV_Status
                             );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Enroll -----> OK\n");
//        qDebug( "Enroll Status: %d\n", l_uc_EnrollStatus);
//        qDebug( "User Database Index: %ld\n", l_ul_UserDBIndex);
        if (l_px_ExportPk != NULL)
        {
            if(i_uc_NormalizedPK_Type == 0)
            {
                i_uc_NormalizedPK_Type = ID_PKCOMP;         // If i_uc_NormalizedPK_Type 0, we have to use normalisedpk as ID_PKCOMP (sagem default format). then only enrolled data verified & identified using ID_PKCOMP type otherwise returns error
            }

            i_px_Buf_PkSrc.m_x_Buf = *l_px_ExportPk->io_px_BiometricData;
            i_px_Buf_PkSrc.m_uc_IdPk = i_uc_NormalizedPK_Type;
            i_px_Buf_PkSrc.m_uc_Index = 0;

            if (l_px_ExportPk->io_px_BiometricData != NULL)
                    free (l_px_ExportPk->io_px_BiometricData);
        }
    }
    else
    {
        qDebug( "MSO_Bio_Enroll ret=%d status=0x%02X EnrollStatus=%d\n",
                                               l_i_Ret, l_uc_Status, l_uc_EnrollStatus);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        if (l_px_ExportPk->io_px_BiometricData != NULL)
                free (l_px_ExportPk->io_px_BiometricData);
        return false;
    }

    bool l_bool_ret = identify_mat(i_h_Mso100Handle, &i_px_Buf_PkSrc, lstbyt_PkRef, match_index, i_uc_NormalizedPK_Type);

    if (i_px_Buf_PkSrc.m_x_Buf.m_puc_Buf != NULL)
        free (i_px_Buf_PkSrc.m_x_Buf.m_puc_Buf);

    if(!l_bool_ret)
        return false;
    return true;
}



bool func_members::identify_mat(MORPHO_HANDLE i_h_Mso100Handle,
                                PT_BUF_PK i_px_Buf_PkSrc,
                                QList<QByteArray> *lstbyt_PkRef,
                                int *match_index,
                                UC i_uc_NormalizedPK_Type)
{
    *match_index = -1;
    I l_i_Ret, l_i_j, l_i_cnt;
    l_i_Ret = 0;
//    fprintf(stdout,"---Verifies if the input PkSrc matches against list of input PkRef---\n");
    I i_uc_NbPkRef = lstbyt_PkRef->size();

    if(i_uc_NbPkRef > 20)
        l_i_cnt = 20;
    else
        l_i_cnt = i_uc_NbPkRef;

    T_BUF_PK l_x_Buf_Pk[l_i_cnt];

    for (l_i_j = 0; l_i_j < l_i_cnt; l_i_j++)
    {
        l_x_Buf_Pk[l_i_j].m_x_Buf.m_ul_Size = 512;
        l_x_Buf_Pk[l_i_j].m_x_Buf.m_puc_Buf =(PUC) malloc (512);
        memset (l_x_Buf_Pk[l_i_j].m_x_Buf.m_puc_Buf, 0, 512);
    }

    QByteArray tempBarray;
    int cnt_no_data = 0, tmpcount = 0;
    l_i_j = 0;
    do
    {
        for(l_i_j = l_i_j; l_i_j<i_uc_NbPkRef; l_i_j ++)
        {
            if(cnt_no_data > 0)
            {
                l_x_Buf_Pk[ l_i_j- ((cnt_no_data * 20))].m_uc_IdPk = i_uc_NormalizedPK_Type;
                l_x_Buf_Pk[ l_i_j- ((cnt_no_data * 20))].m_uc_Index = 0;
                tempBarray = lstbyt_PkRef->at(l_i_j);
                for(tmpcount = 0 ; tmpcount<tempBarray.size(); tmpcount++)
                    l_x_Buf_Pk[l_i_j - ((cnt_no_data * 20))].m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)tempBarray.at(tmpcount);
                l_x_Buf_Pk[l_i_j - ((cnt_no_data * 20))].m_x_Buf.m_ul_Size = (UL) tempBarray.size();
                tempBarray.clear();

                if(((l_i_j + 1) - (cnt_no_data * 20)) == 20)
                {
                    qDebug()<<"loop break";
                    l_i_j ++;
                    break;
                }
            }
            else
            {
                l_x_Buf_Pk[ l_i_j].m_uc_IdPk =  i_uc_NormalizedPK_Type;
                l_x_Buf_Pk[ l_i_j].m_uc_Index = 0;
                tempBarray = lstbyt_PkRef->at(l_i_j);
                for(tmpcount = 0 ; tmpcount<tempBarray.size(); tmpcount++)
                    l_x_Buf_Pk[l_i_j].m_x_Buf.m_puc_Buf[tmpcount] = (unsigned char)tempBarray.at(tmpcount);
                l_x_Buf_Pk[l_i_j].m_x_Buf.m_ul_Size = (UL) tempBarray.size();
                tempBarray.clear();

                if(((l_i_j + 1) - (cnt_no_data * 20)) == 20)
                {
                    l_i_j ++;
                    break;
                }
            }
       }

        bool l_bool_Ret = VerifyMatch_custom(i_h_Mso100Handle, i_px_Buf_PkSrc,
                                     l_x_Buf_Pk, l_i_j - (cnt_no_data * 20),
                                     match_index);
        if(!l_bool_Ret)
        {
            l_i_Ret = -1;
            break;
        }
        else if(*match_index != -1)
        {
            *match_index = (cnt_no_data * 20) + *match_index;
            break;
        }
        cnt_no_data ++;
    }while(l_i_j < i_uc_NbPkRef);

    for (l_i_j = 0; l_i_j < l_i_cnt; l_i_j++)
    {
        if (l_x_Buf_Pk[l_i_j].m_x_Buf.m_puc_Buf != NULL)
        {
            free (l_x_Buf_Pk[l_i_j].m_x_Buf.m_puc_Buf);
        }
    }
    if(l_i_Ret == -1)
        return false;
    return true;
}

bool func_members::VerifyMatch_custom(MORPHO_HANDLE i_h_Mso100Handle,
                       PT_BUF_PK i_px_Buf_PkSrc,
                       PT_BUF_PK i_px_Buf_PkRef,
                       UC i_uc_NbPkRef, int *match_index)
{
    *match_index = -1;
    I l_i_Ret;
    UC		l_uc_MatchingResult;
    UC		l_uc_ListRefIndex;
    PUL		l_pul_Score;
    UC		l_uc_Status;
    UL		l_ul_Score = 0;

    if(g_uc_ExportScore)
        l_pul_Score = &l_ul_Score;
    else
        l_pul_Score = NULL;

    l_i_Ret = MSO_Bio_VerifyMatch( i_h_Mso100Handle,
                                   1,                       //UC        i_uc_NbPkSrc (must be set to 1)
                                   i_px_Buf_PkSrc,          //PT_BUF_PK i_px_PkSrc
                                   i_uc_NbPkRef,            //UC        i_uc_NbPkRef
                                   i_px_Buf_PkRef,  	    //PT_BUF_PK i_px_PkRef
                                   5,                       //US        i_us_MatchingTreshold,
                                   &l_uc_MatchingResult,    //PUC       o_puc_MatchingResult,
                                   &l_uc_ListRefIndex,      //PUC       o_puc_ListRefIndex,
                                   l_pul_Score,             //PUL       o_pul_score,
                                   &l_uc_Status             //PUC       o_puc_ILV_Status
                                 );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
//        qDebug( "Verify Match -----> OK\n");
//        qDebug("MatchingResult=%d score=%ld index=%d\n", l_uc_MatchingResult, l_ul_Score, l_uc_ListRefIndex);
        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
//            qDebug( "Verify Match OK--> index: %d\n", l_uc_ListRefIndex);
            *match_index = l_uc_ListRefIndex;
//            break;
        }
        else
            qDebug( "Verify Match KO: Not Identified !! \n");

    }
    else
    {
        qDebug( "MSO_Bio_VerifyMatch ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return false;
    }
    return true;
}
/***************************************************************************/
/*
*/
int func_members::ListDataBaseUser(MORPHO_HANDLE   i_h_Mso100Handle)
{
    I				   l_i_Ret;
    I				   l_i_i;
    UC				   l_uc_Status;
    UL				   ul_NbTransport;
    PT_TRANSPORT_PUBLIC_LIST_FIELD l_px_TransportPublicField;

    UC 				   l_uc_FingerNb;
    UC 				   l_uc_NormalizedPK_Type;
    UL 				   l_ul_MaxRecord;
    UL 				   l_ul_CurrentRecord;
    UL 				   l_ul_AddFieldNb;
    T_FIELD        		   l_x_BaseAddField[2];
    UL				   l_ul_EmbeddedError;

    // GetBaseConfig to get current number user in database
    memset((PC)&l_x_BaseAddField, 0, sizeof(l_x_BaseAddField));
    l_ul_AddFieldNb = 2;
    l_i_Ret = MSO_BioDB_GetBaseConfig( i_h_Mso100Handle,
                                       0,                           //UC              i_uc_IndexDB,
                                       &l_uc_FingerNb,              //PUC             o_puc_FingerNb,
                                       &l_ul_MaxRecord,             //PUL             o_pul_MaxRecord,
                                       &l_ul_CurrentRecord,         //PUL             o_pul_CurrentRecord,
                                       &l_ul_AddFieldNb,            //PUL             io_pul_AddFieldNb,
                                       (PT_FIELD)&l_x_BaseAddField, //PT_FIELD        o_px_AddField,
                                       &l_uc_NormalizedPK_Type,     //PUC             o_puc_NormalizedPK_Type,
                                       &l_uc_Status,                //PUC             o_puc_ILV_Status,
                                       &l_ul_EmbeddedError          //PUL             o_pul_EmbeddedError
                                     );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Current User Number in Database:%ld\n", l_ul_CurrentRecord);
    }
    else
    {
        qDebug( "MSO_BioDB_GetBaseConfig ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return -1;
    }


    ul_NbTransport = l_ul_CurrentRecord;	// Must be >= to number of current record in database.
                                                // Retrieve Current number with GetBaseConfig
    l_px_TransportPublicField = (PT_TRANSPORT_PUBLIC_LIST_FIELD) malloc(sizeof(T_TRANSPORT_PUBLIC_LIST_FIELD)*ul_NbTransport);
    if(l_px_TransportPublicField == NULL)
    {
        perror("error malloc");
        return -1;
    }
    memset(l_px_TransportPublicField, 0, sizeof(T_TRANSPORT_PUBLIC_LIST_FIELD)*ul_NbTransport);

    for(l_i_i=0;(unsigned) l_i_i<ul_NbTransport; l_i_i++)
    {
        l_px_TransportPublicField[l_i_i].m_puc_Data = (unsigned char*) malloc(128);
        if(l_px_TransportPublicField[l_i_i].m_puc_Data == NULL)
        {
            perror("error malloc");
            l_i_Ret = -1;
            break;
        }
        memset(l_px_TransportPublicField[l_i_i].m_puc_Data, 0, 128);
        l_px_TransportPublicField[l_i_i].m_ul_DataLenght = 128;
    }

    if(l_i_Ret == 0)
    {
        l_i_Ret = MSO_BioDB_GetPublicListData( i_h_Mso100Handle,
                                               0,			     //UC  i_uc_IndexDB,
                                               0,			     //UL  i_ul_UidData,
                                               &ul_NbTransport,	             //PUL io_pul_NbTranport,
                                               l_px_TransportPublicField,    //PT_TRANSPORT_PUBLIC_LIST_FIELD  io_ax_Strct,
                                               &l_uc_Status		     //PUC o_puc_ILV_Status
                                             );



        if(l_i_Ret==0 && l_uc_Status==0)
        {
            qDebug( "List User -----> OK\n");
            qDebug( "User Number: %ld\n", ul_NbTransport);
            for(l_i_i=0;(unsigned) l_i_i<ul_NbTransport; l_i_i++)
                qDebug( "\tIndex %ld: %s\n", l_px_TransportPublicField[l_i_i].m_ul_UserIndex,
                                                     l_px_TransportPublicField[l_i_i].m_puc_Data);
        }
        else
        {
            qDebug( "MSO_BioDB_GetPublicListData ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
            if(l_uc_Status != 0)
                ConvertError(l_uc_Status);
            l_i_Ret = -1;
        }
    }

    for(l_i_i=0;(unsigned) l_i_i<ul_NbTransport; l_i_i++)
    {
        if(l_px_TransportPublicField[l_i_i].m_puc_Data != NULL)
            free(l_px_TransportPublicField[l_i_i].m_puc_Data);
    }
    if(l_px_TransportPublicField != NULL)
        free(l_px_TransportPublicField);

    return l_i_Ret;
}


int AddBaseRecord( MORPHO_HANDLE   i_h_Mso100Handle,
                   PT_BUF_PK       i_px_Buf_Pk,
                   UC		   i_uc_NbPk)
{
    I	l_i_Ret;
    UC	l_uc_Status;
    UC	l_uc_BaseStatus;
    UL  l_ul_IndexUser;
    T_BUF       l_x_UserID;
    T_BUF       l_x_addField[2];

    UC          l_auc_UserID[25];
    UC          l_auc_AddField1[25];
    UC          l_auc_AddField2[25];

    qDebug( "---Add Base Record:---\n");

    qDebug( "Enter UserID:\n->");
    fgets((PC)l_auc_UserID, 25, stdin);
    l_auc_UserID[strlen((PC)l_auc_UserID)-1] = 0;               // Suppress '\n'

    qDebug( "Enter Additionnal field 1:\n->");
    fgets((PC)l_auc_AddField1, 25, stdin);
    l_auc_AddField1[strlen((PC)l_auc_AddField1)-1] = 0; // Suppress '\n'

    qDebug( "Enter Additionnal field 2:\n->");
    fgets((PC)l_auc_AddField2, 25, stdin);
    l_auc_AddField2[strlen((PC)l_auc_AddField2)-1] = 0; // Suppress '\n'

    l_x_UserID.m_ul_Size =  strlen((PC)l_auc_UserID)+1;
    l_x_UserID.m_puc_Buf = l_auc_UserID;

    l_x_addField[0].m_ul_Size = strlen((PC)l_auc_AddField1)+1;
    l_x_addField[0].m_puc_Buf = l_auc_AddField1;

    l_x_addField[1].m_ul_Size = strlen((PC)l_auc_AddField2)+1;
    l_x_addField[1].m_puc_Buf = l_auc_AddField2;

    l_i_Ret = MSO_BioDBAddBaseRecord( i_h_Mso100Handle,	//MORPHO_HANDLE          i_h_Mso100Handle,
                                      0,		//UC                     i_uc_IndexDB,
                                      i_uc_NbPk,	//UC                     i_uc_NbPk,
                                      i_px_Buf_Pk,	//PT_BUF_PK              i_px_Pk,
                                      &l_x_UserID,	//PT_BUF                 i_px_UserId,
                                      2,		//UC                     i_uc_NbAddField,
                                      (PT_BUF)&l_x_addField,	//PT_BUF                 i_px_AddField,
                                      &l_ul_IndexUser,  //PUL                    o_pul_IndexUser,
                                      &l_uc_Status,	//PUC                    o_puc_ILV_Status,
                                      &l_uc_BaseStatus, //PUC                    o_puc_Base_Status,
                                      0			//BOOL                   i_b_NoCheckOnTemplate
                                   );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Add Base Record -----> OK\n");
        qDebug( "User Index: %ld\n", l_ul_IndexUser);
    }
    else
    {
        qDebug( "MSO_BioDBAddBaseRecord ret=%d status=0x%02X BaseStatus=0x%02X\n", l_i_Ret, l_uc_Status, l_uc_BaseStatus);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }


    return l_i_Ret;
}


bool func_members::capture( MORPHO_HANDLE    i_h_Mso100Handle,
                            UL               i_ul_AsynchronousEvnt,
                            US               i_us_Timeout,
                            PT_EXPORT_PK     io_px_ExportPk,
                            PT_EXPORT_IMAGE  io_px_ExportImage )
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_EnrollStatus;
    UL		l_ul_UserDBIndex;

    l_i_Ret = MSO_Bio_Enroll( i_h_Mso100Handle,
                              0,                        //UC            i_uc_IndexDB,
                              i_us_Timeout,             //US            i_us_Timeout,
                              1,                        //UC            i_uc_EnrollmentType,
                              1,                        //UC            i_uc_NbFinger,
                              0,                        //UC            i_uc_SaveRecord,
                              0,                        //UC            i_uc_NormalizedPK_Type,
                              0,                        //UC            i_uc_NbAddField,
                              NULL,                     //PT_BUF        i_px_AddField,
                              i_ul_AsynchronousEvnt,    //UL            i_ul_AsynchronousEvnt,
                              io_px_ExportPk,           //PT_EXPORT_PK  io_px_ExportPk,      //can be NULL
                              io_px_ExportImage,        //PT_EXPORT_IMAGE io_px_ExportImage, //can be NULL
                              &l_uc_EnrollStatus,       //PUC           o_puc_EnrollStatus,
                              &l_ul_UserDBIndex,        //PUL           o_pul_UserDBIndex,
                              &l_uc_Status              //PUC           o_puc_ILV_Status
                             );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        qDebug( "Capture -----> OK\n");
    }
    else
    {
        qDebug( "MSO_Bio_Enroll ret=%d status=0x%02X EnrollStatus=%d\n",
                                               l_i_Ret, l_uc_Status, l_uc_EnrollStatus);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        return false;
    }

    return true;
}


/*************************************MSO_connect************************/


int func_members::MSO_Connect( MORPHO_HANDLE  *i_ph_Mso100Handle,
                                int i_i_ConnectionMode,		// COM_USB or COM_RS232
                                char * i_c_StrDevice,			// Serial port device /dev/ttyS0
                                int i_i_speed,				// Baud Rate
                                int *o_pi_IdProduct)			// Return type of product
{
        I                               l_i_Ret;
        I                               l_i_i;
        UL                              l_ul_NbDevice;
        PT_MSO_USB_DEVICE_PROPERTIES    l_px_Devices;
        struct usb_device               *dev;
        C                               l_ac_string[32];

        l_i_Ret = -1;
        l_px_Devices = NULL;
        dev = NULL;
        l_ul_NbDevice = 0;

        // Com USB
        if(i_i_ConnectionMode == 0)
        {
                if( strncmp(i_c_StrDevice, "/proc/bus/", 10) == 0 )
                {
                        qDebug( "Open device: %s\n", i_c_StrDevice);
                        l_i_Ret = MSO_InitCom(i_ph_Mso100Handle,(char *) COM_USB, i_c_StrDevice, i_i_speed);
                }
                else
                {
                        l_i_Ret = MSO_Usb_EnumDevices( &l_px_Devices, &l_ul_NbDevice);
                        if(l_i_Ret < 0)
                        {
                                qDebug( "Error USB Enum Devices\n");
                                return -1;
                        }

                        char l_c_tempstr[256];
                        sprintf(l_c_tempstr, "---List of connected devices (Number: %ld)---\n", l_ul_NbDevice);
                        qDebug()<<QString(l_c_tempstr);
                        for(l_i_i=0; l_i_i < (I)l_ul_NbDevice; l_i_i++)
                        {
                            sprintf(l_ac_string, "\t%d:  %s - %s\n", l_i_i, (l_px_Devices+l_i_i)->m_puc_FriendlyName, (l_px_Devices+l_i_i)->m_puc_SerialNumber);
                            qDebug()<<l_ac_string;
                        }

                        if(l_ul_NbDevice == 0)
                        {
                            qDebug( "No Usb device connected\n");
//                            l_i_Ret = MSO_Usb_ReleaseEnumDevices(&l_px_Devices, l_ul_NbDevice);
                            return -1;
                        }
                        if(l_ul_NbDevice == 1)
                        {
                                l_i_i = 0;
                                dev = l_px_Devices->m_px_device;
                        }
                        else if(l_ul_NbDevice>1)
                        {
                            l_i_i = 0;
                            dev = l_px_Devices->m_px_device;

//                    if multiple reader is available the following code will be used to give option to user to select one device to be used*****/
//                                qDebug( "Select -> ");
//                                while(1)
//                                {
//                                        if(fgets(l_ac_string, 32, stdin) == NULL)
//                                                qDebug( "->Error\n");
//                                        if(sscanf(l_ac_string, "%d", &l_i_i) == 1)
//                                        {
//                                                if(l_i_i >= 0 && (unsigned)l_i_i <l_ul_NbDevice)
//                                                        break;
//                                        }
//                                        qDebug( "Select -> ");
//                                }

//                                if((unsigned)l_i_i>=l_ul_NbDevice)
//                                        l_i_i = l_ul_NbDevice-1;
//                                dev = (l_px_Devices+l_i_i)->m_px_device;
                        }

                        qDebug( "Connect to %s - %s\n", (l_px_Devices+l_i_i)->m_puc_FriendlyName,
                                                                                (l_px_Devices+l_i_i)->m_puc_SerialNumber);

                        *o_pi_IdProduct = dev->descriptor.idProduct;
                        l_i_Ret = MSO_InitCom(i_ph_Mso100Handle,(char*) COM_USB, (PC)(l_px_Devices+l_i_i)->m_puc_SerialNumber, 0);
                        l_i_Ret = MSO_Usb_ReleaseEnumDevices(&l_px_Devices, l_ul_NbDevice);
                }
        }
        // Com RS232
        else if(i_i_ConnectionMode == 1)
        {
                l_i_Ret = MSO_InitCom(i_ph_Mso100Handle,(char *) COM_RS232, i_c_StrDevice, i_i_speed);
        }


        // Send Cancel and Clean buffer
        if(l_i_Ret == 0)
        {
                int nb_retry = 2;
                MSO_Cancel(*i_ph_Mso100Handle);
                while(nb_retry > 0)
                {
                        I l_i_RecvRet;
                        PUC l_puc_data = NULL;
                        UL l_ul_len = 0;
                        l_i_RecvRet = MSO_ComReceive( *i_ph_Mso100Handle,
                                                                                500,				//UL		i_ul_Timeout,
                                                                                &l_puc_data,		//PUC*		io_ppuc_Data,
                                                                                &l_ul_len			//PUL		o_pul_DataSize
                                                                                        );

                        //printf("MSO_ComReceive ret %d, read %ld\n", l_i_RecvRet, l_ul_len);
                        if(l_ul_len > 0)
                                MSO_FrameRelease(*i_ph_Mso100Handle, &l_puc_data);

                        if(l_ul_len == 0)
                                nb_retry--;
                }
        }

        return l_i_Ret;
}


/*****************************MSO_ERRORS********************************/
typedef struct
{
        UC	m_uc_ErrorCode;
        UC  m_auc_ErrorString[256];
} T_ERROR_TABLE;

// Error Table with string explanation
T_ERROR_TABLE g_x_ErrorTable[] =
                {
                        { ILV_OK,                               "Successful result "},								 		// 0x00
                        { ILVERR_ERROR,                         "An error occurred" },										// 0xFF
                        { ILVERR_BADPARAMETER,			"Input parameters are not valid" }, 						// 0xFE
                        { ILVERR_INVALID_MINUTIAE,		"The minutiae is not valid" },      				 		// 0xFD
                        { ILVERR_INVALID_USER_ID,		"The record identifier does not exist in the database" },	// 0xFC
                        { ILVERR_INVALID_USER_DATA,		"The user data are not valid" },    			 			// 0xFB
                        { ILVERR_TIMEOUT,                       "No response after defined time" }, 						// 0xFA
                        { ILVERR_INVALID_ID_PROTOCOL,           "The protocole used is not valid" },						// 0xF9
                        { ILVERR_ALREADY_ENROLLED,		"The person is already in the base"},						// 0xF8
                        { ILVERR_BASE_NOT_FOUND,		"The specified base does not exist"},   					// 0xF7
                        { ILVERR_BASE_ALREADY_EXISTS,           "The specified base already exist"},    					// 0xF6
                        { ILVERR_BIO_IN_PROGRESS,		"Command received during biometric processing"},			// 0xF5
                        { ILVERR_CMD_INPROGRESS,		"Command received while another command is running"},		// 0xF4
                        { ILVERR_FLASH_INVALID,			"Flash type invalid" },										// 0xF3
                        { ILVERR_NO_SPACE_LEFT,			"Not Enough memory for the creation of a database" },		// 0xF2
                        { ILVERR_FIELD_NOT_FOUND, 		"Field does not exist"  },   								// 0xE9
                        { ILVERR_FIELD_INVALID,  		"Field size or field name is invalid"  },					// 0xE8
                        { ILVERR_SECURITY_MODE,  		"The request is not compatible with security mode" },		// 0xE7
                        { ILVERR_USER_NOT_FOUND, 		"The searched user is not found" },							// 0xE6
                        { ILVERR_CMDE_ABORTED,   		"Command has been aborted by the user" },					// 0xE5
                        { ILVERR_SAME_FINGER,   		"There are two templates of the same finger" },				// 0xE4
                        { ILVERR_NO_HIT,                        "Presented finger does not match" },						// 0xE3
                        { ILVERR_FFD,                           "False finger detected"},									// 0xDB
                        { ILVERR_MOIST_FINGER,			"Too moist finger detected" },								// 0xDA
                };

UL	g_ul_NbError = sizeof(g_x_ErrorTable)/sizeof(T_ERROR_TABLE);

/*****************************************************************************/
/*****************************************************************************/
int func_members::ConvertError(UC i_uc_Status)
{
        int l_i_i;
        char l_c_string[256];

        for(l_i_i=0; (unsigned)l_i_i<g_ul_NbError; l_i_i++)
        {
                if(g_x_ErrorTable[l_i_i].m_uc_ErrorCode == i_uc_Status)
                {
                    sprintf (l_c_string,
                            "Error: %s",
                            g_x_ErrorTable[l_i_i].m_auc_ErrorString);
                    strFPlastError = l_c_string;
                    qDebug()<<strFPlastError;
                    break;
                }
        }

        if( (unsigned) l_i_i == g_ul_NbError)
        {
            sprintf (l_c_string,
                    "Error 0x%02X: Unknown error ",
                    i_uc_Status);
            strFPlastError = l_c_string;
            qDebug()<<strFPlastError;
            return -1;
        }

        return 0;
}

QByteArray func_members::Format_Image(unsigned char *image_dat, int width, int height, int header)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);
    uint ValidByt;
    int nlen, Max;
    bool OK=true;
    QString HeaderInfo;

    Max = width * height;
    BMPHeader bmpHeader;
    bmpHeader.Size=0;
    bmpHeader.Reserved=0;
    bmpHeader.Offset=1078;
    bmpHeader.header_sz=40;
    bmpHeader.width=width;
    bmpHeader.height=height;
    bmpHeader.nplanes=1;
    bmpHeader.bitspp=8;
    bmpHeader.compress_type=0;
    bmpHeader.bmp_bytesz=0;
    bmpHeader.hres=0;
    bmpHeader.vres=0;
    bmpHeader.ncolors=256;
    bmpHeader.nimpcolors=256;
HeaderInfo="424D" +Reverse(QString::number(bmpHeader.Size,16).rightJustified(sizeof(bmpHeader.Size)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.Reserved,16).rightJustified(sizeof(bmpHeader.Reserved)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.Offset,16).rightJustified(sizeof(bmpHeader.Offset)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.header_sz,16).rightJustified(sizeof(bmpHeader.header_sz)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.width,16).rightJustified(sizeof(bmpHeader.width)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.height,16).rightJustified(sizeof(bmpHeader.height)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.nplanes,16).rightJustified(sizeof(bmpHeader.nplanes)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.bitspp,16).rightJustified(sizeof(bmpHeader.bitspp)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.compress_type,16).rightJustified(sizeof(bmpHeader.compress_type)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.bmp_bytesz,16).rightJustified(sizeof(bmpHeader.bmp_bytesz)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.hres,16).rightJustified(sizeof(bmpHeader.hres)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.vres,16).rightJustified(sizeof(bmpHeader.vres)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.ncolors,16).rightJustified(sizeof(bmpHeader.ncolors)*2,'0').toUpper())
        + Reverse(QString::number(bmpHeader.nimpcolors,16).rightJustified(sizeof(bmpHeader.nimpcolors)*2,'0').toUpper());
    nlen=HeaderInfo.length();
    for(int i = 0; i<(nlen-1);i+=2)
    {
        ValidByt  = HeaderInfo.mid(i, 2).toInt(&OK,16);
        out<<(quint8)ValidByt;
    }

//ColorInfo 1024 bytes
    for(int i = 0;i<=255;i++)
    {
        out<<(quint8) i;
        out<<(quint8) i;
        out<<(quint8) i;
        out<<(quint8) 0;
    }
    //PIXELS

    if(header >0)
    {
        for(int lX = 0 + (header - width ) ; lX< Max;lX++)
        {
            out<<(quint8) image_dat[lX];
        }
    }
    else
    {
        for(int lX = 0; lX<Max;lX++)
        {
            out<<(quint8) image_dat[lX];
        }
    }
    return data;
}
