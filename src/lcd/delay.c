/**
 *  @file  : delay.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 11 nov 2020
 */
#include "stm32f4xx.h"
#include "lcd\delay.h"

__IO uint32_t _req_delay_us;

/**
 * @brief Initializes TIM2
 */
void Delay_init(void)
{
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef            NVIC_InitStructure;
    RCC_ClocksTypeDef           RCC_ClocksStatus;

	_req_delay_us = 0;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    RCC_GetClocksFreq(&RCC_ClocksStatus);
    uint16_t prescaler = ((RCC_ClocksStatus.PCLK1_Frequency*2)) / 1000000  - 1; //1 tick = us

    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

    TIM_TimeBaseInitStruct.TIM_Prescaler = prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 1;                       /* period => 1ns*1000 = 1us*/
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);    /* TIM 2 */

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);              /* triggers when it reload */
}

/**
 * @brief
 * @param delay
 */
void Delay_ms(uint16_t delay)
{
	do
	{
		Delay_us(1000);
		delay--;
	}while(delay);
}

/**
 * @brief
 * @param delay
 */
void Delay_us(uint16_t delay)
{
	_req_delay_us = delay;

	TIM_Cmd(TIM2, ENABLE);
	while(_req_delay_us);

	TIM_Cmd(TIM2, DISABLE);
}

/**
 *
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        TIM2->CR1 &= (uint16_t)~TIM_CR1_CEN;
        if (_req_delay_us != 0)
        {
            _req_delay_us--;
        }
        TIM2->CR1 |= TIM_CR1_CEN;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
