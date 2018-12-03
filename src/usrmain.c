/*
 * usrmain.c
 *
 *  Created on: 2018. 5. 13.
 *      Author: eclipse
 */

#include "../hal/common.h"
#include "hal/uart0.h"
#include "hal/hal_mcu.h"
#include "sys/log.h"

#include "os/wow_os.h"

#include "task/task_common.h"
#include "task/task_rf.h"
#include "task/task_hal.h"
#include "task/task_rf_mac.h"

void sys_usrmain( )
{
	/*
	 * This function is main for general user
	 */

	log_message("Start User Function!!!\r\n", 24);

	// Initialize HAL task
	{
		task_hal_init( );
		wow_sche_task_evt_enable(PRIORITY_TASK_HAL, EVENT_HAL_INIT);
	}

	// Initialize RF task
	{
//		task_rf_init( );
//		wow_sche_task_evt_enable(PRIORITY_TASK_RF, EVENT_RF_INIT);
	}

	// Initialize IEEE 802.15.4 stack Task
	{
		//zb_init()->zb_sched_init();
		wow_sche_task_evt_enable(PRIORITY_TASK_RF_MAC, EVENT_RF_MAC_INIT);
	}
}
