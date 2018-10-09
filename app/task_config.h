#ifndef	_TASK_CONFIG_H
#define	_TASK_CONFIG_H

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define LED_QUEUE_LENGTH	5
#define BN_QUEUE_LENGTH		2
#define BNIF_QUEUE_LENGTH	2
#define ETH_APP_QUEUE_LENGTH	5

#define	LED_TASK_PRIORITY			tskIDLE_PRIORITY+3
#define	MBMASTER_POLL_TASK_PRIORITY	tskIDLE_PRIORITY+2
#define	MBMASTER_ACYC_TASK_PRIORITY	tskIDLE_PRIORITY+2
#define	BACNET_TASK_PRIORITY		tskIDLE_PRIORITY+2
#define	ETH_APP_TASK_PRIORITY			tskIDLE_PRIORITY+2






#endif
