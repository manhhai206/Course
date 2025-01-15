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
 * @brief Receives data from the CAN bus via FIFO0
 * 
 * @details This function waits for a CAN message in FIFO0, 
 *          retrieves it, and stores its payload in the provided buffer.
 */
void CanIf_ReceiveData(uint8* DataPtr)
{
    while (CAN_MessagePending(CAN1, CAN_FIFO0) < 1) {
        /* Ensures a message is available before proceeding */
    }

    /* Create a temporary structure to store the received CAN message */
    CanRxMsg RxMessage;

    /* Retrieve the message from FIFO0 */
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

    /* Copy the received payload into the provided buffer */
    for (uint8 i = 0; i < RxMessage.DLC; i++) {
        DataPtr[i] = RxMessage.Data[i];
    }

    /* Release the FIFO after reading the message */
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
