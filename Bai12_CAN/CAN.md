# **CAN BUS**

**Controller Area Network (CAN)** là một giao thức nối tiếp hỗ trợ mạnh mẽ cho các hệ thống điều khiển thời gian thực phân tán **(Distributed Real-time Control System)**.

Giao thức này được sử dụng rộng rãi, đặc biệt trong ngành ô tô, cho phép các vi điều khiển và các thiết bị giao tiếp trực tiếp mà không cần máy tính chủ.

![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-protocol-part1-pic2-2.png)

# **Kiến trúc**
##  **1. Bus topology**

Giao thức CAN sử dụng cấu trúc **bus topology** để kết nối các thiết bị **(node)**. Tất cả các thiết bị được kết nối song song vào một cặp dây truyền thông chung gọi là **CAN bus**.

CAN có đường dây đơn giản gồm 2 dây chính là:
- **CANH (CAN HIGH)**: Dây tín hiệu cao.
- **CANL (CAN LOW)**: Dây tín hiệu thấp.

Các tín hiệu truyền qua bus CAN gọi là tín hiệu **vi sai** (different signaling), nghĩa là thông tin được mã hóa dựa trên sự chênh lệch điện áo giữa 2 dây CANH và CANL.

- **Chống nhiễu**: Nhiễu môi trường tác động đồng đều lên cả hai dây, giúp bộ thu loại bỏ nhiễu chung.

- **Tín hiệu ổn định trên khoảng cách xa**: CAN bus có thể truyền tín hiệu ổn định ở tốc độ cao lên đến hàng trăm mét.

## **2. Điện trở kết thúc và trở kháng đặc trưng**

Khi tín hiệu chạy qua dây cáp và gặp một sự thay đổi về trở kháng (như tại điểm cuối dây), tín hiệu sẽ bị phản xạ ngược lại. Điều này gây ra nhiễu hoặc méo tín hiệu.

Điện trở 120 ohm được đặt ở hai đầu dây để:
- Khớp với trở kháng đặc trưng của dây (120 ohm).
- Hấp thụ tín hiệu thay vì để tín hiệu phản xạ lại.

Trở kháng đặc trưng (characteristic impedance) là một thuộc tính của dây cáp, phụ thuộc vào các yếu tố:
- Đường kính của dây dẫn.
- Khoảng cách giữa hai dây (CANH và CANL).
- Loại vật liệu cách điện giữa hai dây.
    
![](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEjJzsKyxaD_sQHwILOMuOLc0SV3Df5Tb64uYCUDKF62MVwz4CExMRGIME_QK_P6VWYMQZZlDcQC5y7BC5Utcq1WExcU6a5Lb8RwHglhM7OYvsOX_HiKBOxXC_vGuPGXghNdENhYHdbYBgrB/s1600/4.CAN_bus_structure_and_Node.png)


Hai dây tín hiệu này được xoắn tạo thành đường dây dôi giúp:
- **Giảm thiều nhiễu từ môi trường bên ngoài**:Khi các dây được xoắn lại, mỗi đoạn của cặp dây sẽ nhận nhiễu với cường độ khác nhau và theo các hướng ngược nhau, làm triệt tiêu phần lớn nhiễu điện từ.
- **Giảm thiểu nhiễu xuyên âm**: Việc xoắn đôi các dây giúp giảm hiện tượng này bằng cách phân tán nhiễu xuyên âm ra khắp chiều dài của cáp.

## **3. CAN Node**

Mỗi một nút CAN yêu cầu phải có một MCU kết nối với một CAN – Controller. CAN – Controller sẽ được kết nối với CAN – Transceiver thông qua một đường ra dữ liệu nối tiếp Tx và một đường vào dữ liệu nối tiếp Rx.

- **Microcontroller - MCU** thực thi các chức năng chính, điều khiển chính của một Node. Thực hiện cấu hình hoạt động cho CAN controller, phân phối dữ liệu cần truyền đến CAN controller, lấy dữ liệu nhận từ CAN controller để sử dụng cho hoạt động của Node.
- **CAN controller** thực thi các xử lý về truyền nhận dữ liệu, báo lỗi, tính toán thời gian bit, ... theo chuẩn CAN quy định; phát dữ liệu cần truyền dạng số (theo mức logic 0/1) ra chân TX; nhận dữ liện dạng số qua chân RX.
- **CAN transceiver** hoạt động như bộ chuyển đổi từ tín hiệu số (mức logic 0/1) trên đường TX thành tín hiệu tương tự trên bus CAN và ngược lại, chuyển đổi từ tín hiệu tương tự trên bus CAN (CAN_H và CAN_L) thành tín hiệu số trên đường RX

