
# Struct - Union

## Struct

Định nghĩa Struct: là kiểu dữ liệu cho phép người dùng tự định nghĩa. Bằng cách chúng ta sẽ được nhóm nhiều kiểu dữ liệu khác nhau lại.

- Ví dụ khai báo 1:
```c
struct {
    char name;
    int lop;
    int mssv;
}Student;

struct Student ManhHai;
```

- Ví dụ khai báo 2:
```c
typedef struct {
    char name;
    int lop;
    int mssv;
}Student;

Student ManhHai;
```
### Data alignment
Data alignment là quá trình sắp xếp các thành phần của struct sao cho những thành phần địa chỉ bên trong struct nằm phù hợp với kiểu dữ liệu căn chỉnh.  

### Padding
Padding là thêm những byte trống giữa các thành phần để cho những địa chỉ phù hợp với dữ liệu căn chỉnh.

![](https://daynhauhoc.s3.dualstack.ap-southeast-1.amazonaws.com/optimized/1X/420ba75bce5f66d58382cef2027897c2f79f549c_2_690x91.png)

### Tính kích thước của struct
Kích thươc struct sẽ được tính bằng cách dựa vào kích thước lớn nhất trong struct để cấp phát ô nhớ. Mỗi lần cấp phát nếu không đủ cho kiểu dữ liệu tiếp theo thì sẽ được cấp phát tiếp các ô nhớ . Các thành phần trống thì sẽ được lấp đầy bằng thành phần padding.
```c
#include <stdio.h>

struct Example {
    char a;     // 1 byte
    int b;      // 4 bytes
    char c;     // 1 byte
};

int main() {
    printf("Size of struct Example: %zu bytes\n", sizeof(struct Example));
    return 0;
}
```
Mỗi lần sẽ được cấp phát 4 ô nhớ tương đương 4 byte do int là kiểu dữ liệu lớn nhất trong struct.4 ô nhớ đầu tiên sẽ được cấp phjaps để chưa char a và còn 3 byte còn lại sẽ không đủ cho int b nên sẽ được cấp phát tiếp 4 ô nhớ. Và char c cũng vậy. Các thành phần trống sẽ được thêm vào padding.
```c
Size of struct Example: 12 bytes
```
## Union

Union là kiểu dữ liệu người dùng tự định nghĩa tương tự struct. Khi khai báo một union, các thành phần của nó sẽ được lưu trữ tại cùng một địa chỉ bộ nhớ, nghĩa là chúng sẽ ghi đè lên nhau.

Điểm khác giữa Union với Struct thì struct là tổng các kiểu dữ liệu được khai báo bên trong + padding. Còn union thì chỉ là kiểu dữ liệu lớn nhất + padding.

```c
#include <stdio.h>

typedef union {
    int i;        // 4 bytes
    float f;      // 4 bytes
    char c;       // 1 byte
}Data;

int main() {
    printf("Size of union Data: %zu bytes\n", sizeof(Data));
    return 0;
}
```
- Kết quả:
```c
Size of union Data: 4 bytes

```