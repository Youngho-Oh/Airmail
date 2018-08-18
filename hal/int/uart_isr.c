/*
 * uart_isr.c
 *
 *  Created on: 2018. 5. 13.
 *      Author: eclipse
 */

#include "../common.h"
#include "hal/uart0.h"
#include "hal/int/hal_int.h"

#if (SYS_XSTACK_SUPPROT == 1)
void uart0_rx_isr(void) __interrupt(URX0_VECTOR) __using(2)
#else
void uart0_rx_isr(void) __interrupt(URX0_VECTOR) __using(1)
#endif
{
	//WOW TODO
    unsigned char x;

    HAL_INT_LOCK(x);

//    if( RFIRQF0 & IRQ_RXPKTDONE )
//    {
//        if(pfISR){
//            (*pfISR)();                 // Execute the custom ISR
//        }
//        S1CON= 0;                   // Clear general RF interrupt flag
//        RFIRQF0&= ~IRQ_RXPKTDONE;   // Clear RXPKTDONE interrupt
//    }
    HAL_INT_UNLOCK(x);
}
