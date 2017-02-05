/**
 * @file tfmtypes.h
 *
 * PTAPI types and definitions
 *
 * Copyright (C) 2001-2006 UPEK Inc.
 */

#ifndef tfmtypes_h
#define tfmtypes_h

#if defined(_MSC_VER)
#ifdef _DOS
#include <winapr.h>
#else
#include <windows.h>
#endif
#endif

/*------------ miscellaneous -----------------------------------------------*/

/**
 * Linkage specification macro
 */
#if !defined(PTAPI_DLL)
	#if defined(BUILD_PTAPI_DLL)
		#if defined(_MSC_VER) 
            #if defined(PTAPI_STATIC)
                #if defined __cplusplus 
                    #define PTAPI_DLL extern "C" 
                #else
                    #define PTAPI_DLL
                #endif
            #else
                #if defined __cplusplus 
                    #define PTAPI_DLL extern "C"
                #else
                    #define PTAPI_DLL extern
                #endif
            #endif
		#else
			#define PTAPI_DLL
		#endif
	#else
		#if defined(_MSC_VER)
            #if defined(PTAPI_STATIC)
                #if defined __cplusplus 
                    #define PTAPI_DLL extern "C"
                #else
                    #define PTAPI_DLL
                #endif
            #else    
    			#if defined __cplusplus 
	    			#define PTAPI_DLL extern "C" __declspec(dllimport)
		    	#else
			    	#define PTAPI_DLL __declspec(dllimport)
			    #endif
            #endif
		#else
			#define PTAPI_DLL
		#endif
	#endif
#endif


/**
 * Macro for standard call convention
 */
#ifndef PTAPI
#if defined(_MSC_VER)
#define PTAPI __stdcall
#else
#define PTAPI
#endif
#endif



/*
nothing doing macros used for better documenting parameter specification
*/

/** 
 * This is a definition which has sole purpose of 
 * helping readability.  It indicates that formal
 * parameter is an input parameter.
 */
#ifndef IN
#define IN
#endif

/** 
 * This is a definition which has sole purpose of 
 * helping readability.  It indicates that formal
 * parameter is an output parameter.  
 */
#ifndef OUT
#define OUT
#endif

/** 
 * This is a definition which has sole purpose of 
 * helping readability.  It indicates that formal
 * parameter is both input and output parameter.  
 */
#ifndef INOUT 
#define INOUT
#endif

/** 
 * This is a definition which has sole purpose of 
 * helping readability.  It indicates that formal
 * parameter is an optional parameter.  
 */
#ifndef OPTIONAL
#define OPTIONAL
#endif


/*------------ single types -------------------------------------------------*/

/** 
 * Signed byte
 */
typedef	char			PT_CHAR;

/** 
 * Unsigned byte 
 */
typedef	unsigned char 	PT_BYTE;

/** 
 * Signed 2 bytes
 */
typedef	short			PT_SHORT;

/** 
 * Unsigned 2 bytes
 */
typedef	unsigned short	PT_WORD;

/** 
 * Signed 4 bytes 
 */
typedef	long			PT_LONG;

/** 
 * Unsigned 4 bytes
 */
typedef	unsigned long	PT_DWORD;

/** 
 * Boolean value (zero, non-zero)
 */
typedef	unsigned long	PT_BOOL;

/**
 * Return status of functions
 */
typedef PT_LONG			PT_STATUS;

/**
 * Handle to a connection to the TFM. This is the connection between proxy and
 * the physical TFM.
 */
typedef	PT_DWORD		PT_TFM;

/**
 * Handle to a connection to a proxy
 */
typedef	PT_DWORD		PT_CONNECTION;

/**
 * Prototype of memory allocating function
 */
typedef void* (PTAPI *PT_MALLOC) (PT_DWORD Size);

/**
 * Prototype of memory freeing function
 */
typedef void (PTAPI *PT_FREE) (void *Memblock);


/*----------- structures ---------------------------------------------------*/

/**
 * The global information about this PerfectTrust implementation, especially
 * the version info.
 */
typedef struct pt_global_info {
    /**
     * Version of TFM API. Highest byte = major version, second highest 
     * byte = minor version, low word = subversions.
     */
    PT_DWORD    ApiVersion; 

    /**
     * Bitmask, defining which blocks of functions are supported (see PT_GIFUNC_xxxx).
     */
    PT_DWORD    Functionality;

    /**
     * Additional flags (e.g. encryption strength), see PT_GIFLAGS_xxxx.
     */
    PT_DWORD    Flags;
} PT_GLOBAL_INFO;

#define PT_GIFUNC_STANDARD      0x00000001  /**< Standard embedded biometrics */
#define PT_GIFUNC_SENSORONLY    0x00000002  /**< Sensor only solution */
#define PT_GIFUNC_PARTNER       0x80000000  /**< Functions available only to partners */
#define PT_GIFUNC_STONLY        0x40000000  /**< Functions available only to ST (manufacturer) */

#define PT_GIFLAGS_STRONGCRYPTO         0x00000001  /**< This PT API library supports strong crypto */
#define PT_GIFLAGS_MATCH_ON_HOST        0x00000002  /**< This PT API library supports 'Match on Host' functionality */
#define PT_GIFLAGS_CONST_AUTH_CHALLENGE 0x80000000  /**< This PT API library uses constant challenge for authentification (for testing purposes) */


#define DSNSUBSTR_MAXLEN    260
#define DISPLAYINFO_MAXLEN  128
#define OTHERINFO_MAXLEN    96

/**
 * Device info list item
 */
typedef struct pt_device_list_item {
    PT_CHAR DisplayInfo[DISPLAYINFO_MAXLEN];///< String with displayable device info
    PT_CHAR DsnSubString[DSNSUBSTR_MAXLEN]; ///< String usable as part of DSN for PTOpen() to connect to this device
    PT_CHAR OtherInfo[OTHERINFO_MAXLEN];    ///< String with other info
    PT_DWORD DeviceType;                    ///< Device type
    PT_BYTE reserved[28];                   ///< Reserved for future use
} PT_DEVICE_LIST_ITEM;

/**
 * List with devices info
 */
typedef struct pt_device_list {
    PT_DWORD            NumDevices; ///< Number of devices in the list
    PT_DEVICE_LIST_ITEM List[1];    ///< Array of the devices
} PT_DEVICE_LIST;


/**
 * This structure is used to associate any arbitrary long data block with
 * the length information.
 */
typedef struct pt_data {
	PT_DWORD Length; /**< Length of the Data field in bytes */
	PT_BYTE Data[1]; /**< The data itself, variable length */
} PT_DATA;


/**
 * This structure is used to hand over to PerfectTrust the set of memory
 * allocation/freeing routines, which will be then used for all dynamic memory management.
 */
typedef struct pt_memory_funcs {
	PT_MALLOC pfnMalloc; 	/**< Memory allocating function */
	PT_FREE pfnFree;	/**< Memory freeing function */

} PT_MEMORY_FUNCS;  


/**
 * The header of the BIR (Biometric Identification Record). This type is exactly
 * equivalent to BioAPI's BioAPI_BIR_HEADER. All the integer values in the header
 * are little-endians to ensure portability between different computers. 
 */
typedef struct pt_bir_header {
	/**
	 * Length of Header + Opaque Data
	 */
	PT_DWORD Length; 
	
	PT_BYTE HeaderVersion;
	PT_BYTE Type;
	PT_WORD FormatOwner;
	PT_WORD FormatID;
	PT_CHAR Quality;
	PT_BYTE Purpose;
	PT_DWORD FactorsMask;
} PT_BIR_HEADER;


/**
 * A container for biometric data. BIR (Biometric Identification Record). It can be
 * enrolled template, audit data etc. BIR consists of a header, followed by the opaque
 * data and optionally by a signature. This type is binary compatible with BioAPI's 
 * BioAPI_BIR. The only difference is, that in BioAPI_BIR the data are divided into
 * four separate memory blocks, while PT_BIR keeps all the data together.
 */
