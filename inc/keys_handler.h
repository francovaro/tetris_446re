/**
 *  @file  : keys_handler.h
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 14 gen 2021
 */

#ifndef INC_KEYS_HANDLER_H_
#define INC_KEYS_HANDLER_H_

typedef enum
{
	eKey_UP,
	eKey_DOWN,
	eKey_LEFT,
	eKey_RIGHT,
	eKey_OK,
	eKey_CANCEL,
	eKey_LAST,
} eKeyboard_key;

extern void Keys_HW_Init(void);
extern void vKeysHandlerTask(void* pvParameters);

#endif /* INC_KEYS_HANDLER_H_ */
