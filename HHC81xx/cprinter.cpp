#include "cprinter.h"
#include <QMessageBox>
#include <QVariant>
#include "cglobal.h"

using namespace ClanCor;
using namespace Global;

CPheripherals *pheripheralsPIC = NULL;

CPrinter::CPrinter()
{
    m_listDatas.clear();
    if ( NULL == gpheripheralsPIC ) {
        if ( gsharedMemPIC.attach() ) {
            /* do the process for not first application call */
            gbFirsCall = false;
            gLoadIntoSharedPIC(const_strSTARTED);
            pheripheralsPIC = new CPheripherals(COPROCESSOR_PORTNAME);
            gpheripheralsPIC = pheripheralsPIC;
            gLoadIntoSharedPIC(const_strCOMPLETED);
        }
    }
    m_bNativeLanguage = false;
}

CPrinter::~CPrinter()
{
    m_listDatas.clear();
    if ( NULL != pheripheralsPIC ) {
        if(!gsharedMemPIC.detach())
        {
            qDebug()<<"\Error while detaching shared memory..";
        }
        delete pheripheralsPIC;
        pheripheralsPIC = NULL;
        gpheripheralsPIC = NULL;
    }
}

void CPrinter::setNativeLanguage(E_NativeLanguage e_NativeLanguage)
{
    m_eNativeLanguage = e_NativeLanguage;
    switch ( (int) e_NativeLanguage ) {
    case e_NativeLanguage_NONE :
         m_stringNativeLanguage = "00";
         break;
    case e_NativeLanguage_TAMIL :
         m_stringNativeLanguage = "01";
         break;
    case e_NativeLanguage_MALAYALAM :
         m_stringNativeLanguage = "02";
         break;
    case e_NativeLanguage_KANNADA :
         m_stringNativeLanguage = "03";
         break;
    case e_NativeLanguage_TELUGU :
         m_stringNativeLanguage = "04";
         break;
    case e_NativeLanguage_HINDI :
         m_stringNativeLanguage = "05";
         break;
    case e_NativeLanguage_BENGALI :
         m_stringNativeLanguage = "06";
         break;
    case e_NativeLanguage_SINGALAM :
         m_stringNativeLanguage = "07";
         break;
    }
    if(m_stringNativeLanguage != "" && m_stringNativeLanguage != "00")
    {
        m_bNativeLanguage = true;
    }
    else
    {
        m_bNativeLanguage = false;
    }
}

