
# Inline Function
- Inline Function đóng vai quan trọng. Tăng hiệu suất bằng cách giảm thiểu gánh nặng của các lần gọi hàm.

- Inline function cho phép thay thế toàn bộ code trong hàm vào trực tiếp trong vị trí gọi hàm tại thời điểm biên dịch.

- Nhưng các inline function cũng sẽ tăng kích thước mã.

![](https://media.geeksforgeeks.org/wp-content/uploads/20221229112934/Inline-Function-in-Cpp.png)

- Ví dụ :
    ```c
    #include <iostream>
    using namespace std;

    inline int square(int x) {
        return x * x;
    }

    int main() {
        int a = 5;
        cout << "Square of " << a << " is " << square(a) << endl;
        return 0;
    }
    ```

    Thì khi ở thời điểm compiler thì nó thay thế code trong hàm vào vị trí gọi hàm

    ```c
    int main() {
        int a = 5;
        cout << "Square of " << a << " is " << (a * a) << endl; // Thay thế trực tiếp nội dung hàm
        return 0;
    }

    ```

## Inline function hoạt động
Trong quá trình biên dịch, source code trong hàm inline sẽ được thay thế tại vị trí gọi:
- Mã nguồn bên trong inline function được biên dịch bởi trình biên dịch.
- Khi gọi hàm trình biên dịch sẽ thay thế hàm gọi với mã đối tượng bên trong inline function
- Mã sẽ thêm vào trực tiếp tại vị trí gọi trong assembly hoặc mã máy.

![](https://embeddedwala.com/uploads/images/202307/img_temp_64aab07540c198-03196557-24610214.png)

## Uư và Nhược điểm
- Ưu điểm
    - Nó không yêu cầu chức năng gọi overhead.
    - Tiết kiệm chi phí gọi hàm, thực hiện chương trình nhanh.

- Nhược điểm
    - Nếu hàm inline được gọi ở nhiều nơi trong chương trình, mã hàm sẽ được sao chép vào mỗi vị trí gọi thì tốn địa chỉ lưu trên Ram làm tăng kích thước.
