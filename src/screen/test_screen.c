/*
 *  @file  : test_screen.c
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 30 gen 2021
 */

#include "screen\test_screen.h"
#include "lcd\lcd.h"
#include "lcd/st7735_cmd.h"
#include "lcd\color.h"

static void test_block(void);

void Test_screen(void)
{
    test_block();
}




static void test_block(void)
{
    static uint8_t x0 = 0;
    static uint8_t y0 = 0;

    s_piece pippo;

    pippo._actual_rotation = rotation_0;
    pippo._pos.x = x0;
    pippo._pos.y = y0;
    pippo.id = 0;
    pippo._base_prop = &pieces[e_piece_I];

    Lcd_print_piece(&pippo, 5, 5);
    ST7735_draw_unfilled_rectangle(1, 1, 127 -1, 127-1, COLOR_BROWN);
    ST7735_draw_filled_rectangle(40, 40, 127-40, 127-40, COLOR_BROWN);

}

