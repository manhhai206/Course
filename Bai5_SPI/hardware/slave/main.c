#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

#define SPI1_NSS 	GPIO_Pin_4
#define SPI1_SCK 	GPIO_Pin_5
#define SPI1_MISO GPIO_Pin_6
#define SPI1_MOSI GPIO_Pin_7
#define SPI1_GPIO	GPIOA

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI | SPI1_NSS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
}

void SPI_Config(){
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}

uint8_t SPI_Receive1Byte(void){
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} 
    return(uint8_t)SPI_I2S_ReceiveData(SPI1);
}

void TIM_Config(){
    TIM_TimeBaseInitTypeDef TIM_InitStruct;

    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_Prescaler = 7200 - 1; 
    TIM_InitStruct.TIM_Period = 0xFFFF;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint32_t time){
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time * 10) {}
}

uint8_t receivedData;

int main() {
    RCC_Config();   
    GPIO_Config(); 
    SPI_Config();   
    TIM_Config();   

    while (1) {
        receivedData = SPI_Receive1Byte(); 
        delay_ms(500); 
    }
}