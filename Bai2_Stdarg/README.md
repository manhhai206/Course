
# Stdarg - Assert

## Stdarg
Thư viện Stdarg: được dùng để viết một hàm mà số lượng đối số có thể biến đổi (variable arguments). 

Ví dụ:
```c
#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__,'\n')

int sum(int count,...){
    va_list args;
    va_start(args,count);

    int sum = count;
    int value;

    while ((value = va_arg(args,int)) != '\n')
    {
       sum += value;
    }

    va_end(args);
    return sum;

}

int main()
{
    printf("tong = %d\n",tong(3,1,2,3,0,1));
    return 0;
}
```

Kết quả:

```c 
tong = 10
 ```

Trong thư viện stdarg có :

- va_list: là một kiểu dữ liệu để đại diện cho danh sách các đối số biến đổi.

- va_start: Bắt đầu một danh sách đối số biến đổi. Nó cần được gọi trước khi truy cập các đối số biến đổi đầu tiên.

- va_arg: Truy cập một đối số trong danh sách. Hàm này nhận một đối số của kiểu được xác định bởi tham số thứ hai

- va_end: Kết thúc việc sử dụng danh sách đối số biến đổi. Nó cần được gọi trước khi kết thúc hàm.

## Assert

Assert: là một thư viện trong C cung cấp hàm assert để giúp chẩn đoán và gỡ lỗi chương trình. Hàm assert kiểm tra một biểu thức và nếu biểu thức đó là false, chương trình sẽ in ra thông báo lỗi và dừng thực thi.

-   Projects quá lớn và nhiều file thì assert giúp kiểm tra nhanh tính đúng đắn của các điều kiện trong chương trình mà không cần phải in thông tin.
-   Đối với các MCU không có khả năng hiển thị, assert có thể tạo điều kiện để phát hiện lỗi và dừng chương trình khi có vấn đề, tránh việc chương trình chạy tiếp với lỗi ngầm.

```c
#include <stdio.h>
#include <assert.h>

int main() {
    int x = 10;

    assert(x != 10);

    // Chương trình sẽ tiếp tục thực thi nếu điều kiện là đúng.
    printf("x = %d", x);
    
    return 0;
}
```

Ví dụ trên thì khi x = 10 và vô hàm assert thì không đáp ứng đúng điều kiện thì sẽ bị dừng chương trình luôn.
