/*
 * main.c
 *
 *  Created on: 2018. 1. 25.
 *      Author: eclipse
 */

#include "hal/common.h"
#include "hal/hal_mcu.h"
#include "rf/basic_rf.h"
#include "sys/log.h"
#include "os/wow_os.h"

// IF YOU WANT TO ADD ISR FUNCTION INTO RST FILE, A PROTOTYPE OF ISR FUNCTION MUST BE PRESENT IN THE MAIN SOURCE FILE
// YOU CAN SEE BELOW EXAMPLE HOW TO USE
#include "hal/uart0.h"
#include "hal/timer3.h"

extern void sys_usrmain(void);

//XXX Temp variable for RF test
basicRfCfg_t rfValue;

int main()
{
	/* Set up System setting(clock) for runnning CC2530 */
	halMcuInit();

	/* Set up uart0 for printing log message */
	{
		uart0_init();
		sys_setting.enable_log = 1;
	}
	/* Set up RF for IEEE 802.15.4 */
	{
		basicRfInit(&rfValue);
		sys_setting.enable_rf = 1;
	}

	/* Set up wow os */
	{
		// Set up kernel clock
		wow_clock_init( );
		// Set up task
		wow_sche_task_init( );
		// start kernel clock
		wow_clock_start( );
	}

	/* Start User programs */
	sys_usrmain();

	return 0;
}
