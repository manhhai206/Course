#ifndef SPI_CFG_H
#define SPI_CFG_H

#include "Spi_Types.h"


/*******************************************************************
 * @section Định nghĩa các kênh SPI
 * Kênh SPI là đại diện cho đường truyền giữa MCU và ngoại vi.
 ******************************************************************* */
#define SPI_CHANNEL_1   0   /**<SPI Channel 1 */
#define SPI_CHANNEL_2   1   /**<SPI Channel 2 */
#define SPI_CHANNEL_3   2   /**<SPI Channel 3 */

/*******************************************************************
 * @section Định nghĩa các Job SPI
 * Job là công việc cần thực hiện
 ******************************************************************* */
#define SPI_JOB_READ_TEMP_SENSOR      0   /**<  */
#define SPI_JOB_WRITE_EEPROM          1   /**<  */
#define SPI_JOB_READ_EEPROM           2   /**<  */

/*******************************************************************
 * @section Định nghĩa các Sequence SPI
 * Sequence đại diện cho 1 chuỗi các job cần thực hiện liên tiếp
 ******************************************************************* */
#define SPI_SEQUENCE_0  0   /**<  */
#define SPI_SEQUENCE_1  1   /**<  */
#define SPI_SEQUENCE_2  2   /**<  */

/*******************************************************************
 * @section Cấu hình cho từng Job
 * Cấu hình chi tiết cho từng Job, bao gồm  kênh và tốc đọo và các tham số khác.
 ******************************************************************* */
typedef struct 
{
    Spi_ChannelType Channel;    /**<Kênh SPI được dùng cho Job */
    uint32 BaudRate;          /**<Tốc độ Baudrate được dùng cho Job */
    uint8 CPOL;                 /**<Cực tính Clock */
    uint8 CPHA;                 /**<Pha Clock */
    uint8 Mode;               /**<Chế độ Master hoặc Slave */
		uint8* DataBuffer;
} Spi_JobConfigType;

#define SPI_JOB_MAX 4  // Giới hạn số lượng job, có thể thay đổi tùy theo ứng dụng

// Khai báo mảng chứa các job
Spi_JobConfigType Spi_jobs[SPI_JOB_MAX];

/*******************************************************************
 * @section Cấu hình chi tiết cho từng Job
 * Bao gồm bao gồm  kênh và tốc độ và các tham số khác.
 ******************************************************************* */

// Cấu hình cho SPI1
const Spi_JobConfigType Spi_Job_Config_Read_Sensor = {
    .Channel = SPI_CHANNEL_1,
    .BaudRate = 1000000,
    .CPOL = 0,
    .CPHA = 0,
    .Mode = 1
};

/*******************************************************************
 * @section Cấu hình Sequence SPI
 * Các Sequence xác định chuỗi các Job sẽ được thực thi theo thứ tự
 *******************************************************************/
#define SPI_SEQUENCE_MAX 2

typedef struct {
    Spi_JobType* Jobs;   /**< Danh sách các Job trong Sequence */
    uint8 JobCount;      /**< Số lượng Job trong Sequence */
} Spi_SequenceConfigType;

// Khai báo mảng chứa cấu hình cho các Sequence
Spi_SequenceConfigType Spi_Sequences[SPI_SEQUENCE_MAX];


#define SPI_JOB_MAX 4  // Giới hạn số lượng job, có thể thay đổi tùy theo ứng dụng

// Khai báo mảng chứa các job
Spi_JobConfigType Spi_jobs[SPI_JOB_MAX];


#endif /* SPI_CFG_H */