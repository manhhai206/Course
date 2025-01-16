/***************************************************************
* @file Spi.h
* @brief SPI Driver Header File
* @details File này chứa các quy định về kiểu dữ liệu và 
*          khai báo các API của SPI Driver tuân thủ theo AUTOSAR.
*          Driver này được thiết kế để điều khiển SPI của STM32F103C8.  
* @author Mạnh Trọng Hải
****************************************************************/
#ifndef SPI_H
#define SPI_H

#include "Spi_Types.h"
#include "Spi_Cfg.h"
#include "Spi_Hw.h"

/* ============================================
* Định nghĩa kiểu dữ liệu của SPI Driver
* ============================================ */

/******************************************************************
* @brief Khởi tạo SPI Handle/Driver với cấu hình đã cho
* @details Khởi tạo các thành phần của SPI, bao gồm phần cứng và
*          các kênh
* @param[in] ConfigPtr Con trỏ tới cấu hình Spi_ConfigType
**************************************************************** */
void Spi_Init (const Spi_ConfigType* ConfigPtr);


/******************************************************************
* @brief Hàm hủy khởi tạo SPI Handle/Driver
* @details Hủy hàm khởi tạo và giải phóng tài nguyên liên quan đến SPI
* @return E_OK nếu thành công, E_NOT_OK nếu thất bại
**************************************************************** */
Std_ReturnType Spi_DeInit(void);


/******************************************************************
* @brief Ghi dữ liệu vào bộ đệm nội bộ của SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] DataBufferPtr Con trỏ tới buffer chứa dữ liệu cần ghi
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, const Spi_DataBufferType* DataBufferPtr);


/******************************************************************
* @brief Truyền dữ liệu không đồng bộ qua SPI
* @param[in] Sequence ID của Sequence cần truyền
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
* @details Truyền dữ liệu không đồng bộ qua các job trong Sequence SPI
**************************************************************** */
Std_ReturnType Spi_AsyncTransmit (Spi_SequenceType Sequence);


/******************************************************************
* @brief Đọc dữ liệu vào bộ đệm nội bộ của SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] DataBufferPtr Con trỏ tới buffer chứa dữ liệu nhận được
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer);


/******************************************************************
* @brief Cấu hình bộ đệm ngoài cho SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] SrcDataBufferPtr Con trỏ tới buffer nguồn
* @param[in] DesDataBufferPtr Con trỏ tới buffer đích
* @param[in] Length Số lượng phần tử dữ liệu cần nhận
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_SetupEB (Spi_ChannelType Channel, const Spi_DataBufferType* SrcDataBufferPtr,
                           Spi_DataBufferType* DesDataBufferPtr, Spi_NumberOfDataType Length);


/******************************************************************
* @brief Lấy trạng thái hiện tại của SPI Handle/Driver
* @details Hàm này trả về trạng thái của SPI (SPI_UNINIT, SPI_IDLE, SPI_BUSY)
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Spi_StatusType Spi_GetStatus (void);


/******************************************************************
* @brief Lấy kết quả của 1 job SPI
* @param[in] Job ID của 1 job
* @details Hàm này trả về kết quả của 1 job được truyền
* @return Kết quả Job (SPI_JOB_OK, SPI_JOB_PEDDING, SPI_JOB_FAILED)
**************************************************************** */
Spi_JobResultType Spi_GetJobResult (Spi_JobType Job);


/******************************************************************
* @brief Lấy kết quả của 1 Sequence SPI
* @param[in] Sequence ID của 1 seq
* @details Hàm này trả về kết quả của 1 sequence được truyền
* @return Kết quả Sequence (SPI_SEQ_OK, SPI_SEQ_PEDDING, SPI_SEQ_FAILED)
**************************************************************** */
Spi_SeqResultType Spi_GetSequenceResult (Spi_SequenceType Sequence);


/******************************************************************
* @brief Lấy thông tin phiên bản của SPI Handle/Driver
* @param[in] versioninfo trỏ tới cấu trúc phiên bản
* @details Hàm này trả về thông tin phiên bản bao gồm
*          vendorID, moduleID và các phiên bản phần mềm
**************************************************************** */
void Spi_GetVersionInfo(Std_VersionInfoType* versioninfo);


/******************************************************************
* @brief Truyền dữ liệu đồng bộ qua cổng SPI
* @param[in] Sequence ID của seq cần truyền
* @details Truyền dữ liệu đồng bộ qua SequenceSPI, đợi quá trình 
*          truyền hoàn thành.
* @return E_OK thành công, E_NOT_OK nếu có lỗi
**************************************************************** */
Std_ReturnType Spi_SyncTransmit(Spi_SequenceType Sequence);


/******************************************************************
* @brief Lấy trạng thái đơn vị phần cứng của SPI
* @details Truyền dữ liệu đồng bộ qua SequenceSPI, đợi quá trình 
*          truyền hoàn thành.
* @return Trạng thái hiện tại của phần cứng (SPI_BUSY, SPI_IDLE)
**************************************************************** */
Spi_StatusType  Spi_GetHWUnitStatus(void);

#endif /* SPI_H*/
