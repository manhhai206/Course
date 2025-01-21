#ifndef SPI_TYPES_H
#define SPI_TYPES_H

#include "Std_Types.h"



/*********************************************************
 * @typedef 8.2.2 Spi_StatusType
 * @brief Trạng thái của SPI Handle/Driver
 * @details Xác định trạng thái hiện tại của SPI Handle/Driver,
 *           cho biết SPI đang ở trạng thái nào.
 ******************************************************** */
typedef enum{
    SPI_UNINIT = 0x00,        /* SPI chưa được khởi tạo*/
    SPI_IDLE = 0x01,          /* SPI đang nhàn rỗi*/
    SPI_BUSY = 0x02           /* SPI đang bận */
} Spi_StatusType;


/*********************************************************
 * @typedef 8.2.3 Spi_JobResultType
 * @brief Kết quả của một Job SPI
 * @details Trạng thái hoàn thành của một job SPI, cho 
 *          biết là thành công hay không.
 ******************************************************** */
typedef enum{
    SPI_JOB_OK = 0x00,          /* Job hoàn toàn thành công*/
    SPI_JOB_PENDING = 0x01,     /* Job đang chờ xử lý*/
    SPI_JOB_FAILED = 0x02,     /* Job thất bại */
    SPI_JOB_QUEUE = 0x03      /* Job đang đợi trong hàng đợi*/
} Spi_JobResultType;


/*********************************************************
 * @typedef 8.2.4 Spi_SeqResultType
 * @brief Kết quả của một Sequency SPI
 * @details Trạng thái hoàn thành của một sequence SPI, cho 
 *          biết là đã xong hay chưa
 ******************************************************** */
typedef enum{
    SPI_SEQ_OK = 0x00,         /* Seq hoàn toàn thành công*/
    SPI_SEQ_PENDING = 0x01,     /* Seq đang chờ */
    SPI_SEQ_FAILED = 0x02,      /* Seq thất bại */
    SPI_SEQ_CANCELED = 0x03,    /* Seq bị hủy */    
} Spi_SeqResultType;


/*********************************************************
 * @typedef 8.2.5 Spi_DataBufferType
 * @brief Kiểu dữ liệu buffer chứa phần tử dữ liệu SPI
 * @details Kiểu dữ liệu được sử dụng để lưu trữ dữ liệu
 *          cần truyền/nhận cho một kênh SPI
 ******************************************************** */
typedef uint8 Spi_DataBufferType;

/*********************************************************
 * @typedef 8.2.6 Spi_NumberOfDataType
 * @brief Kiểu dữ liệu cho số lượng phần tử dữ liệu
 * @details Xác định số lượng dữ liệu cần truyền/nhận cho một kênh SPI
 ******************************************************** */
typedef uint16 Spi_NumberOfDataType;


/*********************************************************
 * @typedef 8.2.7 Spi_ChannelType
 * @brief Kiểu dữ liệu của 1 kênh dữ liệu
 * @details Xác định kiểu dữ liệu của 1 kênh SPI
 ******************************************************** */
typedef uint8 Spi_ChannelType;


/*********************************************************
 * @typedef 8.2.8 Spi_JobType
 * @brief Kiểu dữ liệu của 1 job trong SPI
 * @details Xác định kiểu dữ liệu của 1 job
 ******************************************************** */
typedef uint16 Spi_JobType;


/*********************************************************
 * @typedef  8.2.9 Spi_SequenceType
 * @brief Kiểu dữ liệu của 1 sequence trong SPI
 * @details Xác định kiểu dữ liệu của 1 sequence
 ******************************************************** */
typedef uint8 Spi_SequenceType;


/*********************************************************
 * @typedef 8.2.10 Spi_HWUnitType
 * @brief Xác định kiểu ngoại vi của (SPI) (SPI1 = 0, SPI2 =1)
 * @details Xác định kiểu ngoại vi
 ******************************************************** */
typedef uint8 Spi_HWUnitType;


/*********************************************************
 * @typedef 8.2.11 Spi_AsyncModeType
 * @brief Kiểu dữ liệu xác định chế độ không đồng bộ của Spi
 * @details Xác định chế độ không đồng bộ(polling hoặc interrupt)
 ******************************************************** */
typedef enum
{
    SPI_POLLING_MODE = 0x00,    /* Chế độ polling*/
    SPI_INTERRUPT_MODE = 0x01   /* Chế độ interrupt*/
} Spi_AsyncModeType;



/* Định nghĩa kiểu dữ liệu cho các thành phần SPI */

/* Spi_BaudRateType: Tốc độ Baud rate */
typedef uint32 Spi_BaudRateType;  /**< Tốc độ Baud rate, sử dụng kiểu uint32_t để hỗ trợ tốc độ baud lớn */

/* Spi_ClockPolarityType: Cực tính của tín hiệu CLOCK */
typedef uint16 Spi_ClockPolarityType;  /**< Cực tính CLOCK, giá trị có thể là 0 hoặc 1 */

/* Spi_ClockPhaseType: Pha của tín hiệu CLOCK */
typedef uint16 Spi_ClockPhaseType;  /**< Pha CLOCK, giá trị có thể là 0 hoặc 1 */

/* Spi_ModeType: Chế độ SPI */
typedef uint16 Spi_ModeType;  /**< Chế độ SPI, giá trị có thể là 0 (Master) hoặc 1 (Slave) */

/* Spi_NSSManagementType: Quản lý tín hiệu NSS (Slave Select) */
typedef uint16 Spi_NSSManagementType;  /**< Quản lý NSS, có thể là 0 (phần mềm) hoặc 1 (phần cứng) */

/* Spi_DataSizeType: Kích thước dữ liệu truyền qua SPI */
typedef uint16 Spi_DataSizeType; 




/*********************************************************
 * @typedef 8.2.1 Spi_ConfigType
 * @brief Cấu trúc dữ liệu cho cấu hình SPI
 * @details Ba thông số đầu tiên thì bắt buộc, còn các thông
 *          số sau sẽ có giá trị mặc định nếu không cung cấp.
 ******************************************************** */
typedef struct 
{
    Spi_ChannelType Channel;        /**<Kênh SPI (bắt buốc) */
    Spi_JobType Job;                /**<Job SPI (bắt buộc) */
    Spi_SequenceType Sequence;      /**<Sequence SPI (bắt buộc) */
    
    //Các thông số cấu hình cấu hình cho SPI
    Spi_BaudRateType BaudRate;      /**<Tốc đô Baud rate(tùy chọn , mặc đinh 1Mhz) */
    Spi_ClockPolarityType CPOL;     /**<Cực tính CLOCK(tùy chọn, mặc định CPOL = 0) */
    Spi_ClockPhaseType CPHA;        /**<Pha CLOCK(tùy chọn, mặc định CPAL = 0) */
    Spi_ModeType Mode;              /**<Chế độ SPI(tùy chọn, mặc định Master) */
    Spi_NSSManagementType NSS;      /**<Quản lý NSS(tùy chọn, mặc định Software) */
    Spi_DataSizeType DataSize;      /**<Kích thước dữ liệu */
		uint16 Direction; 
		uint16 FirstBit;
	  uint16 CRCPolynomial; 
} Spi_ConfigType;

#endif /* SPI_TYPES_H */
