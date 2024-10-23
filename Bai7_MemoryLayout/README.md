
# Memory layout

Memory layout là một khái niệm quan liên quan đến cách các biến và đối tượng được tổ chức và lưu trữ trong bộ nhớ. Mỗi phân vùng có mục đích và quy tắc sử dụng riêng.

Tổng cộng có 5 vùng nhớ:
+ Text Segment
+ Data Segment(DS và BSS)
+ Heap Segment
+ Stack Segment

![](https://images.viblo.asia/eccce77d-6b51-4792-b544-a058f013b43d.png)

## Text Segment

Vùng nhớ Text Segment là vùng nhớ được lưu trữ các câu lệnh thực thi bên trong chương trình.

Bất kì những gì nằm bên trong vùng text thì có quyền chỉ được đọc và thực thi thôi chứ không có quyền ghi.Tránh thay đổi mã máy khi thực thi thì sẽ làm chương trình bị thay đổi không mong muốn.

Các biến hằng số (const) và chuỗi hằng thì được lưu trên vùng Text nếu như sử dụng compiler(Clang). Còn nếu sử dụng compiler(GCC) thì sẽ được lưu ở vùng nhớ data.

Ví dụ:
```c
#include "stdio.h"

const int a = 10;   //Window => rdata; MacOS => text
char *ptr = "xin chao" //Window => rdata; MacOS => text

int main(){}
```

## Data Segment

### DS(Initialized data)
Vùng nhớ DS sẽ lưu trữ các biến static và các biến global được khai báo với giá trị khác 0 và biến sẽ tồn tại cho đến khi chương trình kết thúc.

Vùng nhớ này có quyền được đọc và ghi, có thể đọc và thay đổi giá trị của biến.

Ví dụ:
```c
#include "stdio.h"

int a = 5;
const int b = 10;
void *ptr = &a;
static double c = 3.14;
void test()
{
    static int d =7;
}
int main(){
    return 0;
}
```
Cùng chuyển qua code assembly để nhìn rõ hơn:
```
	.file	"Ex1.c"
	.text
	.globl	a
	.data
	.align 4
a:
	.long	5
	.globl	b
	.section .rdata,"dr"
	.align 4
b:
	.long	10
	.globl	ptr
	.data
	.align 8
ptr:
	.quad	a
	.align 8
c:
	.long	1374389535
	.long	1074339512
	.text
	.globl	test
	.def	test;	.scl	2;	.type	32;	.endef
	.seh_proc	test
```
Có thể thấy các biến global int a, const int(compiler in Window),con trỏ global và các biến static (local,global) đều được khởi tạo sẽ lưu vào phân vùng Data Segment.

### BSS(UnInitialized data)
Vùng nhớ DS sẽ lưu trữ các biến static và các biến global được khai báo với giá trị bằng 0 hoặc không được khởi tạo và biến sẽ tồn tại cho đến khi chương trình kết thúc.

Quyền truy câp: Vùng nhớ này có quyền được đọc và ghi, có thể đọc và thay đổi giá trị của biến.

Ví dụ:
```c
#include "stdio.h"

int a;
const int b = 0;
void *ptr = &a;
static double c = 0;
void test()
{
    static int d;
}
int main(){
    return 0;
}
```

## Stack 

Stack chứa các biến cục bộ và tham số truyền vào hàm. Mỗi khi một hàm được gọi, một stack frame mới được tạo để lưu trữ các biến cục bộ và tham số truyền vào của hàm đó. Khi hàm kết thúc, stack frame này sẽ bị loại bỏ khỏi stack, và vùng nhớ dành cho các biến cục bộ sẽ được giải phóng.

Quyền truy cập: Stack có quyền đọc và ghi, nên có thể đọc và thay đổi giá trị của các biến trong stack.

Stack hoạt động theo cơ chế LIFO push vào đầu tiên thì pop ra cuối cùng.

![](https://gochocit.com/wp-content/uploads/2021/11/minh-hoa-stack.png)

```c
#include "stdio.h"

int *ptr = NULL;

void test(){
    const int a = 5;
    ptr = &a;
    *ptr=20;
    printf("%d",a);
}

int main(){
    test();
}
```
```
Trước khi gọi hàm test
+-----------------+
| main's frame    |
| - ptr (NULL)    |  <- Top of Stack
+-----------------+

Khi gọi hàm test: biến cục bộ a được lưu trữ với giá trị 5. Con trỏ toàn cục ptr trỏ đến địa chỉ của biến a.
+-----------------+
| test's frame    |
| - Return Addr   |
| - Local var     |
|   a = 5         |  <- Top of Stack
+-----------------+
| main's frame    |
| - ptr (NULL)    |
+-----------------+

Sau khi gọi hàm test kết thúc,pop stack frame của test ra ngoài.
+-----------------+
| main's frame    |
| - ptr (invalid) |  <- Top of Stack
+-----------------+
```

## Heap
 
Heap sử dụng để cấp phát động bộ nhớ trong quá trình thực thi của chương trình thông qua 1 số hàm như malloc, calloc, realloc thì sẽ lưu vào phân vùng Heap và khác với Stack thì Heap phải tự thu hồi vùng nhớ bằng cách sử dụng free để tránh vùng nhớ này sẽ phình lên (grows upward).

Ví dụ:
```c
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

int main()
{
	uint16_t *ptr = NULL;
	int size = 3;
	//malloc cấp phát ban đầu cho 3 phần tử.
	ptr =(uint16_t*)malloc(size*sizeof(uint16_t));

	for(int i=0;i<size;i++)
	{
		ptr[i] = i+1;												
    }

	for(int i=0;i<size;i++)
	{
		printf("dia chi:  %p, gia tri %d\n",&ptr[i],ptr[i]);		
    }

	//realloc mở rộng bộ nhớ để chứa 6 phần tử.
    ptr = (uint16_t*)realloc(ptr,6*sizeof(uint16_t));
    size+=3;
    for(int i=0;i<size;i++)
	{
		ptr[i] = i+1;												
    }

	for(int i=0;i<size;i++)
	{
		printf("dia chi:  %p, gia tri %d\n",&ptr[i],ptr[i]);		
    }
	//giai phong bo nho
	free();
    return 0;
}

```
- malloc dùng để cấp phát một vùng nhớ động có kích thước nhất định.

	```void* malloc(size_t size);```

- realloc dùng để thay đổi kích thước của vùng nhớ đã cấp phát trước đó

	``` void* realloc(void* ptr, size_t new_size);```

### So sánh giữa malloc và calloc

| **So sánh**              | **`malloc()`**                              | **`calloc()`**                              |
|---------------------------|---------------------------------------------|---------------------------------------------|
| **Chức năng**             | Cấp phát bộ nhớ động                        | Cấp phát bộ nhớ động và khởi tạo vùng nhớ về 0 |
| **Cú pháp**               | `void* malloc(size_t size);`                | `void* calloc(size_t num, size_t size);`    |
| **Khởi tạo giá trị**       | Không khởi tạo hoặc vùng nhớ chứa giá trị rác    | Khởi tạo tất cả các phần tử thành 0         |
| **Hiệu suất**             | Nhanh hơn do không khởi tạo                 | Chậm hơn vì phải khởi tạo tất cả phần tử về 0 |

Việc sử dụng phương thức calloc sẽ an toàn hơn malloc  vì vùng nhớ cấp phát động sẽ được gán giá trị bằng 0 thay vì giá trị rác như calloc. Tuy nhiên việc thêm 1 bước gán giá trị các ô nhớ bằng 0 này cũng sẽ khiến nó bị chậm hơn so với malloc do phải thực hiện thêm thao tác.
