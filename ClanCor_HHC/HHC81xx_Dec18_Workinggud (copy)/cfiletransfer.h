/**
 * \file "cfiletransfer.h"
 * \brief it provides an interface for transfer file from ClanCor HHC 80xx device to system.
 *
 * This file is used to send teh file via Serialport or Ethernet.
 *
 * Copy Right © Clancor Technovates 2009. All Rights Reserved.
 */
#ifndef CFileTransfer_H
#define CFileTransfer_H
/*****************************************************************************
                                INCLUDES
******************************************************************************/
#include <QtGui>
#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>

namespace ClanCor
{
    /**
     * \class CFileTransfer
     * \brief The CFileTransfer class is used to send the file via serialport or ethernet.
     */
    class CFileTransfer : public QDialog
    {
        Q_OBJECT

     public:
        /**
         * \fn CFileTransfer()
         * A constructor.
         * \brief alocate the resource for display the dialog for send the file.
         */
        CFileTransfer();

        /**
         * \fn ~CFileTransfer()
         * A destructor.
         * \brief destroys the allocated resources.
         */
        ~CFileTransfer();

        /**
         * \fn bool sendFile(const QString r_const_strFILENAME)
         * \brief This function is used to set the file which to be transfered.
         * it will show the filetransfer dialog if file exists only.
         * \param[in] r_const_strFILENAME used to set the file name.
         * \return It returns true, if file exist and transfered successfully; otherwise returns false.
         */
        bool sendFile(const QString r_const_strFILENAME);

    private:
        /**
         * \var QTcpSocket *m_tcpSocket
         * \brief used to send the data to ethernet.
         */
        QTcpSocket *m_tcpSocket;
        /**
         * \var QLabel *m_labelStatus
         * \brief used to display the file name.
         */
        QLabel *m_labelStatus;
        /**
         * \var QCheckBox *m_checkBoxViaLan
         * \brief used to set the checked for sent the file via Lan.
         */
        QCheckBox *m_checkBoxViaLan;
        /**
         * \var QLineEdit *m_lineEditIpAddress
         * \brief used to enter the Ip Address of the system.
         */
        QLineEdit *m_lineEditIpAddress;
        /**
         * \var QPushButton *m_pushButtonOk
         * \brief used for user to send the file.
         */
        QPushButton *m_pushButtonOk;
        /**
         * \var QPushButton *m_pushButtonOk
         * \brief used for user to cancel the operation.
         */
        QPushButton *m_pushButtonCancel;
        /**
         * \var QProgressBar *m_progressbarSend
         * \brief used to show the progress when file is transfering.
         */
        QProgressBar *m_progressbarSend;
        /**
         * \var QString m_strFileName
         * \brief used to store the sending file name.
         */
        QString m_strFileName;

        /**
         * \var qint64 m_nNoOfPackets
         * \brief used to store the total no of packets.
         */
        qint64 m_nNoOfPackets;
        /**
         * \var qint64 m_nNoOfBytes
         * \brief used to store the no of bytes.
         */
        qint64 m_nNoOfBytes;
        /**
         * \var qint64 m_nTotalBytes
         * \brief used to store the total no of bytes is written.
         */
        qint64 m_nTotalBytes;
        /**
         * \var bool m_bResponse
         * \brief used to store the response sucessfully.
         */
        bool m_bResponse;
        /**
         * \var bool m_bConnected
         * \brief used to the device is connected with system.
         */
        bool m_bConnected;

        /**
         * \fn void msleep(int nMsec)
         * \brief This function is used to sleep for milli seconds.
         * \param[in] nMsec used to set the milli seconds.
         */
        void msleep(int nMsec);

        /**
         * \fn bool sendData(const QByteArray r_const_byteArrayDATA,long nWait)
         * \brief This function is used to send data & and wait for response.
         * \param[in] r_const_byteArrayDATA used to set the data to be sent.
         * \param[in] nWait used to set the response time out.
         * \return It returns true, if file exist and transfered successfully; otherwise returns false.
         */
        bool sendData(const QByteArray r_const_byteArrayDATA,long nWait);

        /**
         * \fn void arrivedData()
         * \brief This function is used to read the available data from the port.
         */
        void arrivedData();

     private slots:
        /**
         * \fn void bytesWritten(qint64 nBytes)
         * \brief This function is used to update the program depends on the no of bytes written.
         * \param[in] nBytes used to set no of bytes written.
         */
        void bytesWritten(qint64 nBytes);

        /**
         * \fn on_checkBoxViaLanChk_stateChanged(int nstate)
         * \brief This function is used to check the file is transferd via lan or serialport.
         * \param[in] nstate used to get the checkbos state.
         */
        void on_checkBoxViaLanChk_stateChanged(int nstate);

        /**
         * \fn on_pushButtonOk_clicked()
         * \brief This function is used to send the file data to serialport or ethernet.
         */
        void on_pushButtonOk_clicked();

        /**
         * \fn on_pushButtonCancel_clicked()
         * \brief This function is used to cancel the file transfer and close the dialog.
         */
        void on_pushButtonCancel_clicked();
    };
}
#endif // CFileTransfer_H