typedef struct pt_bir {
	PT_BIR_HEADER Header;
	PT_BYTE Data[1];	
} PT_BIR;


/**
 * A structure used to input a BIR to the API. Such input can be either the actual
 * BIR data, or one of the predefined handles to the template cache.
 */
typedef struct pt_input_bir {
	PT_BYTE byForm; /**< Form of the input BIR */

	union {
		PT_BIR *pBIR; /**< Used when byForm = PT_FULLBIR_INPUT */
		PT_LONG lSlotNr; /**< Used when byForm = PT_SLOT_INPUT */
		PT_BYTE abyReserved[20]; /** For future use */
	} InputBIR;
} PT_INPUT_BIR;

#define	PT_FULLBIR_INPUT	(3)
#define	PT_SLOT_INPUT		(128)


/**
 * BIR and biometric operations purposes.
 */
//@{
#define PT_PURPOSE_VERIFY                           (1)
#define PT_PURPOSE_IDENTIFY                         (2)
#define PT_PURPOSE_ENROLL                           (3)
#define PT_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY     (4)
#define PT_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY   (5)
#define PT_PURPOSE_AUDIT                            (6)
//@}


/**
 * Types of grabbed fingerprint images
 */
//@{
#define PT_GRAB_TYPE_UPPER_HALF                         (0)
#define PT_GRAB_TYPE_BOTTOM_HALF                        (1)
#define PT_GRAB_TYPE_THREE_QUARTERS_SUBSAMPLE           (2)
#define PT_GRAB_TYPE_ONE_HALF_SUBSAMPLE                 (3)
#define PT_GRAB_TYPE_THREE_QUARTERS_SUBSAMPLE_BINARIZED (4)

#define PT_GRAB_TYPE_381_381_8                          PT_GRAB_TYPE_THREE_QUARTERS_SUBSAMPLE // = 2
#define PT_GRAB_TYPE_254_254_8                          PT_GRAB_TYPE_ONE_HALF_SUBSAMPLE // = 3
#define PT_GRAB_TYPE_381_381_8_BINARIZED                PT_GRAB_TYPE_THREE_QUARTERS_SUBSAMPLE_BINARIZED // = 4
#define PT_GRAB_TYPE_508_254_8                          (5)
#define PT_GRAB_TYPE_508_508_4                          (6)
#define PT_GRAB_TYPE_381_381_4                          (7)
#define PT_GRAB_TYPE_508_254_4                          (8)
#define PT_GRAB_TYPE_254_254_4                          (9)
#define PT_GRAB_TYPE_508_508_8_WIDTH208                 (10)
#define PT_GRAB_TYPE_508_508_8_COMPRESS1                (11)
#define PT_GRAB_TYPE_508_508_4_SCAN4                    (12)
#define PT_GRAB_TYPE_381_381_8_FAST                     (13)
#define PT_GRAB_TYPE_508_254_4_SCAN4                    (14)
#define PT_GRAB_TYPE_254_254_4_SCAN4                    (15)
#define PT_GRAB_TYPE_381_381_4_FAST                     (16)
#define PT_GRAB_TYPE_381_381_8_BINARIZED_FAST           (17)
#define PT_GRAB_TYPE_508_508_8_COMPRESS2                (18)
#define PT_GRAB_TYPE_381_381_8_SCAN381                  (19)
#define PT_GRAB_TYPE_381_381_4_SCAN381                  (20)
#define PT_GRAB_TYPE_381_381_8_BINARIZED_SCAN381        (21)
#define PT_GRAB_TYPE_381_381_8_LP                       (22)    /// Low power
#define PT_GRAB_TYPE_381_381_4_LP                       (23)    /// Low power
#define PT_GRAB_TYPE_381_381_8_BINARIZED_LP             (24)    /// Low power
#define PT_GRAB_TYPE_381_381_8_VLP                      (25)    /// Very low power
#define PT_GRAB_TYPE_381_381_4_VLP                      (26)    /// Very low power
#define PT_GRAB_TYPE_381_381_8_BINARIZED_VLP            (27)    /// Very low power
#define PT_GRAB_TYPE_381_381_8_SCAN381_381_4            (28)
#define PT_GRAB_TYPE_381_381_4_SCAN381_381_4            (29)
#define PT_GRAB_TYPE_381_381_8_BINARIZED_SCAN381_381_4  (30)
#define PT_GRAB_TYPE_381_381_8_SCAN381_254_4            (31)
#define PT_GRAB_TYPE_381_381_4_SCAN381_254_4            (32)
#define PT_GRAB_TYPE_381_381_8_BINARIZED_SCAN381_254_4  (33)
#define PT_GRAB_TYPE_508_508_8_SCAN508_508_8            (34)
#define PT_GRAB_TYPE_508_508_4_SCAN508_508_8            (35)
#define PT_GRAB_TYPE_508_508_8_BINARIZED_SCAN508_508_8  (36)
//@}

/**
 * Types of compression of grabbed fingerprint images
 */
//@{
#define PT_GRAB_COMPRESSION_TYPE_NONE           (0) ///< No compression
//@}


/**
 * Flags for PTDetectFingerEx
 */
//@{
#define PT_DETECT_GUI           0x00000001  ///< Display GUI
#define PT_DETECT_NO_FINGER     0x00000002  ///< Wait for finger removing
#define PT_DETECT_ACCEPTABLE    0x00000004  ///< Wait for acceptable quality of finger
//@}


/**
 * A structure used by PTInfo to return status-independent information about FM.
 */
typedef struct pt_info {
    /**
     * Version of the TFM's firmware. Highest byte = major version,
     * second highest byte = minor version, low word = subversions/revisions.
     */
    PT_DWORD    FwVersion;

    /**
     * Minimal version required for future firmware update
     */
    PT_DWORD    FwMinNextVersion;

    /**
     * Variant of firmware 
     */
    PT_DWORD    FwVariant;	

    /**
     * Blocks of functionality included in firmware. See PT_FWFUNC_xxxx.
     */
    PT_DWORD    FwFunctionality; 

    /**
     * FW's configuration flags, set up during manufacturing. See PT_FWCFG_xxxx.
     */
    PT_DWORD    FwConfig;

    /** 
     * TFM ID.  If used, allows to assign unique ID to every TFM/ESS piece. Otherwise 0.
     */
    PT_DWORD    Id;

    /**
     * ID of the Authentify group. Every TFM with the same Authentify code
     * belongs to the same Authentify group. If AuthentifyId == 0,
     * PTAuthentify is not necessary. See PTAuthentify().
     */
    PT_DWORD    AuthentifyId;

    /**
     * Type of the reader in which the TFM is used. 0 = unspecified usage.
     */
    PT_DWORD    Usage;

    /**
     * Type and version of sensor.
     */
    PT_DWORD    SensorType;

    /**
     * Sensor image width
     */
    PT_WORD     ImageWidth;	

    /**
     * Sensor image height (for strip sensor max. height)
     */
    PT_WORD     ImageHeight;	

    /**
     * Max. guaranteed length of the output data for PTGrabWindow
     */
    PT_DWORD    MaxGrabWindow;

    /**
     * Companion vendor code
     */
    PT_DWORD    CompanionVendorCode;

} PT_INFO;


/**
 * Sensor type flags
 */
 //@{
#define PT_SENSORBIT_STRIP_SENSOR   0x80000000  ///< Strip sensor
#define PT_SENSORBIT_TURBO_MODE     0x40000000  ///< Turbo mode is activated
#define PT_SENSORBIT_CALIBRATED     0x20000000  ///< Calibration for full power formats was done
#define PT_SENSORBIT_CALIBRATED_LP  0x10000000  ///< Calibration for low power formats was done
#define PT_SENSORBIT_CALIBRATED_MP  0x08000000  ///< Calibration for medium power formats was done
//@}

