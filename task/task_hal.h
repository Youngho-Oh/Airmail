/*
 * task_hal.h
 *
 *  Created on: 2018. 8. 24.
 *      Author: eclipse
 */

#ifndef TASK_TASK_HAL_H_
#define TASK_TASK_HAL_H_

#include "os/wow_os.h"

#include "task/task_common.h"
#include "hal/common.h"

void task_hal_init(void);
//unsigned char task_rf_event_function(unsigned char cur_task_event);

// Defined RF task event
#define EVENT_HAL_INIT	0

extern sche_task task_hal;

#endif /* TASK_TASK_HAL_H_ */
