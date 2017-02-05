#include "cfingerprint.h"
#include "cfpmodule.h"

using namespace ClanCor;
CFpModule *Fpm;
CFingerPrint::CFingerPrint()
{
    Fpm=new CFpModule;
}

CFingerPrint::~CFingerPrint()
{
    delete Fpm;
}

void CFingerPrint::setTimeout(int nTimeout_mSecs) const
{
    extern int nTIMEOUT_MSECS;
    nTIMEOUT_MSECS = nTimeout_mSecs;
}

bool CFingerPrint::getFingerImage(QImage &r_imageFinger) const
{    
    return Fpm->getFingerImage(r_imageFinger);
}

bool CFingerPrint::enrollFinger(QByteArray &r_byteArrayTemplate) const
{
    return Fpm->enrollFinger(r_byteArrayTemplate);
}

bool CFingerPrint::enrollFinger(QByteArray &r_byteArrayTemplate, QImage &r_imageFinger) const
{
    return Fpm->enrollFinger(r_byteArrayTemplate,r_imageFinger);
}

bool  CFingerPrint::verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE1, const QByteArray &r_const_byteArrayTEMPLATE2, bool &r_bMatch) const
{
    return Fpm->verifyFinger(r_const_byteArrayTEMPLATE1,r_const_byteArrayTEMPLATE2,r_bMatch);
}

bool  CFingerPrint::verifyFinger(const QByteArray &r_const_byteArrayTEMPLATE, bool &r_bMatch) const
{
    return Fpm->verifyFinger(r_const_byteArrayTEMPLATE,r_bMatch);
}

bool  CFingerPrint::captureFinger(QByteArray &r_byteArrayTemplate) const
{
    return Fpm->captureFinger(r_byteArrayTemplate);
}
