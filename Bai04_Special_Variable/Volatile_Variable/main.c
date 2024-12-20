#include <stdio.h>
#include <stdint.h>  // Thêm thư viện để định nghĩa uint8_t

uint8_t *addr = (uint8_t*)0x20000000;  // Địa chỉ bộ nhớ
volatile uint8_t var = 0;  // Khai báo biến var để lưu giá trị đọc được

int main(){
    while(1){
        var = *addr;  // Đọc giá trị từ địa chỉ bộ nhớ
        printf("s");
        if(var != 0){
            printf("oke");
        }
    }
    return 0;  // Kết thúc chương trình
}