/**
 * TFM functionality flags.
 */
//@{
#define	PT_FWFUNC_STANDARD      0x00000001  ///< Std. embedded biometrics
#define	PT_FWFUNC_EXTEEPROM     0x00000002  ///< Supports external EEPROM as a fingerprint template store
#define	PT_FWFUNC_ANTISPOOF     0x00000004  ///< Antispoofing support
#define PT_FWFUNC_STRIP         0x00000008  ///< Strip sensor support (if missing, area sensor support is included)
#define PT_FWFUNC_SC            0x00000010  ///< Smart card support
#define PT_FWFUNC_FINGER_DETECT 0x00000020  ///< Hardware finger detect support	 
#define PT_FWFUNC_TURBOMODE     0x00000040  ///< Turbo mode is supported
#define PT_FWFUNC_SECCHAN_V2    0x00000080  ///< Secure channel protocol version 2 is supported
#define	PT_FWFUNC_SIO           0x00010000  ///< Serial line support
#define	PT_FWFUNC_USB           0x00020000  ///< USB support
#define PT_FWFUNC_SONLY         0x80000000  ///< Sensor only
//@}

/**
 * Firmware configuration flags.
 */
//@{
#define	PT_FWCFG_EXTEEPROM  0x00000001  ///< Use external EEPROM as a fingerprint template store

#define	PT_FWCFG_LED        0x00000002  ///< LED interface activated

#define PT_FWCFG_SC         0x00000004  ///< Smart card module activated

#define PT_FWCFG_ANTISPOOF  0x00000008  ///< Antispoofing activated

#define PT_FWCFG_AWAKE      0x00000010  ///< AWAKE signal (DSR) activated

#define	PT_FWCFG_NOSLEEP    0x00004000  ///< If serial line is used, do not enter sleep when session is terminated
#define	PT_FWCFG_NORTS      0x00008000  ///< If serial line is used, do not use RTS handshaking

#define	PT_FWCFG_SIO        0x00010000	///< Use serial line as comm. channel
/**
 * Use USB as comm. channel. If both PT_FWCFG_SIO and PT_FWCFG_USB is defined, 
 * perform comm. channel detect during startup.
 */
#define	PT_FWCFG_USB        0x00020000
#define	PT_FWCFG_CFGLOCKED  0x80000000  ///< Firmware configuration cannot be changed anymore
#define	PT_FWCFG_FWLOCKED   0x40000000  ///< Firmware cannot be updated anymore
//@}


/// Size of GUID
#define PT_GUID_SIZE        16

/// Maximal possible length of SystemName string
#define PT_SYSTEM_NAME_MAX_LEN      64

/**
 * A structure used by PTExtendedInfo to return additional information about FM.
 */
typedef struct pt_extended_info {
    PT_DWORD    Version;            ///< Version of this structure (currently 1)
    PT_BYTE     GUID[PT_GUID_SIZE]; ///< TFM/ESS GUID
    PT_DWORD    SystemId;           ///< System identification bits
    PT_CHAR     SystemName[PT_SYSTEM_NAME_MAX_LEN]; ///< System identification name
} PT_EXTENDED_INFO;


/**
 * Accounts
 */
//@{
#define PT_ACCOUNT_ANONYMOUS    0       ///< Anonymous account
#define PT_ACCOUNT_1            1       ///< Account 1
#define PT_ACCOUNT_2            2       ///< Account 2
#define PT_ACCOUNT_3            3       ///< Account 3
#define PT_ACCOUNT_WRP          (-1)    ///< Wrapped profile account
//@}

/**
 * Access rights flags
 */
//@{
#define PT_ACC_ENABLE_SCANNER                               (0)
#define PT_ACC_ENABLE_ENROLL                                (1)
#define PT_ACC_ENABLE_VERIFY_CAPTURED                       (2)
#define PT_ACC_ENABLE_VERIFY_MATCH                          (3)
#define PT_ACC_ENABLE_USE_NVM_TEMPLATE                      (4)
#define PT_ACC_ENABLE_USE_EXTERN_TEMPLATE                   (5)
#define PT_ACC_ENABLE_UPDATE_NVM_TEMPLATE                   (6)
#define PT_ACC_ENABLE_GET_TEMPLATE_WITH_PAYLOAD             (7)
#define PT_ACC_ENABLE_GET_TEMPLATE_WITHOUT_PAYLOAD          (8)
#define PT_ACC_ENABLE_NAVIGATION                            (9)
#define PT_ACC_ENABLE_SET_APP_DATA_APP                      (10)
#define PT_ACC_ENABLE_SET_APP_DATA_OEM                      (11)
#define PT_ACC_ENABLE_SET_APP_DATA_PARTNER                  (12)
#define PT_ACC_ENABLE_GET_APP_DATA_APP                      (13)
#define PT_ACC_ENABLE_GET_APP_DATA_OEM                      (14)
#define PT_ACC_ENABLE_GET_APP_DATA_PARTNER                  (15)
#define PT_ACC_ENABLE_OTHER_FUNCS                           (16)
#define PT_ACC_ENABLE_MANUFACTURING_FUNCS                   (17)
#define PT_ACC_ENABLE_SET_AUTHKEY_1                         (18)
#define PT_ACC_ENABLE_SET_AUTHKEY_2                         (19)
#define PT_ACC_ENABLE_SET_AUTHKEY_3                         (20)
#define PT_ACC_ENABLE_SET_ACCESS_RIGHTS_ANONYMOUS           (21)
#define PT_ACC_ENABLE_SET_ACCESS_RIGHTS_1                   (22)
#define PT_ACC_ENABLE_SET_ACCESS_RIGHTS_2                   (23)
#define PT_ACC_ENABLE_SET_ACCESS_RIGHTS_3                   (24)
#define PT_ACC_ENABLE_GET_VERIFY_MATCH_PAYLOAD              (25)
#define PT_ACC_ENABLE_SECURE_CHANNEL                        (26)
#define PT_ACC_ENABLE_ANTISPOOFING                          (27)
#define PT_ACC_ENABLE_CHANGE_ANTISPOOFING_LEVEL             (28)
#define PT_ACC_ENABLE_GET_ANTISPOOFING_INFO                 (29)
#define PT_ACC_ENABLE_OTP_SET_SECRET_KEY                    (30)
#define PT_ACC_ENABLE_OTP_SET_USER_KEY                      (31)
#define PT_ACC_ENABLE_OTP_SET_SEQUENCE_NUMBER               (32)
#define PT_ACC_ENABLE_OTP_GENERATE                          (33)
#define PT_ACC_ENABLE_SET_FINGER_PAYLOAD                    (34)
#define PT_ACC_ENABLE_UPDATE_FINGER_PAYLOAD                 (35)
#define PT_ACC_ENABLE_ACCESS_FPDATAEX                       (36)
#define PT_ACC_ENABLE_CONTROL_LMD                           (37)
#define PT_ACC_ENABLE_USE_WRAPPED_TEMPLATE                  (38)
#define PT_ACC_ENABLE_UPDATE_WRAPPED_TEMPLATE               (39)
#define PT_ACC_ENABLE_CREATE_WRAPPED_PROFILE                (40)
//@}

/**
 * Macro for setting one of the access rights bit.
 * pAccessRights is a pointer to access rights byte array.
 * Bit is the number of access right to be set.
 */
#define SET_ACCESS_RIGHTS_BIT(pAccessRights, Bit)    (((PT_BYTE*)pAccessRights)[Bit>>3] |= (1 << (Bit&7)))

/**
 * Macro for clearing one of the access rights bit.
 * pAccessRights is a pointer to access rights byte array.
 * Bit is the number of access right to be cleared.
 */
#define CLEAR_ACCESS_RIGHTS_BIT(pAccessRights, Bit)  (((PT_BYTE*)pAccessRights)[Bit>>3] &= ~(1 << (Bit&7)))

