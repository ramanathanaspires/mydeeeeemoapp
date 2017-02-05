#ifndef CFP_API_MORPHO_H
#define CFP_API_MORPHO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

class CFP_API_Morpho : public QWidget
{
    Q_OBJECT

public:
    explicit CFP_API_Morpho(QWidget *parent = 0);
    ~CFP_API_Morpho();

//    bool showWidget();
//    int CommandCallback (void* i_pv_context, int i_i_command, void* i_pv_param);

private:
    QLabel lbl_fingerinfo;
    QLabel lbl_fingerstat;
    QLabel lbl_fingerimage;
    QPushButton pBtn_close;
    QByteArray FP_sample;

    void keyPressEvent(QKeyEvent *);

private slots:


private slots:
    void on_pushButton_clicked();
};

#include <QLabel>
#include <QString>

#include "libMSO.h"
#include "Ilv_definitions.h"
#define MSO_TEST_BIO_VERSION	"1.0"

#define DEFAULT_SERIAL_PORT		"/dev/ttyS0"
#define DEFAULT_BAUD_RATE		115200


#define CORRECT_LEVEL2(a)	if (a == 0x00)	   \
                                                                a = 0x02;      \
                                                        else if (a == 0x40)\
                                                                a = 0x48;      \
                                                        else if (a == 0x80)\
                                                                a = 0xB0;      \
                                                        else if (a == 0xC0)\
                                                                a = 0xFE;      \

#define CORRECT_LEVEL1(a)	if (a == 0x00)     \
                                                                a = 0x00;      \
                                                        else if (a == 0x80)\
                                                                a = 0xFF;      \





namespace func_members
{

    int MSO_Connect( MORPHO_HANDLE * i_h_Mso100Handle,
                                     int i_i_ConnectionMode,	// COM_USB or COM_RS232
                                     char *i_c_StrDevice,	// Serial port device /dev/ttyS0
                                     int i_i_speed,	// Baud Rate
                                     int *o_pi_IdProduct	// Return type of product
                                    );



    int ConvertError(UC i_uc_Status);

    int DeleteUserIndex(MORPHO_HANDLE i_h_Mso100Handle);
    int DeleteAllUser(MORPHO_HANDLE i_h_Mso100Handle);
    int DestroyDatabase(MORPHO_HANDLE i_h_Mso100Handle);
    int CreateDataBase(MORPHO_HANDLE i_h_Mso100Handle);
    int GetBaseConfig(MORPHO_HANDLE i_h_Mso100Handle);

    int ListDataBaseUser(MORPHO_HANDLE   i_h_Mso100Handle);

    bool VerifyMatch(MORPHO_HANDLE i_h_Mso100Handle,
                                    PT_BUF_PK i_px_Buf_PkSrc,
                                    PT_BUF_PK i_px_Buf_PkRef,
                                    UC i_uc_NbPkRef);

    bool Identify_custom(MORPHO_HANDLE i_h_Mso100Handle,
                                    QList<QByteArray> *lstbyt_PkRef,
                                    UL i_ul_AsynchronousEvnt,
                                    US i_us_Timeout, int *match_index,
                                    UC i_uc_NormalizedPK_Type);

    bool VerifyMatch_custom(MORPHO_HANDLE i_h_Mso100Handle,
                           PT_BUF_PK i_px_Buf_PkSrc,
                           PT_BUF_PK i_px_Buf_PkRef,
                           UC i_uc_NbPkRef, int *match_index);

    bool identify_mat(MORPHO_HANDLE i_h_Mso100Handle,
                      PT_BUF_PK i_px_Buf_PkSrc,
                      QList<QByteArray> *lstbyt_PkRef,
                      int *match_index,
                      UC i_uc_NormalizedPK_Type);

    int IdentifyMatch(MORPHO_HANDLE i_h_Mso100Handle, PT_BUF_PK i_px_Buf_Pk);

    bool Verify(MORPHO_HANDLE i_h_Mso100Handle,
               PT_BUF_PK i_x_Buf_Pk,
               UC i_uc_NbFinger, UL i_ul_AsynchronousEvnt, US i_us_Timeout);

    int Identify(MORPHO_HANDLE i_h_Mso100Handle, UL i_ul_AsynchronousEvnt, US i_us_Timeout);

    bool EnrollUser( MORPHO_HANDLE i_h_Mso100Handle,
                                    UL i_ul_AsynchronousEvnt,
                                    US i_us_Timeout,
                                    PT_EXPORT_PK io_px_ExportPk,	//can be NULL
                                    PT_EXPORT_IMAGE io_px_ExportImage,	//can be NULL
                                    UC i_uc_NormalizedPK_Type);

    bool capture( MORPHO_HANDLE                  i_h_Mso100Handle,
                             UL                 i_ul_AsynchronousEvnt,
                             US                 i_us_Timeout,
                             PT_EXPORT_PK       io_px_ExportPk,
                             PT_EXPORT_IMAGE    io_px_ExportImage );



    I Display_Image (PUC i_puc_Img, US i_us_NbRow, US i_us_NbCol,
                    UC i_uc_NbBitsPerPixel);
    I SaveBufInFile (PT_BUF i_px_Buf, PC i_pc_Ext);
    I SaveImgBufInFile(PT_BUF i_px_Buf, int width, int height, int header);
    I OpenPkFile (PT_BUF_PK i_px_Buf_Pk, PC i_pc_String);
    I OpenImgFile (PUC i_puc_Img, I i_i_SizeBuf);
    I ConvertImage(	PUC i_puc_Img,
                                    US i_us_NbRow,
                                    US i_us_NbCol,
                                    UC i_uc_NbBitsPerPixel,
                                    PUC o_puc_Img8BitsPerPixel);

    extern UC g_uc_ExportScore;
    extern QLabel *lbl_fingstat, *lbl_finginfo, *lbl_image;
    extern QString strFPlastError;
    extern int FingerMatch;

    QByteArray Format_Image(unsigned char* image_dat, int width, int height, int header);

    /*************connect***************/}

#endif // CFP_API_MORPHO_H
