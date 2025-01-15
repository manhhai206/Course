
# **LIN**

LIN(Local Interconnect Network) sinh ra nhằm giảm thiểu sự phức tạp và chi phí trong truyền thông giữa các thiết bị điện tử đơn giản trong xe.

Lin thường được sử dụng trong các ứng dụng điều khiển các chức năng không an toàn của xe như điều khiển cửu sổ, đèn, gương  và điều hòa không khí...

![](https://static.wixstatic.com/media/cb0e64_3a9cfaeaa9ca437fa8e4c98a9a0cd103~mv2.png/v1/fill/w_512,h_313,al_c,q_85,enc_auto/cb0e64_3a9cfaeaa9ca437fa8e4c98a9a0cd103~mv2.png)

## **Đặc điểm**
- Mô hình  Master -Slave
- Node Slave chỉ phản hồi yêu cầu từ Master
- Master "quét" yêu cầu đến tất cả Slave để thăm dò thông tin
- Master có dữ liệu từ Slave gửi lên bus CAN để đi tới LIN khác
- LIN sử dụng giao thức UART để truyền /nhận dữ liệu với khung truyền 1 start, 8 bit data và 1 hoặc 2 stop bit

![](https://www.mouser.vn/images/marketingid/2018/microsites/0/TI_TLIN1024-Q1_simpsch.png)

## **Cấu trúc khung LIN**

![](https://canlogger1000.csselectronics.com/img/intel/lin-bus/LIN-Bus-Frame-Message-Header-Response-Master-Slave.png)
### **1.  Break Field (Trường Break)**
- **Break Field** là phần đầu tiên của khung truyền LIN, bao gồm một chuỗi các bit 0 dài hơn một ký tự truyền thông thường (ít nhất 13 bit). Nó có vai trò như một tín hiệu báo hiệu cho các node slave biết rằng một khung truyền mới sắp bắt đầu.
    - Chức năng: Trường Break giúp các node slave nhận biết rằng master đang chuẩn bị gửi một khung truyền và giúp chúng đồng bộ lại trạng thái nhận dữ liệu. Vì mạng LIN sử dụng truyền thông không đồng bộ, trường Break đóng vai trò quan trọng trong việc đồng bộ các thiết bị trên bus.
    - Cách hoạt động: Khi master phát ra Break, tất cả các node slave sẽ ngừng bất kỳ hoạt động nào đang thực hiện và chuẩn bị nhận dữ liệu từ master. Thời gian của Break dài hơn một ký tự UART tiêu chuẩn để đảm bảo tất cả các node slave nhận ra tín hiệu này.

### **2. Sync Field (Trường Đồng bộ)**
- Sync Field là phần thứ hai của khung LIN, và nó luôn có giá trị cố định là 0x55 (01010101 trong nhị phân). Đây là byte đồng bộ hóa giúp các node slave điều chỉnh tốc độ truyền của chúng cho phù hợp với node master.
    - Chức năng: Trường Sync đảm bảo rằng tất cả các node slave trong mạng LIN có thể đồng bộ hóa tốc độ truyền (baud rate) với master. Vì LIN sử dụng giao tiếp không đồng bộ dựa trên UART, các node slave cần đảm bảo rằng chúng nhận và gửi dữ liệu với cùng tốc độ như master. Trường Sync đóng vai trò như một mẫu chuẩn để slave so sánh và điều chỉnh tốc độ truyền của mình.
    - Lý do chọn giá trị 0x55: Giá trị 0x55 được chọn vì nó có dạng xen kẽ giữa các bit 0 và 1, giúp dễ dàng phát hiện lỗi trong quá trình đồng bộ hóa. Các bit 1 và 0 xen kẽ này cung cấp một tín hiệu mạnh mẽ để các node slave hiệu chỉnh tốc độ truyền.
### **3. Identifier Field (Trường định danh - ID)**
- Identifier Field (ID) chứa thông tin quan trọng về loại khung dữ liệu và định danh của node slave cần phản hồi. Trường ID gồm 6 bit dữ liệu và 2 bit kiểm tra chẵn lẻ (parity). Mỗi khung ID đại diện cho một loại thông điệp hoặc chức năng trong hệ thống và được sử dụng để xác định node slave nào cần phản hồi.
    - 6 bit ID (Bit 0 - 5): Xác định loại thông điệp hoặc hành động cần thực hiện. 6 bit này cho phép có tối đa 64 ID khác nhau, và mỗi ID đại diện cho một nhóm dữ liệu cụ thể (ví dụ: dữ liệu từ cảm biến nhiệt độ, điều khiển động cơ, v.v.).
    - 2 bit Parity (Bit 6 - 7): Hai bit này được sử dụng để kiểm tra chẵn lẻ nhằm phát hiện lỗi khi truyền ID. Parity trong LIN là parity bảo vệ, được tính toán dựa trên 6 bit ID. Có hai loại parity là "even parity" (chẵn) và "odd parity" (lẻ), giúp phát hiện nếu có bất kỳ lỗi đơn bit nào xảy ra trong quá trình truyền ID.
        - P0 được tính bằng phép XOR giữa bit 0, bit 1, bit 2 và bit 4 của ID.
        - P1 được tính bằng phép XOR giữa bit 1, bit 3, bit 4, và bit 5 của ID.
- Với 2 bit kiểm tra này, node slave có thể phát hiện lỗi trong quá trình truyền ID và báo cáo lỗi nếu cần thiết.

### **4. Data Field (Trường dữ liệu)**
- Data Field là phần chứa nội dung dữ liệu chính được truyền giữa các node trong mạng LIN. Trường này có độ dài từ 2 đến 8 byte, tùy thuộc vào loại thông tin được gửi.
    - Chức năng: Trường Data chứa thông tin điều khiển, trạng thái của các thiết bị hoặc dữ liệu cảm biến. Nội dung của trường Data phụ thuộc vào loại thông điệp được truyền, và nó có thể bao gồm các lệnh điều khiển, phản hồi từ cảm biến, hoặc các trạng thái hệ thống.
    - Số lượng byte: Số byte dữ liệu truyền trong trường Data phụ thuộc vào yêu cầu của hệ thống. LIN cho phép truyền tối đa 8 byte dữ liệu trong một khung, nhưng các khung nhỏ hơn với 2 hoặc 4 byte dữ liệu cũng được sử dụng phổ biến trong các hệ thống đơn giản.

### **5. Checksum Field (Trường kiểm tra tổng)**
Checksum Field là byte cuối cùng trong khung LIN, được sử dụng để phát hiện lỗi trong quá trình truyền dữ liệu. Checksum giúp đảm bảo rằng dữ liệu không bị thay đổi trong quá trình truyền từ master đến slave hoặc ngược lại. LIN có hai loại checksum:
- Classic Checksum:
    + Được sử dụng cho tất cả các khung truyền ngoại trừ khung chứa trường ID.
    + Checksum được tính toán dựa trên các byte dữ liệu trong trường Data. Giá trị checksum là tổng (không dấu) của tất cả các byte dữ liệu, sau đó lấy phần bù của tổng này.
    + Cách tính toán checksum này đảm bảo rằng nếu có bất kỳ thay đổi nào trong dữ liệu, giá trị checksum sẽ khác đi và hệ thống sẽ phát hiện ra lỗi.
- Enhanced Checksum:
    + Được sử dụng trong các phiên bản LIN mới hơn và bao gồm cả byte ID trong phép tính checksum.
    + Tương tự như Classic Checksum, Enhanced Checksum tính tổng tất cả các byte trong khung (bao gồm cả byte ID), sau đó lấy phần bù của tổng này.
    + Phương pháp này cung cấp mức độ bảo mật cao hơn cho dữ liệu, đặc biệt là khi byte ID có vai trò quan trọng trong việc xác định loại thông điệp.


## **Qúa trình truyền thông**

Master sẽ gửi **Header** cho Slave trước.
- Nếu Master yêu cầu dữ liệu từ Slave thì Slave sẽ **Response** gửi lại.
- Nếu Master muốn gửi dữ liệu cho Slave thì gửi kèm **Response** cho Slave
Slave sẽ xem ID có khớp với mình không, nếu có thì xử lý nếu không thì bỏ qua.


![](https://canlogger1000.csselectronics.com/img/intel/lin-bus/LIN-Bus-Data-Flow-Transmission-Header-Response.png)

