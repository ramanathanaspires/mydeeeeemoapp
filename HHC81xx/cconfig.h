#ifndef CCONFIG_H
#define CCONFIG_H

#include "Qt/qstring.h"
//AT#GPPPCFG="",25,2
#define BUILDVERSION           ("2.4.6") // ("2.4.5")// ("2.4.4")    // ("2.4.3")  //("2.3")
#define BUILDDATE              ("2014-02-20T16:15:00") //("2014-02-11T11:30:00")//("2014-02-04T11:30:00")//("2014-01-28T11:30:00")  //("2014-01-03T11:30:00") //("2014-01-03T17:30:00")// ("2013-12-27T17:30:00")// ("2013-12-24T17:30:00")// ("2013-12-18T17:30:00") // ("2013-11-29T17:30:00")// ("2013-11-28T17:30:00")// ("2013-11-11T17:30:00")// ("2013-11-09T17:30:00")//("2013-11-1T17:30:00") //("2013-10-30T17:00:00")// ("2013-10-28T111:30:00")//("2013-10-25T117:30:00") //  ("2013-10-17T117:30:00")  // ("2013-08-09T12:00:00")// ("2013-08-22T12:00:00")//("2013-07-04T19:00:10")    //("2013-06-07T11:00:10")   //("2012-06-22T10:00:00")
#define DEBUG                   (0)   /**  Enable the debug information set value as 1.for disable set to 0 */
#define SERIAL_DEBUG_FLAG       (0)   /**  Enable the debug information set value as 1.for disable set to 0 */
//#define DEBUG_PORTNAME          ("/dev/ttyS0")
#define COPROCESSOR_PORTNAME    ("/dev/ttyS2")
#define GSM_PORTNAME            ("/dev/ttyS1")
//#define BARCODE_PORTNAME        ("/dev/ttyS3")
#define GSM_CMUX1PORTNAME       ("/dev/cmux1")
#define GSM_CMUX3PORTNAME       ("/dev/cmux3")
#define GPS_PORTNAME        ("/dev/ttyS3")
//#define ENABLE_BARCODE          (0) /* set 1 to process the barcode, set 0 to dont process the barcode. */

//const QString const_strCONFIG_FILENAME = "/etc/.config/HHC80xx.plist";  /* config file path */

#endif // CCONFIG_H
