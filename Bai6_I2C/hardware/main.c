#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_i2c.h"              // Include I2C header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

typedef enum {
    NOT_OK = 0,
    OK = 1
} status;

typedef enum {
    NACK = 0,
    ACK = 1
} ACK_Bit;

uint8_t Data1[10] = {0x03, 0x05, 0x0E, 0xDA, 0xA6, 0x6F, 0x50, 0x00, 0x00, 0xF0};
uint8_t Data2[10] = {0x01, 0x0A, 0x19, 0x24, 0xFA, 0x10, 0x3C, 0x48, 0x59, 0x77};
uint8_t Rcv[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

void I2C_Config() {
    I2C_InitTypeDef I2C_InitStructure;

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
		I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitStructure.I2C_OwnAddress1 = 0;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  
    I2C_Init(I2C1, &I2C_InitStructure); 
    I2C_Cmd(I2C1, ENABLE);
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

status EPROM_Read(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));

    I2C_Send7bitAddress(I2C1, SlaveAddr << 1, I2C_Direction_Transmitter);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR));
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C_SendData(I2C1, (MemAddr >> 8) & 0xFF);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));
    I2C_SendData(I2C1, MemAddr & 0xFF);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));

    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));

    I2C_Send7bitAddress(I2C1, (SlaveAddr << 1) | 0x01, I2C_Direction_Receiver);
    while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR));
    (void)I2C1->SR1; 

    // Read data
    for (uint8_t i = 0; i < NumByte; ++i) {
        if (i < NumByte - 1) {
            I2C_AcknowledgeConfig(I2C1, ENABLE); // Acknowledge next byte
        } else {
            I2C_AcknowledgeConfig(I2C1, DISABLE); // Last byte not acknowledged
        }
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE)); // Wait until data received
        pData[i] = I2C_ReceiveData(I2C1); // Read data
    }

    // Send stop condition
    I2C_GenerateSTOP(I2C1, ENABLE);
    return OK;
}

status EPROM_Write(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    for (uint8_t i = 0; i < NumByte; ++i) {
        // Send start condition
        I2C_GenerateSTART(I2C1, ENABLE);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));

        // Send the device address for write
        I2C_Send7bitAddress(I2C1, SlaveAddr << 1, I2C_Direction_Transmitter);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR));
        (void)I2C1->SR1; // Clear ADDR flag

        // Send memory address
        I2C_SendData(I2C1, (MemAddr + i) >> 8);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));
        I2C_SendData(I2C1, (MemAddr + i) & 0xFF);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));

        // Send data
        I2C_SendData(I2C1, pData[i]);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));

        // Send stop condition
        I2C_GenerateSTOP(I2C1, ENABLE);
        delay_us(10000); // Delay for EEPROM write cycle
    }
    return OK;
}

int main() {
    RCC_Config();
    GPIO_Config();
    I2C_Config();

    while (EPROM_Write(0x0045, 0xA0, 10, Data1) == NOT_OK) {}
    while (EPROM_Write(0x0060, 0xA0, 10, Data2) == NOT_OK) {}

    while (1) {
        while (EPROM_Read(0x0045, 0xA0, 10, Rcv) == NOT_OK) {}
        while (EPROM_Read(0x0060, 0xA0, 10, Rcv) == NOT_OK) {}
    }
}
