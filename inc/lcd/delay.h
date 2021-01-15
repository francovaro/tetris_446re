/*
 *  @file  : delay.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 11 nov 2020
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include <stdint.h>

extern void Delay_init(void);
extern void Delay_ms(uint16_t delay);
extern void Delay_us(uint16_t delay);


#endif /* INC_DELAY_H_ */
