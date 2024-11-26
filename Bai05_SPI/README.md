
# Config SPI Protocols 

## Config SPI software

### **Master**

```c
#define SPI_SCK_Pin 	GPIO_Pin_0
#define SPI_MISO_Pin 	GPIO_Pin_1
#define SPI_MOSI_Pin 	GPIO_Pin_2
#define SPI_CS_Pin 		GPIO_Pin_3
#define SPI_GPIO 		GPIOA
#define SPI_RCC 		RCC_APB2Periph_GPIOA
```

Đầu tiên phải định nghĩa các chân SPI từ các chân GPIO muốn sử dụng bao gồm GPIOA, 4 chân của GPIOA và RCC.

```c
void RCC_Config(){
	RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
```
Cấp clock lần lượt cho từng ngoại vi sử dụng như Timer2 và GPIOA.

```C
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin | SPI_CS_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}
```
Cấu hình các chân GPIO cho hoạt động SPI:
- SCK (Serial Clock): Chân này được sử dụng để cung cấp tín hiệu đồng hồ từ Master đến Slave, vì vậy nó sẽ được cấu hình là Output.
- MOSI (Master Out Slave In): Chân này được sử dụng để truyền dữ liệu từ Master đến Slave, nên nó cũng được cấu hình là Output.
- MISO (Master In Slave Out): Chân này được sử dụng để nhận dữ liệu từ Slave đến Master, vì vậy nó sẽ được cấu hình là Input.
- CS (Chip Select): Chân này được sử dụng để chọn Slave mà Master muốn giao tiếp, nên nó sẽ được cấu hình là Output.

```c
void TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;

    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_Prescaler = 7200 - 1; 
    TIM_InitStruct.TIM_Period = 0xFFFF;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}


void delay_ms(uint32_t time)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time * 10) {}
}
```
Tạo hàm delay.

```c
void Clock(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
	delay_ms(1);
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	delay_ms(1);
}

void SPI_init(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
}
```
Hàm Clock() tạo xung giả lập cho code và hàm SPI_init() thì thiết lập ban đầu cho các chân SPI, đảm bảo rằng SCK là LOW và CS là HIGH để không chọn bất kỳ Slave nào.

```c
void SPI_Master_Transmit(uint8_t u8Data){	
	uint8_t u8Mask = 0x80;	
	uint8_t tempData;
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay_ms(1);
	for(int i = 0; i < 8; i++){
		tempData = u8Data & u8Mask;
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay_ms(1);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay_ms(1);
		}
		u8Data = u8Data << 1;
		Clock();
	}
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay_ms(1);
}
```
Mô tả của bạn về hàm SPI_Master_Transmit. 
- Khởi tạo mặt nạ u8Mask = 0x80 và biến tạm tempData  để lưu trạng thái bit hiện tại.
```c
	uint8_t u8Mask = 0x80;	
	uint8_t tempData;
```
- Setup chân CS xuống LOW và delay một chút trước khi bắt đầu truyền.
```c
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay_ms(1);
```    
- Vòng lặp truyền từng bit: Kiểm tra bit cao nhất của u8Data bằng cách cho & u8Mask. Nếu bit = 1, đặt MOSI lên HIGH, nếu bit = 0, đặt MOSI xuống LOW. Sau đó dịch bit u8Data sang trái để kiểm tra bit tiếp theo. Gửi xung clock để đồng bộ dữ liệu.
```c
	for(int i = 0; i < 8; i++){
		tempData = u8Data & u8Mask;
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay_ms(1);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay_ms(1);
		}
		u8Data = u8Data << 1;
		Clock();
	}
```       

- Sau khi truyền xong 1byte thì setup chân CS lên HIGH để ngừng truyền và delay một chút sau khi truyền xong.
```c
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay_ms(1);
```

### **Slave**

Đối với Slave thì GPIO_Config sẽ khác với Master và phải viết 1 hàm nhận data từ Master.

```c
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin | SPI_CS_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}
```
Các chân SCK, MOSI, và CS được config là Input để nhận dữ liệu từ Master, trong khi chân MISO được config là Output để truyền dữ liệu về Master. Còn lại thì giống như Master.

