
# **Bài 3 Pointer**

## *Khái niệm về con trỏ*

Con trỏ là 1 biến chứa địa chỉ bộ nhớ của biến khác. Sử dụng con trỏ giúp chúng ta thao tác trên bộ nhớ linh hoạt hơn.

![](https://daynhauhoc.s3.dualstack.ap-southeast-1.amazonaws.com/original/3X/1/7/171d3190d623c6323f6343374a0b570f824e7301.png)

Cách khai báo:
```c
int *ptr;   // con trỏ đến kiểu int
float *ptr; // con trỏ đến kiểu float
char *ptr;  // con trỏ đến kiểu char
```
Lấy địa chỉ 1 biến bằng cách:
```c
int *ptr = &a ; //con trỏ ptr sẽ lưu địa chỉ của a
```
Lấy giá trị của con trỏ :
```c
int b = *ptr ;
```
Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch:
```c
#include <stdio.h>

int main() {
    int *ptr;
    printf("Size of pointer: %d bytes\n", sizeof(ptr));
    return 0;
}
```
## *Các loại pointer*

### Void pointer

Con trỏ kiểu void dùng để trỏ đến bất kì địa chỉ nào mà không cần biết trước kiểu dữ liệu của địa chỉ đó. Và muốn lấy giá trị của con trỏ thì chúng ta chỉ cần ép kiểu thành kiểu dữ liệu mà con trỏ đó trỏ đến.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
   
    int value = 5;
    double test = 15.7;
    char letter = 'A';
   
    void *ptr = &value;
    printf("value is: %d\n", *(int*)(ptr));

    ptr = &test;
    printf("value is: %f\n", *(double*)(ptr));

    ptr = &letter;
    printf("value is: %c\n", *(char*)(ptr));
   
    return 0;
}
```

### Constant pointer
``` <data type> *const ptrname; ```

Con trỏ hằng là con trỏ mà sau khi được khởi tạo và trỏ đến một địa chỉ cụ thể, nó không thể thay đổi để trỏ tới một địa chỉ khác.

```c
int value1 = 10;
int value2 = 20;
int *const ptr = &value1; // ptr là con trỏ hằng trỏ đến value1

// ptr = &value2; // Lỗi: Không thể thay đổi địa chỉ mà ptr trỏ đến

*ptr = 15; // Có thể thay đổi giá trị của biến mà con trỏ trỏ đến
```
### Pointer to constant

```const <data type> *ptrname; ```

Con trỏ trỏ đến hằng là con trỏ mà không thể thay đổi giá trị của biến mà nó trỏ đến, nhưng có thể thay đổi địa chỉ mà nó trỏ đến.
```c
const int value1 = 10;
const int value2 = 20;
const int *ptr = &value1; // ptr là con trỏ trỏ đến hằng

// *ptr = 15; // Lỗi: Không thể thay đổi giá trị của biến mà ptr trỏ đến
```

### Function pointer

Con trỏ hàm dùng để tham chiếu 1 hàm thay vì tham chiếu các giá trị dữ liệu khác.

```return_type (* pointer_name) (arg_1_datatype, arg_2_datatype, ...);```

Ví dụ: 
```c
#include <stdio.h>
#include <stdbool.h>

bool KiemTraLon(int a, int b) {
    return a > b;
}

bool KiemTraBe(int a, int b) {
    return a < b; 
}

void sort(int arr[], int size, bool (*compare)(int, int)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (compare(arr[i], arr[j])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Mảng gốc: ");
    printArray(arr, size);

    sort(arr, size, KiemTraLon);
    printf("Mảng sau khi sắp xếp tăng dần: ");
    printArray(arr, size);

    sort(arr, size, KiemTraBe);
    printf("Mảng sau khi sắp xếp giảm dần: ");
    printArray(arr, size);

    return 0;
}

```
```c
Mảng gốc: 5 2 9 1 5 6 
Mảng sau khi sắp xếp tăng dần: 1 2 5 5 6 9 
Mảng sau khi sắp xếp giảm dần: 9 6 5 5 2 1

```
### Pointer to pointer

![](https://media.geeksforgeeks.org/wp-content/uploads/20230412184414/double-pointers-in-c.webp)

Con trỏ đến con trỏ là một kiểu dữ liệu cho phép lưu trữ địa chỉ của một con trỏ. Cho phép bạn thay đổi giá trị của con trỏ bằng  địa chỉ của một con trỏ khác.
 ```c
#include <stdio.h>

void modifyPointer(int **ptr) {
    static int new_value = 20;
    *ptr = &new_value;
}

int main() {
    int value = 10;
    int *ptr = &value;
    int **ptr_to_ptr = &ptr;

    printf("Giá trị ban đầu: %d\n", *ptr);

    modifyPointer(ptr_to_ptr);

    printf("Giá trị sau khi thay đổi: %d\n", *ptr);

    return 0;
}

 ```
- ```int **ptr_to_ptr = &ptr```: Con trỏ ptr_to_ptr lưu trữ địa chỉ của con trỏ ptr.
- Hàm ```modifyPointer``` thay đổi giá trị mà ptr trỏ tới bằng cách sử dụng con trỏ ptr_to_ptr.
- Kết quả là giá trị mà ptr trỏ đến đã thay đổi từ 10 thành 20.


### NULL pointer

Null Pointer là một con trỏ không trỏ đến bất kỳ đối tượng hoặc vùng nhớ cụ thể nào.'

```c
#include <stdio.h>

int main() {
    int *ptr = NULL;  // Gán giá trị NULL cho con trỏ

    if (ptr == NULL) {
        printf("Pointer is NULL\n");
    } else {
        printf("Pointer is not NULL\n");
    }

    return 0;
}
```
