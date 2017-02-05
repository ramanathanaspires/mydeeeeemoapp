#ifndef NFC_API_H
#define NFC_API_H
#include <QString>
#include <nfc/nfc-types.h>
#include <nfc/nfc.h>
#include <nfc/nfc-messages.h>

#  ifdef __cplusplus
extern  "C" {
#  endif                        // __cplusplus

#  ifdef __cplusplus
}
#  endif                        // __cplusplus


namespace global_NFC
{
    extern nfc_device_t *pndg;
    extern QString g_str_lastError;

    int connectNFC(QString *Reader);
    bool nfcReadUID(QString *atr, QString *uid, QString *cardstat);
    int disconnectNFC();
    QString print_hex (const byte_t * pbtData, const size_t szBytes);
}

#endif // NFC_API_H
