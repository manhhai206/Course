
# Bitmask trong quản lý OptionCar
Định nghĩa các mã với màu sắc, công suất và động cơ được định nghĩa bằng các macro:
- Màu sắc (Red, Blue, Black, White).
- Công suất động cơ (100HP, 150HP, 200HP).
- Dung tích động cơ (1.5L, 2.0L).
```c
#define COLOR_RED 0	
#define COLOR_BLUE 1
#define COLOR_BLACK 2
#define COLOR_WHITE 3

#define POWER_100HP 0
#define POWER_150HP 1
#define POWER_200HP 2

#define ENGINE_1_5L 0
#define ENGINE_2_0L 1
```
Các bit được thiết lập thông qua phép shift bit sang trái:
- SUNROOF_MASK: Được gán giá trị 1 << 0, tương ứng với bit đầu tiên (Bit 0).
- PREMIUM_AUDIO_MASK: Được gán giá trị 1 << 1, tương ứng với bit thứ hai (Bit 1).
- SPORTS_PACKAGE_MASK: Được gán giá trị 1 << 2, tương ứng với bit thứ ba (Bit 2).
```c
#define SUNROOF_MASK 1 << 0        // Bit 0
#define PREMIUM_AUDIO_MASK 1 << 1  // Bit 1
#define SPORTS_PACKAGE_MASK 1 << 2 // Bit 2
```
Sử dụng Bit fields chỉ định số lượng bit cụ thể cho CarOptions.
```c
typedef struct {
    uint8_t additionalOptions : 3; 
    CarColor color : 2;
    CarPower power : 2;
    CarEngine engine : 1;  
} CarOptions;
```
Hàm configureCar giúp thiết lập các thông số ban đầu của xe.
```c
void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options) {
    car->color = color;
    car->power = power;
    car->engine = engine;
    car->additionalOptions = options;
}
```
Hàm setOption bật các tùy chọn bổ sung bằng cách sử dụng phép OR (|):
```c
void setOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions |= optionMask;
}
```
- Sử dụng toán tử OR (|=) để bật các bit tương ứng trong additionalOptions.
- Ví dụ: Bật cả Sunroof và Premium Audio:
    ```c
    setOption(&myCar, SUNROOF_MASK | PREMIUM_AUDIO_MASK);
    ```

Hàm unsetOption tắt các tùy chọn bằng cách sử dụng phép AND với phủ định của optionMask:
```c
void unsetOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions &= ~optionMask;
}
```
- Sử dụng toán tử AND (&=) với phủ định của optionMask (~optionMask) để tắt các bit tương ứng.

- Ví dụ: Tắt Premium Audio:
    ```c
    unsetOption(&myCar, PREMIUM_AUDIO_MASK);
    ```

Hàm displayCarOptions in thông tin cấu hình của xe:
```c
void displayCarOptions(const CarOptions car) {
    const char *colors[] = {"Red", "Blue", "Black", "White"};
    const char *powers[] = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}
```
Kiểm tra trạng thái của các tùy chọn bổ sung bằng phép AND (&)
