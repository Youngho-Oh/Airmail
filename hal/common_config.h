/*
 * common_config.h
 *
 *  Created on: 2018. 5. 15.
 *      Author: eclipse
 */

#ifndef HAL_COMMON_CONFIG_H_
#define HAL_COMMON_CONFIG_H_

// Definition for System
/* You must add "--xstack" in sdcc compile option */
#define SYS_XSTACK_SUPPROT		1


// Definition for UART0
#define UART0_CONF_ENABLE		1
#define LOG_CONF_ENABLED		1
#define UART0_CONF_WITH_INPUT	1

// Definition for RF
//#define SECURITY_CCM

#endif /* HAL_COMMON_CONFIG_H_ */
