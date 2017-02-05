#include "cpkcs11.h"

CK_FUNCTION_LIST_PTR pFunctionList;
static const char *	CKR2Str(CK_ULONG res);
QString g_strLastError;

#define check_return_value(rv, message) \
if (rv != CKR_OK) \
{ \
  g_strLastError = QString("PKCS11 function ") + QString(message) + QString(" failed: ") + QString(CKR2Str(rv)) + QString(" 0x") + QString::number((unsigned int) rv); \
                   return false; \
               }
static const char * CKR2Str(CK_ULONG res)
{
        switch (res) {
        case CKR_OK:
                return "CKR_OK";
        case CKR_CANCEL:
                return "CKR_CANCEL";
        case CKR_HOST_MEMORY:
                return "CKR_HOST_MEMORY";
        case CKR_SLOT_ID_INVALID:
                return "CKR_SLOT_ID_INVALID";
        case CKR_GENERAL_ERROR:
                return "CKR_GENERAL_ERROR";
        case CKR_FUNCTION_FAILED:
                return "CKR_FUNCTION_FAILED";
        case CKR_ARGUMENTS_BAD:
                return "CKR_ARGUMENTS_BAD";
        case CKR_NO_EVENT:
                return "CKR_NO_EVENT";
        case CKR_NEED_TO_CREATE_THREADS:
                return "CKR_NEED_TO_CREATE_THREADS";
        case CKR_CANT_LOCK:
                return "CKR_CANT_LOCK";
        case CKR_ATTRIBUTE_READ_ONLY:
                return "CKR_ATTRIBUTE_READ_ONLY";
        case CKR_ATTRIBUTE_SENSITIVE:
                return "CKR_ATTRIBUTE_SENSITIVE";
        case CKR_ATTRIBUTE_TYPE_INVALID:
                return "CKR_ATTRIBUTE_TYPE_INVALID";
        case CKR_ATTRIBUTE_VALUE_INVALID:
                return "CKR_ATTRIBUTE_VALUE_INVALID";
        case CKR_DATA_INVALID:
                return "CKR_DATA_INVALID";
        case CKR_DATA_LEN_RANGE:
                return "CKR_DATA_LEN_RANGE";
        case CKR_DEVICE_ERROR:
                return "CKR_DEVICE_ERROR";
        case CKR_DEVICE_MEMORY:
                return "CKR_DEVICE_MEMORY";
        case CKR_DEVICE_REMOVED:
                return "CKR_DEVICE_REMOVED";
        case CKR_ENCRYPTED_DATA_INVALID:
                return "CKR_ENCRYPTED_DATA_INVALID";
        case CKR_ENCRYPTED_DATA_LEN_RANGE:
                return "CKR_ENCRYPTED_DATA_LEN_RANGE";
        case CKR_FUNCTION_CANCELED:
                return "CKR_FUNCTION_CANCELED";
        case CKR_FUNCTION_NOT_PARALLEL:
                return "CKR_FUNCTION_NOT_PARALLEL";
        case CKR_FUNCTION_NOT_SUPPORTED:
                return "CKR_FUNCTION_NOT_SUPPORTED";
        case CKR_KEY_HANDLE_INVALID:
                return "CKR_KEY_HANDLE_INVALID";
        case CKR_KEY_SIZE_RANGE:
                return "CKR_KEY_SIZE_RANGE";
        case CKR_KEY_TYPE_INCONSISTENT:
                return "CKR_KEY_TYPE_INCONSISTENT";
        case CKR_KEY_NOT_NEEDED:
                return "CKR_KEY_NOT_NEEDED";
        case CKR_KEY_CHANGED:
                return "CKR_KEY_CHANGED";
        case CKR_KEY_NEEDED:
                return "CKR_KEY_NEEDED";
        case CKR_KEY_INDIGESTIBLE:
                return "CKR_KEY_INDIGESTIBLE";
        case CKR_KEY_FUNCTION_NOT_PERMITTED:
                return "CKR_KEY_FUNCTION_NOT_PERMITTED";
        case CKR_KEY_NOT_WRAPPABLE:
                return "CKR_KEY_NOT_WRAPPABLE";
        case CKR_KEY_UNEXTRACTABLE:
                return "CKR_KEY_UNEXTRACTABLE";
        case CKR_MECHANISM_INVALID:
                return "CKR_MECHANISM_INVALID";
        case CKR_MECHANISM_PARAM_INVALID:
                return "CKR_MECHANISM_PARAM_INVALID";
        case CKR_OBJECT_HANDLE_INVALID:
                return "CKR_OBJECT_HANDLE_INVALID";
        case CKR_OPERATION_ACTIVE:
                return "CKR_OPERATION_ACTIVE";
        case CKR_OPERATION_NOT_INITIALIZED:
                return "CKR_OPERATION_NOT_INITIALIZED";
        case CKR_PIN_INCORRECT:
                return "CKR_PIN_INCORRECT";
        case CKR_PIN_INVALID:
                return "CKR_PIN_INVALID";
        case CKR_PIN_LEN_RANGE:
                return "CKR_PIN_LEN_RANGE";
        case CKR_PIN_EXPIRED:
                return "CKR_PIN_EXPIRED";
        case CKR_PIN_LOCKED:
                return "CKR_PIN_LOCKED";
        case CKR_SESSION_CLOSED:
                return "CKR_SESSION_CLOSED";
        case CKR_SESSION_COUNT:
                return "CKR_SESSION_COUNT";
        case CKR_SESSION_HANDLE_INVALID:
                return "CKR_SESSION_HANDLE_INVALID";
        case CKR_SESSION_PARALLEL_NOT_SUPPORTED:
                return "CKR_SESSION_PARALLEL_NOT_SUPPORTED";
        case CKR_SESSION_READ_ONLY:
                return "CKR_SESSION_READ_ONLY";
        case CKR_SESSION_EXISTS:
                return "CKR_SESSION_EXISTS";
        case CKR_SESSION_READ_ONLY_EXISTS:
                return "CKR_SESSION_READ_ONLY_EXISTS";
        case CKR_SESSION_READ_WRITE_SO_EXISTS:
                return "CKR_SESSION_READ_WRITE_SO_EXISTS";
        case CKR_SIGNATURE_INVALID:
                return "CKR_SIGNATURE_INVALID";
        case CKR_SIGNATURE_LEN_RANGE:
                return "CKR_SIGNATURE_LEN_RANGE";
        case CKR_TEMPLATE_INCOMPLETE:
                return "CKR_TEMPLATE_INCOMPLETE";
        case CKR_TEMPLATE_INCONSISTENT:
                return "CKR_TEMPLATE_INCONSISTENT";
        case CKR_TOKEN_NOT_PRESENT:
                return "CKR_TOKEN_NOT_PRESENT";
        case CKR_TOKEN_NOT_RECOGNIZED:
                return "CKR_TOKEN_NOT_RECOGNIZED";
        case CKR_TOKEN_WRITE_PROTECTED:
                return "CKR_TOKEN_WRITE_PROTECTED";
        case CKR_UNWRAPPING_KEY_HANDLE_INVALID:
                return "CKR_UNWRAPPING_KEY_HANDLE_INVALID";
        case CKR_UNWRAPPING_KEY_SIZE_RANGE:
                return "CKR_UNWRAPPING_KEY_SIZE_RANGE";
        case CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT:
                return "CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT";
        case CKR_USER_ALREADY_LOGGED_IN:
                return "CKR_USER_ALREADY_LOGGED_IN";
        case CKR_USER_NOT_LOGGED_IN:
                return "CKR_USER_NOT_LOGGED_IN";
        case CKR_USER_PIN_NOT_INITIALIZED:
                return "CKR_USER_PIN_NOT_INITIALIZED";
        case CKR_USER_TYPE_INVALID:
                return "CKR_USER_TYPE_INVALID";
        case CKR_USER_ANOTHER_ALREADY_LOGGED_IN:
                return "CKR_USER_ANOTHER_ALREADY_LOGGED_IN";
        case CKR_USER_TOO_MANY_TYPES:
                return "CKR_USER_TOO_MANY_TYPES";
        case CKR_WRAPPED_KEY_INVALID:
                return "CKR_WRAPPED_KEY_INVALID";
        case CKR_WRAPPED_KEY_LEN_RANGE:
                return "CKR_WRAPPED_KEY_LEN_RANGE";
        case CKR_WRAPPING_KEY_HANDLE_INVALID:
                return "CKR_WRAPPING_KEY_HANDLE_INVALID";
        case CKR_WRAPPING_KEY_SIZE_RANGE:
                return "CKR_WRAPPING_KEY_SIZE_RANGE";
        case CKR_WRAPPING_KEY_TYPE_INCONSISTENT:
                return "CKR_WRAPPING_KEY_TYPE_INCONSISTENT";
        case CKR_RANDOM_SEED_NOT_SUPPORTED:
                return "CKR_RANDOM_SEED_NOT_SUPPORTED";
        case CKR_RANDOM_NO_RNG:
                return "CKR_RANDOM_NO_RNG";
        case CKR_DOMAIN_PARAMS_INVALID:
                return "CKR_DOMAIN_PARAMS_INVALID";
        case CKR_BUFFER_TOO_SMALL:
                return "CKR_BUFFER_TOO_SMALL";
        case CKR_SAVED_STATE_INVALID:
                return "CKR_SAVED_STATE_INVALID";
        case CKR_INFORMATION_SENSITIVE:
                return "CKR_INFORMATION_SENSITIVE";
        case CKR_STATE_UNSAVEABLE:
                return "CKR_STATE_UNSAVEABLE";
        case CKR_CRYPTOKI_NOT_INITIALIZED:
                return "CKR_CRYPTOKI_NOT_INITIALIZED";
        case CKR_CRYPTOKI_ALREADY_INITIALIZED:
                return "CKR_CRYPTOKI_ALREADY_INITIALIZED";
        case CKR_MUTEX_BAD:
                return "CKR_MUTEX_BAD";
        case CKR_MUTEX_NOT_LOCKED:
                return "CKR_MUTEX_NOT_LOCKED";
        case CKR_VENDOR_DEFINED:
                return "CKR_VENDOR_DEFINED";
        }
        return "unknown PKCS11 error";
}

