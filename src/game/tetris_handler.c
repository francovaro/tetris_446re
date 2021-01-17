/**
 *  @file  : tetris_handler.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 14 gen 2021
 */

#include <game/tetris_handler.h>
#include <stdint.h>

#include "lcd\color.h"

#define		AREA_HEIGTH			(10u)
#define		AREA_LENGTH			(30u)
#define		PIXEL_PER_SQUARE	(1u)


/**
 * @brief Array with const prop for all pieces
 */
const s_base_piece_prop pieces[e_piece_last] =
		{
			// e_piece_I
			{
				.probability	= 10,
				.color			= COLOR_CYAN,
				.base_schema 	= (1<<1) | (1<<5) | (1<<9) | (1<<13),
				.max_height 	= 1,
				.max_height 	= 4,
				._type 			= e_piece_I
			},
			// e_piece_J
			{
				.probability 	= 10,
				.color			= COLOR_BLUE,
				.base_schema 	= (1<<1) | (1<<2) | (1<<5) | (1<<9),
				.max_height 	= 2,
				.max_height 	= 3,
				._type 			= e_piece_J
			},
			// e_piece_L
			{
				.probability 	= 10,
				.color			= COLOR_ORANGE,
				.base_schema 	= (1<<1) | (1<<2) | (1<<6) | (1<<10),
				.max_height 	= 2,
				.max_height 	= 3,
				._type 			= e_piece_L
			},
			// e_piece_O
			{
				.probability	 = 10,
				.color			= COLOR_YELLOW,
				.base_schema 	= (1<<1) | (1<<2) | (1<<5) | (1<<6),
				.max_height 	= 2,
				.max_height 	= 2,
				._type 			= e_piece_O
			},
			// e_piece_S
			{
				.probability 	= 10,
				.color			= COLOR_GREEN,
				.base_schema 	= (1<<1) | (1<<2) | (1<<4) | (1<<5),
				.max_height 	= 2,
				.max_height 	= 3,
				._type 			= e_piece_S
			},
			// e_piece_T
			{
				.probability 	= 10,
				.color			= COLOR_PURPLE,
				.base_schema 	= (1<<0) | (1<<1) | (1<<2) | (1<<5),
				.max_height 	= 2,
				.max_height 	= 3,
				._type 			= e_piece_T
			},
			// e_piece_Z
			{
				.probability 	= 10,
				.color			= COLOR_RED,
				.base_schema	= (1<<0) | (1<<1) | (1<<5) | (1<<6),
				.max_height 	= 2,
				.max_height 	= 3,
				._type 			= e_piece_Z
			}
		};