/**
 * Macro for getting state of one of the access rights bit
 * pAccessRights is a pointer to access rights byte array.
 * Bit is the number of access right to be read.
 */
#define GET_ACCESS_RIGHTS_BIT(pAccessRights, Bit)    ((((PT_BYTE*)pAccessRights)[Bit>>3] >> (Bit&7)) & 1)


/**
 * Crypto mechanisms for secure channel
 */
//@{
#define PT_SECURECHANNEL_MECH_NONE      0x00000000  ///< Disables channel encryption
#define PT_SECURECHANNEL_MECH_DES_CBC   0x00000021  ///< DES in CBC mode, max possible key length is 56 bits
#define PT_SECURECHANNEL_MECH_AES_CBC   0x00000031  ///< AES in CBC mode, max possible key length is 256 bits
//@}

/**
 * Secure channel flags
 */
//@{
#define PT_SECURECHANNELBIT_DISABLE_GUI_ENCRYPTION  0x00000001  ///< Disable encryption of GUI callbacks
//@}


/**
 * Areas for storing application data
 */
//@{
#define PT_AREA_APP     (1)     ///< Application area
#define PT_AREA_OEM     (2)     ///< OEM area
#define PT_AREA_PARTNER (3)     ///< Partner area
#define PT_AREA_LATENT  (4)     ///< Latent area is used in PerfectPrint emulation to store the latent data
//@}

/**
 * Types of EEPROM memory for call of PTGetAvailableMemory
 */
 //@{
#define PT_MEMTYPE_ALL      0xffffffff  ///< Total of all available memory
#define PT_MEMTYPE_INTERNAL        0x0  ///< Internal EEPROM
#define PT_MEMTYPE_EXTERNAL        0x1  ///< External EEPROM
//@}


/**
 * Modes for LEDs control
 */
//@{
#define PT_LED_MODE_MANUAL          0   ///< Full control of the LEDs
#define PT_LED_MODE_BIO             1   ///< Bio feedback mode
//@}


/**
 * Reconstruction error policies
 */
//@{
#define PT_SCANQUALQUERY_GRAB           0x0001  //< Set scan quality query mode for PTGrab function
#define PT_SCANQUALQUERY_ENROLL         0x0002  //< Set scan quality query mode for PTEnroll function and PTCapture with purpose = enroll
#define PT_SCANQUALQUERY_VERIFY         0x0004  //< Set scan quality query mode for PTVerify and all other finger verification/matching biometric functions
#define PT_IMAGEQUALQUERY_GRAB          0x0008  //< Set image quality query mode for PTGrab function when parameter boWaitForAcceptableFinger is PT_FALSE
#define PT_IMAGEQUALQUERY_GRAB_WAIT     0x0010  //< Set image quality query mode for PTGrab function when parameter boWaitForAcceptableFinger is PT_TRUE
#define PT_IMAGEQUALQUERY_ENROLL        0x0020  //< Set image quality query mode for PTEnroll function and PTCapture with purpose = enroll
#define PT_IMAGEQUALQUERY_VERIFY        0x0040  //< Set image quality query mode for PTVerify and all other finger verification/matching biometric functions
//@}


/**
 * Reconstruction input types for biometrics
 */
//@{
#define PT_BIO_INPUT_TYPE_NORMAL    0       ///< Normal input
#define PT_BIO_INPUT_TYPE_FAST      1       ///< Fast input
#define PT_BIO_INPUT_TYPE_381       2       ///< Use 381/381 dpi 8 bpp as input format
#define PT_BIO_INPUT_TYPE_LP        3       ///< Low power input
#define PT_BIO_INPUT_TYPE_VLP       4       ///< Very low power input
#define PT_BIO_INPUT_TYPE_381_381_4     5   ///< Use 381/381 dpi 4 bpp as input format   
#define PT_BIO_INPUT_TYPE_381_254_4     6   ///< Use 381/254 dpi 4 bpp as input format   
//@}


/**
 * Security levels for template matching
 */
//@{
#define PT_MATCH_MIN_SECURITY       1   ///< Minimal security setting
#define PT_MATCH_LOWER_SECURITY     2   ///< Lower security setting
#define PT_MATCH_MEDIUM_SECURITY    3   ///< Medium and default security setting
#define PT_MATCH_HIGHER_SECURITY    4   ///< Higher security setting
#define PT_MATCH_MAX_SECURITY       5   ///< Maximal security setting
//@}

/** Security level type */
typedef PT_DWORD PT_SECURITY_LEVEL;


/**
 * Antispoofing security levels
 */
//@{
#define PT_ANTISPOOFING_MIN_SECURITY        1   ///< Minimal security setting
#define PT_ANTISPOOFING_LOWER_SECURITY      2   ///< Lower security setting
#define PT_ANTISPOOFING_MEDIUM_SECURITY     3   ///< Medium and default security setting
#define PT_ANTISPOOFING_HIGHER_SECURITY     4   ///< Higher security setting
#define PT_ANTISPOOFING_MAX_SECURITY        5   ///< Maximal security setting
//@}

/** Antispoofing level type */
typedef PT_DWORD PT_ANTISPOOFING_LEVEL;


/**
 * Types of called GUI callbacks
 */
//@{
#define CALLBACKS_NONE      0   ///< No callbacks at all
#define CALLBACKS_SIMPLE    1   ///< Only put/lift finger
#define CALLBACKS_ADVANCED  2   ///< Positioning feedback
#define CALLBACKS_FULL      3   ///< Begin/end + positioning feedback 
//@}

/**
 * Additional flags describing behavior of GUI callbacks
 */
//@{
#define CALLBACKSBIT_SWIPE_IN_PROGRESS  0x00010000  // Flag enabling PT_GUIMSG_SWIPE_IN_PROGRESS GUI message
#define CALLBACKSBIT_SAMPLE_IMAGE       0x00020000  // Flag enabling sending of sample image
//@}

/** GUI callbacks level type */
typedef PT_DWORD PT_CALLBACK_LEVEL;


/**
 * Consolidation types
 */
//@{
#define PT_CONSOLIDATION_NORMAL     0   ///< Normal consolidation policy
#define PT_CONSOLIDATION_SMART      1   ///< Smart consolidation policy
#define PT_CONSOLIDATION_STRICT     2   ///< Strict consolidation policy
//@}


/** 
 * Finger scan termination policies
 */
//@{
#define PT_SCAN_TERMINATION_BASIC       0   ///< When the scanned image is longer than allowed number of rows, return the beginning of the image from the scan start on.
#define PT_SCAN_TERMINATION_FINGERTIP   1   ///< When the scanned image is longer than allowed number of rows, return the end of the image up to the fingertip.
#define PT_SCAN_TERMINATION_CORE        2   ///< When the scanned image is longer than allowed number of rows, return the most valuable part of the image from biometrical viewpoint (typically the fingerprint's core).
#define PT_SCAN_TERMINATION_CORE_PLUS   3   ///< When the scanned image is longer than allowed number of rows, return the most valuable part of the image from biometrical viewpoint (typically the fingerprint's core), while skipping finger joint.
//@}


/**
 * Retuning options
 */
//@{
#define PT_RETUNING_DISABLED            0   ///< Retuning disabled
#define PT_RETUNING_ENABLED             1   ///< Retuning enabled
//@}


/**
 * Swipe direction options
 */
//@{
#define PT_SWIPEDIR_STANDARD            0   ///< Standard direction for given mounting
#define PT_SWIPEDIR_INVERTED            1   ///< Inverted direction
#define PT_SWIPEDIR_AUTODETECT          2   ///< Direction is detected at the begining of swipe
#define PT_SWIPEDIR_STANDARD_WARN       3   ///< Standard direction with warning for backward swipe
#define PT_SWIPEDIR_INVERTED_WARN       4   ///< Inverted direction with warning for backward swipe
//@}


/**
 * Navigation modes
 */
