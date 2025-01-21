#ifndef SPI_HW_H
#define SPI_HW_H

#include "stm32f10x_spi.h"	/* Thư viện chuẩn của STM32F103C8 */
#include "stm32f10x_rcc.h"	/* Thư viện chuẩn của STM32F103C8 */
#include "stm32f10x_gpio.h"	/* Thư viện chuẩn của STM32F103C8 */

/*************************************************************
 * @brief Định nghĩa các trạng thái của NSS (Select Slave)
 ************************************************************* */
typedef enum{
    SPI_NSS_LOW = 0,    /**<Kéo chân NSS xuống thấp (kích hoạt chọn Slave) */
    SPI_NSS_HIGH = 1    /**<Kéo chân NSS lên cao (giải phóng Slave) */
} Spi_NssStateType;

/*************************************************************
 * @brief Định nghĩa các giá trị cấu hình SPI
 ************************************************************* */

// Các giá trị BaudRate Prescaler cho SPI (giảm xung nhịp từ clock nguồn)
#define SPI_BRatePrescaler_2     SPI_BaudRatePrescaler_2     /**< Tốc độ baud của clock nguồn / 2 */
#define SPI_BRatePrescaler_4     SPI_BaudRatePrescaler_4     /**< Tốc độ baud của clock nguồn / 4 */
#define SPI_BRatePrescaler_8     SPI_BaudRatePrescaler_8     /**< Tốc độ baud của clock nguồn / 8 */
#define SPI_BRatePrescaler_16    SPI_BaudRatePrescaler_16    /**< Tốc độ baud của clock nguồn / 16 */
#define SPI_BRatePrescaler_32    SPI_BaudRatePrescaler_32    /**< Tốc độ baud của clock nguồn / 32 */
#define SPI_BRatePrescaler_64    SPI_BaudRatePrescaler_64    /**< Tốc độ baud của clock nguồn / 64 */
#define SPI_BRatePrescaler_128   SPI_BaudRatePrescaler_128   /**< Tốc độ baud của clock nguồn / 128 */
#define SPI_BRatePrescaler_256   SPI_BaudRatePrescaler_256   /**< Tốc độ baud của clock nguồn / 256 */

// Các giá trị cấu hình Clock Polarity (CPOL)
#define SPI_CPOL_LOW     SPI_CPOL_Low      /**< Clock ở trạng thái thấp khi nhàn rỗi */
#define SPI_CPOL_HIGH   SPI_CPOL_High     /**< Clock ở trạng thái cao khi nhàn rỗi */

// Các giá trị cấu hình Clock Phase (CPHA)
#define SPI_CPHA_1EDGE    SPI_CPHA_1Edge    /**< Dữ liệu được chốt vào cạnh đầu tiên */
#define SPI_CPHA_2EDGE    SPI_CPHA_2Edge    /**< Dữ liệu được chốt vào cạnh thứ hai */

// Các giá trị Mode SPI
#define SPI_MODE_MASTER   SPI_Mode_Master   /**< Mode Master */
#define SPI_MODE_SLAVE    SPI_Mode_Slave    /**< Mode Slave */

// Các giá trị cấu hình NSS (Slave Select)
#define SPI_NSS_SOFT     SPI_NSS_Soft      /**< NSS quản lý bằng phần mềm */
#define SPI_NSS_HARD     SPI_NSS_Hard      /**< NSS quản lý bằng phần cứng */

// Các giá trị cấu hình Data Size (Số bit dữ liệu)
#define SPI_DATASIZE_8b   SPI_DataSize_8b   /**< Dữ liệu 8-bit */
#define SPI_DATASIZE_16b  SPI_DataSize_16b  /**< Dữ liệu 16-bit */

/*************************************************************
 * @brief Định nghĩa xung nhịp cho SPI1 và SPI2
 ************************************************************* */
#define SPI1_CLOCK_RCC  RCC_APB2Periph_SPI1
#define SPI2_CLOCK_RCC  RCC_APB1Periph_SPI2

/**
 * @section Định nghĩa cổng và chân GPIO cho SPI1
 */
