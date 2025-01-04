
# Lamda
- Là 1 hàm cục bộ không tên khắc với function(nằm ở toàn cục và tái sử dụng) chỉ sử dụng 1 lần duy nhất.
- Được định nghĩa tại chỗ
- Có thể sử dụng trực tiếp hoặc gán cho biến
- cú pháp:
```c
[capture] (parameters) -> <return type>
{
    //function body
}
```
- capture: cho biết các biến ở phạm vi bên ngoài được sử dụng trong Lamda

    - []: Không chụp bất kỳ biến nào.
    ```c
        auto lambda = []() {
        std::cout << "Lambda không sử dụng biến ngoài!" << std::endl;
    };

    lambda();
    ```
    - [x]: Chỉ chụp biến x (theo giá trị, chỉ đọc).
    ```c
    int x = 5;
    auto lambda = [x]() {
        std::cout << "x: " << x << std::endl;
    };
    lambda();
    ```
    - [&]: Chụp tất cả các biến có phạm vi bên ngoài (tham chiếu, có thể thay đổi giá trị).
    ```c
        int a = 5, b = 10;

    auto lambda = [&]() {
        // Chụp a và b theo tham chiếu
        a += 1;
        b += 2;
        std::cout << "a: " << a << ", b: " << b << std::endl;
    };

    lambda();
    std::cout << "Sau lambda: a = " << a << ", b = " << b << std::endl
    ```
    - [=]: Chụp tất cả các biến có phạm vi bên ngoài (theo giá trị, chỉ đọc).
    ```c
        int a = 5, b = 10;

    auto lambda = [=]() {
        std::cout << "a: " << a << ", b: " << b << std::endl;
    };

    lambda();
    ```
    - [&, x]: Chụp tất cả biến theo tham chiếu, trừ x chụp theo giá trị.
    ```c
        int x = 5, y = 10;

    auto lambda = [&, x]() {
        // x được chụp theo giá trị
        // y được chụp theo tham chiếu
        std::cout << "x: " << x << ", y: " << y << std::endl;
        y += 5; // Thay đổi y
        // x++; // Lỗi: không thể thay đổi x
    };

    lambda();
    std::cout << "Sau lambda: y = " << y << std::endl;
    ```
    - [=, &x]: Chụp tất cả biến theo giá trị, trừ x chụp theo tham chiếu.
    ```c
        int x = 5, y = 10;

    auto lambda = [=, &x]() {
        // x được chụp theo tham chiếu
        // y được chụp theo giá trị
        std::cout << "x: " << x << ", y: " << y << std::endl;
        x += 5; // Thay đổi x
        // y++; // Lỗi: không thể thay đổi y
    };

    lambda();
    std::cout << "Sau lambda: x = " << x << std::endl;
    ```
    - parameters: danh sách các tham số truyền vào của lambda (giống function)

- return_type: 

    + kiểu trả về của lambda. 
    
    + Nếu không chỉ định, kiểu trả về sẽ được suy diễn.

- function body: phần định nghĩa logic của lambda

# Sự khác nhau giữa 'lambda' và 'function'?

## function

- toàn cục

- tái sử dụng nhiều lần (ít nhất 2 lần)

- có địa chỉ trả về để PC trỏ tới thực thi

## lambda

- cục bộ

- chỉ sử dụng 1 lần duy nhất

- không có địa chỉ trả về