//@{
#define PT_NAVTYPE_508_8            0   ///< Navigation is using 508 DPI resolution, 8 bits/pixel (best quality)
#define PT_NAVTYPE_508_4            1   ///< Navigation is using 508 DPI resolution, 4 bits/pixel (best quality)
#define PT_NAVTYPE_254_8_LOPOWER    2   ///< Navigation is using 254 DPI resolution, 8 bits/pixel. Companion chip and sensor are both running in low-power slow-clock mode. Power saving mode with lower quality of navigation.
#define PT_NAVTYPE_254_4_LOPOWER    3   ///< Navigation is using 254 DPI resolution, 4 bits/pixel. Companion chip and sensor are both running in low-power slow-clock mode. Power saving mode with lower quality of navigation. 
#define PT_NAVTYPE_381_8            4   ///< Navigation is using 381 DPI resolution, 8 bits/pixel.
#define PT_NAVTYPE_254_8_VLOPOWER   2   ///< Navigation is using 254 DPI resolution, 8 bits/pixel. Companion chip and sensor are both running in low-power slow-clock mode. Power saving mode with lower quality of navigation.
#define PT_NAVTYPE_381_4            5   ///< Navigation is using 381 DPI resolution, 4 bits/pixel.
//@}


/**
 * Navigation orientation
 */
//@{
#define PT_NAVORIENT_STANDARD   0   ///< Standard orientation of navigation
#define PT_NAVORIENT_BYSWIPE    1   ///< Navigation orientation is controlled by direction of last swipe
//@}


/**
 * Device suspend during sleep commands options
 */
//@{
#define PT_SUSPEND_IN_SLEEP_DISABLED    0   ///< Device suspend disabled
#define PT_SUSPEND_IN_SLEEP_ENABLED     1   ///< Device suspend enabled
//@}


/**
 * PT_SESSION_CFG structure version 1
 */
typedef struct pt_session_cfg_v1 {
    PT_SECURITY_LEVEL     SecuritySetting;   ///< Security level for templates matching
    PT_DWORD    AntispoofingLevel; ///< Level of anti-spoofing
    PT_BOOL     MultipleEnroll; ///< Indicates whether or not enrollment should use multiple finger images
    PT_BOOL     LatentDetect;   ///< Indicates whether or not latent detection should be activated
    PT_BOOL     SubSample;      ///< Indicates whether or not extraction should sub-sample images
    PT_BOOL     SensorDisabling;///< Indicates whether or not put sensor into sleep mode after each biometric operation
    PT_CALLBACK_LEVEL CallbackLevel;    ///< Indicates what amount of GUI callbacks is received during biometric operations
    
    PT_BYTE     Reserved[20];   ///< Not used
} PT_SESSION_CFG_V1;

/**
 * PT_SESSION_CFG structure version 2
 */
typedef struct pt_session_cfg_v2 {
    PT_SECURITY_LEVEL     SecuritySetting;   ///< Security level for templates matching
    PT_DWORD    AntispoofingLevel; ///< Level of anti-spoofing
    PT_BOOL     MultipleEnroll; ///< Indicates whether or not enrollment should use multiple finger images
    PT_BOOL     LatentDetect;   ///< Indicates whether or not latent detection should be activated
    PT_BOOL     SubSample;      ///< Indicates whether or not extraction should sub-sample images
    PT_BOOL     SensorDisabling;///< Indicates whether or not put sensor into sleep mode after each biometric operation
    PT_CALLBACK_LEVEL CallbackLevel;    ///< Indicates what amount of GUI callbacks is received during biometric operations
    PT_BOOL     WakeUpByFinger; ///< If PT_TRUE, FM can be woken up from deep sleep by a finger on sensor
    PT_BYTE     SubWindowArea;  ///< Area of the subwindow in percents of the full area used for extractor
    
    /** STRIP SENSOR ONLY CONFIG DATA */
    //@{
    /** Wait for finger */
    //@{
    PT_BOOL     WffUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     WffFingerDownDelay; ///< Timing for finger touch
    PT_WORD     WffFingerUpDelay;   ///< Timing for finger lift
    //@}
    
    /** Reconstruction */
    //@{
    PT_BOOL     RecUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     RecFingerDownDelay; ///< Timing for finger touch
    PT_WORD     RecFingerUpDelay;   ///< Timing for finger lift
    //@}
    
    /** Striation removal */
    //@{
    PT_BOOL     RecRemoveTopdown;   ///< Remove striation from top   
    PT_BOOL     RecRemoveBottomup;  ///< Remove striation from bottom
    //@}
    
    /** Navigation */
    //@{
    PT_BOOL     NavUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     NavFingerDownDelay; ///< Timing for finger touch
    PT_WORD     NavFingerUpDelay;   ///< Timing for finger lift
    PT_WORD     NavClickTimeMin;  	///< Minimum elapsed time to detect a click
    PT_WORD     NavClickTimeMax;  	///< Maximum elapsed time to detect a click 
    PT_WORD     NavMovementDelay;   ///< Delay before movement detection
    PT_DWORD    NavClickAllowedMovement; ///< Maximum allowed movement for click
    //@}
    //@}
} PT_SESSION_CFG_V2;

/**
 * PT_SESSION_CFG structure version 3
 */
typedef struct pt_session_cfg_v3 {
    PT_SECURITY_LEVEL     SecuritySetting;   ///< Security level for templates matching (see PT_MATCH_xxxx values)
    PT_DWORD    AntispoofingLevel; ///< Level of anti-spoofing (see PT_ANTISPOOFING_xxxx values)
    PT_BOOL     MultipleEnroll; ///< Indicates whether or not enrollment should use multiple finger images
    PT_BOOL     LatentDetect;   ///< Indicates whether or not latent detection should be activated
    PT_BOOL     SubSample;      ///< Indicates whether or not extraction should sub-sample images
    PT_BOOL     SensorDisabling;///< Indicates whether or not put sensor into sleep mode after each biometric operation
    PT_CALLBACK_LEVEL CallbackLevel;    ///< Indicates what amount of GUI callbacks is received during biometric operations (see CALLBACKS_xxxx values)
    PT_BOOL     WakeUpByFinger; ///< If PT_TRUE, FM can be woken up from deep sleep by a finger on sensor
    PT_DWORD    WakeUpByFingerTimeout;  ///< Timeout for returning to standby after wake-up by finger (in milliseconds)
    PT_BYTE     SubWindowArea;  ///< Area of the subwindow in percents of the full area used for extractor
    PT_BYTE     ConsolidationType;  ///< Type of consolidation in multienrollment (see PT_CONSOLIDATION_xxxx values)

    /** STRIP SENSOR ONLY CONFIG DATA */
    //@{
    /** Wait for finger */
    //@{
    PT_BOOL     WffUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     WffFingerDownDelay; ///< Timing for finger touch
    PT_WORD     WffFingerUpDelay;   ///< Timing for finger lift
    //@}
    
    /** Reconstruction */
    //@{
    PT_BOOL     RecUseHwDetection;      ///< Use Hardware finger detection
    PT_WORD     RecFingerDownDelay;     ///< Timing for finger touch
    PT_WORD     RecFingerUpDelay;       ///< Timing for finger lift
    PT_WORD     RecTerminationPolicy;   ///< Defines the way, how end of finger scan is determined (see PT_SCAN_TERMINATION_xxxx values)
    PT_BYTE     RecRetuning;            ///< Enable retuning (see PT_RETUNING_xxxx values)
    PT_BYTE     RecDigitalGain;         ///< Digital gain
    //@}
   
    /** Striation removal */
    //@{
    PT_BOOL     RecRemoveTopdown;   ///< Remove striation from top   
    PT_BOOL     RecRemoveBottomup;  ///< Remove striation from bottom
    //@}
    
    /** Navigation */
    //@{
    PT_BOOL     NavUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     NavFingerDownDelay; ///< Timing for finger touch
    PT_WORD     NavFingerUpDelay;   ///< Timing for finger lift
    PT_WORD     NavClickTimeMin;  	///< Minimum elapsed time to detect a click
    PT_WORD     NavClickTimeMax;  	///< Maximum elapsed time to detect a click 
    PT_WORD     NavMovementDelay;   ///< Delay before movement detection
    PT_DWORD    NavClickAllowedMovement; ///< Maximum allowed movement for click
    PT_WORD     NavNavigationType;  ///< Navigation type (see PT_NAVTYPE_xxxx values)
    //@}
    
    /** Misc */
    //@{
    PT_WORD    BioEnrollInputType;     ///< Reconstruction type for enrollment (see PT_BIO_INPUT_TYPE_xxxx values)
    PT_WORD    BioVerifyInputType;     ///< Reconstruction type for verification (see PT_BIO_INPUT_TYPE_xxxx values)
    PT_WORD    EnableScanQualityQuery; ///< Bitmask of scan quality modes (see PT_SCANQUALQUERY_xxxx values)
    //@}
    //@}
} PT_SESSION_CFG_V3;

