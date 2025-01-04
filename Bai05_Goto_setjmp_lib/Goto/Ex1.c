#include <stdio.h>

void delay(double second)
{
    double start = 0;
    while (start < second)
    {
        start++;
    }
    
}

// Khai báo các trạng thái đèn giao thông
typedef enum 
{
    RED,
    YELLOW,
    GREEN
} TrafficLightState;


int main() {
    

    // Ban đầu, đèn giao thông ở trạng thái đỏ
    TrafficLightState state = RED;

    // Vòng lặp vô hạn để mô phỏng đèn giao thông
    while (1) {
        switch (state) {
            case RED:
                printf("RED Light\n");
                delay(2);  // Giữ trạng thái đèn đỏ trong x giây
                
                // Chuyển đến trạng thái đèn vàng
                state = GREEN;
                goto skip_sleep;  // Nhảy qua sleep() khi chuyển trạng thái
            case YELLOW:
                printf("YELLOW Light\n");
                delay(2);  // Giữ trạng thái đèn vàng trong y giây
                
                // Chuyển đến trạng thái đèn xanh
                state = RED;
                goto skip_sleep;  // Nhảy qua sleep() khi chuyển trạng thái
            case GREEN:
                printf("GREEN Light\n");
                delay(2);  // Giữ trạng thái đèn xanh trong z giây
                
                // Chuyển đến trạng thái đèn đỏ
                state = YELLOW;
                goto skip_sleep;  // Nhảy qua sleep() khi chuyển trạng thái
        }

        // Nhãn để nhảy qua sleep() khi chuyển trạng thái
        skip_sleep:;
    }

    return 0;
}


