/**
 * \file "ctouchcalibrate.h"
 * \brief it provides the calibrate the touch screen positions.
 *
 * This file is used to show the calibration dialog to calibrate the touch coordinate
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CTOUCHCALIBRATE_H
#define CTOUCHCALIBRATE_H

#include <QObject>
#include <QDialog>

extern "C"
{
    #include "tslib.h"
}

namespace ClanCor
{
    /**
     * \class CTouchCalibrate
     * \brief The CTouchCalibrate class is used to show the Touchscreen dialog for calibrate co-ordinates.
     */
    class CTouchCalibrate : QObject
    {
       Q_OBJECT

    public:
        /**
         * \fn CTouchCalibrate()
         * A constructor.
         * Creates dialog for get the co-ordinates from user.
         */
        CTouchCalibrate();

        /**
         * \fn ~CTouchCalibrate()
         * A destructor.
         * \brief Destroys the touch screen dialog.
         */
        ~CTouchCalibrate();

        /**
         * \fn bool getTouchval()
         * \brief This function is used to show the touchscren dialog for calibration.
         * \return It returns true if calibrartion successfullt; otherwise return false.
         */
        bool getTouchval();

    private:

        /**
         * \var QDialog *m_dialogTouch
         * \brief used to display the touch screen dialog.
         */
        QDialog *m_dialogTouch;
    };
}
#endif // CTOUCHCALIBRATE_H
