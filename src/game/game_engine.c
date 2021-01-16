/**
 *  @file  : game_engine.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 16 gen 2021
 */
/* FreeRTOS include */
#include "FreeRTOS.h"
#include "task.h"

#include "game\game_engine.h"

#include "common_options.h"

#if DEBUG_KEYS_PRINT == 1
#include <string.h>
#include <stdio.h>
#include "lib_uart.h"
#endif
/* -------------------------------------------------------------------------------------------------------------------- */
typedef enum
{
    e_game_status_splash,
    e_game_status_playing,
    e_game_status_game_over,
    e_game_status_none
}t_game_status;

/* -------------------------------------------------------------------------------------------------------------------- */
#define GAME_ENGINE_PERIOD         (250u)


static t_game_status _actual_game_status = e_game_status_none;

/* -------------------------------------------------------------------------------------------------------------------- */
/**
 *
 */
void GameEngine_Init(void)
{
    _actual_game_status = e_game_status_splash;
}

/**
 *
 * @param portTASK_FUNCTION(vKeysHandlerTask, pvParameters)
 */
portTASK_FUNCTION(vGameEngineTask, pvParameters)
{
    TickType_t                  loop_start_tick = 0;
    TickType_t                  _time_increment = GAME_ENGINE_PERIOD;
    static t_game_status        next_game_status;

    while (1)
    {
        _actual_game_status = next_game_status;

        switch (_actual_game_status)
        {
            case e_game_status_splash:
            {
                next_game_status = e_game_status_playing;
                _time_increment = GAME_ENGINE_PERIOD * 20;
                /*
                 * TODO
                 * draw the nice splash screen
                 */
            }
            break;
            case e_game_status_playing:
            {
                _time_increment = GAME_ENGINE_PERIOD;
            }
            break;
            case e_game_status_game_over:
            {
                next_game_status = e_game_status_playing;
                _time_increment = GAME_ENGINE_PERIOD * 20;
                /*
                 * TODO
                 * draw the end game screen
                 */
            }
            break;
            default:
            case e_game_status_none:
            {
#if DEBUG_GAME_ENGINE == 1
                char str_debug[100] = "0";
                snprintf(str_debug, sizeof(str_debug), "GameEngine not initialized\n");
                UART_lib_sendData(str_debug, strlen(str_debug));
#endif
                /*
                 * ops
                 */
                return;
            }
            break;
        }

        vTaskDelayUntil (&loop_start_tick, _time_increment);
    }
}