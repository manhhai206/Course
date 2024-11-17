#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// Task 1 function
void* task1(void* data)
{
    static int i = 0;
    while (1)
    {
        printf("count task1: %d\n", i++);
        sleep(1);
    }
    return NULL;
}

// Task 2 function
void* task2(void* data)
{
    static int i = 0;
    while (1)
    {
        printf("count task2: %d\n", i++);
        sleep(3);
    }
    return NULL;
}

// Display function
void* display(void* a)
{
    while (1)
    {
        printf("%s\n", (char*)a);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char const* argv[])
{
    char* ptr = "Hello world";

    pthread_t t1; // Thread 1
    pthread_t t2; // Thread 2
    pthread_t t3; // Thread 3

    // Create threads
    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);
    pthread_create(&t3, NULL, display, (void*)ptr);

    // Wait for threads (although they run infinitely)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
