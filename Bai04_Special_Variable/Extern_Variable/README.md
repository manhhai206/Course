# Biến Extern
- Biến được sử dụng để khai báo một biến hoặc một hàm được định nghĩa ở một tệp khác.
- Nó chỉ khai báo chứ không cấp phát bộ nhớ cho biến.
- Biến được tham chiếu phải được khai báo toàn cục và có thể nằm trong một file khác.

Ví dụ file main:
```c
#include <stdio.h>

void display1();
void display2();

extern int a;
extern int b;

int main() {
    display1();
    display2();

    return 0;
}
```

File test1:
```c
#include <stdio.h>

int a = 10;

void display1() {
    printf("Display 1: a = %d\n", a);
}
```

File test2:
```c
#include <stdio.h>

int b = 20;

void display2() {
    printf("Display 2: a=b = %d\n", b);
}
```
- Trong khi đó mình sẽ sử dụng biến **extern** để gọi các biến và các hàm được khai báo từ file khác qua: 
    ```c
    extern int a;
    extern int b;
    ```
    - Sử dụng biến extern để gọi hàm display1 biến a ở file test1.c và display2 và biến b ở test2.c mà không cần include cả 2 file vào.
    ```c 
    gcc main.c test1.c test2.c -o main
    ``` 
    Sử dụng lệnh biên dịch để liên kết 3 file .o lại với nhau