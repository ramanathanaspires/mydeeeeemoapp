#ifndef CPKCS11_H
#define CPKCS11_H

#include "pkcs11/pkcs11.h"
#include <QStringList>
#include <QFile>
#include <QDebug>

#include <QString>

#define CK_PTR *
#define CK_DECLARE_FUNCTION(returnType, name) \
     returnType name
#define CK_DECLARE_FUNCTION_POINTER(returnType, name) \
     returnType (* name)
#define CK_CALLBACK_FUNCTION(returnType, name) \
     returnType (* name)
#ifndef NULL_PTR
#define NULL_PTR 0
#endif

class CPKCS11
{
public:

         /**
          * The enum describes the Key Type
          */
         enum E_KeyType
         {
             eKeyType_PRIVATE = CKO_PRIVATE_KEY, /**< Key ID */
             eKeyType_PUBLIC = CKO_PUBLIC_KEY, /**< Key LABEL */
         };

         /**
          * The enum describes the Key Identifier
          */
         enum E_KeyIdentifierType
         {
             eKeyIdentifierType_KEY_ID = CKA_ID, /**< Key ID */
             eKeyIdentifierType_KEY_LABEL = CKA_LABEL, /**< Key LABEL */
         };

    CPKCS11();
    ~CPKCS11();
    void setPin(QString strPin);
    void selectKey(QString strKeyIdentifier, E_KeyIdentifierType eKeyIDType);
    bool getKey(QStringList &r_strlstKeyId, QStringList &r_strlstKeyLabel, E_KeyType eKeyType);
    bool digest_data(CK_SESSION_HANDLE session, FILE *data_file, CK_BYTE *digest, CK_ULONG *digestLen);
    bool sign(CK_SESSION_HANDLE session,  FILE *data_file, FILE *signature_file);
    bool verify(CK_SESSION_HANDLE session,  FILE *data_file, FILE *signature_file);
    bool signData(QString strDataFile, QString strSignatureFile);
    bool verifyData(QString strDataFile, QString strSignatureFile);
    QString lastError();

private:
    CK_SLOT_ID slot;
    CK_RV rv;
    QString m_strUser_pin, m_strKeyIdentifier;
    E_KeyIdentifierType m_eKeyIDType;
    bool bslotAvailable;

    bool getKey_info(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE key, QString &r_strKeyId, QString &r_strKeyLabel);
    bool get_private_key(CK_SESSION_HANDLE session, CK_BYTE *id, size_t id_len, CK_OBJECT_HANDLE &key);
    bool get_public_key(CK_SESSION_HANDLE session, CK_BYTE *id, size_t id_len, CK_OBJECT_HANDLE &key);

};

#endif // CPKCS11_H
