# Vector
Vector là một class template cung cấp một mảng động với khả năng thay đổi kích thước linh hoạt. Vector là một phần của thư viện <vector> và thường được sử dụng để làm việc với danh sách các phần tử mà số lượng có thể thay đổi trong quá trình chạy chương trình.
```c
#include <vector> 
#include <iostream> 

int main() {
    /* Vecto được cấu tạo bằng class template */
    vector<int> arr = {2, 5, 7, 9}; // Khởi tạo vector với các phần tử ban đầu
    for (auto num : arr) {
        cout << num << endl;
    }
    return 0;
}
```
Đặc điểm của vector:
- Mảng động linh hoạt: Vector tự động thay đổi kích thước khi thêm hoặc xóa phần tử.
- Truy cập ngẫu nhiên: Vector hỗ trợ truy cập phần tử nhanh như mảng thông thường qua chỉ số ([] hoặc at()).
- Thêm và xóa: Chèn và xóa phần tử ở cuối vector có hiệu suất tốt. Tuy nhiên, chèn và xóa ở vị trí bất kỳ có thể đòi hỏi di chuyển một số phần tử.

Một số method của vector:
- **at()**: Truy cập vào phần tử của vector
- **size()**: Trả về kích thước của vector
```c
    vector<int> arr = {2, 5, 7, 9};

    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output:
```c
    value 2
    value 5
    value 7
    value 9
```   
- **resize()**: Thay đổi kích thước của vector
```c
    vector<int> arr = {2, 5, 7, 9};

    arr.resize(7);//Thay đổi kích thước của mảng động 

    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output
```
    value 2
    value 5
    value 7
    value 9
    value 0
    value 0
    value 0
```    
- **begin()**: Địa chỉ của phần tử đầu tiên của vector
- **end()**: Địa chỉ của phần tử cuối cùng của vector
```c
    vector<int>::iterator it;

    for(it = arr.begin();it != arr.end();it++){
        /** 
         * arr.begin(): địa chỉ phần tử đầu tiên
         * arr.end(): địa chỉ phần tử cuối cùng
         */
        cout << "value "<<*it<<endl;
    }
```
- **push_back()**: Thêm phần tử vào vị trí cuối của vector
```c

    arr.push_back(15); //Thêm 15 ở cuối vector
    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output
```c
    value 2
    value 5
    value 7
    value 9
    value 15
```
- **pop_back()**: Xóa phần tử ở cuối của vector
```c
    arr.push_back(15); //Thêm 15 ở cuối vector
    arr.pop_back(); //Xóa vị trí cuối của vector
    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output
```
    value 2
    value 5
    value 7
    value 9
```
- **insert()**: Thêm vào vị trí bất kì
```c
    /* Vecto được cấu tạo bằng class template */
    vector<int> arr = {2, 5, 7, 9};

    arr.insert(arr.begin(),10); //Thêm vào vị trí đầu tiên thông quan insert
    arr.insert(arr.begin() + 3 ,15); // Thêm vào vị trí thứ 4
    arr.insert(arr.end(),50); //Thêm vào vị trí cuối

    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output
```c
value 10
value 2
value 5
value 15
value 7
value 9
value 50
```
- **erase()**: Xóa vào vị trí bất kì
```c
    /* Vecto được cấu tạo bằng class template */
    vector<int> arr = {2, 5, 7, 9, 11};

    arr.erase(arr.begin());     //Xóa phần tử ở vị trí đầu
    arr.erase(arr.begin()+1);   //Xóa phần tử ở vị trí 2
    arr.erase(arr.end() - 1);       //Xóa phần tử ở vị trí cuối

    for(int i = 0; i < arr.size(); i++){
        cout << "value " << arr.at(i) << endl;
    }
```
Output
```c
value 5
value 9
```
# List
List được triển khai dưới dạng danh sách liên kết đôi. Nó khác với vector ở chỗ các phần tử trong list không được lưu trữ liên tiếp trong bộ nhớ mà liên kết với nhau thông qua con trỏ.

Một số đặc điểm quan trọng của list:
- Truy cập tuần tự: Truy cập các phần tử của list chỉ có thể thực hiện tuần tự, không hỗ trợ truy cập ngẫu nhiên do phải thao tấc thông qua con trỏ
- Hiệu suất chèn và xóa: Chèn và xóa ở bất kỳ vị trí nào trong danh sách có hiệu suất tốt hơn so với vector. Điều này đặc biệt đúng khi thêm/xóa ở giữa danh sách.

Có 2 cách khởi tạo 1 danh sách:
- Cách 1: Khai báo cụ thể giá trị của từng node
```c
list<int> lst = {1,2,3,4};
```
- Cách 2: Sử dụng **push_back** và **push_front**:
```
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(10);
```

Cũng có 2 cách để đọc các node:
- Dùng vòng lặp cải tiến:
```
    auto i = 0;
    /* Vòng for cải tiến */
    for(auto item : lst){
        cout <<"node: " <<i++<<", value: " << item <<endl;
    }
