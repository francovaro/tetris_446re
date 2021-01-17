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

extern const s_base_piece_prop pieces[];

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

/**
 * @brief print a string at x y
 *
 * @param string
 * @param n_byte
 * @param x
 * @param y
 */
void Lcd_print_string(const char* string, uint16_t n_byte, uint8_t x, uint8_t y)
{
#ifdef ST7735

#endif
}

/**
 *
 * @param x
 * @param y
 */
void Lcd_print_piece(s_piece* piece_to_display, uint8_t x, uint8_t y)
{
#ifdef ST7735

    switch(piece_to_display->_base_prop->_type)
    {
        case e_piece_I:
        {
            (void)pieces[e_piece_I];    // no warning :p
        }
        break;
        case e_piece_J:
        {
            // ...
        }
        break;
    }

#endif
}
