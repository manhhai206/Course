
# Stack - Queue

## Stack

Stack là ngăn xếp hoạt động theo cơ chế **LIFO (Last In, First Out)**, nghĩa là phần tử nào đưa vào sau cùng sẽ được lấy ra trước, và phần tử đưa vào đầu tiên sẽ nằm ở đáy và được lấy ra sau cùng.

![](https://images.viblo.asia/f90f90ab-e709-431b-9e15-726ec6550dc7.png)

Các thao tác cơ bản trên stack bao gồm:
- “ push” (đẩy) để thêm một phần tử vào đỉnh của stack.
- “ pop” để xóa một phần tử ở đỉnh stack.
- “ top” để lấy giá trị của phần tử ở đỉnh stack.

```c
typedef struct {
    int *data;
    int size;
    int top;
} stack;
```
Sử dụng struct để tạo ra một cấu trúc stack với 3 thành phần:

- data: Con trỏ tới mảng chứa các phần tử của stack.
- size: Kích thước tối đa của stack.
- top: Chỉ số của phần tử trên cùng trong stack. Khi stack rỗng, top sẽ là -1.

```c
void StackInitialize(stack *Stack, int size) {
    Stack->data = (int*)malloc(size * sizeof(int));
    Stack->size = size;
    Stack->top = -1;
}
```
Sử dụng malloc để cấp phát bộ nhớ động cho stack. Hàm này giúp linh hoạt trong việc xác định kích thước của stack tại thời điểm chạy chương trình.

```c
bool isEmpty(stack Stack) {
    return (Stack.top == -1);
}

bool isFull(stack Stack) {
    return (Stack.top == Stack.size - 1);
}
```
- isEmpty: Kiểm tra nếu stack rỗng (top == -1).
- isFull: Kiểm tra nếu stack đầy (top đạt giá trị size - 1).

```c
void push(stack *Stack, int value) {
    if (!isFull(*Stack)) { 
        Stack->data[++Stack->top] = value;
    } else {
        printf("Stack overflow !!\n");
    }
}
```


push: Thêm một phần tử vào đỉnh của stack. Nếu stack chưa đầy, tăng top lên và gán value vào vị trí top mới. Nếu stack đầy, thông báo tràn stack.

```c

int pop(stack *Stack) {
    if (!isEmpty(*Stack)) {
        return Stack->data[Stack->top--];
    } else {
        printf("Stack underflow !!\n");
        return -1;
    }
}
```
pop: Lấy và xóa phần tử trên đỉnh của stack. Nếu stack không rỗng, trả về giá trị tại top và giảm top đi 1. Nếu stack rỗng, thông báo stack underflow và trả về -1.

```c
int top(stack *Stack) {
    if (!isEmpty(*Stack)) {
        return Stack->d[Stack->top];
    } else {
        printf("Stack is empty.\n");
        return -1;
    }
}
```
pop: Lấy và xóa phần tử trên đỉnh của stack. Nếu stack không rỗng, trả về giá trị tại top và giảm top đi 1. Nếu stack rỗng, thông báo stack underflow và trả về -1.


## Queue

Queue là cấu trúc hoạt động theo cơ chế FIFO, phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên hàng đợi bao gồm:
- “enqueue” (thêm phần tử vào cuối hàng đợi)
- “dequeue” (lấy phần tử từ đầu hàng đợi). 
- “front” để lấy giá trị của phần tử đứng đầu hàng đợi.
### Linear Queue

```c
typedef struct Queue {
    int* items;
    int size;
    int front;
    int rear;
} Queue;
```

Sử dụng struct để tạo ra một cấu trúc Queue với 3 thành phần:

- items: Con trỏ tới mảng chứa các phần tử của Queue.
- size: Kích thước tối đa của queue.
- front: Chỉ số của phần tử đứng đầu của queue.
- rear: Chỉ số của phần tử đứng cuôi của queue.

```c
Queue *Initialize(int size)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(sizeof(int) * size);
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
    return queue;
}
```
- Cấp phát bộ nhớ cho cấu trúc hàng đợi Queue.
- Cấp phát bộ nhớ cho mảng items để chứa các phần tử trong hàng đợi, với kích thước là size.
- Gán kích thước (size) cho hàng đợi.
- Khởi tạo front và rear ở vị trí -1 để biểu thị rằng hàng đợi đang trống.
- Trả về con trỏ đến hàng đợi đã được khởi tạo
```c
bool isEmpty(Queue queue) {
    return queue.front == -1 || queue.front > queue.rear;
}
```
Kiểm tra xem hàng đợi có trống hay không. Kiểm tra xem front có bằng -1 hoặc lớn hơn rear không.
```c
bool isFull(Queue queue) {
    return queue.rear == queue.size - 1;
}
```
Kiểm tra xem hàng đợi có đầy không.

```c
void enqueue(Queue *queue, int data)
{
    if (isFull(*queue)) {
        printf("Queue full\n");
        return;
    } else {
        if (isEmpty(*queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear++;
        }
        queue->items[queue->rear] = data;
        printf("Enqueue %d\n", data);
    }
}
```
Thêm một phần tử vào cuối hàng đợi nếu hàng đợi chưa đầy.

Kiểm tra nếu hàng đợi đầy (gọi hàm isFull).
Nếu hàng đợi không đầy:
- Nếu hàng đợi đang trống, đặt cả front và rear về 0 để chuẩn bị cho việc thêm phần tử đầu tiên.
- Nếu hàng đợi có sẵn phần tử, tăng rear lên 1 để trỏ tới vị trí trống tiếp theo.

```c
int dequeue(Queue *queue)
{
    if (isEmpty(*queue)) {
        printf("Queue empty\n");
        return -1;
    } else {
        int value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front++;
        }
        return value;
    }
}
```
Lấy và xóa một phần tử từ đầu hàng đợi nếu hàng đợi không trống.

Kiểm tra nếu hàng đợi trống (gọi hàm isEmpty)
Nếu hàng đợi không trống:
- Lấy giá trị từ queue->front và lưu lại trong biến value.
- Nếu front bằng rear, đặt lại front và rear về -1 để biểu thị hàng đợi trống sau khi xóa phần tử.
- Nếu không, tăng front lên 1 để trỏ tới phần tử tiếp theo.


**Nhược điểm** của linear queue là khi con trỏ rear đạt đến giới hạn size - 1 thì hàng đợi sẽ được coi là đầy, ngay cả khi có các vị trí trống ở phía trước front do các thao tác dequeue. Điều này dẫn đến lãng phí bộ nhớ vì không thể sử dụng lại các ô trống này cho các phần tử mới.

### Circular Queue

Để giải quyết vấn đề này, bạn có thể sử dụng circular queue:
- Khi con trỏ rear đạt đến cuối mảng, nếu có vị trí trống ở phía trước, nó sẽ quay vòng lại và bắt đầu từ đầu mảng.
- Điều này tận dụng hiệu quả toàn bộ mảng và tránh lãng phí bộ nhớ.

```c
bool isFull(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;  
}
```
Bây giờ kiểm tra full khác với linear queue rồi. Kiểm tra bằng cách cộng 1 vô phần tử rear rồi % với size để xem có bằng vị trí front không.

```c
void enqueue(Queue *queue, int value) {
    if (isFull(*queue)) {
        printf("Queue full !!! \n");
    } else {
        if (isEmpty(*queue)) {
            queue->front = queue->rear = 0; 
        } else {
            queue->rear = (queue->rear + 1) % queue->size; 
        }
        queue->data[queue->rear] = value; 
        printf("Enqueue %d\n", value); 
    }
}
```
Hàm enqueue sẽ kiểm tra isFull và isEmpty nếu không thỏa thì sẽ gán phần tử rear bằng(rear+1)%size để xác định phần tử rear nằm ở đâu. Sau đó gán data vào rear.

```c
int dequeue(Queue *queue) {
    if (isEmpty(*queue)) {
        printf("Queue underflow\n");
        return -1;
    } else {
        int dequeued_value = queue->data[queue->front]; 
        if (queue->front == queue->rear) { 
            queue->front = queue->rear = -1; 
        } else {
            queue->front = (queue->front + 1) % queue->size; 
        }
        return dequeued_value; 
    }
}
```
Hàm dequeue sẽ kiểm tra isFull và isEmpty nếu không thỏa thì sẽ gán phần tử front bằng(front+1)%size để xác định phần tử front nằm ở đâu. Sau đó gán data vào rear.