#define SPI1_GPIO_RCC   RCC_APB2Periph_GPIOA     /**< Xung nhịp cho GPIOA (SPI1) */
#define SPI1_GPIO_PORT  GPIOA                    /**< Cổng GPIOA */
#define SPI1_SCK_PIN    GPIO_Pin_5               /**< Chân SCK của SPI1 (PA5) */
#define SPI1_MISO_PIN   GPIO_Pin_6               /**< Chân MISO của SPI1 (PA6) */
#define SPI1_MOSI_PIN   GPIO_Pin_7               /**< Chân MOSI của SPI1 (PA7) */
#define SPI1_NSS_PIN    GPIO_Pin_4               /**< Chân NSS của SPI1 (PA4) */

/**
 * @section Định nghĩa cổng và chân GPIO cho SPI2
 */
#define SPI2_GPIO_RCC   RCC_APB2Periph_GPIOB     /**< Xung nhịp cho GPIOB (SPI2) */
#define SPI2_GPIO_PORT  GPIOB                    /**< Cổng GPIOB */
#define SPI2_SCK_PIN    GPIO_Pin_13              /**< Chân SCK của SPI2 (PB13) */
#define SPI2_MISO_PIN   GPIO_Pin_14              /**< Chân MISO của SPI2 (PB14) */
#define SPI2_MOSI_PIN   GPIO_Pin_15              /**< Chân MOSI của SPI2 (PB15) */
#define SPI2_NSS_PIN    GPIO_Pin_12              /**< Chân NSS của SPI2 (PB12) */


/***************************************************************
 * @brief Macro để bật xung nhịp và cấu hình GPIO cho SPI
 * @param[in] SPI_CHANNEL   SPI kênh (SPI1/SPI2)
 * @param[in] RCC_APB       Xung nhịp cho SPI (RCC_APB1/RCC_APB2)
 * @param[in] GPIO_RCC      Xung nhịp cho GPIO
 * @param[in] GPIO_PORT     Cổng GPIO
 * @param[in] GPIO_PINS     Các chân GPIO
 ***************************************************************/
#define SETUP_SPI_GPIO(SPI_CHANNEL, RCC_APB, GPIO_RCC, GPIO_PORT, GPIO_PINS)\
    do {                                                                    \
        /* Bật xung nhịp cho SPI và GPIO */ 																\
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);																																		\
        if ((SPI_CHANNEL) == SPI1) {                                        \
            RCC_APB2PeriphClockCmd((RCC_APB), ENABLE);                      \
        } else {                                                            \
            RCC_APB1PeriphClockCmd((RCC_APB), ENABLE);                      \
        }                                                                   \
        RCC_APB2PeriphClockCmd((GPIO_RCC), ENABLE);                         \
                                                                            \
        /* Cấu hình GPIO cho SPI */                                         \
        GPIO_InitTypeDef GPIO_InitStruct;                                   \
        GPIO_InitStruct.GPIO_Pin = (GPIO_PINS);                             \
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                        \
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                      \
        GPIO_Init((GPIO_PORT), &GPIO_InitStruct);                           \
    } while (0)


		
/*************************************************************
 * @brief Khởi tạo phần cứng cho SPI1
 *************************************************************/
static inline void Spi_Hw_Init_SPI1(void) {
    /* Bật clock và cấu hình GPIO cho SPI1 */
    SETUP_SPI_GPIO(SPI1, RCC_APB2Periph_SPI1, SPI1_GPIO_RCC, SPI1_GPIO_PORT,
                   SPI1_SCK_PIN | SPI1_MISO_PIN | SPI1_MOSI_PIN);

    /* Cấu hình NSS nếu cần */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = SPI1_NSS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI1_GPIO_PORT, &GPIO_InitStruct);
}


/*************************************************************
 * @brief Khởi tạo phần cứng cho SPI2
 *************************************************************/
static inline void Spi_Hw_Init_SPI2(void) {
    /* Bật clock và cấu hình GPIO cho SPI2 */
    SETUP_SPI_GPIO(SPI2, RCC_APB1Periph_SPI2, SPI2_GPIO_RCC, SPI2_GPIO_PORT,
                   SPI2_SCK_PIN | SPI2_MISO_PIN | SPI2_MOSI_PIN);

    /* Cấu hình NSS nếu cần */
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = SPI2_NSS_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI2_GPIO_PORT, &GPIO_InitStruct);
}


/*************************************************************
 * @brief Bật SPI1 
 *************************************************************/
