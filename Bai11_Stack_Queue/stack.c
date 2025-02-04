#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @typedef struct stack
 * Cấu trúc dữ liệu ngăn xếp (stack) với 3 thành phần:
 *  - data: Con trỏ đến mảng chứa các phần tử của stack.
 *  - size: Kích thước tối đa của stack.
 *  - top: Chỉ số phần tử trên cùng trong stack (ban đầu là -1 khi rỗng).
 */
typedef struct {
    int *data;
    int size;
    int top;
} stack;


/**
 * @brief Khởi tạo một stack mới với kích thước tối đa cho trước.
 * @param size Kích thước tối đa của stack.
 * @return Con trỏ đến struct stack nếu thành công, NULL nếu thất bại.
 * @note Hàm này cấp phát bộ nhớ động, cần gọi `free()` để giải phóng sau khi sử dụng.
 */
stack *StackInitialize(int size) {
    // Cấp phát bộ nhớ cho struct stack
    stack *stackPtr = (stack*)malloc(sizeof(stack));
    if (stackPtr == NULL) {  
        printf("Memory allocation failed for stack.\n");
        return NULL;
    }

    // Cấp phát bộ nhớ cho mảng chứa dữ liệu của stack
    stackPtr->data = (int*)malloc(size * sizeof(int));
    if (stackPtr->data == NULL) {  
        printf("Memory allocation failed for stack data.\n");
        free(stackPtr); 
        return NULL;
    }

    stackPtr->size = size;
    stackPtr->top = -1;  // Stack ban đầu rỗng
    return stackPtr;  // Trả về con trỏ tới stack đã khởi tạo
}


/**
 * @brief Kiểm tra xem stack có rỗng không.
 * @param Stack Con trỏ đến stack cần kiểm tra.
 * @return true nếu stack rỗng, false nếu không.
 */
bool isEmpty(stack *Stack) {
    return (Stack->top == -1);
}

/**
 * @brief Kiểm tra xem stack có đầy không.
 * @param Stack Con trỏ đến stack cần kiểm tra.
 * @return true nếu stack đầy, false nếu không.
 */
bool isFull(stack *Stack) {
    return (Stack->top == Stack->size - 1);
}


/**
 * @brief Thêm một phần tử vào đỉnh của stack.
 * @param Stack Con trỏ đến stack cần thêm phần tử.
 * @param value Giá trị cần đẩy vào stack.
 * 
 * @note Nếu stack đầy, hàm sẽ in thông báo lỗi và không thêm phần tử.
 */
void push(stack *Stack, int value) {
    if (!isFull(Stack)) {
        Stack->data[++(Stack->top)] = value; 
        printf("Pushed %d at address: %p\n", value, (void*)&Stack->data[Stack->top]);
    } else {
        printf("Stack overflow !!\n");
    }
}


/**
 * @brief Lấy và xóa phần tử trên cùng của stack.
 * @param Stack Con trỏ đến stack cần thao tác.
 * @return Giá trị của phần tử trên cùng nếu stack không rỗng, 
 *         trả về -1 nếu stack rỗng (underflow).
 * 
 * @note Nếu stack rỗng, hàm sẽ in thông báo lỗi và trả về -1.
 */
int pop(stack *Stack) {
    if (!isEmpty(Stack)) {
        printf("Popping element %d from address: %p\n", Stack->data[Stack->top], (void*)&Stack->data[Stack->top]);
        return Stack->data[Stack->top--];
    } else {
        printf("Stack underflow !!\n");
        return -1;
    }
}


/**
 * @brief Lấy phần tử trên cùng của stack mà không xóa.
 * @param Stack Con trỏ đến stack cần thao tác.
 * @return Giá trị của phần tử trên cùng nếu stack không rỗng, 
 *         trả về -1 nếu stack rỗng.
 * 
 * @note Nếu stack rỗng, hàm sẽ in thông báo lỗi và trả về -1.
 */
int top(stack *Stack) {
    if (!isEmpty(Stack)) {
        return Stack->data[Stack->top];
    } else {
        printf("Stack is empty.\n");
        return -1;
    }
}

int main() {
    stack *Stack = StackInitialize(5);

    push(Stack, 10);
    push(Stack, 20);
    push(Stack, 30);
    push(Stack, 40);
    push(Stack, 50);

    printf("Pop element: %d\n", pop(Stack));
    printf("Pop element: %d\n", pop(Stack));
    printf("Pop element: %d\n", pop(Stack));
    printf("Pop element: %d\n", pop(Stack));
    printf("Pop element: %d\n", pop(Stack));
    
    free(Stack->data);
    free(Stack); 

    return 0;
}