/**
 * PT_SESSION_CFG structure version 4
 */
typedef struct pt_session_cfg_v4 {
    PT_DWORD    SecuritySetting;            ///< Security level for templates matching (see PT_MATCH_xxxx values)
    PT_WORD     AntispoofingEnable;         ///< If PT_TRUE, antispoofing is enabled
    PT_WORD     AntispoofingSecurityLevel;  ///< Level of anti-spoofing security (see PT_ANTISPOOFING_xxxx values)
    PT_BOOL     MultipleEnroll;             ///< Indicates whether or not enrollment should use multiple finger images
    PT_BOOL     LatentDetect;               ///< Indicates whether or not latent detection should be activated
    PT_BOOL     SubSample;                  ///< Indicates whether or not extraction should sub-sample images
    PT_BOOL     SensorDisabling;            ///< Indicates whether or not put sensor into sleep mode after each biometric operation
    PT_DWORD    CallbackLevel;              ///< Indicates what amount of GUI callbacks is received during biometric operations (see CALLBACKS_xxxx values)
    PT_BOOL     WakeUpByFinger;             ///< If PT_TRUE, FM can be woken up from deep sleep by a finger on sensor
    PT_DWORD    WakeUpByFingerTimeout;      ///< Timeout for returning to standby after wake-up by finger (in milliseconds)
    PT_BYTE     SubWindowArea;              ///< Area of the subwindow in percents of the full area used for extractor
    PT_BYTE     ConsolidationType;          ///< Type of consolidation in multienrollment (see PT_CONSOLIDATION_xxxx values)
    PT_BYTE     CreateWrappedBIRs;          ///< Indicates whether or not wrapped BIRs should be created by biometric functions
    PT_BYTE     SignatureType;              ///< Type of signing method (see PT_SIGNATURE_TYPE_xxxx values)
    PT_BOOL     RestartBioTimeout;          ///< Restart biometric timeout for each fingerprint scan
    PT_BYTE     IdentificationThreshold;    ///< Threshold for biometric identification
    PT_BYTE     ExtractionMaxMinu;          ///< Max number of minutiae in biometric template from extraction
    PT_BYTE     EnrollMaxMinu;              ///< Max number of minutiae in biometric template after enroll (must be less or equal to ExtractionMaxMinu)
    PT_BYTE     TemplateType;               ///< Type of templates created by FM (see PT_TEMPLATE_TYPE_xxxx values)

    /** STRIP SENSOR ONLY CONFIG DATA */
    //@{
    /** Wait for finger */
    //@{
    PT_BOOL     WffUseHwDetection;  ///< Use Hardware finger detection
    PT_WORD     WffFingerDownDelay; ///< Timing for finger touch
    PT_WORD     WffFingerUpDelay;   ///< Timing for finger lift
    //@}
    
    /** Reconstruction */
    //@{
    PT_BOOL     RecUseHwDetection;      ///< Use Hardware finger detection
    PT_BYTE     RecSwipeDirection;      ///< Swipe direction (see PT_SWIPEDIR_xxxx values)
    PT_BYTE     Reserved1[3];           ///< Not used
    PT_LONG     RecSwipeTimeout;        ///< Timeout for swipe termination
    PT_LONG     RecNoMovementTimeout;   ///< If no movement is detected for that period [ms], the swipe is terminated regardless on the finger presence. This feature is disabled if set to 0. 
    PT_LONG     RecNoMovementResetTimeout; ///< If no movement is detected for that period [ms] and image is very short, the reconstruction is not restarted any more. This feature is disabled if set to 0.
    PT_WORD     RecTerminationPolicy;   ///< Defines the way, how end of finger scan is determined (see PT_SCAN_TERMINATION_xxxx values)
    PT_BYTE     Reserved2[2];            ///< Not used
    //@}
   
    /** Striation removal */
    //@{
    PT_BOOL     RecRemoveTopdown;   ///< Remove striation from top   
    PT_BOOL     RecRemoveBottomup;  ///< Remove striation from bottom
    //@}
    
    /** Navigation */
    //@{
    PT_BOOL     NavUseHwDetection;      ///< Use Hardware finger detection
    PT_WORD     NavFingerDownDelay;     ///< Timing for finger touch
    PT_WORD     NavFingerUpDelay;       ///< Timing for finger lift
    PT_WORD     NavClickTimeMin;  	    ///< Minimum elapsed time to detect a click
    PT_WORD     NavClickTimeMax;  	    ///< Maximum elapsed time to detect a click 
    PT_WORD     NavMovementDelay;       ///< Delay before movement detection
    PT_BYTE     Reserved3[2];           ///< Not used
    PT_DWORD    NavClickAllowedMovement; ///< Maximum allowed movement for click
    PT_WORD     NavNavigationType;      ///< Navigation type (see PT_NAVTYPE_xxxx values)
    PT_BYTE     NavOrientation;         ///< Orientation of navigation (see PT_NAVORIENT_xxxx values)
    PT_BYTE     Reserved4[1];           ///< Not used
    PT_BOOL     NavSubPixelPrecision;   ///< Use sub-pixel precision for navigation
    //@}
    
    /** Misc */
    //@{
    PT_WORD    BioEnrollInputType;      ///< Reconstruction type for enrollment (see PT_BIO_INPUT_TYPE_xxxx values)
    PT_WORD    BioVerifyInputType;      ///< Reconstruction type for verification (see PT_BIO_INPUT_TYPE_xxxx values)
    PT_WORD    BioFingerDetectInputType;///< Reconstruction type for finger detection commands (see PT_BIO_INPUT_TYPE_xxxx values)
    PT_WORD    EnableScanQualityQuery;  ///< Bitmask of scan quality modes (see PT_SCANQUALQUERY_xxxx values)
    PT_BOOL    UseHwFingerDetection;    ///< Use TCD based hardware finger detection for biometrics
    PT_BYTE    Retuning;                ///< Enable retuning (see PT_RETUNING_xxxx values)
    PT_BYTE    SuspendInSleep;            ///< Enable device suspend during PTSleep/PTSleepThenGrab/PTSleepThenCapture (see PT_SUSPEND_IN_SLEEP_xxxx values) (this parameter affects SOnly)
    
    PT_BYTE    Reserved5[18];            ///< Not used
    //@}
    //@}
} PT_SESSION_CFG_V4;

#if ESS_VER >= 0x0202
#define PT_CURRENT_SESSION_CFG  (4)         ///< For ESS 2.2 is default PT_SESSION_CFG structure version 4
typedef PT_SESSION_CFG_V4 PT_SESSION_CFG;   ///< For ESS 2.2 is default PT_SESSION_CFG structure version 4
#else
#define PT_CURRENT_SESSION_CFG  (3)         ///< For TFM 2.0 and ESS 2.1 is default PT_SESSION_CFG structure version 3
typedef PT_SESSION_CFG_V3 PT_SESSION_CFG;   ///< For TFM 2.0 and ESS 2.1 is default PT_SESSION_CFG structure version 3
#endif


