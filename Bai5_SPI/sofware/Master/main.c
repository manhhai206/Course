#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

// define cac chan SPI
#define SPI_SCK_Pin 	GPIO_Pin_0
#define SPI_MISO_Pin 	GPIO_Pin_1
#define SPI_MOSI_Pin 	GPIO_Pin_2
#define SPI_CS_Pin 	GPIO_Pin_3
#define SPI_GPIO 	GPIOA
#define SPI_RCC 	RCC_APB2Periph_GPIOA

void delay_ms(uint32_t time);

// Cau hinh CLock cho ngoai vi
void RCC_Config(){
	RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

// Khoi tao cac chan SPI
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin | SPI_CS_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}

//Set up Timer 
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

void Clock(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
	delay_ms(1);
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	delay_ms(1);
}

//Khoi tao Start
void SPI_init(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
}

void SPI_Master_Transmit(uint8_t u8Data){	
	uint8_t u8Mask = 0x80;	
	uint8_t tempData;
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay_ms(1);
	for(int i = 0; i < 8; i++){
		tempData = u8Data & u8Mask;
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay_ms(1);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay_ms(1);
		}
		u8Data = u8Data << 1;
		Clock();
	}
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay_ms(1);
}

uint8_t DataTrans[] = {1,2,3,4,5,6,7,8};
int main(){
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	SPI_init();
	while(1){	
		for(int i = 0; i < 7; i++){
			SPI_Master_Transmit(DataTrans[i]);
			delay_ms(1000);
		}
	}
}
