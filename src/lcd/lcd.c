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
 * @param R red
 * @param G green
 * @param B blue
 * @return the uin16 rapresentation of the signle R G B color
 */
uint16_t Lcd_Get_RGB565(uint8_t R,uint8_t G,uint8_t B)
{
	return ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
}

/**
 *@brief
 */
void Lcd_reset(void)
{
	RST_H();
	Delay_ms(100);
	RST_L();
	Delay_ms(200);
	RST_H();
	Delay_ms(100);
}
