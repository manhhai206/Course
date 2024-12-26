#include "Dio.h" 

/******************************************************************
 * @brief Đọc trạng thái của 1 kênh DIO.
 * @details Hàm này đọc trạng thái HIGH/LOW của một chân DIO (Channel).
 *          Hàm xác định cổng và chân GPIO dựa trên ChannelID, sau đó 
 *          trả về trạng thái logic hiện tại của chân đó.
 * 
 * @param[in] ChannelID ID của kênh cần đọc trạng thái.
 * @return Trạng thái logic của chân DIO (STD_HIGH hoặc STD_LOW).
 **************************************************************** */
Dio_LevelType Dio_ReadChannel(Dio_ChannelTypes ChannelID) {
    GPIO_TypeDef* GPIO_Port;   /**< Con trỏ đến cổng GPIO */
    uint16_t GPIO_Pin;         /**< Chân GPIO cần đọc trạng thái */

    // Xác định cổng GPIO tương ứng với ChannelID
    GPIO_Port = DIO_GET_PORT(ChannelID);

    // Nếu không tìm thấy cổng GPIO hợp lệ, trả về trạng thái thấp (STD_LOW)
    if (GPIO_Port == NULL) {
        return STD_LOW;
    }

    // Xác định chân GPIO tương ứng với ChannelID
    GPIO_Pin = DIO_GET_PIN(ChannelID);

    // Đọc trạng thái của chân GPIO
    if (GPIO_ReadInputDataBit(GPIO_Port, GPIO_Pin) == Bit_SET) {
        return STD_HIGH;        /* Nếu chân có mức logic cao, trả về STD_HIGH */
    } else {
        return STD_LOW;         /* Nếu chân có mức logic thấp, trả về STD_LOW */
    }
}


/******************************************************************
 * @brief Ghi trạng thái của 1 kênh DIO.
 * @details Hàm này ghi trạng thái HIGH/LOW cho 1 chân DIO Channel.
 *          Hàm xác định cổng và chân GPIO dựa trên ChannelID sau 
 *          đó ghi mức logic được chỉ định.
 * 
 * @param[in] ChannelID ID của kênh được ghi
 * @param[in] Level Trạng thái logic cần được ghi vào kênh DIO
 *             (STD_HIGH hoặc STD_LOW)
 **************************************************************** */
void Dio_WriteChannel(Dio_ChannelTypes ChannelID, Dio_LevelType Level) {
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(ChannelID);   /**< Con trỏ đến cổng GPIO */
    uint16_t GPIO_Pin = DIO_GET_PIN(ChannelID);        /**< Chân GPIO cần ghi trạng thái */

    // Nếu không tìm thấy cổng GPIO hợp lệ, thoát hàm
    if (GPIO_Port == NULL) {
        return;
    }

    // Ghi trạng thái của chân GPIO
    if (Level == STD_HIGH) {
        GPIO_SetBits(GPIO_Port, GPIO_Pin);      /* Đặt chân GPIO ở mức cao */
    } else {
        GPIO_ResetBits(GPIO_Port, GPIO_Pin);    /* Đặt chân GPIO ở mức thấp */
    }
}


/******************************************************************
 * @brief Đọc trạng thái logic của toàn bộ cổng DIO
 * @details Hàm này đọc trạng thái logic của tất cả chân GPIO trong 
 *          một Port. 
 *          Hàm xác định cổng GPIO dựa trên PortID và toàn bộ cổng 
 *          được trả về dưới dạng 16 bit (tương ứng với 16 chân GPIO).
 * 
 * @param[in] PortID ID của cổng cần đọc (ví dụ GPIOA, GPIOB, GPIOC,...)
 * @return Trạng thái logic của toàn bộ cổng DIO, trả về giá trị 16 bit
 **************************************************************** */
