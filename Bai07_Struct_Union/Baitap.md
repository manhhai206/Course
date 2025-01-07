# Struct - Union

Định nghĩa các cấu trúc bên trong DataFrame
```c
#define ID_SIZE 2
#define DATA_SIZE 4
#define CHECKSUM_SIZE 2
#define FRAME_SIZE (ID_SIZE + DATA_SIZE + CHECKSUM_SIZE)
```

Định nghĩa kiểu dữ liệu DataFrame:
```c
typedef union {
    struct {
        uint8_t id[ID_SIZE];        
        uint8_t data[DATA_SIZE];  
        uint8_t check_sum[CHECKSUM_SIZE];
    } data;

    uint8_t frame[FRAME_SIZE];     
} Data_Frame;
```
- Trong union thì tất cả các thành viên cùng chia sẻ một vùng nhớ duy nhất có kích thước bằng kích thước của thành viên lớn nhất.
- Thì tất cả các biến đều dùng chung 1 kiểu dữ liệu uint8_t và không cần truy cập đồng thời thì dùng union giúp tiết kiệm bộ nhớ
- Nếu dùng struct thay vì union thì kích thước của Data_Frame sẽ là tổng kích thước của các thành viên data và frame.

```c
Data_Frame transmitter_data;  
Data_Frame receiver_data;     

memcpy(transmitter_data.data.id, "01", ID_SIZE);
memcpy(transmitter_data.data.data, "1234", DATA_SIZE);
memcpy(transmitter_data.data.check_sum, "70", CHECKSUM_SIZE);
memcpy(receiver_data.frame, transmitter_data.frame, FRAME_SIZE);
```
- Sử dụng memcpy để copy chuỗi vào mảng 