static inline void Spi_Hw_Enable_SPI1(void){
    SPI_Cmd(SPI1, ENABLE);  // Kích hoạt SPI1
}

/*************************************************************
 * @brief Bật SPI2
 *************************************************************/
static inline void Spi_Hw_Enable_SPI2(void){
    SPI_Cmd(SPI2, ENABLE);  // Kích hoạt SPI2
}

/*************************************************************
 * @brief Tắt SPI1 
 *************************************************************/
static inline void Spi_Hw_Disable_SPI1(void){
    SPI_Cmd(SPI1, DISABLE); // Tắt SPI1
}

/*************************************************************
 * @brief Tắt SPI2
 *************************************************************/
static inline void Spi_Hw_Disable_SPI2(void){
    SPI_Cmd(SPI2, DISABLE); // Tắt SPI2
}

/*************************************************************
 * @brief Tắt xung nhịp cho SPI1 
 *************************************************************/
static inline void Spi_Hw_DisableClock_SPI1(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);
}

/*************************************************************
 * @brief Tắt xung nhịp cho SPI2
 *************************************************************/
static inline void Spi_Hw_DisableClock_SPI2(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);
}

/*************************************************************
 * @brief Hàm hủy phần cứng SPI1
 *************************************************************/
static inline void Spi_Hw_DeInit_SPI1(void){
    // Tắt SPI1
    SPI_Cmd(SPI1, DISABLE);         // Tắt SPI1
    Spi_Hw_DisableClock_SPI1();     // Tắt xung nhịp cho SPI1
}

/*************************************************************
 * @brief Hàm hủy phần cứng SPI2
 *************************************************************/
static inline void Spi_Hw_DeInit_SPI2(void){
    // Tắt SPI2
    SPI_Cmd(SPI2, DISABLE);         // Tắt SPI2
    Spi_Hw_DisableClock_SPI2();     // Tắt xung nhịp cho SPI2
}

/*************************************************************
 * @brief Đợi cho đến khi bộ truyền của SPI1 trống
 *************************************************************/
static inline void Spi_Hw_WaitTransmitBufferEmpty_SPI1(void){
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);  /* Chờ bộ đệm trống */
}

/*************************************************************
 * @brief Gửi dữ liệu qua SPI1
 * @param[in] DataBufferPtr Con trỏ tới dữ liệu cần gửi
 *************************************************************/
static inline void Spi_I2S_SendData_SPI1(const Spi_DataBufferType* DataBufferPtr){
    SPI_I2S_SendData(SPI1, *DataBufferPtr);     /* Gửi dữ liệu qua SPI1 */
}

/*************************************************************
 * @brief Đợi cho đến khi bộ truyền của SPI2 trống
 *************************************************************/
static inline void Spi_Hw_WaitTransmitBufferEmpty_SPI2(void){
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);  /* Chờ bộ đệm trống */
}

/*************************************************************
 * @brief Gửi dữ liệu qua SPI2
 * @param[in] DataBufferPtr Con trỏ tới dữ liệu cần gửi
 *************************************************************/
static inline void Spi_I2S_SendData_SPI2(const Spi_DataBufferType* DataBufferPtr){
    SPI_I2S_SendData(SPI2, *DataBufferPtr);     /* Gửi dữ liệu qua SPI2 */
}


/*************************************************************
 * @brief Chờ cho đến khi có dữ liệu nhận được từ SPI1 (dùng cờ RXNE)
 * @note  Hàm này sẽ chờ trong vòng lặp, cần cẩn thận khi sử dụng để tránh treo hệ thống.
 *************************************************************/
static inline void Spi_Hw_WaitReceiveBufferFull_SPI1(void) {
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {}
}


/*************************************************************
 * @brief Chờ cho đến khi có dữ liệu nhận được từ SPI2 (dùng cờ RXNE)
 * @note  Hàm này sẽ chờ trong vòng lặp, cần cẩn thận khi sử dụng để tránh treo hệ thống.
 *************************************************************/
static inline void Spi_Hw_WaitReceiveBufferFull_SPI2(void) {
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) {}
}

/*************************************************************
 * @brief Đọc dữ liệu nhận được từ SPI1
 * @return Dữ liệu từ bộ đệm nhận của SPI1
 *************************************************************/
static inline Spi_DataBufferType Spi_I2S_ReceiveData_SPI1(void) {
    return (Spi_DataBufferType)SPI_I2S_ReceiveData(SPI1);
}


