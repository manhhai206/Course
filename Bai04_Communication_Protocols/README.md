
# Communication Protocols

## Truyền nhận dữ liệu

Các MCU truyền nhận dữ liệu với nhau hoặc với các thiết bị khác thông qua tín hiệu điện áp. MCU có thể giao tiếp song song như giao tiếp GPIO hay các chuẩn giao tiếp nối tiếp như UART, SPI, I2C...

## SPI

SPI là chuẩn giao tiêp nối tiếp có đồng bộ (sử dụng xung clock để đồng bộ tín hiệu). SPI hoạt động theo chế độ full - duplex (song công), vừa truyền vừa nhận tại cùng 1 thời điểm.

Chuẩn giao tiếp SPI có quan hệ master - slave. Master thường là là vi điều khiển, còn slave thường là cảm biến hay là các mcu khác  nhận lệnh từ master. Cấu hình đơn giản nhất của SPI là hệ thống một slave, một master duy nhất và có thể một master có thể điều khiển nhiều slave.

![](https://dientutuonglai.com/uploads/media/vi-dieu-khien/giao-tiep-spi.png?1615521775609)

- MOSI (Master Out Slave In) - truyền dữ liệu từ master đến slave. Chân MOSI ở master sẽ kết nối đến chân MOSI ở slave.

- MISO (Master In Slave Out) - truyền dữ liệu từ slave đến master. Chân MISO ở master sẽ kết nối đến chân MISO ở slave.

- SCK (Serial Clock) - xung clock phát ra từ master giúp cho master và slave đồng nhất với nhau tại từng thời điểm. 

- SS / CS (Slave Select / Chip Select) - chân CS được master sử dụng để lựa chọn slave cần giao tiếp. Để chọn slave giao tiếp với thiết bị master thì chỉ cần kéo chân CS xuống mức 0.

Một master có thể điều khiển nhiều hơn một slave:
![](https://upload.wikimedia.org/wikipedia/commons/thumb/9/97/SPI_three_slaves_daisy_chained.svg/1200px-SPI_three_slaves_daisy_chained.svg.png)

### Truyền dữ liệu

![](https://chuyenmuccongnghe.com/wp-content/uploads/2014/08/spi_5.jpg?w=710)

Khi SPI Master muốn giao tiếp với một SPI Slave, nó sẽ kéo tín hiệu SS của slave xuống mức thấp. Điều này giúp chọn slave cụ thể để bắt đầu quá trình truyền dữ liệu.

Tạo tín hiệu clock SCK: Sau khi tín hiệu SS đã kéo xuống, SPI Master tạo tín hiệu clock SCK trên đường dây này. SCK là tín hiệu đồng bộ hóa, quyết định thời điểm gửi và nhận dữ liệu.

Khi truyền dữ liệu từ SPI Master sang SPI Slave:

Tại một cạnh lên hoặc xuống của tín hiệu SCLK, SPI Master tạo điện áp mức cao hoặc thấp để biểu diễn 1 hoặc 0 trên đường MOSI. SPI Master sẽ duy trì điện áp này trong một chu kỳ clock của SCLK trước khi chuyển sang một mức điện áp khác để gửi đi bit tiếp theo trong chu kỳ clock kế tiếp. Việc tạo điện áp được gọi là setup.

SPI Slave nhận dữ liệu trên đường MOSI bằng cách lấy data điện áp trên đường dây này. Để thu được dữ liệu chính xác, SPI Slave phải lấy mẫu một bit dữ liệu trong khoảng thời gian từ khi SPI Master setup bit đó đến trước khi SPI Master setup bit kế tiếp.

**Tóm lại** trên đường MOSI, Master sẽ setup một bit ở một cạnh của SCLK, Slave sẽ chờ một nửa chu kỳ rồi mới lấy data bit đó ở cạnh kế tiếp của SCLK. SPI Master sẽ chờ thêm một nửa chu kỳ kể từ khi SPI Slave bắt đầu data rồi mới setup bit kế tiếp ở cạnh tiếp theo của SCLK. Cứ mỗi chu kỳ của SCLK, một bit sẽ được truyền đi.

Khi truyền dữ liệu từ Slave sang Master trên đường MISO, Slave setup tín hiệu còn Master thu data tín hiệu lần lượt ở mỗi cạnh của SCLK.

Khi quá trình truyền dữ liệu kết thúc, Master không gửi tín hiệu SCLK nữa và sau đó chuyển tín hiệu CS sang mức cao để Slave không thể thu hay setup data trên các đường MOSI/MISO.


**Hiện tại có 4 mode cơ bản**:

![](https://chuyenmuccongnghe.com/wp-content/uploads/2014/08/spi_7.jpg?w=710)

**CPOL(Clock Polarity)** xác định mức trạng thái mặc định (idle) của tín hiệu đồng hồ khi không có giao tiếp.

- CPOL = 0: Tín hiệu SCLK mặc định ở mức thấp khi không hoạt động. Xung đồng hồ bắt đầu với cạnh lên và kết thúc bằng cạnh xuống.

- CPOL = 1: Tín hiệu SCLK mặc định ở mức cao khi không hoạt động. Xung đồng hồ bắt đầu với cạnh xuống và kết thúc bằng cạnh lên.

**CPHA (Clock Phase)**  xác định tại cạnh nào của xung SCLK mà dữ liệu trên các chân MOSI và MISO được setup và thu.

- CPHA = 0:

     Dữ liệu được lấy mẫu (thu) tại cạnh đầu tiên của xung SCLK.

     Dữ liệu được thiết lập tại cạnh thứ hai của xung SCLK.

- CPHA = 1:

     Dữ liệu được thiết lập tại cạnh đầu tiên của xung SCLK.

     Dữ liệu được lấy mẫu (thu) tại cạnh thứ hai của xung SCLK.

Tổng hợp hai thông số CPOL và CPHA cho **4 MODE** :

![](https://kienltb.files.wordpress.com/2015/04/040515_0923_chungiaotip42.jpg?w=700)

- Mode 0 (CPOL = 0, CPHA = 0): dữ liệu được bên phát setup ở cạnh xuống của xung clock trước đó và được bên thu data ở cạnh lên của xung clock hiện tại.

- Mode 1 (CPOL =0, CPHA = 1): dữ liệu được bên phát setup ở cạnh lên của xung clock và được bên thu data ở cạnh xuống của xung clock.

- Mode 2 (CPOL =1, CPHA = 0): dữ liệu được bên phát setup ở cạnh lên của xung clock trước đó và được bên thu data ở cạnh xuống của xung clock hiện tại.

- Mode 3 (CPOL =1, CPHA = 1): dữ liệu được bên phát setup ở cạnh xuống của xung clock và được bên thu data ở cạnh lên của xung clock.


## I2C

I2C (Inter – Integrated Circuit) là 1 giao thức giao tiếp nối tiếp đồng bộ, sử dụng để truyền nhận dữ liệu giữa các IC với nhau chỉ sử dụng hai đường truyền tín hiệu.

Đặc điểm:
- Tốc độ không cao
- Thường sử dụng onboard với đường truyền ngắn
- Nối được nhiều thiết bị trên cùng một bus
- Giao tiếp đồng bộ, sử dụng Clock từ master
- Sử dụng 7 bit hoặc 10 bit địa chỉ
- Chỉ sử dụng 2 chân tín hiệu SDA, SCL
- Có 2 tốc độ tiêu chuẩn là Standard mode (100 kb/s)và Low mode (10 kbit/s)


I2C chỉ sử dụng hai dây để truyền dữ liệu giữa các thiết bị:

- SDA (Serial Data) - đường truyền cho master và slave để gửi và nhận dữ liệu.

- SCL (Serial Clock) - đường mang tín hiệu xung nhịp.

Các bit dữ liệu sẽ được truyền từng bit một dọc theo một đường duy nhất (SDA) theo các khoảng thời gian đều đặn được thiết lập bởi 1 tín hiệu đồng hồ (SCL).

![](https://dammedientu.vn/wp-content/uploads/2019/05/Basics-of-I2C-Communication.jpg)

### Cách hoạt động

Giao tiếp I2C bao gồm quá trình truyền nhận dữ liệu giữa các thiết bị chủ tớ, hay Master - Slave.

Master và Slave được kết nối với nhau bằng hai đường bus SCL và SDA đều hoạt động ở chế độ Open Drain, nghĩa là bất cứ thiết bị nào kết nối với mạng I2C này cũng chỉ có thể kéo 2 đường bus này xuống mức thấp (LOW), nhưng lại không thể kéo được lên mức cao. Vì để tránh trường hợp bus vừa bị 1 thiết bị kéo lên mức cao vừa bị 1 thiết bị khác kéo xuống mức thấp gây hiện tượng ngắn mạch. Do đó cần có 1 điện trờ ( từ 1 – 4,7 kΩ) để giữ mặc định ở mức cao.   

![](https://www.thegioiic.com/upload/large/44530.jpg)

Điều kiện **Start** và **Stop**:

- Điều kiện Start: SDA chuyển từ mức điện áp cao xuống mức điện áp thấp trước khi SCL chuyển từ mức cao xuống mức thấp.
- Điều kiện Stop: SDA chuyển từ mức điện áp thấp lên mức điện áp cao sau khi SCL chuyển từ mức thấp lên mức cao.

**Bit địa chỉ**: Được sử dụng để xác định thiết bị mục tiêu trong quá trình truyền nhận dữ liệu. Địa chỉ này có thể là địa chỉ vật lý 7 bit hoặc 10 bit.

**Bit R/W**: Xác định quá trình là gửi (write) hoặc nhận (read) dữ liệu. Bit này có giá trị '0' khi Master gửi dữ liệu và '1' khi Master nhận dữ liệu.

**Bit ACK/NACK**: Sau mỗi byte dữ liệu, thiết bị nhận phản hồi lại bằng bit ACK (Acknowledged) hoặc NACK (Not Acknowledged). Nếu thiết bị nhận dữ liệu thành công, nó sẽ gửi ACK (bit '0'), còn không thì gửi NACK (bit '1').

**Bit dữ liệu**: Mỗi khung dữ liệu bao gồm 8 bit dữ liệu. Sau khi Master gửi hoặc nhận một byte dữ liệu từ Slave, nó sẽ gửi một bit ACK/NACK để xác nhận việc nhận dữ liệu.


### Quá trình truyền nhận

Khi bắt đầu Master sẽ gửi đi 1 xung Start bằng cách kéo lần lượt các đường SDA, SCL từ mức 1 xuống 0.

Tiếp theo đó, Master gửi đi 7 bit địa chỉ tới các Slave cùng với bit Read/Write.

Slave sẽ so sánh địa chỉ vừa được gửi tới. Nếu trùng khớp, Slave sẽ xác nhận bằng cách kéo đường SDA xuống 0 và set bit ACK/NACK bằng ‘0’. Nếu không trùng khớp thì SDA và bit ACK/NACK đều mặc định bằng ‘1’.

Thiết bị Master sẽ gửi hoặc nhận khung bit dữ liệu. Nếu Master gửi đến Slave thì bit Read/Write ở mức 0. Ngược lại nếu nhận thì bit này ở mức 1.

Nếu như khung dữ liệu đã được truyền đi thành công, bit ACK/NACK được set thành mức 0 để báo hiệu cho Master tiếp tục.

Sau khi tất cả dữ liệu đã được gửi đến Slave thành công, Master sẽ phát 1 tín hiệu Stop để báo cho các Slave biết quá trình truyền đã kết thúc bằng các chuyển lần lượt SCL, SDA từ mức 0 lên mức 1.

### Các chế độ hoạt động của I2C:

- Chế độ chuẩn (standard mode) với tốc độ 100 kBit/s.
- Chế độ tốc độ thấp (low speed mode) với tốc độ 10 kBit/s.

## UART

UART (Universal Asynchronous Receiver-Transmitter) là một giao thức truyền thông  nối tiếp không đồng bộ và có thể cấu hình được tốc độ.

Giao thức UART là một giao thức đơn giản và phổ biến, bao gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). Dữ liệu được truyền và nhận qua các đường truyền này dưới dạng các khung dữ liệu (data frame) có cấu trúc chuẩn, với một bit bắt đầu (start bit), một số bit dữ liệu (data bits), một bit kiểm tra chẵn lẻ (parity bit) và một hoặc nhiều bit dừng (stop bit).

Thông thường, tốc độ truyền của UART được đặt ở một số chuẩn, chẳng hạn như 9600, 19200, 38400, 57600, 115200 baud và các tốc độ khác. Tốc độ truyền này định nghĩa số lượng bit được truyền qua mỗi giây. Các tốc độ truyền khác nhau thường được sử dụng tùy thuộc vào ứng dụng và hệ thống sử dụng.

![](https://dientutuonglai.com/uploads/media/arduino/giao-tiep-uart-giua-2-arduino-1.png?1615518866975)

Uart truyền dữ liệu nối tiếp, theo 1 trong 3 chế độ:

- Simplex: Chỉ tiến hành giao tiếp một chiều
- Half duplex: Dữ liệu sẽ đi theo một hướng tại 1 thời điểm
- Full duplex: Thực hiện giao tiếp đồng thời đến và đi từ mỗi master và slave

### Cách hoạt động

![](https://tapit.vn/wp-content/uploads/2018/06/1-2.png)

Chân Tx (truyền) của một chip sẽ kết nối trực tiếp với chân Rx (nhận) của chip khác và ngược lại. Quá trình truyền dữ liệu thường sẽ diễn ra ở 3.3V hoặc 5V. Uart là một giao thức giao tiếp giữa một master và một slave. Trong đó 1 thiết bị được thiết lập để tiến hành giao tiếp với chỉ duy nhất 1 thiết bị khác.

Dữ liệu truyền đến và đi từ Uart song song với thiết bị điều khiển. Khi tín hiệu gửi trên chân Tx (truyền), bộ giao tiếp Uart đầu tiên sẽ dịch thông tin song song này thành dạng nối tiếp và sau đó truyền tới thiết bị nhận. Chân Rx (nhận) của Uart thứ 2 sẽ biến đổi nó trở lại thành dạng song song để giao tiếp với các thiết bị điều khiển.

Dữ liệu truyền qua Uart sẽ đóng thành các gói (packet). Mỗi gói dữ liệu chứa 1 bit bắt đầu, 5 – 9 bit dữ liệu (tùy thuộc vào bộ Uart), 1 bit chẵn lẻ tùy chọn và 1 bit hoặc 2 bit dừng.

Quá trình truyền dữ liệu Uart sẽ diễn ra dưới dạng các gói dữ liệu này, bắt đầu bằng 1 bit bắt đầu, đường mức cao được kéo dần xuống thấp. Sau bit bắt đầu là 5 – 9 bit dữ liệu truyền trong khung dữ liệu của gói, theo sau là bit chẵn lẻ tùy chọn để nhằm xác minh việc truyền dữ liệu thích hợp. Sau cùng, 1 hoặc nhiều bit dừng sẽ được truyền ở nơi đường đặt tại mức cao. Vậy là sẽ kết thúc việc truyền đi một gói dữ liệu