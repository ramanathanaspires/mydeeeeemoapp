/**
 * @file tfmapi.h
 *
 * PTAPI standard commands
 *
 * Copyright (C) 2001-2006 UPEK Inc.
 */

#ifndef tfmapi_h
#define tfmapi_h

#include "tfmtypes.h"

/*---------------------------------------------------------------------------*/

/**
 * @name Application General Functions
 * The Application General Functions allow to initialize the library, create
 * and close logical connections to TFM, set callbacks and perform other general
 * operations.
 */
/*@{*/

/**
 * Initialize the API library. Must be called before any other function.
 *
 * @param pMemoryFuncs Struct of pointers to the memory allocation and unallocation
 *  routines
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTInitialize(IN PT_MEMORY_FUNCS *pMemoryFuncs);


/**
 * Uninitialize the API library. Must not be called while any connection is
 * still open. There is usually no need to call this function.
 *
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTTerminate(void);


/**
 * Get information about the API version and other global information,
 * independent on any connection.
 *
 * @param ppGlobalInfo Address of a pointer which will be set to point to a global info
 *  block. The global info block is dynamically allocated by PerfectTrust and must
 *  be freed by the application.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGlobalInfo(OUT PT_GLOBAL_INFO **ppGlobalInfo);


/**
 * Enumerate TFM/ESS devices
 *
 * @param pszEnumDsn    Zero terminated ASCII string describing the TFM/ESS
 *                      connection interface, where enumeration is required,
 *                      e.g. USB. Example: "usb".
 * @param ppDeviceList  Address of the pointer, which will be set to point to
 *                      the list of found TFM/ESS devices. The data has to be
 *                      freed by a call to PTFree.
 * @return              Status code.
 */
PTAPI_DLL PT_STATUS PTAPI PTEnumerateDevices(
    IN PT_CHAR *pszEnumDsn,
    OUT PT_DEVICE_LIST **ppDeviceList
);


/**
 * Opens and prepares connection interface with TFM/ESS. In order to open communication
 * session function PTOpenSession must be called afterwards. Call PTCloseDevice
 * to close opened interface.
 *
 * @param pszDsn Zero terminated ASCII string describing the TFM/ESS connection
 *  interface parameters, e.g. port number etc. Example: "Port=COM1".
 * @param phConnection Resulting connection handle.
 * @return Status code.
 */
PTAPI_DLL PT_STATUS PTAPI PTOpenDevice(
    IN PT_CHAR *pszDsn,
    OUT PT_CONNECTION *phConnection
);


/**
 * Open communication session with TFM/ESS device. Connection interface must be
 * opened by previous call of PTOpenDevice.
 *
 * @param hConnection Connection handle to opened device interface.
 * @param pszDsn Currently not used, can be NULL.
 * @return Status code.
 */
PTAPI_DLL PT_STATUS PTAPI PTOpenSession(
    IN PT_CONNECTION hConnection,
    IN PT_CHAR *pszDsn
);


/**
 * Open new "local" connection to TFM.
 *
 * @param pszDsn Zero terminated ASCII string describing the TFM connection
 *  parameters, e.g. port number etc. Example: "Port=COM1".
 * @param phConnection Resulting connection handle. At the end of the connection
 *  it should be closed using PTClose. To close local connection you should  call
 *  PTClose().
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTOpen(
    IN PT_CHAR *pszDsn,
    OUT PT_CONNECTION *phConnection
);


/**
 * Close communication session, device interface remains open.
 *
 * @param hConnection Connection handle to opened session.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTCloseSession(IN PT_CONNECTION hConnection);


/**
 * Close connection interface, if communication session is still opened it is
 * automatically closed.
 *
 * @param hConnection Connection handle to opened connection interface or session.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTCloseDevice(IN PT_CONNECTION hConnection);


/**
 * Close a connection previously opened by PTOpen().
 *
 * @param hConnection Connection handle of the connection to be closed.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTClose(IN PT_CONNECTION hConnection);


/**
 * Sets the address of the callback routine to be called if any called function
 * involves displaying a biometric user interface. The callback functionality is
 * described below.
 *
 * @param hConnection Connection handle
 * @param pfnGuiStreamingCallback A pointer to an application callback to deal with the
 *  presentation of biometric streaming data. Reserved for future used, currently not
 *  implemented. Use NULL for this parameter.
 * @param pGuiStreamingCallbackCtx A generic pointer to context information provided by the
 *  application that will be presented on the callback. Reserved for future used,
 *  currently not implemented. Use NULL for this parameter.
 * @param pfnGuiStateCallback A pointer to an application callback to deal with GUI state changes
 * @param pGuiStateCallbackCtx A generic pointer to context information provided by the
 *  application that will be presented on the callback
 * @return Status code
 *
 * Application has three basic options:
 *  - Use @c pfnGuiStateCallback == NULL. In this case no user interface will be displayed.
 *  - Use @c pfnGuiStateCallback == PT_STD_GUI_STATE_CALLBACK. This will display the standard
 *  Perfect Trust built-in user interface. In this variant @c pGuiStateCallbackCtx can have
 *  the value of the window handle to the window, which should serve as the parent for the UI.
 *  Could be NULL, if the UI windows should have no parent.
 *  - Use @c pfnGuiStateCallback == your own callback. In this case your callback will be responsible
 *  for displaying the user interface.
 *
 * The default settings before the first call are @c pfnGuiStateCallback == PT_STD_GUI_STATE_CALLBACK
 * and @c pGuiStateCallbackCtx == NULL.
 *
 * Example:
 * @code
 * HWND hWnd;
 * PT_STATUS status;
 *
 * hWnd = GetActiveWindow ();
 * status = PTSetGUICallbacks(hConnection, NULL, NULL, PT_STD_GUI_STATE_CALLBACK, (void *)hWnd);
 * @endcode
 */
PTAPI_DLL PT_STATUS PTAPI PTSetGUICallbacks(
    IN PT_CONNECTION hConnection,
    IN PT_GUI_STREAMING_CALLBACK pfnGuiStreamingCallback,
    IN void *pGuiStreamingCallbackCtx,
    IN PT_GUI_STATE_CALLBACK pfnGuiStateCallback,
    IN void *pGuiStateCallbackCtx
);


