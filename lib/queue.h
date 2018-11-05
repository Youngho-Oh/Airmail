/*
 * queue.h
 *
 *  Created on: 2018. 11. 6.
 *      Author: eclipse
 */

#ifndef LIB_QUEUE_H_
#define LIB_QUEUE_H_

#include "rf/rf_config.h"
#include "hal/bool.h"

typedef struct {
    uint8_t size;
    uint8_t * data;
    uint16_t p_data_head;
    uint16_t p_data_tail;
} app_Packet_t;

bool Queue_Initialize(app_Packet_t * p_tx_packet, app_Packet_t * p_rx_packet,
		uint8_t * ptr_tx_buf, uint8_t * ptr_rx_buf, uint8_t tx_buf_size, uint8_t rx_buf_size);

bool Queue_Is_Empty(app_Packet_t * p_packet);

void Queue_EnQueue(app_Packet_t * p_packet, uint8_t data);
uint8_t Queue_DeQueue(app_Packet_t * p_packet);

#endif /* LIB_QUEUE_H_ */
