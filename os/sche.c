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

sche_task * task_list[NUM_OF_TASK] = {NULL, NULL, NULL};

// BIT WISED
unsigned int int_task_evt = 0;
unsigned int int_task_sleep = 0;

unsigned int running_executed_task = 0;

static unsigned char _wow_sche_curtask_event_check(sche_task * taget_task);

T_ERROR wow_sche_task_init( )
{
	int_task_evt = 0;
	int_task_sleep = 0;
	running_executed_task = 0;

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

	if(task_list[priority] == NULL)
		task_list[priority] = add_task_info;
	else if( (is_forced == true) && (running_executed_task != priority) )	// task_list[priority].func_event != NULL && is_forced == true
		task_list[priority] = add_task_info;
	else	// task_list[priority].func_event != NULL && is_forced == false
		return OS_PARAM_ERROR;

	return OS_OK;
}

void wow_sche_task_run( )
{
	unsigned char ptr_task_evt = 0;
	bool is_task_enable = false;
	unsigned char task_evt_state = 0;

	while(1){
		is_task_enable = (int_task_evt >> ptr_task_evt)&0x01;

		if( (is_task_enable == true) && (task_list[ptr_task_evt] != NULL) && (task_list[ptr_task_evt]->func_event != NULL) ){
			task_evt_state = _wow_sche_curtask_event_check(task_list[ptr_task_evt]);
			wow_sche_task_evt_disable(ptr_task_evt, task_evt_state);
			running_executed_task = ptr_task_evt;
			task_list[ptr_task_evt]->func_event(task_evt_state);
		}

		if( ++ptr_task_evt == NUM_OF_TASK )
			ptr_task_evt = 0;
	}
}

T_ERROR wow_sche_task_evt_enable(unsigned int task, unsigned char event)
{
	if( (task >= NUM_OF_MAXIMUM_TASK) || (task >= NUM_OF_TASK) )
		return OS_PARAM_ERROR;
	if( (task_list[task] == NULL) || (task_list[task]->func_event == NULL) )
		return OS_PARAM_ERROR;

	int_task_evt |= (0x01 << running_executed_task);
	task_list[task]->bit_event |= (0x01 << event);

	return OS_OK;
}

T_ERROR wow_sche_task_evt_disable(unsigned int task, unsigned char event)
{
	if( (task >= NUM_OF_MAXIMUM_TASK) || (task >= NUM_OF_TASK) )
		return OS_PARAM_ERROR;
	if( (task_list[task] == NULL) || (task_list[task]->func_event == NULL) )
		return OS_PARAM_ERROR;

	task_list[task]->bit_event &= ~(0x01 << event);
	if(task_list[task]->bit_event == 0)
		int_task_evt &= ~(0x01 << running_executed_task);

	return OS_OK;
}

//T_ERROR wow_sche_task_evt_timer_enable(unsigned int task, unsigned char event, unsigned int term);
//T_ERROR wow_sche_task_evt_timer_disable(unsigned int task, unsigned char event);

unsigned char _wow_sche_curtask_event_check(sche_task * taget_task)
{
	unsigned char check_task_event = 0;
	bool is_event_set = false;

	while(check_task_event <= 31){
		is_event_set = ((taget_task->bit_event >> check_task_event) & 0x01);
		if(is_event_set == true)
			break;

		check_task_event++;
	}
	if(check_task_event >= 32)
		check_task_event = 0xff;	// 0xff means no have active event.

	return check_task_event;
}

T_ERROR wow_sche_task_sleep(unsigned int sleep_ms)
{
	unsigned int cur_clock_ms = wow_clock_get_cur_time( );

	task_list[running_executed_task]->time_wakeup = cur_clock_ms+sleep_ms;

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
			if(task_list[check_task_wakeup]->time_wakeup == cur_clock_ms){
				int_task_sleep &= ~(0x01 << check_task_wakeup);
				int_task_evt |= (0x01 << running_executed_task);
				task_list[check_task_wakeup]->time_wakeup = 0;
			}
		}
		check_task_wakeup++;
	}
}
