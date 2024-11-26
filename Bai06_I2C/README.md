
# I2C Protocols

## I2C Software

### Stm32 with HW-111

```c
#define I2C_SCL     GPIO_Pin_6
#define I2C_SDA     GPIO_Pin_7
#define I2C_GPIO    GPIOB
```
- **I2C_SCL**: Chân được sử dụng để gửi tín hiệu clock cho I2C.
- **I2C_SDA**: Chân được sử dụng để truyền dữ liệu giữa Master và Slave.
- **I2C_GPIO**: Chỉ định Port GPIO mà các chân SCL và SDA đang sử dụng.

```c
#define WRITE_SDA_0 GPIO_ResetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SDA_1 GPIO_SetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SCL_0 GPIO_ResetBits(I2C_GPIO, I2C_SCL)
#define WRITE_SCL_1 GPIO_SetBits(I2C_GPIO, I2C_SCL)
#define READ_SDA_VAL GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)
```
- **WRITE_SDA_0**: Hàm này sử dụng GPIO_ResetBits để đặt chân SDA xuống mức logic thấp.
- **WRITE_SDA_1**: Hàm này sử dụng GPIO_SetBits để đặt chân SDA lên mức logic cao.
- **WRITE_SCL_0**: Hàm này sử dụng GPIO_ResetBits để đặt chân SCL xuống mức logic thấp.
- **WRITE_SCL_1**: Hàm này sử dụng GPIO_SetBits để đặt chân SCL lên mức logic cao.
- **READ_SDA_VAL**: Hàm này sử dụng GPIO_ReadInputDataBit để đọc giá trị hiện tại từ chân SDA. Hàm này trả về mức logic hiện tại của chân SDA, cho phép kiểm tra xem thiết bị có đang gửi dữ liệu 0 hay 1.

```c
typedef enum {
    NOT_OK = 0,
    OK = 1
} status;

typedef enum {
    NACK = 0,
    ACK = 1
} ACK_Bit;
```
Các định nghĩa này xác định trạng thái cho kết quả hoạt động OK hoặc NOT_OK và bit xác nhận ACK hoặc NACK.

```c
void RCC_Config() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
```
Cấu hình cấp xung clock cho các ngoại vi như GPIOB và Timer2.

```c
void TIM_Config() {
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_Prescaler = 72 - 1;
    TIM_InitStruct.TIM_Period = 0xFFFF;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_Cmd(TIM2, ENABLE);
}

void delay_us(uint32_t time) {
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time) {}
}
```
Setup Timer2 để tính hàm delay_us.

```c
void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = I2C_SDA | I2C_SCL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
}
```
Set up GPIO ở Mode Output Open Drain.

