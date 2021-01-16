/**
 *  @file  : tetris_handler.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 14 gen 2021
 */

#include "tetris_handler.h"
#include <stdint.h>

#include "lcd\color.h"

#define		HEIGTH_IN_PIXEL		(128u)
#define		LENGTH_IN_PIXEL		(128u)

#define		AREA_HEIGTH			(10u)
#define		AREA_LENGTH			(30u)
#define		PIXEL_PER_SQUARE	(1u)

typedef enum
{
	e_piece_I,
	e_piece_J,
	e_piece_L,
	e_piece_O,
	e_piece_S,
	e_piece_T,
	e_piece_Z,
	e_piece_last
}t_piece_type;

typedef enum
{
	rotation_0,
	rotation_90,
	rotation_180,
	rotation_270,
	rotation_max
}t_rotation;

/*
 * rotation: we assume to be clockwise!
 *
 * 						 rotation_0
 *                          |
 *                          |
 *                          |
 *                          |
 *                          |
 * rotation_270 ------------------------- rotation_90
 *                          |
 *                          |
 *                          |
 *                          |
 *                          |
 * 						rotation_180
 *
 */

/**
 *
 */
typedef struct
{
	uint8_t			probability;	// TODO probability make sense ?
	uint16_t		color;
	uint16_t		base_schema;
	uint8_t 		max_height;
	uint8_t 		max_length;
	t_piece_type 	_type;
}s_base_piece_prop;

/*
 * How is basic_schema organized:
 *	 ___ ___ ___ ___
 *	| 0 | 1 | 2 | 3 |
 *	|___|___|___|___|
 *	| 4 | 5 | 6 | 7 |
 *	|___|___|___|___|
 *	| 8 | 9 |10 |11 |
 *	|___|___|___|___|
 *	|12 |13 |14 |15 |
 *	|___|___|___|___|
 *
 *	If in the "matrix" the block is present, the bit is set. So we can hold a schema in a uint16
 */

typedef struct
{
	uint8_t				x;
	uint8_t				y;
}t_position;

/**
 *
 */
typedef struct
{
	uint16_t			id;
	t_rotation			_actual_rotation;
	t_position			_pos;
	s_base_piece_prop*	_base_prop;
}s_piece;

const uint16_t _base_schema_I = 0x0000;
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
