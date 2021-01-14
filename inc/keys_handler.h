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

typedef struct
{
	uint32_t 			pin;
	uint32_t			intLine;
	GPIO_TypeDef*		port;
	eKeyboard_key 		key;
	void (*func) (void);
}t_keyboard;

void Keyboard_Init(void);

#endif /* INC_KEYS_HANDLER_H_ */
