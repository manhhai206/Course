#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Khai báo vector và khởi tạo giá trị
    vector<int> vec = {1, 2, 3, 4, 5};

    // Sử dụng iterator để duyệt qua vector
    cout << "Duyet qua vector bang iterator:" << endl;
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " "; // Truy cập giá trị phần tử
    }
    cout << endl;
}