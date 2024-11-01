#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void ADC_Config() {
    ADC_InitTypeDef ADC_InitStruct;
    
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;   
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    
    ADC_Init(ADC1, &ADC_InitStruct);
    
    // S?a thành ADC_Channel_5 d? s? d?ng PA5 (ADC1_IN5)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t final = 0;

int main() {
    RCC_Config();
    GPIO_Config();
    ADC_Config();
    
    while (1) {
        final = ADC_GetConversionValue(ADC1);
        // B?n có th? thêm mã x? lý ? dây n?u c?n
    }
}
