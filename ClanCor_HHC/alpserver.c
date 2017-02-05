/*******************************************************************************
 *
 * Copyright (C) u-blox ag
 *
 * u-blox ag
 * Zuercherstrasse 68
 * CH-8800 Thalwil, Switzerland
 *
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 *
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHOR NOR U-BLOX MAKES ANY
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 *******************************************************************************
 *
 * Project: u-blox 5
 *
 ******************************************************************************/
/*!
	\mainpage AlmanacPlus Sample Server 

    This project implements the server function for AlmanacPlus (ALP)


	At startup, it opens the serial port and reads the ALP 
	file into memory

	It then enables the UBX-AID-ALPSRV message. This is all
    done in the main() function.

	It then goes to an endless looop, accepting UBX-AID-ALP 
	requests from a connected GPS receiver, and supplies 
	the data required using function processAIDALPSRV(). 

	Optionally, but recommended, it modifies the in-memory 
	copy of the ALP file, improving position fixes for 
	consecutive starts. This too is in function processAIDALPSRV()

	In this demo code, additional, the message UBX-NAV-SOL 
	is decoded, and every full minute, a warmstart command 
	is issued. This code is implemented in processNAVSOL()

	This code has been successfully tested on linux devices.
	(little endian. big endian systems won't work right out 
	of the box)

	It can be compiled as follows:
	
	\verbatim
	gcc -g -Wall -o alpserver alpserver.c
	\endverbatim

	In order to use it, you need to download an ALP file from 
	http://alp.u-blox.com (http download sample code not included 
	here)

	you can then start the alpserver

	\verbatim
	./alpserver /dev/ttyACM0 115200 current_7d.alp
	\endverbatim

	/dev/ttyACM0 would be a u-blox 5 receiver connected via USB,
	115200 would be the baudrate (ignored if USB), and
	current_7d.alp is the ALP file you downloaded


	\file
	Almanac Plus Sample Server
	

*/
/*******************************************************************************
 * $Id: alpserver.c 34739 2009-08-06 11:49:57Z daniel.ammann $
 * $HeadURL: http://svn.u-blox.ch/GPS/SOFTWARE/PRODUCTS/AssistNowOfflineSample/alpserver.c $
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/termios.h>
#include "ubx.h"

#define PARSE_BUFFER_SIZE 8192	//!< Size of the parse buffer
#define ALP_MAX_SIZE 64*1024	//!< Maximum size of an ALP file (in 16-bit words)

//! ALP file data
typedef struct ALP_FILE_STRUCT
{
	U2* pFileData;  //!< Pointer to file in memory 
	U4  length;		//!< Size of file, in U2 words
	U2  fileId;		//!< ID of this file (needs to be changed if a new file is loaded)
} ALP_FILE_STRUCT_t, *ALP_FILE_STRUCT_pt;

//! Parse Handle Structure
typedef struct PARSE_HANDLE_s
{
	CH *pBuffer; //!< pointer to buffer holding data to be parsed
	CH *pWrite;  //!< pointer to byte to be written next in buffer
	CH *pEnd;    //!< end of the buffer
} PARSE_HANDLE_t, *PARSE_HANDLE_pt;


//! Process AID-ALP and eventually send data to GPS receiver
/*!
   This is the core function for implementing an ALP server 
   functionality

   The function basically
   - gets the message, as received from the ALP client 
	 (i.e. the GPS receiver)
   - in case this is a data request (i.e. the GPS receiver
     wants data from the server), it is answered
   - in case the client wants to store updated data on
	 on the server, we modify the alp file we have in memory
	 please note that this is optional (e.g if the alp file 
	 in memory is read-only), and is not necessarily
	 needed, however, if implemented, it can improve 
	 positioning accuracy

  \param gpsDes    handle to GPS device (in order to send data to)
  \param pData     pointer to received message payload
  \param size      size of payload
  \param pAlpData  pointer to memory area containing ALP file

*/
void processAIDALPSRV(II gpsDes, CH* pData, U2 size, ALP_FILE_STRUCT_pt pAlpData);