Dio_PortLevelType Dio_ReadPort(Dio_PortTypes PortID) {
    // Sử dụng macro DIO_GET_PORT để xác định cổng GPIO từ PortID
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(PortID);

    // Kiểm tra xem con trỏ cổng GPIO có hợp lệ không
    if (GPIO_Port == NULL) {
        // Nếu không hợp lệ, trả về giá trị 0 hoặc một giá trị lỗi nào đó
        return 0;
    }

    // Đọc trạng thái toàn bộ cổng DIO và trả về dưới dạng 16 bit
    return (Dio_PortLevelType)GPIO_ReadInputData(GPIO_Port);
}


/******************************************************************
 * @brief Ghi trạng thái logic của toàn bộ cổng DIO
 * @details Hàm này ghi trạng thái logic của tất cả chân GPIO trong 
 *          một Port. 
 *          Hàm xác định cổng GPIO dựa trên PortID và toàn bộ cổng 
 *          được trả về dưới dạng 16 bit (tương ứng với 16 chân GPIO).
 * 
 * @param[in] PortID ID của cổng cần ghi
 * @param[in] Level Trạng thái logic cần ghi vào toàn bộ cổng DIO
 **************************************************************** */
void Dio_WritePort(Dio_PortTypes PortID, Dio_LevelType Level) {
    // Sử dụng macro DIO_GET_PORT để xác định cổng GPIO
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(PortID);

    // Kiểm tra xem con trỏ cổng GPIO có hợp lệ không
    if (GPIO_Port == NULL) {
        // Nếu không hợp lệ, thoát khỏi hàm (không thực hiện gì thêm)
        return;
    }

    // Ghi trạng thái vào toàn bộ cổng GPIO
    if (Level == STD_HIGH) {
        // Đặt toàn bộ các chân GPIO của cổng ở mức HIGH
        GPIO_Write(GPIO_Port, 0xFFFF);  // Tất cả các chân đều ở mức cao
    } else {
        // Đặt toàn bộ các chân GPIO của cổng ở mức LOW
        GPIO_Write(GPIO_Port, 0x0000);  // Tất cả các chân đều ở mức thấp
    }
}


/*********************************************************
  * @brief Đọc trạng thái của tất cả các chân trong một nhóm cổng DIO
  * @param[in] ChannelGroupIdPtr Con trỏ đến nhóm các kênh cần đọc trạng thái
  * @return Trạng thái logic của toàn bộ nhóm cổng DIO dưới dạng giá trị 16 bit,
  *         trong đó mỗi bit đại diện cho trạng thái của một chân (HIGH hoặc LOW)
  ******************************************************** */
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr){
    /* Sử dụng macro DIO_GET_PORT để xác định cổng GPIO*/
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(ChannelGroupIdPtr->port);

    // Kiểm tra xem con trỏ cổng GPIO có hợp lệ không
    if (GPIO_Port == NULL) {
        // Nếu không hợp lệ, thoát khỏi hàm (không thực hiện gì thêm)
        return 0;
    }

    /* Đọc trạng thái logic toàn bộ cổng GPIO */
    uint16 portData = GPIO_ReadInputData(GPIO_Port);

    /* Lấy giá trị bằng sử dụng mask và offset */
    return (Dio_PortLevelType)((portData & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset);
}


/*********************************************************
  * @brief Ghi trạng thái cho tất cả các chân trong một nhóm cổng DIO
  * @param[in] ChannelGroupIdPtr Con trỏ đến nhóm các kênh cần ghi trạng thái
  * @param[in] Level Trạng thái logic cần ghi cho nhóm cổng DIO (mỗi bit đại diện cho trạng thái của một chân)
  * @details Hàm này sẽ ghi trạng thái (HIGH hoặc LOW) vào từng chân trong nhóm cổng DIO
  *          dựa trên giá trị của tham số Level. Mỗi bit trong Level sẽ đại diện cho trạng thái
  *          của một chân tương ứng trong nhóm các kênh.
  ******************************************************** */
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level) {
    /* Sử dụng macro DIO_GET_PORT để xác định cổng GPIO */
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(ChannelGroupIdPtr->port);

    // Kiểm tra xem con trỏ cổng GPIO có hợp lệ không
    if (GPIO_Port == NULL) {
        // Nếu không hợp lệ, thoát khỏi hàm (không thực hiện gì thêm)
        return;
    }

    /* Đọc trạng thái logic toàn bộ cổng GPIO */
    uint16 portData = GPIO_ReadInputData(GPIO_Port);

    /* Xóa các bit trong nhóm, sau đó ghi lại bit mới */
    portData &= ~(ChannelGroupIdPtr->mask); /* Xóa các bit tương ứng với mask */

    /* Dịch giá trị Level vào đúng vị trí bằng cách sử dụng offset,
     * sau đó dùng mask để chỉ thay đổi các bit cần thiết */
    portData |= ((Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask);

    /* Ghi giá trị mới vào cổng GPIO */
    GPIO_Write(GPIO_Port, portData);
}


/*********************************************************
  * @brief Lấy thông tin phiên bản của module Dio
  * @param[out] VersionInfo Con trỏ đến cấu trúc chứa thông tin phiên bản
  * @details Hàm này cung cấp thông tin về phiên bản của module Dio.
  ******************************************************** */
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo){
    VersionInfo->vendorID = 0x0000; /* ID nhà cung cấp*/
    VersionInfo->moduleID = 0x0001; /* ID module DIO */
    VersionInfo->sw_major_version = 2;
    VersionInfo->sw_minor_version = 0;
    VersionInfo->sw_patch_version = 0; 
}