/**
 * Open a new connection to a remote instance of PTAPI library, set the address
 * of a communication callback for this connection and return a connection handle.
 * The callback function is described at the description of PT_COMM_CALLBACK.
 *
 * @param pfnCommCallback Application-provided callback to pass data packet to/from
 *    the remote library instance.
 * @param pCommCallbackCtx A general value passed to the callback and remembered for
 *  given connection handle. From now on this value will be used in all callbacks
 *  generated by calls using given connection handle.
 * @param phConnection Resulting connection handle. At the end of the connection it
 *  should be closed using PTClose.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTOpenRemote(
    IN PT_COMM_CALLBACK pfnCommCallback,
    IN void *pCommCallbackCtx,
    OUT PT_CONNECTION *phConnection
);


/**
 * Send the request data packet to the FM, wait for a response and get the response data
 * packet. This is a blocking function, which does not return until the request is
 * processed. The request data are created by PT_COMM_CALLBACK function and response data
 * must be passed to PT_COMM_CALLBACK function as return value.
 *
 * @param hConnection Handle to the connection to FM.
 * @param pInPkt Packet, which has to be submitted to FM
 * @param ppOutPkt Address of pointer which will be set to the response packet data. The
 *    data has to be discarded by a call to PTFree().
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTTransact(
    IN PT_TFM hConnection,
    IN PT_DATA *pInPkt,
    OUT PT_DATA **ppOutPkt
);


/**
 * Releases memory block using deallocation function passed to API by PTInitialize() call.
 * This function may be used for releasing structures allocated by other API functions.
 */
PTAPI_DLL void PTAPI PTFree(void *Memblock);

/*@}*/
/*---------------------------------------------------------------------------*/

/**
 * @name PerfectTrust Biometric functions
 * This section has been strongly inspired by the BioAPI standard. The function calls
 * are practically the same, except for different naming of the parameter types.
 * BioAPI is using its own type definitions, too specialized to be used in PerfectTrust.
 * Also some parameters were simplified and some handles replaced by pointers to binary
 * data blocks.
 */
/*@{*/

/**
 * Scan the living finger and return the scanned image.
 *
 * @param hConncetion Handle to the connection to FM
 * @param byType Requested type of the returned data. The data may be compressed,
 *  subsampled, etc. Use one of the PT_GRAB_TYPE_xxx values.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param boWaitForAcceptableFinger - If PT_TRUE, the function verifies the quality of
 *  the finger image and returns only when the finger quality would be acceptable for
 *  other biometric functions. If PT_FALSE, the function return immediately without
 *  verifying image quality.
 * @param ppGrabbedData Address of the pointer, which will be set to point to the
 *  resulting grabbed data. The data has to be discarded by a call to PTFree().
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGrab(
    IN PT_CONNECTION hConnection,
    IN PT_BYTE byType,
    IN PT_LONG lTimeout,
    IN PT_BOOL boWaitForAcceptableFinger,
    OUT PT_DATA **ppGrabbedData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);

/**
 * Scan the live finger and return the scanned image. Only a defined window of
 * the sensor will be returned.
 *
 * @param hConnection Handle to the connection to FM.
 * @param byCompressionType Requested type of compression of the data. Use one
 *        of the PT_GRAB_COMPRESSION_TYPE_xxxx values.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param boWaitForAcceptableFinger If PT_TRUE, the function verifies the
 *        quality of the finger image and returns only when the finger quality
 *        would be acceptable for other biometric functions. If PT_FALSE, the
 *        function returns immediately without verifying image quality.
 * @param lRows Number of rows to grab. This is the number of actually grabbed
 *        rows, taking into account the subsampling factor. Example: If
 *        lRows=4, lRowOffset=10 and lRowDelta=2, the resulting image will
 *        contain rows 10, 12, 14 and 16. This is the number of actually
 *        grabbed rows, taking into account the subsampling factor.
 * @param lCols Number of columns to grab
 * @param lRowOffset First row to grab. [0,0] = Upper left corner.
 * @param lColOffset First column to grab. [0,0] = Upper left corner.
 * @param lRowDelta Subsampling factor = number of rows to advance between the
 *        neighbour used rows. 1=Normal full image.
 * @param lColDelta Subsampling factor = number of columns to advance between the
 *        neighbour used columns. 1=Normal full image.
 * @param ppGrabbedData Address of the pointer, which will be set to point to
 *        the resulting grabbed data. The data has to be discarded by a call
 *        to PTFree().
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code.
 *
 * Note: Due to memory limitations TFM it is not possible to grab the full
 * image from the whole sensor. The caller has to use such combination of
 * lRows, lCols and lRowDelta, lColDelta parameters to fit into the memory
 * requirements. Otherwise PTGrabWindow will return an error.
 * You can use PTInfo function to get the max. guaranteed size of the output
 * data. The value is stored in MaxGrabWindow field. The value is valid for
 * uncompressed images; for compress images please review the description of
 * given compression method to get relevant data.
 * MaxGrabWindow is the max. guaranteed size of the output data in bytes.
 * Therefore the following equation applies:
 * MaxGrabWindow >= lRows * lCols
 * Please note that MaxGrabWindow is just the max. guaranteed size. It is
 * possible that in some cases PTGrabWindow may succeed even for bigger image
 * data, but this is not guaranteed.
 */
