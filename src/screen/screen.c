/**
 *  @file  : screen.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 17 gen 2021
 */

#include "screen\screen.h"
#include "screen\splash_screen.h"
#include "screen\test_screen.h"

/*
 * Best way to print a form:
 *  - directly in the call ?
 *  - set a variable and then have a proper task to handle it ?
 */

/**
 *
 * @param screen_to_print
 */
void Screen_Print(t_screen screen_to_print)
{
    switch(screen_to_print)
    {
        case e_screen_splash_screen:
        {
            Splash_Screen_Print();
        }
        break;
        case e_screen_game:
        {
            Test_screen();
        }
        break;
        case e_screen_game_over:
        {

        }
        break;
        default:
        case e_screen_max:
        {

        }
        break;
    }
}
