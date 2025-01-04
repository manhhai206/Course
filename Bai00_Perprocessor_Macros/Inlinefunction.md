
# Inline Function

Inline function cho phép thay thế toàn bộ code trong hàm vào trực tiếp trong vị trí gọi hàm tại thời điểm biên dịch

```c
#include <iostream>
using namespace std;

inline int square(int x) {
    return x * x;
}

int main() {
    int a = 5;
    cout << "Square of " << a << " is " << square(a) << endl;
    return 0;
}
```

Thì khi ở thời điểm compiler thì nó thay thế code trong hàm vào vị trí gọi hàm
```c
int main() {
    int a = 5;
    cout << "Square of " << a << " is " << (a * a) << endl; // Thay thế trực tiếp nội dung hàm
    return 0;
}

```

**Ưu điểm**
- Nó không yêu cầu chức năng gọi overhead.
- Tiết kiệm chi phí gọi hàm, thực hiện chương trình nhanh.
**Nhược điểm**
- Nếu hàm inline được gọi ở nhiều nơi trong chương trình, mã hàm sẽ được sao chép vào mỗi vị trí gọi thì tốn địa chỉ lưu trên Ram làm tăng kích thước