#include "stm32f10x.h"                
#include "stm32f10x_rcc.h"              
#include "stm32f10x_gpio.h"            
#include "stm32f10x_tim.h"             

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA

#define BRateTime 104  // Adjust this for accurate baud rate timing 9600

typedef enum {
    Parity_Mode_NONE,
    Parity_Mode_ODD,
    Parity_Mode_EVEN
} Parity_Mode;

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
				// Neu bit 1 chan => thêm 1; neu le => thêm 0
        case Parity_Mode_ODD:
            return (data << 1) | (count % 2 ? 1 : 0);
        case Parity_Mode_EVEN:
            return (data << 1) | (count % 2 ? 0 : 1);
        default:
            return data;
    }
}

uint8_t Parity_Check(uint8_t data, Parity_Mode Mode) {
    uint8_t count = 0;
    for (int i = 0; i < 8; i++) {
        if (data & 0x01) {
            count++;
        }
        data >>= 1;
    }
    switch (Mode) {
        case Parity_Mode_NONE:
            return 1;
        case Parity_Mode_ODD:
            return (count % 2) == 1;
        case Parity_Mode_EVEN:
            return (count % 2) == 0;
        default:
            return 0;
    }
}

void UARTSoftware_Transmitt(char c, Parity_Mode mode) {
    uint16_t data_with_parity = Parity_Generate(c, mode);

    // Start bit
    GPIO_ResetBits(GPIOA, TX_Pin);
    clock();

    // Send each bit, including parity bit if set
    for (int i = 0; i < 9; i++) {
        if (data_with_parity & (1 << i)) {
            GPIO_SetBits(GPIOA, TX_Pin);
        } else {
            GPIO_ResetBits(GPIOA, TX_Pin);
        }
        clock();
    }

    // Stop bit
    GPIO_SetBits(GPIOA, TX_Pin);
    clock();
}

char UARTSoftware_Receive(Parity_Mode mode) {
    char c = 0;

    // Wait for start bit
    while (GPIO_ReadInputDataBit(GPIOA, RX_Pin) == 1);
    delay_us(BRateTime + BRateTime / 2);
    // Receive each data bit (8 bits + 1 parity)
    for (int i = 0; i < 8; i++) {
        if (GPIO_ReadInputDataBit(GPIOA, RX_Pin)) {
            c |= (1 << i);
        }
        clock();
    }
    // Read parity bit
    uint8_t parity_bit = GPIO_ReadInputDataBit(GPIOA, RX_Pin);
    clock();
    // Stop bit 
    delay_us(BRateTime / 2);
    // Check parity
    if (mode != Parity_Mode_NONE) {
        uint8_t data_with_parity = (c << 1) | parity_bit;
        if (!Parity_Check(data_with_parity, mode)) {
            return -1;
        }
    }
    return c;
}

uint8_t data[6] = {'h', 'a', 'i','2' ,'0' ,'6'};

int main() {
    RCC_Config();
    GPIO_Config();
    TIM_Config();

    Parity_Mode parity_mode = Parity_Mode_NONE; 
    for (int i = 0; i < 6; i++) {
        UARTSoftware_Transmitt(data[i], parity_mode);
        delay_us(1000);
    }

    while (1) {
    }
}
