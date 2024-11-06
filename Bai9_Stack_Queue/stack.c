#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int top;
} stack;

stack *StackInitialize(int size) {
    stack *Stack = (stack*)malloc(sizeof(stack));
    Stack->data = (int*)malloc(size * sizeof(int));
    Stack->size = size;
    Stack->top = -1; // Initially the stack is empty
    return Stack;
}

bool isEmpty(stack *Stack) {
    return (Stack->top == -1);
}

bool isFull(stack *Stack) {
    return (Stack->top == Stack->size - 1);
}

void push(stack *Stack, int value) {
    if (!isFull(Stack)) {
        Stack->data[++(Stack->top)] = value; 
        printf("Pushed %d at address: %p\n", value, (void*)&Stack->data[Stack->top]);
    } else {
        printf("Stack overflow !!\n");
    }
}

int pop(stack *Stack) {
    if (!isEmpty(Stack)) {
        printf("Popping element %d from address: %p\n", Stack->data[Stack->top], (void*)&Stack->data[Stack->top]);
        return Stack->data[Stack->top--];
    } else {
        printf("Stack underflow !!\n");
        return -1;
    }
}

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
    free(Stack); // Don't forget to free the stack structure itself

    return 0;
}