CK_RV initialize()
{
    return pFunctionList->C_Initialize(NULL);
}

CK_RV get_slot(CK_SLOT_ID &r_slotId, CK_ULONG &r_slotCount)
{
    CK_RV rv;
    CK_ULONG slotCount = 10;
    CK_SLOT_ID *slotIds = (CK_SLOT_ID *)malloc(sizeof(CK_SLOT_ID) * slotCount);

    rv = pFunctionList->C_GetSlotList(CK_TRUE, slotIds, &slotCount);

    r_slotCount = slotCount;
    if (slotCount < 1) {
        g_strLastError = "could not find any slots..!";
        return rv;
    }

    r_slotId = slotIds[0];
    free(slotIds);
    return rv;
}

CK_RV start_session(CK_SLOT_ID slotId, CK_SESSION_HANDLE &r_sessionHandle)
{
    CK_RV rv;
    rv = pFunctionList->C_OpenSession(slotId,
                                      CKF_SERIAL_SESSION,
                                      NULL,
                                      NULL,
                                      &r_sessionHandle);
    return rv;
}

CK_RV login(CK_SESSION_HANDLE session, CK_BYTE *pin)
{
    CK_RV rv;
    if (pin) {
        rv = pFunctionList->C_Login(session, CKU_USER, pin, strlen((const char *)pin));
    }
    return rv;
}

