#include "Spi.h"

/* Các biến toàn cục để quản lý trạng thái SPI */
static Spi_StatusType SpiStatus = SPI_UNINIT;
static Spi_JobResultType JobResult = SPI_JOB_OK;
static Spi_SeqResultType SeqResult = SPI_SEQ_OK;


/******************************************************************
* @brief Khởi tạo SPI Handle/Driver với cấu hình đã cho
* @details Khởi tạo các thành phần của SPI, bao gồm phần cứng và
*          các kênh
* @param[in] ConfigPtr Con trỏ tới cấu hình Spi_ConfigType
**************************************************************** */
void Spi_Init (const Spi_ConfigType* ConfigPtr){
   /* Kiểm tra nếu ConfigPtr là NULL */
   if(ConfigPtr == NULL){
       return; /* Không khởi tạo nếu không có cấu hình*/
   }

//    /* Thiết lập các giá trị mặc định nếu chưa được cấu hình */
//    Spi_SetupDefaultConfig((Spi_ConfigType*)ConfigPtr);

   /* Khởi tạo và kích hoạt phần cứng SPI1 hoặc SPI2*/
   if(ConfigPtr->Channel ==  SPI_CHANNEL_1){
       //Khởi tạo SPI1 với cấu hình từ SPI1
       Spi_Hw_Init_SPI1();
       //Bật SPI1 sau khi khởi tạo
       Spi_Hw_Enable_SPI1();
   } else if( ConfigPtr->Channel == SPI_CHANNEL_2){
       //Khởi tạo SPI2 với cấu hình từ SPI2
       Spi_Hw_Init_SPI2();
       //Bật SPI2 sau khi khởi tạo
       Spi_Hw_Enable_SPI2();        
   } else {
       //Xử lý ngoại lệ
       return;
   }

   /* Cập nhật trạng thái SPI sau khi khởi tạo thành công */
   SpiStatus = SPI_IDLE;           /* SPI sẵn sàng và ở chế độ nhàn rỗi*/
   JobResult = SPI_JOB_OK;         /* Thiết lập Job về trạng thái mặc định */
   SeqResult = SPI_SEQ_OK;         /* Thiết lập Seq về trạng thái mặc định */
}  

/******************************************************************
* @brief Hàm hủy khởi tạo SPI Handle/Driver
* @details Hủy hàm khởi tạo và giải phóng tài nguyên liên quan đến SPI
* @return E_OK nếu thành công, E_NOT_OK nếu thất bại
**************************************************************** */
Std_ReturnType Spi_DeInit(void){
   /* Kiểm tra trạng thái SPI trước khi hủy khởi tạo */
   if(SpiStatus == SPI_UNINIT){
       return E_NOT_OK;
   }

   /* Hủy khởi tạo phần cứng SPI1*/
   Spi_Hw_DeInit_SPI1();

   /* Hủy khởi tạo phần cứng SPI2 */
   Spi_Hw_DeInit_SPI2();

   /* Đặt trạng thái SPI về trạng thái chưa khởi tạo*/\
   SpiStatus = SPI_UNINIT;

   /* Cập nhật trạng thái Job và Seq mặc định*/
   JobResult = SPI_JOB_OK;
   JobResult = SPI_JOB_OK;

   return E_OK; /* Hủy thành công*/
}


/******************************************************************
* @brief Ghi dữ liệu vào bộ đệm nội bộ của SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] DataBufferPtr Con trỏ tới buffer chứa dữ liệu cần ghi
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, const Spi_DataBufferType* DataBufferPtr){
   //Kiểm tra trạng thái SPI
   if(SpiStatus == SPI_UNINIT){
        return E_NOT_OK; //SPI chưa được khởi tạo
   }

   //Kiểm tra nếu buffer dữ liệu là NULL
   if(DataBufferPtr == NULL){
       return E_NOT_OK; //Dữ liệu chưa hợp lệ
   }    

   //Kiểm tra kênh SPI và ghi dữ liệu
   if(Channel == SPI_CHANNEL_1){
       //Đợi cho đến khi bộ đệm truyền của SPI trống
       Spi_Hw_WaitTransmitBufferEmpty_SPI1();

       //Gửi dữ liệu cho qua SPI1
       Spi_I2S_SendData_SPI1(DataBufferPtr);
   } else if(Channel == SPI_CHANNEL_2) {
       //Đợi cho đến khi bộ đệm truyền của SPI trống
       Spi_Hw_WaitTransmitBufferEmpty_SPI2();

       //Gửi dữ liệu cho qua SPI2
       Spi_I2S_SendData_SPI2(DataBufferPtr);       
   } else {
       // trả về lỗi
       return E_NOT_OK;
   }

   return E_OK; /* Thành công */
}


