/*
 * kernel_clock.h
 *
 *  Created on: 2018. 8. 8.
 *      Author: eclipse
 */

#ifndef OS_KERNEL_CLOCK_H_
#define OS_KERNEL_CLOCK_H_

/***********************************************************************************
 * INCLUDES
 */
#include "wow_config.h"
#include "wow_bool.h"

/***********************************************************************************
 * TYPEDEFS
 */

/***********************************************************************************
* MACROS
*/

/***********************************************************************************
 * VALUES
 */

// define kernel time value.
extern unsigned long int_time_ms;

/***********************************************************************************
 * FUNCTIONS
 */
T_ERROR wow_clock_init(void);
T_ERROR wow_clock_start(void);
T_ERROR wow_clock_stop(void);

unsigned long wow_clock_get_cur_time(void);

void wow_clock_tick_increment(void);

#endif /* OS_KERNEL_CLOCK_H_ */
