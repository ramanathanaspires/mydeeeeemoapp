/**
 * \file "cvolume.h"
 * \brief it provides an interface for control the speaker and mic volumes .
 *
 * This file is used to construct the dialog for speaker volume dialog and volume setting dialog.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CVOLUME_H
#define CVOLUME_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QDialog>
#include <QtGui>

namespace ClanCor
{
    /**
     * \class CVolume
     * \brief The CVolume class provides an interface for adjust the speaker volume and show dialog.
     *
     *  This class is used to show the speaker volume dialog when adjust the values using shortcuts.
     */
    class CVolume : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * \fn CVolume()
         * A constructor.
         * \brief Creates a volume dialog object for display speaker volume & initialize it.
         */
        CVolume();

        /**
         * \fn void increaseVolume()
         * \brief This function is used to increase the speaker volume by 10 percentage.
         */
        void increaseVolume();

        /**
         * \fn void decreaseVolume()
         * \brief This function is used to decrease the speaker volume by 10 percentage.
         */
        void decreaseVolume();

    private:
        /**
         * \var QSlider *sliderSpeaker
         * \brief used to store the added data for printing.
         */
        QSlider *sliderSpeaker;
        /**
         * \var QLabel *labelVolume
         * \brief used to display the current speaker volume in percentage.
         */
        QLabel *labelVolume;
        /**
         * \var int m_nValue
         * \brief used to store the current speaker volume.
         */
        int m_nValue;
    };

    /**
     * \class CVolumeSetting
     * \brief The CVolumeSetting class provides an interface for show the dialog to adjust the speaker & mic volumes.
     *
     *  This class is used to show the audio setting dialog.
     */
    class CVolumeSetting : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * \fn CVolumeSetting()
         * A constructor.
         * \brief Creates a volume setting dialog for adjust speaker & mic volume.
         * It will initialize the previous values.
         */
        CVolumeSetting();

    private:
        /**
         * \var int m_nSpeakerVol
         * \brief used to store the speaker volume.
         */
        int m_nSpeakerVol;
        /**
         * \var int m_nMicVol
         * \brief used to store the mic volume.
         */
        int m_nMicVol;

        /**
         * \var QPushButton *pushButtonSpeaker
         * \brief used to display the speaker button for mute/unmute the speaker volumes.
         */
        QPushButton *pushButtonSpeaker;
        /**
         * \var QPushButton *pushButtonMic
         * \brief used to display the mic button for mute/unmute the mic volumes.
         */
        QPushButton *pushButtonMic;
        /**
         * \var QPushButton *pushButtonDefault
         * \brief used to display the button for default speaker & mic volumes.
         */
        QPushButton *pushButtonDefault;
        /**
         * \var QSlider *sliderSpeakerVol
         * \brief used to adjust speaker volume.
         */
        QSlider *sliderSpeakerVol;
        /**
         * \var QSlider *sliderMicVol
         * \brief used to adjust mic volume.
         */
        QSlider *sliderMicVol;
        /**
         * \var bool isMute
         * \brief used to store the speaker is muted or not.
         */
        bool isMute;
        /**
         * \var bool isMicMute
         * \brief used to store the mic is muted or not.
         */
        bool isMicMute;
        /**
         * \var bool isMicMute
         * \brief used to
         */

        /**
         * \fn void keyPressEvent(QKeyEvent *keyEvent
         * \brief This function is used to handle the key for mute/unmute from shortcuts.
         */
        void keyPressEvent(QKeyEvent *keyEvent);

    private slots:
        /**
         * \fn void slotVol()
         * \brief This function is used to set the speaker volume.
         */
        void slotVol();

        /**
         * \fn void slotVolmic()
         * \brief This function is used to set the mic volume.
         */
        void slotVolmic();

        /**
         * \fn bool getVolume(const QString &r_const_strELEMENT, int &r_nVolume, bool &r_bMute)
         * \brief This function is used to get the volume of given element.
         * \arg[in] r_const_strELEMENT used to set the element Speaker or Mic.
         * \arg[out] r_nVolume used to get the volume.
         * \arg[out] r_bMute used to get the status mute/unmute.
         * \return It returns true, if successfully executed; otherwise false.
         */
        bool getVolume(const QString &r_const_strELEMENT, int &r_nVolume, bool &r_bMute);

        /**
         * \fn void slotMute(const QString &r_const_strELEMENT, bool bMute)
         * \brief This function is used to mute or unmute by given element.
         * \arg[in] r_const_strELEMENT used to set the element Speaker or Mic.
         * \arg[in] r_bMute used to set the status mute/unmute.
         */
        void slotMute(const QString &r_const_strELEMENT, bool bMute);

        /**
         * \fn void muteUnMute(const QString &r_const_strELEMENT)
         * \brief This function is used to update the mute / unmute in display.
         * if given element is muted, then unmute otherwise mute.
         * \arg[in] r_const_strELEMENT used to set the element Speaker or Mic.
         */
        void muteUnMute(const QString &r_const_strELEMENT);

        /**
         * \fn void changeVal(int nValue)
         * \brief This function is used intimate when speaker volume is changed by user.
         * \arg[in] nValue used to set the changed volume.
         */
        void changeVal(int nValue);

        /**
         * \fn void slotBtnvol(int nValue)
         * \brief This function is used intimate when mic volume is changed by user.
         * \arg[in] nValue used to set the changed volume.
         */
        void changeValmic(int nValue);

        /**
         * \fn void slotBtnvol()
         * \brief This function is used intimate when speaker volume is mute/unmute by user.
         */
        void slotBtnvol();

        /**
         * \fn void slotBtnmic()
         * \brief This function is used intimate when mic volume is mute/unmute by user.
         */
        void slotBtnmic();

        /**
         * \fn void setDefault()
         * \brief This function is used intimate when default speaker & mic volume by user.
         */
        void setDefault();
    };
}
#endif // CVOLUME_H
