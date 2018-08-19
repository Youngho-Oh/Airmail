/*
 * task_rf.h
 *
 *  Created on: 2018. 8. 18.
 *      Author: eclipse
 */

#ifndef TASK_TASK_RF_H_
#define TASK_TASK_RF_H_

#include "os/wow_os.h"

#include "task/task_common.h"
#include "hal/common.h"

void task_rf_init(void);
//unsigned char task_rf_event_function(unsigned char cur_task_event);

// Defined RF task event
#define EVENT_RF_INIT		0
#define EVENT_RF_LAW_SEND	1

extern sche_task task_rf;


#endif /* TASK_TASK_RF_H_ */
