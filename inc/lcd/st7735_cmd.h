/*
 *  @file  : st7735_cmd.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 27 nov 2019
 */

#ifndef ST7735_CMD_H_
#define ST7735_CMD_H_

//#include <sdint.h>

typedef struct
{
	uint8_t cmd;
	uint8_t *data;
	uint8_t nrOfByte;
} tLCD_cmd;

typedef enum {
	eLCD_orientation_normal 		= 0,
	eLCD_orientation_CW     		= 1,
	eLCD_orientation_normal_CCW    	= 2,
	eLCD_orientation_normal_180    	= 3,
	eLCD_orientation_max
} tLCD_orientation;

typedef enum
{
	NOP,
	SYS_CMD_SWRESET,
	RDDID,
	RDDST,
	RDDPM,
	RDD_MADCTL,
	RDD_COLMOD,
	RDDIM,
	RDDSM,
	RDDSDR,
	SLPIN,
	SLPOUT,
	PTLON,
	NORON,
	INVOFF,
	INVON,
	GAMSET,
	DISPOFF,
	DISPON,
	CASET,
	RASET,
	RAMWR,
	RGBSET,
	RAMRD,
	PTLAR,
	SCRLAR,
	TEOFF,
	TEON,
	MADCTL,
	VSCSAD,
	IDMOFF,
	IDMON,
	COLMOD,
	RDID1,
	RDID2,
	RDID3,
	e_syscmd_max
}tST7735_system_cmd;

typedef enum
{
	FRMCTR1,
	FRMCTR2,
	FRMCTR3,
	INVCTR,
	PWCTR1,
	PWCTR2,
	PWCTR3,
	PWCTR4,
	PWCTR5,
	VMCTR1,
	VMOFCTR,
	WRID2,
	WRID3,
	NVCTR1,
	NVCTR2,
	NVCTR3,
	GAMCTRP1,
	GAMCTRN1,
	e_panelcmd_max
}tST7735_panel_cmd;

typedef struct
{
    uint8_t     x0;
    uint8_t     y0;
    uint16_t    schema;
    uint16_t    bck_color;
    uint16_t    for_color;
}t_draw_box;

extern void ST7735_init_with_commands(void);

extern void ST7735_send_sys_cmd(tST7735_system_cmd sysCmd);
extern void ST7735_send_panel_cmd(tST7735_panel_cmd panelCmd);
extern void ST7735_turns_display(uint8_t power);
extern void ST7735_set_orientation(tLCD_orientation orientation);
extern void ST7735_set_windows(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
extern void ST7735_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
extern void ST7735_draw_unfilled_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
extern void ST7735_draw_filled_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
extern void ST7735_draw_v_line(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color);
extern void ST7735_draw_h_line(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color);
extern void ST7735_clear(uint16_t color);
extern void ST7735_draw_box(t_draw_box box);
extern void ST7735_draw_multiple_box(t_draw_box box, uint8_t how_many);

#endif /* ST7735_CMD_H_ */
