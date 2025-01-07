#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ReadData.h"
#include "User.h"

#define DATA_PATH "D:\\Course\\C\\Bai11_Binary_Search\\Src\\users.csv"

int main() {
    Node* head = NULL;

    const char* filename = DATA_PATH;
    readCSV(filename, &head);

    int size;
    User* array = convertToArray(head, &size);

    int choice;
    printf("\nChoose search:\n");
    printf("1. Search by name\n");
    printf("2. Search by phone number\n");
    printf("3. Add User\n");
    scanf("%d", &choice);
    getchar(); 
    assert((choice == 1 || choice == 2 || choice == 3)  && "Choice must be 1 or 2 or 3!");

    char target[10];
    int index = -1;
    if (choice == 1) {
        printf("Enter search value: ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0'; 
        bubbleSort(array, size, nameSort);
        index = binarySearch(array, 0, size - 1, target, nameSearch);
    } else if (choice == 2) {
        printf("Enter search value: ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0';         
        bubbleSort(array, size, phoneSort);
        index = binarySearch(array, 0, size - 1, target, phoneSearch);
    } else if (choice == 3) {
        User user;
        addUser(filename,user);
    }

    if (index != -1) {
        printf("User found:\n");
        printUser(array[index]);
    } else if(choice == 3){
    } else {
        printf("User not found.\n");
    }

    freeUserArray(array, size);
    return 0;
}
