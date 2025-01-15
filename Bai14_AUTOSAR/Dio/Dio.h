/***************************************************************
 * @file Dio.h
 * @brief Digital Input/Output (DIO) Driver Header File
 * @details File này chứa các quy định về kiểu dữ liệu và 
 *          khai báo các API của DIO Driver tuân thủ theo AUTOSAR.
 *          Driver này được thiết kế để điều khiển GPIO của STM32F103C8.   
 * @version 1.0
 * @author Mạnh Trọng Hải
 ****************************************************************/

#ifndef DIO_H
#define DIO_H

#include "stm32f10x_gpio.h"	    /* Thư viện chuẩn của STM32F103C8 */
#include "Std_Types.h"	        /* Dữ liệu chuẩn của AUTOSAR*/

/**************************************************
 * Macro xác định cổng GPIO và các chân GPIO dựa trên ChannelID
 **************************************************/

/* Macro xác định cổng GPIO dựa trên ChannelID */
#define DIO_GET_PORT(ChannelID) \
    (((ChannelID) < 16) ? GPIOA : \
    (((ChannelID) < 32) ? GPIOB : \
    (((ChannelID) < 48) ? GPIOC : \
    (((ChannelID) < 64) ? GPIOD : NULL))))


/*Macro xác định chân GPIO  dựa trên  ChannelID*/
#define DIO_GET_PIN(ChannelID) (1 << ((ChannelID) % 16))   /* Tính chân GPIO tương ứng */

/*************************************************************
 * Macro xác định ChannelID cho từng chân GPIO
 * @param[in] GPIOx: Cổng GPIO (GPIOA, GPIOB, GPIOC, GPIOD)
 * @param[in] Pin: Số chân (Pin) từ 0 đến 15
 *************************************************************/
#define DIO_CHANNEL(PORT_INDEX, PIN) (((PORT_INDEX) << 4) | (PIN))


/* Channel cho tất cả các chân trên GPIOA */		
#define DIO_CHANNEL_A0  DIO_CHANNEL(0, 0)   /* GPIO Pin 0 */
#define DIO_CHANNEL_A1  DIO_CHANNEL(0, 1)   /* GPIO Pin 1 */
#define DIO_CHANNEL_A2  DIO_CHANNEL(0, 2)   /* GPIO Pin 2 */
#define DIO_CHANNEL_A3  DIO_CHANNEL(0, 3)   /* GPIO Pin 3 */
#define DIO_CHANNEL_A4  DIO_CHANNEL(0, 4)   /* GPIO Pin 4 */
#define DIO_CHANNEL_A5  DIO_CHANNEL(0, 5)   /* GPIO Pin 5 */
#define DIO_CHANNEL_A6  DIO_CHANNEL(0, 6)   /* GPIO Pin 6 */
#define DIO_CHANNEL_A7  DIO_CHANNEL(0, 7)   /* GPIO Pin 7 */
#define DIO_CHANNEL_A8  DIO_CHANNEL(0, 8)   /* GPIO Pin 8 */
#define DIO_CHANNEL_A9  DIO_CHANNEL(0, 9)   /* GPIO Pin 9 */
#define DIO_CHANNEL_A10 DIO_CHANNEL(0, 10)  /* GPIO Pin 10 */
#define DIO_CHANNEL_A11 DIO_CHANNEL(0, 11)  /* GPIO Pin 11 */
#define DIO_CHANNEL_A12 DIO_CHANNEL(0, 12)  /* GPIO Pin 12 */
#define DIO_CHANNEL_A13 DIO_CHANNEL(0, 13)  /* GPIO Pin 13 */
#define DIO_CHANNEL_A14 DIO_CHANNEL(0, 14)  /* GPIO Pin 14 */
#define DIO_CHANNEL_A15 DIO_CHANNEL(0, 15)  /* GPIO Pin 15 */

