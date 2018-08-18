/*
 * hal_led.h
 *
 *  Created on: 2018. 4. 22.
 *      Author: eclipse
 */

#ifndef HAL_HAL_LED_H_
#define HAL_HAL_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************
* INCLUDES
*/

/***********************************************************************************
 * CONSTANTS AND DEFINES
 */
typedef enum{
	eLedId_one = 0,
	eLedId_two = 1
} eLedId;

/***********************************************************************************
 * GLOBAL FUNCTIONS
 */

void halLedInit(void);
void halLedOn(eLedId id);
void halLedOff(eLedId id);
void halLedToggle(eLedId id);

#ifdef  __cplusplus
}
#endif

/**********************************************************************************/

#endif /* HAL_HAL_LED_H_ */