/// Maximal possible length of application data associated with finger stored in TFM's non-volatile memory.
#define PT_MAX_FINGER_DATA_LENGTH   (96)

/**
 * Finger list item
 */
typedef struct pt_finger_list_item {
    PT_LONG     SlotNr;                                ///< Number of slot, where is the finger stored
    PT_DWORD    FingerDataLength;                      ///< Length of data associated with the finger
    PT_BYTE     FingerData[PT_MAX_FINGER_DATA_LENGTH]; ///< Data associated with the finger
} PT_FINGER_LIST_ITEM;

/**
 * PT_FINGER_LIST structure
 */
typedef struct pt_finger_list {
    PT_DWORD    NumFingers;         ///< Number of fingers in the list
    PT_FINGER_LIST_ITEM List[1];    ///< Array of the fingers
} PT_FINGER_LIST;


/// Slut number representing last matched slot template
#define PT_SLOT_LASTMATCHED     (-1)


/**
 * The navigation data passed to the PT_NAVIGATION_CALLBACK.
 */
typedef struct pt_navigation_data 
{
    PT_SHORT dx;            ///< Delta X since the last navigation data
    PT_SHORT dy;            ///< Delta Y since the last navigation data
    PT_WORD  signalBits;    ///< Information bitmask, see PT_NAVIGBITS_xxxx
} PT_NAVIGATION_DATA; 

/**
 * Signal bits of PT_NAVIGATION_DATA
 */
//@{
#define PT_NAVIGBITS_FINGER	    0x0001  ///< Finger is present
#define PT_NAVIGBITS_CLICK	    0x0002	///< At least one click (tap) since the last navigation data
#define PT_NAVIGBITS_CALIB_OVER	0x0004	///< Calibration phase has enough data and can be completed. This bit is used only for PTClickCalibrate.
//@}


/**
 * Sleep modes for PTSleep()
 */
//@{
#define PT_SLEEP_MODE_DEEPSLEEP     (0) ///< Deep sleep without HW finger detect
#define PT_SLEEP_MODE_STANDBY       (1) ///< Deep sleep with HW finger detect
//@}

/**
 * Wake up causes for PTSleep()
 */
//@{
#define PT_WAKEUP_CAUSE_HOST        (0) ///< Waken up by host via RTS
#define PT_WAKEUP_CAUSE_FINGER      (1) ///< Waken up by finger on sensor
//@}

/**
 * Response from IDLE callback
 */
//@{
#define PT_SLEEP_STOP               (0) ///< Wake-up
#define PT_SLEEP_CONTINUE           (1) ///< Continue to sleep
//@}


/**
 * Predefined biometric time-out values
 **/
//@{
#define PT_BIO_DEFAULT_TIMEOUT      (-1) ///< Default timeout
#define PT_BIO_INFINITE_TIMEOUT     (-2) ///< Infinite timeout
//@}


/**
 * Swipe information structure.
 */
typedef struct pt_swipe_info {
    PT_SHORT    RealHeight;     ///< Number of actually reconstructed lines.
    PT_SHORT    BackgroundColor;///< Image background color.
    PT_SHORT    ROIPos;         ///< Vertical position of the center of the region of interest (e.g. the core). Negative if no ROI was detected.
    PT_SHORT    ROILength;      ///< Vertical length of the region of interest, zero if no ROI was detected.
    PT_WORD     RecErrorStates; ///< Bit array with signaled reconstruction errors (see PT_RECERRBIT_xxxx).
    PT_WORD     QualityMessage; ///< GUI message resulting from image quality test (see PT_GUIMSG_xxxx), 0xffff when image quality wasn't assessed.
    PT_CHAR     RecScore;       ///< Reconstruction score.
    PT_CHAR     QualityScore;   ///< Image quality score, negative when image quality wasn't assessed.
    PT_CHAR     InvertedSwipe;  ///< Direction of swipe (0 = standard direction, 1 = inverted direction). 
    PT_BYTE     reserved[9];
} PT_SWIPE_INFO;


/**
 * Reconstruction errors
 */
//@{
#define PT_RECERRBIT_SWIPE_TOO_FAST     0x1     ///< Swipe too fast
#define PT_RECERRBIT_SWIPE_TOO_SKEWED   0x2     ///< Swipe too skewed
#define PT_RECERRBIT_BACKWARDS_MOVEMENT 0x4     ///< Backwards movement detected
#define PT_RECERRBIT_JOINT_DETECTED     0x8     ///< Finger joint detected
#define PT_RECERRBIT_TOO_SHORT          0x10    ///< Swipe too short
//@}


/**
 * Signature methods
 */
//@{
#define PT_SIGNATURE_TYPE_STANDARD      0   ///< Standard signature method
//@}


/**
 * Template types
 */
//@{
#define PT_TEMPLATE_TYPE_LEGACY         0   // Legacy template format
#define PT_TEMPLATE_TYPE_ALPHA          1   // Basic template type
#define PT_TEMPLATE_TYPE_BETA           2   // Extended template type
//@}


/**
 * Structure with additional parameters for on-host matching functions.
 */
//@{
typedef struct pt_match_on_host_params {
    PT_DWORD    Length;                     ///< Length of this structure, set to 'sizeof(PT_MATCH_ON_HOST_PARAMS)'
    PT_DWORD    Version;                    ///< Version of this structure (currently 1)
    PT_DWORD    SecuritySetting;            ///< Security level for templates matching (see PT_MATCH_xxxx values)
    PT_BYTE     IdentificationThreshold;    ///< Threshold for biometric identification
} PT_MATCH_ON_HOST_PARAMS;
//@}


/**
 * Prototype of callback function that an application supplies to allow the FM 
 * API to display GUI state information to the user, and to receive
 * responses back.
 *
 * @param pGuiStateCallbackCtx A generic pointer to context information that was
 *		provided by the original requester and is being returned to its originator.
 * @param dwGuiState A bitmask indicating the current GUI state plus an indication
 *		of what others parameters are available. It can be combined from values 
 *		PT_SAMPLE_AVAILABLE, PT_MESSAGE_PROVIDED and PT_PROGRESS_PROVIDED.
 *		In the current implementation only PT_MESSAGE_PROVIDED is used.
 * @param pbyResponse The response from the application back to the PerfectTrust Proxy
 *		API on return from the callback. Can be one of values PT_CANCEL or PT_CONTINUE.
 *		Other values are reserved for future use.
 * @param dwMessage The number of a message to display to the user. For message numbers
 *		see PT_GUIMSG_XXXX. GuiState indicates if a Message is provided; if not
 *		the parameter is 0.
 * @param byProgress A Value that indicates (as a percentage) the amount of progress
 *		in the development of a Sample/BIR. The value may be used to display a progress
 *		bar. GuiState indicates if a sample Progress value is provided in the call;
 *		if not the parameter is 0. This parameter is reserved for future use,
 *		currently it is always 0.
 * @param pSampleBuffer The current sample buffer for the application to display.
 *		GuiState indicates if a sample Buffer is provided; if not the parameter is
 *		NULL. This parameter is reserved for future use, currently it is always NULL.
 *		The buffer is allocated and controlled by PerfectTrust, it must not be freed.
 * @param pData Optional data, which may be available for some GUI message codes.
 *		If no data is provided the parameter is NULL. The data is allocated and
 *		controlled by PerfectTrust, it must not be freed.
 * @return Status code
 *
 * It is guaranteed, that if an operation displays GUI, the first GUI message will be
 * "Begin GUI" and the last one "End GUI". At least one more call with message
 * "End GUI" will be sent even in the case when the application used 
 * @c pbyResponse = PT_CANCEL.
 */
