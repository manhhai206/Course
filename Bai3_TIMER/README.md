
# Advance C
## ** Buổi 3: Interrupt - Timer **
<details>
### Interrupt
Định nghĩa ngắt: Ngắt là 1 event làm cho vi điều khiển phải tạm dừng chương trình hiện tại để chuyển sang thực thi chương trình phục vụ ngắt (Interrupt Service Routine - ISR). Sau khi xử lý xong ngắt, MCU sẽ quay trở lại điểm trước đó và tiếp tục thực hiện công việc.

Khi một ngắt xảy ra, MCU sẽ tìm địa chỉ của ISR tương ứng (gọi là vector ngắt) trong bộ nhớ để thực thi mã xử lý ngắt. Mỗi loại ngắt có một ISR riêng biệt để đảm bảo sự kiện được xử lý đúng cách.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTtfqeiyc1dZCj767IYVPQ9tNJxGXDS90VSAQ&s)

#### Extenal Interrupt
Xảy ra khi có sự thay đổi điện áp của chân GPIO được cấu hình làm input.
Có 4 loại ngắt ngoài:
- LOW: ngắt được kích hoạt khi chân ở mức thấp
- HIGH: ngắt được kích hoạt khi chân ở mức cao
- RISING: ngắt được kích hoạt ở sườn lên
- LOW: ngắt được kích hoạt ở sườn xuống

#### Timer Interrupt
Ngắt timer: xảy ra khi thanh ghi đếm của timer bị tràn.Sau mỗi lần tràn thì phải reset lại thanh khi để có thể tạo ngắt tiếp theo.

#### Ngắt truyền thông
 Xảy ra khi truyền/nhận dữ liệu giữa MCU và thiết bị khác, thường sử dụng trong các giao thức UART, SPI,I2C... để đảm bảo luôn truyền được đẩy đủ data và chính xác.

#### Độ ưu tiên Ngắt
Mức độ ưu tiên - Priority được coi là mức độ khẩn cấp của ngắt, tức là quy định ngắt nào cần được thực hiện trước.

Nếu hai ngắt xảy ra cùng lúc thì sẽ tiếp nhận thực thi ngắt có mức độ ưu tiên cao hơn (priority value thấp hơn), và đưa ngắt còn lại vào trạng thái chờ - Pending.

Khi mà 1 ngắt xảy ra thì có 1 ngắt khác có mức độ ưu tiên cao hơn thì ngắt có priority thấp hơn sẽ được đưa vào Stack Pointer.

### Timer
Định nghĩa Timer: Timer là bộ đếm thời gian bằng cách đếm từng chu kỳ clock (đếm lên hoặc đếm xuống).

![](https://visualgdb.com/w/wp-content/uploads/tutorials/arm/stm32/timers/01-timer.png)

Trong STM32f103C8:
```c
    // đếm lên 1 lần với  mỗi 0.1 ms
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //72MHz
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;
	TIM_InitStruct.TIM_Period = 0xFFFF;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
```
- TIM_ClockDivision: bộ chia xung clock khi nạp vào.
- TIM_CounterMode: sau bao nhiêu dao động thì đếm lên 1 lần.
- TIM_Period: Set giá trị bị tràn, sau khi đếm quá giá trị thì sẽ bị reset về ban đầu
- TIM_CounterMode: Set chế độ đếm lên hay đếm xuống.
