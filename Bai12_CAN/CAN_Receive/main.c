#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_can.h"

uint8_t dataTransmit[4];

void CAN_Clock_Configuration()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void CAN_GPIO_Configuration(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void CAN_Config()
{
    CAN_InitTypeDef CAN_InitStructure;

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = ENABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
    CAN_InitStructure.CAN_Prescaler = 6;

    CAN_Init(CAN1, &CAN_InitStructure);
}

void CAN_FilterConfiguration(void) {
    CAN_FilterInitTypeDef CAN_FilterInitStructure;

    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321 << 5;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

    CAN_FilterInit(&CAN_FilterInitStructure);
}

void CAN_ReceiveData(uint8_t* data)
{
    while(CAN_MessagePending(CAN1, CAN_FIFO0) < 1); 
    CanRxMsg RxMessage;
    
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);  
    
    for(int i = 0; i < RxMessage.DLC; i++) {
        data[i] = RxMessage.Data[i];  
    }
    CAN_FIFORelease(CAN1, CAN_FIFO0);  
}


int main()
{
    CAN_Clock_Configuration();
    CAN_GPIO_Configuration();
    CAN_Config();
    CAN_FilterConfiguration();
    
    while(1) 
    {
        CAN_ReceiveData(dataTransmit);
    }
    
    return 0;
}
