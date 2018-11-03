/*
 * rf_isr.c
 *
 *  Created on: 2018. 11. 4.
 *      Author: eclipse
 */


/*
 * uart_isr.c
 *
 *  Created on: 2018. 5. 13.
 *      Author: eclipse
 */

#include "hal/common.h"
#include "rf/hal_rf.h"
#include "hal/int/hal_int.h"


#ifndef MRFI
/************************************************************************************
* @fn          rfIsr
*
* @brief       Interrupt service routine that handles RFPKTDONE interrupt.
*
* @param       none
*
* @return      none
*/
void rf_isr(void) __interrupt(RF_VECTOR) __using(2)
{
    uint8_t x;

    HAL_INT_LOCK(x);

    if( RFIRQF0 & IRQ_RXPKTDONE )
    {
        if(pfISR){
            (*pfISR)();                 // Execute the custom ISR
        }
        S1CON= 0;                   // Clear general RF interrupt flag
        RFIRQF0&= ~IRQ_RXPKTDONE;   // Clear RXPKTDONE interrupt
    }
    HAL_INT_UNLOCK(x);
}
#endif
