#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // GPIO driver for STM32F10x
#include "stm32f10x_rcc.h"              // RCC driver for clock configuration
#include "stm32f10x_spi.h"              // SPI driver for communication
#include "stm32f10x_tim.h"              // Timer driver for delays

#define SPI_SCK_Pin     GPIO_Pin_0
#define SPI_MISO_Pin    GPIO_Pin_1
#define SPI_MOSI_Pin    GPIO_Pin_2
#define SPI_CS_Pin      GPIO_Pin_3
#define SPI_GPIO        GPIOA
#define SPI_RCC         RCC_APB2Periph_GPIOA

void delay_ms(uint32_t time);            


void RCC_Config(){
    RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);           		
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  
}


void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin | SPI_CS_Pin; // Pins for SCK, MOSI, CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                       // Output mode
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      // Set speed to 50 MHz
    GPIO_Init(SPI_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;           								 // Pin for MISO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 								 // Input mode (floating)
    GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}

// Configure Timer for delay function
void TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // Set clock division
    TIM_InitStruct.TIM_Prescaler = 7200 - 1;              // Set prescaler to 7200 for 0.1 ms resolution
    TIM_InitStruct.TIM_Period = 0xFFFF;                   // Set maximum period
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // Count up mode

    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);              // Initialize TIM2 with configuration
    TIM_Cmd(TIM2, ENABLE);                                // Start TIM2
}

void delay_ms(uint32_t time)
{
    TIM_SetCounter(TIM2, 0);                           
    while (TIM_GetCounter(TIM2) < time * 10) {}         
}

void Clock(){
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);       // Set SCK high
    delay_ms(1);
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);     // Set SCK low
    delay_ms(1);
}

void SPI_init(){
    GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);     // Reset SCK
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);        // Set CS high (inactive)
    GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);    // Reset MISO
    GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);    // Reset MOSI
}

void SPI_Master_Transmit(uint8_t u8Data){    
    uint8_t u8Mask = 0x80;                               // Bit mask for MSB
    uint8_t tempData;
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);      // Start frame (CS low)
    delay_ms(1);

    for(int i = 0; i < 8; i++){
        tempData = u8Data & u8Mask;                      // Mask to get each bit
        if(tempData){                                    // Set or reset MOSI based on bit value
            GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
            delay_ms(1);
        } else {
            GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
            delay_ms(1);
        }
        u8Data = u8Data << 1;                            // Shift data left for next bit
        Clock();                                         // Generate clock pulse
    }
    GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);        // Stop frame (CS high)
    delay_ms(1);
}

uint8_t DataTrans[] = {1, 2, 3, 4, 5, 6, 7, 8};        

int main(){
    RCC_Config();           
    GPIO_Config();           
    TIM_Config();            
    SPI_init();             

    while(1){    
        for(int i = 0; i < 8; i++){
            SPI_Master_Transmit(DataTrans[i]);            
            delay_ms(1000);                               
        }
    }
}