![](https://canlogger1000.csselectronics.com/img/ecu-electronic-control-unit-can-bus-node.svg)

## **4. Tín hiệu trên bus CAN**

CAN transceiver chuyển đổi qua lại giữa tín hiệu số (giao tiếp với CAN controller) và tương tự (giao tiếp với bus CAN). Trong giao thức CAN:
- Mức dominant, nghĩa là "mức trội" hay "mức chiếm ưu thế", là mức logic 0
- Mức recessive, nghĩa là "mức lặn" hay "mức ẩn", là mức 1

Có 2 dạng truyền :
- Truyền CAN LOW SPEED
- Truyền CAN HIGH SPEED

### **1. CAN HIGH SPEED**
- Tốc độ 125 kb/s tới 1Mb/s 
- Vi sai ở mức "dominant" là 2V
- Vi sai ở mức "recessive" là 0V

![](https://lh3.googleusercontent.com/proxy/aU4DMUse0PrRJt8rv5vfn3GZv1GQusgmFyTYfy_2yatflDTbFxgHb7662MwGR_G9ffz9pS7ufOi_XzGDbYUpZE8k4HAovrWg4emExg)

### **2. CAN LOW SPEED**
- Tốc độ đạt đến 125 kb/s 
- Vi sai ở mức "dominant" là 3V
- Vi sai ở mức "recessive" là 1.5 V

![](https://lh3.googleusercontent.com/proxy/wh-szaMu5Zyh_5_xQJLH3S6zbQgqFe5MsBM381lHAbs-4_PpWTXid1_qnwyPlCyuvzPXi-Kpw8DMVhsZo509LlbttuoczUs)

Vì tính chất vi sai trên đườnng truyền tín hiệu của bus CAN, sự miễn trừ tác động điện từ được bảo đảm vì 2 dây của bus đều bị tác động như nhau cùng một lúc bởi tín hiệu nhiễu. Vì vậy CAN bus thường được xoắn vào nhau đễ triệt tiêu nhiễu.

## **5. Giải quyết tranh chấp trên bus**
Khi một node gửi thông điệp, thông điệp đó sẽ được phát sóng đến tất cả các node khác trên bus. Tuy nhiên, không phải tất cả các node đều xử lý thông điệp này. Mỗi node sẽ sử dụng bộ lọc để kiểm tra xem thông điệp có phù hợp với mình hay không.

Một đặc điểm quan trọng của mạng CAN là khả năng giải quyết tranh chấp quyền gửi dữ liệu giữa các node. Nếu có nhiều node cùng muốn gửi dữ liệu lên bus cùng một lúc, cơ chế arbitration sẽ được thực hiện:
- Mỗi thông điệp CAN có một ID ưu tiên. Node nào có thông điệp với ID ưu tiên thấp hơn (tức có độ ưu tiên cao hơn) sẽ chiếm quyền truy cập bus và gửi thông điệp trước.
- Những node khác có ID ưu tiên cao hơn sẽ tự động dừng lại và chờ lượt tiếp theo để gửi thông điệp.
- Quá trình arbitration diễn ra mà không gây mất dữ liệu hay làm gián đoạn các thiết bị khác, vì thế mạng CAN là một hệ thống non-destructive (không gây mất dữ liệu).

![](https://images.javatpoint.com/tutorial/computer-network/images/can-protocol9.png)

# **Khung truyền của CAN**
Trong giao thức CAN (Controller Area Network), có 4 loại frame chính: 
- Data Frame
- Remote Frame
- Error frame 
- Overload Frame. 

## **CAN Frame**
Dữ liệu CAN được truyền dưới dạng các Frame (khung). Một khung có dạng chung như sau:

![](https://www.researchgate.net/publication/339370805/figure/fig1/AS:863892452425729@1582979419748/Format-of-a-CAN-data-frame-Every-CAN-data-frame-consists-of-Start-Of-Frame-SOF.png)


Chuẩn CAN định nghĩa bốn loại Frame: 
- **Data frame** dùng khi node muốn truyền dữ liệu tới các node khác
- **Remote frame** dùng để yêu cầu truyền data frame. 
- **Error frame** và **overload frame**  dùng trong việc xử lý lỗi.

### **1. Data Frame**
Dùng để truyền dữ liệu. 

Có hai dạng: **standard frame** và **extended frame**

![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-P2-pic1.png)

Một data frame có 7 trường khác nhau:

**Trường bắt đầu (Start of Frame Field - SOF)**: trường bắt đầu là vị trí của bit đầu tiên trong khung. Trường này chiếm 1 bit data. Bit đầu tiên là một dominant bit(0) để đánh dấu bắt đầu khung truyền.

**Trường xác định quyền ưu tiên (Arbitration)**: Định dạng vùng xác định quyền ưu tiên là khác nhau với dạng khung chuẩn và khung mở rộng
- Định dạng chuẩn: vùng xác định quyền ưu tiên có 12bit, bao gồm 11bit ID và 1bit RTR
- Định dạng mở rộng: trường xác định quyền ưu tiên có độ dài 32bit bao gồm 29bit ID, 1 bit SRR, 1bit IDE và 1 bit RTR.
- RTR (Remote Transmittion Request) : Là bit dùng để phân biệt khung là Data Frame hay Remote Frame.
    - Nếu Data Frame thì bit này luôn là 0 ( dominant bit)
    - Nếu Remote Frame thì bit này luôn bằng 1 (recessive bit)
    - Nếu trường hợp Data Frame và Remote Frame cùng ID được gửi đi đồng thời thì Data Frame sẽ được ưu tiên trước.
- SRR (Substitute Remote Request):Bit này chỉ có ở khung mở rộng và giá trị là 1 (recessive bit).
**Trường điều khiển (control Field)**: khung chuẩn và khung mở rộng có sự khác nhau
- Khung chuẩn gồm IDE, r0 và DLC (Data Length Code).
- Khung chuẩn mở rộng gồm r1,r0 và DLC.
    + Bit r0, r1(hai bit dự trữ): phải được truyền là recessive bit bởi bộ truyền nhưng không quan tâm đến 2 bit này.
    + DLC: có độ dài 4 bit quy định số byte của trường dữ liệu của Data Frame, chỉ được mang giá trị từ 0 đến 8.
**Trường dữ liệu (Data Field)**: Trường này có độ dài 0 đến 8 byte tùy vài giá trị của DLC ở trường điều khiển.

![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-P2-pic2.png)

**Trường kiêm tra (Cyclic Redun)dancy Check Field - CRC)**: Trường CRC gồm 16 bit và chia thành 2 phần:
- CRC Sequence gồm 15 bit CRC tuần tự.
- CRC Delimiter: là 1 recessive bit làm nhiệm vụ phân cacshhs trường CRC với ACK

![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-P2-pic12.png)

**Trường xác nhận (Acknowledge Field - ACK)**: có độ dài 2 bit bao gồm 2 phần:
- ACK Slot: có độ dài 1 bit, Node truyền dữ liệu sẽ truyền bit này là recessive. Khi một hoặc nhiều Node nhận chính xác thông điệp( không có lỗi và đã so sánh với CRC Sequence trùng khớp) thì nố sẽ  báo lại cho bộ truyền bằng cách truyền ra 1 dominant bit này vị trí ACK Slot để ghi đè lên recessive bit của bộ truyền.
- ACK Delimiter: có độ dài 1 bit, nó luôn là một recessive bit.Như vậy ACK bit luon đặt giữa 2 recessive bit của CRC Delimiter và ACK Delimiter.
**Trường kết thúc ( End of Frme Field)**":Trường EOF là trường thông báo kết thúc 1 Data frame hay Remote frame. Trường này gồm 7 recessive.

### **2. Remote Frame**
- Remote Frame được sử dụng để yêu cầu dũ liệu, tức là Data Frame từ bất kỳ Node nào trên cùng bus.
- Remote Frame giống như Data Frame, nó có 2 đặc điểm quan trọng
    + Nó được đánh dấu rõ ràng là Remote Frame ( RTR bit trong trường xác định quyền ưu tiên là recessive)
    + Không có trường dữ liệu
- Remote frame truyeebf ở cả 2 định dạng tiêu chuẩn và định dạng mở rộng
![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-P2-pic5.png)

![](https://www.peritec.vn/wp-content/uploads/2020/07/CAN-P2-pic6.png)

### **3. Error Frame**
Error Frame là khung được tự động phát ra bởi một node CAN khi nó phát hiện lỗi trong quá trình giao tiếp. Khung này có mục đích thông báo cho các node khác trong mạng về việc phát hiện lỗi và yêu cầu quá trình truyền thông được khởi động lại. Error Frame không được người dùng gửi trực tiếp, mà phần cứng CAN sẽ tự động phát hiện và phát ra khi có lỗi.

Trong giao thức CAN, có 3 loại Error Frame:
- **Active Error Frame**: Được phát ra bởi một node đang trong trạng thái Active Error, có thể can thiệp để sửa lỗi. Node này sẽ phát ra 6 bit Error Flag.
- **Passive Error Frame**: Được phát ra bởi một node trong trạng thái Passive Error, khi nó đã gặp nhiều lỗi nhưng không thể sửa lỗi. 12 bit Error Flag được gửi thay vì 6 bit
- **Bus Off**: Node rơi vào trạng thái Bus Off khi số lượng lỗi tích lũy vượt qua một ngưỡng cao hơn. Node bị ngắt kết nối hoàn toàn khỏi bus.
Cấu trúc của Error Frame:
- **Error Flag**: 6 hoặc 12 bit, phụ thuộc vào trạng thái lỗi (Active hoặc Passive).
- **Error Delimiter**: 8 bit để phân tách Error Frame với các khung khác.

![](https://elearning.vector.com/pluginfile.php/514/mod_page/content/5/CAN_3.1_GRA_ErrorFrame_EN.png)

Error Frame xảy ra khi một node phát hiện một trong các lỗi sau trong quá trình truyền dữ liệu:
- Bit Error: Xảy ra khi một node phát hiện bit truyền ra không giống với bit nhận được.
- CRC Error: Xảy ra khi có lỗi trong quá trình kiểm tra mã CRC.
- ACK Error: Xảy ra khi node không nhận được tín hiệu ACK từ các node khác.
- Form Error: Xảy ra khi một trường trong khung không tuân theo định dạng đúng của giao thức CAN.
- Stuff Error: Xảy ra khi có nhiều hơn 5 bit giống nhau liên tiếp trong một khung (CAN sử dụng Bit stuffing để tránh điều này).
Khi bất kỳ lỗi nào được phát hiện, node phát ra Error Frame và các node khác trên mạng CAN sẽ tạm dừng quá trình giao tiếp và xử lý lại khung.

### **4. Overload Frame**
Overload Frame là một loại khung đặc biệt trong giao thức CAN được sử dụng để trì hoãn việc truyền dữ liệu khi một node trong mạng CAN cần thêm thời gian để xử lý. Khung này không chứa dữ liệu, mà chỉ báo hiệu rằng một node đang quá tải và cần thời gian trước khi tiếp tục giao tiếp. Mục tiêu của Overload Frame là ngăn không cho các khung khác được truyền quá nhanh, giúp node bị quá tải có đủ thời gian để xử lý các khung trước đó.

Overload Frame không phải do người dùng phát ra, mà được tự động phát ra bởi phần cứng CAN khi cần thiết. Node CAN sẽ phát ra Overload Frame khi một trong các điều kiện sau xảy ra:
- Node không thể xử lý tiếp dữ liệu do buffer đã đầy hoặc cần thêm thời gian xử lý dữ liệu.
- Node không thể nhận khung mới do có quá trình xử lý nội bộ cần hoàn thành trước.
Cấu trúc của Overload Frame:
- Overload Flag: 6 bit dominant (bit 0) để báo hiệu trạng thái quá tải.
- Overload Delimiter: 8 bit recessive (bit 1), để phân tách khung quá tải với các khung khác và báo hiệu kết thúc Overload Frame.

![](https://automotivevehicletesting.com/wp-content/uploads/2024/04/Overload-frame-structure-in-CAN.png)
Các điều kiện có thể gây ra Overload Frame:
- FIFO (First-In-First-Out) buffer trong node nhận đầy và node cần thêm thời gian để xử lý dữ liệu đã nhận.
- Tạm dừng nội bộ trong node để hoàn tất việc xử lý một sự kiện trước khi nhận thêm khung dữ liệu mới.
- Node cần xử lý một yêu cầu cao cấp khác (như một yêu cầu từ phần mềm ứng dụng).

# **Tốc độ truyền và giới hạn vật lý của CAN**
Giao thức CAN được thiết kế để hoạt động hiệu quả trong các hệ thống nhúng với khả năng truyền thông dữ liệu tin cậy và độ trễ thấp. Một số yếu tố quan trọng ảnh hưởng đến hiệu suất của mạng CAN bao gồm tốc độ truyền (baud rate), chiều dài của bus, và điện trở kết cuối (termination resistor). Các yếu tố này liên quan chặt chẽ với nhau, ảnh hưởng đến khả năng truyền tín hiệu trên bus CAN.

## **1. Tốc độ baud của CAN**
Tốc độ baud là tốc độ truyền dữ liệu trên bus CAN, thường được đo bằng kbps (kilobits per second) hoặc Mbps (megabits per second). Tốc độ baud quyết định tốc độ truyền thông giữa các thiết bị trên mạng và phụ thuộc vào khả năng xử lý của hệ thống cũng như chiều dài của bus.

Mạng CAN hỗ trợ dải tốc độ baud từ 10 kbps đến 1 Mbps.
- 10 kbps: Tốc độ thấp nhất, thường được sử dụng cho các hệ thống có yêu cầu truyền thông chậm, nhưng cần truyền xa.
- 1 Mbps: Tốc độ cao nhất, thường được sử dụng trong các ứng dụng yêu cầu truyền thông nhanh, chẳng hạn như trong hệ thống ô tô hoặc robot.

Ảnh hưởng của tốc độ baud:
- Chiều dài tối đa của bus: Tốc độ truyền càng cao, chiều dài tối đa của bus càng ngắn do ảnh hưởng của thời gian lan truyền tín hiệu trên bus. Điều này có nghĩa là khi cần truyền dữ liệu với tốc độ cao, hệ thống phải chấp nhận giảm chiều dài của bus để đảm bảo tín hiệu truyền chính xác và đồng bộ.
- Độ trễ: Tốc độ baud càng cao, độ trễ của việc truyền thông tin trên mạng càng giảm, giúp cải thiện khả năng đáp ứng của hệ thống.

## **2. Chiều dài tối đa của bus trong CAN**
Chiều dài của bus trong mạng CAN bị giới hạn bởi tốc độ baud và chất lượng của dây dẫn (bus). Sự kết hợp giữa tốc độ truyền và chiều dài của bus quyết định khả năng truyền tín hiệu đúng cách và độ tin cậy của mạng.
- Tốc độ truyền càng cao, chiều dài bus càng ngắn: Điều này do thời gian lan truyền tín hiệu trên dây dẫn cần phải nhỏ hơn một khoảng thời gian nhất định để đảm bảo tất cả các node trên bus có thể nhận được tín hiệu đồng bộ.
- Khi tốc độ baud tăng lên, thời gian bit ngắn lại, nghĩa là tín hiệu phải đến các node nhận nhanh hơn. Do đó, chiều dài tối đa của bus phải giảm để đảm bảo thời gian lan truyền tín hiệu phù hợp với tốc độ baud.

# **Quá trình cấu hình và thiết lập CAN**
## **1. Thiết lập tốc độ baud trong CAN**
Tốc độ baud (baud rate) là tốc độ truyền dữ liệu trên bus CAN, được tính bằng số bit truyền trên giây (bps - bit per second). Việc thiết lập tốc độ baud chính xác là một bước quan trọng vì nó ảnh hưởng trực tiếp đến khả năng truyền dữ liệu và chiều dài của bus.

![](https://mesidas.com/wp-content/uploads/2020/11/can-canbus-02.png)

**Thời gian mẫu (Sample Point)**:
- Thời gian mẫu là thời điểm mà tín hiệu trên bus CAN được đọc để xác định giá trị của một bit (dominant hoặc recessive). Mẫu thường được lấy ở vị trí cuối mỗi bit để đảm bảo tín hiệu đã ổn định.
- Vị trí của điểm mẫu (sample point) được tính toán dựa trên tỷ lệ phần trăm trong một khoảng thời gian bit. Điểm mẫu lý tưởng thường nằm ở khoảng 75% đến 90% thời gian của một bit.
**Bộ chia thời gian (Time Segment)**: là một thành phần quan trọng để đồng bộ hóa và điều chỉnh thời gian truyền thông giữa các node trên bus CAN. Một bit trong mạng CAN được chia thành các phân đoạn thời gian (time segment), bao gồm:
- **Sync Segment**: là đoạn đầu tiên của mỗi bit và có độ dài cố định là 1 time quanta (TQ). Đoạn này giúp đồng bộ hóa tất cả các node trên bus. Nó đảm bảo rằng tất cả các node đều nhận biết sự bắt đầu của một bit tại cùng một thời điểm. Node nhận sẽ phát hiện ra cạnh thay đổi (rising edge hoặc falling edge) của tín hiệu CAN tại đoạn này để điều chỉnh thời gian của chính nó, đảm bảo đồng bộ với các node khác trên bus.
- **Propagation Segment**: Đoạn này bù đắp thời gian cần thiết để tín hiệu lan truyền qua bus CAN từ node gửi đến node nhận. Tín hiệu cần thời gian để di chuyển từ một node đến một node khác, và thời gian này phụ thuộc vào chiều dài của bus và tốc độ truyền. Propagation Segment được cấu hình sao cho nó bao gồm độ trễ lan truyền và thời gian trễ xử lý của cả phần cứng CAN.
- Phase Segment 1 (PS1) và Phase Segment 2 (PS2): Hai phân đoạn này được sử dụng để đồng bộ hóa tín hiệu và bù đắp cho các sai lệch về thời gian hoặc độ trễ nhỏ trong quá trình truyền.
    - PS1 là đoạn thời gian trước điểm lấy mẫu. Đoạn này cho phép node điều chỉnh thời gian đọc tín hiệu để đồng bộ với tín hiệu thực tế trên bus.
    - PS2 là đoạn thời gian sau điểm lấy mẫu. Nó có thể được kéo dài hoặc thu ngắn để bù trừ sự sai lệch nhỏ giữa các node, giữ cho tất cả node đồng bộ với nhau. Đây là đoạn để kết thúc 1 bit.
    - Cả PS1 và PS2 đều có thể được điều chỉnh linh hoạt tùy thuộc vào sự thay đổi thời gian cần thiết để đảm bảo việc lấy mẫu tín hiệu một cách chính xác.
![](https://mesidas.com/wp-content/uploads/2020/11/can-canbus-01.png)

## **2. Bộ lọc CAN**:
Trong CAN, các node có thể nhận rất nhiều thông điệp, nhưng không phải tất cả thông điệp đều liên quan đến tất cả các node. Bộ lọc CAN cho phép các node lựa chọn và chỉ nhận những thông điệp cần thiết, dựa trên ID của thông điệp hoặc các tiêu chí khác.

Vai trò của bộ lọc CAN:
- Lựa chọn thông điệp: Bộ lọc CAN giúp các node lọc ra những thông điệp cần thiết và bỏ qua những thông điệp không liên quan. Điều này giúp giảm tải cho vi điều khiển, vì nó chỉ xử lý những dữ liệu mà nó cần.
- Giảm băng thông: Bằng cách chỉ nhận những thông điệp có ID cụ thể, node có thể giảm khối lượng dữ liệu cần xử lý, giúp mạng hoạt động hiệu quả hơn.

Bộ lọc CAN hoạt động dựa trên hai thành phần chính:
- **Mask (Mặt nạ)**: Quy định những bit nào trong ID của thông điệp cần được kiểm tra.
- **Filter (Bộ lọc)**: Được dùng để so sánh các bit của ID thông điệp với giá trị quy định trong bộ lọc. Nếu các bit này khớp với mask, thông điệp sẽ được chấp nhận và xử lý.
### **Mask**
Mask là một dãy bit mà các bit có giá trị 1 sẽ được kiểm tra, còn các bit có giá trị 0 sẽ bị bỏ qua. Điều này cho phép chỉ định cụ thể những phần của ID thông điệp mà node sẽ quan tâm, trong khi bỏ qua các phần không quan trọng. Mask giúp xác định phạm vi ID mà node quan tâm.
### **Filter**
Filter là giá trị mà các bit trong ID của thông điệp phải khớp với, dựa trên mask. Các bit được phép kiểm tra thông qua mask sẽ được so sánh với filter. Nếu ID thông điệp trùng khớp với giá trị của bộ lọc (sau khi áp dụng mask), thông điệp sẽ được chấp nhận. Nếu không trùng khớp, thông điệp sẽ bị bỏ qua, node sẽ không xử lý nó.
