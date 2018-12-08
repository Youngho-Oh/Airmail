/*
 * task_rf.c
 *
 *  Created on: 2018. 8. 18.
 *      Author: eclipse
 */

#include <stdio.h>

#include "rf/rf_config.h"
#include "rf/basic_rf.h"
#include "rf/hal_rf_util.h"
#include "rf/hal_rf.h"
#include "rf/zb/hdr/zb_zdo.h"

#include "task_rf.h"

#include "lib/queue.h"

#include "hal/bool.h"
#include "sys/log.h"

#define RF_QUEUE_TX_BUF_SIZE	100
#define RF_QUEUE_RX_BUF_SIZE	100

sche_task task_rf = {0, 0, NULL};

// Variable for RF test
basicRfCfg_t rfValue;
uint16_t g_deviceAddr;
uint8_t g_txPower;

static app_Packet_t txPacket;
static app_Packet_t rxPacket;

uint8_t txPacket_databuf[RF_QUEUE_TX_BUF_SIZE] = {0,};
uint8_t rxPacket_databuf[RF_QUEUE_RX_BUF_SIZE] = {0,};

//TODO temporary value
uint8_t temp_data[RF_QUEUE_TX_BUF_SIZE] = {0,};

unsigned short des_addr = 0;
unsigned char data_buf[255] = {0,};

static T_ERROR task_rf_event_function(unsigned char cur_task_event);
static T_ERROR _task_rf_event_init(void);
static T_ERROR _task_rf_event_law_send(uint8_t * sendbuf, uint16_t buf_size);

static void _rf_init_default(basicRfCfg_t * rfconfig);
static void _rf_init_power(void);


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
		Queue_Initialize(&txPacket, &rxPacket, txPacket_databuf, rxPacket_databuf, RF_QUEUE_TX_BUF_SIZE, RF_QUEUE_RX_BUF_SIZE);
		break;
	case EVENT_RF_LAW_SEND :
		//TODO
		_task_rf_event_law_send(temp_data, 0);
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
		_rf_init_default(&rfValue);
		val_return = basicRfInit(&rfValue);

		if( val_return == SUCCESS ){
			log_message("Success to init RF\r\n",20);
			sys_setting.enable_rf = 1;
			//TODO
//		    _rf_init_power();
//		    halSetRxNormalMode();
//		    basicRfReceiveOn();

			wow_sche_task_evt_enable(wow_sche_task_now_running(), EVENT_RF_LAW_SEND);
		}
		else
		{
			log_message("Fail to init RF\r\n",17);
			sys_setting.enable_rf = 0;
			wow_sche_task_evt_timer_enable(PRIORITY_TASK_RF, EVENT_RF_INIT, 100);
		}
	}

	return OS_OK;
}

static T_ERROR _task_rf_event_law_send(uint8_t * sendbuf, uint16_t buf_size)
{
	log_message("RF law data send\r\n",18);

//	if( (sendbuf == NULL) || (buf_size == 0) )
//		return OS_PARAM_ERROR;

//    basicRfSendPacket(g_deviceAddr, (uint8_t *)sendbuf, buf_size + 1);

	wow_sche_task_evt_timer_enable(wow_sche_task_now_running(), EVENT_RF_LAW_SEND, 5000);

	return OS_OK;
}


void _rf_init_default(basicRfCfg_t * rfconfig)
{
    // Config basicRF
	rfconfig->panId = PAN_ID;
	rfconfig->ackRequest = false;

    // Set channel
	rfconfig->channel = APP_DEFAULT_CHANNEL;

    // Initialize BasicRF
#ifdef COORDINATOR
	rfconfig->myAddr = SERVER_ADDR;
    g_deviceAddr           = DEVICE_ADDR;
#else
    rfconfig->myAddr = DEVICE_ADDR;
    g_deviceAddr           = SERVER_ADDR;
#endif

#if INCLUDE_PA==2591 || INCLUDE_PA==2592
//    g_txPower = HAL_RF_TXPOWER_0_DBM;
//    g_txPower = HAL_RF_TXPOWER_13_DBM;
//    g_txPower = HAL_RF_TXPOWER_16_DBM;
//    g_txPower = HAL_RF_TXPOWER_18_DBM;
    g_txPower = HAL_RF_TXPOWER_20_DBM;
#else
//    g_txPower = HAL_RF_TXPOWER_MIN_3_DBM;
//    g_txPower = HAL_RF_TXPOWER_0_DBM;
    g_txPower = HAL_RF_TXPOWER_4_DBM;
#endif
}

void _rf_init_power(void)
{
    int txTmpPower = g_txPower;

    halRfSetTxPower(txTmpPower);

#ifdef INCLUDE_PA
    // Select gain (for modules with CC2590/91 only)
    halRfSetGain(HAL_RF_GAIN_HIGH);
//    halRfSetGain(HAL_RF_GAIN_LOW);
#endif
}

void zb_zdo_startup_complete(zb_uint8_t param)
{
	//TODO

	return;
}
