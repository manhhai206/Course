#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *json = "12345.678abc";
    char *end;
    
    // Chuyển đổi chuỗi thành số
    double num = strtod(json, &end);

    // In ra số đã chuyển đổi
    printf("Parsed number: %f\n", num);
    
    // Kiểm tra giá trị của end
    if (*end == '\0') {
        printf("End points to the null terminator.\n");
    } else {
        printf("Remaining characters after the number: '%s'\n", end);
    }

    return 0;
}
