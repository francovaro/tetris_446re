/**
 *  @file  : hardware.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 15 gen 2021
 */
#include "hardware.h"
#include "keys_handler.h"
#include "spi.h"
#include "lib_uart.h"
#include "lcd\delay.h"
#include "lcd\lcd.h"

/**
 * @brief Call the init for all the different peripheral handled.
 */
void Hardware_Init(void)
{
    Keys_HW_Init();
    SPI_Config();
    UART_lib_config(e_UART_2, DISABLE, 0, 0);

    delay_init();
    Lcd_Init();
}