/*********************************************************
 * @brief Hàm lập giá trị logic của một kênh DIO
 * @param[out] ChannelID ID của kênh cần lật
 * @details Hàm này lật giá trị logic của 1 chân GPIO(HIGH -> LOW và LOW -> HIGH).
 ******************************************************** */
Dio_LevelType Dio_FlipChannel(Dio_ChannelTypes ChannelID){
    Dio_LevelType CurrentLevel = Dio_ReadChannel(ChannelID);

    /* Lật giá trị của kênh */
    if(CurrentLevel == STD_HIGH){
        Dio_WriteChannel(ChannelID,STD_LOW);
        return STD_LOW;
    } else {
        Dio_WriteChannel(ChannelID,STD_HIGH);
        return STD_HIGH;   
    }
}

/*********************************************************
 * @brief Ghi trạng thái vào cổng DIO với mặt nạ (mask)
 * @param[in] PortID ID của cổng DIO cần ghi trạng thái
 * @param[in] Level Trạng thái logic cần ghi vào cổng DIO (mỗi bit đại diện cho trạng thái của một chân)
 * @param[in] Mask Mặt nạ để chỉ định những chân nào trong cổng DIO sẽ bị ảnh hưởng
 * @details Hàm này sẽ ghi trạng thái (HIGH hoặc LOW) vào các chân trong cổng DIO dựa trên tham số
 *          `Level` và `Mask`. Mỗi bit trong `Level` sẽ tương ứng với trạng thái của một chân,
 *          và chỉ những chân có bit tương ứng bằng 1 trong `Mask` sẽ bị thay đổi trạng thái.
 ******************************************************** */
void Dio_MaskedWritePort(Dio_PortTypes PortID, Dio_PortLevelType Level, Dio_PortLevelType Mask) {
    /* Xác định cổng GPIO tương ứng từ PortID */
    GPIO_TypeDef* GPIO_Port = DIO_GET_PORT(PortID);
    
    // Kiểm tra xem con trỏ cổng GPIO có hợp lệ không
    if (GPIO_Port == NULL) {
        // Nếu không hợp lệ, thoát khỏi hàm (không thực hiện gì thêm)
        return;
    }

    /* Đọc trạng thái hiện tại của cổng GPIO */
    uint16 portData = GPIO_ReadOutputData(GPIO_Port);

    /* Xóa các bit trong cổng theo mặt nạ (Mask) */
    portData &= ~(Mask); 

    /* Ghi các bit mới vào cổng GPIO theo trạng thái được chỉ định (Level) */
    portData |= (Level & Mask); 

    /* Ghi giá trị mới vào cổng GPIO */
    GPIO_Write(GPIO_Port, portData);
}
