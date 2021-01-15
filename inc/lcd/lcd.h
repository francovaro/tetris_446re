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

extern void ST7735_write(uint8_t data);

extern uint16_t RGB565(uint8_t R,uint8_t G,uint8_t B);

extern void ST7735_Init(void);
extern void ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE);
extern void ST7735_Clear(uint16_t color);

extern void ST7735_HLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color);
extern void ST7735_VLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color);
extern void ST7735_Line(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color);
extern void ST7735_Rect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
extern void ST7735_FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);

extern void ST7735_PutChar5x7(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color);
extern void ST7735_PutStr5x7(uint8_t X, uint8_t Y, char *str, uint16_t color);

extern void Lcd_write_reg(uint8_t reg, uint8_t data);
extern void Lcd_reset(void);

extern void ST7735_cmd(uint8_t cmd);
extern void ST7735_data(uint8_t cmd);

#endif /* LCD_H_ */