/******************************************************************
* @brief Truyền dữ liệu không đồng bộ qua SPI
* @param[in] Sequence ID của Sequence cần truyền
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
* @details Truyền dữ liệu không đồng bộ qua các job trong Sequence SPI
**************************************************************** */
Std_ReturnType Spi_AsyncTransmit (Spi_SequenceType Sequence){
   //Kiểm tra trạng thái SPI
   if(SpiStatus == SPI_UNINIT){
        return E_NOT_OK; //SPI chưa khởi tạo
   }

   //Kiểm tra nếu Sequence vượt giới hạn hoặc không tồn tại
   if(Sequence >= SPI_SEQUENCE_MAX){
       return E_NOT_OK;  //Sequence không hợp lệ
   } 

   //Lấy cấu hình sequence tương ứng
   const Spi_SequenceConfigType* SequenceConfig = &Spi_Sequences[Sequence];
	 
	 if (SequenceConfig == NULL) {
        return E_NOT_OK;
    }

   //Duyệt qua từng Job trong Sequence
   for(uint8 jobIndex = 0; jobIndex < SequenceConfig->JobCount;jobIndex++){
       Spi_JobType currentJob  = SequenceConfig->Jobs[jobIndex];

       //Lấy cấu hình job hiện tại
       const Spi_JobConfigType* JobConfig = &Spi_jobs[currentJob];

       //Lấy kênh SPI từ JobConfig
       Spi_ChannelType channel = JobConfig->Channel;

       //Truyền dữ liệu của JOb hiện tại qua kênh tương ứng
       if(channel == SPI_CHANNEL_1){
           //Đợi cho đến khi bộ đệm truyền của SPI trống
           Spi_Hw_WaitTransmitBufferEmpty_SPI1();

           //Gửi dữ liệu cho qua SPI1
           Spi_I2S_SendData_SPI1(JobConfig->DataBuffer);
       } else if(channel == SPI_CHANNEL_2) {
           //Đợi cho đến khi bộ đệm truyền của SPI trống
           Spi_Hw_WaitTransmitBufferEmpty_SPI2();

           //Gửi dữ liệu cho qua SPI2
           Spi_I2S_SendData_SPI2(JobConfig->DataBuffer);   
       } else {
           // trả về lỗi
           return E_NOT_OK;
       }
       
       //Cập nhất lại Job thành công
       JobResult = SPI_JOB_OK;
   }

   //Cập nhật lại  kết quả Sequence
   SeqResult = SPI_SEQ_OK;
   return E_OK;
}


/******************************************************************
* @brief Đọc dữ liệu vào bộ đệm nội bộ của SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] DataBufferPtr Con trỏ tới buffer chứa dữ liệu nhận được
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer){
   //Kiểm tra trạng thái SPI
   if(SpiStatus == SPI_UNINIT){
        return E_NOT_OK;
   }

   //Kiểm tra nếu buffer dữ liệu là NULL
   if(DataBufferPointer == NULL){
       return E_NOT_OK;
   }

   //Kiểm tra kênh SPI và ghi dữ liệu
   if(Channel == SPI_CHANNEL_1){
       //Đợi cho đến khi bộ đệm truyền của SPI trống
       Spi_Hw_WaitReceiveBufferFull_SPI1();

       //Đọc dữ liệu từ SPI1
       *DataBufferPointer = Spi_I2S_ReceiveData_SPI1();
   } else if(Channel == SPI_CHANNEL_2) {
       //Đợi cho đến khi bộ đệm truyền của SPI trống
       Spi_Hw_WaitReceiveBufferFull_SPI2();

       //Đọc dữ liệu từ SPI2
       *DataBufferPointer = Spi_I2S_ReceiveData_SPI2();      
   } else {
       // trả về lỗi
       return E_NOT_OK;
   }

   return E_OK; /* Thành công */
}


