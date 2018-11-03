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

#include "rf/rf_config.h"

/*********************************************************************
 * CONSTANTS
 */




/*********************************************************************
 * TYPEDEFS
 */



/*********************************************************************
 * PUBLIC FUNCTIONS
 */
int8_t halSampleED(uint8_t channel, uint16_t sampleTime);
void halSetRxScanMode(void);
void halSetRxNormalMode(void);

#ifdef __cplusplus
}
#endif

#endif

