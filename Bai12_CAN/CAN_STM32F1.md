
# **CAN_STM32F103C8**

## **1. Cấu hình Clock cho ngoại vi**
Trước tiên, cần kích hoạt clock cho CAN1 và các chân GPIO cần thiết (PA11 và PA12 trên STM32F103):
```c
void CAN_Clock_Configuration()
{
	/* Active Clock for CAN1 and GPIOA */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}
```
## **2. Cấu hình GPIO cho CAN**
Sau khi kích hoạt clock cho CAN1 và GPIOA, bước tiếp theo là cấu hình các chân GPIO (PA11 và PA12) để sử dụng cho giao tiếp CAN. Cụ thể, PA11 sẽ được sử dụng cho CAN_RX (nhận dữ liệu) và PA12 cho CAN_TX (truyền dữ liệu).
```C
void CAN_GPIO_Configuration(void) 
	{
    GPIO_InitTypeDef GPIO_InitStructure;

    // configure PA11 (CAN RX) is Input Pull-up
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // configure PA12 (CAN TX) is Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
```
- `GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;` cấu hình PA11 là đầu vào với chế độ Pull-up (tức là khi không có tín hiệu CAN, chân này sẽ ở trạng thái cao).
- `GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;` cấu hình PA12 là chân Alternate Function Push-Pull, cho phép truyền tín hiệu CAN từ vi điều khiển ra ngoài.

## **3. Cấu hình CAN**
```c
void CAN_Config()
{
	CAN_InitTypeDef CAN_InitStructure;
	
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
	CAN_Init(CAN1,&CAN_InitStructure);
}
```
**Cấu hình các chế độ CAN**:
- `CAN_TTCM = DISABLE;`: Tắt chế độ Time Trigger Communication Mode (Chế độ truyền thông theo thời gian).
- `CAN_ABOM = ENABLE;`: Bật chế độ tự động quản lý Bus-Off. Điều này giúp tự động khôi phục trạng thái CAN khi vi điều khiển bị "bus-off" (không thể truyền dữ liệu).
- `CAN_AWUM = ENABLE;`: Bật chế độ tự động Wake-up Mode. Khi hệ thống CAN bị tắt, chế độ này sẽ tự động kích hoạt lại CAN khi có tín hiệu.
- `CAN_NART = DISABLE;`: Tắt chế độ tự động retransmission (truyền lại). Nếu truyền dữ liệu không thành công, dữ liệu sẽ không được truyền lại tự động.
- `CAN_RFLM = DISABLE;`: Tắt chế độ Receive FIFO Locked. Chế độ này sẽ làm khóa FIFO khi không còn không gian trong bộ đệm.
- `CAN_TXFP = DISABLE;`: Tắt chế độ ưu tiên FIFO trong việc truyền dữ liệu.
- `CAN_Mode = CAN_Mode_Normal;`: Chế độ CAN bình thường, cho phép truyền và nhận dữ liệu trong mạng CAN

**Cấu hình Bit Timing**:
- `CAN_SJW = CAN_SJW_1tq;`: Đặt độ rộng đồng bộ (Synchronization Jump Width) bằng 1 time quantum (tq). Đây là độ rộng của bước nhảy trong quá trình đồng bộ.
- `CAN_BS1 = CAN_BS1_6tq;`: Đặt độ rộng của Bit Segment 1 là 6 time quanta (tq). Segment này chịu trách nhiệm cho các tín hiệu điều khiển như đồng bộ hóa.
- `CAN_BS2 = CAN_BS2_8tq;`: Đặt độ rộng của Bit Segment 2 là 8 time quanta (tq). Segment này sử dụng cho việc truyền tín hiệu dữ liệu.
- `CAN_Prescaler = 6;`: Bộ chia tần số được đặt là 6. Điều này có nghĩa là baud rate của CAN sẽ được tính bằng tần số clock CAN chia cho giá trị prescaler.
**Tính toán tốc độ truyền (Bit Rate)**

Tốc độ truyền bit (Bit Rate) được tính theo công thức:

    Bit Rate = Can_Clock / Prescaler * (Synchronization + BS1 + BS2)

Bit Time (thời gian của mỗi bit) được tính theo công thức:

    Bit Time = Prescaler * (Synchronization + BS1 + BS2) / Can_Clock
