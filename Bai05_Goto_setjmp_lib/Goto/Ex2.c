#include <stdio.h>

int main() {
    int i = 0;

    // Đặt nhãn
    start:
        if (i >= 5) {
            goto end;  // Chuyển control đến nhãn "end"
        }

        printf("%d ", i);
        i++;

        goto start;  // Chuyển control đến nhãn "start"

    // Nhãn "end"
    end:
        printf("\n");

    return 0;
}


