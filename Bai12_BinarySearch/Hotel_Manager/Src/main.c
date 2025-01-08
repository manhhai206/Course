#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ReadData.h"
#include "User.h"

#define DataBase_Path "..\\HOTEL_MANAGER\\DataBase.csv"

int main() 
{
    Node* root = NULL;

    // Đọc dữ liệu từ file CSV và thêm vào cây nhị phân theo tên
    readCSV(DataBase_Path, &root, compareByName);

    // In ra thông tin người dùng trong cây nhị phân
    inorder(root);

    // Menu cho người dùng chọn tìm kiếm
    int choice;
    printf("\nSelect search option:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // Đọc ký tự newline sau khi nhập số

    if (choice == 1) {
        // Tìm kiếm theo tên
        char name[50];
        printf("\nEnter name to search: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';  // Loại bỏ ký tự newline

        Node* foundByName = searchByName(root, name);
        if (foundByName != NULL) {
            printf("Found: %s, %d, %s, %s\n", foundByName->item.name, foundByName->item.age, foundByName->item.addr, foundByName->item.phone_number);
        } else {
            printf("User not found by name.\n");
        }
    } else if (choice == 2) {
        // Tìm kiếm theo số điện thoại
        char phone[15];
        printf("\nEnter phone number to search: ");
        fgets(phone, 15, stdin);
        phone[strcspn(phone, "\n")] = '\0';  // Loại bỏ ký tự newline

        Node* foundByPhone = searchByPhone(root, phone);
        if (foundByPhone != NULL) {
            printf("Found: %s, %d, %s, %s\n", foundByPhone->item.name, foundByPhone->item.age, foundByPhone->item.addr, foundByPhone->item.phone_number);
        } else {
            printf("User not found by phone number.\n");
        }
    } else {
        printf("Invalid choice! Please enter 1 or 2.\n");
    }

    freeTree(root);

    return 0;
}


