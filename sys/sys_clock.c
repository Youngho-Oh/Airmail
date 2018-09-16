/*
 * sys_clock.c
 *
 *  Created on: 2018. 8. 8.
 *      Author: eclipse
 */

#include "hal/hal_clock.h"

#include "os/wow_os.h"

#include "hal/common.h"
#include "sys/log.h"

#define TIMIF_T3OVFIF			0x01

#define IRCON_T3IF				(0x01 << 3)

#define IEN0_EA					(0x01 << 7)

#define IEN1_T3IE				(0x01 << 3)

#define T3CTL_DIV_1				(0x00 << 5)
#define T3CTL_DIV_2				(0x01 << 5)
#define T3CTL_DIV_4				(0x02 << 5)
#define T3CTL_DIV_8				(0x03 << 5)
#define T3CTL_DIV_16			(0x04 << 5)
#define T3CTL_DIV_32			(0x05 << 5)
#define T3CTL_DIV_64			(0x06 << 5)
#define T3CTL_DIV_128			(0x07 << 5)
#define T3CTL_START				(0x01 << 4)
#define T3CTL_OVFIM				(0x01 << 3)
#define T3CTL_CLR				(0x01 << 2)
#define T3CTL_MODE_MODULO		(0x02)
#define T3CTL_MODE_UPANDDOWN	(0x03)

#define T3CCTL0_MODE			(0x01 << 2)
#define T3CCTL0_IM				(0x01 << 6)

T_ERROR _wow_clock_init(void)
{
	// Stop Timer3
	{
		// 0x08 is default value of T3CTL Register
		T3CTL = T3CTL_CLR;
		T3CTL = 0x08;
	}

	// Enable timer3 overflow interrupt
	{
		// Clear interrupt flags ; IRCON.T3IF
		T3IF = 0;
		// Set individual interrupt-enable bit in the pheripherals SFR register
		T3CTL |= T3CTL_OVFIM;
		// Set corresponding individual interrupt-enable bit in the IEN0, IEN1, IEN2 register to 1 ; IEN1.T3IE
		T3IE = 1;
		// Enable global interrupt by setting the EA bit in IEN0 to 1
		EA = 1;
	}

	// Setting for timer3
	{
		T3CCTL0 = (T3CCTL0_MODE | T3CCTL0_IM);
		// DIV : 128 freescale
		T3CTL |= T3CTL_DIV_128;
//		T3CTL |= T3CTL_DIV_32;
		// Set modulo(compare) mode.
		T3CTL |= T3CTL_MODE_MODULO;
		// main clock(32MHz) / Tick DIV(1) = 32MHz / T3_DIV(128) = 250Khz / T3CNT(250) = 1Khz
		T3CC0 = 250;
	}

	return OS_OK;
}

T_ERROR _wow_clock_start(void)
{
	// Start timer3
	T3CTL |= T3CTL_START;

	return OS_OK;
}

T_ERROR _wow_clock_stop(void)
{
	// Stop timer3
	T3CTL &= ~(T3CTL_START);

	return OS_OK;
}