//! Parse UBX Messages
/*!
  Checks whether a valid UBX message is available at the beginning of
  the buffer.

  - checks for sync characters
  - verifies size
  - verifies checksum

  If more bytes are needed to decide whether a valid message is at hand,
  the function returns 0.

  If there's no valid message (no sync chars, non-matching checksum),
  the function returns -1.

  If a message was found, returns the size of this message

  \param pHandle    pointer to parse handle structure
  \return >0 on success, 0 on wait for data, -1 on fail
*/
II parse(PARSE_HANDLE_pt pHandle);

//! Process UBX Messages
/*!
  Processes UBX messages by doing some consistency checks
  and forwarding them to the according message handlers. 

  \param gpsDes    handle to GPS device (in order to send data to)
  \param pData     pointer to message 
  \param size      overall size (including frame)
  \param pAlpData  pointer to structure describing ALP file
*/
void process(II gpsDes, CH* pData, II size, ALP_FILE_STRUCT_pt pAlpData);

//! Process NAV-SOL and eventually issue a restart command
/*!
  
  This function processes the UBX NAVSOL message, as decoded 
  by the process() function, and restarts 
  the receiver every 60 seconds, in order to demonstrate 
  the AlmanacPlus (ALP) functionality

  \param gpsDes    handle to GPS device (in order to send data to)
  \param pData     pointer to received message payload
  \param size      size of payload
*/
void processNAVSOL(II gpsDes, CH* pData, U2 size);


//! Initialize Serial Port
/*!
  This initializes a serial port connected to a PC.
  Depending on your operating system, this might need 
  modifications or a rewrite

  This code has been tested using Linux, both with real 
  serial ports (e.g. /dev/ttyS0) as well as Serial-over-USB
  (using ACM devices, such as /dev/ttyACM0)

  Further, throughout the code, the serial port is 
  initialized, read and write using the functions 
  open(), read() and write(). This functions shall be replaced 
  with corresponding functions of your operating system
*/
II setSerialParams(II gpsDes, II baudrate);


//! Create an UBX message from a given Class/ID and payload
/*!
  This function prepares an UBX message, for later sending.
  The function allocates sufficient memory, takes 
  a payload of a certain length, and adds UBX framing, Class-,
  ID- and length fields, the payload, and adds a checksum

  Please note that \sa freeMsg must be called in order to free 
  memory allocated

  \param ubxclassid Class (higher byte) and ID (lower byte)
  \param pData pointer to memory containing payload
  \param length length of pData memory area
*/
CH * createMsg (U2 ubxclassid, CH * pData, II length);

//! Free memory as allocated by createMsg
/*! 
  \param pMsg pointer, as previously returned by createMsg()
*/
void freeMsg(CH * pMsg);


