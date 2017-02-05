/**
 * \file "cbarcode.h"
 * \brief it provides an barcode interface for ClanCor HHC80xx hand-held device.
 *
 * This file is used to get the barcode data.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CBARCODE_H
#define CBARCODE_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QThread>
#include "qextserialport.h"

namespace ClanCor
{
    /**
     * \class CBarCode
     * \brief The CBarCode class is used to get the barcode data if available.
     */
    class CBarCode : public QThread
    {
        Q_OBJECT

    public:
        /**
         * \fn CBarCode(const QString &r_const_strPORTNAME)
         * A constructor.
         * \brief Creates an object for receive the data from barcode module .
         * \arg[in] r_const_strPORTNAME used to set the barcode port name.
         */
        CBarCode(const QString &r_const_strPORTNAME);

        /**
         * \fn ~CBarCode()
         * A destructor.
         * \brief Stop the thread and destroys the allocated resources.
         */
        ~CBarCode();

        /**
         * \fn void startThread()
         * \brief This function is used to start the thread for get the barcode data.
         */
        void startThread();

        /**
         * \fn void stopThread()
         * \brief This function is used to stop the thread.
         */
        void stopThread();

    private:
        /**
         * \var QextSerialPort *m_serialportBarCode
         * \brief used to connect the barcode module via serialport.
         */
        QextSerialPort *m_serialportBarCode;
        /**
         * \var bool m_bThreadRunning
         * \brief used to store the thread is running or not.
         */
        bool m_bThreadRunning;
        /**
         * \var bool m_bThreadRunning
         * \brief used to store the barcode module is initiated or not.
         */
        bool m_bInitiated;

        /**
         * \fn virtual void run()
         * \brief The starting point for the thread. this function is remplemented of thread class.
         * it performs to get the barcode data if available.
         */
        virtual void run();

        /**
         * \fn bool portInitialize(const QString &r_const_strPORTNAME)
         * \brief This function is used to intialize the gsm port.
         * \param[in] r_const_strPORTNAME used to set the port name.
         * \return It returns true, if port opened successfully; otherwise returns false.
         */
        bool portInitialize(const QString &r_const_strPORTNAME);

        /**
         * \fn void arrivedData()
         * \brief This function is used to read the available data from the port.
         */
        void arrivedData();

    signals:    /** Signals */
        /*\@{*/

        /**
         * \fn oid barcodeData(const QString &r_const_strBARCODE)
         * \param[in] r_const_strBARCODE it gives the barcode data.
         * \brief This signal is emitted whenever barcode is readed successfully.
         */
        void barcodeData(const QString &r_const_strBARCODE);

        /*\@}*/
    };
}

#endif // CBARCODE_H
