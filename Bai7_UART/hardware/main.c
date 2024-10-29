#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

void RCC_Config() 
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		//PA9 TX
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		//PA10 RX
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void UART_Config()
{
		USART_InitTypeDef UART_TnitStruct;
		UART_TnitStruct.USART_BaudRate = 9600;
		UART_TnitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		UART_TnitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		UART_TnitStruct.USART_Parity = USART_Parity_No;
		UART_TnitStruct.USART_StopBits = USART_StopBits_1;
		UART_TnitStruct.USART_WordLength = USART_WordLength_8b;
	
		USART_Init(USART1,&UART_TnitStruct);
		USART_Cmd(USART1,ENABLE);
}


void TIM_Config() {
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_Prescaler = 72 - 1; 
    TIM_InitStruct.TIM_Period = 0xFFFF;   
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}

void delay_us(uint32_t time) {
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time) {}
}

uint8_t data[10] = {'h','a','i','2','0','6','0','0','0','0'};
uint8_t datarc;
int main()
{
    RCC_Config();
    GPIO_Config();
    UART_Config();
    TIM_Config();

    for (int i = 0; i < 10; i++) 
    {
        USART_SendData(USART1, data[i]);
				// kiem tra transmit flag xem co dang empty khong ?
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
        delay_us(1000);
    }

    while (1) 
    {
			if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
			{
				datarc = USART_ReceiveData(USART1);
				USART_SendData(USART1, datarc);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
				
			}
    }
}