//------------------------------------------------------------------------------
void processAIDALPSRV(II gpsDes, CH* pData, U2 size, ALP_FILE_STRUCT_pt pAlpData)
{

	GPS_UBX_AID_ALPSRV_CLI_pt pMsg = (GPS_UBX_AID_ALPSRV_CLI_pt)pData;

	// The message type indicates whether this a data request
	// or a data submission
	if (pMsg->type != 0xff)
	{
		// Data request from client -> send reply message

		CH * pOutMsgPayload; // Pointer to temporary buffer where we will assemble the reply
		CH * pOutMsg;        // Pointer to temporary buffer, where the message (including UBX framing) is stored
		GPS_UBX_AID_ALPSRV_SRV_pt  pOutMsgHeader; 

		fprintf(stderr,"SERVER->CLIENT> Sending %4i bytes from offset %6i\n",
                2*(II)pMsg->size,
                2*(II)pMsg->ofs);


		// Create a buffer to hold the header + data
		pOutMsgPayload = malloc(pMsg->idSize + (pMsg->size<<1));
		if (!pOutMsgPayload)
		{
			fprintf(stderr,"unable to allocate memory.\n");
			exit(-1);
		}

		// Copy over data from the request message
		memcpy(pOutMsgPayload,pMsg,pMsg->idSize); 

		// and fill in additional values
		pOutMsgHeader = (GPS_UBX_AID_ALPSRV_SRV_pt) pOutMsgPayload;
		pOutMsgHeader->fileId = pAlpData->fileId; //
		pOutMsgHeader->dataSize = pMsg->size<<1; // client requests number of U2 values, but wants dataSize in units of U1

		// Check that we do not read beyond our buffer
		if ( pMsg->ofs + pMsg->size > pAlpData->length)
		{
			
			pOutMsgHeader->dataSize = (pAlpData->length - pMsg->ofs)<<1;
		}

		// Check that offset does not start beyond our buffer
		// This is a paranoia check, only
		if ( pMsg->ofs < pAlpData->length )
		{

			// then append actual data as requested
			memcpy(pOutMsgPayload+pMsg->idSize, // copy at end of identifier block
				   pAlpData->pFileData + pMsg->ofs, // data, offset by pMsg->ofs from start of 
				                                    // file (note: pAlpData->pFileData is a U2 pointer)
				   pOutMsgHeader->dataSize // number of bytes, as requested
				   );
		
			// and send out the UBX message
			pOutMsg = createMsg(UBXID_AID_ALPSRV,(CH *)pOutMsgPayload,pMsg->idSize + pOutMsgHeader->dataSize );
			write(gpsDes,pOutMsg,pMsg->idSize + pOutMsgHeader->dataSize + GPS_UBX_FRAME_SIZE );
			freeMsg(pOutMsg);
			free(pOutMsgPayload);
		}
	}
	else 
	{
	
		// Data submission from client -> overwrite current data

		// check if it is the right file we have loaded
		if (pMsg->fileId == pAlpData->fileId)
		{
			fprintf(stderr,"CLIENT->SERVER> Accepting %4i bytes for offset %6i for file %i\n",
                    2*(II)pMsg->size,
                    2*(II)pMsg->ofs,
					pMsg->fileId);

			// copy to the appropriate location
			memcpy(pAlpData->pFileData+pMsg->ofs,pData+pMsg->idSize,pMsg->size<<1);
		}
		else
		{
			// ignore, because client wants to update an outdated file
			fprintf(stderr,"CLIENT->SERVER> Ignoring %4i bytes for offset %6i (we have file %i, client wants to write to %i)\n",
                    2*(II)pMsg->size,
                    2*(II)pMsg->ofs,
                    (II)pAlpData->fileId,
                    (II)pMsg->fileId
					);
			
		}
	}
}

//------------------------------------------------------------------------------
void processNAVSOL(II gpsDes, CH* pData, U2 size)
{
	// get pointer to message
	GPS_UBX_NAV_SOL_pt pMsg = (GPS_UBX_NAV_SOL_pt)pData;
	// check size
	if (size == sizeof(GPS_UBX_NAV_SOL_t))
	{
		// for this example, we reset the receiver every full 
		// minute, using a warm start. We trigger this from 
		// the NAV-SOL message

		if (( pMsg->gpsFix>1) && ((U)(pMsg->iTOW/1000) % 60 == 0))
		{
			GPS_UBX_CFG_RST_t cfgRst;
			CH * pOutMsg;

			fprintf(stdout,"Resetting receiver at week %d tow %.3fs\n",pMsg->week,(R8)pMsg->iTOW/1000);
			
			// Warm start, discarding all Orbit data
			cfgRst.navBbrMask = GPS_UBX_CFG_RST_NAVBBRMASK_EPH_MASK | GPS_UBX_CFG_RST_NAVBBRMASK_ALM_MASK; 
			cfgRst.resetMode  = 0x02; // Reset mode 2 here (otherwise, USB stack reinit would cause connect/disconnect
			cfgRst.res        = 0;
			
			pOutMsg = createMsg(UBXID_CFG_RST,(CH *)&cfgRst,sizeof(cfgRst));
			write(gpsDes,pOutMsg,sizeof(cfgRst)+GPS_UBX_FRAME_SIZE);
			freeMsg(pOutMsg);
		}
	}
}