QString CPrinter::ToUtf16_Printable(const QString &r_const_strDATA)
{
    QByteArray bytearrayPrintDataUtf16, bytearrayPrintDataUtf8;
    bytearrayPrintDataUtf8 = QByteArray(r_const_strDATA.toAscii());
    const int const_nUTF16BitShiftValByte1 = 4, const_nUTF16BitShiftValByte2 = 2, const_nUTF16BitShiftValByte3 = 2;
    const int const_nStartCharAscii = 32, const_nEndCharAscii = 122;
    const unsigned char const_ByteAllBitsHigh = 0xFF;
    int nCharCount = 0;
    unsigned char ucByteUtf8to16[3], ucCurrentChar, ucByte1Utf16Result, ucByte2Utf16Result;

    while( nCharCount < bytearrayPrintDataUtf8.size())
    {
        ucCurrentChar = bytearrayPrintDataUtf8.at(nCharCount);

        /* Condition to check English characters & symbols from space character( ascii 32) to small z (ascii 122) */
        if(((int)ucCurrentChar >= const_nStartCharAscii) && ((int)ucCurrentChar <= const_nEndCharAscii))
        {
            if((m_eNativeLanguage == CPrinter::e_NativeLanguage_MALAYALAM) && (m_bNativeLanguage))
            {
                /* if malayalam, need to add value 0x60 with the hex value of common English characters & symbols, to avoid confusions of Malayalam & English character unicodes */
                bytearrayPrintDataUtf16.append(QByteArray::fromHex(QByteArray((const char*)&ucCurrentChar, 1).toHex()).at(0) + 0x60);
            }
            else if((m_eNativeLanguage == CPrinter::e_NativeLanguage_HINDI) && (m_bNativeLanguage))
            {
                /* if Hindi, need to add value 0x80 with the hex value of common English characters & symbols, to avoid confusions of Hindi & English character unicodes */
                bytearrayPrintDataUtf16.append(QByteArray::fromHex(QByteArray((const char*)&ucCurrentChar, 1).toHex()).at(0) + 0x80);
            }
            else if((m_eNativeLanguage == CPrinter::e_NativeLanguage_TELUGU) && (m_bNativeLanguage))
            {
                /* if Telugu, need to add value 0x80 with the hex value of common English characters & symbols, to avoid confusions of Telugu & English character unicodes */
                bytearrayPrintDataUtf16.append(QByteArray::fromHex(QByteArray((const char*)&ucCurrentChar, 1).toHex()).at(0) + 0x80);
            }
            else
            {
                bytearrayPrintDataUtf16.append(QByteArray::fromHex(QByteArray((const char*)&ucCurrentChar, 1).toHex()));
            }
            nCharCount++;
        }
        else
        {
            /* UTF-8 to UTF-16 conversion algorithm
                        UTF-16  |<-----------UTF-8------------>|
               Bits              Byte1       Byte2       Byte3
               ----------------------------------------------------------
               16	U+XXXX	 1110XXXX    10XXXXXX    10XXXXXX

               By removing the above mentioned bits from Byte-1,2 & 3 of UTF-8 value. the remaining 16 bits (x's) forms UTF-16 value.
               [NOTE: The above mentioned bits to remove are common for all languages represented in UTF-8 format]
            */
            /* Assign 3 byte UTF-8 data into array ucByteUtf8to16 [] */
            ucByteUtf8to16[0] = bytearrayPrintDataUtf8.at(nCharCount);
            ucByteUtf8to16[1] = bytearrayPrintDataUtf8.at(nCharCount + 1);
            ucByteUtf8to16[2] = bytearrayPrintDataUtf8.at(nCharCount + 2);

            /* Left shift 4 bits to remove value 1000 from first byte, then right shift 4 bits then AND with 0xFF to get 1 Byte actual value. (eg: if actual value in first byte is 10001010, then result of below line is 00001010) */
            ucByteUtf8to16[0] = (((ucByteUtf8to16[0] << const_nUTF16BitShiftValByte1) & const_ByteAllBitsHigh) >> const_nUTF16BitShiftValByte1 & const_ByteAllBitsHigh);
            /* Left shift 2 bits to remove value 10 from second byte, then right shift 2 bits then AND with 0xFF to get 1 Byte actual value. (eg: if actual value in second byte is 10101010, then result of below line is 00101010) */
            ucByteUtf8to16[1] = (((ucByteUtf8to16[1] << const_nUTF16BitShiftValByte2) & const_ByteAllBitsHigh) >> const_nUTF16BitShiftValByte2 & const_ByteAllBitsHigh);
            /* Left shift 2 bits to remove value 10 from third byte, then right shift 2 bits then AND with 0xFF to get 1 Byte actual value. (eg: if actual value in third byte is 10101010, then result of below line is 00101010) */
            ucByteUtf8to16[2] = (((ucByteUtf8to16[2] << const_nUTF16BitShiftValByte3) & const_ByteAllBitsHigh) >> const_nUTF16BitShiftValByte3 & const_ByteAllBitsHigh);

            /*To take first byte of hex value from 2 byte UTF16 Unicode (eg) 0xC5 from 0x05C5*/

            /* Left Shift 6 bits to remove first 6 bits value from the second byte,
                then AND with 0xFF to get actual value.
                (eg : if actual value in second byte is 00101010, then result of below line is 10000000) */
            ucByte1Utf16Result = ((ucByteUtf8to16[1] << 6) & const_ByteAllBitsHigh);
            /* OR right shifted second byte result with third byte to get first byte of UTF-16, then append it into the byte array. (eg : if actual value in second byte is 10000000 and in third byte is 00101010, then result of below line is 10101010) */
            ucByte1Utf16Result = ucByte1Utf16Result | ucByteUtf8to16[2];

            /* To identify zero width joiner & non zero width joiner */
            if((m_eNativeLanguage == CPrinter::e_NativeLanguage_MALAYALAM) && ((ucByte1Utf16Result == 0x0C) || (ucByte1Utf16Result == 0x0D)))
            {
                ///To take second byte of hex value from 2 byte UTF16 Unicode (eg) 0x05 from 0x05C5

                /* Right shift 2 bits to remove first 2 bits value from the second byte, then AND with 0xFF to get actual value. (eg : if actual value in second byte is 00101010, then result of below line is 00001010) */
                ucByte2Utf16Result = ((ucByteUtf8to16[1] >> const_nUTF16BitShiftValByte2) & const_ByteAllBitsHigh);
                /* OR right shifted second byte result with first byte to get second byte of UTF-16. (eg : if actual value in second byte is 00001010 and in first byte is 10000000, then result of below line is 10001010) */
                ucByte2Utf16Result = ucByte2Utf16Result | ((ucByteUtf8to16[0] << const_nUTF16BitShiftValByte1) & const_ByteAllBitsHigh);

                /* To Identify if the UTF16 character is 0x200D or 0x200C */
                if(ucByte2Utf16Result == 0x20)
                {
                    /* Need to add value 0x60 with the hex value of UTF16 first byte, if it is one of the characters mentioned above*/
                    ucByte1Utf16Result = ucByte1Utf16Result + 0x60;
                }
            }

            /* Append converted UTF16 first byte into the byte array. */
            bytearrayPrintDataUtf16.append(ucByte1Utf16Result);
            /* Increment count value by 3, because native language's one character is represented by 3 byte UTF8 value */
            nCharCount += 3;
        }
    }
    return QString::fromLatin1(bytearrayPrintDataUtf16).toAscii().toHex().toUpper();
}

