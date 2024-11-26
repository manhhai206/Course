#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

#define I2C_SCL     GPIO_Pin_6
#define I2C_SDA     GPIO_Pin_7
#define I2C_GPIO    GPIOB

#define WRITE_SDA_0 GPIO_ResetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SDA_1 GPIO_SetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SCL_0 GPIO_ResetBits(I2C_GPIO, I2C_SCL)
#define WRITE_SCL_1 GPIO_SetBits(I2C_GPIO, I2C_SCL)
#define READ_SDA_VAL GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)

typedef enum {
    NOT_OK = 0,
    OK = 1
} status;

typedef enum {
    NACK = 0,
    ACK = 1
} ACK_Bit;

void delay_us(uint32_t time);

void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = I2C_SDA | I2C_SCL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
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

void I2C_Config() {
    WRITE_SDA_1;
    delay_us(1);
    WRITE_SCL_1;
    delay_us(1);
}

void I2C_Start() {
    WRITE_SDA_1;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    WRITE_SDA_0;
    delay_us(3);
    WRITE_SCL_0;
    delay_us(3);
}

void I2C_Stop() {
    WRITE_SDA_0;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    WRITE_SDA_1;
    delay_us(3);
}

status I2C_Write(uint8_t u8Data) {
	
    status stRet;
    for (int i = 0; i < 8; i++) {
        if (u8Data & 0x80) {
            WRITE_SDA_1;
        } else {
            WRITE_SDA_0;
        }
        delay_us(3);
				
        WRITE_SCL_1;
        delay_us(5);
        WRITE_SCL_0;
        delay_us(5);
        u8Data <<= 1;
    }

    WRITE_SDA_1;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    
    if (READ_SDA_VAL) {
        stRet = NOT_OK;
    } else {
        stRet = OK;
    }
    delay_us(2);
    WRITE_SCL_0;
    delay_us(5);
    
    return stRet;
}

uint8_t I2C_Read(ACK_Bit _ACK) {
    uint8_t u8Ret = 0x00;
	
    WRITE_SDA_1;
    delay_us(1);
	
    for (int i = 0; i < 8; ++i) {
        u8Ret <<= 1;
        WRITE_SCL_1;
        delay_us(3);
        if (READ_SDA_VAL) {
            u8Ret |= 0x01;
        }
        delay_us(2);
        WRITE_SCL_0;
        delay_us(5);
    }

    if (_ACK) {
        WRITE_SDA_0;
    } else {
        WRITE_SDA_1;
    }
    delay_us(1);
		
    WRITE_SCL_1;
    delay_us(5);
    WRITE_SCL_0;
    delay_us(5);
		
    return u8Ret;
}

status EPROM_Read(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    uint8_t i;
	
    I2C_Start();
    if (I2C_Write(SlaveAddr << 1) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
    if (I2C_Write(MemAddr >> 8) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
    if (I2C_Write(MemAddr) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
		
		I2C_Start();
    if (I2C_Write((SlaveAddr << 1)|1) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }		
		
    for (i = 0; i < NumByte - 1; ++i) {
        pData[i] = I2C_Read(ACK);
    }
    pData[i] = I2C_Read(NACK);
    I2C_Stop();
    return OK;
}

status EPROM_Write(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    uint8_t i;
	
    for (i = 0; i < NumByte; ++i) {
        I2C_Start();
        if (I2C_Write(SlaveAddr << 1) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        if (I2C_Write((MemAddr + i) >> 8) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        if (I2C_Write(MemAddr + i) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        if (I2C_Write(pData[i]) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        I2C_Stop();
        delay_us(10000); 
    }
    return OK;
}

uint8_t Data1[10] = {0x03, 0x05, 0x0E, 0xDA, 0xA6, 0x6F, 0x50, 0x00, 0x00, 0xF0};
uint8_t Data2[10] = {0x01, 0x0A, 0x19, 0x24, 0xFA, 0x10, 0x3C, 0x48, 0x59, 0x77};
uint8_t Rcv[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

int main() {
    RCC_Config();
    TIM_Config();
    GPIO_Config();
    I2C_Config();

    while (EPROM_Write(0x0045, 0x50, 10, Data1) == NOT_OK) {}
		while (EPROM_Write(0x0060, 0x50, 10, Data2) == NOT_OK) {}

    while (1) {
        while (EPROM_Read(0x0045, 0x50, 10, Rcv) == NOT_OK) {}
				while (EPROM_Read(0x0060, 0x50, 10, Rcv) == NOT_OK) {}
    }
}
