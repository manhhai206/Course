#include "stm32f10x.h"                
#include "stm32f10x_rcc.h"              
#include "stm32f10x_gpio.h"            
#include "stm32f10x_tim.h"             

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA

#define BRateTime 104  // Adjust this for accurate baud rate timing 9600

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = RX_Pin;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART_GPIO, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Pin = TX_Pin;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(UART_GPIO, &GPIOInitStruct);
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

void clock() {
    delay_us(BRateTime);
}

void UARTSoftware_Init(){

	GPIO_SetBits(GPIOA,TX_Pin);
	delay_us(1);

uint16_t Parity_Generate(uint8_t data, Parity_Mode Mode) {
    uint8_t count = 0;
    uint8_t data1 = data;
	
		// Dem so luong bit 1
    for (int i = 0; i < 8; i++) {
        if (data1 & 0x01) {
            count++;
        }
        data1 >>= 1;
    }
    switch (Mode) {
        case Parity_Mode_NONE:
            return data;
				// Neu bit 1 chan => thÃªm 1; neu le => thÃªm 0
        case Parity_Mode_ODD:
            return (data << 1) | (count % 2 ? 1 : 0);
        case Parity_Mode_EVEN:
            return (data << 1) | (count % 2 ? 0 : 1);
        default:
            return data;
    }
}

void UARTSoftware_Transmitt(char c) {
    // Start bit
    GPIO_ResetBits(GPIOA, TX_Pin);
    clock();

    // Truy?n các bit d? li?u (LSB tru?c)
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i)) {
            GPIO_SetBits(GPIOA, TX_Pin);
        } else {
            GPIO_ResetBits(GPIOA, TX_Pin);
        }
        clock();
    }
}

char UARTSoftware_Receive() {
    char c = 0;

    // Ð?i Start bit
    while (GPIO_ReadInputDataBit(GPIOA, RX_Pin) == 1);

    // Ch? m?t n?a th?i gian bit d? vào gi?a start bit
    delay_us(BRateTime + BRateTime/ 2);

    // Ð?c các bit d? li?u (LSB tru?c)
    for (int i = 0; i < 8; i++) {
				
        if (GPIO_ReadInputDataBit(GPIOA, RX_Pin)) {
            c |= (1 << i);
        }
				clock(); // Ð?i d?n gi?a bit ti?p theo
    }

    // Ð?i Stop bit
    delay_us(BRateTime / 2);

    return c;
}

int main() {
    RCC_Config();
    GPIO_Config();
    TIM_Config();
		UARTSoftware_Init();

    while (1) 
		{
        UARTSoftware_Transmitt(UARTSoftware_Receive());
		}
 }
