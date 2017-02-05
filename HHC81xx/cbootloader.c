
#include <stdio.h>

#include <usb.h>
#include <hid.h>

#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "cbootloader.h"
static HIDInterface *hid = NULL;
unsigned char        usbBuf[64];

/****************************************************************************
 Function    : usbOpen
 Description : Searches for and opens the first available HID Bootloader device.
 Parameters  : unsigned short         Vendor ID to search for.
               unsigned short         Product ID to search for.
 Returns     : Status code:
                 ERR_NONE             Success; device open and ready for I/O.
                 ERR_USB_INIT1        Initialization error in HID init code.
                 ERR_USB_INIT2        New HID alloc failed.
                 ERR_UBW32_NOT_FOUND  HID Bootloader not detected on any USB bus
                                      (might be connected but not in
                                       Bootloader mode).
 ****************************************************************************/
ErrorCode usbOpen(
  const unsigned short vendorID,
  const unsigned short productID)
{
    ErrorCode           status = ERR_USB_INIT1;
    HIDInterfaceMatcher matcher;

    matcher.vendor_id  = vendorID;
    matcher.product_id = productID;
    matcher.matcher_fn = NULL;

    if(HID_RET_SUCCESS == hid_init()) {
            status = ERR_USB_INIT2;
            if((hid = hid_new_HIDInterface())) {
                    if(HID_RET_SUCCESS ==
                      hid_force_open(hid,0,&matcher,3)) {
                            return ERR_NONE;
                    }
                    status = ERR_UBW32_NOT_FOUND;
                    hid_delete_HIDInterface(&hid);
            }
            hid_cleanup();
    }
    return status;
}

/****************************************************************************
 Function    : usbWrite
 Description : Write data packet to currently-open HID Bootloader device, optionally
               followed by a packet read operation.  Data source is always
               global array usbBuf[].  For read operation, destination is
               always usbBuf[] also, overwriting contents there.
 Parameters  : char       Size of source data in bytes (max 64).
               char       If set, read response packet.
 Returns     : ErrorCode  ERR_NONE on success, ERR_USB_WRITE on error.
 Notes       : Device is assumed to have already been successfully opened
               by the time this function is called; no checks performed here.
 ****************************************************************************/
ErrorCode usbWrite(
  const char len,
  const char read)
{
    if(HID_RET_SUCCESS != hid_interrupt_write(hid,0x01,(const char *)usbBuf,len,0))
            return ERR_USB_WRITE;

    DEBUGMSG("\rDone w/write");

    if(read) {
        DEBUGMSG("\rAbout to read");
        if(HID_RET_SUCCESS != hid_interrupt_read(hid,0x81,usbBuf,64,0))
        {
            return ERR_USB_READ;
        }

    }
    return ERR_NONE;
}

/****************************************************************************
 Function    : usbClose
 Description : Closes previously-opened USB device.
 Parameters  : None (void)
 Returns     : Nothing (void)
 Notes       : Device is assumed to have already been successfully opened
               by the time this function is called; no checks performed here.
 ****************************************************************************/
void usbClose(void)
{        
        (void)hid_close(hid);        
        hid_delete_HIDInterface(&hid);        
        (void)hid_cleanup();
        hid = NULL;
}

static char          *hexFileData = NULL; /* Memory-mapped hex file data */
static char          *hexPlusOne;         /* Saves a lot of "+1" math    */
static int            hexFd;              /* Open hex file descriptor    */
static size_t         hexFileSize;        /* Save for use by munmap()    */
static unsigned char  hexBuf[56];         /* Data read/written to USB    */
//extern unsigned char  usbBuf[];           /* In usb code                 */

/****************************************************************************
 Function    : hexOpen
 Description : Open and memory-map an Intel hex file.
 Parameters  : char*      Filename (must be non-NULL).
 Returns     : ErrorCode  ERR_NONE     Success
                          ERR_HEX_OPEN File not found or no read permission
                          ERR_HEX_STAT fstat() call failed for some reason
                          ERR_HEX_MMAP Memory-mapping failed
 ****************************************************************************/