/* Channel cho tất cả các chân trên GPIOB */
#define DIO_CHANNEL_B0  DIO_CHANNEL(1, 0)   /* GPIO Pin 0 */
#define DIO_CHANNEL_B1  DIO_CHANNEL(1, 1)   /* GPIO Pin 1 */
#define DIO_CHANNEL_B2  DIO_CHANNEL(1, 2)   /* GPIO Pin 2 */
#define DIO_CHANNEL_B3  DIO_CHANNEL(1, 3)   /* GPIO Pin 3 */
#define DIO_CHANNEL_B4  DIO_CHANNEL(1, 4)   /* GPIO Pin 4 */
#define DIO_CHANNEL_B5  DIO_CHANNEL(1, 5)   /* GPIO Pin 5 */
#define DIO_CHANNEL_B6  DIO_CHANNEL(1, 6)   /* GPIO Pin 6 */
#define DIO_CHANNEL_B7  DIO_CHANNEL(1, 7)   /* GPIO Pin 7 */
#define DIO_CHANNEL_B8  DIO_CHANNEL(1, 8)   /* GPIO Pin 8 */
#define DIO_CHANNEL_B9  DIO_CHANNEL(1, 9)   /* GPIO Pin 9 */
#define DIO_CHANNEL_B10 DIO_CHANNEL(1, 10)  /* GPIO Pin 10 */
#define DIO_CHANNEL_B11 DIO_CHANNEL(1, 11)  /* GPIO Pin 11 */
#define DIO_CHANNEL_B12 DIO_CHANNEL(1, 12)  /* GPIO Pin 12 */
#define DIO_CHANNEL_B13 DIO_CHANNEL(1, 13)  /* GPIO Pin 13 */
#define DIO_CHANNEL_B14 DIO_CHANNEL(1, 14)  /* GPIO Pin 14 */
#define DIO_CHANNEL_B15 DIO_CHANNEL(1, 15)  /* GPIO Pin 15 */

/* Channel cho tất cả các chân trên GPIOC */
#define DIO_CHANNEL_C0  DIO_CHANNEL(2, 0)   /* GPIO Pin 0 */
#define DIO_CHANNEL_C1  DIO_CHANNEL(2, 1)   /* GPIO Pin 1 */
#define DIO_CHANNEL_C2  DIO_CHANNEL(2, 2)   /* GPIO Pin 2 */
#define DIO_CHANNEL_C3  DIO_CHANNEL(2, 3)   /* GPIO Pin 3 */
#define DIO_CHANNEL_C4  DIO_CHANNEL(2, 4)   /* GPIO Pin 4 */
#define DIO_CHANNEL_C5  DIO_CHANNEL(2, 5)   /* GPIO Pin 5 */
#define DIO_CHANNEL_C6  DIO_CHANNEL(2, 6)   /* GPIO Pin 6 */
#define DIO_CHANNEL_C7  DIO_CHANNEL(2, 7)   /* GPIO Pin 7 */
#define DIO_CHANNEL_C8  DIO_CHANNEL(2, 8)   /* GPIO Pin 8 */
#define DIO_CHANNEL_C9  DIO_CHANNEL(2, 9)   /* GPIO Pin 9 */
#define DIO_CHANNEL_C10 DIO_CHANNEL(2, 10)  /* GPIO Pin 10 */
#define DIO_CHANNEL_C11 DIO_CHANNEL(2, 11)  /* GPIO Pin 11 */
#define DIO_CHANNEL_C12 DIO_CHANNEL(2, 12)  /* GPIO Pin 12 */
#define DIO_CHANNEL_C13 DIO_CHANNEL(2, 13)  /* GPIO Pin 13 */
#define DIO_CHANNEL_C14 DIO_CHANNEL(2, 14)  /* GPIO Pin 14 */
#define DIO_CHANNEL_C15 DIO_CHANNEL(2, 15)  /* GPIO Pin 15 */

