/*
 * task_hal.c
 *
 *  Created on: 2018. 8. 24.
 *      Author: eclipse
 */


#include "stdio.h"

#include "task_hal.h"

#include "sys/log.h"

sche_task task_hal = {0, 0, NULL};

static T_ERROR task_hal_event_function(unsigned char cur_task_event);
static T_ERROR _task_hal_event_init(void);


void task_hal_init(void)
{
	task_hal.bit_event = 0;
	task_hal.time_wakeup = 0;
	task_hal.func_event = task_hal_event_function;

	wow_sche_task_add(&task_hal, PRIORITY_TASK_HAL, true);
}

T_ERROR task_hal_event_function(unsigned char cur_task_event)
{
	T_ERROR value_task_return = OS_OK;

	switch(cur_task_event){
	case EVENT_HAL_INIT :
		_task_hal_event_init( );
		break;
	default :
		log_message("Undefined event!!!\r\n", 20);
		value_task_return = OS_PARAM_ERROR;
		break;
	}

	return value_task_return;
}

T_ERROR _task_hal_event_init(void)
{
	log_message("Init HAL task init!!!\r\n", 23);

	return OS_OK;
}