typedef PT_STATUS (PTAPI *PT_GUI_STATE_CALLBACK) (
	IN void *pGuiStateCallbackCtx,
	IN PT_DWORD dwGuiState,
	OUT PT_BYTE *pbyResponse,
	IN PT_DWORD dwMessage,
	IN PT_BYTE byProgress,
	IN void *pSampleBuffer,
	IN PT_DATA *pData
);


/**
 * A type of the callback function that the application must supply to the PTNavigate
 * and PTClickCalibrate functions to receive the navigation data.
 *
 * @param pNavigationCallbackCtx A generic pointer to context information that was
 *     provided when calling PTNavigate or PTClickCalibrate.
 * @param pNavigationData The received navigation data.
 * @param pbyResponse The response from the application back to the PTAPI on return
 *     from the callback. Can be one of the values PT_CANCEL or PT_CONTINUE. Other 
 *     values are reserved for future use.
 * @return Status code
 */
typedef PT_STATUS (PTAPI *PT_NAVIGATION_CALLBACK) (
    IN void *pNavigationCallbackCtx,
    IN PT_NAVIGATION_DATA *pNavigationData,
    OUT PT_BYTE *pbyResponse
);


/**
 * A type of the callback function that the application could optionally
 * supply to the PTSleep function to be periodically called while FM is
 * in a sleep or standby mode.
 *
 * @param pIdleCallbackCtx A generic pointer to context information that
 *     was provided when calling PTSleep.
 * @param pbyResponse The response from the application back to the PTAPI
 *     on return from the callback. Can be one of the values PT_SLEEP_STOP,
 *     i.e. wakeup, or PT_SLEEP_CONTINUE, i.e. continue to sleep. Other
 *     values are reserved for future use.
 * @return Status code
 */
typedef PT_STATUS (PTAPI *PT_IDLE_CALLBACK) (
    IN void *pIdleCallbackCtx,
    OUT PT_BYTE *pbyResponse
);

                                           
/**
 * Prototype of callback function that an application supplies to allow to send data
 * in the form of a sequence of packets to the remote instance of PTAPI library. This
 * is a blocking function, which does not return until the request is processed, or
 * a communication error is encountered.
 * @param pCommCallbackCtx A generic pointer to context information that was provided
 *	    by the original requester and is being returned to its originator.
 * @param pInPkt A pointer to a packet to be sent to the communicating partner. This
 *	    data is dynamically allocated and controlled by PTAPI, must not be freed
 *      by the application.
 * @param ppOutPkt An address of a pointer to be set to point to the packet received
 *		back from the communicating partner. The data has to be allocated by the 
 *      callback function and will be released by the PTAPI library.
 * @return Status code
 */
typedef PT_STATUS (PTAPI *PT_COMM_CALLBACK) (
    IN void *pCommCallbackCtx,
    IN PT_DATA *pInPkt,
    OUT PT_DATA **ppOutPkt
);


/**
 * This is value indicating that message parameter contains 
 * valid value.
 */
#define PT_MESSAGE_PROVIDED         (0x1)

/**
 * This is value indicating that progress parameter contains 
 * valid value with progress of verification.
 */
#define PT_PROGRESS_PROVIDED        (0x2)

/**
 * This is value indicating that sample image is provided.
 */
#define PT_SAMPLE_IMAGE_PROVIDED    (0x4)

/**
 * This is value indicating that additional data are provided
 */
#define PT_DATA_PROVIDED     (0x8)


/**
 * GUI sample image
 */
typedef struct pt_gui_sample_image {
    PT_DWORD Width;         ///< Image width
    PT_DWORD Height;        ///< Image height
    PT_DATA  ImageData;     ///< Image data
} PT_GUI_SAMPLE_IMAGE;


/**
 * @name Callback response values
 */
/*@{*/

/** Cancel biometric operation. */
#define PT_CANCEL    0x00
/** Continue with biometric operation. */
#define PT_CONTINUE  0x01

/*@}*/

/**
 * @name GUI Callback messages
 */
/*@{*/
/** Scanned good image */
#define PT_GUIMSG_GOOD_IMAGE			0
/** No finger detected */
#define PT_GUIMSG_NO_FINGER             1
/** Finger image is too light */
#define PT_GUIMSG_TOO_LIGHT             2
/** Finger is too dry */
#define PT_GUIMSG_TOO_DRY               3  
/** Finger image is too dark */
#define PT_GUIMSG_TOO_DARK              4
/** Finger is too high */
#define PT_GUIMSG_TOO_HIGH              5
/** Finger is too low */
#define PT_GUIMSG_TOO_LOW               6
/** Finger is too left */
#define PT_GUIMSG_TOO_LEFT              7
/** Finger is too right */
#define PT_GUIMSG_TOO_RIGHT             8
/** Finger image is too small */
#define PT_GUIMSG_TOO_SMALL             9
/** Finger image is too strange */
#define PT_GUIMSG_TOO_STRANGE           10
/** Finger has bad quality */
#define PT_GUIMSG_BAD_QUALITY           11
/** Put finger 1st time */
#define PT_GUIMSG_PUT_FINGER			12
/** Put finger 2nd time */
#define PT_GUIMSG_PUT_FINGER2			13
/** Put finger 3rd time */
#define PT_GUIMSG_PUT_FINGER3			14
/** Remove finger */
#define PT_GUIMSG_REMOVE_FINGER         15
/** Consolidation failed */
#define PT_GUIMSG_CONSOLIDATION_FAIL    16
/** Consolidation succeed */
#define PT_GUIMSG_CONSOLIDATION_SUCCEED	17
/** Clean the sensor */
#define PT_GUIMSG_CLEAN_SENSOR			18
/** Keep finger on the sensor */
#define PT_GUIMSG_KEEP_FINGER           19
/** Non specific GUI start (not used now) */
#define PT_GUIMSG_START                 20
/** GUI start for verification */
#define PT_GUIMSG_VERIFY_START          21
/** GUI start for enrollment */
#define PT_GUIMSG_ENROLL_START          22
/** GUI start for finger detection */
#define PT_GUIMSG_FINGER_DETECT_START   23
/** GUI finished without specification of success of biometric operation */
#define PT_GUIMSG_GUI_FINISH            24
/** GUI finished signaling success of biometric operation */
#define PT_GUIMSG_GUI_FINISH_SUCCEED    25
/** GUI finished signaling failure of biometric operation */
#define PT_GUIMSG_GUI_FINISH_FAIL       26
/** GUI start for sensor calibration */
#define PT_GUIMSG_CALIB_START           27
/** Finger was swiped too fast */
#define PT_GUIMSG_TOO_FAST              28
/** Finger was too skewed during swipe */
#define PT_GUIMSG_TOO_SKEWED            29
/** Finger swipe was too short */
#define PT_GUIMSG_TOO_SHORT             30
/** Touch sensor with finger */
#define PT_GUIMSG_TOUCH_SENSOR          31
/** Image processing started */
#define PT_GUIMSG_PROCESSING_IMAGE      32
/** Finger swipe is in progress */
#define PT_GUIMSG_SWIPE_IN_PROGRESS     33
/** Backward movement detected */
#define PT_GUIMSG_BACKWARD_MOVEMENT     34
/** Finger joint detected */
#define PT_GUIMSG_JOINT_DETECTED        35
/** Center finger and press harder */
#define PT_GUIMSG_CENTER_AND_PRESS_HARDER 36
/** Image processing finished */
#define PT_GUIMSG_IMAGE_PROCESSED       37
/*@}*/


/**
 * Prototype of callback function which deals with the presentation of biometric
 * streaming data. Currently not implemented.
 */
typedef PT_STATUS (PTAPI *PT_GUI_STREAMING_CALLBACK) (void);


/*------------ basic values ------------------------------------------------*/

/**
 * Boolean false value
 */
#define	PT_FALSE		(0)

/**
 * Boolean true value
 */
#define	PT_TRUE			(1)

/*-------------------------------------------------------------------------*/

#endif /* tfmtypes_h */
