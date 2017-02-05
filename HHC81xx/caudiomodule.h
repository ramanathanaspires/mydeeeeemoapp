/**
 * \file "caudiomodule.h"
 * \brief it provides an audio interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to record voice and playback.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CAUDIOMODULE_H
#define CAUDIOMODULE_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QtGui>
#include <sys/soundcard.h>
#include "caudio.h"

namespace ClanCor
{
    /**
     * \class CAudioModule
     * \brief The CAudioModule class is used to record voice & playback in the ClanCor HHC80xx device.
     * use setMaxRecording() function to change the maximum recording time.
     */
    class CAudioModule : public QThread
    {
         Q_OBJECT

    public:
        /**
         * \fn CAudioModule()
         * A constructor.
         * \brief creates a new audio object for voice recording & playback.
         * construct the audio dialog
         */
        CAudioModule();

        /**
         * \fn ~CAudioModule()
         * A destructor.
         * \brief free all the allocated resources.
         */
        ~CAudioModule();
        /**
         * \fn void setMaxRecording(int nSeconds)
         * \brief This function is used to set the maximum recording time to adjust the default value.
         * The default maximum recording time is 90 seconds.
         * \param[in] nSecs used to set the maximum recording time in seconds.

         */
        void setMaxRecording(int nSeconds) { m_nMaxRecording = nSeconds; }

        /**
         * \fn bool record(QByteArray &r_byteArrayRecordedData,CAudio::E_AudioQuality eQuality=CAudio::eAudioQuality_MEDIUM, const QString &r_const_strDISPLAYTEXT="")
         * \brief This function is used to show the audio dialog for voice recording.
         * it will give the mp3 data after converting from raw data.
         * audio dialog will be shown only if the audio device is found.
         * \param[out] r_byteArrayRecordedData used to get the recorded voice data.
         * \param[in] eQuality it set the voice recording quality.
         * \param[in] r_const_strDISPLAYTEXT used to display the text in the audio dialog.
         * \return It returns true, if voice recorded successfully; otherwise returns false.
         *
         * \sa see alsoCAudio::E_AudioQuality.
         */
        bool record(QByteArray &r_byteArrayRecordedData,CAudio::E_AudioQuality eQuality=CAudio::eAudioQuality_MEDIUM, const QString &r_const_strDISPLAYTEXT="");

        /**
         * \fn bool play(const QByteArray &r_const_byteArrayDATA,const QString &r_const_strDISPLAYTEXT)
         * \brief This function is used to show the audio dialog for play the mp3 data.
         * It will convert to raw data when loading audio dialog.
         * audio dialog will be shown only if the audio device is found.
         * \param[in] r_const_byteArrayDATA used to pass the voice recorded data.
         * \param[in] r_const_strDISPLAYTEXT used to display the text in the audio dialog.
         * \return It returns true, if audio data played successfully; otherwise returns false.
         */
        bool play(const QByteArray &r_const_byteArrayDATA,const QString &r_const_strDISPLAYTEXT);

        /**
         * \fn bool enableAudio()
         * \brief This function is used to enable audio module wait until device found or timeout.
         * \return It returns if audio device is found; otherwise return false.
         */
        static bool enableAudio();
    private:
        /**
         * \var int m_nFd
         * \brief used to store the sound device file descriptor.
         */
        int m_nFd;
        /**
         * \var int m_nArg
         * \brief used to store the argument for ioctl calls.
         */
        int m_nArg;
        /**
         * \var int m_nStatus
         * \brief used to store the count for wifi search.
         */
        int m_nStatus;
        /**
         * \var int m_nRate
         * \brief used to store the sampling rate.
         */
        int m_nRate;
        /**
         * \var int m_nSize
         * \brief used to store the sampling size.
         */
        int m_nSize;
        /**
         * \var int m_nChannels
         * \brief used to store the channel monio or stero.
         */
        int m_nChannels;
        /**
         * \var int m_nPrevSpeakerVol
         * \brief used to store the previous speaker volume.
         */
        int  m_nPrevSpeakerVol;
        /**
         * \var bool m_bMuted
         * \brief used to store the speaker is muted or not.
         */
        bool m_bMuted;
        /**
         * \var int m_nMaxPlaying
         * \brief used to store the maximum playing time.
         */
        int m_nMaxPlaying;
        /**
         * \var int m_nCountPerSec
         * \brief used to store the number of bytes per second.
         */
        int m_nCountPerSec;
        /**
         * \var int m_nMaxRecording
         * \brief used to store the maximum recording time.
         */
        int m_nMaxRecording;

        /**
         * \var bool m_bMicMuted
         * \brief used to store the mic is muted or not.
         */
        bool m_bMicMuted;
        /**
         * \var bool m_bAudioRecording
         * \brief used to store the audio recording or not.
         */
        bool m_bAudioRecording;
        /**
         * \var bool m_bRecording
         * \brief used to store the recording is running or not.
         */
        bool m_bRecording;
        /**
         * \var bool m_bRecorded
         * \brief used to store the recorded successfully.
         */
        bool m_bRecorded;
        /**
         * \var bool m_bPlaying
         * \brief used to store the audio is playing or not.
         */
        bool m_bPlaying;
        /**
         * \var bool m_bMute
         * \brief used to store the speaker is mute or not.
         */
        bool m_bMute;

        /**
         * \var QTimer m_timerClose
         * \brief used to process for close dialog in 60 seconds if not used.
         */
        QTimer m_timerClose;
        /**
         * \var QWidget *m_widgetMsgScreen
         * \brief used to show the widget when converting to mp3.
         */
        QWidget *m_widgetMsgScreen;
        /**
         * \var QLabel *m_labelMsgStatus
         * \brief used to display the status in message screen.
         */
        QLabel *m_labelMsgStatus;
        /**
         * \var QDialog *m_dialogAudio
         * \brief used to display the audio dialog for recording & playing.
         */
        QDialog *m_dialogAudio;
        /**
         * \var QLabel *m_labelDisplayText
         * \brief used to display the text in the audio dialog.
         */
        QLabel *m_labelDisplayText;
        /**
         * \var QLabel *m_labelStatus
         * \brief used to display the status (recording/playing/completed) in the audio dialog.
         */
        QLabel *m_labelStatus;
        /**
         * \var QLabel *m_labelTime
         * \brief used to display the maximum recording or playing time.
         */
        QLabel *m_labelTime;
        /**
         * \var QLabel *m_labelVolume
         * \brief used to display the speaker volume percentage.
         */
        QLabel *m_labelVolume;
        /**
         * \var QPushButton *m_pushButtonRecord
         * \brief used to display recording button in audio dialog.
         */
        QPushButton *m_pushButtonRecord;
        /**
         * \var QPushButton *m_pushButtonPlay
         * \brief used to display play button in audio dialog.
         */
        QPushButton *m_pushButtonPlay;
        /**
         * \var QPushButton *m_pushButtonStop
         * \brief used to display stop button in audio dialog.
         */
        QPushButton *m_pushButtonStop;
        /**
         * \var QPushButton *m_pushButtonOk
         * \brief used to display ok button in audio dialog.
         */
        QPushButton *m_pushButtonOk;
        /**
         * \var QPushButton *m_pushButtonCancel
         * \brief used to display cancel button in audio dialog.
         */
        QPushButton *m_pushButtonCancel;
        /**
         * \var QSlider *m_sliderTime
         * \brief used to move the slider when recording or playing.
         */
        QSlider *m_sliderTime;
        /**
         * \var QSlider *m_sliderVolume
         * \brief used to increase or decrease the speaker volume.
         */
        QSlider *m_sliderVolume;
        /**
         * \var QToolBar *m_toolbarProgress
         * \brief used to dispaly the progress informations.
         */
        QToolBar *m_toolbarProgress;
        /**
         * \var QToolBar *m_toolbarStatus
         * \brief used to dispaly the status informations.
         */
        QToolBar *m_toolbarStatus;
        /**
         * \var QAction *m_actionVolume
         * \brief used to do speaker mute and unmute.
         */
        QAction *m_actionVolume;
        /**
         * \var QByteArray m_byteArrayTemp
         * \brief used to store the recording data temporarly.
         */
        QByteArray m_byteArrayTemp;
        /**
         * \var QByteArray m_byteArraySaved
         * \brief used to store the recorded audio data.
         */
        QByteArray m_byteArraySaved;
        /**
         * \var QString m_strDummy
         * \brief used to process dummy variable.
         */
        QString m_strDummy;

        /**
         * \fn bool init()
         * \brief This function is used to initalize the audio device.
         * \return It returns if audio device is initiated successfully; otherwise return false.
         */
        bool init();

        /**
         * \fn void updateProgressTime()
         * \brief This function is used to update the slider time and label time.
         * increase step by one every second of data recorded or played.
         */
        void updateProgressTime();

        /**
         * \fn void enableButton(bool bState)
         * \brief This function is used to enable or disable button when recording or playing.
         * \arg[in] bState used to set the buttons should be enabled/disabled.
         */
        void enableButton(bool bState);

        /**
         * \fn QString formatTime(int nSecs)
         * \brief This function is used to convert the seconds into minutes & seconds in string.
         * \arg[in] nSecs used to set the second which is to be converted.
         * \return it returns formatted minutes & seconds text.
         */
        QString formatTime(int nSecs);

        /**
         * \fn virtual void run()
         * \brief The starting point for the thread. this function is remplemented of thread class.
         * it performs the process of recording & playing.
         */
        void run();

        /**
         * \fn void closed()
         * \brief This function is used to stop the thread and close the audio dialog.
         */
        void closed();

        /**
         * \fn void initVolumeDetails()
         * \brief This function is used initalize the volume details and update it in display.
         */
        void initVolumeDetails();

    private slots:
        /**
         * \fn void initVolumeDetails()
         * \brief This function is used to intimate close the audio dialog.
         */
        void on_timerClose_timeout();
        /**
         * \fn void on_pushButtonRecord_clicked()
         * \brief This function is used to start the recording process.
         */
        void on_pushButtonRecord_clicked();
        /**
         * \fn void on_pushButtonPlay_clicked()
         * \brief This function is used to start the playing process.
         */
        void on_pushButtonPlay_clicked();
        /**
         * \fn void on_pushButtonStop_clicked()
         * \brief This function is used to stop recording or playing.
         */
        void on_pushButtonStop_clicked();
        /**
         * \fn void on_pushButtonOk_clicked()
         * \brief This function is used to convert the recorded audio data into mp3 data.
         */
        void on_pushButtonOk_clicked();
        /**
         * \fn void on_pushButtonCancel_clicked()
         * \brief This function is used to cancel the audio process and close the dialog.
         */
        void on_pushButtonCancel_clicked();
        /**
         * \fn void playData()
         * \brief This function is used to play tha curent second of data.
         */
        void playData();
        /**
         * \fn void muteOnOff()
         * \brief This function is used to process mute on/off.
         */
        void muteOnOff();
        /**
         * \fn void updateVolume()
         * \brief This function is used to update the speaker volume.
         */
        void updateVolume();
        /**
         * \fn void displayError()
         * \brief This function is used to show the error when device is disconnected
         */
        void displayError();
        /**
         * \fn void stopProcess()
         * \brief This function is used to end the process.
         */
        void stopProcess();

    signals:
        /**
         * \fn void stopProcess()
         * \brief This signal is emitted for show the error.
         */
        void error();
        /**
         * \fn void stopThread()
         * \brief This signal is emitted for stop the thread.
         */
        void stopThread();
    };
}
#endif // CAUDIOMODULE_H
