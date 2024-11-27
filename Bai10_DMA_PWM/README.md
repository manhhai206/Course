
# DMA

DMA (Direct Memory Access) là một cơ chế cho phép các thiết bị ngoại vi truyền dữ liệu trực tiếp dữ liệu đến bộ nhớ mà không cần CPU phải thực hiện từng bước truyền dữ liệu. DMA có thể làm giảm tải "áp lực làm việc" cho CPU. 

DMA có thể điều khiển data truyền từ SRAM đến Peripheral và ngược lại, mà không thông qua data bus của CPU. 

![](https://open4tech.com/wp-content/uploads/2020/04/DMA_block_diagram-1.jpg)

### Cấu hình DMA:

**MA_PeripheralBaseAddr** Địa chỉ cơ sở (base address) của ngoại vi mà DMA sẽ tương tác.
- DMA sẽ đọc dữ liệu từ địa chỉ này (nếu DMA_DIR_PeripheralSRC) hoặc ghi dữ liệu vào địa chỉ này (nếu DMA_DIR_PeripheralDST).

```
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
```
- Thanh ghi dữ liệu của SPI1 (SPI1->DR) được thiết lập làm nguồn hoặc đích dữ liệu cho DMA.

**DMA_MemoryBaseAddr** Địa chỉ cơ sở của vùng nhớ (RAM) mà DMA sẽ tương tác.
- DMA sẽ lưu dữ liệu nhận được từ ngoại vi hoặc đọc dữ liệu từ bộ nhớ để gửi tới ngoại vi.
```
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buffer;
```
- buffer là mảng lưu trữ dữ liệu được truyền/nhận.

**DMA_DIR** Hướng truyền dữ liệu của DMA.
- DMA_DIR_PeripheralSRC: Truyền dữ liệu từ ngoại vi (Peripheral) đến bộ nhớ (Memory).
- DMA_DIR_PeripheralDST: Truyền dữ liệu từ bộ nhớ (Memory) đến ngoại vi (Peripheral).
```c
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
```
- Nhận dữ liệu từ ngoại vi (SPI).

**DMA_BufferSize** Số lượng dữ liệu (theo đơn vị word, byte, hoặc half-word) mà DMA sẽ truyền trong một lần truyền.
```c
DMA_InitStructure.DMA_BufferSize = 16;
```
- DMA sẽ truyền 16 đơn vị dữ liệu trước khi dừng hoặc quay vòng (nếu DMA_Mode_Circular).

**DMA_PeripheralInc** Tùy chọn tăng địa chỉ ngoại vi sau mỗi lần truyền.
- DMA_PeripheralInc_Enable: Địa chỉ ngoại vi sẽ tự động tăng.
- DMA_PeripheralInc_Disable: Địa chỉ ngoại vi giữ nguyên.
```c
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
```
- Thường dùng khi ngoại vi chỉ có một thanh ghi cố định, như SPI1->DR.

**DMA_MemoryInc** Tùy chọn tăng địa chỉ vùng nhớ sau mỗi lần truyền.
- DMA_MemoryInc_Enable: Địa chỉ vùng nhớ tăng lên.
- DMA_MemoryInc_Disable: Địa chỉ vùng nhớ giữ nguyên (dùng cho một biến duy nhất).
```
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
```
- Lưu dữ liệu vào các vị trí tiếp theo trong buffer.

**DMA_PeripheralDataSize**Kích thước của mỗi đơn vị dữ liệu trên ngoại vi.
- DMA_PeripheralDataSize_Byte: 1 byte.
- DMA_PeripheralDataSize_HalfWord: 2 byte (16-bit).
- DMA_PeripheralDataSize_Word: 4 byte (32-bit).

**DMA_MemoryDataSize** Kích thước của mỗi đơn vị dữ liệu trong vùng nhớ.
- DMA_MemoryDataSize_Byte: 1 byte.
- DMA_MemoryDataSize_HalfWord: 2 byte (16-bit).
- DMA_MemoryDataSize_Word: 4 byte (32-bit).

**DMA_Mode** Chế độ hoạt động của DMA.
- DMA_Mode_Normal: DMA truyền dữ liệu một lần rồi dừng.
- DMA_Mode_Circular: DMA quay vòng liên tục sau khi hoàn thành mỗi buffer.

**DMA_Priority** Mức độ ưu tiên của kênh DMA.
- DMA_Priority_Low: Ưu tiên thấp.
- DMA_Priority_Medium: Ưu tiên trung bình.
- DMA_Priority_High: Ưu tiên cao.
- DMA_Priority_VeryHigh: Ưu tiên rất cao.

**DMA_M2M (Memory-to-Memory)** Chọn DMA có cho phép truyền từ bộ nhớ đến bộ nhớ (Memory-to-Memory) hay không ?
- DMA_M2M_Enable: Cho phép truyền dữ liệu từ RAM đến RAM.
- DMA_M2M_Disable: Chỉ cho phép truyền dữ liệu giữa ngoại vi và RAM.