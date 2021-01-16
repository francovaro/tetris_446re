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
 *
 */
void Lcd_Init(void)
{
#ifdef ST7735
    ST7735_init_with_commands();
#endif
}
