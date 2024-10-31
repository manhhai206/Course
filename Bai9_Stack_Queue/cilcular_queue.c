#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct {
    int *data;
    int size;
    int front;
    int rear;
} Queue;

Queue *Initialize(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(size * sizeof(int));
    queue->size = size;
    queue->front = queue->rear = -1; 
    return queue;  
}

bool isFull(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;  
}

bool isEmpty(Queue queue) {
    return queue.rear == -1; 
}

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

int front(Queue queue) {
    if (!isEmpty(queue)) {
        return queue.data[queue.front]; 
    } else {
        printf("Queue is empty\n");
        return -1; 
    }
}

int main() {
    Queue *queue = Initialize(3); 

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("Front element: %d\n", front(*queue));

    printf("Dequeue element: %d\n", dequeue(queue));

    printf("Dequeue element: %d\n", dequeue(queue));

    printf("Front element: %d\n", front(*queue));

    enqueue(queue, 40);
    printf("Dequeue element: %d\n", dequeue(queue));
    printf("Front element: %d\n", front(*queue));

    return 0;
}
