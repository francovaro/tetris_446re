/**
  ******************************************************************************
  * @file    main.c
  * @author  Francesco Varani
  * @version V1.0
  * @date    01-December-2013
  * @brief   A simple Tetris game for STM uC using FreeRTOS
  ******************************************************************************
*/

/**
 * Task:
 * - key handler. Interrupt based using the "integration" to avoid bouncing
 * 		. handles up, down, left.
 * 		. start ? select ?
 * - blocks handler. Time based. Every x ticks we have to move the current block. x will depends on the level. Can also that we need to clear some lines based on the status.
 * 		. it keeps the "matrix" of the "field"
 * - display handler. Time based. We need to refresh the display based on the blocks handler.
 * 		. blocks area will be...
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx.h"

unsigned long ulRunTimeStatsClock;

int main(void)
{

	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1)
	{
		/* we shouldn't arrive at this point :( */
	}


	return 0;
}
