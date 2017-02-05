#include "caudio.h"
#include "caudiomodule.h"

using namespace ClanCor;

/**
 * \var CAudioModule *objAudio
 * \brief used to call the fucntions.
 */
CAudioModule *objAudio;

CAudio::CAudio()
{
    objAudio=new CAudioModule;
    m_nMaxRecording=90;
}

CAudio::~CAudio()
{
    delete objAudio;
}

bool CAudio::record(QByteArray &r_byteArrayRecordedData, E_AudioQuality eQuality,
                    const QString &r_const_strDISPLAYTEXT) const
{
    objAudio->setMaxRecording(m_nMaxRecording);
    return objAudio->record(r_byteArrayRecordedData,eQuality,r_const_strDISPLAYTEXT);
}

bool CAudio::play(const QByteArray &r_const_byteArrayDATA,
                 const QString &r_const_strDISPLAYTEXT) const
{
    if(r_const_byteArrayDATA.size() > 0)
    {
        qDebug()<<"byte size";
        return objAudio->play(r_const_byteArrayDATA,r_const_strDISPLAYTEXT);
    }else
    {
        return false;
    }
}