/******************************************************************
* @brief Cấu hình bộ đệm ngoài cho SPI
* @param[in] ChannelID ID của kênh SPI
* @param[in] SrcDataBufferPtr Con trỏ tới buffer nguồn
* @param[in] DesDataBufferPtr Con trỏ tới buffer đích
* @param[in] Length Số lượng phần tử dữ liệu cần nhận
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Std_ReturnType Spi_SetupEB (Spi_ChannelType Channel, const Spi_DataBufferType* SrcDataBufferPtr,
                          Spi_DataBufferType* DesDataBufferPtr, Spi_NumberOfDataType Length){
  //Kiểm tra trạng thái SPI
  if(SpiStatus == SPI_UNINIT){
       return E_NOT_OK;
  }

  //Kiểm tra nếu buffer dữ liệu là NULL
  if((SrcDataBufferPtr == NULL) || (DesDataBufferPtr == NULL) || (Length == 0)){
      return E_NOT_OK;
  }

  //Lặp qua từng phần tử dữ liệu dựa trên buffer
  for(Spi_NumberOfDataType i = 0 ; i < Length ; i++){
      //Kiểm tra kênh SPI và ghi dữ liệu
      if(Channel == SPI_CHANNEL_1){
          //Đợi cho đến khi bộ đệm truyền của SPI trống
          Spi_Hw_WaitTransmitBufferEmpty_SPI1();

          //Gửi dữ liệu buffer nguồn qua SPI1
          Spi_I2S_SendData_SPI1(&SrcDataBufferPtr[i]);
          
          //Đợi dữ liệu từ SPI1
          Spi_Hw_WaitReceiveBufferFull_SPI1();

          //Đọc dữ liệu vào buffer đích từ SPI1
          DesDataBufferPtr[i] = Spi_I2S_ReceiveData_SPI1();

      } else if(Channel == SPI_CHANNEL_2) {
          //Đợi cho đến khi bộ đệm truyền của SPI trống
          Spi_Hw_WaitTransmitBufferEmpty_SPI2();

          //Gửi dữ liệu buffer nguồn qua SPI1
          Spi_I2S_SendData_SPI2(&SrcDataBufferPtr[i]);
          
          //Đợi dữ liệu từ SPI1
          Spi_Hw_WaitReceiveBufferFull_SPI2();

          //Đọc dữ liệu vào buffer đích từ SPI1
          DesDataBufferPtr[i] = Spi_I2S_ReceiveData_SPI2();    
      } else {
          // trả về lỗi
          return E_NOT_OK;
      }

      return E_OK; /* Thành công */
  }
}


/******************************************************************
* @brief Lấy trạng thái hiện tại của SPI Handle/Driver
* @details Hàm này trả về trạng thái của SPI (SPI_UNINIT, SPI_IDLE, SPI_BUSY)
* @return E_OK nếu ghi thành công, E_NOT_OK nếu ghi không thành công
**************************************************************** */
Spi_StatusType Spi_GetStatus (void){
   //Nếu SPI chưa khởi tạo, trả về SPI_UNINIT
   if(SpiStatus == SPI_UNINIT){
        return SPI_UNINIT;
   }

   //Kiểm tra trạng thái của SPI1
   if(Spi_Hw_CheckStatus_SPI1() == SPI_BUSY){
       return SPI_BUSY; /* SPI đang bận */    
   }

   //Kiểm tra trạng thái của SPI2
   if(Spi_Hw_CheckStatus_SPI2() == SPI_BUSY){
       return SPI_BUSY; /* SPI đang bận */    
   }

   //Nếu không bận  trả về IDLE
   return SPI_IDLE;
}


///******************************************************************
//* @brief Lấy kết quả của 1 job SPI
//* @param[in] Job ID của 1 job
//* @details Hàm này trả về kết quả của 1 job được truyền
//* @return Kết quả Job (SPI_JOB_OK, SPI_JOB_PEDDING, SPI_JOB_FAILED)
//**************************************************************** */
//Spi_JobResultType Spi_GetJobResult (Spi_JobType Job){
//   //Kiểm tra trạng thái SPI
//   if(SpiStatus == SPI_UNINIT){
//       return SPI_JOB_FAILED;
//   }

//   //Dựa trên Job đang thực hiện
//   if(Job == SPI_JOB_READ_TEMP_SENSOR){
//       //Kiểm tra trạng thái của Job trên SPI1
//       return Spi_Hw_CheckJobStatus_SPI1();
//   } else if (Job == SPI_JOB_READ_EEPROM || Job == SPI_JOB_WRITE_EEPROM){
//       //Kiểm tra trạng thái của Job trên SPI2
//       return Spi_Hw_CheckJobStatus_SPI2();
//   } else {
//       return SPI_JOB_FAILED;
//   }
//}


///******************************************************************
//* @brief Lấy kết quả của 1 Sequence SPI
//* @param[in] Sequence ID của 1 seq
//* @details Hàm này trả về kết quả của 1 sequence được truyền
//* @return Kết quả Sequence (SPI_SEQ_OK, SPI_SEQ_PEDDING, SPI_SEQ_FAILED)
//**************************************************************** */
//Spi_SeqResultType Spi_GetSequenceResult (Spi_SequenceType Sequence){
//   //Kiểm tra trạng thái SPI
//   if(SpiStatus == SPI_UNINIT){
//       return SPI_SEQ_FAILED;
//   }

