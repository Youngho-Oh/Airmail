/*
 * wow.h
 *
 *  Created on: 2018. 7. 22.
 *      Author: eclipse
 */

#ifndef OS_WOW_BOOL_H_
#define OS_WOW_BOOL_H_

/***********************************************************************************
 * INCLUDES
 */
#include "wow_config.h"

#if (EXTERNAL_BOOL_DEFINED == 1)
// YOU ADD INCLUDE FILE PATH WHICH DEFINED BOOL
#include "hal/bool.h"
#endif
/***********************************************************************************
* MACROS
*/

/***********************************************************************************
 * TYPEDEFS
 */

#if (EXTERNAL_BOOL_DEFINED == 0)
typedef unsigned char bool;

#define true	1
#define false	0
#endif

typedef enum {
	OS_PARAM_ERROR = -1,
	OS_OK = 0,
} T_ERROR;

#endif /* OS_WOW_BOOL_H_ */
