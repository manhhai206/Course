#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "User.h"
#include "readdata.h" 

int main() {
    Node* head = NULL;
    const char* filename = "users.csv";
    
    readCSV(filename, &head);
    int size;
    User* array = convertToArray(head, &size);
    
    int choice;
    printf("\nChoose search:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input for search criterion.\n");
        freeUserArray(array, size);
        return 1;  
    }
    getchar();

    assert((choice == 1 || choice == 2) && "Choice must be 1 or 2!");

    char target[50];
    printf("Enter search value: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = '\0';  

    int index = -1;
    if (choice == 1) {
        bubbleSort(array, size,nameSort);
        index = binarySearch(array, 0, size - 1, target, nameSearch);
    } else if (choice == 2) {
        bubbleSort(array, size,phoneSort);
        index = binarySearch(array, 0, size - 1, target, phoneSearch);
    } else {
        printf("Invalid choice.\n");
        freeUserArray(array, size);
        return 0;  
    }

    if (index != -1) {
        printf("User found:\n");
        printUser(array[index]);
    } else {
        printf("User not found.\n");
    }

    freeUserArray(array, size);
    
    return 0;
}