/*************************************************************
 * @brief Đọc dữ liệu nhận được từ SPI2
 * @return Dữ liệu từ bộ đệm nhận của SPI2
 *************************************************************/
static inline Spi_DataBufferType Spi_I2S_ReceiveData_SPI2(void) {
    return (Spi_DataBufferType)SPI_I2S_ReceiveData(SPI2);
}


/******************************************************************
* @brief Kiểm tra trạng thái của kênh SPI1
* @details Hàm này sử dụng cờ trạng thái BSY để kiểm tra xem SPI1
*          đang bận hay sẵn sàng.
* @return Trạng thái của SPI1: SPI_BUSY hoặc SPI_IDLE
******************************************************************/
static inline Spi_StatusType Spi_Hw_CheckStatus_SPI1(void) {
		// Kiểm tra cờ trạng thái BSY của SPI1
		if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
				return SPI_BUSY;
		}
		
		// Nếu cờ BSY không được SET, trả về SPI_IDLE
    return SPI_IDLE; /* SPI1 sẵn sàng */
}

/******************************************************************
* @brief Kiểm tra trạng thái của kênh SPI2
* @details Hàm này sử dụng cờ trạng thái BSY để kiểm tra xem SPI2
*          đang bận hay sẵn sàng.
* @return Trạng thái của SPI2: SPI_BUSY hoặc SPI_IDLE
******************************************************************/
static inline Spi_StatusType Spi_Hw_CheckStatus_SPI2(void) {
    // Kiểm tra cờ trạng thái BSY của SPI2
    if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_BUSY; /* SPI2 đang bận */
    }

    // Nếu cờ BSY không được SET, trả về SPI_IDLE
    return SPI_IDLE; /* SPI2 sẵn sàng */
}


/******************************************************************
* @brief Kiểm tra trạng thái của job trên kênh SPI1
* @details Hàm này kiểm tra trạng thái của job đang được thực thi trên SPI1
*          dựa vào các cờ trạng thái của phần cứng SPI.
* @return Trạng thái của job:
*         - SPI_JOB_OK: Job hoàn thành.
*         - SPI_JOB_PENDING: Job đang được xử lý.
*         - SPI_JOB_FAILED: Job thất bại hoặc không thực hiện được.
******************************************************************/
static inline Spi_JobResultType Spi_Hw_CheckJobStatus_SPI1(void) {
    // Kiểm tra cờ RXNE (Receive Buffer Not Empty) của SPI1
    // Nếu cờ RXNE được SET, nghĩa là dữ liệu đã được nhận xong,
    // job đã hoàn thành thành công.
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == SET) {
        return SPI_JOB_OK; // Job hoàn thành
    } 
    // Kiểm tra cờ BSY (Busy Flag) của SPI1
    // Nếu cờ BSY được SET, nghĩa là SPI1 đang bận xử lý job hiện tại,
    // job vẫn đang được thực hiện.
    else if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_JOB_PENDING; // Job đang xử lý
    } 
    // Nếu cả hai cờ RXNE và BSY đều không được SET,
    // nghĩa là job đã thất bại hoặc SPI không hoạt động.
    else {
        return SPI_JOB_FAILED; // Job thất bại
    }
}


/******************************************************************
* @brief Kiểm tra trạng thái của job trên kênh SPI2
* @details Hàm này kiểm tra trạng thái của job đang được thực thi trên SPI2
*          dựa vào các cờ trạng thái của phần cứng SPI.
* @return Trạng thái của job:
*         - SPI_JOB_OK: Job hoàn thành.
*         - SPI_JOB_PENDING: Job đang được xử lý.
*         - SPI_JOB_FAILED: Job thất bại hoặc không thực hiện được.
******************************************************************/
static inline Spi_JobResultType Spi_Hw_CheckJobStatus_SPI2(void) {
    // Kiểm tra cờ RXNE (Receive Buffer Not Empty) của SPI2
    // Nếu cờ RXNE được SET, nghĩa là dữ liệu đã được nhận xong,
    // job đã hoàn thành thành công.
    if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == SET) {
        return SPI_JOB_OK; // Job hoàn thành
    } 
    // Kiểm tra cờ BSY (Busy Flag) của SPI2
    // Nếu cờ BSY được SET, nghĩa là SPI2 đang bận xử lý job hiện tại,
    // job vẫn đang được thực hiện.
    else if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_JOB_PENDING; // Job đang xử lý
    } 
    // Nếu cả hai cờ RXNE và BSY đều không được SET,
    // nghĩa là job đã thất bại hoặc SPI không hoạt động.
    else {
        return SPI_JOB_FAILED; // Job thất bại
    }
}