```c
uint8_t SPI_Slave_Receive(){
	uint8_t dataReceive = 0x00;	
	uint8_t temp = 0x00;
	while(GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_Pin));
	while(!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
	for(int i = 0; i < 8; i++){ 
		if(GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin)){
			while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin)){
				temp = GPIO_ReadInputDataBit(SPI_GPIO, SPI_MOSI_Pin);
			}
			dataReceive <<= 1;
			dataReceive |= temp;
    		}
		while(!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
	}
	while(!GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_Pin));
	return dataReceive;
}
```
Mô tả của bạn về hàm SPI_Slave_Receive.
-  Khởi tạo biến  dataReceive để lưu trữ dữ liệu nhận được từ Maste và biến tạm tempData để lưu giá trị từng bit được đọc từ chân MOSI.
```c
    uint8_t dataReceive = 0x00;	
    uint8_t temp = 0x00;
```
-   Chờ cho đến khi chân CS được kéo xuống. Điều này có nghĩa là Slave được chọn để nhận dữ liệu.
```c
    while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_Pin));
```
-   Tiếp tục chờ đến khi chân SCK chuyển lên HIGH để biết rằng Master đã sẵn sàng để truyền dữ liệu.
```c
    while (!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
```
-  Vòng lặp truyền nhận từng bit: nếu SCK đang ở trạng thái HIGH, Slave sẽ đọc giá trị trên chân MOSI và ghi vào temp. Và dataReceive dịch trái 1 bit để chuẩn bị cho việc ghi nhận bit tiếp theo. Sử dụng phép | giữa temp và dataReceive ghi nhận giá trị đã đọc được. Sau khi nhận xong một bit, hàm sẽ chờ cho SCK chuyển xuống LOW để chuẩn bị cho bit tiếp theo.
```c
    for (int i = 0; i < 8; i++) { 
        if (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin)) {
            while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin)) {
                temp = GPIO_ReadInputDataBit(SPI_GPIO, SPI_MOSI_Pin); 
            }
            dataReceive <<= 1; 
            dataReceive |= temp; 
        }
        while (!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
    }
```
- Cuối cùng, hàm chờ cho chân CS trở về trạng thái HIGH trước khi trả về dữ liệu đã nhận. Điều này chỉ ra rằng quá trình truyền dữ liệu đã hoàn tất.
```c
    while (!GPIO_ReadInputDataBit(SPI_GPIO, SPI_CS_Pin));
    return dataReceive; 
```

## Config SPI hardware

### Maste

```c
void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
```
Hàm RCC_Config() cấu hình xung nhịp cho các ngoại vi:
- RCC_APB2Periph_AFIO: Bật xung nhịp cho chức năng I/O thay thế.
- RCC_APB2Periph_GPIOA: Bật xung nhịp cho GPIOA.
- RCC_APB2Periph_SPI1: Bật xung nhịp cho SPI1.
- RCC_APB1Periph_TIM2: Bật xung nhịp cho TIM2.

```c
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = SPI1_NSS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
}
```
Hàm này cấu hình các chân GPIO cho giao tiếp SPI:
- SPI1_NSS (PA4): Cấu hình làm chân xuất push-pull để điều khiển CS thủ công.
- SPI1_SCK (PA5), SPI1_MISO (PA6), SPI1_MOSI (PA7): Cấu hình chế độ chức năng thay thế.

```c
void SPI_Config(){
	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
```
Hàm này cấu hình SPI1:
- SPI_Mode_Master: Cấu hình SPI1 ở chế độ master.
- SPI_Direction_2Lines_FullDuplex: Kích hoạt giao tiếp song công trên hai đường truyền.
- SPI_BaudRatePrescaler_16: Cài đặt tỷ lệ chia xung nhịp SPI là 16.
- SPI_CPOL_Low và SPI_CPHA_1Edge: Định nghĩa độ lệch và pha của xung nhịp.
- SPI_DataSize_8b: Định nghĩa kích thước khung dữ liệu là 8 bit.
- SPI_FirstBit_MSB: Gửi bit quan trọng nhất trước.
- SPI_NSS_Soft: Quản lý chân chip select (NSS) thủ công bằng phần mềm.

```c
void SPI_SendByte(uint8_t data) {
    GPIO_ResetBits(SPI1_GPIO, SPI1_NSS);  
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
    SPI_I2S_SendData(SPI1, data); 
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 
    GPIO_SetBits(SPI1_GPIO, SPI1_NSS); 
}
```
Hàm này gửi một byte qua giao tiếp SPI:
- GPIO_ResetBits(SPI1_GPIO, SPI1_NSS): Kích hoạt CS.
- Hàm chờ cờ **TXE**  chờ cho đến khi cờ TXE được Set, có nghĩa là nó sẽ liên tục kiểm tra cho đến khi bộ đệm truyền trống và sẵn sàng nhận dữ liệu mới.
- Cờ **RXNE** được kiểm tra để đảm bảo dữ liệu đã được nhận.
- GPIO_SetBits(SPI1_GPIO, SPI1_NSS): Ngắt kích hoạt CS.

### Slave
```c
uint8_t SPI_Receive1Byte(void){
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 
    return(uint8_t)SPI_I2S_ReceiveData(SPI1);
}
```
Dùng cờ RXNE để kiểm tra xem có dữ liệu nhận được từ SPI.Nếu rồi thì đọc dữ liệu.