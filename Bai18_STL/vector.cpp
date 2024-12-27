#include <iostream>
#include <vector>

using namespace std;

/*
 * Ví dụ sử dụng các phương thức:
 * at(), size(), resize(), end(), push_back(), pop_back(), insert(), erase()
 */

int main() {
    // Khởi tạo vector với các phần tử ban đầu
    vector<int> arr = {2, 5, 7, 9, 11};

    // 1. Xóa phần tử đầu tiên
    arr.erase(arr.begin()); // Xóa phần tử ở vị trí đầu tiên (giá trị 2)

    // 2. Xóa phần tử ở vị trí 2
    if (arr.size() > 2) {
        arr.erase(arr.begin() + 1); // Xóa phần tử tại chỉ số 1 (giá trị 7)
    }

    // 3. Xóa phần tử cuối cùng
    if (!arr.empty()) {
        arr.erase(arr.end() - 1); // Xóa phần tử cuối (giá trị 11)
    }

    // 4. Chèn một phần tử vào vị trí thứ 2
    arr.insert(arr.begin() + 1, 20); // Chèn giá trị 20 vào chỉ số 1

    // 5. Thêm phần tử mới vào cuối vector
    arr.push_back(15); // Thêm giá trị 15 vào cuối vector

    // 6. Xóa phần tử cuối cùng
    arr.pop_back(); // Xóa phần tử cuối (giá trị 15)

    // 7. Thay đổi kích thước của vector
    arr.resize(6, 0); // Tăng kích thước lên 6 phần tử, giá trị mặc định là 0

    // 8. In ra các phần tử của vector
    cout << "Các phần tử trong vector:" << endl;
    for (int i = 0; i < arr.size(); i++) {
        cout << "value[" << i << "] = " << arr.at(i) << endl;
    }

    return 0;
}
