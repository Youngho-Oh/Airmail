/*
 * clock.c
 *
 *  Created on: 2018. 9. 15.
 *      Author: eclipse
 */
#include "sys/clock.h"

/**
 * A second, measured in system clock time.
 *
 * \hideinitializer
 */
#ifdef CLOCK_CONF_SECOND
#define CLOCK_SECOND CLOCK_CONF_SECOND
#else
#define CLOCK_SECOND (clock_time_t)32
#endif

/**
 * Initialize the clock library.
 *
 * This function initializes the clock library and should be called
 * from the main() function of the system.
 *
 */
void clock_init(void)
{
	wow_clock_init( );
}

/**
 * Get the current clock time.
 *
 * This function returns the current system clock time.
 *
 * \return The current clock time, measured in system ticks.
 */
CCIF clock_time_t clock_time(void)
{
	return (clock_time_t)wow_clock_get_cur_time( );
}

/**
 * Get the current value of the platform seconds.
 *
 * This could be the number of seconds since startup, or
 * since a standard epoch.
 *
 * \return The value.
 */
CCIF unsigned long clock_seconds(void)
{
	return (unsigned long)(wow_clock_get_cur_time()/1000);
}

/**
 * Set the value of the platform seconds.
 * \param sec   The value to set.
 *
 */
void clock_set_seconds(unsigned long sec)
{
	//TODO
}

/**
 * Wait for a given number of ticks.
 * \param t   How many ticks.
 *
 */
void clock_wait(clock_time_t t)
{
	//TODO
}

/**
 * Delay a given number of microseconds.
 * \param dt   How many microseconds to delay.
 *
 * \note Interrupts could increase the delay by a variable amount.
 */
void clock_delay_usec(unsigned short dt)
{
	//TODO
}

/**
 * Deprecated platform-specific routines.
 *
 */
int clock_fine_max(void)
{
	return 0xffffffff;
}

unsigned short clock_fine(void)
{
	return 0;
}

void clock_delay(unsigned int delay)
{
	//TODO
}

