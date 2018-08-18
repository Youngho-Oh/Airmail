/*
 * usrmain.c
 *
 *  Created on: 2018. 5. 13.
 *      Author: eclipse
 */

#include "../hal/common.h"
#include "hal/uart0.h"
#include "hal/hal_mcu.h"
#include "sys/log.h"

unsigned char XXX;
char msg_sample[13] = {'H','e','l','l','o',' ','w','o','r','l','d','\r','\n'};
char done_sample[13] = {'F','u','c','k','i','n','g','!','!','!','!','\r','\n'};

extern unsigned char test;

void sys_usrmain( )
{
	/*
	 * This function is main for general user
	 */

	XXX = 0x50;

	//TODO
	while(1){
		//WOW XXX UART testcode
		if(test == 0)
			log_message(msg_sample, 15);
		else
			log_message(done_sample, 15);
		halMcuWaitMs(1000);
	}

	//TODO : create scheduler function
}
