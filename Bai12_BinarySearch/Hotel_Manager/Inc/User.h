#ifndef _USER_H
#define _USER_H

typedef struct User {
    char* name;
    int age;
    char* addr;
    char* phone_number;
} User;

typedef struct Node {
    User item;
    struct Node* pleft;
    struct Node* pright;
} Node;

// Tạo node mới
Node* CreateNode(User user);

// Thêm node vào cây nhị phân theo tên hoặc số điện thoại
Node* AddNode(Node* t, User user, int (*cmp)(User, User));

// So sánh theo tên
int compareByName(User user1, User user2);

// So sánh theo số điện thoại
int compareByPhone(User user1, User user2);

// Duyệt cây theo thứ tự in-order
void inorder(Node* root);

// Tìm kiếm theo tên
Node* searchByName(Node* root, const char* name);

// Tìm kiếm theo số điện thoại
Node* searchByPhone(Node* root, const char* phone_number);

// Hàm giải phóng bộ nhớ
void freeTree(Node* root);
#endif
