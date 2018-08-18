/*
 * config.c
 *
 *  Created on: 2018. 5. 5.
 *      Author: eclipse
 */

#include <stdlib.h>
#include <string.h>

#include <cc2530.h>

#include "hal/common.h"

#if (SYS_XSTACK_SUPPROT == 1)

/* register bank1 is used by external stack pointer */
// External RAM Memory Stack pointer (2bytes) : bank1_r1(high byte) / bank1_r0(low byte)
__data __at (0x08) unsigned char uc_bank1_r0 = 0;
__data __at (0x09) unsigned char uc_bank1_r1 = 0;
__data __at (0x0a) unsigned char uc_bank1_r2 = 0;
__data __at (0x0b) unsigned char uc_bank1_r3 = 0;
__data __at (0x0c) unsigned char uc_bank1_r4 = 0;
__data __at (0x0d) unsigned char uc_bank1_r5 = 0;
__data __at (0x0e) unsigned char uc_bank1_r6 = 0;
__data __at (0x0f) unsigned char uc_bank1_r7 = 0;

/* regitser bank2 is used by interrupt register */

#endif

struct conf_status sys_setting = {0};