//------------------------------------------------------------------------------
II parse(PARSE_HANDLE_pt pHandle)
{
	CH  crcA = 0,crcB = 0;       // calculated crc
	CH  readCrcA, readCrcB;      // read crc
	CH* pTmp = pHandle->pBuffer; // temporary read pointer
	CH* pEnd;                    // pointer to end of message (i.e. next byte after end of message)
	U2   length;

	// are there any bytes?
	if (pHandle->pWrite <= pTmp)
	{
		// tell that we need more bytes
		return 0;
	}
	
	// check for first sync character
	if (*(pTmp++) != (CH)GPS_UBX_SYNC_CHAR_1)
	{
		// invalid first character, tell there's no ubx message at beginning of buffer
		return -1;
	}

	// are there still bytes?
	if (pHandle->pWrite <= pTmp)
	{
		// tell that we need more bytes
		return 0;
	}

	// check for second sync character
	if (*(pTmp++) != (CH)GPS_UBX_SYNC_CHAR_2)
	{
		// invalid second character, tell there's no ubx message at beginning of buffer
		return -1;
	}
	
	// are there still bytes? we need at least 4 bytes to get size (2 bytes message ID followed by 2 bytes size
	if (pHandle->pWrite <= pTmp+4)
	{
		// tell that we need more bytes
		return 0;
	}

	// copy length using a memcopy, as source pointer could be unaligned
	memcpy(&length,pTmp+2,2);
	pTmp += 4; 

	// now we need at least length bytes plus 2 bytes checksum 
	if (pHandle->pWrite <= pTmp+length+GPS_UBX_CHKSUM_SIZE)
	{
		// tell that we need more bytes
		return 0;
	}
	// make pointer to byte after last byte
	pEnd = pTmp+length+GPS_UBX_CHKSUM_SIZE;
	// adjust temporary pointer to after sync chars
	pTmp = pHandle->pBuffer + 2;

	// enough bytes for a message, now check checksum
	readCrcA = *(pEnd-2); // second last byte
	readCrcB = *(pEnd-1); // last byte

	// calculate checksum, not including the 2 last bytes being the checksum itself
	while(pTmp < pEnd - GPS_UBX_CHKSUM_SIZE )
	{
		crcA += *(pTmp++);
		crcB += crcA;
	}

	// do checksums match?
	if ((crcA != readCrcA) || (crcB != readCrcB))
	{
		// invalid checksum, there's no ubx message at beginning of buffer
		return -1;
	}

	// everything ok so far, return number of bytes + 6 header bytes + 2 checksum bytes
	return length + GPS_UBX_FRAME_SIZE;
}

//------------------------------------------------------------------------------
CH * createMsg (U2 ubxclassid, CH * pData, II length)
{
	GPS_UBX_HEAD_pt pHead = (GPS_UBX_HEAD_pt) calloc(1,length+GPS_UBX_FRAME_SIZE); // allocate sufficient memory

	CH * p = ((CH*)pHead)+GPS_UBX_HEAD_SIZE+length;   // pointer to where checksum is to be stored
	CH * q = ((CH*)pHead)+2; // pointer to beginning of where we start with checksum calculation

	if (!pHead) return NULL;

	pHead->prefix = GPS_UBX_PREFIX;
	pHead->classId = ubxclassid >>8;
	pHead->msgId =   ubxclassid & 0xff;
	pHead->size  =   length;

	memcpy(pHead+1,pData,length);
	
	// Calculate Checksum
	while(q<p)
	{
		*p     += *q++;
		*(p+1) += *p;
	}

	return (CH*)pHead;
}

//------------------------------------------------------------------------------
void freeMsg(CH * pMsg)
{
	free(pMsg);
}

