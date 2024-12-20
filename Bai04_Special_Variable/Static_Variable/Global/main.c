// main.c
#include <stdio.h>
#include "motor.h"

int main() {
    MotorController motor;  // Khởi tạo một đối tượng điều khiển động cơ
    init_motor(&motor);     // Khởi tạo các hàm điều khiển động cơ

    motor.start(5);         // Khởi động động cơ ở PIN 5
    motor.changeSpeed(5, 100);  // Thay đổi tốc độ động cơ ở PIN 5
    motor.stop(5);          // Dừng động cơ ở PIN 5

    return 0;
}
