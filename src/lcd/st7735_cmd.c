/**
 *  @file  : st7735_cmd.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 29 nov 2019
 */

#include <stdint.h>
#include "lcd\st7735_cmd.h"
#include "lcd\lcd.h"
#include "spi.h"
#include "lcd\delay.h"

#define NULL    ((void*)0)

static uint8_t _lcd_screen_w;
static uint8_t _lcd_screen_h;

static tLCD_cmd _lcd_sys_cmd[e_syscmd_max];
static tLCD_cmd _lcd_panel_cmd[e_panelcmd_max];

/*
 * Rate = fosc/(1x2+40) * (LINE+2C+2D)
 */
static uint8_t FRMCTR1_buffer[3] = { 0x01, 0x2C, 0x2D};
/*
 * Rate = fosc/(1x2+40) * (LINE+2C+2D)
 */
static uint8_t FRMCTR2_buffer[3] = { 0x01, 0x2C, 0x2D};
/*
 * Dot inversion mode
 * Line inversion mode
 */
static uint8_t FRMCTR3_buffer[6] = { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};

/*
 * 1
 * 2 -4.6v
 * 3 AUTO mode
 */
static uint8_t PWCTR1_buffer[3] = { 0xA2, 0x02, 0x84};
/*
 * VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
 */
static uint8_t PWCTR2_buffer[1] = { 0xC5};
/*
 *  Opamp current small
 *  Boost frequency
 */
static uint8_t PWCTR3_buffer[2] = { 0x0A, 0x00};
/* */
static uint8_t PWCTR4_buffer[2] = { 0x8A, 0x2A};
/* */
static uint8_t PWCTR5_buffer[2] = { 0x8A, 0xEE};
/*
 *
 */
static uint8_t VMCTR1_buffer[1] = { 0x0E};

/*
 * no inversion
 */
static uint8_t INVCTR_buffer[1] = { 0x07};	/* 0x00 or 0x07 or 0x03*/

/*
 * GAMSET
 * 01
 * 02
 * 04
 * 08
 */
static uint8_t GAMSET_buffer_buffer[1] = { 0x01};

static uint8_t GAMCTRP1_buffer[16] = { 0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 };
static uint8_t GAMCTRN1_buffer[16] = { 0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 };

static uint8_t CASET_buffer_buffer[4] 	= {0x00, 0x00, 0x00, 0x7F};	/* line number 0...127*/
static uint8_t RASET_buffer_buffer[4] 	= {0x00, 0x00, 0x00, 0x7F}; /* line number 0...127*/

/* COLMOD
 * 0x03 12 bit/pixel
 * 0x05 16 bit/pixel
 * 0x06 18 bit/pixel
 * 0x07 No used
 * */
static uint8_t COLMOD_buffer_buffer[1] 	= {0x05};

/*
 *
 */
static uint8_t MAD_CTL_buffer[1] = {0x00};	/* was 0 */

static void ST7735_sys_cmd_init(void);
static void ST7735_panel_cmd_init(void);
static void ST7735_write(uint8_t data);
static void ST7735_cmd(uint8_t cmd);
static void ST7735_data(uint8_t cmd);
static void ST7735_Reset(void);

/**
 * @brief Initializes command array and the LCD.
 * @note SPI should be already initialized !
 */
