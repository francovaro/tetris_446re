/**
 *  @file  : spi.c
 *	
 *  @brief	
 *
 *  @author: Francesco Varani
 *  @date  : 25 nov 2019
 */

#include "stm32f4xx_spi.h"
#include "stm32f4xx.h"
#include "spi.h"


/**
 *
 */
void SPI_Config(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(SPIx_SCK_GPIO_CLK | SPIx_MOSI_GPIO_CLK | SPIx_CS_GPIO_CLK
		  	  	  	  	  	  | LCD_A0_GPIO_CLK | LCD_RESET_GPIO_CLK, ENABLE);

  /* Enable the SPI clock */
  SPIx_CLK_INIT(SPIx_CLK, ENABLE);


  /* SPI GPIO Configuration --------------------------------------------------*/
  /* GPIO Deinitialisation */
  GPIO_DeInit(SPIx_SCK_GPIO_PORT);
  GPIO_DeInit(SPIx_MOSI_GPIO_PORT);
  GPIO_DeInit(SPIx_CS_GPIO_PORT);
  GPIO_DeInit(LCD_A0_GPIO_PORT);

  /* Connect SPI pins to AF5 */
  GPIO_PinAFConfig(SPIx_SCK_GPIO_PORT, SPIx_SCK_SOURCE, SPIx_SCK_AF);
  GPIO_PinAFConfig(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_SOURCE, SPIx_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = SPIx_SCK_PIN;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  SPIx_MOSI_PIN;
  GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStructure);



  /* SPI Chip Select pin configuration */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* checked */
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin =  SPIx_CS_PIN;
  GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStructure);

  /* command/data pin*/
  GPIO_InitStructure.GPIO_Pin =  LCD_A0_PIN;
  GPIO_Init(LCD_A0_GPIO_PORT, &GPIO_InitStructure);

  /* reset pin */
  GPIO_InitStructure.GPIO_Pin =  LCD_RESET_PIN;
  GPIO_Init(LCD_RESET_GPIO_PORT, &GPIO_InitStructure);

  GPIO_SetBits(SPIx_CS_GPIO_PORT, SPIx_CS_PIN);		/* SPI closed */
  GPIO_SetBits(LCD_RESET_GPIO_PORT, LCD_RESET_PIN);	/* reset high - LCD enabled */

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPIx);
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		/* from chinese demo... */
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		/* from chinese demo... */
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft /*| SPI_NSSInternalSoft_Set*/;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 10;

  //SPI_NSSInternalSoftwareConfig(SPIx, SPI_NSSInternalSoft_Set);
  SPI_Init(SPIx, &SPI_InitStructure);

  /* Enable the Tx empty interrupt */
  //SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, ENABLE);

  /*
   * TODO
   * use DMA
   */
  //SPI_I2S_DMACmd(SPIx, SPI_DMAReq_Rx, ENABLE);
  //SPI_I2S_DMACmd(SPIx, SPI_DMAReq_Tx, ENABLE);

  /* Enable the SPI peripheral */
  SPI_Cmd(SPIx, ENABLE);

  /* Configure the Priority Group to 1 bit */
#ifdef _SPI_IRQ
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Configure the SPI interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = SPIx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;	/* don't need it*/
  NVIC_Init(&NVIC_InitStructure);
#endif

}

/**
 *
 */
void SPIx_IRQHANDLER(void)
{
  /* SPI in Receiver mode */
  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
  {
	  /* Receive Transaction data */
	  SPI_I2S_ClearITPendingBit(SPIx, SPI_I2S_IT_RXNE);
  }

  if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) == SET)
  {
	  SPI_I2S_ClearITPendingBit(SPIx, SPI_I2S_IT_TXE);
  }
}