CK_RV logout(CK_SESSION_HANDLE session)
{
    CK_RV rv;
    rv = pFunctionList->C_Logout(session);
    return rv;
}

CK_RV end_session(CK_SESSION_HANDLE session)
{
    CK_RV rv;
    rv = pFunctionList->C_CloseSession(session);
    return rv;
}

CK_RV finalize()
{
    CK_RV rv;
    rv = pFunctionList->C_Finalize(NULL);
    return rv;
}

CPKCS11::CPKCS11()
{
    bslotAvailable = false;
    rv = C_GetFunctionList(&pFunctionList);
    if(rv != CKR_OK) {
        g_strLastError = QString("PKCS11 function Get Function List") + QString("failed: ") + QString(CKR2Str(rv)) + QString(" 0x") + QString::number((unsigned int) rv);
        return;
    }
    initialize();
    CK_ULONG slotCount;
    rv = get_slot(slot, slotCount);
    if((rv == CKR_OK) && (slotCount > 0)) {
        bslotAvailable = true;
    }
}

CPKCS11::~CPKCS11()
{
    rv = finalize();
}


void CPKCS11::selectKey(QString strKeyIdentifier, E_KeyIdentifierType eKeyIDType)
{
    m_strKeyIdentifier = strKeyIdentifier;
    m_eKeyIDType = eKeyIDType;
}


void CPKCS11::setPin(QString strPin)
{
    m_strUser_pin = strPin;
}