void ST7735_init_with_commands(void)
{
    //CS_L();
    /* Init command */
    ST7735_sys_cmd_init();
    ST7735_panel_cmd_init();
    /* Reset Sequence START*/
    ST7735_Reset();

    _lcd_screen_w = LCD_SCREEN_W;
    _lcd_screen_h = LCD_SCREEN_H;

    //CS_L();   /* start of transmission */

    ST7735_send_sys_cmd(SYS_CMD_SWRESET);   /* 0x01 */
    Delay_ms(150);

    ST7735_send_sys_cmd(SLPOUT);    /* 0x11 */
    Delay_ms(500);
    /* Reset Sequence END */

    /* Frame Rate */
    ST7735_send_panel_cmd(FRMCTR1); /* 0xB1 */
    ST7735_send_panel_cmd(FRMCTR2); /* 0xB2 */
    ST7735_send_panel_cmd(FRMCTR3); /* 0xB3 */

    ST7735_send_panel_cmd(INVCTR);  /* 0xB4 */      /* dot inversion */

    ST7735_send_panel_cmd(PWCTR1);  /* 0xC0 */
    ST7735_send_panel_cmd(PWCTR2);  /* 0xC1 */
    ST7735_send_panel_cmd(PWCTR3);  /* 0xC2 */
    ST7735_send_panel_cmd(PWCTR4);  /* 0xC3 */
    ST7735_send_panel_cmd(PWCTR5);  /* 0xC4 */

    ST7735_send_sys_cmd(VMCTR1);    /* 0xC5*/

    ST7735_send_sys_cmd(INVOFF);    /* 0x20 */

    ST7735_send_sys_cmd(MADCTL);    /* 0x36*/

    ST7735_send_sys_cmd(COLMOD);    /* 0x3A */

    ST7735_send_panel_cmd(CASET);   /* 0xE0 */
    ST7735_send_panel_cmd(RASET);   /* 0xE1 */
    ST7735_send_panel_cmd(GAMCTRP1);    /* 0xE0 */
    ST7735_send_panel_cmd(GAMCTRN1);    /* 0xE1 */

    ST7735_send_sys_cmd(NORON);     /* */
    Delay_ms(10);

    ST7735_send_sys_cmd(DISPON);    /* */
    Delay_ms(100);

    //CS_H();   /* end of transmission */
}


/**
 *
 * @param sysCmd
 */
void ST7735_send_sys_cmd(tST7735_system_cmd sysCmd)
{
    uint8_t i;
    /*
     * sends cmd
     * check if nrOfbyte != 0
     * if so, sends
    */
    CS_L();
    ST7735_cmd(_lcd_sys_cmd[sysCmd].cmd);
    if (_lcd_sys_cmd[sysCmd].nrOfByte != 0)
    {       
        for( i = 0 ; i < _lcd_sys_cmd[sysCmd].nrOfByte ; i++)
        {
            ST7735_data(_lcd_sys_cmd[sysCmd].data[i]);
        }
    }
    CS_H();
}

/**
 *
 * @param panelCmd
 */
void ST7735_send_panel_cmd(tST7735_panel_cmd panelCmd)
{
    uint8_t i;
    /*
     * sends cmd
     * check if nrOfbyte != 0
     * if so, sends
    */
    CS_L();
    ST7735_cmd(_lcd_panel_cmd[panelCmd].cmd);
    if (_lcd_panel_cmd[panelCmd].nrOfByte != 0)
    {       
        for( i = 0 ; i < _lcd_panel_cmd[panelCmd].nrOfByte ; i++)
        {
            ST7735_data(_lcd_panel_cmd[panelCmd].data[i]);
        }
    }   
    CS_H();
}

/**
 *
 * @param power
 */
void ST7735_turns_display(uint8_t power)
{
	//CS_L();	/* start of transmission */
	if (SET == power)
	{
		ST7735_send_sys_cmd(DISPON);
	}
	else
	{
		ST7735_send_sys_cmd(DISPOFF);
	}
	//CS_H();	/* end of transmission */
}

