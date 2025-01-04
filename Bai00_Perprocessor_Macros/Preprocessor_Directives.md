
# Chỉ thị tiền xử lý trong C
Chỉ thị tiền xử lý trong C là những lệnh được xử lý bởi preprocessor trước khi trình biên dịch bắt đầu biên dịch mã nguồn. Những chỉ thị này bắt đầu với ký tự # và không cần dấu chấm phẩy (;) khi kết thúc, vì chúng không phải là lệnh trong C mà là các chỉ thị đặc biệt cho tiền xử lý.

Chỉ thị tiền xử lý có thể được chia thành ba nhóm chính:
## 1. Chỉ thị bao hàm tệp - File Inclusion Directives
Chỉ thị #include cho phép chúng ta đưa các tệp bên ngoài vào chương trình C. Đây là cách để sử dụng các thư viện hoặc các module mã khác.
- **Cú pháp 1**:
    ```c
    #include <file_name>
    ```
    Khi sử dụng cú pháp này, trình tiền xử lý sẽ tìm tệp file_name trong các thư mục hệ thống của môi trường phát triển (IDE) như Visual Studio. Các tệp header chuẩn như stdio.h, math.h, hoặc conio.h thường được bao gồm theo cách này.

    **Ví dụ**
    ```c
    #include <stdio.h> 
    ```

- **Cú pháp 2**:
    ```c
    #include “file_name”
    ```
    Với cú pháp này, trình tiền xử lý sẽ tìm tệp file_name trong thư mục hiện tại trước, và nếu không tìm thấy, sẽ tìm trong các thư mục hệ thống đã định sẵn. Đây thường được dùng để bao gồm các tệp header do người dùng tự tạo hoặc các tệp có trong cùng thư mục với tệp mã nguồn.

    **Ví dụ**
    ```c
    #include "display.h" 
    ```

## 2. Chỉ thị định nghĩa cho tên - Define Macro
Chỉ thị #define được sử dụng để định nghĩa các macros (biến thay thế hoặc các hàm thay thế). Các macro có thể là hằng số hoặc các biểu thức, và trình tiền xử lý sẽ thay thế chúng trong mã nguồn trước khi biên dịch.
- **Cú pháp**:
    ```c
    #define identifier replacement
    ```
    - identifier là tên muốn định nghĩa.
    - replacement là giá trị hoặc biểu thức mà muốn thay thế cho identifier

    **Ví dụ**
    ```c
    #define PI 3.14159  // Định nghĩa hằng số PI
    ```
    - Khi biên dịch, mọi nơi trong mã mà gặp PI sẽ được thay thế bằng 3.14159.
- Đối với các macro có đối số, cần dùng dấu ngoặc đơn để đảm bảo thứ tự thực thi đúng:
    ```c
    #define SQUARE(x) ((x) * (x))  // Đảm bảo thứ tự thực thi đúng
    ```

    **Ví dụ**

    ```c
    int result = SQUARE(5 + 3);  // Kết quả sẽ là 8 * 8 = 64, không phải 5 + 3 = 8 rồi tính bình phương
    ```
- Chỉ thị #undef: Chỉ thị #undef được sử dụng để hủy bỏ một định nghĩa macro đã được định nghĩa trước đó. 
    
    **Cú pháp**:
    ```c
    #undef identifier
    ```

    Ví dụ:
    ```c
    #define MAX_SIZE 100  // Định nghĩa MAX_SIZE là 100
    #undef MAX_SIZE      // Hủy bỏ định nghĩa MAX_SIZE
    #define MAX_SIZE 200  // Định nghĩa lại MAX_SIZE là 200
    ```

## 3. Chỉ thị biên dịch có điều kiện - Conditional Compilation Directives
Chỉ thị biên dịch có điều kiện cho phép biên dịch mã nguồn tùy thuộc vào các điều kiện xác định tại thời điểm biên dịch. Điều này rất hữu ích trong việc tạo mã nguồn có thể chạy trên các hệ điều hành khác nhau hoặc trong các môi trường khác nhau.

- #if, #else, #elif, #endif: Cho phép kiểm tra điều kiện tại thời điểm biên dịch.

    **Cú pháp**:

    ```c
    #if CONDITION
    // Mã sẽ được biên dịch nếu điều kiện đúng
    #elif ANOTHER_CONDITION
    // Mã sẽ được biên dịch nếu điều kiện trên sai và điều kiện này đúng
    #else
    // Mã sẽ được biên dịch nếu tất cả các điều kiện trên đều sai
    #endif
    ```

    **Ví dụ**:
    ```c
    #define DEBUG
    #if defined(DEBUG)
        printf("Debugging is enabled\n");
    #else
        printf("Debugging is not enabled\n");
    #endif
    ```
- #ifdef và #ifndef: Các chỉ thị này kiểm tra xem một macro có được định nghĩa hay không.
    
    **Cú pháp**":
    ```c
    #ifdef MACRO_NAME
    // Mã sẽ được biên dịch nếu MACRO_NAME được định nghĩa
    #endif

    #ifndef MACRO_NAME
        // Mã sẽ được biên dịch nếu MACRO_NAME không được định nghĩa
    #endif
    ```

## 4. Chỉ thị toán tử 
- Toán tử # trong macro được sử dụng để chuyển đổi một đối số thành chuỗi (string). Khi bạn sử dụng toán tử # trước một đối số trong macro, đối số đó sẽ được chuyển thành một chuỗi ký tự

    **Cú pháp**:

    ```c
    #define MACRO_NAME(arg) #arg
    ``` 
    **Ví dụ**:
    ```c
    #include <stdio.h>

    #define TO_STRING(x) #x

    int main() {
        printf("%s\n", TO_STRING(Hello World));  // In ra "Hello World"
        return 0;
    }
    ```
    **Kết quả**
    ```c
    "Hello World"
    ```
    - Khi gọi TO_STRING(Hello World), đối số Hello World sẽ được chuyển thành chuỗi "Hello World".

- Toán tử ## trong macro được sử dụng để ghép các chuỗi hay văn bản lại với nhau. Điều này có thể hữu ích khi bạn muốn kết hợp hai đối số hoặc một đối số và một chuỗi cố định thành một chuỗi duy nhất.

    **Cú pháp**:
    ```c
    #define MACRO_NAME(arg1, arg2) arg1 ## arg2
    ```
    **Ví dụ**:
    ```c
    #include <stdio.h>

    #define CONCAT(x, y) x ## y

    int main() {
        int xy = 10;
        printf("%d\n", CONCAT(x, y));  // In ra giá trị của biến xy, tức là 10
        return 0;
    }
    ```
