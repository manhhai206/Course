
# Namespace

Namespace là cách nhóm các định danh như tên biến, hàm, lớp... vào một không gian tách biệt. Điều này giúp tránh xung đột tên khi các định danh giống nhau được khai báo trong các phần khác nhau của chương trình hoặc giữa các thư viện.

```c
namespace A{
    char *name = (char*)"Trung 20";

    void display(){
        cout << "Name: " << name << endl;
    }
}
```
Để sử dụng các phần tử trong namespace, bạn cần sử dụng toán tử truy cập **::**
```c
cout << "Name: " << A::name << endl;
    A::display();
```

## Using
Từ khóa using cho phép bạn truy cập trực tiếp các phần tử trong namespace mà không cần sử dụng toán tử ::
```c
#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"Trung 20";

    void display(){
        cout << "Name: " << name << endl;
    }
}

namespace B{
    char *name = (char*)"Trung 21";

    void display(){
        cout << "Name: " << name << endl;
    }
}

using namespace A;

int main(int argc, char const *argv[])
{
    cout << "Name: " << name << endl;
    display();

    cout << "Name: " << B::name << endl;
    B::display();
    return 0;
}
```
- Chỉ sử dụng using namespace khi các thành phần truy cập là duy nhất, vì nếu có nhiều định danh trùng tên trong các namespace khác nhau, chương trình sẽ báo lỗi.
- Trong trường hợp có nhiều namespace, có thể sử dụng toán tử :: để chỉ định rõ ràng namespace muốn truy cập.
## Namespace lồng nhau
Một namespace có thể chứa một namespace khác bên trong nó.
```C
namespace A{
    char *name = (char*)"Trung 20";

    void display(){
        cout << "Name: " << name << endl;
    }

    namespace C {
        char *name2 = (char*)"Hai 22";
    }
}

using namespace A;
```
- Khi sử dụng using namespace, chỉ các thành phần trong namespace chính được truy cập trực tiếp. Các thành phần trong namespace con vẫn cần sử dụng toán tử truy cập ::
```c
    cout << "Name: " << C::name2 << endl;
```

## Namespace mở rộng
Namespace có thể được mở rộng bằng cách khai báo nhiều lần cùng một tên namespace trong các phần khác nhau của chương trình. Các khai báo cùng namespace thì nó sẽ gộp tất cả lại thành 1.