/*
 * sche.c
 *
 *  Created on: 2018. 7. 22.
 *      Author: eclipse
 */

#include "stdio.h"
#include "string.h"

#include "sche.h"
#include "kernel_clock.h"

sche_task task_list[NUM_OF_TASK] = {
		{0, 0, NULL},
		{0, 0, NULL},
		{0, 0, NULL}
};

// BIT WISED
unsigned int int_task_evt = 0;
unsigned int int_task_sleep = 0;

unsigned int running_executed_task = 0;

T_ERROR wow_sche_task_init( )
{
	int_task_evt = 0;

	memset( (void*)task_list, 0, (sizeof(sche_task)*NUM_OF_TASK) );

	return OS_OK;
}

T_ERROR wow_sche_task_add(sche_task * add_task_info, unsigned char priority, char is_forced)
{
	if(add_task_info == NULL)
		return OS_PARAM_ERROR;
	if( (priority >= NUM_OF_MAXIMUM_TASK) || (priority >= NUM_OF_TASK) )
		return OS_PARAM_ERROR;
	if( (is_forced != false) && (is_forced != true) )
		return OS_PARAM_ERROR;

	if(task_list[priority].func_event == NULL)
		memcpy((void *)&task_list[priority], (void *)add_task_info, sizeof(sche_task));
	else if(is_forced == true)	// task_list[priority].func_event != NULL && is_forced == true
		memcpy((void *)&task_list[priority], (void *)add_task_info, sizeof(sche_task));
	else	// task_list[priority].func_event != NULL && is_forced == false
		return OS_PARAM_ERROR;

	return OS_OK;
}

void wow_sche_task_run( )
{
	char ptr_task_evt_state = 0;
	bool is_task_enable = false;

	while(1){
		is_task_enable = (int_task_evt >> ptr_task_evt_state)&0x01;

		if( (is_task_enable == true) && (task_list[ptr_task_evt_state].func_event != NULL) ){
			running_executed_task = ptr_task_evt_state;
			task_list[ptr_task_evt_state].func_event();
		}

		if( ptr_task_evt_state++ == NUM_OF_TASK )
			ptr_task_evt_state = 0;
	}
}

T_ERROR wow_sche_task_evt_enable(unsigned int task, unsigned int event)
{
	if( (task >= NUM_OF_MAXIMUM_TASK) || (task >= NUM_OF_TASK) )
		return OS_PARAM_ERROR;
	if( task_list[task].func_event == NULL )
		return OS_PARAM_ERROR;

	int_task_evt |= (0x01 << running_executed_task);
	task_list[task].bit_event |= event;

	return OS_OK;
}

T_ERROR wow_sche_task_evt_disable(unsigned int task, unsigned int event)
{
	if( (task >= NUM_OF_MAXIMUM_TASK) || (task >= NUM_OF_TASK) )
		return OS_PARAM_ERROR;
	if( task_list[task].func_event == NULL )
		return OS_PARAM_ERROR;

	task_list[task].bit_event &= ~event;
	if(task_list[task].bit_event == 0)
		int_task_evt &= ~(0x01 << running_executed_task);

	return OS_OK;
}

T_ERROR wow_sche_task_sleep(unsigned int sleep_ms)
{
	unsigned int cur_clock_ms = wow_clock_get_cur_time( );

	task_list[running_executed_task].time_wakeup = cur_clock_ms+sleep_ms;

	// enable sleep bit of current task
	int_task_sleep |= (0x01 << running_executed_task);
	// disable event bit of current task
	int_task_evt &= ~(0x01 << running_executed_task);

	return OS_OK;
}

void wow_sche_task_wakeup_check(void)
{
	char check_task_wakeup = 0;
	unsigned int cur_clock_ms = wow_clock_get_cur_time( );

	while(check_task_wakeup < NUM_OF_TASK){
		if((int_task_sleep >> check_task_wakeup) & 0x01){
			if(task_list[check_task_wakeup].time_wakeup == cur_clock_ms){
				int_task_sleep &= ~(0x01 << check_task_wakeup);
				int_task_evt |= (0x01 << running_executed_task);
			}
		}
		check_task_wakeup++;
	}
}
