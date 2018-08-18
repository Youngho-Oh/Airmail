/*********************************************************************
    Filename:       hal_util_rf.h

    Description:    

    Notes:			

    Copyright (c) 2006 by Texas Instruments, Inc.
    All Rights Reserved.  Permission to use, reproduce, copy, prepare
    derivative works, modify, distribute, perform, display or sell this
    software and/or its documentation for any purpose is prohibited
    without the express written consent of Texas Instruments, Inc.
*********************************************************************/
#ifndef UTIL_RF
#define UTIL_RF

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */



/*********************************************************************
 * CONSTANTS
 */




/*********************************************************************
 * TYPEDEFS
 */



/*********************************************************************
 * PUBLIC FUNCTIONS
 */
char halSampleED(unsigned char channel, unsigned short sampleTime);
void halSetRxScanMode(void);
void halSetRxNormalMode(void);

#ifdef __cplusplus
}
#endif

#endif

