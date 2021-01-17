/**
 *  @file  : lcd.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 25 nov 2019
 */

#include <string.h>

#include "lcd\lcd.h"
#include "lcd\delay.h"
#include "lcd\st7735_cmd.h"

/**
 * @brief call Init for the used LCD
 */
void Lcd_Init(void)
{
#ifdef ST7735
    ST7735_init_with_commands();
#endif
}

/**
 * @brief
 */
void Lcd_clear_screen(uint16_t color)
{
#ifdef ST7735
    ST7735_clear(color);
#endif
}