ErrorCode hexOpen(char * const filename)
{
    ErrorCode status = ERR_HEX_OPEN;

    if((hexFd = open(filename,O_RDONLY)) >= 0) {

            struct stat filestat;

            status = ERR_HEX_STAT;
            if(!fstat(hexFd,&filestat)) {

                    status      = ERR_HEX_MMAP;
                    hexFileSize = filestat.st_size;
                    if((hexFileData = mmap(0,hexFileSize,PROT_READ,
                      MAP_FILE | MAP_SHARED,hexFd,0)) != (void *)(-1)) {
                            hexPlusOne = &hexFileData[1];
                            return ERR_NONE;
                    }
                    /* Else clean up and return error code */
                    hexFileData = NULL;
            }
            (void)close(hexFd);
    }
    return status;
}

/****************************************************************************
 Function    : atoh (inline pseudo-function)
 Description : Converts two adjacent ASCII characters (representing an 8-bit
               hexadecimal value) to a numeric value.
 Parameters  : int            Index (within global hex array) to start of
                              input string; must contain at least two chars.
 Returns     : unsigned char  Numeric result; 0 to 255.
 Notes       : Range checking of input characters is somewhat slovenly;
               all input is assumed to be in the '0' to '9' and 'A' to 'F'
               range.  But if any such shenanigans were to occur, the line
               checksum will likely catch it.
 ****************************************************************************/
#define atoh(pos) \
  ((((hexFileData[pos] <= '9') ? (hexFileData[pos] - '0') : \
     (0x0a + toupper(hexFileData[pos]) - 'A')) << 4) |      \
   ( (hexPlusOne [pos] <= '9') ? (hexPlusOne [pos] - '0') : \
     (0x0a + toupper(hexPlusOne [pos]) - 'A')      ))

/****************************************************************************
 Function    : issueBlock
 Description : Send data over USB bus to HID Bootloader.
 Parameters  : unsigned int  Destination address on PIC device.
               char          Byte count (max 56).
               char          Verify vs. write.
 Returns     : ErrorCode     ERR_NONE on success, or error code as returned
                             from usbWrite();
 ****************************************************************************/
static ErrorCode issueBlock(
  const unsigned int  addr,
  const char          len,
  const char          verify)
{
    ErrorCode status;

    fflush(stdout);

    bufWrite32(usbBuf,1,addr);
    usbBuf[5] = len;

    if(verify) {
            DEBUGMSG("\rVerifying");
            usbBuf[0] = GET_DATA;
            if(ERR_NONE == (status = usbWrite(6,1))) {
                fflush(stdout);
                return (memcmp(&usbBuf[64 - len],hexBuf,len) ?
                ERR_VERIFY : ERR_NONE);

            }
    } else {
            DEBUGMSG("\rWriting");
            usbBuf[0] = PROGRAM_DEVICE;
            /* Regardless of actual byte count, data packet is always
               64 bytes.  Following the header, the bootloader wants the
               data portion 'right justified' within packet.  Odd. */
            memcpy(&usbBuf[64 - len],hexBuf,len);
            if((ERR_NONE == (status = usbWrite(64,0))) && (len < 56))
            {
                    /* Short data packets need flushing */
                    DEBUGMSG("\rCompleting");
                    usbBuf[0] = PROGRAM_COMPLETE;
                    status    = usbWrite(1,0);
            }
    }
    return status;
}

/****************************************************************************
 Function    : hexWrite
 Description : Writes (and optionally verifies) currently-open hex file to
               HID Bootloader device.
 Parameters  : char       Verify (1) vs. write (0).
 Returns     : ErrorCode  ERR_NONE on success, else various other values as
                          defined in bootloader.h.
 Notes       : HID Bootloader device and hex file are both assumed already open and
               valid; no checks performed here.
 ****************************************************************************/
