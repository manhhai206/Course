#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node
typedef struct node {
    int item;                // Dữ liệu của node
    struct node* pleft;      // Node con bên trái
    struct node* pright;     // Node con bên phải
} Node;

// Hàm tạo node mới
Node* CreateNode(int x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->item = x;
    p->pleft = NULL;
    p->pright = NULL;
    return p;
}

// Hàm thêm node vào cây
Node* AddNode(Node* t, int x) {
    if (t == NULL) { // Nếu cây rỗng
        return CreateNode(x); // Tạo node mới và trả về
    }
    if (x < t->item) { // Nếu x nhỏ hơn giá trị hiện tại, thêm vào trái
        t->pleft = AddNode(t->pleft, x);
    } else if (x > t->item) { // Nếu x lớn hơn giá trị hiện tại, thêm vào phải
        t->pright = AddNode(t->pright, x);
    }
    return t; // Trả về gốc cây
}

// Hàm duyệt cây theo thứ tự giữa (In-Order Traversal)
void InOrder(Node* t) {
    if (t != NULL) {
        InOrder(t->pleft);            // Duyệt cây con trái
        printf("%d ", t->item);       // In giá trị node hiện tại
        InOrder(t->pright);           // Duyệt cây con phải
    }
}

Node* Search(Node* t, int x)
{
    if (t == NULL || t->item == x) {
        return t; // Trả về NULL nếu không tìm thấy hoặc node chứa giá trị cần tìm
    }

    if (x < t->item) {
        return Search(t->pleft, x); // Tìm trong cây con trái
    }

    return Search(t->pright, x); // Tìm trong cây con phải
}


int main() {
    Node* t = NULL; 

    t = AddNode(t, 50);
    t = AddNode(t, 30);
    t = AddNode(t, 70);
    t = AddNode(t, 20);
    t = AddNode(t, 40);
    t = AddNode(t, 60);
    t = AddNode(t, 80);

     int x = 40;
    Node* result = Search(t, x);

    if (result != NULL) {
        printf("Tìm thấy phần tử %d trong cây.\n", result->item);
    } else {
        printf("Không tìm thấy phần tử %d trong cây.\n", x);
    }
}
