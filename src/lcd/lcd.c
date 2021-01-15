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
 * @param data
 */
void ST7735_write(uint8_t data)
{
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPIx, data);
}

/**
 *
 * @param reg
 * @param data
 */
void Lcd_write_reg(uint8_t reg, uint8_t data)
{
	ST7735_cmd(reg);
	ST7735_data(data);
}

/**
 *
 * @param cmd
 */
void ST7735_cmd(uint8_t cmd)
{
	A0_L();
	ST7735_write(cmd);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}

void ST7735_data(uint8_t data)
{
	A0_H();
	ST7735_write(data);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET);
}

/**
 *
 * @param R red
 * @param G green
 * @param B blue
 * @return the uin16 rapresentation of the signle R G B color
 */
uint16_t RGB565(uint8_t R,uint8_t G,uint8_t B)
{
	return ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
}

void ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE)
{
	CS_L();
	ST7735_cmd(0x2a); // Column address set
	A0_H();
	ST7735_write(XS >> 8);
	ST7735_write(XS);
	ST7735_write(XE >> 8);
	ST7735_write(XE);

	ST7735_cmd(0x2b); // Row address set
	A0_H();
	ST7735_write(YS >> 8);
	ST7735_write(YS);
	ST7735_write(YE >> 8);
	ST7735_write(YE);

	ST7735_cmd(0x2c); // Memory write
	CS_H();
}

void ST7735_Clear(uint16_t color)
{
	uint16_t i;
	uint8_t  CH;
	uint8_t  CL;

	CH = color >> 8;
	CL = (uint8_t)color;

	CS_L();
	ST7735_AddrSet(0,0,LCD_SCREEN_W - 1,LCD_SCREEN_H - 1);
	A0_H();
	for (i = 0; i < LCD_SCREEN_W * LCD_SCREEN_H; i++)
	{
		ST7735_write(CH);
		ST7735_write(CL);
	}
	CS_H();
}

void ST7735_HLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color)
{
    uint16_t i;
    uint8_t CH = color >> 8;
    uint8_t CL = (uint8_t)color;

    CS_L();
    ST7735_AddrSet(X1,Y,X2,Y);
	A0_H();
	for (i = 0; i <= (X2 - X1); i++)
	{
		ST7735_write(CH);
		ST7735_write(CL);
	}
	CS_H();
}

void ST7735_VLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color)
{
    uint16_t i;
    uint8_t CH = color >> 8;
    uint8_t CL = (uint8_t)color;

    CS_L();
    ST7735_AddrSet(X,Y1,X,Y2);
	A0_H();
	for (i = 0; i <= (Y2 - Y1); i++)
	{
		ST7735_write(CH);
		ST7735_write(CL);
	}
	CS_H();
}

void ST7735_Line(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color)
{
	int16_t dX = X2-X1;
	int16_t dY = Y2-Y1;
	int16_t dXsym = (dX > 0) ? 1 : -1;
	int16_t dYsym = (dY > 0) ? 1 : -1;

	if (dX == 0)
	{
		if (Y2>Y1) 
		{
			ST7735_VLine(X1,Y1,Y2,color); 
		}
		else
		{
			ST7735_VLine(X1,Y2,Y1,color);
		}		 
		return;
	}
	if (dY == 0)
	{
		if (X2>X1) 
		{
			ST7735_HLine(X1,X2,Y1,color); 
		}
		else
		{
			ST7735_HLine(X2,X1,Y1,color);
		} 
		return;
	}

	dX *= dXsym;
	dY *= dYsym;
	int16_t dX2 = dX << 1;
	int16_t dY2 = dY << 1;
	int16_t di;

	if (dX >= dY)
	{
		di = dY2 - dX;
		while (X1 != X2)
		{
			//ST7735_Pixel(X1,Y1,color);
			X1 += dXsym;
			if (di < 0)
			{
				di += dY2;
			}
			else
			{
				di += dY2 - dX2;
				Y1 += dYsym;
			}
		}
	}
	else
	{
		di = dX2 - dY;
		while (Y1 != Y2)
		{
			//ST7735_Pixel(X1,Y1,color);
			Y1 += dYsym;
			if (di < 0)
			{
				di += dX2;
			}
			else
			{
				di += dX2 - dY2;
				X1 += dXsym;
			}
		}
	}
	//ST7735_Pixel(X1,Y1,color);
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

void ST7735_Rect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color)
{
	CS_L();
	ST7735_HLine(X1,X2,Y1,color);
	ST7735_HLine(X1,X2,Y2,color);
	ST7735_VLine(X1,Y1,Y2,color);
	ST7735_VLine(X2,Y1,Y2,color);
	CS_H();
}

void ST7735_FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color)
{
	uint16_t i;
	uint16_t FS = (X2 - X1 + 1) * (Y2 - Y1 + 1);
    uint8_t CH = color >> 8;
    uint8_t CL = (uint8_t)color;

	CS_L();
	ST7735_AddrSet(X1,Y1,X2,Y2);
	A0_H();
	for (i = 0; i < FS; i++)
	{
		ST7735_write(CH);
		ST7735_write(CL);
	}
	CS_H();
}
