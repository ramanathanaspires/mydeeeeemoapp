/*********************************************************************************
 The API calls used in this source file are referred from NFC forum,
            for more information...
   -----http://www.libnfc.org/documentation/api
   -----http://www.libnfc.org/download
***********************************************************************************/

#include "nfc_api.h"
using namespace global_NFC;
#include <QDebug>
#include <QMutex>

using namespace std;

nfc_device_t *global_NFC::pndg = 0;
QString global_NFC::g_str_lastError = 0;


int global_NFC::connectNFC(QString *Reader)
{
    nfc_device_t *pnd;

//----- Connect using the first available NFC device
    pnd = nfc_connect (NULL);

    if (pnd == NULL) {
        g_str_lastError  =  "Unable to connect to NFC device.";
        return EXIT_FAILURE;
    }

    pndg = pnd;

//----- Set connected NFC device to initiator mode
    nfc_initiator_init (pnd);

//----- Let the reader only try once to find a tag
    if (!nfc_configure (pnd, NDO_INFINITE_SELECT, false)) {
        const char *l_c_err = nfc_strerror(pnd);
        g_str_lastError = QString::fromLatin1(l_c_err);
        return EXIT_FAILURE;
    }

    qDebug ("Connected to NFC reader: %s\n", pnd->acName);
    *Reader = QString(pnd->acName);

    return EXIT_SUCCESS;
}

bool global_NFC::nfcReadUID(QString *atr, QString *uid, QString *cardstat)
{
    QString l_str_hex;
    nfc_target_t ntt;

//----- List for a ISO14443A (MIFARE) tag
    nfc_modulation_t nm;
    nm.nmt = NMT_ISO14443A,
    nm.nbr = NBR_106;

//----- Enable field so more power consuming cards can power themselves up
    nfc_configure (pndg, NDO_ACTIVATE_FIELD, true);

//----- to List ISO14443A targets
    if ( nfc_initiator_select_passive_target (pndg, nm, NULL, 0, &ntt )) {
        *cardstat = "(NFC) ISO14443A tag was found";
//        qDebug ("The following (NFC) ISO14443A tag was found:\n");
        l_str_hex = print_hex (ntt.nti.nai.abtAtqa, 2);
//        qDebug ("    ATQA (SENS_RES): " + l_str_hex.toLatin1());
        l_str_hex = print_hex (ntt.nti.nai.abtUid, ntt.nti.nai.szUidLen);
        *uid = l_str_hex;
//        qDebug ("       UID (NFCID%c): " + l_str_hex.toLatin1(), (ntt.nti.nai.abtUid[0] == 0x08 ? '3' : '1'));
        l_str_hex = print_hex (&ntt.nti.nai.btSak, 1);
//        qDebug ("      SAK (SEL_RES): " + l_str_hex.toLatin1());
        if (ntt.nti.nai.szAtsLen) {
            l_str_hex = print_hex (ntt.nti.nai.abtAts, ntt.nti.nai.szAtsLen);
            *atr = l_str_hex;
//            qDebug ("          ATS (ATR): " + l_str_hex.toLatin1());
        }
    }
    else
    {
        if(pndg->iLastError != 0)
        {
            switch(pndg->iLastError)
            {
            case 0x0100:
                g_str_lastError = "Device level error - NACK";
                break;
            case 0x0200:
                g_str_lastError = "Device level error - Unexpected data";
                break;
            case 0x0300:
                g_str_lastError = "Device level error - Error frame";
                break;
            case 0x0400:
                g_str_lastError = "Device level error - Not supported";
                break;
            default:
                g_str_lastError = QString::fromLatin1(nfc_strerror(pndg));
                break;
            }
            return false;
        }
        else
        {
            *cardstat = "No target found..";
        }
    }

//----- Release and deselect all active communications
    nfc_initiator_deselect_target (pndg);

//----- Disable RF field to avoid heating
    nfc_configure (pndg, NDO_ACTIVATE_FIELD, false);

    return true;
}

int global_NFC::disconnectNFC()
{
//----- Disconnect from NFC device
    nfc_disconnect (pndg);
    return EXIT_SUCCESS;
}

QString global_NFC::print_hex (const byte_t * pbtData, const size_t szBytes)
{
    QString hex;
    char temp[10];
    size_t  szPos;

    for (szPos = 0; szPos < szBytes; szPos++) {
        sprintf((char*)temp, "%02x", pbtData[szPos]);
        hex = hex + QString(temp);
    }
    return hex;
}