```c
void I2C_Config() {
    WRITE_SDA_1;
    delay_us(1);
    WRITE_SCL_1;
    delay_us(1);
}
```
Set up trạng thái ban đầu của I2C khi kéo 2 dây SDA và SCL lên mức 1.
```c
void I2C_Start() {
    WRITE_SDA_1;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    WRITE_SDA_0;
    delay_us(3);
    WRITE_SCL_0;
    delay_us(3);
}
```
Để bắt đầu khung truyền thì ban đầu 2 dây phải ở mức cao và lần lượt kéo dây SDA xuống mức thấp rồi delay 1 khoảng thời gian và kéo dây SCL xuông mức thấp để báo hiệu bắt đầu khung truyền.
```c
void I2C_Stop() {
    WRITE_SDA_0;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    WRITE_SDA_1;
    delay_us(3);
}
```
Để kết thúc khung truyền thì kéo dây SDA xuống mức thấp và lần lượt kéo SCL rồi kéo SDA lên mức cao theo thứ tự.
![](https://images.viblo.asia/full/fd35ce18-37a1-4185-8163-c63aa00c1fa7.png)

```c
status I2C_Write(uint8_t u8Data) {
	
    status stRet;
    for (int i = 0; i < 8; i++) {
        if (u8Data & 0x80) {
            WRITE_SDA_1;
        } else {
            WRITE_SDA_0;
        }
        delay_us(3);
				
        WRITE_SCL_1;
        delay_us(5);
        WRITE_SCL_0;
        delay_us(5);
        u8Data <<= 1;
    }

    WRITE_SDA_1;
    delay_us(3);
    WRITE_SCL_1;
    delay_us(3);
    
    if (READ_SDA_VAL) {
        stRet = NOT_OK;
    } else {
        stRet = OK;
    }
    delay_us(2);
    WRITE_SCL_0;
    delay_us(5);
    
    return stRet;
}
```
Ghi 1 byte dữ liệu:
- Bắt đầu với việc lấy một byte dữ liệu (u8Data) và sẽ gửi từng bit một qua chân SDA. Mỗi bit được kiểm tra bằng cách sử dụng phép | với bit mask 0x80.
- Nếu bit cao nhất  của byte là 1, thì chân SDA sẽ được kéo lên mức cao, và nếu không thì sẽ kéo xuống mức thấp.
Đợi xung clock:
- Sau khi thiết lập chân SDA, bạn đợi một thời gian để đảm bảo rằng thiết bị bên nhận có thể thấy tín hiệu trên SDA.
- Sau đó, chân SCL được kéo lên mức cao để tạo xung đồng hồ cho thiết bị bên nhận đọc giá trị trên SDA, rồi lại kéo về mức thấp để kết thúc chu kỳ xung đồng hồ.
Dịch trái 1 bit:
- Sau khi gửi một bit, bạn dịch byte dữ liệu sang trái (u8Data <<= 1) để chuẩn bị cho việc gửi bit tiếp theo. Điều này giúp kiểm tra từng bit một từ bit cao nhất xuống bit thấp nhất.
Đọc bit thứ 9 (ACK/NACK):
- Sau khi đã gửi đủ 8 bit, bạn kéo chân SDA lên 1 để chuẩn bị nhận bit ACK/NACK từ thiết bị bên nhận.
- Chân SCL lại được kéo lên mức cao để thiết bị bên nhận gửi phản hồi về chân SDA.
- Nếu chân SDA ở mức cao khi bạn đọc nó, điều đó có nghĩa là thiết bị bên nhận đã không xác nhận (NACK), trong khi mức thấp có nghĩa là thiết bị bên nhận đã xác nhận (ACK).

```c
uint8_t I2C_Read(ACK_Bit _ACK) {
    uint8_t u8Ret = 0x00;
	
    WRITE_SDA_1;
    delay_us(1);
	
    for (int i = 0; i < 8; ++i) {
        u8Ret <<= 1;
        WRITE_SCL_1;
        delay_us(3);
        if (READ_SDA_VAL) {
            u8Ret |= 0x01;
        }
        delay_us(2);
        WRITE_SCL_0;
        delay_us(5);
    }

    if (_ACK) {
        WRITE_SDA_0;
    } else {
        WRITE_SDA_1;
    }
    delay_us(1);
		
    WRITE_SCL_1;
    delay_us(5);
    WRITE_SCL_0;
    delay_us(5);
		
    return u8Ret;
}
```
- Trong vòng lặp for, hàm sẽ thực hiện việc đọc từng bit từ thiết bị bên nhận, tổng cộng 8 bit. Mỗi lần lặp, biến u8Ret sẽ được dịch trái (u8Ret <<= 1) để chuẩn bị cho việc lưu MSB trước.
-  Sau khi đọc đủ 8 bit thì đợi 1 clock, trong clock đó khi SCL đang ở mức cao thì đọc giữa xung cao SCL để đọc data SDA.
Gửi ACK hoặc NACK:
- Sau khi đọc đủ 8 bit, hàm kiểm tra tham số _ACK để xác định xem có nên gửi bit ACK hay NACK không.
- Nếu _ACK là true, chân SDA sẽ được kéo xuống mức thấp (WRITE_SDA_0) để gửi bit ACK. Nếu không, chân SDA sẽ được giữ ở mức cao (WRITE_SDA_1) để gửi bit NACK.

```c
status EPROM_Read(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    uint8_t i;
	
    I2C_Start();
    if (I2C_Write(SlaveAddr << 1) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
    if (I2C_Write(MemAddr >> 8) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
    if (I2C_Write(MemAddr) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }
		
	I2C_Start();
    if (I2C_Write((SlaveAddr << 1)|1) == NOT_OK) {
        I2C_Stop();
        return NOT_OK;
    }		
		
    for (i = 0; i < NumByte - 1; ++i) {
        pData[i] = I2C_Read(ACK);
    }
    pData[i] = I2C_Read(NACK);
    I2C_Stop();
    return OK;
}
```
Gửi Địa Chỉ Slave:
- Gọi I2C_Write(SlaveAddr << 1) để gửi địa chỉ của thiết bị slave với bit LSB là 0 (ghi dữ liệu). Nếu không nhận được ACK (trả về NOT_OK), dừng và gửi tín hiệu Stop, trả về NOT_OK.
Gửi Địa Chỉ Bộ Nhớ:
- Hai lần gọi I2C_Write() để gửi byte cao và thấp của địa chỉ bộ nhớ (MemAddr). Nếu không nhận được ACK cho bất kỳ lần gửi nào, dừng, gửi Stop và trả về NOT_OK.
Gọi I2C_Start() để bắt đầu một phiên giao tiếp mới.
Gửi Địa Chỉ Slave với Bit Đọc:
- Gửi địa chỉ slave với bit LSB là 1 (đọc dữ liệu). Nếu không nhận được ACK (trả về NOT_OK), dừng, gửi Stop và trả về NOT_OK.
Đọc Dữ Liệu Từ Slave:
- Trong vòng lặp, gọi I2C_Read(ACK) để đọc từng byte dữ liệu từ slave, gửi ACK cho tất cả ngoại trừ byte cuối. Đối với byte cuối, gọi I2C_Read(NACK) để thông báo không muốn nhận thêm dữ liệu.
Kết Thúc Giao Tiếp:
- Gọi I2C_Stop() để gửi tín hiệu Stop, kết thúc phiên giao tiếp.
Trả về trạng thái OK sau khi hoàn thành việc đọc dữ liệu.
```c
status EPROM_Write(uint16_t MemAddr, uint8_t SlaveAddr, uint8_t NumByte, uint8_t *pData) {
    uint8_t i;
	
    for (i = 0; i < NumByte; ++i) {
        I2C_Start();
        if (I2C_Write(SlaveAddr << 1) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        if (I2C_Write((MemAddr + i) >> 8) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        } 
        if (I2C_Write(MemAddr + i) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        if (I2C_Write(pData[i]) == NOT_OK) {
            I2C_Stop();
            return NOT_OK;
        }
        I2C_Stop();
        delay_us(10000); 
    }
    return OK;
}
```
Khởi tạo vòng lặp ghi:
- Hàm nhận vào các tham số: địa chỉ bộ nhớ (MemAddr), địa chỉ thiết bị slave (SlaveAddr), số byte cần ghi (NumByte), và con trỏ đến dữ liệu cần ghi (pData).
- Vòng lặp for sẽ lặp lại từ 0 đến NumByte - 1, cho phép ghi từng byte dữ liệu.
Gửi tín hiệu Start:
- Gọi hàm I2C_Start() để bắt đầu một phiên giao tiếp I2C.
Gửi địa chỉ Slave:
- Sử dụng hàm I2C_Write(SlaveAddr << 1) để gửi địa chỉ của thiết bị slave với bit LSB là 0 (chỉ rõ rằng master muốn ghi).
- Nếu không nhận được ACK (trả về NOT_OK), hàm sẽ dừng giao tiếp với I2C_Stop() và trả về NOT_OK.
Gửi địa chỉ bộ nhớ:
- Gửi byte cao của địa chỉ bộ nhớ bằng cách gọi I2C_Write((MemAddr + i) >> 8).
- Gửi byte thấp của địa chỉ bộ nhớ bằng cách gọi I2C_Write(MemAddr + i).
- MemAddr + i cho phép bạn ghi từng byte dữ liệu vào các địa chỉ liên tiếp trong EEPROM, bắt đầu từ MemAddr.
- Nếu không nhận được ACK cho bất kỳ lần gửi nào, hàm sẽ dừng giao tiếp và trả về NOT_OK.
Gửi dữ liệu:
- Gửi byte dữ liệu cần ghi từ pData[i] bằng cách gọi I2C_Write(pData[i]).
- Nếu không nhận được ACK, hàm sẽ dừng giao tiếp và trả về NOT_OK.
Kết thúc giao tiếp:
- Gọi hàm I2C_Stop() để gửi tín hiệu Stop, kết thúc phiên giao tiếp I2C.
Delay sau mỗi lần ghi:
- Gọi delay_us(10000) để đợi 10 ms giữa các lần ghi, điều này giúp đảm bảo rằng EEPROM có đủ thời gian để hoàn thành quá trình ghi.
Trả về trạng thái:
- Sau khi ghi xong tất cả các byte, hàm trả về OK.


