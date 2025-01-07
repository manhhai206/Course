#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Queue {
    int* items;
    int size;
    int front;
    int rear;
} Queue;

Queue *Initialize(int size)
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(sizeof(int) * size);
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

bool isEmpty(Queue queue) {
    return queue.front == -1 || queue.front > queue.rear;
}

bool isFull(Queue queue) {
    return queue.rear == queue.size - 1;
}

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
