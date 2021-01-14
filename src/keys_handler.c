/**
 *  @file  : keys_handler.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 14 gen 2021
 */
/* FreeRTOS include */
#include "FreeRTOS.h"
#include "task.h"

/* hw stuff include */
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"

#include <stdint.h>
#include "keys_handler.h"

/**
 * here we:
 * - initializes HW for keyboard
 * -
 */
/* -------------------------------------------------------------------------------------------------------------------- */
#define KEYS_HANDLER_PERIOD 		(1u)
#define KEYS_PRESSED_THRESHOLD		(5u)	/* in ms*/
/* -------------------------------------------------------------------------------------------------------------------- */
static void keyboard_Init(void);
static void keyboard_SetFunctionality(void);
static void keyboard_HW_init(void);
/* -------------------------------------------------------------------------------------------------------------------- */
__IO uint16_t _keyPressedGlobal;
__IO uint16_t _notifyKeyPressed;
static t_keyboard keyboard[eKey_LAST];

/* -------------------------------------------------------------------------------------------------------------------- */
portTASK_FUNCTION(vKeysHandlerTask, pvParameters)
{
	static uint16_t 	counter[eKey_LAST] = {0};
	TickType_t 			loop_start_tick = 0;
	uint8_t				i;

	keyboard_Init();
	loop_start_tick = xTaskGetTickCount();

	while(1)	/* live forever */
	{
		for( i = 0; i < eKey_LAST; i++)
		{
			if (_keyPressedGlobal & (1<<i))
			{
				counter[i]++;
				if (counter[i] > KEYS_PRESSED_THRESHOLD)
				{
					_notifyKeyPressed |= (1<<i);	/* set it */
				}
			}
			else
			{
				counter[i] = 0;
				_notifyKeyPressed &= (~(1<<i));	/*	clear it */
			}
		}
		vTaskDelayUntil (&loop_start_tick, KEYS_HANDLER_PERIOD);
	}
}

/* -------------------------------------------------------------------------------------------------------------------- */
/**
 *
 */
static void keyboard_Init(void)
{
	_keyPressedGlobal = 0;
	_notifyKeyPressed = 0;

	keyboard_SetFunctionality();
	keyboard_HW_init();
}


/**
 * @brief init the structure that holds the info about handled keys.
 */
void keyboard_SetFunctionality(void)
{
	uint8_t i;

	for (i = 0; i < eKey_LAST ; i++)
	{
		keyboard[i].func = (void*)0;
		keyboard[i].key = (eKeyboard_key)i;
	}

	keyboard[0].port = GPIOA;
	keyboard[0].pin	= GPIO_Pin_10;
	keyboard[0].intLine = EXTI_Line10;
	keyboard[0].key = eKey_UP;

	keyboard[1].port = GPIOA;
	keyboard[1].pin	= GPIO_Pin_11;
	keyboard[1].intLine = EXTI_Line11;
	keyboard[1].key = eKey_DOWN;

	keyboard[2].port = GPIOA;
	keyboard[2].pin	= GPIO_Pin_12;
	keyboard[2].intLine = EXTI_Line12;
	keyboard[2].key = eKey_LEFT;

	keyboard[3].port = GPIOA;
	keyboard[3].pin	= GPIO_Pin_5;
	keyboard[3].intLine = EXTI_Line5;
	keyboard[3].key = eKey_RIGHT;

	keyboard[4].port = GPIOA;
	keyboard[4].pin	= GPIO_Pin_6;
	keyboard[4].intLine = EXTI_Line6;
	keyboard[4].key = eKey_OK;

	keyboard[5].port = GPIOA;
	keyboard[5].pin	= GPIO_Pin_15;
	keyboard[5].intLine = EXTI_Line15;
	keyboard[5].key = eKey_CANCEL;
}

/**
 *
 */
static void keyboard_HW_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* init clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Enable SYSCFG's APB interface clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);	/* useful ? */

	GPIO_StructInit(&GPIO_InitStructure);
	EXTI_StructInit(&EXTI_InitStructure);

	/*--------------------------------------------------------------------------------------*/
	/* GPIO Init */
	/* init GPIO as input */
	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_15);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

	/* connect pin to ext */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource11);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource12);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource15);


	/*--------------------------------------------------------------------------------------*/
	/* EXTINT Init */
	/* set ext  10 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		/* yeah rising or falling ? */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* set ext  11 to 15 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	EXTI_Init(&EXTI_InitStructure);

	/*--------------------------------------------------------------------------------------*/
	/* INTERRUPT Init */
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			/* to check ! */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}

/* -------------------------------------------------------------------------------------------------------------------- */
/**
 *
 */
void EXTI9_5_IRQHandler(void)
{
	uint8_t i;

	for (i = 0; i< eKey_LAST; i++)
	{
		if (EXTI_GetITStatus(keyboard[i].intLine) == SET)
		{
			EXTI_ClearITPendingBit(keyboard[i].intLine);
			if (GPIO_ReadInputDataBit(keyboard[i].port, keyboard[i].pin) == RESET)
			{
				_keyPressedGlobal|= (1 << keyboard[i].key);	/* let's xor it */
			}
			else
			{
				_keyPressedGlobal &= (~(1 << keyboard[i].key));	/* let's xor it */
			}
		}
	}

}

/**
 *
 */
void EXTI15_10_IRQHandler(void)
{
	uint8_t i;

	for (i = 0; i< eKey_LAST; i++)
	{
		if (EXTI_GetITStatus(keyboard[i].intLine) == SET)
		{
			EXTI_ClearITPendingBit(keyboard[i].intLine);

			if (GPIO_ReadInputDataBit(keyboard[i].port, keyboard[i].pin) == RESET)
			{
				_keyPressedGlobal |= (1 << keyboard[i].key);	/* let's xor it */
			}
			else
			{
				_keyPressedGlobal &= (~(1 << keyboard[i].key));	/* let's xor it */
			}
		}
	}
}
