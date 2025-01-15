#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_can.h"              // Keil::Device:StdPeriph Drivers:CAN

void CAN_Clock_Configuration()
{
	/* Active Clock for CAN1 and GPIOA */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void CAN_GPIO_Configuration(void) 
	{
    GPIO_InitTypeDef GPIO_InitStructure;

    // configure PA11 (CAN RX) is Input Pull-up
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // configure PA12 (CAN TX) is Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
	
void CAN_Config()
{
	CAN_InitTypeDef CAN_InitStructure;
	
	CAN_InitStructure.CAN_TTCM = DISABLE; /**< Time Trigger Communication Mode */
	CAN_InitStructure.CAN_ABOM = ENABLE; /**< Automatic Bus-Off Management */
	CAN_InitStructure.CAN_AWUM = ENABLE; /**< Automatic Wake-up Mode */
	CAN_InitStructure.CAN_NART = DISABLE; /**< No Automatic Retransmisstion */
	CAN_InitStructure.CAN_RFLM = DISABLE; /**< Receive FIFO Locked Mode */
	CAN_InitStructure.CAN_TXFP = DISABLE; /**< Transmit FIFO Priority */
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /**< CAN mode : Normal */
	
	// Configure Bit timing
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; /**< Synchronization Jump Width = 1 time quanta */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq; /**< Bit segment 1 = 6 time quanta */
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq; /**< Bit segment 2 = 8 time quanta */
	CAN_InitStructure.CAN_Prescaler = 6;	/**< Baudrate 36MHz / Prescaler */
	/***************************************
	* Bit Rate = Can_Clock / (Prescaler * (Synchronization Segment + BS1 + BS2)) (bit per second)
	*	Bit Time = (Prescaler * (Synchronization Segment + BS1 + BS2)) / CAN_Clock	(uS)
	************************************* */
	CAN_Init(CAN1,&CAN_InitStructure);
}

void CAN_FilterConfiguration(void) {
    CAN_FilterInitTypeDef CAN_FilterInitStructure;

    CAN_FilterInitStructure.CAN_FilterNumber = 0; /* Number of filter */
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321 << 5;  // Standard ID 0x321
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;  // Mask compare with 11-bit ID
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;  // Push in FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

    CAN_FilterInit(&CAN_FilterInitStructure);
}

void CAN_TransmitData(uint8_t* data, uint8_t length) {
    CanTxMsg TxMessage;

    TxMessage.StdId = 0x321;  
    TxMessage.RTR = CAN_RTR_DATA;  
    TxMessage.IDE = CAN_ID_STD;  
    TxMessage.DLC = length; 

    for (int i = 0; i < length; i++) {
        TxMessage.Data[i] = data[i];
    }

    uint8_t mailbox = CAN_Transmit(CAN1, &TxMessage); 

    while (CAN_TransmitStatus(CAN1, mailbox) != CAN_TxStatus_Ok);
}

uint8_t dataTransmit[] = {0x10,0x20,0x30,0x40};
 
int main()
{
	CAN_Clock_Configuration();
	CAN_GPIO_Configuration();
	CAN_Config();
	CAN_TransmitData(dataTransmit,4);
	
	return 0;
}