#ifndef _USER_H
#define _USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
    char* addr;
    char* phone_number;
} User;

typedef struct Node {
    User data;
    struct Node* next;
} Node;

Node* createNode(User user);
void addNode(Node** head, User user);
int nameSort(const User* user1, const User* user2);
int phoneSort(const User* user1, const User* user2);
void bubbleSort(User* array, int size, int(*compare)(const User*, const User*));
User* convertToArray(Node* head, int* size);
int nameSearch(const User* user, const void* target);
int phoneSearch(const User* user, const void* target);
int binarySearch(User* array, int left, int right, const void* target, int (*Comparator)(const User*, const void*));
void printUser(User user);
void freeUserArray(User* array, int size);

#endif 