bool CPKCS11::getKey_info(CK_SESSION_HANDLE session, CK_OBJECT_HANDLE key, QString &r_strKeyId, QString &r_strKeyLabel)
{
    CK_RV rv;
    CK_UTF8CHAR *label = (CK_UTF8CHAR *) malloc(256);
    CK_BYTE *id = (CK_BYTE *) malloc(256);
    size_t label_len;
    char *label_str, *id_str;

    memset(id, 0, 256);

    CK_ATTRIBUTE template1[] = {
        {CKA_LABEL, label, 256},
        {CKA_ID, id, 256}
    };

    rv = pFunctionList->C_GetAttributeValue(session, key, template1, 2);
    check_return_value(rv, "get attribute value");

    label_len = template1[0].ulValueLen;
    if (label_len > 0) {
         label_str = (char*) malloc(label_len + 1);
         memcpy(label_str, label, label_len);
         label_str[label_len] = '\0';
         r_strKeyLabel.append(label_str);
         free(label_str);
    } else {
        r_strKeyLabel.append("");
    }
    if (template1[1].ulValueLen > 0) {
        id_str = (char*) malloc(template1[1].ulValueLen + 1);
        memcpy(id_str, id, template1[1].ulValueLen);
        id_str[template1[1].ulValueLen] = '\0';
        r_strKeyId.append(id_str);
    } else {
        r_strKeyId.append("");
    }

    free(label);
    free(id);
    return true;
}

bool CPKCS11::getKey(QStringList &r_strlstKeyId, QStringList &r_strlstKeyLabel, E_KeyType E_KeyType)
{
    if(bslotAvailable)
    {
        CK_RV rv;
        CK_SESSION_HANDLE session;
        CK_OBJECT_CLASS keyClass = E_KeyType;
        CK_ATTRIBUTE template1[] = {
             { CKA_CLASS, &keyClass, sizeof(keyClass) }
        };
        CK_ULONG objectCount;
        CK_OBJECT_HANDLE object;

        rv = start_session(slot, session);
        check_return_value(rv, "close session");
        if(m_strUser_pin != "")
        {
            rv = login(session,(CK_BYTE*) m_strUser_pin.toLocal8Bit().constData());
            check_return_value(rv, "login");
        }
        else
        {
            g_strLastError = "Enter Valid pin..!";
            return false;
        }

        rv = pFunctionList->C_FindObjectsInit(session, template1, 1);
        check_return_value(rv, "Find objects init");

        rv = pFunctionList->C_FindObjects(session, &object, 1, &objectCount);
        check_return_value(rv, "Find first object");

        QString strKeyID, strKeyLabel;
        while (objectCount > 0) {
            if(!getKey_info(session, object, strKeyID, strKeyLabel))
            {
                return false;
            }
            r_strlstKeyId.append(strKeyID);
            r_strlstKeyLabel.append(strKeyLabel);

            strKeyID.clear();
            strKeyLabel.clear();

            rv = pFunctionList->C_FindObjects(session, &object, 1, &objectCount);
            check_return_value(rv, "Find other objects");
        }
        rv = pFunctionList->C_FindObjectsFinal(session);
        check_return_value(rv, "Find objects final");

        rv = logout(session);
        if (rv != CKR_USER_NOT_LOGGED_IN) {
            check_return_value(rv, "log out");
        }

        rv = end_session(session);
        check_return_value(rv, "close session");
    }
    else
    {
        return false;
    }
    return true;
}

bool CPKCS11::get_private_key(CK_SESSION_HANDLE session, CK_BYTE *id, size_t id_len, CK_OBJECT_HANDLE &key)
{
    CK_RV rv;
    CK_OBJECT_CLASS keyClass = CKO_PRIVATE_KEY;
    CK_ATTRIBUTE template1[] = {
        { CKA_CLASS, &keyClass, sizeof(keyClass) },
        { m_eKeyIDType, id, (id_len + 1) }
    };
    CK_ULONG objectCount;
    CK_OBJECT_HANDLE object;

    rv = pFunctionList->C_FindObjectsInit(session, template1, 2);
    check_return_value(rv, "Find objects init");

    rv = pFunctionList->C_FindObjects(session, &object, 1, &objectCount);
    check_return_value(rv, "Find first object");

    if (objectCount > 0) {
        rv = pFunctionList->C_FindObjectsFinal(session);
        check_return_value(rv, "Find objects final");
        key = object;
    } else {
        g_strLastError = "Private key not found\n";
        return false;
    }
    return true;
}

