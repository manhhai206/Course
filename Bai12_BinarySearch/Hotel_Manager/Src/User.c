#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************
 * @brief Hàm tạo node mới với thông tin khách hàng
 * @details Hàm này dựa vào con trỏ hàm trỏ vào hàm so sánh (theo tên 
 *          hoặc theo số điện thoại) để thực hiện gọi hàm và sắp xếp
 *          theo đúng yêu cầu.
 *          - Nếu so sánh theo tên, sử dụng hàm compareByName.
 *          - Nếu so sánh theo số điện thoại, sử dụng hàm compareByPhone.
 * @param[in] user Truyền vào thông tin người dùng để khởi tạo
 * @return Trả về địa chỉ node gốc.
 ******************************************************************** */
Node* CreateNode(User user) 
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->item = user;
    p->pleft = NULL;
    p->pright = NULL;
    return p;
}

/*******************************************************************
 * @brief Thêm node vào cây nhị phân theo tên (hoặc số điện thoại)
 * @details Hàm này dựa vào con trỏ hàm trỏ vào hàm so sánh (theo tên 
 *          hoặc theo số điện thoại) để thực hiện gọi hàm và sắp xếp
 *          theo đúng yêu cầu.
 *          - Nếu so sánh theo tên, sử dụng hàm compareByName.
 *          - Nếu so sánh theo số điện thoại, sử dụng hàm compareByPhone.
 * @param[in] t Node gốc của cây nhị phân.
 * @param[in] user Thông tin người dùng cần thêm vào cây.
 * @param[in] cmp Con trỏ hàm so sánh giữa hai node kiểu User.
 *              - int compareByName(User user1, User user2);
 *              - int compareByPhone(User user1, User user2);
 * @return Trả về địa chỉ node sau khi thêm người dùng vào cây.
 ******************************************************************** */
Node* AddNode(Node* t, User user, int (*cmp)(User, User)) 
{
    if (t == NULL) {
        return CreateNode(user); // Tạo node mới chứa thông tin người dùng
    }
    
    // So sánh thông tin người dùng (user) với node hiện tại trong cây
    if (cmp(user, t->item) < 0) {
        t->pleft = AddNode(t->pleft, user, cmp);  
    } 
    // Nếu giá trị người dùng lớn hơn node hiện tại, thêm vào cây con phải
    else if (cmp(user, t->item) > 0) {
        t->pright = AddNode(t->pright, user, cmp); 
    }
    // Trả về gốc của cây
    return t;
}


/*************************************************************
 * @brief So sánh theo tên
 * @param[in] user1 thông tin người dùng 1
 * @param[in] user2 thông tin người dùng 2
 * @details Hàm dùng để so sánh tên của 2 người dùng.
 *          Hàm này sử dụng hàm `strcmp` để so sánh hai chuỗi tên của người dùng.
 * @return
 *          - < 0: nếu tên của user1 nhỏ hơn tên của user2.
 *          - 0: nếu tên của user1 bằng tên của user2.
 *          - > 0: nếu tên của user1 lớn hơn tên của user2.
 ************************************************************ */
int compareByName(User user1, User user2) 
{
    return strcmp(user1.name, user2.name);
}


/*************************************************************
 * @brief So sánh theo số điện thoại
 * @param[in] user1 thông tin người dùng 1
 * @param[in] user2 thông tin người dùng 2
 * @details Hàm dùng để so sánh số điện thoại của 2 người dùng.
 *          Hàm này sử dụng hàm `strcmp` để so sánh hai chuỗi số điện thoại của người dùng.
 * @return
 *          - < 0: nếu số điện thoại của user1 nhỏ hơn số điện thoại của user2.
 *          - 0: nếu số điện thoại của user1 bằng số điện thoại của user2.
 *          - > 0: nếu số điện thoại của user1 lớn hơn số điện thoại của user2.
 ************************************************************ */
int compareByPhone(User user1, User user2) 
{
    return strcmp(user1.phone_number, user2.phone_number); 
}


/*******************************************************************
 * @brief Duyệt cây theo thứ tự in-order
 * @details Hàm này thực hiện duyệt cây nhị phân theo thứ tự in-order, 
 *          nghĩa là duyệt qua cây từ cây con trái, sau đó đến node gốc 
 *          và cuối cùng là cây con phải.
 * @param[in] root Đầu vào là node gốc của cây nhị phân cần duyệt.
 * @return Không trả về giá trị, chỉ thực hiện duyệt cây và in thông tin.
 ******************************************************************** */
void inorder(Node* root) 
{
    if (root != NULL) {
        inorder(root->pleft); // Duyệt cây con trái
        printf("%s, %d, %s, %s\n", root->item.name, root->item.age, root->item.addr, root->item.phone_number);
        inorder(root->pright); // Duyệt cây con phải
    }
}

/*******************************************************************
 * @brief Tìm kiếm theo tên
 * @details Hàm này tìm kiếm thông tin người dùng trong cây nhị phân 
 *          dựa vào tên của người dùng.
 * @param[in] root Đầu vào là node gốc của cây nhị phân cần tìm kiếm.
 * @param[in] name Tên của người dùng cần tìm.
 * @return Trả về node chứa thông tin người dùng nếu tìm thấy, 
 *         hoặc NULL nếu không tìm thấy.
 ******************************************************************** */
Node* searchByName(Node* root, const char* name) 
{
    if (root == NULL) {
        return NULL; // Nếu cây rỗng thì không tìm thấy
    }

    int cmp = strcmp(name, root->item.name);
    if (cmp == 0) {
        return root; // Tìm thấy người dùng
    } else if (cmp < 0) {
        return searchByName(root->pleft, name); // Tìm kiếm trong cây con trái
    } else {
        return searchByName(root->pright, name); // Tìm kiếm trong cây con phải
    }
}


/*******************************************************************
 * @brief Tìm kiếm theo số điện thoại
 * @details Hàm này tìm kiếm thông tin người dùng trong cây nhị phân 
 *          dựa vào số điện thoại của người dùng.
 * @param[in] root Đầu vào là node gốc của cây nhị phân cần tìm kiếm.
 * @param[in] phone_number Số điện thoại cần tìm.
 * @return Trả về node chứa thông tin người dùng nếu tìm thấy, 
 *         hoặc NULL nếu không tìm thấy.
 ******************************************************************** */
Node* searchByPhone(Node* root, const char* phone_number) {
    if (root == NULL) {
        return NULL; // Nếu cây rỗng thì không tìm thấy
    }

    int cmp = strcmp(phone_number, root->item.phone_number);
    if (cmp == 0) {
        return root; // Tìm thấy người dùng
    } else if (cmp < 0) {
        return searchByPhone(root->pleft, phone_number); // Tìm kiếm trong cây con trái
    } else {
        return searchByPhone(root->pright, phone_number); // Tìm kiếm trong cây con phải
    }
}


void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->pleft);   // Giải phóng cây con trái
        freeTree(root->pright);  // Giải phóng cây con phải

        // Giải phóng các trường dữ liệu trong node
        free(root->item.name);
        free(root->item.addr);
        free(root->item.phone_number);

        // Giải phóng node
        free(root);
    }
}