//   //Dựa trên Sequence đang thực hiện
//   if(Sequence == SPI_SEQUENCE_0){
//       //Kiểm tra trạng thái của sequence trên SPI1
//       return Spi_Hw_CheckSequenceStatus_SPI1();
//   } else if (Sequence == SPI_SEQUENCE_1 || Sequence == SPI_SEQUENCE_2){
//       //Kiểm tra trạng thái của Sequence trên SPI2
//       return Spi_Hw_CheckSequenceStatus_SPI2();
//   } else {
//       return SPI_SEQ_FAILED;
//   }   
//}


///******************************************************************
//* @brief Lấy thông tin phiên bản của SPI Handle/Driver
//* @param[in] versioninfo trỏ tới cấu trúc phiên bản
//* @details Hàm này trả về thông tin phiên bản bao gồm
//*          vendorID, moduleID và các phiên bản phần mềm
//**************************************************************** */
//void Spi_GetVersionInfo(Std_VersionInfoType* versioninfo){
//   //Kiểm tra con trỏ versioninfo
//   if(SpiStatus == NULL){
//       return;
//   }

//   // Gán thông tin vendorID và moduleID
//   versioninfo->vendorID = 1;
//   versioninfo->moduleID = 123;
//   
//   //Gán các thông tin phiên bản phần mềm
//   versioninfo->sw_major_version = 1;
//   versioninfo->sw_minor_version = 0;
//   versioninfo->sw_patch_version = 0;
//}

///******************************************************************
//* @brief Truyền dữ liệu đồng bộ qua cổng SPI
//* @param[in] Sequence ID của seq cần truyền
//* @details Truyền dữ liệu đồng bộ qua SequenceSPI, đợi quá trình 
//*          truyền hoàn thành.
//* @return E_OK thành công, E_NOT_OK nếu có lỗi
//**************************************************************** */
//Std_ReturnType Spi_SyncTransmit(Spi_SequenceType Sequence){
//   //Kiểm tra trạng thái SPI
//   if(SpiStatus == SPI_UNINIT){
//       return E_NOT_OK; //SPI chưa được khởi tạo
//   }

//   //Gọi hàm truyền không đồng bộ trước để quá trình bắt đầu truyền
//   Std_ReturnType result = Spi_AsyncTransmit(Sequence);
//   if(result != E_OK){
//       return E_NOT_OK; //Nếu không thể truyền đồng bộ thì bị lỗi
//   }

//   //Đợi cho đến khi các Job trong Sequence được hoàn tất
//   Spi_SeqResultType seqResult;
//   do{
//       seqResult = Spi_GetSequenceResult(Sequence);
//   } while (seqResult == SPI_SEQ_PENDING); //Tiếp tục đợi nếu Sequence vẫn đang thực hiện

//   //Kiểm tra kết quả cuối cùng của Sequence
//   if(seqResult == SPI_SEQ_OK){
//       return E_OK; //Truyền động bộ thành công
//   } else {
//       return E_NOT_OK; //Truyền đồng bộ không thành công
//   }
//}


///******************************************************************
//* @brief Lấy trạng thái đơn vị phần cứng của SPI
//* @details Truyền dữ liệu đồng bộ qua SequenceSPI, đợi quá trình 
//*          truyền hoàn thành.
//* @return Trạng thái hiện tại của phần cứng (SPI_BUSY, SPI_IDLE)
//**************************************************************** */
//Spi_StatusType  Spi_GetHWUnitStatus(void){
//   //Kiểm tra trạng thái phần cứng của SPI1
//       //Kiểm tra trạng thái của SPI1
//   if(Spi_Hw_CheckStatus_SPI1() == SPI_BUSY){
//       return SPI_BUSY; /* SPI đang bận */    
//   }

//   //Kiểm tra trạng thái của SPI2
//   if(Spi_Hw_CheckStatus_SPI2() == SPI_BUSY){
//       return SPI_BUSY; /* SPI đang bận */    
//   }

//   //Nếu không bận  trả về IDLE
//   return SPI_IDLE;
//}


///******************************************************************
//* @brief Hủy một Sequence đang truyền
//* @param[in] Sequence ID của Sequence cần hủy
//* @details Hủy quá trình truyền của một Sequence hiện tại và
//*          dừng quá trình truyền dữ liệu.
//* @return Nếu E_OK là thành cộng, còn E_NOT_OK là không thành công
//**************************************************************** */
////void Spi_Cancel (Spi_SequenceType Sequence){
////    //Kiểm tra trạng thái của SPI
////    if(SpiStatus == SPI_UNINIT){
////        return E_NOT_OK; //Chưa được khởi tạo SPI
////    }

////    //Dựa trên Sequence, hủy quá trình truyền trên kênh SPI tương ứng
////    if(Sequence = SPI_SEQUENCE_0){
////        //Hủy quá trình truyền trên SPI1
////        spi_hw_
////    }

////}
