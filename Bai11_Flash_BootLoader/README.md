
# FLASH

**RAM**
- Tốc độ đọc ghi nhanh.
- Không cần xóa trước khi ghi, ghi và đọc trực tiếp.
- Dữ liệu bị mất đi không co nguồn.
=> Lưu trữ giá trị tạm thời, biến đổi liên tục trong chương trình

**FLASH**
- Tốc độ ghi chậm nhưng đọc nhanh.
- Phải xóa cả page trước khi ghi và ghi theo từng page.
- Dữ liệu không bị mất đi khi bị mất nguồn.
- Giới hạn số lần xóa/ghi.
=> Lưu trữ chương trình (firmware) và dữ liệu cố định

**EPROM**
- Tương tự FLASH nhưng đọc ghi theo từng byte
- Phải xóa trước khi ghi
=> Lưu trữ giá trị cần giữ lâu dài.

## FLASH
- FLASH sẽ chia thành các page để quản lý.
-  Mỗi page có kích thước 1kb
- Trước khi ghi thì phải xóa. Mỗi lần xóa thì xóa cả page(Oxff)
- Mỗi lần ghi thì chỉ ghi Half hay 1word tại 1 thời điểm
- Flash có giới hạn số lần  xóa/ghi
- Bắt đầu từ địa chỉ 0x0800 0000 và có 128 page
![](https://tapit.vn/wp-content/uploads/2018/08/1-3-e1544774495858.png)

### Đọc và ghi bộ nhớ Flash
- Xóa bộ nhớ Flash
![](https://tapit.vn/wp-content/uploads/2018/08/2-3.png)
```c
void Flash_Erase(uint32_t pageAddress) {
    FLASH_Unlock(); 
    while (FLASH_GetFlagStatus(FLASH_FLAG_BSY)) {} 
    
    FLASH->CR |= FLASH_CR_PER;          
    FLASH->AR = pageAddress;           
    FLASH->CR |= FLASH_CR_STRT;         

    while (FLASH->SR & FLASH_SR_BSY) {} 
    FLASH->CR &= ~FLASH_CR_PER;        
    FLASH_Lock(); 
}
```
```c
    FLASH_Unlock(): 
```
- unlock bộ điều khiển flash để cho phép thực hiện các thao tác như xóa hoặc ghi. Nếu không unlock, bộ nhớ flash sẽ bị bảo vệ và không thể chỉnh sửa.
```c
    while (FLASH_GetFlagStatus(FLASH_FLAG_BSY))
```
- Chờ flash sẵn sàng: Dòng này kiểm tra trạng thái của flash để đảm bảo rằng nó không bận (busy) với các thao tác khác trước khi thực hiện xóa.
```c
    FLASH->CR |= FLASH_CR_PER;         \
``` 
- Kích hoạt chế độ xóa trang: Đặt bit PER (Page Erase) trong thanh ghi điều khiển FLASH->CR để chuẩn bị xóa một trang.
```c

    FLASH->AR = pageAddress;    
 ```       
- Chỉ định địa chỉ trang cần xóa: Ghi địa chỉ trang cần xóa vào thanh ghi FLASH->AR (Address Register).
```c
    FLASH->CR |= FLASH_CR_STRT;  
```      
- Bắt đầu xóa: Đặt bit STRT (Start) trong thanh ghi điều khiển FLASH->CR để bắt đầu thao tác xóa trang.
```c
    while (FLASH->SR & FLASH_SR_BSY)
```
- Chờ quá trình xóa hoàn thành: Kiểm tra bit BSY (Busy) trong thanh ghi trạng thái FLASH->SR để đảm bảo quá trình xóa đã hoàn tất.
```c
    FLASH->CR &= ~FLASH_CR_PER;      
```  
- Tắt chế độ xóa trang: Xóa bit PER để dừng chế độ xóa trang, tránh các thao tác xóa không mong muốn.
```c
    FLASH_Lock(); 
```
- FLASH_Lock(): Khóa lại bộ điều khiển flash sau khi hoàn thành thao tác, đảm bảo flash được bảo vệ.

## Bootloader

Bootloader là 1 chương trình và là chương trinh đầu tiên chạy khi Chip được khởi động. Nhiệm vụ của Bootloader là kiểm tra xem các điều kiện để lựa chọn thực thi 1 trương trình; firmware update hay firmware current.

Mục tiêu chính của Bootloader là update hoặc fix các lỗi phần mềm hệ thống mà không cần can thiệp trực tiếp mà có thể update từ xa.
Nó cũng cos thể dùng để quản lý các ứng dụng hay sử dụng các giao thưc UART, CAN, I2C, I2S , Ethernet và USB để thiết lập giao tiếp và cập nhật firmware.

### Cấu trúc và cách hoạt động của Bootloader
**Start or Reset**
- Khi STM32 khởi động hoặc bị reset thì chương trình sẽ bắt đầu tại vị đầu tiên trong bộ nhớ FLASH 0x0800 0000. Đây là vị trí Bootloader đầu tiên được lưu trữ và thực thi đầu tiên.

**Kiểm tra chương trình hiên tại**
- Thì Bootloader sẽ kiếm tra xem sau khi kích hoạt thì có điều kiện nào cần thiết để chuyển đến chương trình mới hay không: 
+ Kiểm tra xem APP update có chương trình nào mới không
+ Nếu không có sự thay đổi và nó tiếp tục nhảy vài app current để thực thi chương trình hiện tại.

**Chạy chương trình hiện tại**
- Nếu kh có update firmware thì vẫn sẽ nhảy đến chương trình firmware hiện tại được lưu trên FLASH

**Cập nhập firmware từ xa**
- Bootloader hỗ trợ cập nhật firmware từ xa mà không cần can thiệt trực tiếp vào phần cứng. Thông qua các giao thức như UART, I2C, I2S, Ethernet, USB có thể giao tiếp và cập nhật firmware.

### Hoạt động của hàm Boot
**Lấy địa chỉ new firmware**
- thi Bootloader sẽ lấy địa chỉ của chương trình firmware vùng nhớ FLASH
**Tát tất cả ngắt và chương trình lỗi**
- Trước khi chuyển sang firmware mới khi Bootloader sẽ tắt tất cả các ngắt và đảm bảo không có lỗi phần mềm trong quá trình chuyển đổi.
**Nhảy sang chương trình mới**
- Bootloader sẽ thiết lập đại chỉ MSP để trỏ đến vị trí firmware mới.
- Sau đó Bootloader sẽ lấy địa chỉ tại MSP để  nhảy đến vị trí mới lưu trữ.
**Gọi ngắt RS**
- Khi đã nhảy đến vị trí mới, Bootloader sẽ gọi ngắt Reset để khởi động lại hệ thống và thực thi firmware mới.

