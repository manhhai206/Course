#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "Spi.h"


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

uint8_t txBuffer[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
uint8_t rxBuffer[5];

int main()
{     
  TIM_Config(); 
	
	Spi_ConfigType* spiConfig = NULL;
	Spi_Init(spiConfig);
	
	Spi_SetupEB(SPI_CHANNEL_1, txBuffer, rxBuffer, 5);
	
	while(1){
		Spi_SyncTransmit(SPI_CHANNEL_1);
    delay_ms(1000);
	}
	
}
