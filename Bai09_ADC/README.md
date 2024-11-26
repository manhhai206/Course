
# ADC

ADC là bộ chuyển đổi chuyển tử tín hiệu tương tự sang tín hiệu số.

Trong bộ chuyển đổi ADC, bao gồm là độ phân giải (resolution) và thời gian lấy mẫu (sampling time):

![](https://tapit.vn/wp-content/uploads/2018/06/1.gif)
- Độ phân giải (resolution):  dùng để chỉ số bit cần thiết để chứa hết các mức giá trị số (digital) sau quá trình chuyển đổi ở ngõ ra. Độ phân giải càng cao => Càng nhiều mức => Kết quả càng chính xác.

- Thời gian lấy mẫu (sampling time) là tần suất mà tín hiệu tương tự được lấy mẫu. Tần số lấy mẫu càng cao => Lấy được nhiều mẫu hơn => Kết quả càng chính xác

Các tham số  cấu hình cho ADC:

- ADC_Mode:  Cấu hình chế độ hoạt động cho ADC là đơn (Independent) hay đa, ngoài ra còn có các chế độ ADC chuyển đổi tuần tự các kênh (regularly) hay chuyển đổi khi có kích hoạt (injected).

- ADC_NbrOfChannel: Số kênh ADC để cấu hình

- ADC_ContinuousConvMode: Cấu hình bộ ADC có chuyển đổi liên tục hay không, Enable để cấu hình ADC  chuyển đổi lien tục, nếu cấu hình Disable, ta phải gọi lại lệnh đọc ADC để bắt đầu quá trình chuyển đổi. 

- ADC_ExternalTrigConv: Enable để sử dụng tín hiệu trigger. 

- ADC_ScanConvMode: Cấu hình chế độ quét ADC lần lượt từng kênh. Enable nếu sử dụng chế độ quét này.

- ADC_DataAlign: Cấu hình căn lề cho data. Vì bộ ADC xuất ra giá trị 12bit, được lưu vào biến 16 hoặc 32 bit nên phải căn lề các bit về trái hoặc phải.

## Sử dụng  bộ lọc trong một chuỗi để lọc tín hiệu hiệu quả hơn
### Bộ Lọc Trung Bình
Bộ lọc trung bình là một phương pháp lọc tín hiệu đơn giản. Nó làm giảm nhiễu bằng cách tính giá trị trung bình của một số lượng mẫu tín hiệu trước đó.

Cách Thực Hiện:
- Thu thập một số lượng mẫu dữ liệu cố định và tính giá trị trung bình của các mẫu này.
- Bộ lọc này phù hợp để loại bỏ nhiễu có biên độ nhỏ và biến đổi nhanh.

### Bộ Lọc Kalman
Bộ lọc Kalman là một phương pháp nâng cao, sử dụng mô hình toán học để ước lượng trạng thái của một hệ thống động theo thời gian. Nó rất hiệu quả trong việc lọc tín hiệu khi có sự không chắc chắn hoặc nhiễu ngẫu nhiên.
