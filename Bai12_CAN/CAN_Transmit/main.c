#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_can.h"              // Keil::Device:StdPeriph Drivers:CAN

/**
 * @brief Configure the clocks for CAN and GPIO modules
 */	
 
void CAN_Clock_Configuration(void)
{
	/* Enable clock for CAN1 on APB1 bus */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	/* Enable clock for GPIOA on APB2 bus */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}


/**
 * @brief Configure GPIOA pins for CAN functionaly.
 */

void CAN_GPIO_Configuration(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    /* Configure PA11 (CAN_RX) as Input Pull-Up */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA12 (CAN_TX) as Alternate Function Push-Pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/** 
 * @brief Configures the CAN module for transmission and reception.
 */
void CAN_Config(void)
{
	CAN_InitTypeDef CAN_InitStructure;
	/* Initialize CAN configuration parameters */
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
	
	/* Initialize CAN peripheral with the configuration */
	CAN_Init(CAN1,&CAN_InitStructure);
}


/** 
 * @brief Configures the CAN filter for message reception.
 */
void CAN_FilterConfiguration(void) 
{
    CAN_FilterInitTypeDef CAN_FilterInitStructure;

    /* Configure the CAN Filter parameters */
    CAN_FilterInitStructure.CAN_FilterNumber = 0; /* Select Filter Bank 0 */
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask; /**< Set filter mode to Mask Mode */
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; /**< Use 32-bit filter */
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321 << 5; /**< Set Standard ID (Left-shift by 5) */
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0; /**< Set mask to compare only the first 11 bits */
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0; /**< Assign messages to FIFO0 */
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; /**< Enable the filter */

    /* Initialize the CAN filter */
    CAN_FilterInit(&CAN_FilterInitStructure);
}


/** 
 * @brief Transmits data over the CAN bus.
 * @param[in] data: Pointer to the data array to be transmitted.
 * @param[in] length: Length of the data to be transmitted (max 8 bytes).
 */
void CAN_TransmitData(uint8_t* data, uint8_t length) 
{
    CanTxMsg TxMessage;

    /* Configure the CAN message parameters */
    TxMessage.StdId = 0x321; /**< Set Standard Identifier */
    TxMessage.RTR = CAN_RTR_DATA; /**< Data Frame */
    TxMessage.IDE = CAN_ID_STD; /**< Standard ID */
    TxMessage.DLC = length; /**< Data Length Code */

    /* Copy the data to the CAN message */
    for (int i = 0; i < length; i++) 
    {
        TxMessage.Data[i] = data[i];
    }

    /* Transmit the CAN message */
    uint8_t mailbox = CAN_Transmit(CAN1, &TxMessage); 

    /* Wait until the message is successfully transmitted */
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
