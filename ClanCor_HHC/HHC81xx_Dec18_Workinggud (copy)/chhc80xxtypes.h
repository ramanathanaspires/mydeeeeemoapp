#ifndef CHHC80XXTYPES_H
#define CHHC80XXTYPES_H

namespace ClanCor
{
/**
     * The enum describes the beep types.
     */
enum E_BeepType
{
    eBeepType_SINGLE_BEEP = 1, /**< single beep */
    eBeepType_SUCCESS_BEEP = 2, /**< success beep */
    eBeepType_ERROR_BEEP = 3, /**< error beep */
    eBeepType_LONG_BEEP = 4 /**< long beep */
};

/**
     * The enum describes the keypad modes.
     */
enum E_KeypadMode
{
    eKeypadMode_NUMERIC = 1, /**< numeric mode */
    eKeypadMode_ALPHABETS = 2, /**< alphabets mode */
    eKeypadMode_ALPHABETS_CAPS = 3 /**< alphabets CapsLock mode */
};

/**
     * The enum describes the GPRS NETWORK modes.
     */
enum E_NetworkMode
{
    eNetworkMode_Auto=0,/**< Auto mode */
    eNetworkMode_Manual = 1 /**< Manual mode */
};

/**
     * The enum describes the charging status.
     */
enum E_ChargeStatus
{
    eChargeStatus_NONE = 0,         /**< charger not connected*/
    eChargeStatus_CONNECTED = 1,    /**< charger connected */
    eChargeStatus_REMOVED = 2,      /**< charger removed */
    eChargeStatus_COMPLETED = 3,    /**< charger completed */
    eChargeStatus_INVALID = 4       /**< invalid charger */
};

/**
     * The enum describes the active network status.
     */
enum E_NetworkStatus
{
    eNetworkStatus_NONE = 0,     /**< No active network */
    eNetworkStatus_ETHERNET = 1, /**< active network is Ethernet */
    eNetworkStatus_GPRS = 2,     /**< active network is GPRS */
    eNetworkStatus_WIFI = 3      /**< active network is WIFI */
};

/**
         * The enum describes the Gadget Types
         */
enum E_GadgetMode
{
    eSerial_USBMode = 0, /**< Serial Communication Mode */
    eUSB_GadgetMode = 1, /**< USB Gadget Mode */
    eMass_StorageMode = 2, /**< Mass Storage Mode*/
    eNormal_StorageMode = 3 /**< Normal Storage Mode*/
};

/**
         * The enum describes the Mass Storage Types
         */
enum E_MassStorage
{
    eNone = 0, /**< None is Selected for Other Types Of Gadgets */
    ePenDrive = 1, /**< Pen Drive Type For Mass Storage */
    eSDCard = 2 /**< SD Card Type For Mass Storage */
};

/**
     * The enum describes the firmware log types.
     */
enum E_FirmwareLog
{
    eFirmwareLog_Process     = 0,  /**< Process log */
    eFirmwareLog_Power       = 1  /**< Power log */
};

/**
     * The enum describes track options to read magnetic card.
     */
enum E_MagneticCard
{
    eMagneticCard_Read_ALL      = 0,  /**< Reads all 3 tracks */
    eMagneticCard_Read_TRACK1   = 1,  /**< Reads Track1 */
    eMagneticCard_Read_TRACK2   = 2,  /**< Reads Track2 */
    eMagneticCard_Read_TRACK3   = 3  /**< Reads Track3*/
};

/**
     * The enum describes track options to SMART Card Slot.
     */
enum E_SmartcardSlot
{
    eSmartCard_slot1   = 2,  /**< Read slot1 */
    eSmartCard_slot2   = 3  /**< Read slot2 */
};
}

#endif // CHHC80XXTYPES_H