ErrorCode hexWrite(const char verify)
{
    char         *ptr,pass;
    ErrorCode     status;
    int           checksum,i,end,offset;
    short         bufLen;
    unsigned int  len,type,addrHi,addrLo,addr32,addrSave;

    for(pass=0;pass<=verify;pass++) {
      offset   = 0; /* Start at beginning of hex file         */
      bufLen   = 0; /* Hex buffer initially empty             */
      addrHi   = 0; /* Initial address high bits              */
      addrSave = 0; /* PIC start addr for hex buffer contents */
      addr32   = 0;

      if(pass) {(void)printf("\nVerifying:"); offset = 110;}

      for(;;) {  /* Each line in file */

        /* Line start contains length, 16-bit address and type */
        if(3 != sscanf(&hexFileData[offset],":%02x%04x%02x",
          &len,&addrLo,&type)) return ERR_HEX_SYNTAX;

        /* Position of %02x checksum at end of line */
        end = offset + 9 + len * 2;

        /* Verify checksum on first (write) pass */
        if(!pass) {
          for(checksum = 0,i = offset + 1;i < end;
            checksum = (checksum + (0x100 - atoh(i))) & 0xff,i += 2);
          if(atoh(end) != checksum) return ERR_HEX_CHECKSUM;
        }

        /* Process different hex record types.  Using if/else rather
           than a switch in order to better handle EOF cases (allows
           simple 'break' rather than goto or other nasties). */

        if(0 == type) { /* Data record */

          /* If new record address is not contiguous with prior record,
             issue accumulated hex data (if any) and start anew. */
          if((addrHi + addrLo) != addr32) {
            addr32 = addrHi + addrLo;
            if(bufLen) {
              if(ERR_NONE != (status = issueBlock(addrSave,bufLen,pass)))
                return status;
              bufLen = 0;
            }
            addrSave = addr32;
          }

          /* Parse bytes from line into hexBuf */
          for(i = offset + 9;i < end;i += 2) {
            hexBuf[bufLen++] = atoh(i); /* Add to hex buffer */
            fflush(stdout);
            /* If buffer is full, issue block and start anew */
            if(sizeof(hexBuf) == bufLen) {
              if(ERR_NONE != (status = issueBlock(addrSave,bufLen,pass)))
                return status;
              bufLen = 0;
            }

            /* Increment address, wraparound as per hexfile spec */
            if(0xffffffff == addr32) {
              /* Wraparound.  If any hex data, issue and start anew. */
              if(bufLen) {
                if(ERR_NONE !=
                  (status = issueBlock(addrSave,bufLen,pass)))
                    return status;
                bufLen = 0;
              }
              addr32 = 0;
            } else {
              addr32++;
            }

            /* If issueBlock() used, save new address for next block */
            if(!bufLen) addrSave = addr32;
          }

        } else if(1 == type) { /* EOF record */

          break;

        } else if(4 == type) { /* Extended linear address record */

          if(1 != sscanf(&hexFileData[offset+9],"%04x",&addrHi))
            return ERR_HEX_SYNTAX;
          addrHi <<= 16;
          addr32 = addrHi + addrLo;
          /* Assume this means a noncontiguous address jump; issue block
             and start anew.  The prior noncontiguous address code should
             already have this covered, but in the freak case of an
             extended address record with no subsequent data, make sure
             the last of the data is issued. */
          if(bufLen) {
            if(ERR_NONE != (status = issueBlock(addrSave,bufLen,pass)))
              return status;
            bufLen   = 0;
            addrSave = addr32;
          }
        }
        else { /* Unsupported record type */
          return ERR_HEX_RECORD;
        }

        /* Advance to start of next line (skip CR/LF/etc.), unless EOF */
        if(NULL == (ptr = strchr(&hexFileData[end+2],':'))) break;

        offset = ptr - hexFileData;
      }

      /* At end of file, issue any residual data (counters reset at top) */
      if(bufLen &&
        (ERR_NONE != (status = issueBlock(addrSave,bufLen,pass))))
          return status;

      /* Make sure last data is flushed (issueBlock() does this
         automatically if less than 56 bytes...but if the last packet
         is exactly this size, an explicit flush is done here). */
      if(!pass && (bufLen == 56)) {
        DEBUGMSG("\rCompleting");
        usbBuf[0] = PROGRAM_COMPLETE;
        if(ERR_NONE != (status = usbWrite(1,0))) return status;
      }
    }

    return ERR_NONE;
}

/****************************************************************************
 Function    : hexClose
 Description : Unmaps and closes previously-opened hex file.
 Parameters  : None (void)
 Returns     : Nothing (void)
 Notes       : File is assumed to have already been successfully opened
               by the time this function is called; no checks performed here.
 ****************************************************************************/
void hexClose(void)
{
        (void)munmap(hexFileData,hexFileSize);
        hexFileData = NULL;
        (void)close(hexFd);
}


//extern unsigned char usbBuf[];  /* In usb code */

/* Program's actions aren't necessarily performed in command-line order.
   Bit flags keep track of options set or cleared during input parsing,
   then are singularly checked as actions are performed.  Some actions
   (such as writing) don't have corresponding bits here; certain non-NULL
   string values indicate such actions should occur. */
#define ACTION_UNLOCK (1 << 0)
#define ACTION_ERASE  (1 << 1)
#define ACTION_VERIFY (1 << 2)
#define ACTION_RESET  (1 << 3)