/******************************************************************
* @brief Kiểm tra trạng thái của một Sequence trên SPI1
* @details Hàm này kiểm tra cờ trạng thái phần cứng để xác định 
* trạng thái hiện tại của Sequence
* @return Kết quả Sequence (SPI_SEQ_OK, SPI_SEQ_PENDING, SPI_SEQ_FAILED)
**************************************************************** */
static inline Spi_SeqResultType Spi_Hw_CheckSequenceStatus_SPI1(void) {
    // Kiểm tra nếu cờ RXNE (Receive Not Empty) được bật
    if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == SET) {
        return SPI_SEQ_OK; // Sequence hoàn thành
    } 
    // Kiểm tra nếu cờ BSY (Busy) đang bật
    else if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_SEQ_PENDING; // Sequence đang xử lý
    } 
    // Các trường hợp khác, coi như Sequence thất bại
    else {
        return SPI_SEQ_FAILED; // Sequence thất bại
    }
}


/******************************************************************
* @brief Kiểm tra trạng thái của một Sequence trên SPI2
* @details Hàm này kiểm tra cờ trạng thái phần cứng để xác định 
* trạng thái hiện tại của Sequence
* @return Kết quả Sequence (SPI_SEQ_OK, SPI_SEQ_PENDING, SPI_SEQ_FAILED)
**************************************************************** */
static inline Spi_SeqResultType Spi_Hw_CheckSequenceStatus_SPI2(void) {
    // Kiểm tra nếu cờ RXNE (Receive Not Empty) được bật
    if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == SET) {
        return SPI_SEQ_OK; // Sequence hoàn thành
    } 
    // Kiểm tra nếu cờ BSY (Busy) đang bật
    else if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {
        return SPI_SEQ_PENDING; // Sequence đang xử lý
    } 
    // Các trường hợp khác, coi như Sequence thất bại
    else {
        return SPI_SEQ_FAILED; // Sequence thất bại
    }
}


///******************************************************************
//* @brief Chuyển SPI sang chế độ Polling (thăm dò)
//* @details Tắt tất cả các ngắt liên quan đến SPI và chuyển chế độ sang Polling.
//**************************************************************** */
//static inline void Spi_Hw_SetPollingMode(void) {
//    // Tắt các ngắt chính và phụ của SPI1
//    NVIC_DisableIRQ(SPI1_IRQn); 
//    NVIC_DisableIRQ(SPI1_RX_IRQn);
//    NVIC_DisableIRQ(SPI1_TX_IRQn);

//    // Tắt các ngắt chính và phụ của SPI2
//    NVIC_DisableIRQ(SPI2_IRQn); 
//    NVIC_DisableIRQ(SPI2_RX_IRQn);
//    NVIC_DisableIRQ(SPI2_TX_IRQn); 

//    // Đặt trạng thái SPI về IDLE
//    SpiS = SPI_IDLE;
//}


///******************************************************************
//* @brief Chuyển SPI sang chế độ Interrupt (ngắt)
//* @details Bật tất cả các ngắt liên quan đến SPI và chuyển chế độ sang Interrupt.
//**************************************************************** */
//static inline void Spi_Hw_InterruptMode(void) {
//    // Bật các ngắt chính và phụ của SPI1
//    NVIC_EnableIRQ(SPI1_IRQn); 
//    NVIC_EnableIRQ(SPI1_RX_IRQn);
//    NVIC_EnableIRQ(SPI1_TX_IRQn);

//    // Bật các ngắt chính và phụ của SPI2
//    NVIC_EnableIRQ(SPI2_IRQn); 
//    NVIC_EnableIRQ(SPI2_RX_IRQn);
//    NVIC_EnableIRQ(SPI2_TX_IRQn); 

//    // Đặt trạng thái SPI về IDLE
//    SpiStatus = SPI_IDLE;
//}


#endif /* SPI_HW_H */