void ST7735_set_orientation(tLCD_orientation orientation)
{
    CS_L();
	ST7735_cmd(0x36); // Memory data access control:
	switch(orientation)
	{
		case eLCD_orientation_CW:
		{
			_lcd_screen_w  = LCD_SCREEN_H;
			_lcd_screen_h = LCD_SCREEN_W;
			ST7735_data(0xA0); // X-Y Exchange,Y-Mirror
		}
		break;
		case eLCD_orientation_normal_CCW:
		{
			_lcd_screen_w  = LCD_SCREEN_H;
			_lcd_screen_h = LCD_SCREEN_W;
			ST7735_data(0x60); // X-Y Exchange,X-Mirror
		}
		break;
		case eLCD_orientation_normal_180:
		{
			_lcd_screen_w  = LCD_SCREEN_W;
			_lcd_screen_h = LCD_SCREEN_H;
			ST7735_data(0xc0); // X-Mirror,Y-Mirror: Bottom to top; Right to left; RGB
		}
		break;
		default:
		{
			_lcd_screen_w  = LCD_SCREEN_W;
			_lcd_screen_h = LCD_SCREEN_H;
			ST7735_data(0x00); // Normal: Top to Bottom; Left to Right; RGB
		}
		break;
	}
    CS_H();
}

void ST7735_set_windows(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t tempVal = 0;

    if (x0 >= LCD_SCREEN_W)
    {
        x0 = LCD_SCREEN_W - 1;
    }
    if (x1 >= LCD_SCREEN_W)
    {
        x1 = LCD_SCREEN_W - 1;
    }

    if (y0 >= LCD_SCREEN_H)
    {
        y0 = LCD_SCREEN_H - 1;
    }

    if (y1 >= LCD_SCREEN_H)
    {
        y1 = LCD_SCREEN_H - 1;
    }

    if (x0 > x1)
    {
        tempVal = x1;
        x1 = x0;
        x0 = tempVal;
    }

    if (y0 > y1)
    {
        tempVal = y1;
        y1 = y0;
        y0 = tempVal;
    }

    //CASET_buffer_buffer[0] = (x0>>8);
    CASET_buffer_buffer[0] = (0x00);
    CASET_buffer_buffer[1] = (x0 & 0xff);
    //CASET_buffer_buffer[2] = (x1>>8);
    CASET_buffer_buffer[2] = (0x00);
    CASET_buffer_buffer[3] = (x1 & 0xff);

    //RASET_buffer_buffer[0] = (y0>>8);
    RASET_buffer_buffer[0] = (0x00);
    RASET_buffer_buffer[1] = (y0 & 0xff);
    //RASET_buffer_buffer[2] = (y1>>8);
    RASET_buffer_buffer[2] = (0x00);
    RASET_buffer_buffer[3] = (y1 & 0xff);

    // CS_L();    
	ST7735_send_sys_cmd(CASET);		/* 0x2A */
	ST7735_send_sys_cmd(RASET);		/* 0x2B */    

	ST7735_send_sys_cmd(RAMWR);		/* 0x2C */

    // CS_H();
}

void ST7735_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    CS_L();
    ST7735_set_windows(x, y, x, y);    
    A0_H();
    ST7735_write(color >> 8);
    ST7735_write((uint8_t)color);
    CS_H();
}

void ST7735_draw_filled_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint8_t i;
    uint8_t j;

    //CS_L();
    ST7735_set_windows(x0, y0, x1, y1);

    A0_H();
    CS_L();

    for (i = x0; i < x1; i++) 
    {
        for (j = y0; j < y1; j++) 
        {
            ST7735_write(color >> 8);
            ST7735_write((uint8_t)color);
        }
    }

    CS_H();
}

void ST7735_draw_unfilled_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	ST7735_draw_v_line(x0, y0, y1, color);
	ST7735_draw_v_line(x1, y0, y1, color);

	ST7735_draw_h_line(x0, x1, y0, color);
	ST7735_draw_h_line(x0, x1, y1, color);
}


void ST7735_draw_h_line(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color)
{
    ST7735_draw_filled_rectangle(x0, y, x1, y, color);
}

void ST7735_draw_v_line(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color)
{
    ST7735_draw_filled_rectangle(x, y0, x, y1, color);
}

void ST7735_clear(uint16_t color)
{
    ST7735_draw_filled_rectangle(0, 0, (LCD_SCREEN_W - 1), (LCD_SCREEN_H - 1), color);
}