/* Channel cho tất cả các chân trên GPIOD */
#define DIO_CHANNEL_D0  DIO_CHANNEL(3, 0)   /* GPIO Pin 0 */
#define DIO_CHANNEL_D1  DIO_CHANNEL(3, 1)   /* GPIO Pin 1 */
#define DIO_CHANNEL_D2  DIO_CHANNEL(3, 2)   /* GPIO Pin 2 */
#define DIO_CHANNEL_D3  DIO_CHANNEL(3, 3)   /* GPIO Pin 3 */
#define DIO_CHANNEL_D4  DIO_CHANNEL(3, 4)   /* GPIO Pin 4 */
#define DIO_CHANNEL_D5  DIO_CHANNEL(3, 5)   /* GPIO Pin 5 */
#define DIO_CHANNEL_D6  DIO_CHANNEL(3, 6)   /* GPIO Pin 6 */
#define DIO_CHANNEL_D7  DIO_CHANNEL(3, 7)   /* GPIO Pin 7 */
#define DIO_CHANNEL_D8  DIO_CHANNEL(3, 8)   /* GPIO Pin 8 */
#define DIO_CHANNEL_D9  DIO_CHANNEL(3, 9)   /* GPIO Pin 9 */
#define DIO_CHANNEL_D10 DIO_CHANNEL(3, 10)  /* GPIO Pin 10 */
#define DIO_CHANNEL_D11 DIO_CHANNEL(3, 11)  /* GPIO Pin 11 */
#define DIO_CHANNEL_D12 DIO_CHANNEL(3, 12)  /* GPIO Pin 12 */
#define DIO_CHANNEL_D13 DIO_CHANNEL(3, 13)  /* GPIO Pin 13 */
#define DIO_CHANNEL_D14 DIO_CHANNEL(3, 14)  /* GPIO Pin 14 */
#define DIO_CHANNEL_D15 DIO_CHANNEL(3, 15)  /* GPIO Pin 15 */


/* ============================================
 * Định nghĩa kiểu dữ liệu của DIO Driver
 * ============================================ */

/***************************************************************
 * @typedef Dio_ChannelType
 * @brief Kiểu dữ liệu cho một kênh DIO
 * @details Đây là kiểu định danh cho một chân (pin) cụ thể.
 *************************************************************** */
typedef uint8 Dio_ChannelTypes;

/***************************************************************
 * @typedef Dio_PortType
 * @brief Kiểu dữ liệu cho một cổng DIO
 * @details Đây là kiểu định danh cho một cổng (port) cụ thể.
 *************************************************************** */
typedef uint16 Dio_PortTypes;

/***************************************************************
 * @typedef Dio_LevelType
 * @brief Kiểu dữ liệu cho mức logic của một kênh DIO
 * @details Các mức logic này là HIGH(1) hoặc LOW(0)
 *************************************************************** */
typedef uint8 Dio_LevelType;

/***************************************************************
 * @typedef Dio_PortLevelType
 * @brief Kiểu dữ liệu cho mức logic của một cổng DIO
 * @details Mỗi cổng có thể chứa nhiều kênh, do đó mức logic của cổng
 *          có thể là 1 tập hợp các mức logic của nhiều kênh
 *************************************************************** */
typedef uint16 Dio_PortLevelType;

/**************************************************************
 * @struct Dio_ChannelGroupType
 * @brief Cấu trúc định nghĩa một nhóm các kênh DIO
 * @details Được sử dụng để thao tác với nhóm các kênh DIO đồng thời
 *************************************************************/
typedef struct 
{
    Dio_PortTypes port;   /**< Cổng DIO của nhóm (DIO port) */
    uint8 offset;         /**< Độ dịch của bit đầu tiên trong nhóm (bit offset) */
    uint16 mask;        /**< Mặt nạ của các kênh thuộc nhóm (bitmask cho các kênh trong nhóm) */
} Dio_ChannelGroupType;

/* =========================================================
 * Khai báo các hàm API của Driver
 * ========================================================= */
 /*********************************************************
  * @brief Đọc trạng thái của 1 kênh DIO
  * @param[in] ChannelID ID của kênh cần đọc
  * @return Trạng thái logic của kênh (STD_HIGH hoặc STD_lOW)
  ******************************************************** */