## **4. Cấu hình bộ lọc cho CAN**
```C
void CAN_FilterConfiguration(void) {
    CAN_FilterInitTypeDef CAN_FilterInitStructure;

    CAN_FilterInitStructure.CAN_FilterNumber = 0;  // Số bộ lọc (Filter Number)
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  // Chế độ lọc: Lọc theo ID Mask
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;  // Quy mô bộ lọc: 32 bit
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321 << 5;  // ID chuẩn 0x321 (chuyển sang 11 bit)
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;  // Mặt nạ so khớp với 11 bit của ID
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;  // Đẩy vào FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;  // Bật bộ lọc

    CAN_FilterInit(&CAN_FilterInitStructure);  // Khởi tạo bộ lọc CAN
}
```
- `CAN_FilterInitStructure.CAN_FilterNumber = 0;`: Cấu hình bộ lọc với số bộ lọc là 0 nghĩa là bộ lọc đầu tiên trong danh sách.
- `CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;`: Bộ lọc sẽ được cấu hình để lọc theo ID của thông điệp, với chế độ ID Mask.
- `CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;``: Bộ lọc được cấu hình để sử dụng 32-bit. Điều này cho phép lọc thông điệp CAN với cả ID chuẩn (11 bit) hoặc mở rộng (29 bit).
- `CAN_FilterInitStructure.CAN_FilterIdHigh = 0x321 << 5;`: Đặt ID chuẩn là 0x321. Để phù hợp với cấu trúc 32-bit của bộ lọc, ID chuẩn phải được dịch sang trái 5 bit để lấp đầy vị trí trong 32-bit.
 - `CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;`: Đây là phần thấp của ID. Vì ID chuẩn chỉ sử dụng 11 bit, phần này sẽ là 0x0000.
- `CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;`: Mặt nạ so khớp với 11-bit đầu tiên của ID chuẩn. Mặt nạ này cho phép khớp với các bit của ID (từ bit 0 đến bit 10).
- `CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;`: Phần thấp của mặt nạ ID.
- `CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;`: Bộ lọc này sẽ đẩy thông điệp vào FIFO0 khi nhận được một thông điệp phù hợp với bộ lọc.
- `CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;`: Bật bộ lọc sau khi cấu hình. Khi bộ lọc được bật, CAN sẽ bắt đầu lọc các thông điệp dựa trên các điều kiện mà bạn đã cấu hình.

## **5. Hàm truyền CAN**
```C
void CAN_TransmitData(uint8_t* data, uint8_t length) {
    CanTxMsg TxMessage;

    // Cấu hình ID chuẩn (Standard ID)
    TxMessage.StdId = 0x321;  

    // Cấu hình loại yêu cầu: Dữ liệu (Data frame)
    TxMessage.RTR = CAN_RTR_DATA;  

    // Cấu hình kiểu ID: ID chuẩn (Standard)
    TxMessage.IDE = CAN_ID_STD;  

    // Cấu hình chiều dài dữ liệu (Data Length Code)
    TxMessage.DLC = length; 

    // Gán dữ liệu vào thông điệp CAN
    for (int i = 0; i < length; i++) {
        TxMessage.Data[i] = data[i];
    }

    // Truyền thông điệp CAN
    uint8_t mailbox = CAN_Transmit(CAN1, &TxMessage); 

    // Đợi cho đến khi việc truyền hoàn tất
    while (CAN_TransmitStatus(CAN1, mailbox) != CAN_TxStatus_Ok);
}
```
**Cấu hình thông điệp CAN (CanTxMsg TxMessage)**:
- TxMessage.StdId = 0x321;: Thiết lập Standard ID cho thông điệp CAN là 0x321. Đây là ID của thông điệp sẽ được gửi.
- TxMessage.RTR = CAN_RTR_DATA;: Chỉ định loại thông điệp là Data frame (thông điệp dữ liệu). Trong CAN, có thể có hai loại thông điệp: Data frame (chứa dữ liệu) và Remote frame (yêu cầu dữ liệu).
- TxMessage.IDE = CAN_ID_STD;: Thiết lập kiểu ID là Standard (11-bit ID). STM32 hỗ trợ cả ID chuẩn (11 bit) và ID mở rộng (29 bit).
- TxMessage.DLC = length;: Chỉ định DLC (Data Length Code), tức là chiều dài dữ liệu của thông điệp CAN. length là số byte dữ liệu cần gửi (tối đa 8 byte).
Gán dữ liệu vào thông điệp CAN:
- Dữ liệu cần truyền được sao chép từ mảng data vào mảng `TxMessage.Data[]`. Vòng lặp for giúp gán từng byte dữ liệu vào thông điệp CAN.
Truyền thông điệp CAN:
- `uint8_t mailbox = CAN_Transmit(CAN1, &TxMessage);`: Hàm CAN_Transmit() gửi thông điệp CAN. STM32 sử dụng khái niệm "mailbox" để lưu trữ thông điệp CAN trong các ô nhớ của phần cứng. CAN_Transmit() trả về một giá trị mailbox, dùng để kiểm tra trạng thái truyền.
Kiểm tra trạng thái truyền:
- `while (CAN_TransmitStatus(CAN1, mailbox) != CAN_TxStatus_Ok);`: Sau khi gọi CAN_Transmit(), hàm CAN_TransmitStatus() được sử dụng để kiểm tra trạng thái của việc truyền thông điệp. Vòng lặp while sẽ tiếp tục chạy cho đến khi thông điệp được truyền thành công (trạng thái CAN_TxStatus_Ok)

## **6. Hàm nhận CAN**

Hàm này chờ đợi một thông điệp CAN có sẵn trong bộ đệm FIFO của CAN, sau đó nhận thông điệp đó, lưu trữ dữ liệu từ thông điệp vào bộ đệm và cuối cùng giải phóng FIFO để nhận các thông điệp mới.

```C
void CAN_ReceiveData(uint8_t* data)
{
    while(CAN_MessagePending(CAN1, CAN_FIFO0) < 1); 
    CanRxMsg RxMessage;
    
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);  
    
    for(int i = 0; i < RxMessage.DLC; i++) {
        data[i] = RxMessage.Data[i];  
    }
    CAN_FIFORelease(CAN1, CAN_FIFO0);  
}
```
**while(CAN_MessagePending(CAN1, CAN_FIFO0) < 1)**;
- Dòng lệnh này kiểm tra xem có thông điệp nào đang chờ trong FIFO0 (một hàng đợi FIFO dùng để lưu trữ các thông điệp CAN đã nhận) của CAN1 không.
- Hàm CAN_MessagePending(CAN1, CAN_FIFO0) trả về số lượng thông điệp đang chờ trong FIFO0.
- Nếu không có thông điệp nào (giá trị trả về nhỏ hơn 1), hàm sẽ tiếp tục ở trong vòng lặp while, nghĩa là chương trình sẽ bị "chặn" tại đây cho đến khi có thông điệp mới đến.
- Khi có ít nhất một thông điệp trong FIFO, vòng lặp while sẽ thoát và chương trình sẽ tiếp tục.
**CanRxMsg RxMessage;**
- Định nghĩa một cấu trúc CanRxMsg tên là RxMessage. Cấu trúc này sẽ chứa thông tin của thông điệp CAN vừa nhận, bao gồm dữ liệu, độ dài dữ liệu, mã định danh và các thuộc tính khác.
**CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);**
- Hàm này sẽ nhận thông điệp CAN từ FIFO0 của CAN1 và lưu vào biến RxMessage.
- Sau khi gọi hàm này, RxMessage sẽ chứa toàn bộ thông tin của thông điệp CAN vừa nhận, bao gồm dữ liệu và các thông tin đi kèm khác.
**for(int i = 0; i < RxMessage.DLC; i++) { data[i] = RxMessage.Data[i]; }**
- Vòng lặp này sao chép dữ liệu nhận được từ RxMessage.Data vào bộ đệm data được truyền vào hàm.
- RxMessage.DLC (Data Length Code) chỉ số lượng byte dữ liệu trong thông điệp. Vòng lặp sẽ lặp qua số byte này và sao chép từng byte vào mảng data.
**CAN_FIFORelease(CAN1, CAN_FIFO0);**
- Sau khi xử lý xong thông điệp, hàm CAN_FIFORelease sẽ được gọi để giải phóng FIFO0.
- Đây là bước quan trọng, vì nó thông báo cho bộ điều khiển CAN rằng thông điệp đã được xử lý, cho phép bộ điều khiển tiếp tục nhận các thông điệp mới và lưu trữ chúng vào FIFO.