bool CPKCS11::get_public_key(CK_SESSION_HANDLE session, CK_BYTE *id, size_t id_len, CK_OBJECT_HANDLE &key)
{
    CK_RV rv;
    CK_OBJECT_CLASS keyClass = CKO_PUBLIC_KEY;
    CK_ATTRIBUTE template1[] = {
        { CKA_CLASS, &keyClass, sizeof(keyClass) },
        { m_eKeyIDType, id, (id_len + 1)}
    };
    CK_ULONG objectCount;
    CK_OBJECT_HANDLE object;

    rv = pFunctionList->C_FindObjectsInit(session, template1, 2);
    check_return_value(rv, "Find objects init");

    rv = pFunctionList->C_FindObjects(session, &object, 1, &objectCount);
    check_return_value(rv, "Find first object");

    if (objectCount > 0) {
        rv = pFunctionList->C_FindObjectsFinal(session);
        check_return_value(rv, "Find objects final");
        key = object;
    } else {
        g_strLastError = "Public key not found\n";
        return false;
    }
    return true;
}

bool CPKCS11::digest_data(CK_SESSION_HANDLE session,
            FILE *data_file,
            CK_BYTE *digest,
            CK_ULONG *digestLen)
{
     CK_MECHANISM digest_mechanism;
     CK_RV rv;

     CK_ULONG dataLen;
     CK_BYTE *data = (CK_BYTE *) malloc(1024);

     if (!data_file) {
          g_strLastError = "Error, no file handle in digest";
          return false;
     }

     digest_mechanism.mechanism = CKM_SHA_1;
     digest_mechanism.pParameter = NULL;
     digest_mechanism.ulParameterLen = 0;

     rv = pFunctionList->C_DigestInit(session, &digest_mechanism);
     check_return_value(rv, "digest init");

     dataLen = fread(data, 1, 1024, data_file);
     while (dataLen > 0) {
          rv = pFunctionList->C_DigestUpdate(session, data, dataLen);
          check_return_value(rv, "digest update");
          dataLen = fread(data, 1, 1024, data_file);
     }

     rv = pFunctionList->C_DigestFinal(session, digest, digestLen);
     check_return_value(rv, "digest final");

     free(data);
     return true;
}

bool CPKCS11::sign(CK_SESSION_HANDLE session, FILE *data_file, FILE *signature_file)
{
    CK_RV rv;
    CK_OBJECT_HANDLE key;
    if(!get_private_key(session,(CK_BYTE*) m_strKeyIdentifier.toLocal8Bit().constData(), strlen(m_strKeyIdentifier.toLocal8Bit().constData()), key))
    {
        return false;
    }
    CK_MECHANISM sign_mechanism;

    CK_ULONG digestLen = 20;
    CK_BYTE *digest =(CK_BYTE *) malloc(digestLen);

    CK_ULONG signatureLen = 512;
    CK_BYTE *signature =(CK_BYTE *) malloc(signatureLen);

    sign_mechanism.mechanism = CKM_RSA_PKCS;
    sign_mechanism.pParameter = NULL;
    sign_mechanism.ulParameterLen = 0;

    if(!digest_data(session, data_file, digest, &digestLen))
    {
//        check_return_value(rv, "digest data");
        return false;
    }


    rv = pFunctionList->C_SignInit(session, &sign_mechanism, key);
    check_return_value(rv, "sign init new");

    rv = pFunctionList->C_Sign(session, digest, digestLen, signature, &signatureLen);
    check_return_value(rv, "sign final");

    if (signatureLen > 0) {
         fwrite(signature, signatureLen, 1, signature_file);
    }

    free(digest);
    free(signature);
    return true;
}

