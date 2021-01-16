/*
 *  @file  : lcd.h
 *	
 *  @brief	based on LonelyWolf repository https://github.com/LonelyWolf/stm32/tree/master/ST7735
 *
 *  @author: franc
 *  @date  : 25 nov 2019
 */

#ifndef LCD_H_
#define LCD_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "spi.h"

/* Screen resolution */
#define LCD_SCREEN_W         128
#define LCD_SCREEN_H         128

/* LCD definition. Uncomment the one in use */
#define ST7735

extern void Lcd_Init(void);

#endif /* LCD_H_ */
