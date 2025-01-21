#ifndef SPI_CFG_H
#define SPI_CFG_H

#include "Std_Types.h"
#include "Spi_Types.h"
#include "Spi_Hw.h"

/*******************************************************************
 * @section Định nghĩa các kênh SPI
 * Kênh SPI là đại diện cho đường truyền giữa MCU và ngoại vi.
 *******************************************************************/
#define SPI_CHANNEL_1   0   /**<SPI Channel 1 */
#define SPI_CHANNEL_2   1   /**<SPI Channel 2 */
#define SPI_CHANNEL_3   2   /**<SPI Channel 3 */

/*******************************************************************
 * @section Định nghĩa các Job SPI
 * Job là công việc cần thực hiện
 *******************************************************************/
#define SPI_JOB_READ_TEMP_SENSOR      0   /**< Job for reading temperature sensor */
#define SPI_JOB_WRITE_EEPROM          1   /**< Job for writing to EEPROM */
#define SPI_JOB_READ_EEPROM           2   /**< Job for reading from EEPROM */

/*******************************************************************
 * @section Định nghĩa các Sequence SPI
 * Sequence đại diện cho 1 chuỗi các job cần thực hiện liên tiếp
 *******************************************************************/
#define SPI_SEQUENCE_0  0   /**< Sequence for reading data from temperature sensor */
#define SPI_SEQUENCE_1  1   /**< Sequence for writing data to EEPROM */
#define SPI_SEQUENCE_2  2   /**< Sequence for reading data from EEPROM */

/*******************************************************************
 * @section Cấu hình cho từng Job
 *******************************************************************/
 typedef struct {
    Spi_ChannelType Channel;        /**< Kênh SPI được dùng cho Job */
    uint32 BaudRate;              /**< Tốc độ Baudrate được dùng cho Job */
    uint8 CPOL;                   /**< Cực tính Clock */
    uint8 CPHA;                   /**< Pha Clock */
    uint8 Mode;                   /**< Chế độ Master hoặc Slave */
    uint8* DataBuffer;            /**< Dữ liệu sẽ được truyền/nhận qua SPI */
} Spi_JobConfigType;

#define SpiJobConfig_ReadSensor    { SPI_CHANNEL_1, 1000000, 0, 0, 1, NULL }
#define SpiJobConfig_WriteEEPROM   { SPI_CHANNEL_2, 500000, 0, 0, 1, NULL }
#define SpiJobConfig_ReadEEPROM    { SPI_CHANNEL_2, 500000, 0, 0, 1, NULL }

/*******************************************************************
 * @section Cấu hình Sequence SPI
 *******************************************************************/
typedef struct {
    Spi_JobType Jobs[2];   /**< Danh sách các Job trong Sequence */
    uint8 JobCount;      /**< Số lượng Job trong Sequence */
} Spi_SequenceConfigType;

#define SpiSequenceConfig_0    { {SPI_JOB_READ_TEMP_SENSOR}, 1 }
#define SpiSequenceConfig_1    { {SPI_JOB_WRITE_EEPROM}, 1 }
#define SpiSequenceConfig_2    { {SPI_JOB_READ_EEPROM}, 1 }

/*******************************************************************
 * @brief Thiết lập giá trị mặc định cho cấu trúc Spi_ConfigType
 *******************************************************************/
static inline void Spi_SetupDefaultConfig(Spi_ConfigType* config) {
    // Các thiết lập mặc định cho cấu hình SPI
    if (config->BaudRate == 0) {
        config->BaudRate = SPI_BRatePrescaler_16;
    }

    if (config->CPOL == 0) {
        config->CPOL = SPI_CPOL_LOW;
    }

    if (config->CPHA == 0) {
        config->CPHA = SPI_CPHA_1EDGE;
    }

    if (config->Mode == 0) {
        config->Mode = SPI_MODE_SLAVE;
    }

    if (config->NSS == 0) {
        config->NSS = SPI_NSS_SOFT;
    }

    if (config->DataSize == 0) {
        config->DataSize = SPI_DATASIZE_8b;
    }
		
	if (config->DataSize == 0){
        config->Direction = SPI_Direction_2Lines_FullDuplex;
    }

	if (config->FirstBit == 0){
        config->FirstBit = SPI_FirstBit_MSB;
    }

    if (config->CRCPolynomial == 0){
        config->CRCPolynomial = 7;
    }
}

// Declare Spi_Sequences and Spi_jobs globally
extern const Spi_SequenceConfigType Spi_Sequences[];
extern const Spi_JobConfigType Spi_jobs[];

#endif /* SPI_CFG_H */
