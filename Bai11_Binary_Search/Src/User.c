#include "User.h"

Node* createNode(User user) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = user;
    newNode->next = NULL;
    return newNode;
}

void addUser(Node** head, User user) {
    Node* newNode = createNode(user);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

User* convertToArray(Node* head, int* size) {
    int count = 0;
    Node* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    User* array = (User*)malloc(count * sizeof(User));
    temp = head;
    for (int i = 0; i < count; i++) {
        array[i] = temp->data;
        temp = temp->next;
    }
    *size = count;
    return array;
}

int nameSort(const User* user1, const User* user2) {
    return strcmp(user1->name, user2->name);
}

int phoneSort(const User* user1, const User* user2) {
    return strcmp(user1->phone_number, user2->phone_number);
}

void bubbleSort(User* array, int size, int(*compare)(const User*, const User*)) {
    if (array == NULL || size <= 1) return; 

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(&array[j], &array[j + 1]) > 0) {
                User temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int nameSearch(const User* user, const void* target) {
    if (user == NULL || target == NULL) {
        return -1; 
    }
    return strcmp(user->name, (const char*)target);
}

int phoneSearch(const User* user, const void* target) {
    if (user == NULL || target == NULL) {
        return -1; 
    }
    return strcmp(user->phone_number, (const char*)target);
}

int binarySearch(User* array, int left, int right, const void* target, int (*Comparator)(const User*, const void*)) {
    if (array == NULL || left > right) {
        return -1; 
    }

    int mid = left + (right - left) / 2;
    int cmp = Comparator(&array[mid], target);

    if (cmp == 0) {
        return mid;  
    } else if (cmp < 0) {
        return binarySearch(array, mid + 1, right, target, Comparator);
    } else {
        return binarySearch(array, left, mid - 1, target, Comparator);
    }
}

void printUser(User user) {
    printf("Name: %s, Age: %d, Address: %s, Phone: %s\n",
           user.name, user.age, user.addr, user.phone_number);
}

void freeUserArray(User* array, int size) {
    if (array == NULL) return;
    for (int i = 0; i < size; i++) {
        free(array[i].name);
        free(array[i].addr);
        free(array[i].phone_number);
    }
    free(array);
}