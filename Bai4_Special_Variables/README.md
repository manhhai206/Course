
# **Special Variables**

## Biến Extern

- Biến được sử dụng để khai báo một biến hoặc một hàm được định nghĩa ở một tệp khác. Nó chỉ khai báo chứ không cấp phát bộ nhớ cho biến.
- Biến được tham chiếu phải được khai báo toàn cục và có thể nằm trong một file khác.

Ví dụ file 1:
```c
#include <stdio.h>

int globalVar = 10;

void display() {
    printf("Value of globalVar: %d\n", globalVar);
}

```

Ví dụ file 2:
```c
#include <stdio.h>

extern int globalVar;

void modify() {
    globalVar = 20;
}

int main() {
    printf("Initial value of globalVar: %d\n", globalVar);
    modify(); 
    printf("Modified value of globalVar: %d\n", globalVar);
    return 0;
}

```
Kết quả: 
```c
Initial value of globalVar: 10
Modified value of globalVar: 20

```
Điều này cho thấy cách mà biến extern cho phép chia sẻ và thay đổi biến toàn cục giữa các tệp khác nhau trong một chương trình C.

## Biến static

### Biến static cục bộ
Biến sẽ chỉ được khỏi tạo 1 lần duy nhất và tồn tại suốt thời gian chạy chương trình. Giá trị của nó không bị mất đi và được duy trì giữa các lần gọi hàm. Mỗi lần hàm được gọi, giá trị của biến chính bằng giá trị tại lần gần nhất hàm được gọi.

```c
#include <stdio.h>

void counter() {
    static int count = 0;
    count++;
    printf("Giá trị của count: %d\n", count);
}

int main() {
    counter(); // Lần gọi thứ nhất
    counter(); // Lần gọi thứ hai
    counter(); // Lần gọi thứ ba
    return 0;
}
```
Kết quả
```c
Giá trị của count: 1
Giá trị của count: 2
Giá trị của count: 3
```
### Biến static toàn cục
Chỉ cho phép biến đó sử dụng trong 1 file khai báo chứ không được sử dụng ở các file khác(dù có dùng Extern cũng không được). Tránh để các file khác sử dụng.

- File 1:

```c
#include <stdio.h>

static int localGlobalVar = 10; // Khai báo biến toàn cục static

void increment() {
    localGlobalVar++;
    printf("Giá trị của localGlobalVar trong hàm increment: %d\n", localGlobalVar);
}

void decrement() {
    localGlobalVar--;
    printf("Giá trị của localGlobalVar trong hàm decrement: %d\n", localGlobalVar);
}
```

- File 2:
```c
#include <stdio.h>

extern int localGlobalVar; // Thử truy cập biến từ tệp khác

void test() {
    printf("Giá trị của localGlobalVar trong hàm test: %d\n", localGlobalVar);
}
```
- Kết quả:
```c
error: ‘localGlobalVar’ undeclared (first use in this function)
```
Điều này chứng minh rằng biến static toàn cục chỉ có thể được truy cập trong tệp mà nó được khai báo, và không thể truy cập hoặc sử dụng từ các tệp khác, dù có sử dụng extern.

## Biến register

Từ khóa register là làm tăng hiệu năng của chương trình.
Trong kiến trúc vi xử lý thì ALU đóng vài trò xử lý toán học.Dữ liệu đi vào làm việc với ALU phải chứ trong một vùng đặc biệt, gọi là các thanh ghi (register), và ALU chỉ làm việc với đống thanh ghi đó.

Trong khi đó các biến khai báo trong chương trình thì đặt ở bộ nhớ ngoài(RAM… ). Do đó với khai báo biến thông thường, để thực hiên  một phép tính thì cần có 3 bước.


1.Nạp giá trị từ vùng Nhớ chứa biến vào register.

2.Yêu cầu ALU xử lý register vừa được nạp vào giá trị.

3.Đưa kết quả vừa xử lý của ALU ra ngoài vùng nhớ chưa biến.

![](https://khuenguyencreator.com/wp-content/uploads/2021/09/register-.jpg)

Khi thêm từ khóa register để khai báo biến, thì tức là ta đã yêu cầu trình biên dịch ưu tiên đặc biệt dành luôn vùng register để chứa biến đó. Và hiển nhiên khi thực hiện tính toán trên biến đó thì giảm được bước 1 và 3, giảm bớt thủ tục vậy nên hiệu năng tăng lên.

## Biến volatile

Khi một biến được đánh dấu là "volatile", trình biên dịch không được phép tối ưu hóa các thao tác liên quan đến biến đó bằng cách loại bỏ chúng vì sự thay đổi của biến có thể xảy ra bất cứ lúc nào từ các nguồn không dự đoán được. Điều này có nghĩa là các thao tác đọc và ghi vào biến volatile sẽ được thực hiện mà không bị tối ưu hóa bởi trình biên dịch.

Các trường hợp sử dụng biến volatile trong nhúng:
- Memory-mapped peripheral registers (thanh ghi ngoại vi có ánh xạ đến ô nhớ)
- Biến toàn cục được truy xuất từ các tiến trình con xử lý ngắt (interrupt service routine)
- Biến toàn cục được truy xuất từ nhiều tác vụ trong một ứng dụng đa luồng.

Ví dụ: 
```c
#include <stdio.h>
#include <stdbool.h>

volatile bool flag = false;

void interruptHandler() {
    flag = true; 

void checkFlag() {
    printf("Đang chờ flag thay đổi...\n");
    while (!flag) {

    }
    printf("Flag đã thay đổi!\n");
}

int main() {
    interruptHandler();
    checkFlag();
    
    return 0;
}
```

Kết quả:
```c
Đang chờ flag thay đổi...
Flag đã thay đổi!
```
Biến flag được khai báo là volatile để đảm bảo rằng mỗi lần đọc giá trị từ nó trong vòng lặp while luôn lấy giá trị mới nhất từ bộ nhớ.

interruptHandler() giả lập một ngắt thay đổi giá trị của flag, và chương trình sẽ thoát khỏi vòng lặp khi flag được thay đổi.
