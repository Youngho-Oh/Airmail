/*
 * log.c
 *
 *  Created on: 2018. 5. 5.
 *      Author: eclipse
 */

#include <stdlib.h>
#include <string.h>

#include <cc2530.h>
#include "sys/log.h"
#include "hal/uart0.h"

#if LOG_CONF_ENABLED
void log_message(char *str, unsigned short len)
{
	char * str_ptr = str;

//	if(!sys_setting.enable_log)
//		return;
	if(len == 0)
		return;

	while(len){
		uart0_writeb(*str_ptr);
		len--;
		str_ptr++;
	}
}

#endif /* LOG_CONF_ENABLED */
