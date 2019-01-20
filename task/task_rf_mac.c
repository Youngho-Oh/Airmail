/*
 * task_rf_mac.c
 *
 *  Created on: 2018. 11. 11.
 *      Author: eclipse
 */

#include "os/wow_os.h"

#include "task/task_common.h"
#include "task/task_rf_mac.h"

#include "rf/zb/hdr/zb_common.h"
#include "rf/zb/hdr/zb_mac.h"

#include "sys/log.h"

sche_task task_rf_mac = {0, 0, NULL};

static T_ERROR task_rf_mac_event_function(unsigned char cur_task_event);

void zb_sched_init()
{
	task_rf_mac.bit_event = 0;
	task_rf_mac.time_wakeup = 0;
	task_rf_mac.func_event = task_rf_mac_event_function;

	wow_sche_task_add(&task_rf_mac, PRIORITY_TASK_RF_MAC, true);
}

T_ERROR task_rf_mac_event_function(unsigned char cur_task_event)
{
	T_ERROR value_task_return = OS_OK;

	switch(cur_task_event){
	case EVENT_RF_MAC_INIT :
		log_message("Init RF MAC task init!!!\r\n", 26);
		ZB_AIB().aps_designated_coordinator = 1;
		if(zdo_dev_start() != RET_OK){
			log_message("Fail to init zdo_dev_start function!!!\r\n", 40);
		}
		else{
			//TODO
		}
		break;
	case EVENT_RF_MAC_BEACON :
		log_message("Send Beacon packet!!!\r\n", 23);
//		zb_mlme_command_accept(zb_uint8_t param);
		wow_sche_task_evt_timer_enable(wow_sche_task_now_running(), EVENT_RF_MAC_BEACON, 5000);
		break;
	default :
		log_message("Undefined event!!!\r\n", 20);
		value_task_return = OS_PARAM_ERROR;
		break;
	}

	return value_task_return;
}


void zb_zdo_startup_complete(zb_uint8_t param)
{
	log_message("Complete to init zigbee stack!!!\r\n", 34);
	wow_sche_task_evt_enable(PRIORITY_TASK_RF_MAC, EVENT_RF_MAC_BEACON);

	return;
}
