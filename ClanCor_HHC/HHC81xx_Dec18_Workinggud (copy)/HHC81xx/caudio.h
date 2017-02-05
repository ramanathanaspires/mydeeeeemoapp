/**
 * \file "caudio.h"
 * \brief it provides an audio interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to record voice and playback.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CAUDIO_H
#define CAUDIO_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QString>
#include <QByteArray>
namespace ClanCor
{
    /**
     * \class CAudio
     * \brief The CAudio class is used to record voice & playback in the ClanCor HHC80xx device.
     * use setMaxRecording() function to change the maximum recording time.
     */
    class CAudio
    {
    /*****************************************************************************
                                    PUBLIC
    ******************************************************************************/
    public:

        /**
         * This enum type is used to specify the audio quality of voice recording.
         */
        enum E_AudioQuality
        {
              eAudioQuality_VERY_LOW = 1,  /**< very low audio quality. sampling rate is 16000 */
              eAudioQuality_LOW = 2, /**< low audio quality. sampling rate is 24000 */
              eAudioQuality_MEDIUM = 3, /**< medium audio quality. sampling rate is 32000 */
              eAudioQuality_HIGH = 4, /**< high audio quality. sampling rate is 48000 */
              eAudioQuality_VERY_HIGH = 5 /**< very high audio quality. sampling rate is 64000 */
        };

        /**
         * \fn CAudio()
         * A constructor.
         * \brief Creates a new audio object for voice recording & playback.
         */
        CAudio();

        /**
         * \fn ~CAudio()
         * A destructor.
         * \brief Destroys the audio object and frees any allocated resources.
         */
        ~CAudio();

        /**
         * \fn void setMaxRecording(int nSecs)
         * \brief This function is used to set the maximum recording time to adjust the default value.
         * The default maximum recording time is 90 seconds.
         * \param[in] nSecs used to set the maximum recording time in seconds.
         */
        void setMaxRecording(int nSecs) { m_nMaxRecording = nSecs; }

        /**
         * \fn bool record(QByteArray &r_byteArrayRecordedData, E_AudioQuality eQuality=eAudioQuality_MEDIUM, const QString &r_const_strDISPLAYTEXT="") const
         * \brief This function is used to show the audio dialog for voice recording.
         * it will give the mp3 data after converting from raw data.
         * audio dialog will be shown only if the audio device is found.
         * \param[out] r_byteArrayRecordedData used to get the recorded voice data.
         * \param[in] eQuality it set the voice recording quality.
         * \param[in] r_const_strDISPLAYTEXT used to display the text in the audio dialog.
         * \return It returns true, if voice recorded successfully; otherwise returns false.
         *
         * \sa see also E_AudioQuality.
         */
        bool record(QByteArray &r_byteArrayRecordedData, E_AudioQuality eQuality=eAudioQuality_MEDIUM, const QString &r_const_strDISPLAYTEXT="") const;

        /**
         * \fn bool play(const QByteArray &r_const_byteArrayDATA,const QString &r_const_strDISPLAYTEXT) const
         * \brief This function is used to show the audio dialog for play the mp3 data.
         * It will convert to raw data when loading audio dialog.
         * audio dialog will be shown only if the audio device is found.
         * \param[in] r_const_byteArrayDATA used to pass the voice recorded data.
         * \param[in] r_const_strDISPLAYTEXT used to display the text in the audio dialog.
         * \return It returns true, if audio data played successfully; otherwise returns false.
         */
        bool play(const QByteArray &r_const_byteArrayDATA,const QString &r_const_strDISPLAYTEXT) const;

    private:
        /**
         * \var int m_nMaxRecording
         * \brief used to store the maximum recording time.
         */
        int m_nMaxRecording;

    };
}
#endif // CAUDIO_H
