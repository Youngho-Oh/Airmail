/*
 * uart_isr.c
 *
 *  Created on: 2018. 5. 13.
 *      Author: eclipse
 */

#include "../common.h"
#include "hal/timer3.h"
#include "hal/int/hal_int.h"

#include "os/kernel_clock.h"
#include "os/sche.h"

#define IRCON_T3IF				0x08

#define TIMIF_T3OVFIF			0x01

unsigned int a = 0;
unsigned char test = 0;

void timer3_isr(void) __interrupt(T3_VECTOR) __using(2)
{
    unsigned char x;
    unsigned char timif_reg = TIMIF;

    HAL_INT_LOCK(x);

    // increase system clock
	wow_clock_tick_increment();
	// check wake-up task
	wow_sche_task_wakeup_check();

    HAL_INT_UNLOCK(x);
}
