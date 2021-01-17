/**
 *  @file  : tetris_handler.h
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 17 gen 2021
 */

#ifndef INC_GAME_TETRIS_HANDLER_H_
#define INC_GAME_TETRIS_HANDLER_H_

#include <stdio.h>

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

/*
 * rotation: we assume to be clockwise!
 *
 *                       rotation_0
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
 *                      rotation_180
 *
 */

typedef enum
{
    rotation_0,
    rotation_90,
    rotation_180,
    rotation_270,
    rotation_max
}t_rotation;

/*
 * How is basic_schema organized:
 *   ___ ___ ___ ___
 *  | 0 | 1 | 2 | 3 |
 *  |___|___|___|___|
 *  | 4 | 5 | 6 | 7 |
 *  |___|___|___|___|
 *  | 8 | 9 |10 |11 |
 *  |___|___|___|___|
 *  |12 |13 |14 |15 |
 *  |___|___|___|___|
 *
 *  If in the "matrix" the block is present, the bit is set. So we can hold a schema in a uint16
 */
typedef struct
{
    uint8_t         probability;    // TODO probability make sense ?
    uint16_t        color;
    uint16_t        base_schema;
    uint8_t         max_height;
    uint8_t         max_length;
    t_piece_type    _type;
}s_base_piece_prop;

typedef struct
{
    uint8_t             x;
    uint8_t             y;
}t_position;

/**
 *
 */
typedef struct
{
    uint16_t            id;
    t_rotation          _actual_rotation;
    t_position          _pos;
    s_base_piece_prop*  _base_prop;
}s_piece;

extern const s_base_piece_prop pieces[];

#endif /* INC_GAME_TETRIS_HANDLER_H_ */
