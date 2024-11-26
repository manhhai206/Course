
# UART

## Software

```c
#define BRateTime 104  // Adjust this for accurate baud rate timing 9600
```
BaudReat là số bit truyền được trong 1s
Chúng ta sẽ có phép tính biển đổi sau
9600 bit => 1s
1bit     => ~104us

```c
void GPIO_Config() {
    GPIO_InitTypeDef GPIOInitStruct;
    GPIOInitStruct.GPIO_Pin = RX_Pin;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART_GPIO, &GPIOInitStruct);

    GPIOInitStruct.GPIO_Pin = TX_Pin;
    GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(UART_GPIO, &GPIOInitStruct);
}
```
Cấu hình cho 2 chân RX là chân Input FLoating còn TX là Output Pushpull

```c
void UARTSoftware_Init(){

	GPIO_SetBits(GPIOA,TX_Pin);
	delay_us(1);
}
```
Khởi tạo trạng thái ban đầu với chân TX ở mức cao.
```c
void UARTSoftware_Transmitt(char c) {

   // Start bit
    GPIO_ResetBits(GPIOA, TX_Pin);
    clock();

    // Truyen data (LSB)
    for (int i = 0; i < 9; i++)
		{
        if (c & (1 << i)) 
					{
            GPIO_SetBits(GPIOA, TX_Pin);
					} else {
            GPIO_ResetBits(GPIOA, TX_Pin);
					}
        clock();
    }
    // Stop bit
    GPIO_SetBits(GPIOA, TX_Pin);
    clock();
}
```

- Thì khi chân TX kéo từ 1 xuống 0 là bắt đầu khung truyền, sau đó đợi 1 duration. 
- Sử dụng vòng for đọc liên tục 8 bit truyền vào. Nếu điều kiện trong if thỏa bằng 1 thì kéo chân TX lên HIGH và ngược lại nếu  = 0 thì để chân TX mức LOW.
- Mỗi bit gửi đi thì kèm theo 1 clock. 
- Sau khi gửi đủ 8 bit thì kéo chân TX lên để báo truyền xong.

## Hardware

```c
void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
```
- Cấu hình các xung clock cho các thiết bị ngoại vi.
```c
void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStruct;

    // PA9 TX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 RX
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```
PA9 (TX):
- GPIO_Mode_AF_PP: Cấu hình chân ở chế độ ngõ ra thay thế (Alternate Function Push-Pull) cho tín hiệu truyền UART.
PA10 (RX):
- GPIO_Mode_IN_FLOATING: Cấu hình chân ở chế độ ngõ vào không kéo (Floating Input) để nhận tín hiệu UART.
```c
void UART_Config() {
    USART_InitTypeDef UART_InitStruct;
    UART_InitStruct.USART_BaudRate = 9600;
    UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART_InitStruct.USART_Parity = USART_Parity_No;
    UART_InitStruct.USART_StopBits = USART_StopBits_1;
    UART_InitStruct.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART1, &UART_InitStruct);
    USART_Cmd(USART1, ENABLE);
}
```
- USART_BaudRate = 9600: Tốc độ baud là 9600 bps.
- USART_HardwareFlowControl = USART_HardwareFlowControl_None: Không sử dụng kiểm soát luồng phần cứng.
- USART_Mode = USART_Mode_Rx | USART_Mode_Tx: Kích hoạt cả chế độ nhận (Rx) và truyền (Tx).
- USART_Parity = USART_Parity_No: Không sử dụng bit chẵn lẻ.
- USART_StopBits = USART_StopBits_1: Sử dụng 1 bit dừng.
- USART_WordLength = USART_WordLength_8b: Sử dụng dữ liệu 8 bit trong mỗi khung truyền.

```c
void UART_SendDataArray(USART_TypeDef* USARTx, uint8_t* data, uint8_t size) {
    for (int i = 0; i < size; i++) {
        USART_SendData(USARTx, data[i]);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {}
        delay_us(1000);
    }
}
```
- USART_SendData(USARTx, data[i]);: Gửi từng byte trong mảng data.
- while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {}: Chờ cho cờ TXE (Transmit Data Register Empty) được bật.
- delay_us(1000);: Thêm khoảng trễ 1 ms để đảm bảo dữ liệu được gửi đi ổn định.

```c
uint8_t UART_ReceiveByte(USART_TypeDef* USARTx) {
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) {}
    return USART_ReceiveData(USARTx);
}
```
- while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET) {}: Chờ cho cờ RXNE (Receive Data Register Not Empty) được bật.
- return USART_ReceiveData(USARTx);: Đọc và trả về byte dữ liệu nhận được.