//------------------------------------------------------------------------------
void process(II gpsDes, CH* pData, II size,  ALP_FILE_STRUCT_pt pAlpData)
{
	// at the beginning, there's a header
	GPS_UBX_HEAD_pt pHead = (GPS_UBX_HEAD_pt)pData;
	// then, the payload follows
	CH* pPayload = (CH*)(pHead+1);
	// payload length is without frame size
	U2 payloadSize = size - GPS_UBX_FRAME_SIZE;
	// combined cls/msgid
	U2 msgid;

	// combine ids for easier comparison
	msgid = (pHead->classId << 8) + pHead->msgId;

	// print message info
	//fprintf(stdout,"### message 0x%04X, size %d\n",msgid,pHead->size);


	// check if sizes match - just to be sure
	if (payloadSize != pHead->size)
	{
		fprintf(stderr,"ERROR: size mismatch: %d != %d",payloadSize,pHead->size);
	}

	// now process some example messages
	switch(msgid)
	{
	case UBXID_AID_ALPSRV:
		processAIDALPSRV(gpsDes,pPayload,payloadSize, pAlpData);
		break;
	case UBXID_NAV_SOL:
		// forward to NAV-SOL handler
		processNAVSOL(gpsDes,pPayload,payloadSize);
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------
II setSerialParams(II gpsDes, II baudrate)
{
	struct termios  termios;
	speed_t Bbaudrate = 9600;


	switch(baudrate)
	{
      	case 115200: Bbaudrate = B115200;break;
     	case 57600:  Bbaudrate = B57600 ;break;
     	case 38400:  Bbaudrate = B38400 ;break;
    	case 19200:  Bbaudrate = B19200 ;break;
     	case 4800:   Bbaudrate = B4800  ;break;
     	default:   
			Bbaudrate = B9600;
	}

	// Set serial port parameters
	if (tcgetattr(gpsDes, &termios) < 0)
	{
		fprintf(stderr,"ERROR: tcgetattr fails: %s\n",strerror(errno));
		return (0);
	}
	termios.c_iflag = 0;
	termios.c_oflag = 0;        /* (ONLRET) */
	termios.c_cflag = CS8 | CLOCAL | CREAD;
	termios.c_lflag = 0;
	{
		int             cnt;
		
		for (cnt = 0; cnt < NCCS; cnt++)
			termios.c_cc[cnt] = -1;
	}
	termios.c_cc[VMIN] = 100;
	termios.c_cc[VTIME] = 10;	
	if ((cfsetispeed(&termios, B115200) != 0) || (cfsetospeed(&termios, B115200) != 0))
	{
		fprintf(stderr,"ERROR: cfset[io]speed fails: %s\n",strerror(errno));
		return 0;

	}

	if (tcsetattr(gpsDes, 0, &termios) < 0) {
		fprintf(stderr,"ERROR: tcsetattr: %s\n",strerror(errno));
		return 0;
	}
	if (tcflush(gpsDes, TCIOFLUSH) < 0) {
		fprintf(stderr,"ERROR: tcflush: %s\n",strerror(errno));
		return 0;
	}
	if (fcntl(gpsDes, F_SETFL, 0) == -1) {
		fprintf(stderr,"ERROR: fcntl: %s\n",strerror(errno));
		return 0;
	}
	return 1;
}

//------------------------------------------------------------------------------
//! Main Entry
/*!
  Main function
  - check arguments
  - init parse handle
  - open gps receiver
  - read alp file into memory (ALP files can be downloaded from http://alp.u-blox.com)
  - perform parse & process, triggering ALP processing if needed
  - cleanup

  \param argc   number of arguments
  \param argv   argument string array
  \return 1 on error, 0 on success
*/
II main1(II argc, char **argv)
{
	PARSE_HANDLE_t   handle;
    II                gpsDes;  // File description to GPS device
    II                readChar = 0;
	FILE *           alpFile; // File handle to ALP file
	ALP_FILE_STRUCT_t alpData;


	// check arguments
	if (argc != 4)
	{
		// insufficient number of arguments, display usage info
		fprintf(stderr,"usage: %s <gpsdevice> <baudrate> <alpfilename>\n",argv[0]);
		return 1;
	}
   
	// check if gps receiver can be opened
	gpsDes = open(argv[1],O_RDWR | O_NONBLOCK);
	if (gpsDes == -1)
	{
		fprintf(stderr,"ERROR: unable to open port %s. exiting.\n",argv[1]);
		return 1;
	}
	// set baud rates etc
	if (!setSerialParams(gpsDes, atoi(argv[2])))
	{
		fprintf(stderr,"ERROR: unable to set serial port parameters for %s @ %s",argv[2],argv[1]);
		return 1;
		
	}

	// try to allocate buffer and init write pointer
	handle.pWrite = handle.pBuffer = (CH*)malloc(PARSE_BUFFER_SIZE);
	// check if allocation was successful
	if (handle.pBuffer == NULL)
	{
		fprintf(stderr,"ERROR: no memory to allocate buffer. exiting.\n");
		return 1;
	}
	// adjust end pointer
	handle.pEnd = handle.pBuffer + PARSE_BUFFER_SIZE;


	// read in the AlmanacPlus file
	alpFile=fopen(argv[3],"rb");
	if (!alpFile) {
		fprintf(stderr,"Unable to read %s\n",argv[3]);
		return 1;
	}
  
	alpData.pFileData = malloc(ALP_MAX_SIZE*sizeof(U2));
	if (!alpData.pFileData) 
	{
		fprintf(stderr,"Unable to allocate %i bytes\n",ALP_MAX_SIZE);
		fclose(alpFile);
		return 1;
	}

	alpData.length = fread(alpData.pFileData,sizeof(U2),ALP_MAX_SIZE,alpFile);
	if (ferror(alpFile)) 
	{
		fprintf(stderr,"Unable to read data from %s\n",argv[3]);
		free(alpData.pFileData);
		fclose(alpFile);
		return 1;
	}
  
	if (!feof(alpFile)) // all the file should be loaded now. so EOF should be set
	{
		fprintf(stderr,"File %s too large ?!?\n",argv[1]);
		free(alpData.pFileData);
		fclose(alpFile);
		return 1;
	}
	
	// In this example, we use a random number for the file number.
	// In a real application, you'd probably use a sequence number, 
	// and increase it when you serve a new file to a GPS receiver.
	
	srand(time(NULL));
	alpData.fileId = rand() & 0xFFFF;

	printf("Successfully read file %i from %s to memory (%i words)\n",alpData.fileId,argv[3],alpData.length);
	fclose(alpFile);


	// Enable the UBX-AID-ALP message (this is not necessarily
	// enable by default)
	{
		GPS_UBX_CFG_MSG_SETCURRENT_t cfgMsg = {UBXID_AID_ALPSRV>>8, UBXID_AID_ALPSRV&0xFF, 0x01} ;
		
		CH * pOutMsg = createMsg(UBXID_CFG_MSG,(CH *)&cfgMsg,sizeof(GPS_UBX_CFG_MSG_SETCURRENT_t) );
		write(gpsDes,pOutMsg,sizeof(GPS_UBX_CFG_MSG_SETCURRENT_t) + GPS_UBX_FRAME_SIZE );
		freeMsg(pOutMsg);

		// This sample code periodically resets the receiver. 
		// For that, we need to enable also the UBX-NAV-SOL
		// Naturally, in a real application, you would not want to do this
                cfgMsg.class1 =  UBXID_NAV_SOL >> 8;
		cfgMsg.msgID =  UBXID_NAV_SOL & 0xff;
		cfgMsg.rate  =  1;
		pOutMsg = createMsg(UBXID_CFG_MSG,(CH *)&cfgMsg,sizeof(GPS_UBX_CFG_MSG_SETCURRENT_t) );
		write(gpsDes,pOutMsg,sizeof(GPS_UBX_CFG_MSG_SETCURRENT_t) + GPS_UBX_FRAME_SIZE );
		freeMsg(pOutMsg);

	}

	// now read from GPS receiver in a loop, parsing bytes as they are 
	// obtained
	while(1)
	{
        II parsedBytes = 0;
		// get character
		do
		{
			; 
		} while(read(gpsDes,&readChar,1)<1); 

		if (handle.pWrite < handle.pEnd)
		{
			*(handle.pWrite++) = (CH)readChar;
		}
		else
		{
			// there's no more room for additional data
			fprintf(stderr,"WARNING: no more size in buffer\n");
			return 0;
		}
		// now try to parse it
		do
		{
			parsedBytes = parse(&handle);
			// check return value:
			//  > 0   found ubx message at beginning of buffer
			//  < 0   no ubx message found at beginning of buffer
			//  = 0   possible message at beginning of buffer, but need more bytes
			if (parsedBytes > 0)
			{
				process(gpsDes,handle.pBuffer,parsedBytes,&alpData);
				// remove all parsed bytes from buffer
				memmove(handle.pBuffer,handle.pBuffer+parsedBytes,handle.pWrite-handle.pBuffer-parsedBytes);	
				// decrement write pointer
				handle.pWrite-=parsedBytes;
			}
			else if (parsedBytes < 0)
			{
				// remove one byte and try again
				memmove(handle.pBuffer,handle.pBuffer+1,handle.pWrite-handle.pBuffer-1);
				// decrement write pointer
				handle.pWrite--;
			}
		} while(parsedBytes != 0);
	}
	fprintf(stderr,"exiting.\n");
	
	// discard ALP data in memory
	free(alpData.pFileData);

	// close file
	close(gpsDes);
	// dispose of buffer
	free(handle.pBuffer);
	// indicate success
	return 0;
}



// Local Variables:
// tab-width:4
// c-brace-offset: 0
// c-continued-statement-offset: 0
// c-indent-level: 5
// c-basic-offset: 4
// End:
