/*
 * task_rf.h
 *
 *  Created on: 2018. 8. 18.
 *      Author: eclipse
 */

#ifndef TASK_TASK_RF_H_
#define TASK_TASK_RF_H_

#include "os/wow_os.h"

#include "task/task_common.h"
#include "hal/common.h"

#include "rf/rf_config.h"
#include "rf/basic_rf.h"

// Channel 11, first channel in band
#define APP_DEFAULT_CHANNEL     11

#define APP_MAX_PAYLOAD_LENGTH       100

// BasicRF definitions
#define PAN_ID                0x2007

#define SERVER_ADDR               0x2520
#define DEVICE_ADDR               0xBEEF

#define RSSI_AVG_WINDOW_SIZE   32  // Window size for RSSI moving average

// Defined RF task event
#define EVENT_RF_INIT		0
#define EVENT_RF_LAW_SEND	1

// PER test packet format
typedef struct {
    uint8_t size;
    uint8_t data[APP_MAX_PAYLOAD_LENGTH];
} app_Packet_t;

extern basicRfCfg_t g_basicRfConfig;
extern uint16_t g_deviceAddr;
extern uint8_t g_txPower;

void task_rf_init(void);
//unsigned char task_rf_event_function(unsigned char cur_task_event);

extern sche_task task_rf;


#endif /* TASK_TASK_RF_H_ */