bool BootLoader(const char * File)
{
    char        *hexFile   = NULL,
                 actions   = ACTION_VERIFY;
    ErrorCode    status    = ERR_NONE;
    int          i;
    unsigned int vendorID  = 0x04d8,
                 productID = 0x003c;

    const char * errorString[ERR_EOL] = {
            "Missing or malformed command-line argument",
            "Command not recognized",
            "HID Bootloader device not found (is device attached and in Bootloader mode?)",
            "USB initialization failed (phase 1)",
            "USB initialization failed (phase 2)",
            "HID Bootloader device could not be opened for I/O",
            "USB write error",
            "USB read error",
            "Could not open hex file for input",
            "Could not query hex file size",
            "Could not map hex file to memory",
            "Unrecognized or invalid hex file syntax",
            "Bad end-of-line checksum in hex file",
            "Unsupported record type in hex file",
            "Verify failed"
    };
    actions |= ACTION_UNLOCK;
    hexFile = (char*) File;
    actions |= ACTION_ERASE;
    actions |= ACTION_RESET;


    /*find/open USB device. */

    if((ERR_NONE == status) &&
       (ERR_NONE == (status = usbOpen(vendorID,productID))))
    {

            /* And start doing stuff... */

            (void)printf("\rHID Bootloader device found");
            usbBuf[0] = QUERY_DEVICE;
            if(ERR_NONE == (status = usbWrite(1,1))) {
                    int j;
                    for(i=1,j=3;usbBuf[j]!=TypeEndOfTypeList;j+=9,i++) {
                      if(usbBuf[j] == TypeProgramMemory)
                        (void)printf("\r: %d bytes free",bufRead32(j + 5));
                    }
            }
            (void)putchar('\n');

            if((ERR_NONE == status) && (actions & ACTION_UNLOCK)) {
                    (void)puts("Unlocking configuration memory...");
                    usbBuf[0] = UNLOCK_CONFIG;
                    usbBuf[1] = UNLOCKCONFIG;
                    status    = usbWrite(2,0);
            }

            /* Although the next actual operation is ACTION_ERASE,
               if we anticipate hex-writing in a subsequent step,
               attempt opening file now so we can display any error
               message quickly rather than waiting through the whole
               erase operation (it's usually a simple filename typo). */
            if((ERR_NONE == status) && hexFile &&
               (ERR_NONE != (status = hexOpen(hexFile))))
                    hexFile = NULL;  /* Open or mmap error */

            if((ERR_NONE == status) && (actions & ACTION_ERASE)) {
                    (void)puts("\rErasing...");
                    usbBuf[0] = ERASE_DEVICE;
                    status    = usbWrite(1,0);
                    /* The query here isn't needed for any technical
                       reason, just makes the presentation better.
                       The ERASE_DEVICE command above returns
                       immediately...subsequent commands can be made
                       but will pause until the erase cycle completes.
                       So this query just keeps the "Writing" message
                       or others from being displayed prematurely. */
                    usbBuf[0] = QUERY_DEVICE;
                    status    = usbWrite(1,1);
            }

            if(hexFile) {
                    if(ERR_NONE == status) {
                      (void)printf("\rWriting hex file '%s':",hexFile);
                      status = hexWrite((actions & ACTION_VERIFY) != 0);
                      (void)putchar('\n');
                    }
                    hexClose();
            }

            if((ERR_NONE == status) && (actions & ACTION_RESET)) {
                    (void)puts("\rResetting device...");
                    usbBuf[0] = RESET_DEVICE;
                    status = usbWrite(1,0);
            }

            usbClose();
    }

    if (ERR_NONE != status)
    {
        strcpy(err , "\r HID Bootloader Error- ");

           if (status <= ERR_EOL){
                strcat(err ,errorString[status - 1]);
            }
            else
                strcat(err , " of indeterminate type.");
            return false;
    }
    return  true;
}

bool isUSBBootloader()
{    
    ErrorCode    status    = ERR_NONE;
    unsigned int vendorID  = 0x04d8,
                 productID = 0x003c;
    if((ERR_NONE == status) &&
       (ERR_NONE == (status = usbOpen(vendorID,productID)))) {

            /* And start doing stuff... */            
            (void)printf("\rHID Bootloader device found");
            usbClose();            
            return true;
        }

    hid= NULL;
    return false;
}
