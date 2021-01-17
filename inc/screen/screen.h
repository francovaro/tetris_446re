/**
 *  @file  : screen.h
 *	
 *  @brief	
 *
 *  @author: franc
 *  @date  : 17 gen 2021
 */

#ifndef INC_SCREEN_SCREEN_H_
#define INC_SCREEN_SCREEN_H_

typedef enum
{
    e_screen_splash_screen,
    e_screen_game,
    e_screen_game_over,
    e_screen_max
}t_screen;

extern void Screen_Print(t_screen screen_to_print);

#endif /* INC_SCREEN_SCREEN_H_ */
