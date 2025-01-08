# Binary Search
- Tìm kiếm nhị phân là một thuật toán tìm kiếm được sử dụng trong một mảng đã được sắp xếp bằng cách chia đôi mảng cần tìm kiếm nhiều lần.
- Chúng ta chia đôi mảng và gọi 2 phần chia đôi đó là left và right
- Phần tử đứng ở giữa left và Right được gọi là Mid
- Chúng ta sẽ dựa vào Mid để tìm xem giá trị chúng ta cần tìm nó nằm trên mảng left hay right
- Nếu giá trị cần tìm nằm ở trên left thì chúng ta sẽ loại bỏ mảng right và chỉ thực hiện tìm kiếm trên left và ngược lại!

![](https://images.viblo.asia/full/b9341996-70ec-4f9b-9c56-464fe4e326f6.png)

## Các bước thực hiện

- Bước 1: Cho 1 mảng arr[] số nguyên đã được sắp xếp và x là giá trị cần tìm
- Bước 2: Thực hiện tách mảng ra làm 2 và tìm phần tử ở giữa mảng và gọi nó là mid, công thức tính (Mid = (left + right)/2)
- Bước 3:
    - Nếu arr[mid] == x thì sẽ return ra mid 
    - Ngược lại nếu arr[mid] > x thì right = mid - 1 vì giá trị cần tìm chắc chắn ko nằm trên right nên ta sẽ loại bỏ nó và tìm từ left đến Mid-1.
    - Ngược lại nếu arr[mid] < x thì left = mid + 1 vì giá trị cần tìm chắc chắn ko nằm trên left nên ta sẽ loại bỏ và tìm từu Mid+1 đến right.

- Triển khai
```c
int binarySearch(int* arr, int l, int r, int x)
{
    if(l <= r)
    {
        int mid = l + (r - l) / 2;

        if(arr[mid] == x) return mid;

        if(arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        return binarySearch(arr, mid+1, r ,x);
    }

    return -1;
}
```
# Binary Tree
- Là cấu trúc dữ liệu cây, trong đó nút cha có thể có tối đa hai nút con. Mỗi nút của cây nhị phân bao gồm 3 trường chứa:
    - dữ liệu
    - địa chỉ của con trái
    - địa chỉ của con phải

![](https://gochocit.com/wp-content/uploads/2021/11/vi-du-cay-nhi-phan-tim-kiem.png)

## Triển khai:
```c
// Định nghĩa cấu trúc node
typedef struct node {
    int item;                // Dữ liệu của node
    struct node* pleft;      // Node con bên trái
    struct node* pright;     // Node con bên phải
} Node;
```
- Mỗi Node trong cây nhị phân chứa 3 thành phần:
    - item: Lưu giá trị dữ liệu của node.
    - pleft: Trỏ tới node con bên trái.
    - pright: Trỏ tới node con bên phải.

```c
// Hàm tạo node mới
Node* CreateNode(int x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->item = x;
    p->pleft = NULL;
    p->pright = NULL;
    return p;
}
```
- Hàm này cấp phát bộ nhớ cho một node mới và khởi tạo các con trỏ pleft và pright về NULL, nghĩa là node chưa có con trái hoặc con phải.
- Giá trị x được gán vào trường item để lưu dữ liệu của node

```c
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
```
- Kiểm tra xem cây hiện tại có rỗng không (t == NULL). Nếu rỗng, tạo một node mới làm node gốc.
- Nếu không rỗng:
    - Nếu x < t->item, đệ quy gọi hàm AddNode với cây con trái (t->pleft).
    - Nếu x > t->item, đệ quy gọi hàm AddNode với cây con phải (t->pright).
```c
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
```
- Nếu cây rỗng (t == NULL) hoặc giá trị tại node hiện tại (t->item) bằng với giá trị cần tìm x, thì trả về node đó.
- Nếu x < t->item, tìm tiếp trong cây con trái (t->pleft).
- Nếu x > t->item, tìm tiếp trong cây con phải (t->pright).

# File operations
Ngôn ngữ lập trình C cung cấp 1 số thư viện dùng để hỗ trợ trong việc thao tác với file.

File CSV là một loại văn bản được sủ dụng để lưu trữ và truyền tải dữ liệu có cấu trúc bảng, trong đó các dữ liệu của các cột được phân tách bằng dấu "," hoặc 1 ký tư khác.

Để mở một file. sủ dụng hàm fopen(). Hàm này trả về 1 con trỏ File,và cần được kiểm tra đảm bảo mở file thành công.

`File *file = fopen(const char* file_name, const char* access_mode)`

- Chế độ:
    + r: Mở file với chế độ đọc file. Nếu thành công trả về địa chỉ phần tử đầu tiên còn không thì trả về NULL.
    + rb: Mở file ở chế độ đọc file theo định dạng binary.
    + w: Mở file ở chế độ ghi.
    + wb: Mở file ở chế độ ghi theo địng dạng binary.
    .....

- Đọc file:
    + fscanf(): sử dụng chuỗi được địng dạng và danh sách biến đổi số để lấy đầu vào từ 1 file
    + fgets(): Copy nội dung trong File vào mảng dùng để lưu trữ tối đa lượng phần tử của mảng hoặc tới ký tự xuống đòng.
    + fgetc(): Lấy giá trị địa chỉ hiện tại của file, sau đó di chuyển tới địa chỉ tiếp theo. Kiểu trả về là char.
    + fread(): Đọc số lượng byte được chỉ định từ file.bin
    ....

## Triển khai

```c
    FILE *file = fopen(DataBate_Path, "w" );

    if(file == NULL)
    {
        printf("Cannot open file\n");
        return FILE_CREATE_FAILED;
    }

    /* Ghi dòng tiêu đề vào file csv */
    fprintf(file, "Name,Age,Address,Phone-Number");

    /* Ghi các thông tin vào file CSV */
    fprintf(file, "Hai,20,Binh Duong,023-476\n");
    fprintf(file, "Nam,21,Thu Duc,067-444\n");
    fprintf(file, "Ne,22,Dong Nai,033-630\n");
    fprintf(file, "An,23,Vung Tau,013-006\n");

    /* Đóng file CVS */
    fclose(file);
```
- Ghi các thông tin vào file csv
    + Truyền DataBate_Path: địa chỉ file cvs cần tại
    + `w` là quyền ghi vào csv.
- Dùng fprintf để ghi thông tin vào file csv
- Đóng file bằng hàm fclose().

```c
/* Mở file ở chế độ đọc */
    file = fopen(DataBate_Path, "r");

    if (file == NULL) {
        printf("Cannot open file for reading\n");
        return FILE_CREATE_FAILED;
    }

    char line[100]; /* Bộ nhớ đệm dùng để lưu trữ dòng CSV */

    /* Bỏ qua dòng tiêu đề */
    fgets(line, sizeof(line), file); // "Name,Age,Address,Phone-Number"

    /* In ra tiêu đề */
    printf("%-20s %-5s %-20s %-15s\n", "Name", "Age", "Address", "Phone Number");

    /* Đọc từng dòng dữ liệu từ file CSV */
    while (fgets(line, sizeof(line), file)) {
        char name[20], address[20], phone[15];
        int age;

        /* Tách dữ liệu từ dòng CSV và in ra */
        sscanf(line, "%[^,],%d,%[^,],%s", name, &age, address, phone);
        printf("%-20s %-5d %-20s %-15s\n", name, age, address, phone);
    }

    /* Đóng file CSV */
    fclose(file);
```
- fopen: Mở file tại DataBate_Path với chế độ "r" (read). File được mở chỉ để đọc.
- fgets: Đọc một dòng từ file và lưu vào line.
- Dòng đầu tiên là tiêu đề (Name,Age,Address,Phone-Number) nên chỉ cần đọc và bỏ qua.
- fgets: Đọc từng dòng dữ liệu từ file CSV.
- sscanf: Phân tích (parse) dòng dữ liệu thành các trường:
    - %[^,]: Đọc chuỗi đến dấu phẩy (,) và lưu vào name.
    - %d: Đọc số nguyên và lưu vào age.
    - %[^,]: Đọc chuỗi đến dấu phẩy và lưu vào address.
    - %s: Đọc chuỗi còn lại và lưu vào phone.

