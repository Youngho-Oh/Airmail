/*
 * kernel_clock.c
 *
 *  Created on: 2018. 8. 8.
 *      Author: eclipse
 */

#include "kernel_clock.h"

#include "sys/log.h"

// IMPORTANT : YOU MUST BE MAKE THIS FUNCTION DEPENDS ON YOUR TARGET CPU.
extern T_ERROR _wow_clock_init(void);
extern T_ERROR _wow_clock_start(void);
extern T_ERROR _wow_clock_stop(void);

unsigned int int_time_ms = 0;

T_ERROR wow_clock_init(void)
{
	int_time_ms = 0;

	return _wow_clock_init();
}

T_ERROR wow_clock_start(void)
{
	return _wow_clock_start();
}

T_ERROR wow_clock_stop(void)
{
	return _wow_clock_stop();
}

unsigned int wow_clock_get_cur_time(void)
{
	return int_time_ms;
}

void wow_clock_tick_increment(void)
{
	int_time_ms++;
}
