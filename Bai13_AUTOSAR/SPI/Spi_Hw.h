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
#define SPI_BaudRatePrescaler_2     SPI_BaudRatePrescaler_2     /**< Tốc độ baud của clock nguồn / 2 */
#define SPI_BaudRatePrescaler_4     SPI_BaudRatePrescaler_4     /**< Tốc độ baud của clock nguồn / 4 */
#define SPI_BaudRatePrescaler_8     SPI_BaudRatePrescaler_8     /**< Tốc độ baud của clock nguồn / 8 */
#define SPI_BaudRatePrescaler_16    SPI_BaudRatePrescaler_16    /**< Tốc độ baud của clock nguồn / 16 */
#define SPI_BaudRatePrescaler_32    SPI_BaudRatePrescaler_32    /**< Tốc độ baud của clock nguồn / 32 */
#define SPI_BaudRatePrescaler_64    SPI_BaudRatePrescaler_64    /**< Tốc độ baud của clock nguồn / 64 */
#define SPI_BaudRatePrescaler_128   SPI_BaudRatePrescaler_128   /**< Tốc độ baud của clock nguồn / 128 */
#define SPI_BaudRatePrescaler_256   SPI_BaudRatePrescaler_256   /**< Tốc độ baud của clock nguồn / 256 */

// Các giá trị cấu hình Clock Polarity (CPOL)
#define SPI_CPOL_Low      SPI_CPOL_Low      /**< Clock ở trạng thái thấp khi nhàn rỗi */
#define SPI_CPOL_High     SPI_CPOL_High     /**< Clock ở trạng thái cao khi nhàn rỗi */

// Các giá trị cấu hình Clock Phase (CPHA)
#define SPI_CPHA_1Edge    SPI_CPHA_1Edge    /**< Dữ liệu được chốt vào cạnh đầu tiên */
#define SPI_CPHA_2Edge    SPI_CPHA_2Edge    /**< Dữ liệu được chốt vào cạnh thứ hai */

// Các giá trị Mode SPI
#define SPI_MODE_MASTER   SPI_Mode_Master   /**< Mode Master */
#define SPI_MODE_SLAVE    SPI_Mode_Slave    /**< Mode Slave */

// Các giá trị cấu hình NSS (Slave Select)
#define SPI_NSS_Soft      SPI_NSS_Soft      /**< NSS quản lý bằng phần mềm */
#define SPI_NSS_Hard      SPI_NSS_Hard      /**< NSS quản lý bằng phần cứng */

// Các giá trị cấu hình Data Size (Số bit dữ liệu)
#define SPI_DATASIZE_8b   SPI_DataSize_8b   /**< Dữ liệu 8-bit */
#define SPI_DATASIZE_16b  SPI_DataSize_16b  /**< Dữ liệu 16-bit */

/*************************************************************
 * @brief Định nghĩa xung nhịp cho SPI1 và SPI2
 ************************************************************* */
#define SPI1_CLOCK_RCC  RCC_APB2Periph_SPI1
#define SPI2_CLOCK_RCC  RCC_APB1Periph_SPI2

/*************************************************************
 * @brief Khởi tạo phần cứng cho SPI1
 *************************************************************/
static inline void Spi_HW_Init_SPI1(void){
    /* Bật clock và cấu hình GPIO cho SPI1 */
    SETUP_SPI_GPIO(SPI1, SPI1_CLOCK_RCC, SPI1_GPIO_RCC, SPI1_GPIO_PORT,
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
static inline void Spi_HW_Init_SPI2(void){
    /* Bật clock và cấu hình GPIO cho SPI2 */
    SETUP_SPI_GPIO(SPI2, SPI2_CLOCK_RCC, SPI2_GPIO_RCC, SPI2_GPIO_PORT,
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

#endif /* SPI_HW_H */