PTAPI_DLL PT_STATUS PTAPI PTGrabWindow(
    IN PT_CONNECTION hConnection,
    IN PT_BYTE byCompressionType,
    IN PT_LONG lTimeout,
    IN PT_BOOL boWaitForAcceptableFinger,
    IN PT_LONG lRows,
    IN PT_LONG lRowOffset,
    IN PT_LONG lRowDelta,
    IN PT_LONG lCols,
    IN PT_LONG lColOffset,
    IN PT_LONG lColDelta,
    OUT PT_DATA **ppGrabbedData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Scan the live finger and process it into a template. The last template obtained
 * through PTCapture will be remembered throughout the session and can be used by
 * biometric matching functions. In addition it can be optionally returned to the caller.
 * This function can call GUI callbacks.
 *
 * @param hConnection Handle to the connection to FM
 * @param byPurpose Purpose of the enrollment. Use one of the PT_PURPOSE_xxxx values.
 * @param ppCapturedTemplate Address of the pointer, which will be set to point to the
 *  resulting template (BIR). The template has to be discarded by a call to PTFree().
 *  If the template should be only remembered for use of next functions, leave this
 *  parameter NULL
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param ppAuditData Reserved, use NULL.
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTCapture(
    IN PT_CONNECTION hConnection,
    IN PT_BYTE byPurpose,
    OUT PT_BIR **ppCapturedTemplate,
    IN PT_LONG lTimeout,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);

/**
 * Scan the live finger once or several times, depending on the session settings,
 * and combine the images into one enrollment template. The last template obtained
 * through PTEnroll will be remembered throughout the session and can be used by
 * biometric matching functions. This function can call GUI callbacks.
 *
 * @param hConnection Handle to the connection to FM
 * @param byPurpose Purpose of the enrollment. Use one of the PT_PURPOSE_xxxx values.
 * @param pStoredTemplate Reserved, use NULL.
 * @param ppNewTemplate Address of the pointer, which will be set to point to the resulting
 *  template (BIR). The template has to be discarded by a call to @c PTFree(). If the
 *  template should be stored only in TFM's non-volatile memory, leave this parameter NULL.
 * @param plSlotNr Pointer to a variable which receives slot number (0..N-1)
 *  where the template was stored. If the value is NULL, template is not stored on TFM.
 * @param pPayload Data to be embedded into the resulting template. Payload data is
 *  an output parameter from @c PTVerify and @c PTVerifyEx when successful match is
 *  achieved.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param ppAuditData Reserved, use NULL.
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTEnroll(
    IN PT_CONNECTION hConnection,
    IN PT_BYTE byPurpose,
    IN PT_INPUT_BIR *pStoredTemplate,
    OUT PT_BIR **ppNewTemplate,
    OUT PT_LONG *plSlotNr,
    IN PT_DATA *pPayload,
    IN PT_LONG lTimeout,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Match the supplied captured template against the supplied enrollment template.
 * This function does not scan live finger and therefore does not call GUI callbacks.
 *
 * @param hConnection Handle to the connection to FM
 * @param plMaxFARRequested Max. FAR requested by the caller. Value of this parameter
 *  is currently ignored.
 * @param plMaxFRRRequested Max. FRR requested by the caller. Optional, can be NULL.
 *  Value of this parameter is currently ignored.
 * @param pboFARPrecedence If both FAR and FRR are provided, this parameter decides
 *  which of them takes precedence: PT_TRUE -> FAR, PT_FALSE -> FRR. Value of this
 *  parameter is currently ignored.
 * @param pCapturedTemplate The template to verify - BIR data or one of the predefined
 *  handles. If NULL, the result of the last PTCapture or PTEnroll will be used.
 * @param pStoredTemplate The template to be verified against - BIR data or one of
 *  the predefined handles.
 * @param ppAdaptedTemplate Reserved, use NULL.
 * @param pboResult The result: Match/no match
 * @param plFARAchieved Reserved, use NULL.
 * @param plFRRAchieved Reserved, use NULL.
 * @param ppPayload Address of the pointer, which will be set to point to the payload
 *  data, originally embedded in the @c pStoredTemplate. Payload data is available
 *  only when successful match is achieved.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTVerifyMatch(
    IN PT_CONNECTION hConnection,
    IN PT_LONG *plMaxFARRequested,
    IN PT_LONG *plMaxFRRRequested,
    IN PT_BOOL *pboFARPrecedence,
    IN PT_INPUT_BIR *pCapturedTemplate,
    IN PT_INPUT_BIR *pStoredTemplate,
    OUT PT_BIR **ppAdaptedTemplate,
    OUT PT_BOOL *pboResult,
    OUT PT_LONG *plFARAchieved,
    OUT PT_LONG *plFRRAchieved,
    OUT PT_DATA **ppPayload
);


/**
 * Scan the live finger or use the last captured finger data and try to match it
 * against the supplied enrollment template. If the functions scans live finger, the
 * template obtained will be remembered throughout the session and can be used by
 * other biometric matching functions. This function can call GUI callbacks (unless
 * boCaptured is FALSE);
 *
 * @param hConnection Handle to the connection to FM
 * @param plMaxFARRequested Max. FAR requested by the caller. Value of this parameter
 *  is currently ignored.
 * @param plMaxFRRRequested Max. FRR requested by the caller. Optional, can be NULL.
 *  Value of this parameter is currently ignored.
 * @param pboFARPrecedence If both FAR and FRR are provided, this parameter decides
 *  which of them takes precedence: PT_TRUE -> FAR, PT_FALSE -> FRR. Value of this
 *  parameter is currently ignored.
 * @param pStoredTemplate The template to be verified against - BIR data or one of
 *  the predefined handles.
 * @param ppAdaptedTemplate Reserved, use NULL.
 * @param pboResult The result: Match/no match
 * @param plFARAchieved Reserved, use NULL.
 * @param plFRRAchieved Reserved, use NULL.
 * @param ppPayload Address of the pointer, which will be set to point to the payload
 *  data, originally embedded in the @c pStoredTemplate. Payload data is available
 *  only when successful match is achieved.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param boCapture If PT_TRUE, PTVerify at first captures live fingerprint. If
 *  PT_FALSE, result of the last finger capturing function (e.g. PTCapture or PTEnroll)
 *  will be used.
 * @param ppAuditData Reserved, use NULL.
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTVerify(
    IN PT_CONNECTION hConnection,
    IN PT_LONG *plMaxFARRequested,
    IN PT_LONG *plMaxFRRRequested,
    IN PT_BOOL *pboFARPrecedence,
    IN PT_INPUT_BIR *pStoredTemplate,
    OUT PT_BIR **ppAdaptedTemplate,
    OUT PT_BOOL *pboResult,
    OUT PT_LONG *plFARAchieved,
    OUT PT_LONG *plFRRAchieved,
    OUT PT_DATA **ppPayload,
    IN PT_LONG lTimeout,
    IN PT_BOOL boCapture,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Scan the live finger or use the last captured finger data and try to match it
 * against the set of supplied enrollment templates. If the function scans live
 * finger, the template obtained will be remembered throughout the session and
 * can be used by other biometric matching functions. Return the index of the
 * best matching template or -1 if no match.
 *
 * This is an extension to BioAPI. Its main purpose is to be able to match user's
 * finger against all his enrolled fingers (i.e. up to 10 fingers) without the necessity
 * to ask user several times to scan his finger.
 *
 * @param hConnection Handle to the connection to FM
 * @param plMaxFARRequested Max. FAR requested by the caller. Value of this parameter
 *  is currently ignored.
 * @param plMaxFRRRequested Max. FRR requested by the caller. Optional, can be NULL.
 *  Value of this parameter is currently ignored.
 * @param pboFARPrecedence If both FAR and FRR are provided, this parameter decides
 *  which of them takes precedence: PT_TRUE -> FAR, PT_FALSE -> FRR. Value of this
 *  parameter is currently ignored.
 * @param pStoredTemplates An array of templates to be verified against - BIR data
 *  or one of the predefined handles.
 * @param byNrTemplates Number of templates in @c pStoredTemplates
 * @param ppAdaptedTemplate Reserved, use NULL.
 * @param pshResult The result: The zero-based index of the best matching template
 *  or -1 if no match.
 * @param plFARAchieved Reserved, use NULL.
 * @param plFRRAchieved Reserved, use NULL.
 * @param ppPayload Address of the pointer, which will be set to point to the payload
 *  data, originally embedded in the @c pStoredTemplate. Payload data is available
 *  only when successful match is achieved.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param boCapture If PT_TRUE, PTVerifyEx at first captures live fingerprint. If
 *  PT_FALSE, result of the last finger capturing function (e.g. PTCapture or
 *  PTEnroll) will be used.
 * @param ppAuditData Reserved, use NULL.
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTVerifyEx(
    IN PT_CONNECTION hConnection,
    IN PT_LONG *plMaxFARRequested,
    IN PT_LONG *plMaxFRRRequested,
    IN PT_BOOL *pboFARPrecedence,
    IN PT_INPUT_BIR *pStoredTemplates,
    IN PT_BYTE byNrTemplates,
    OUT PT_BIR **ppAdaptedTemplate,
    OUT PT_SHORT *pshResult,
    OUT PT_LONG *plFARAchieved,
    OUT PT_LONG *plFRRAchieved,
    OUT PT_DATA **ppPayload,
    IN PT_LONG lTimeout,
    IN PT_BOOL boCapture,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Scan the live finger or use the last captured finger data and try to match it
 * against the templates stored in TFM's non-volatile memory. If the function scans
 * live finger, the template obtained will be remembered throughout the session and
 * can be used by other biometric matching functions. Return the slot of the
 * best matching template or -1 if no match.
 *
 * This is an extension to BioAPI. Its main purpose is to be able to match user's
 * finger against all the enrolled templates in the TFM's database, but without the
 * complexity of the heavy-weight BioAPI database mechanism. This is not a real
 * one-to-many matching, but one-to-few matching.
 *
 * @param hConnection Handle to the connection to TFM
 * @param plMaxFARRequested Max. FAR requested by the caller. Value of this parameter
 *  is currently ignored.
 * @param plMaxFRRRequested Max. FRR requested by the caller. Optional, can be NULL.
 *  Value of this parameter is currently ignored.
 * @param pboFARPrecedence If both FAR and FRR are provided, this parameter decides
 *  which of them takes precedence: PT_TRUE -> FAR, PT_FALSE -> FRR. Value of this
 *  parameter is currently ignored.
 * @param ppAdaptedTemplate Reserved, use NULL.
 * @param plResult The result: The zero-based index of the best matching template
 *  or -1 if no match.
 * @param plFARAchieved Reserved, use NULL.
 * @param plFRRAchieved Reserved, use NULL.
 * @param ppPayload Address of the pointer, which will be set to point to the payload
 *  data, originally embedded in the @c pStoredTemplate. Payload data is available
 *  only when successful match is achieved.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout.
 * @param boCapture If PT_TRUE, PTVerifyEx at first captures live fingerprint. If
 *  PT_FALSE, result of the last finger capturing function (e.g. PTCapture or
 *  PTEnroll) will be used.
 * @param ppAuditData Reserved, use NULL.
 * @param pSignData Reserved, use NULL.
 * @param ppSignature Reserved, use NULL.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTVerifyAll(
    IN PT_CONNECTION hConnection,
    IN PT_LONG *plMaxFARRequested,
    IN PT_LONG *plMaxFRRRequested,
    IN PT_BOOL *pboFARPrecedence,
    OUT PT_BIR **ppAdaptedTemplate,
    OUT PT_LONG *plResult,
    OUT PT_LONG *plFARAchieved,
    OUT PT_LONG *plFRRAchieved,
    OUT PT_DATA **ppPayload,
    IN PT_LONG lTimeout,
    IN PT_BOOL boCapture,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Verifies, if there is a finger on the sensor. If Timeout is nonzero, the function
 * waits for the specified time interval until the required conditions are met.
 *
 * This function is an extension to BioAPI. BioAPI handles finger detection through
 * MODULE_EVENT events. However, this mechanism is not suitable for implementation
 * on FM (requires a possibility to send out asynchronous events, while FM is purely
 * slave device). If needed, a BioAPI-compatible event behavior can be built using
 * the PTDetectFingerEx function, but the implementation will be inefficient.
 *
 * PTDetectFingerEx is a superset of an obsolete function PTDetectFinger, which was
 * used in previous versions of FM. PTDetectFinger is equivalent to
 * PTDetectFingerEx (hConnection, lTimeout, PT_DETECT_ACCEPTABLE | PT_DETECT_GUI).
 *
 * @param hConnection Handle to the connection to TFM
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout. "0" is an
 *   acceptable value for this function, it means "test if the current state meats
 *   the required conditions".
 * @param dwFlags Bit mask, determining the behavior of the function and the conditions
 *   for which the function waits.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTDetectFingerEx(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lTimeout,
    IN PT_DWORD dwFlags
);


/**
 * Stores given fingerprint template in the selected slot in the non-volatile memory
 * of the TFM. If pTemplate is NULL, it only clears the slot.
 *
 * This function is an extension to BioAPI. The standard BioAPI interface for this
 * functionality are the database functions (DbStoreBIR, DbGetBIR etc.). However,
 * this interface is too heavyweight for the TFM's needs.
 *
 * The template cache consists of a predefined number of "slots". The slots are
 * numbered 0..N-1 and accessible through setting byForm field in the PT_INPUT_BIR
 * to PT_SLOT_INPUT.
 *
 * The "N" depends on the model of the TFM and can be found using the @c PTInfo() call.
 * Please note, that the real number of templates storable in TFM is further limited
 * by the available memory and can be therefore lower than "N".
 *
 * @param hConnection Handle to the connection to TFM
 * @param pTemplate Template (BIR) to be stored in the template cache
 * @param plSlotNr Pointer to a variable which receives slot number (0..N-1)
 *  where the template was stored. If the value is NULL, the template is not stored.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTStoreFinger(
    IN PT_CONNECTION hConnection,
    IN PT_INPUT_BIR *pTemplate,
    OUT PT_LONG *plSlotNr
);


/**
 * Deletes fingerprint template stored in the selected slot in the non-volatile memory
 * of the FM.
 *
 * This function is an extension to BioAPI. The standard BioAPI interface for this
 * functionality are the database functions (DbStoreBIR, DbGetBIR etc.). However,
 * this interface is too heavyweight for the FM's needs.
 *
 * @param hConnection Handle to the connection to FM
 * @param lSlotNr Number of slot to delete (0..N-1)
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTDeleteFinger(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr
);

/**
 * Deletes all fingerprint templates stored in slots in the non-volatile memory
 * of the FM.
 *
 * This function is an extension to BioAPI. The standard BioAPI interface for this
 * functionality are the database functions (DbStoreBIR, DbGetBIR etc.). However,
 * this interface is too heavyweight for the FM's needs.
 *
 * @param hConnection Handle to the connection to FM.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTDeleteAllFingers(
    IN PT_CONNECTION hConnection
);


/**
 * Assign an additional application data to a finger template stored in FM's
 * non-volatile memory.
 *
 * @param hConnection Handle to the connection to FM.
 * @param lSlotNr The slot number of the template to be associated with data.
 * @param pFingerData The data to be stored together with the template. If
 *  the data length is zero, the application data associated with given fingerprint
 *  will be deleted
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSetFingerData(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr,
    IN PT_DATA *pFingerData
);


/**
 * Read the additional application data associated with a finger template stored
 * in FM's non-volatile memory.
 *
 * @param hConnection Handle to the connection to FM.
 * @param lSlotNr The slot number of the template whose application data should
 *  be read.
 * @param ppFingerData Address of the pointer, which will be set to point to the
 *  application data associated with given fingerprint. If no data are associated
 *  with the fingerprint, the result will be a data block with zero length. The
 *  data has to be freed by a call to PTFree.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetFingerData(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr,
    OUT PT_DATA **ppFingerData
);


/**
 * Return list of all fingers stored in the FM's non-volatile memory together with
 * their associated application data.
 *
 * @param hConnection Handle to the connection to FM.
 * @param ppFingerList Address of the pointer, which will be set to point to the list
 *  of stored fingerprints and their associated data. The data has to be freed by
 *  a call to PTFree.
 */
PTAPI_DLL PT_STATUS PTAPI PTListAllFingers(
    IN PT_CONNECTION hConnection,
    OUT PT_FINGER_LIST **ppFingerList
);


/**
 * Read template data stored in given slot.
 *
 * @param hConnection Handle to the connection to FM
 * @param lSlotNr Number of slot from which the template should be read
 * @param boReturnPayload If TRUE then the template is returned with its payload.
 * @param ppStoredTemplate Address of the pointer, which will be set to point to the
 *  loaded template (BIR). The template has to be discarded by a call to PTFree().
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTLoadFinger(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr,
    IN PT_BOOL boReturnPayload,
    OUT PT_BIR **ppStoredTemplate
);


/**
 * Change payload data of a finger template stored in TFM's
 * non-volatile memory.
 *
 * @param hConnection Handle to the connection to TFM.
 * @param lSlotNr The slot number of the template which payload data has to be set.
 * @param pPayload New payload data.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSetFingerPayload(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr,
    IN PT_DATA *pPayload
);


/**
 * Update payload data of a finger template stored in TFM's
 * non-volatile memory.
 *
 * @param hConnection Handle to the connection to TFM.
 * @param lSlotNr The slot number of the template which payload data has to be changed.
 * @param lOffset Offset from which are the payload data changed.
 * @param pData Data to be stored at the given offset in payload.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTUpdateFingerPayload(
    IN PT_CONNECTION hConnection,
    IN PT_LONG lSlotNr,
    IN PT_LONG lOffset,
    IN PT_DATA *pData
);


/**
 * Switch FM to navigation mode (a.k.a. biometric mouse). In this mode FM will provide
 * navigation info to the host.
 *
 * During the PTNavigate call the FM sends periodically packets with navigation data
 * to the host. The arrived packets trigger calling the pfnCallback to deliver the data
 * to the application. Please note, that a new callback will not be called until the
 * current returns. If the callback processing takes too long, some navigation data
 * may be lost. Also other communication errors may lead to a lost navigation data -
 * due to the nature of navigation it makes no sense to use error-correcting protocol.
 *
 * If lEventPeriod = -1, FM will use on-demand mode. In this mode FM at beginning sends
 * one navigation data packet and then waits with sending next navigation data until it
 * receives a request from the host. The request is sent every time when the pfnCallback
 * function on the host returns. This mode is suitable for host applications with slow
 * callback processing, it protects against losing navigation data due to an overrun.
 *
 * PTNavigate will finish, when the pfnCallback returns with cancel request value. Due
 * to asynchronous communication the host may still receive a few navigation callbacks
 * after the cancel was requested.
 *
 * @param hConnection Handle to the connection to FM
 * @param lEventPeriod Delay in milliseconds between sending navigation data from FM.
 *    FM will send one packet per period, with all the navigation data accumulated
 *    over the period. If lEventPeriod is set to "-1", FM will use an on-demand mode.
 * @param pfnCallback Callback function, called every time when a navigation data packet
 *    arrives to the host.
 * @param pNavigationCallbackCtx A generic pointer to context data. This pointer will
 *    be supplied to the callback function every time it is called.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTNavigate (
    IN PT_CONNECTION hConnection,
    IN PT_LONG lEventPeriod,
    IN PT_NAVIGATION_CALLBACK pfnCallback,
    IN void *pNavigationCallbackCtx
);


/**
 * Return scan quality of last finger swipe
 *
 * @param hConnection Handle to the connection to FM
 * @param pdwScanQuality Returns scan quality of last finger swipe
 * @result Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTScanQuality(
    IN PT_CONNECTION hConnection,
    OUT PT_DWORD *pdwScanQuality
);


/**
 * Return information about last finger swipe
 *
 * @param hConnection Handle to the connection to FM
 * @param ppSwipeInfo Address of the pointer, which will be set to point to the
 *   resulting PT_SWIPE_INFO structure with last swipe information. The structure
 *   has to be discarded by a call to PTFree().
 * @param ppSkewInfo When not NULL, it represents the address of the pointer, which
 *  will be set to point to the last swipe skew information. The skew information
 *  has to be discarded by a call to PTFree().
 * @param ppSpeedInfo When not NULL, it represents the address of the pointer, which
 *  will be set to point to the last swipe speed information. The speed information
 *  has to be discarded by a call to PTFree().
 *
 * @result Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetSwipeInfo(
    IN PT_CONNECTION hConnection,
    OUT PT_SWIPE_INFO **ppSwipeInfo,
    OUT PT_DATA **ppSkewInfo,
    OUT PT_DATA **ppSpeedInfo
);


/**
 * Switches FM to the standby (finger detect) mode. If finger is detected, the FM wakes
 * up and immediately starts an image grabbing operation. This function is especially
 * useful for low-power image grabbing.
 *
 * @param hConnection Handle to the connection to FM
 * @param pfnCallback Callback function, called periodically all the time FM is sleeping.
 *     Optional, can be NULL. See the description of PT_IDLE_CALLBACK.
 * @param pIdleCallbackCtx A generic pointer to callback's context data. This pointer
 *     will be supplied to the callback function every time it is called.
 * @param byGrabType Requested type of the returned data. the data may be compressed,
 *     subsampled, etc. Use one of the PT_GRAB_TYPE_xxxx values.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout. This timeout
 *     controls the max. time between HW finger detect (finger touched the metallic
 *     frame of the sensor) and start of the swipe (finger touched the sensor's
 *     surface). Timeout does not include the time needed for the grab itself (once
 *     the swipe starts, it will not be interrupted), image processing and transfer
 *     to the host. We recommend to use a short time, e.g. 1 sec.
 * @param boAssessImageQuality If PT_TRUE, the function will after a successful grab
 *     perform also image quality analysis. If there is any problem with the image
 *     quality, it will be reported via the pdwGrabGuiMessage. This parameter controls
 *     the same image quality checks, which are controlled in PTGrab by
 *     boWaitForAcceptableFinger.
 * @param pdwWakeupCause The cause of wakeup. Currently the following causes are
 *     possible: PT_WAKEUP_CAUSE_HOST (0) (signal from the Host) or
 *     PT_WAKEUP_CAUSE_FINGER (1) (a finger was detected)
 * @param pdwGrabGuiMessage Assessment of the quality of the grab result. It is used
 *     to indicate problems like too fast, too skewed or too short finger swipe, or
 *     image quality problems (e.g. too right, too left etc.). The codes returned are
 *     the same as the GUI message codes in GUI callbacks (PT_GUIMSG_xxxx). Good image
 *     is indicated by a code PT_GUIMSG_GOOD_IMAGE. pdwGrabGuiMessage is valid only if
 *     *pdwWakeupCause is PT_WAKEUP_CAUSE_FINGER.
 * @param ppGrabbedData Address of the pointer, which will be set to point to the
 *     resulting grabbed data. The data has to be discarded by a call to pfnFree()
 *     (see PT_MEMORY_FUNCS). Valid only if *pdwWakeupCause is PT_WAKEUP_CAUSE_FINGER
 *     *pdwGrabGuiMessage is PT_GUIMSG_GOOD_IMAGE.
 * @param pSignData Reserved, use NULL
 * @param ppSignature Reserved, use NULL
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSleepThenGrab(
    IN PT_CONNECTION hConnection,
    IN PT_IDLE_CALLBACK pfnCallback,
    IN void *pIdleCallbackCtx,
    IN PT_BYTE byGrabType,
    IN PT_LONG lTimeout,
    IN PT_BOOL boAssessImageQaulity,
    OUT PT_DWORD *pdwWakeupCause,
    OUT PT_DWORD *pdwGrabGuiMessage,
    OUT PT_DATA **ppGrabbedData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);


/**
 * Switches FM to the standby (finger detect) mode. If finger is detected, the FM wakes
 * up and immediately scans the finger and processes it into a template. The last
 * template obtained through PTSleepThenCapture will be remembered throughout the session
 * and can be used by biometric matching functions. In addition the template can be
 * optionally returned to the caller. This function is especially useful for low-power
 * capturing.
 *
 * @param hConnection Handle to the connection to FM
 * @param pfnCallback Callback function, called periodically all the time FM is sleeping.
 *     Optional, can be NULL. See the description of PT_IDLE_CALLBACK.
 * @param pIdleCallbackCtx A generic pointer to callback's context data. This pointer
 *     will be supplied to the callback function evry time it is called.
 * @param byPurpose Purpose of the enrollment. Use one of the PT_PURPOSE_xxxx values.
 * @param lTimeout Timeout in milliseconds. "-1" means default timeout. This timeout
 *     controls the max. time between HW finger detect (finger touched the metallic
 *     frame of the sensor) and start of the swipe (finger touched the sensor's
 *     surface). Timeout does not include the time needed for the scan itself (once
 *     the swipe starts, it will not be interrupted), template processing and transfer
 *     to the host. We recommend to use a short time, e.g. 1 sec.
 * @param pdwWakeupCause The cause of wakeup. Currently the following causes are
 *     possible: PT_WAKEUP_CAUSE_HOST (0) (signal from the Host) or
 *     PT_WAKEUP_CAUSE_FINGER (1) (a finger was detected)
 * @param pdwCaptureGuiMessage Assessment of the quality of the capture result. It is used
 *     to indicate problems like too fast, too skewed or too short finger swipe, or
 *     image quality problems (e.g. too right, too left etc.). The codes returned are
 *     the same as the GUI message codes in GUI callbacks (PT_GUIMSG_xxxx). Good image
 *     is indicated by a code PT_GUIMSG_GOOD_IMAGE. pdwGrabGuiMessage is valid only if
 *     *pdwWakeupCause is PT_WAKEUP_CAUSE_FINGER.
 * @param ppCapturedTemplate Address of the pointer, which will be set to point to the
 *     resulting template (BIR). The template has to be discarded by a call to PTFree().
 *     If the template should be only remembered for use of next functions and not returned
 *     to the host, leave this parameter NULL
 * @param ppAuditData Reserved, use NULL
 * @param pSignData Reserved, use NULL
 * @param ppSignature Reserved, use NULL
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSleepThenCapture(
    IN PT_CONNECTION hConnection,
    IN PT_IDLE_CALLBACK pfnCallback,
    IN void *pIdleCallbackCtx,
    IN PT_BYTE byPurpose,
    IN PT_LONG lTimeout,
    OUT PT_DWORD *pdwWakeupCause,
    OUT PT_DWORD *pdwCaptureGuiMessage,
    OUT PT_BIR **ppCapturedTemplate,
    OUT PT_BIR **ppAuditData,
    IN PT_DATA *pSignData,
    OUT PT_DATA **ppSignature
);

/*@}*/
/*---------------------------------------------------------------------------*/

/**
 * @name PerfectTrust Miscellaneous functions
 */
/*@{*/

/**
 * Return a set of information about the connection and the TFM, including the version
 * of TFM.
 *
 * @param hConnection Handle to the connection to TFM
 * @param pInfo  Address of the pointer, which will be set to point to the structure
 *   with TFM/ESS information. The structure has to be freed by a call to PTFree.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTInfo(IN PT_CONNECTION hConnection, OUT PT_INFO **ppInfo);


/**
 * Return an additional information about the TFM/ESS.
 *
 * @param hConnection Handle to the connection to TFM
 * @param pExtInfo  Address of the pointer, which will be set to point to the structure
 *   with extended TFM/ESS information. The structure has to be freed by a call to PTFree.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTExtendedInfo(IN PT_CONNECTION hConnection, OUT PT_EXTENDED_INFO **ppExtInfo);


/**
 * Set the session parameters of the TFM. The parameters influence especially the
 * behavior of the biometric functions - e.g. should we use the advanced or the standard
 * templates etc.
 *
 * The change of parameters is valid only for the current session. Each new session
 * starts with the default settings.
 *
 * PTSetSessionCfgEx is an extension of the now obsolete function PTSetSessionCfg.
 *
 * @param hConnection Handle to the connection to TFM
 * @param wCfgVersion Version of the configuration data. Use the constant PT_CURRENT_SESSION_CFG
 * @param wCfgLength Length of the configuration data
 * @param pSessionCfg Session configuration to be set
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSetSessionCfgEx(
    IN PT_CONNECTION hConnection,
    IN PT_WORD wCfgVersion,
    IN PT_WORD wCfgLength,
    IN PT_SESSION_CFG *pSessionCfg
);


/**
 * Get the current session parameters of the TFM. The parameters influence especially
 * the behavior of the biometric functions - e.g. should we use the advanced or
 * the standard templates etc.
 *
 * PTGetSessionCfgEx is an extension of the now obsolete function PTGetSessionCfg.
 *
 * @param hConnection Handle to the connection to TFM
 * @param wCfgVersion Requested version of the configuration data
 * @param pwCfgLength Pointer to the length of the received configuration data
 * @param ppSessionCfg Returned session configuration
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetSessionCfgEx(
    IN PT_CONNECTION hConnection,
    IN PT_WORD wCfgVersion,
    OUT PT_WORD *pwCfgLength,
    OUT PT_SESSION_CFG **ppSessionCfg
);


/**
 * Returns the size in bytes of the remaining EEPROM memory on the TFM available
 * for application's usage.
 *
 * @param hConnection Handle to the connection to TFM
 * @param dwType Requested type of memory (see values PT_MEMTYPE_xxxx)
 * @param pdwAvailableMemory Returned size of remaining EEPROM memory
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetAvailableMemory(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwType,
    OUT PT_DWORD *pdwAvailableMemory
);


/**
 * This function allows the application to store a block of arbitrary binary data
 * in TFM's non-volatile memory. There is only one block, shared by all applications.
 *
 * @param hConnection Handle to the connection to TFM
 * @param dwArea Area to write. One of the PT_AREA_xxx values.
 * @param pAppData The data to be stored in NVM. If the data length is zero, the
 *  application data will be deleted.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSetAppData(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwArea,
    IN PT_DATA *pAppData
);


/**
 * Read the application data stored in TFM's non-volatile memory.
 *
 * @param hConnection Handle to the connection to TFM
 * @param dwArea Area to read. One of the PT_AREA_xxx values.
 * @param ppAppData Address of the pointer, which will be set to point to the
 *  application data. If no data are stored in NVM, the result will be a data block
 *  with zero length. The data has to be freed by a call to PTFree.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetAppData(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwArea,
    OUT PT_DATA **ppAppData
);


/**
 * This function allows the application to control the state and behavior of
 * the two user interface LEDs, which can be optionally connected to the TFM.
 *
 * @param hConnection Handle to the connection to TFM
 * @param dwMode Mode of the LEDs. Different modes define different behavior
 *  of the LEDs during specific operations, especially the biometrics. See
 *  PT_LED_MODE_xxxx.
 * @param dwLED1 Parameter defining the detailed behavior of the first LED.
 *  This parameter is mode-specific.
 * @param dwLED2 Parameter defining the detailed behavior of the second LED.
 *  This parameter is mode-specific.
 * @return Status code.
 */
PTAPI_DLL PT_STATUS PTAPI PTSetLED(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwMode,
    IN PT_DWORD dwLED1,
    IN PT_DWORD dwLED2
);

/**
 * This function allows the application to query the state and behavior of
 * the two user interface LEDs, which can be optionally connected to the TFM.
 *
 * @param hConnection Handle to the connection to TFM
 * @param pdwMode Mode of the LEDs. See PTSetLED for details.
 * @param pdwLED1 Parameter defining the detailed behavior of the first LED.
 *  This parameter is mode-specific. See PTSetLED for details.
 * @param pdwLED2 Parameter defining the detailed behavior of the second LED.
 *  This parameter is mode-specific. See PTSetLED for details.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetLED(
    IN PT_CONNECTION hConnection,
    OUT PT_DWORD *pdwMode,
    OUT PT_DWORD *pdwLED1,
    OUT PT_DWORD *pdwLED2
);


/**
 * Switch FM to deep sleep or standby mode. In this mode FM's CPU is stopped
 * to minimize power consumption. FM can be woken up from the sleep mode either
 * by the host or by another event (e.g. when a finger is detected on FM's
 * sensor).
 *
 * When FM wakes up, the PTSleep function completes and returns the cause of
 * wake up to the caller.
 *
 * @param hConnection Handle to the connection to FM.
 * @param dwSleepMode Sleep mode to be used. Possible values are
 *  PT_SLEEP_MODE_DEEPSLEEP (fingerprint sensor is powered down (finger detect
 *  is not active),	PT_SLEEP_MODE_STANDBY (finger detect is active).
 * @param pfnCallback Callback function, called periodically all the time FM is
 *  sleeping. Optional, can be NULL.
 * @param pIdleCallbackCtx A generic pointer to context data. This pointer will
 *  be supplied to the callback function every time it is called.
 * @param pdwWakeupCause The cause of wakeup. Currently the following causes are
 *  possible: PT_WAKEUP_CAUSE_HOST (signal from the Host),
 *  PT_WAKEUP_CAUSE_FINGER (a finger was detected).
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSleep (
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwSleepMode,
    IN PT_IDLE_CALLBACK pfnCallback,
    IN void *pIdleCallbackCtx,
    OUT PT_DWORD *pdwWakeupCause
);


/**
 * Authentify the caller (host) to the FM, allow access to FM functions.
 * This function is used only when FM is configured to require authentication.
 * In that case PTAuthentify should be called right after PTOpen. Without
 * PTAuthentify it is possible to use only specifically approved functions,
 * namely PTInfo, PTDiagnostics, PTFirmwareGetCfg, PTFirmwareSetCfg and
 * PTFirmwareUpdate.
 *
 * Every TFM can be configured to belong to one authentication group, which is
 * identified by its AuthentifyId. There is typically one group per costumer.
 * Each authentication group is assigned one secret key, which must be provided
 * by a caller to PTAuthentify. AuthentifyId = 0 is reserved to "no authentication"
 * group; TFMs belonging to this group do not require PTAuthentify. It is
 * possible to get AuthentifyId by calling PTInfo.
 *
 * Note: PTAuthentify is not implemented in TFM 1.1.
 *
 * @param hConnection Handle to the connection to FM
 * @param dwAuthentifyId ID of the authentication group
 * @param pKey The authentication key
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTAuthentify (
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwAuthentifyId,
    IN PT_DATA *pKey
);


/**
 * Authentify the caller (host) to the specific FM account allowing access to
 * functions enabled for that account.
 *
 * Note: PTAuthentifyEx is implemented only in ESS 2.2.
 *
 * @param hConnection Handle to the connection to FM
 * @param dwAccountId ID of the account to which the caller wants to be authentified,
 * @param pKey The authentication key
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTAuthentifyEx (
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwAccountId,
    IN PT_DATA *pKey
);


/**
 * Establish a secure channel for the given connection. Secure channel can be
 * established only after successful authentification via PTAuthentify/PTAuthentifyEx
 * when session key is generated from exchanged challenges.
 *
 * @param hConnection Handle to the connection to FM
 * @param dwMechanism Crypto mechanism used for channel encryption.
 * @param dwKeyLength Length of key (in bits) used for channel encryption. Note
 *   that only some key lengths are allowed for certain crypto mechanisms.
 * @param dwFlags Additional flags for channel encryption (like enabling
 *   encryption of GUI callbacks).
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSecureChannel(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwMechanism,
    IN PT_DWORD dwKeyLength,
    IN PT_DWORD dwFlags
);


/**
 * Establish a secure channel for the given connection. Secure channel can be
 * established only after successful authentification via PTAuthentify/PTAuthentifyEx
 * when session key is generated from exchanged challenges. This function uses specified
 * version of secure channel protocol.
 *
 * @param hConnection Handle to the connection to FM
 * @param dwMechanism Crypto mechanism used for channel encryption.
 * @param dwKeyLength Length of key (in bits) used for channel encryption. Note
 *   that only some key lengths are allowed for certain crypto mechanisms.
 * @param dwFlags Additional flags for channel encryption (like enabling
 *   encryption of GUI callbacks).
 * @param dwVersion Version of secure channel protocol.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTSecureChannelEx(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD dwMechanism,
    IN PT_DWORD dwKeyLength,
    IN PT_DWORD dwFlags,
    IN PT_DWORD dwVersion
);


/**
 * Get access rights mask of given account
 *
 * @param hConnection   Handle to the connection to FM
 * @param dwAccountId   ID of account which access rights mask has to be returned
 * @param ppAccessRights Address of the pointer, which will be set to point to the
 *                       access rights mask of given user's account. The data has
 *                       to be freed by a call to PTFree.
 * @return Status code
 */
PTAPI_DLL PT_STATUS PTAPI PTGetAccessRights(
    IN PT_CONNECTION hConnection,
    IN PT_DWORD      dwAccountId,
    OUT PT_DATA      **ppAccessRights
);


/*@}*/
/*---------------------------------------------------------------------------*/

/**
 * @name Callback related definitions
 */

/*@{*/


/**
 * Standard PerfectTrust GUI callback. This callback is default, until
 * other callback is specified by PTSetGUICallbacks
 */
PTAPI_DLL PT_STATUS PTAPI PT_STD_GUI_STATE_CALLBACK(
    IN void *pGuiStateCallbackCtx,
    IN PT_DWORD dwGuiState,
    OUT PT_BYTE *pbyResponse,
    IN PT_DWORD dwMessage,
    IN PT_BYTE byProgress,
    IN void *pSampleBuffer,
    IN PT_DATA *pData
);

/*@}*/

/*---------------------------------------------------------------------------*/


#endif /* tfmapi_h */