/**
 *
 */
static void ST7735_sys_cmd_init(void)
{
    /* Software Reset */
    _lcd_sys_cmd[SYS_CMD_SWRESET].cmd = 0x01;
    _lcd_sys_cmd[SYS_CMD_SWRESET].nrOfByte = 0;
    _lcd_sys_cmd[SYS_CMD_SWRESET].data = NULL;

    /* Sleep ON */
    _lcd_sys_cmd[SLPIN].cmd = 0x10;
    _lcd_sys_cmd[SLPOUT].nrOfByte = 0;
    _lcd_sys_cmd[SLPIN].data = NULL;

    /* Sleep Out & Booster On */
    _lcd_sys_cmd[SLPOUT].cmd = 0x11;
    _lcd_sys_cmd[SLPOUT].nrOfByte = 0;
    _lcd_sys_cmd[SLPOUT].data = NULL;

    /* Memory Data Access Control */
    _lcd_sys_cmd[MADCTL].cmd = 0x36;
    _lcd_sys_cmd[MADCTL].nrOfByte = 1;
    _lcd_sys_cmd[MADCTL].data = MAD_CTL_buffer;

    /* Column Address Set */
    _lcd_sys_cmd[CASET].cmd = 0x2A;
    _lcd_sys_cmd[CASET].nrOfByte = 4;
    _lcd_sys_cmd[CASET].data = CASET_buffer_buffer;

    /* Row Address Set */
    _lcd_sys_cmd[RASET].cmd = 0x2B;
    _lcd_sys_cmd[RASET].nrOfByte = 4;
    _lcd_sys_cmd[RASET].data = RASET_buffer_buffer;

    /* Display ON */
    _lcd_sys_cmd[DISPON].cmd = 0x29;
    _lcd_sys_cmd[DISPON].nrOfByte = 0;
    _lcd_sys_cmd[DISPON].data = NULL;

    /* Display OFF */
    _lcd_sys_cmd[DISPOFF].cmd = 0x28;
    _lcd_sys_cmd[DISPOFF].nrOfByte = 0;
    _lcd_sys_cmd[DISPOFF].data = NULL;

    /* Interface Pixel Format */
    _lcd_sys_cmd[COLMOD].cmd = 0x3A;
    _lcd_sys_cmd[COLMOD].nrOfByte = 1;
    _lcd_sys_cmd[COLMOD].data = COLMOD_buffer_buffer;

    /* Display Inversion Off (Normal) */
    _lcd_sys_cmd[INVOFF].cmd = 0x20;
    _lcd_sys_cmd[INVOFF].nrOfByte = 0;
    _lcd_sys_cmd[INVOFF].data = NULL;


    /* VCOM Control 1 */
    _lcd_sys_cmd[NORON].cmd = 0x13;
    _lcd_sys_cmd[NORON].nrOfByte = 0;
    _lcd_sys_cmd[NORON].data = NULL;

    /* VCOM Control 1 */
    _lcd_sys_cmd[GAMSET].cmd = 0x26;
    _lcd_sys_cmd[GAMSET].nrOfByte = 1;
    _lcd_sys_cmd[GAMSET].data = GAMSET_buffer_buffer;

    /* Memory Write */
    _lcd_sys_cmd[RAMWR].cmd = 0x2C;
    _lcd_sys_cmd[RAMWR].nrOfByte = 0;
    _lcd_sys_cmd[RAMWR].data = NULL;

    /* IDLE MODE OFF */
    _lcd_sys_cmd[IDMOFF].cmd = 0x38;
    _lcd_sys_cmd[IDMOFF].nrOfByte = 0;
    _lcd_sys_cmd[IDMOFF].data = NULL;

    /* IDLE MODE ON */
    _lcd_sys_cmd[IDMON].cmd = 0x39;
    _lcd_sys_cmd[IDMON].nrOfByte = 0;
    _lcd_sys_cmd[IDMON].data = NULL;


}

