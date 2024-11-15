


# LinkedList

Danh sách liên kết đơn là một cấu trúc dữ liệu động, nó là một danh sách mà mỗi phần tử đều liên kết với phần tử đúng sau nó trong danh sách. Mỗi phần tử (được gọi là một node hay nút) trong danh sách liên kết đơn là một cấu trúc có hai thành phần:

- Thành phần dữ liệu: lưu thông tin về bản thân phần tử đó.
- Thành phần liên kết: lưu địa chỉ phần tử đứng sau trong danh sách, nếu phần tử đó là phần tử cuối cùng thì thành phần này bằng NULL.

![](https://topdev.vn/blog/wp-content/uploads/2020/10/Single-linked-list-3.png)

## Đặc điểm của danh sách liên kết đơn
Do danh sách liên kết đơn là một cấu trúc dữ liệu động, được tạo nên nhờ việc cấp phát động nên nó có một số đặc điểm sau đây:
- Được cấp phát bộ nhớ khi chạy chương trình
- Có thể thay đổi kích thước qua việc thêm, xóa phần tử

## Triển khai code

**Tạo Node**    
Một node gồm hai thành phần là thành phần dữ liệu và thành phần liên kết. Thành phần liên kết là địa chỉ con trỏ, con trỏ này trỏ đến node tiếp theo, do đó, con trỏ này là con trỏ trỏ vào một node.

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;
```

Để tạo một node mới, ta thực hiện cấp phát động cho node mới, khởi tạo giá trị ban đầu và trả về địa chỉ của node mới được cấp phát.
```c
Node* createNode(int value) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}
```

![](https://topdev.vn/blog/wp-content/uploads/2020/10/Add-node-to-head-1.png)
```c
void addFirst(Node** head, int value) {
    Node* p = createNode(value);
    p->next = *head; 
    *head = p;       
}
```
Chúng ta sẽ tạo 1 node mới là p. Ta thực hiện trỏ p->next của node p vào head của danh sách, sau đó ta trỏ head vào node mới vừa được thêm. Vậy là phần tử đó đã nằm ở đầu danh sách.

![](https://topdev.vn/blog/wp-content/uploads/2020/10/Add-node-to-tail-1.png)
```c
void addLast(Node** head, int value){
    Node* p = createNode(value);

    if (*head == NULL) {
        *head = p;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = p;
}
```
Chúng ta thực hiện thêm node p vào danh sách. 

Kiểm tra con trỏ head có đang trỏ đén Null hay không ?
- Nếu có thì gán *head = p;
- Nếu không trống thì tạo *last và gán bằng *head và duyệt qua từng node bằng cách gán last = last->next.Nếu thỏa điểu kiện thì thoát ra vòng while thì vị trí trỏ đến null là last thì last->next = p => p đã được thêm vào cuối.

![](https://topdev.vn/blog/wp-content/uploads/2020/10/Insert-after-Q-1-1.png)
```c
void addAfter(Node **head, int v2, int value){
    Node *p = createNode(value);
    Node *q = *head;
    while(q != NULL && q->data != v2){
        q = q->next;
    }

    if(q != NULL){
        p->next = q->next;
        q->next = p;
    }
}
```
Chúng ta thực hiện thêm node p vào danh sách.

Tạo thêm node q và gán bằng *head

Sử dụng vòng while để duyệt từng phần tử và kiếm tra xem nó duyệt đến data cần chèn sau chưa, chưa thỏa thì cứ  q = q->next.

Nếu thỏa rồi thì thoát hàm while và sau đó gán p->next = q->next và q->next = p.

![](https://topdev.vn/blog/wp-content/uploads/2020/10/Remove-head-2.png)
```c
void deleteFirst(Node **head){

    if(head != NULL)
    {
        Node*p = *head;
        *head = p->next;
        p->next=NULL;
        free(p);
    }
}
```
Mình trỏ head đến next của node p (hiện đang là head do *p = *head), thì head lúc này sẽ là p->next , sau đó mình free đi node p là được.

![](https://media.geeksforgeeks.org/wp-content/uploads/20240730120651/Deletion-At-End.webp)
```c
void deleteLast(Node **head){
    if(head != NULL)
    {
        Node* last = *head;
        Node*prev = NULL;

        while(last->next != NULL){
            prev = last;
            last = last->next;
        }

        if(prev == NULL)
        {
            deleteFirst(head);
        } else {
        prev->next = NULL;
        free(last);
        }
    }
}
```
Kiểm tra xem head có phải là NULL không. Nếu head là NULL, tức là danh sách rỗng, thì không làm gì thêm.

Khởi tạo con trỏ last và prev:
- last được khởi tạo để trỏ đến node đầu tiên (*head), và prev là con trỏ trước last, khởi tạo NULL vì chưa có node nào trước head.

Dùng vòng lặpđể quét qua từng node trong danh sách cho đến khi tìm thấy node cuối cùng = NULL.
- prev = last; gán prev bằng last.
- last = last->next; di chuyển last tới node tiếp theo.

Khi chỉ có 1 node duy nhất trong danh sách(prev == NULL)  thì deleteFirst(head) để xóa node đầu tiên trong danh sách.

Nếu prev không phải là NULL, điều này có nghĩa là có ít nhất hai node trong danh sách. prev->next = NULL; gán next của prev bằng NULL, do đó loại bỏ last khỏi danh sách. 

![](https://images.viblo.asia/full/6ad02c40-ecf1-4ec4-b8f4-2075e2c9cf30.png)
```c
void deleteNode(Node **head, int value){
    if(head != NULL){
        Node* p = *head;
        Node* prev =  NULL;

        while(p->data != value){
            prev = p;
            p = p->next;
        }
        
        if(p != NULL)
        {
            if(prev ==NULL){
               deleteFirst(head);
            }
            else
            {
            prev->next=p->next;
            p->next=NULL;
            free(p);
            }
        }
    }
}
```
Kiểm tra xem head có phải là NULL không. Nếu head là NULL, tức là danh sách rỗng, thì không làm gì thêm.

Khởi tạo con trỏ *p và prev:
- p được khởi tạo để trỏ đến node đầu tiên (*head), và prev là con trỏ trước p, khởi tạo NULL vì chưa có node nào trước head.

Dùng vòng lặp để quét qua từng node trong danh sách cho đến khi tìm thấy node có data cần xóa.
- prev = p; gán prev bằng p.
- p = p->next; di chuyển tới node tiếp theo.

Khi chỉ có 1 node duy nhất trong danh sách(prev == NULL)  thì deleteFirst(head) để xóa node đầu tiên trong danh sách.

Nếu prev không phải là NULL, điều này có nghĩa là có ít nhất hai node trong danh sách. prev->next = p->next; gán next của p bằng NULL, do đó loại bỏ p khỏi danh sách. 
```c
void output(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}
```
Gán *p = head và duyết qua các node trong danh sách  p = p->next cho đến khi  p = NULL thì thoát điều kiện.
