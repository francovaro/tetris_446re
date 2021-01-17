/**
 *  @file  : log_event.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 16 gen 2021
 */

#include <string.h>
#include <stdio.h>
#include "lib_uart.h"

#include "log_event.h"

/**
 *
 * @param message
 * @param nrByte
 * @param task_id
 */
void Log_message(char* message, uint16_t nrByte, t_task task_id)
{
    UART_lib_sendData(message, strlen(message));
}
