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

void sys_usrmain( )
{
	/*
	 * This function is main for general user
	 */

	log_message("Start User Function!!!\r\n", 24);

	//TODO : create scheduler function
	task_rf_init( );
	wow_sche_task_evt_enable(PRIORITY_TASK_RF, EVENT_RF_INIT);
}
