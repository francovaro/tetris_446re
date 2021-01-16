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
#include "lcd\st7735_cmd.h"

/* Screen resolution */
#define LCD_SCREEN_W         128
#define LCD_SCREEN_H         128

extern uint16_t Lcd_Get_RGB565(uint8_t R,uint8_t G,uint8_t B);
extern void Lcd_reset(void);

#endif /* LCD_H_ */