void CPrinter::paperFeed(int n_MM)
{
    m_listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_FEED, gAlignNumber(n_MM,2)));
}

void CPrinter::addData(const QString &r_const_strDATA, E_FontSize eFontSize, E_FontStyle eFontStyle, E_Alignment eAlign, bool bUnderLine)
{
    QChar cFontSize, cAlignment, cUnderline;
    QString cFontStyle;
    switch ( (int) eFontSize ) {
        case eFontSize_SMALL :
            cFontSize = 's';
            break;
        case eFontSize_MEDIUM :
            cFontSize = 'm';
            break;
        default:
            cFontSize = 'b';
    }
    switch ( (int) eFontStyle ) {
        case eFontStyle_REGULAR :
            cFontStyle = "00";
            break;
        case eFontStyle_BOLD :
            cFontStyle = "10";
            break;
        case eFontStyle_ITALIC :
            cFontStyle = "01";
            break;
        default:
            cFontStyle = "11";
    }
    switch ( (int) eAlign ) {
        case eAlignment_LEFT :
            cAlignment = 'l';
            break;
        case eAlignment_CENTER :
            cAlignment = 'c';
            break;
        default:
            cAlignment = 'r';
    }
    if ( bUnderLine ) {
        cUnderline = '1';
    }
    else {
        cUnderline = '0';
    }

    /* split the data it contains '\n' */
    QList<QString> listDatas= r_const_strDATA.split('\n');
    QString strData;
    foreach ( strData, listDatas ) {
        /* add data one by one */
        if ( strData.trimmed() == "" ) {
            if(m_bNativeLanguage)
            {
                strData = ToUtf16_Printable(strData.trimmed() + "  ");
                m_listDatas.append(strData.trimmed() + "ls" + m_stringNativeLanguage.simplified() + "000" + const_StringNativeData_EOP);
            }
            else
            {
                m_listDatas.append(strData.trimmed() + "  ls000");
            }
        }
        else {
            // m_listDatas.append( CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_DATA ,r_const_strDATA));
            /* increase speed */
            if(m_bNativeLanguage)
            {
                strData = ToUtf16_Printable(strData.trimmed() + "  ");           //Added two space char's to seperate data from end of packet, which is used to identify native data to check for addition of language offset
                m_listDatas.append(strData.trimmed() + cAlignment + cFontSize + m_stringNativeLanguage + cFontStyle + cUnderline + const_StringNativeData_EOP);

                /*temperary logic to print Tamil Lang*/
//                strData = strData.toAscii().toHex().replace("e0ae", "").replace("e0af8", "c").replace("e0af9", "d").replace("e0afa", "e").replace("e0afb", "f").toUpper();
            }
            else
            {
                m_listDatas.append(strData.trimmed() + "  " + cAlignment + cFontSize + cFontStyle + cUnderline );
            }
        }
        strData.clear();
    }
}

void CPrinter::addNumber_bigFont(const QString &r_const_strDATA)
{

    m_listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER , const_cPACKETID_PRINT_NUMBER,
                                                 r_const_strDATA));
}

void CPrinter::addBarcode(const QString &r_const_strDATA, E_FontSize eFontSize)
{
    QChar cFontSize;
    switch ( (int) eFontSize ) {
        case eFontSize_BIG :
            cFontSize = 'b';
            break;
        case eFontSize_MEDIUM :
            cFontSize = 'm';
            break;
        default:
            cFontSize = 's';
    }
    m_listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER , const_cPACKETID_PRINT_BARCODE,
                                                 r_const_strDATA + const_cBARCODE_CODE128 + const_cBARCODE_CODEB + cFontSize));
}

void CPrinter::addImage(const QImage &r_const_imagePRINT, bool bDithering,E_ImageBrightness e_ImageBrightness)
{
    switch(e_ImageBrightness)
    {
    case 0:
        gstrImageBrightness="L";
        break;
    case 1:
        gstrImageBrightness="H";
        break;
    }

    if ( bDithering ) {
        m_listImages.append(r_const_imagePRINT.convertToFormat(QImage::Format_MonoLSB,Qt::MonoOnly|Qt::OrderedAlphaDither|Qt::PreferDither));
    }
    else {
        m_listImages.append(r_const_imagePRINT.convertToFormat(QImage::Format_Mono));
    }
    m_listDatas.append("image");
}

