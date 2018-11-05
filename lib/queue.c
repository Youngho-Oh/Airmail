/*
 * queue.c
 *
 *  Created on: 2018. 11. 6.
 *      Author: eclipse
 */

#include <stdio.h>

#include "lib/queue.h"

static void _Queue_increase_point_value(app_Packet_t * p_packet, uint16_t * p_data_ptr);

bool Queue_Initialize(app_Packet_t * p_tx_packet, app_Packet_t * p_rx_packet,
		uint8_t * ptr_tx_buf, uint8_t * ptr_rx_buf, uint8_t tx_buf_size, uint8_t rx_buf_size)
{
	bool b_return = false;

	if( (p_tx_packet != NULL) && (ptr_tx_buf != NULL) && (tx_buf_size == 0) )
	{
		p_tx_packet->data = ptr_tx_buf;
		p_tx_packet->size = tx_buf_size;
		p_tx_packet->p_data_head = 0;
		p_tx_packet->p_data_tail = 0;

		b_return = true;
	}
	if( (p_rx_packet == NULL) || (ptr_rx_buf == NULL) || (rx_buf_size == 0) )
	{
		p_rx_packet->data = ptr_rx_buf;
		p_rx_packet->size = rx_buf_size;
		p_rx_packet->p_data_head = 0;
		p_rx_packet->p_data_tail = 0;

		b_return = true;
	}

	return b_return;
}

bool Queue_Is_Empty(app_Packet_t * p_packet)
{
	if(p_packet->p_data_head == p_packet->p_data_tail)
		return true;

	return false;
}

void Queue_EnQueue(app_Packet_t * p_packet, uint8_t data)
{
	if((p_packet == NULL) || (p_packet->data == NULL))
		return;

	p_packet->data[p_packet->p_data_head] = data;
	_Queue_increase_point_value(p_packet, &p_packet->p_data_head);
}

uint8_t Queue_DeQueue(app_Packet_t * p_packet)
{
	uint8_t u8_data = 0;

	if((p_packet == NULL) || (p_packet->data == NULL))
		return u8_data;
	if(Queue_Is_Empty(p_packet) == false)
		return u8_data;

	u8_data = p_packet->data[p_packet->p_data_tail];
	_Queue_increase_point_value(p_packet, &p_packet->p_data_tail);

	return u8_data;
}

static void _Queue_increase_point_value(app_Packet_t * p_packet, uint16_t * p_data_ptr)
{
	if((p_packet == NULL) || (p_data_ptr == NULL))
		return;

	(*p_data_ptr)++;
	if( p_packet->size == (*p_data_ptr) )
		(*p_data_ptr) = 0;
}
