/*
 * task_rf.c
 *
 *  Created on: 2018. 8. 18.
 *      Author: eclipse
 */

#include <stdio.h>

#include "rf/rf_config.h"
#include "rf/basic_rf.h"
#include "rf/net/netstack.h"

#include "task_rf.h"

#include "sys/log.h"

sche_task task_rf = {0, 0, NULL};

// RF driver
const struct radio_driver cc2530_rf_driver = {0,};
const struct mac_driver csma_driver = {0,};
const struct network_driver rime_driver = {0,};
const struct rdc_driver nullrdc_driver = {0,};

// Variable for RF test
basicRfCfg_t rfValue;

unsigned short des_addr = 0;
unsigned char data_buf[255] = {0,};

static T_ERROR task_rf_event_function(unsigned char cur_task_event);
static T_ERROR _task_rf_event_init(void);
static T_ERROR _task_rf_event_law_send(void);


void task_rf_init(void)
{
	task_rf.bit_event = 0;
	task_rf.time_wakeup = 0;
	task_rf.func_event = task_rf_event_function;

	wow_sche_task_add(&task_rf, PRIORITY_TASK_RF, true);
}

T_ERROR task_rf_event_function(unsigned char cur_task_event)
{
	T_ERROR value_task_return = OS_OK;

	switch(cur_task_event){
	case EVENT_RF_INIT :
		_task_rf_event_init( );
		break;
	case EVENT_RF_LAW_SEND :
		_task_rf_event_law_send( );
		break;
	default :
		log_message("Undefined event!!!\r\n", 20);
		value_task_return = OS_PARAM_ERROR;
		break;
	}

	return value_task_return;
}

T_ERROR _task_rf_event_init(void)
{
	unsigned char val_return = SUCCESS;

	log_message("Init RF task init!!!\r\n", 22);

	/* Set up RF for IEEE 802.15.4 */
	{
		val_return = basicRfInit(&rfValue);
		if( val_return == SUCCESS ){
			log_message("Success to init RF\r\n",20);
			sys_setting.enable_rf = 1;
			//TODO
			wow_sche_task_evt_enable(wow_sche_task_now_running(), EVENT_RF_LAW_SEND);
		}
		else
		{
			log_message("Fail to init RF\r\n",17);
			sys_setting.enable_rf = 0;
		}
	}

	return OS_OK;
}

static T_ERROR _task_rf_event_law_send(void)
{
	log_message("RF law data send\r\n",18);

	//TODO : send test
	basicRfSendPacket(des_addr, data_buf, 8);

	wow_sche_task_evt_timer_enable(wow_sche_task_now_running(), EVENT_RF_LAW_SEND, 1000);

	return OS_OK;
}