void CPrinter::drawLine()
{
    m_listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER ,const_cPACKETID_DRAW_LINE ,""));
}

void CPrinter::clear()
{
    /* clear the buffer */
    m_listDatas.clear();
    m_listImages.clear();
}

bool CPrinter::print(bool bHeader,bool bFooter) const
{
    const int const_nPAPER_FEED = 7 ;
    bool bResponse = false;
    QList<QString> listDatas;
    if ( m_listDatas.count() == 0 ) {
        return false;
    }
    listDatas = m_listDatas;
    gLoadIntoSharedPIC(const_strSTARTED);
    if ( bHeader ) {
        /* print the header image which is loaded */
        listDatas.insert(0,CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_HEADER_FOOTER , QString(const_cHEADER_IMAGE_DATA)));
    }
    if ( bFooter ) {
        /* print the footer image which is loaded */
        listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PRINT_HEADER_FOOTER , QString(const_cFOOTER_IMAGE_DATA)));
    }
    else
    {
        /* add End of print data */
        listDatas.append( const_StringEndOfPrint );
    }
    if (! gstrDeviceModel.contains("HHC-7") ) {
        /* add paper feed at end of print to bring out paper*/
        listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_FEED, gAlignNumber(const_nPAPER_FEED,2)));
    }
    else
    {
        /* add paper feed at end of print to bring out paper*/
//        listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_FEED, gAlignNumber(const_nPAPER_FEED+7,2)));
        listDatas.append(CPheripherals::formPacket(const_cPHERIPHERAL_PRINTER, const_cPACKETID_PAPER_FEED, gAlignNumber(1,2)));
    }
    bResponse = gpheripheralsPIC->printData(listDatas,m_listImages);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    listDatas.clear();
    return bResponse;
}

bool CPrinter::loadHeaderImage(const QImage &r_const_imageHEADER) const
{
    bool bResponse = false;
    if ( ( NULL == gpheripheralsPIC ) && ( NULL == gpheripheralsPIC ) ) {
        pheripheralsPIC = new CPheripherals(COPROCESSOR_PORTNAME);
        gpheripheralsPIC = pheripheralsPIC;
    }
    QString strSharedMemData;
    int nCount = 0;
    bool bSharedMemRunning = false;
    do {
        /* read the data after wait 50 milli seconds to check paused */
        if(nCount != 0)
        {
            gUpdateScreen(100);
        }
        nCount ++;
        /*Read current data from PIC chared Memory */
        gLoadFromSharedPIC(strSharedMemData);
        if(strSharedMemData.trimmed() == const_strRUNNING)
        {
            bSharedMemRunning = true;
        }
    } while ( (!bSharedMemRunning) && nCount < 20 );
    if(bSharedMemRunning)
    {
        gLoadIntoSharedPIC(const_strSTARTED);
    }
    else
    {
        return false;
    }
    bResponse = gpheripheralsPIC->loadHeaderImage(r_const_imageHEADER);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CPrinter::loadFooterImage(const QImage &r_const_imageFOOTER) const
{
    bool bResponse = false;
    if ( ( NULL == gpheripheralsPIC ) && ( NULL == gpheripheralsPIC ) ) {
        pheripheralsPIC = new CPheripherals(COPROCESSOR_PORTNAME);
        gpheripheralsPIC = pheripheralsPIC;
    }
    QString strSharedMemData;
    int nCount = 0;
    bool bSharedMemRunning = false;
    do {
        /* read the data after wait 50 milli seconds to check paused */
        if(nCount != 0)
        {
            gUpdateScreen(100);
        }
        nCount ++;
        /*Read current data from PIC chared Memory */
        gLoadFromSharedPIC(strSharedMemData);
        if(strSharedMemData.trimmed() == const_strRUNNING)
        {
            bSharedMemRunning = true;
        }
    } while ( (!bSharedMemRunning) && nCount < 20 );
    if(bSharedMemRunning)
    {
        gLoadIntoSharedPIC(const_strSTARTED);
    }
    else
    {
        return false;
    }
    bResponse = gpheripheralsPIC->loadFooterImage(r_const_imageFOOTER);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CPrinter::testPrinter() const
{
    bool bResponse = false;
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->testPrinter();
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}

bool CPrinter::paperStatus(bool &r_const_bPaperAvailable) const
{
    bool bResponse = false;
    gLoadIntoSharedPIC(const_strSTARTED);
    bResponse = gpheripheralsPIC->checkPaperStatus(r_const_bPaperAvailable);
    gLoadIntoSharedPIC(const_strCOMPLETED);
    return bResponse;
}
