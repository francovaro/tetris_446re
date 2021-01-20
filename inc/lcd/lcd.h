/**
 *  @file  : lcd.h
 *	
 *  @brief
 *
 *  @author: Francesco Varani
 *  @date  : 25 nov 2019
 */

#ifndef LCD_H_
#define LCD_H_

/* Includes ------------------------------------------------------------------*/
#include "game\tetris_handler.h"

/* LCD definition. Uncomment the one in use */
#define ST7735
//#define LCD_NO_SE_QUE

/* Screen resolution */
#ifdef ST7735
#define LCD_SCREEN_W         (128u)
#define LCD_SCREEN_H         (128u)
#endif

extern void Lcd_Init(void);
extern void Lcd_clear_screen(uint16_t color);
extern void Lcd_print_string(const char* string, uint16_t n_byte, uint8_t x, uint8_t y);
extern void Lcd_print_piece(s_piece* piece, uint8_t x, uint8_t y);

#endif /* LCD_H_ */
