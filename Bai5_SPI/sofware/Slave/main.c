#include "stm32f10x.h"                  
#include "stm32f10x_gpio.h"             
#include "stm32f10x_rcc.h"              
#include "stm32f10x_spi.h"              
#include "stm32f10x_tim.h"              

#define SPI_SCK_PIN 	GPIO_Pin_0 
#define SPI_MISO_PIN 	GPIO_Pin_1
#define SPI_MOSI_PIN 	GPIO_Pin_2
#define SPI_CS_PIN 		GPIO_Pin_3
#define SPI_GPIO			GPIOA
#define SPI_RCC 			RCC_APB2Periph_GPIOA

void delay_ms(uint32_t time);


void RCC_Config()
{
	RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}


void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN | SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}


void TIM_Config()
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;
	TIM_InitStruct.TIM_Period = 0xFFFF;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint32_t time)
{
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < time * 10) {}
}


void SPI_init()
{
	GPIO_WriteBit(SPI_GPIO, SPI_MISO_PIN, Bit_RESET);
}


uint8_t SPI_Slave_Receive()
{
	uint8_t u8Data = 0;
	uint8_t u8Mask = 0x80;
	

	while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_PIN) == Bit_SET);
	
	for (int i = 0; i < 8; i++)
	{
		while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_PIN) == Bit_RESET);
		
		if (GPIO_ReadInputDataBit(SPI_GPIO, SPI_MOSI_PIN))
		{
			u8Data |= u8Mask;
		}
		
		u8Mask >>= 1;
		
		while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_PIN) == Bit_SET);
	}
	
	while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_PIN) == Bit_RESET);
	
	return u8Data;
}

int main()
{
	uint8_t receivedData;
	
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	SPI_init();
	
	while (1)
	{
		receivedData = SPI_Slave_Receive();
		delay_ms(1000);
	}
}
