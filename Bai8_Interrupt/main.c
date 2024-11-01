#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void RCC_Config(){
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Config(){
    GPIO_InitTypeDef GPIOInitStruct;

    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIOInitStruct);
}

void EXTI_Config(){
    EXTI_InitTypeDef EXTIInitStruct;

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTIInitStruct.EXTI_Line = EXTI_Line0;
    EXTIInitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTIInitStruct.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTIInitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTIInitStruct);
}

void NVIC_Config(){
    NVIC_InitTypeDef NVICInitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVICInitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVICInitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVICInitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVICInitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVICInitStruct);
}


void EXTI0_IRQHandler(void){
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        GPIOC->ODR ^= GPIO_Pin_13;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

int main(){

    RCC_Config();
    GPIO_Config();
    EXTI_Config();
    NVIC_Config();

    while(1) {
			
    }
}
