/**
 *  @file  : task_handler.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 14 gen 2021
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* tasks include */
#include "task_handler.h"
#include "keys_handler.h"

#define TOTAL_TASK 	(1u)

static TaskHandle_t * taskArray[TOTAL_TASK];

/**
 * @brief Simply creates all the tasks
 * @return
 */
uint8_t uiTaskhandler_CreateAllTasks(void)
{
	uint8_t retVal = 0;

	xTaskCreate( vKeysHandlerTask,	/* function*/
			"Key Task", 	/* name */
			1000, 			/* stack size */
			NULL, 			/* param */
			3, 				/* prio */
			taskArray[0] );			/* handler */

	return retVal;
}