```
- Dùng iterator:
```c
    list<int>::iterator it;

    it = lst.end();
    cout <<"address end: "<<&(*it)<<endl;

    /* Vòng for sử dụng iterator*/
    for(it = lst.begin();it != lst.end();it++){
        cout << "addr: " <<&(*it)<<", node: "<<i++ <<", value: "<<*it<<endl;
    }
```
- Thêm/Xóa các node ở vị trí bất kì:
```c
    i = 0;
    for(it = lst.begin();it != lst.end();it++)
    {
        if(i ==  1){ //them node tai vi tri thu 2
            lst.insert(it,50);
        }

        if(i ==  2){ //them node tai vi tri thu 3
            lst.insert(it,100);
        }

        if(i == 3){
            lst.erase(it); //xoa node
        }

        i++;
    }
```
## So sánh giữa Vecto và List
- So về truy cập ngẫu nhiên thì : Vector trội hơn List vì Vecto được cấp phát địa chỉ liên tiếp nhau nên truy cập ngay lập tức thông qua các chỉ số còn List phải duyệt qua từng node bằng con trỏ.
- Còn so về các thao tác thêm/xóa: thì List lại trội hơn vector vì khi thay đổi thì vector bị tác động với các địa chỉ các vị trí xung quanh còn List thì nhanh hơn do các địa chỉ ngẫu nhiên nên không tác động đến vị trí xung quanh.
- Dung lượng: Vecto thì phải quan tâm đến số lượng còn List thì không quan tâm đến số lượng node.
# Map
Map lưu trữ các phần tử dưới dạng cặp key-value, trong đó mỗi key phải là duy nhất trong map.

Ta có thể thêm phần tử mới vào map bằng cách sử dụng operator [] hoặc hàm insert(). Để xóa phần tử, bạn có thể sử dụng hàm erase().

Ta có thể sử dụng iterator để duyệt qua các phần tử của map

- Hoạt động theo kiểu Key-Value
- Object testmap được khởi tại tại Stack
- Key-Value được lưu ở Heap
- Key phải khác nhau
- Key được tự động sắp xếp theo thứ tự theo bảng mã ASCI
```c
     map<int,string> testmap;
    //testmap[string key ] = string value;
    testmap[1] =  "Hai";    // Cách khai báo 
    testmap[2] = "Ha"; 

    // for(auto item: testmap){
    //     cout <<"Key: " << item.first << " , Value:  " <<item.second <<endl;
    // }

    testmap.insert({4,"Ho"});   // Có thể dùng insert để khai báo
    testmap.insert({3,"Hoang"});
    testmap.erase(3);

    map<int, string>::iterator it;
    
    for(it = testmap.begin(); it != testmap.end(); it++){
        cout <<"Key: " << (*it).first << " , Value: " <<(*it).second <<endl;
    }
```
# Iterator
Iterator cung cấp một cách chung để duyệt qua các phần tử của một container mà không cần biết chi tiết về cách container được triển khai.
- Iterator là một đối tượng cho phép truy cập tuần tự qua các phần tử của một container.
- Nó giống như con trỏ, cho phép di chuyển qua các phần tử trong container.

## Array
Array là một class template cung cấp như một mảng tĩnh với kích thước cố định. Array là một phần của thư viện <vector>.
- array có kích thước cố định được xác định tại thời điểm biên dịch và không thể thay đổi sau khi được khai báo.
- array hỗ trợ truy cập ngẫu nhiên vào các phần tử thông qua toán tử []
```c
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
```

# Algorithm
Algorithm cung cấp một số thuật toán tiêu biểu . Các thuật toán này hoạt động trên các phạm vi hoặc các loại dữ liệu khác nhau, giúp thực hiện các nhiệm vụ như sắp xếp, tìm kiếm, chuyển đổi dữ liệu, và nhiều thao tác khác. 
```c
    vector <int> arr = {3,5,7,4,1};

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    sort(arr.begin(), arr.end());
    cout << "vector after sort ascending: " << endl;
    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    sort(arr.begin(), arr.end(), greater<int>());
    cout << "vector after sort descending: " << endl;
    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }
```