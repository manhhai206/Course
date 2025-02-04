#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"


/**
 * @typedef struct Queue
 * @brief Cấu trúc hàng đợi vòng (Circular Queue) với các thành phần:
 *  - data: Con trỏ đến mảng chứa các phần tử của hàng đợi.
 *  - size: Kích thước tối đa của hàng đợi.
 *  - front: Chỉ số của phần tử đầu tiên trong hàng đợi.
 *  - rear: Chỉ số của phần tử cuối cùng trong hàng đợi.
 * 
 * @note Sử dụng cơ chế vòng để tối ưu việc sử dụng bộ nhớ khi các phần tử được loại bỏ và thêm vào.
 */
typedef struct {
    int *data;
    int size;
    int front;
    int rear;
} Queue;


/**
 * @brief Khởi tạo một hàng đợi vòng với kích thước xác định.
 * 
 * @param size Kích thước tối đa của hàng đợi.
 * @return Con trỏ đến hàng đợi đã được cấp phát bộ nhớ.
 */
Queue *Initialize(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));  // Cấp phát bộ nhớ cho hàng đợi
    queue->data = (int*)malloc(size * sizeof(int));  // Cấp phát bộ nhớ cho mảng chứa dữ liệu
    queue->size = size;
    queue->front = queue->rear = -1; // Hàng đợi rỗng ban đầu
    return queue;
}


/**
 * @brief Kiểm tra xem hàng đợi có đầy không.
 * 
 * @param queue Hàng đợi cần kiểm tra.
 * @return true nếu hàng đợi đầy, ngược lại là false.
 */
bool isFull(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front; // Kiểm tra nếu rear + 1 quay lại front
}


/**
 * @brief Kiểm tra xem hàng đợi có rỗng không.
 * 
 * @param queue Hàng đợi cần kiểm tra.
 * @return true nếu hàng đợi rỗng, ngược lại là false.
 */
bool isEmpty(Queue queue) {
    return queue.rear == -1; // Nếu rear == -1 thì hàng đợi rỗng
}


/**
 * @brief Thêm một phần tử vào cuối hàng đợi vòng.
 * 
 * @param queue Con trỏ đến hàng đợi cần thêm phần tử.
 * @param value Giá trị cần thêm vào hàng đợi.
 * 
 * @note Nếu hàng đợi đầy, hàm sẽ in thông báo lỗi.
 *       Nếu hàng đợi rỗng, đặt front = rear = 0.
 *       Nếu không, tăng rear theo kiểu vòng.
 */
void enqueue(Queue *queue, int value) {
    if (isFull(*queue)) {
        printf("Queue full !!! \n");
    } else {
        if (isEmpty(*queue)) {
            queue->front = queue->rear = 0; // Đặt lại front và rear về 0 khi thêm phần tử đầu tiên
        } else {
            queue->rear = (queue->rear + 1) % queue->size; // Di chuyển rear theo kiểu vòng
        }
        queue->data[queue->rear] = value; // Thêm phần tử vào vị trí của rear
        printf("Enqueue %d\n", value);
    }
}


/**
 * @brief Loại bỏ và trả về phần tử đầu tiên của hàng đợi vòng.
 * 
 * @param queue Con trỏ đến hàng đợi cần lấy phần tử.
 * @return Giá trị của phần tử đầu tiên nếu hàng đợi không rỗng, trả về -1 nếu hàng đợi rỗng.
 * 
 * @note Nếu chỉ còn một phần tử, đặt lại front và rear về -1.
 *       Nếu không, di chuyển front theo kiểu vòng.
 */
int dequeue(Queue *queue) {
    if (isEmpty(*queue)) {
        printf("Queue underflow\n");
        return -1;
    } else {
        int dequeued_value = queue->data[queue->front]; // Lấy giá trị từ phần tử đầu tiên
        if (queue->front == queue->rear) { // Nếu chỉ còn một phần tử, đặt lại front và rear
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->size; // Di chuyển front theo kiểu vòng
        }
        return dequeued_value; // Trả về giá trị đã loại bỏ
    }
}


/**
 * @brief Lấy giá trị phần tử đầu tiên của hàng đợi mà không loại bỏ.
 * 
 * @param queue Hàng đợi cần lấy phần tử.
 * @return Giá trị phần tử đầu tiên nếu hàng đợi không rỗng, trả về -1 nếu hàng đợi rỗng.
 * 
 * @note Hàm chỉ trả về giá trị mà không thay đổi hàng đợi.
 */
int front(Queue queue) {
    if (!isEmpty(queue)) {
        return queue.data[queue.front]; // Trả về giá trị phần tử đầu tiên
    } else {
        printf("Queue is empty\n");
        return -1; // Nếu hàng đợi rỗng, trả về -1
    }
}


int main() {
    Queue *queue = Initialize(3); 

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("Dequeue element: %d\n", dequeue(queue));

    printf("Dequeue element: %d\n", dequeue(queue));

    printf("Front element: %d\n", front(*queue));

    enqueue(queue, 40);
    enqueue(queue, 50);
    printf("Front element: %d\n", front(*queue));

    return 0;
}
