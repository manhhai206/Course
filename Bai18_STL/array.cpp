#include <iostream>
#include <array> 

using namespace std;

int main() {
    // Khai báo một std::array với 5 phần tử kiểu int
    array<int, 5> arr = {1, 2, 3, 4, 5};

    // 1. Truy cập các phần tử bằng toán tử []
    cout << "Phan tu dau tien: " << arr[0] << endl;
    cout << "Phan tu cuoi cung: " << arr[4] << endl;

    // 2. Truy cập các phần tử bằng phương thức at()
    cout << "Phan tu tai vi tri thu 3: " << arr.at(2) << endl;

    // 3. Sử dụng phương thức front() và back()
    cout << "Phan tu dau tien (front): " << arr.front() << endl;
    cout << "Phan tu cuoi cung (back): " << arr.back() << endl;

    // 4. Sử dụng fill() để gán tất cả các phần tử một giá trị
    arr.fill(0);
    cout << "Array sau khi fill(): ";
    for (auto val : arr) {
        cout << val << endl;
    }
    cout << endl;

    return 0;
}
