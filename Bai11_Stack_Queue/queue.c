#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/**
 * @typedef struct Queue
 * @brief Cấu trúc hàng đợi (Queue) với các thành phần:
 *  - items: Con trỏ đến mảng chứa các phần tử của hàng đợi.
 *  - size: Kích thước tối đa của hàng đợi.
 *  - front: Chỉ số của phần tử đầu tiên trong hàng đợi.
 *  - rear: Chỉ số của phần tử cuối cùng trong hàng đợi.
 */
typedef struct Queue {
    int* items;
    int size;
    int front;
    int rear;
} Queue;

/**
 * @brief Khởi tạo một hàng đợi với kích thước xác định.
 * 
 * @param size Kích thước tối đa của hàng đợi.
 * @return Con trỏ đến hàng đợi đã được cấp phát bộ nhớ.
 */
Queue *Initialize(int size)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue)); // Cấp phát bộ nhớ cho cấu trúc hàng đợi
    queue->items = (int*)malloc(sizeof(int) * size); // Cấp phát bộ nhớ cho mảng dữ liệu
    queue->size = size;
    queue->front = -1; // Hàng đợi rỗng ban đầu
    queue->rear = -1;
    return queue;
}

/**
 * @brief Kiểm tra xem hàng đợi có rỗng không.
 * 
 * @param queue Hàng đợi cần kiểm tra.
 * @return true nếu hàng đợi rỗng, ngược lại là false.
 */
bool isEmpty(Queue queue) {
    return queue.front == -1 || queue.front > queue.rear;
}

/**
 * @brief Kiểm tra xem hàng đợi có đầy không.
 * 
 * @param queue Hàng đợi cần kiểm tra.
 * @return true nếu hàng đợi đầy, ngược lại là false.
 */
bool isFull(Queue queue) {
    return queue.rear == queue.size - 1;
}

/**
 * @brief Thêm một phần tử vào cuối hàng đợi.
 * 
 * @param queue Con trỏ đến hàng đợi cần thêm phần tử.
 * @param data Giá trị cần thêm vào hàng đợi.
 * 
 * @note Nếu hàng đợi đầy, hàm sẽ in thông báo lỗi và không thêm phần tử.
 */
void enqueue(Queue *queue, int data)
{
    if (isFull(*queue)) {
        printf("Queue full\n");
        return;
    } else {
        if (isEmpty(*queue)) {
            queue->front = queue->rear = 0; // Nếu rỗng, đặt lại front và rear về 0
        } else {
            queue->rear++; // Tăng rear để thêm phần tử mới
        }
        queue->items[queue->rear] = data;
        printf("Enqueue %d\n", data);
    }
}

/**
 * @brief Loại bỏ và trả về phần tử đầu tiên của hàng đợi.
 * 
 * @param queue Con trỏ đến hàng đợi cần lấy phần tử.
 * @return Giá trị của phần tử đầu tiên nếu hàng đợi không rỗng, 
 *         trả về -1 nếu hàng đợi rỗng.
 * 
 * @note Nếu hàng đợi rỗng, hàm sẽ in thông báo lỗi và trả về -1.
 */
int dequeue(Queue *queue)
{
    if (isEmpty(*queue)) {
        printf("Queue empty\n");
        return -1;
    } else {
        int value = queue->items[queue->front]; // Lấy giá trị đầu hàng đợi
        if (queue->front == queue->rear) { // Nếu chỉ còn một phần tử, đặt lại hàng đợi rỗng
            queue->front = queue->rear = -1;
        } else {
            queue->front++; // Di chuyển front về phần tử tiếp theo
        }
        return value;
    }
}


int main()
{
    Queue *queue = Initialize(5);
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));
    enqueue(queue, 40);
    enqueue(queue, 50);
    enqueue(queue, 60);
    enqueue(queue, 70);
    printf("Dequeued: %d\n", dequeue(queue));


    free(queue->items);
    free(queue);
    return 0;
}
