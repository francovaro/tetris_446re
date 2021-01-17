/**
 *  @file  : log_event.h
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 16 gen 2021
 */

#ifndef INC_LOG_EVENT_H_
#define INC_LOG_EVENT_H_

typedef enum
{
    e_task_keys_handler,
    e_task_game_engine,
    e_task_none
}t_task;

extern void Log_message(char* message, uint16_t nrByte, t_task task_id);

#endif /* INC_LOG_EVENT_H_ */