bool CPKCS11::verify(CK_SESSION_HANDLE session, FILE *data_file, FILE *signature_file)
{
    CK_RV rv = 0;
    CK_OBJECT_HANDLE key;
    if(!get_public_key(session,(CK_BYTE*) m_strKeyIdentifier.toLocal8Bit().constData(), strlen(m_strKeyIdentifier.toLocal8Bit().constData()), key))
    {
        return false;
    }

    CK_MECHANISM sign_mechanism;
    CK_ULONG digestLen = 21;
    CK_BYTE *digest =(CK_BYTE *) malloc(digestLen);

    CK_ULONG signatureLen = 512;
    CK_BYTE *signature =(CK_BYTE *) malloc(signatureLen);

    signatureLen = fread(signature, 1, signatureLen, signature_file);

    sign_mechanism.mechanism = CKM_RSA_PKCS;
    sign_mechanism.pParameter = NULL;
    sign_mechanism.ulParameterLen = 0;

    if(!digest_data(session, data_file, digest, &digestLen))
    {
        check_return_value(rv, "digest data");
        return false;
    }

    rv = pFunctionList->C_VerifyInit(session, &sign_mechanism, key);
    check_return_value(rv, "verify init");

    rv = pFunctionList->C_Verify(session,
                  digest,
                  digestLen,
                  signature,
                  signatureLen
                  );
    check_return_value(rv, "verify");

    free(digest);
    free(signature);
    return true;
}

bool CPKCS11::signData(QString strDataFile, QString strSignatureFile)
{
    if(bslotAvailable)
    {
        if(!QFile::exists(strDataFile))
        {
            g_strLastError = "Data File Not Found...!";
            return false;
        }
        CK_RV rv;
        CK_SESSION_HANDLE session;
        FILE *input_file = NULL;
        FILE *output_file = NULL;

        /* signing */
        input_file = fopen(strDataFile.toLatin1(), "r");
        output_file = fopen(strSignatureFile.toLatin1(), "w");
        if( !output_file )
        {
            g_strLastError = "Failed to create sign file..\n Please check file path & permission..!";
            return false;
        }

        rv = start_session(slot, session);
        check_return_value(rv, "close session");

        if(m_strUser_pin != "")
        {
            rv = login(session,(CK_BYTE*) m_strUser_pin.toLocal8Bit().constData());
            check_return_value(rv, "login");
        }
        else
        {
            g_strLastError = "Enter Valid pin..!";
            return false;
        }

        if(!sign(session, input_file, output_file))
        {
            return false;
        }

        if (m_strUser_pin != "")
        {
            rv = logout(session);
            if (rv != CKR_USER_NOT_LOGGED_IN) {
                check_return_value(rv, "log out");
            }
        }

        rv = end_session(session);
        check_return_value(rv, "close session");

        fclose(input_file);
        fclose(output_file);

        rv = finalize();
        check_return_value(rv, "finalize");
    }
    else
    {
        return false;
    }
    return true;
}

bool CPKCS11::verifyData(QString strDataFile, QString strSignatureFile)
{
    if(bslotAvailable)
    {
        if(!QFile::exists(strDataFile))
        {
            g_strLastError = "Data File Not Found...!";
            return false;
        }
        if(!QFile::exists(strSignatureFile))
        {
            g_strLastError = "Signature File Not Found...!";
            return false;
        }
        CK_RV rv;
        CK_SESSION_HANDLE session;
        FILE *input_file = NULL;
        FILE *output_file = NULL;

        /* signing */
        input_file = fopen(strDataFile.toLatin1(), "r");
        output_file = fopen(strSignatureFile.toLatin1(), "r");
        if( !output_file )
        {
            g_strLastError = "Failed to creating sign file..\n Please check file path & permission..!";
            return false;
        }

        rv = start_session(slot, session);
        if (rv != CKR_OK) {
            g_strLastError = QString("PKCS11 function login") + QString("failed: ") + QString(CKR2Str(rv)) + QString("0x") + QString::number((unsigned int) rv);
            return false;
        }

        if(m_strUser_pin != "")
        {
            rv = login(session,(CK_BYTE*) m_strUser_pin.toLocal8Bit().constData());
            if (rv != CKR_OK) {
                g_strLastError = QString("PKCS11 function login") + QString("failed: ") + QString(CKR2Str(rv)) + QString("0x") + QString::number((unsigned int) rv);
                return false;
            }
        }
        else
        {
            g_strLastError = "Enter Valid pin..!";
            return false;
        }

        if(!verify(session, input_file, output_file))
        {
            return false;
        }

        if (m_strUser_pin != "")
        {
            rv = logout(session);
            if (rv != CKR_USER_NOT_LOGGED_IN) {
                check_return_value(rv, "log out");
            }
        }

        rv = end_session(session);
        check_return_value(rv, "close session");

        fclose(input_file);
        fclose(output_file);
    }
    else
    {
        return false;
    }
    return true;
}

QString CPKCS11::lastError()
{
    return g_strLastError;
}