Dio_LevelType Dio_ReadChannel(Dio_ChannelTypes ChannelID);

 /*********************************************************
  * @brief Ghi trạng thái của 1 kênh DIO
  * @param[in] ChannelID ID của kênh cần ghi
  * @param[in] Level Trạng thái cần ghi vào kênh (STD_HIGH hoặc STD_lOW)
  ******************************************************** */
void Dio_WriteChannel(Dio_ChannelTypes ChannelID, Dio_LevelType Level);

 /*********************************************************
  * @brief Đọc trạng thái của 1 cổng DIO
  * @param[in] PortlID ID của cổng cần đọc
  * @return Trạng thái logic của toàn bộ cổng DIO
  ******************************************************** */
Dio_PortLevelType Dio_ReadPort(Dio_PortTypes PortID);

 /*********************************************************
  * @brief Ghi trạng thái của 1 cổng DIO
  * @param[in] PortlID ID của cổng cần ghi
  * @param[in] Level Trạng thái cần ghi vào cổng (STD_HIGH hoặc STD_lOW)
  ******************************************************** */
void Dio_WritePort(Dio_PortTypes PortID, Dio_LevelType Level);

/*********************************************************
  * @brief Đọc trạng thái của tất cả các chân trong một nhóm cổng DIO
  * @param[in] ChannelGroupIdPtr Con trỏ đến nhóm các kênh cần đọc trạng thái
  * @return Trạng thái logic của toàn bộ nhóm cổng DIO dưới dạng giá trị 16 bit,
  *         trong đó mỗi bit đại diện cho trạng thái của một chân (HIGH hoặc LOW)
  ******************************************************** */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

/*********************************************************
  * @brief Ghi trạng thái cho tất cả các chân trong một nhóm cổng DIO
  * @param[in] ChannelGroupIdPtr Con trỏ đến nhóm các kênh cần ghi trạng thái
  * @param[in] Level Trạng thái logic cần ghi cho nhóm cổng DIO (mỗi bit đại diện cho trạng thái của một chân)
  * @details Hàm này sẽ ghi trạng thái (HIGH hoặc LOW) vào từng chân trong nhóm cổng DIO
  *          dựa trên giá trị của tham số Level. Mỗi bit trong Level sẽ đại diện cho trạng thái
  *          của một chân tương ứng trong nhóm các kênh.
  ******************************************************** */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

/*********************************************************
  * @brief Lấy thông tin phiên bản của module Dio
  * @param[out] VersionInfo Con trỏ đến cấu trúc chứa thông tin phiên bản
  * @details Hàm này cung cấp thông tin về phiên bản của module Dio.
  ******************************************************** */
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);

/*********************************************************
 * @brief Hàm lập giá trị logic của một kênh DIO
 * @param[out] ChannelID ID của kênh cần lật
 * @details Hàm này lật giá trị logic của 1 chân GPIO(HIGH -> LOW và LOW -> HIGH).
 ******************************************************** */
Dio_LevelType Dio_FlipChannel(Dio_ChannelTypes ChannelID);

/*********************************************************
  * @brief Ghi trạng thái vào cổng DIO với mặt nạ (mask)
  * @param[in] PortID ID của cổng DIO cần ghi trạng thái
  * @param[in] Level Trạng thái logic cần ghi vào cổng DIO (mỗi bit đại diện cho trạng thái của một chân)
  * @param[in] Mask Mặt nạ để chỉ định những chân nào trong cổng DIO sẽ bị ảnh hưởng
  * @details Hàm này sẽ ghi trạng thái (HIGH hoặc LOW) vào các chân trong cổng DIO dựa trên tham số
  *          `Level` và `Mask`. Mỗi bit trong `Level` sẽ tương ứng với trạng thái của một chân,
  *          và chỉ những chân có bit tương ứng bằng 1 trong `Mask` sẽ bị thay đổi trạng thái.
  ******************************************************** */
void Dio_MaskedWritePort(Dio_PortTypes PortID, Dio_PortLevelType Level, Dio_PortLevelType Mask);


#endif /*DIO_H*/
