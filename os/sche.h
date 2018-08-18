/*
 * sche.h
 *
 *  Created on: 2018. 7. 22.
 *      Author: eclipse
 */

#ifndef OS_SCHE_H_
#define OS_SCHE_H_

/***********************************************************************************
 * INCLUDES
 */
#include "wow_config.h"
#include "wow_bool.h"

/***********************************************************************************
 * TYPEDEFS
 */

typedef struct {
	unsigned int bit_event;		// detail event about event task
	unsigned int time_wakeup;	// wake-up time
	void (*func_event)(void);	// when occur event, this function is excuted.
} sche_task;

/***********************************************************************************
* MACROS
*/

/***********************************************************************************
 * VALUES
 */

extern sche_task task_list[NUM_OF_TASK];

// when task's event is occurred, this value is changed.
extern unsigned int int_task_evt;

/***********************************************************************************
 * FUNCTIONS
 */
T_ERROR wow_sche_task_init(void);
T_ERROR wow_sche_task_add(sche_task * add_task_info, unsigned char priority, char is_forced);
void wow_sche_task_run(void);

T_ERROR wow_sche_task_evt_enable(unsigned int task, unsigned int event);
T_ERROR wow_sche_task_evt_disable(unsigned int task, unsigned int event);

T_ERROR wow_sche_task_sleep(unsigned int sleep_ms);

void wow_sche_task_wakeup_check(void);

#endif /* OS_SCHE_H_ */
