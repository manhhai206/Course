#include <stdio.h>
#include <assert.h>

int main() {
    int x = 10;

    assert(x != 10);

    // Chương trình sẽ tiếp tục thực thi nếu điều kiện là đúng.
    printf("x = %d", x);
    
    return 0;
}