#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA

#define BRateTime 104  // Dieu chinh thoi gian cho baudrate (9600 baud)

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
    delay_us(BRateTime);  // Tao 1 baudrate delay
}

void UARTSoftware_Init() {
    GPIO_SetBits(GPIOA, TX_Pin);  
    delay_us(1); 
}

void UARTSoftware_Transmitt(char c) {
    // Bit bat dau
    GPIO_ResetBits(GPIOA, TX_Pin);  // Keo chan TX xuong 0 cho bit bat dau
    clock(); 

    // Truyen 8 bit du lieu (LSB truoc)
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i)) {
            GPIO_SetBits(GPIOA, TX_Pin);  // Gui bit 1
        } else {
            GPIO_ResetBits(GPIOA, TX_Pin);  // Gui bit 0
        }
        clock();  // Doi theo thoi gian cho bit tiep theo
    }

    // Bit dung 
    GPIO_SetBits(GPIOA, TX_Pin);  // Keo chan TX cao cho bit dung
    clock();  // Doi theo thoi gian baudrate de hoan thanh bit dung
}

char UARTSoftware_Receive() {
    char c = 0;

    // Cho den khi co bit bat dau (low)
    while (GPIO_ReadInputDataBit(GPIOA, RX_Pin) == 1);

    // Cho 1.5 baudrate de lay mau du lieu chinh giua cac bit
    delay_us(BRateTime + BRateTime / 2);

    // Doc 8 bit du lieu (LSB truoc)
    for (int i = 0; i < 8; i++) {
        if (GPIO_ReadInputDataBit(GPIOA, RX_Pin)) {
            c |= (1 << i);  // Dat bit neu la 1
        }
        clock();  // Doi theo thoi gian cho bit tiep theo
    }

    // Cho bit dung (nno phai cao)
    delay_us(BRateTime / 2);  // Doi thoi gian 0.5 baudrate sau khi doc du lieu
    return c;
}

char data[] = {'H','A','I'};

int main() {
    RCC_Config();
    GPIO_Config();
    TIM_Config();
    UARTSoftware_Init();

    while (1) {

        for (int i = 0; i < 3; i++) {
            UARTSoftware_Transmitt(data[i]);
            delay_us(1000); 
        }

        char received = UARTSoftware_Receive();
        UARTSoftware_Transmitt(received);
    }
}
