/*
 * timer2.h
 *
 *  Created on: 2018. 8. 15.
 *      Author: eclipse
 */

#ifndef HAL_TIMER3_H_
#define HAL_TIMER3_H_

#include <cc2530.h>

void timer3_isr(void) __interrupt(T3_VECTOR);

#endif /* HAL_TIMER3_H_ */