/**
 *
 */
static void ST7735_panel_cmd_init(void)
{
    /* In Normal Mode (Full Colors) */
    _lcd_panel_cmd[FRMCTR1].cmd = 0xB1;
    _lcd_panel_cmd[FRMCTR1].nrOfByte = 3;
    _lcd_panel_cmd[FRMCTR1].data = FRMCTR1_buffer;

    /* In Idle Mode (8-colors) */
    _lcd_panel_cmd[FRMCTR2].cmd = 0xB2;
    _lcd_panel_cmd[FRMCTR2].nrOfByte = 3;
    _lcd_panel_cmd[FRMCTR2].data = FRMCTR2_buffer;

    /* In Partial Mode + FullColors */
    _lcd_panel_cmd[FRMCTR3].cmd = 0xB3;
    _lcd_panel_cmd[FRMCTR3].nrOfByte = 6;
    _lcd_panel_cmd[FRMCTR3].data = FRMCTR3_buffer;

    /*  Power Control Setting */
    _lcd_panel_cmd[PWCTR1].cmd = 0xC0;
    _lcd_panel_cmd[PWCTR1].nrOfByte = 3;
    _lcd_panel_cmd[PWCTR1].data = PWCTR1_buffer;

    /* Power Control Setting */
    _lcd_panel_cmd[PWCTR2].cmd = 0xC1;
    _lcd_panel_cmd[PWCTR2].nrOfByte = 1;
    _lcd_panel_cmd[PWCTR2].data = PWCTR2_buffer;

    _lcd_panel_cmd[PWCTR3].cmd = 0xC2;
    _lcd_panel_cmd[PWCTR3].nrOfByte = 2;
    _lcd_panel_cmd[PWCTR3].data = PWCTR3_buffer;

    _lcd_panel_cmd[PWCTR4].cmd = 0xC3;
    _lcd_panel_cmd[PWCTR4].nrOfByte = 2;
    _lcd_panel_cmd[PWCTR4].data = PWCTR4_buffer;

    _lcd_panel_cmd[PWCTR5].cmd = 0xC4;
    _lcd_panel_cmd[PWCTR5].nrOfByte = 2;
    _lcd_panel_cmd[PWCTR5].data = PWCTR5_buffer;

    /* VCOM Control 1 */
    _lcd_panel_cmd[VMCTR1].cmd = 0xC5;
    _lcd_panel_cmd[VMCTR1].nrOfByte = 1;
    _lcd_panel_cmd[VMCTR1].data = VMCTR1_buffer;

    _lcd_panel_cmd[GAMCTRP1].cmd = 0xE0;
    _lcd_panel_cmd[GAMCTRP1].nrOfByte = 16;
    _lcd_panel_cmd[GAMCTRP1].data = GAMCTRP1_buffer;

    _lcd_panel_cmd[GAMCTRN1].cmd = 0xE1;
    _lcd_panel_cmd[GAMCTRN1].nrOfByte = 16;
    _lcd_panel_cmd[GAMCTRN1].data = GAMCTRN1_buffer;

    /* VCOM Control 1 */
    _lcd_panel_cmd[INVCTR].cmd = 0xB4;
    _lcd_panel_cmd[INVCTR].nrOfByte = 1;
    _lcd_panel_cmd[INVCTR].data = INVCTR_buffer;
}


/**
 *
 * @param data
 */
static void ST7735_write(uint8_t data)
{
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPIx, data);
}

/**
 *
 * @param cmd
 */
static void ST7735_cmd(uint8_t cmd)
{
    A0_L();
    ST7735_write(cmd);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}

/**
 *
 * @param data
 */
static void ST7735_data(uint8_t data)
{
    A0_H();
    ST7735_write(data);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}

/**
 *@brief
 */
static void ST7735_Reset(void)
{
    RST_H();
    Delay_ms(100);
    RST_L();
    Delay_ms(200);
    RST_H();
    Delay_ms(100);
}
