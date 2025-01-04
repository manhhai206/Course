
# Smart pointers
Smart pointers là một cơ chế quản lý bộ nhớ tự động giúp giảm thiểu rủi ro của lỗi liên quan đến quản lý bộ nhớ và giúp người lập trình tránh được việc quên giải phóng bộ nhớ đã được cấp phát.
Các smart pointer đều là các class template và không phải là con trỏ . Chúng chứa một con trỏ thô bên trong và cung cấp các phương thức để làm việc với đối tượng được quản lý.

# Unique Pointer
Unique Pointer là 1 loại Smart Pointer giúp quản lý tự động và tự động giải phóng bộ nhớ khi không cần thiết.

Đặc điểm của unique_prt chỉ có thể sở hữu một đối tượng hoặc mảng và khi một unique_prt bị hủy , bộ nhớ sẽ được tự động giải phóng.

```c
template <typename T>
class UniquePointer
{
    private:
        T *ptr; /**< Con trỏ thô đến đối tượng được quản lý. */
}
```
- Class unique_prt bên trong chỉ có duy nhất 1 con trỏ ptr trỏ đến đổi tương quản lý.
- Và class unique_prt cũng có các method để đảm rằng con trỏ đó có thể sở hữu 1 đối tượng duy nhất.

```c
    public:
        /**
         * @brief   Constructor khởi tạo con trỏ UniquePointer.
         * @param   p   Con trỏ thô đến đối tượng. Giá trị mặc định là nullptr.
         */
        UniquePointer(T *p = nullptr): ptr(p){}
```
- Constructor trong class được khởi tạo để trỏ đến đối tượng cần quản lý
```c
    UniquePointer<int> uptr(new int(10)); 
```
- Nên khai khởi tạo 1 object thì con trỏ ptr sẽ trỏ đến địa chỉ của cấp phát động new int(10), còn nếu không khởi tạo Constructor thì nó sẽ tự động trỏ đến Null.

```c
        /**
         * @brief   Destructor giải phóng vùng nhớ của đối tượng được quản lý nếu không null.
         */
        ~UniquePointer()
        {
            if (ptr)
            {
                delete ptr;
            }
        }
```
- Hàm Destructor thì nó thu hồi vùng nhớ của object và nó cũng thi hồi lại vùng nhớ mà ptr này đang quản lý.

```c
        /**
         * @brief   Xóa bỏ khả năng sao chép đối tượng UniquePointer.
         */
        UniquePointer(const UniquePointer&) = delete;
```
- Cái method này được sử dụng để tránh các object khác gán bằng các object đã được khởi tạo rồi. Đảm bảo rằng chỉ có 1 đối tượng là được 1 object quản lý thôi.

```c
        /**
         * @brief   Xóa bỏ khả năng gán bằng copy đối tượng UniquePointer.
         * @return  Trả về tham chiếu đến đối tượng UniquePointer hiện tại.
         */
        UniquePointer& operator = (const UniquePointer&) = delete;
```
- unique_prt cũng có operator overloading để tránh sử dụng toán tử = để gán 2 objec bằng nhau.

```c
/**
         * @brief   Toán tử dereference để truy cập đối tượng được quản lý.
         * @return  Tham chiếu đến đối tượng được quản lý.
         */
        T& operator * () const
        {
            return *ptr;    // *0x01 = 10
        }
```
- Toán tử * dùng để giải tham chiếu tại địa chỉ ptr đang quản lý

```c
        /**
         * @brief   Toán tử để truy cập các thành phần của đối tượng.
         * @return  Con trỏ đến đối tượng được quản lý.
         */
        T* operator -> () const
        {
            return ptr;
        }
```
- Toán tử -> dùng để truy cập các thành phần của đối tượng.

```c
    int* rawPtr = uptr.get(); // 0x01
    cout << "giá trị con trỏ thô: " << *rawPtr << endl;
    delete rawPtr;
```
- unique_prt thì chỉ giúp tránh object khác quản lý lại đối tượng mà có 1 object đang quản lý. 
- Nhưng 1 con trỏ thông thường vẫn có thể truy cập tới được.

```c
        /**
         * @brief   Trả về con trỏ thô đến đối tượng được quản lý.
         * @return  Con trỏ thô đến đối tượng.
         */        
        T* get() const
        {
            return ptr; // 0x01
        }

       
        /**
         * @brief   Chuyển quyền sở hữu đối tượng cho con trỏ bên ngoài và đặt ptr thành nullptr.
         * @return  Con trỏ thô đến đối tượng trước khi release.
         */
        T* release()
        {
            T* temp = ptr;  // lưu lại địa chỉ của đối tượng đang quản lý
            ptr = nullptr;  // đặt con trỏ thô ptr thành con trỏ null
            return temp;    // trả về địa chỉ của đối tượng
        }
```
- Hàm get() và release() là trả về địa chỉ đối tượng đang quản lý.
- get() vẫn giữ quyền sở hữu còn release() không còn quản lý do gán bằng null.

***Tóm tắt***
- Smart pointers không phải là 1 con trỏ là 1 class, bên trong class này chứa 1 con trỏ thô bên trong và có chứa các method khác.
- Khi khai báo 1 object thuộc class này thì object đó sẽ quản lý con trỏ thô và method.
- Để mà con trỏ thô quản lý 1 đối tượng thì phải thông qua object, object truyền vào 1 đối tượng thì con trỏ thô ptr sẽ quản lý.
- unique_prt chỉ ngăn chặn các object khác không được truy cập đến đối tượng đó chứ con trỏ khác vẫn truy cập được.

# Share Pointer
share_ptr là 1 Smart Pointer hỗ trợ chia sẽ quyền sở hữu với 1 đối tượng. Nhiều share_ptr cũng có thể sở hữu 1 đối tượng. Đối tượng sẽ được thu hồi nếu không có share_ptr nào sở hữu nó.

```c
    shared_ptr<int> sptr1 = make_shared<int>(20); //0x01
    shared_ptr<int> sptr2 = sptr1;
    shared_ptr<int> sptr3 = sptr1;

    {
        shared_ptr<int> sptr4 = sptr1;
        cout << "Count" <<sptr1.use_count() << endl;
    }

    cout << "Count" << sptr1.use_count() <<endl;
    /***************************************************
     * use_count(): trả về số lượng shared_ptr cùng quản lý đối tương
     * (kiểm tra số lượng tham chiếu) 
     ************************************************** */
    cout << "sptr1 " <<*sptr1 <<endl;
    cout << "sptr2 " <<*sptr2 <<endl;
    cout << "sptr3 " <<*sptr3 <<endl;
```
- Khởi tạo 4 share_ptr để quản lý 1 đối tượng duy nhất.
- use_count() là bộ đếm tham chiếu để theo dỗi số lượng share_ptr đang tham chiếu đến 1 đối tượng.
```c
Count4
Count3
sptr1 20
sptr2 20
sptr3 20
```
- Output trả về ban đầu có 4 share_ptr quản lý đối tượng và sau đó hủy đi 1 và còn 3. Và các giá trị share_ptr tham chiếu đến đối tượng đều cùng giá trị share_ptr quản lý.

```c

    int *rawPtr = sptr1.get();
    cout << "rawPtr: " << *rawPtr << endl;
    /**************************************************
     *  trả về con trỏ thô (int*) trỏ tới vùng mà ptr1 đang quản lý
     ************************************************* */

    *sptr1 = 50;
    cout << "sptr1 " <<*sptr1 <<endl;
    *rawPtr = 100;
    cout << "sptr1 " <<*sptr1 <<endl;
```
- get() trả về con trỏ thô mà shared_ptr đang quản lý thì lúc này rawPtr sẽ trỏ tới đối tượng.
- Có thể thay đối giá trị của đối tượng bằng con trỏ rawPtr.
```c
sptr1 50
sptr1 100
```

```c
    shared_ptr<int> a = make_shared<int>(50);
    shared_ptr<int> b = make_shared<int>(60);
    a.swap(b);
    cout << "a =  " << *a <<endl;
    cout << "b =  " << *b <<endl;
```
- swap lại các đối tượng được luôn.

```c
    a = move(b);
    cout << "a =  " << *a <<endl;
```
- Có thể chuyển quyền sở hữu.

```c
    sptr1.reset(new int(10));
    cout << "sptr1 = " << *sptr1 <<endl;
    cout << "sptr2 = " << *sptr2 <<endl;
```
- Reset lại đối tượng bằng 1 đối tượng mới nhưng khác với unique_prt(giải phóng đối tượng cũ) còn shared_ptr là không giải phóng do vẫn còn các shared_ptr vẫn đang quản lý (giống release của unique_prt).

**TÓM TẮT**
- share_ptr là Smart pointers hỗ trợ chia sẽ quyền sở hữu với 1 đối tượng
- Nhiều share_ptr vẫn có thể sở hữu 1 đối tượng
- đối tượng sẽ bị thu hồi nếu không có share_ptr nào tham chiếu đến đối tượng

# Weak Pointer

Weak Pointer là 1 Smart pointers dùng để theo dõi 1 đối tượng đang được quản lý bởi shared_ptr.

Sẽ không làm tăng bộ đếm tham chiếu của shared_ptr, không truy cập trực tiếp đến đối tượng đang theo dõi.

```c
    shared_ptr<int> sptr1 = make_shared<int>(20);
    shared_ptr<int> sptr2 = sptr1;

    //Tạo 1 weak pointer trỏ tới đối tượng mà shared pointer đang quản lý
    weak_ptr<int> ptr3 = sptr1;
    
    cout << "Count" << sptr1.use_count() <<endl;
```
Output : chứng tỏ weak_ptr không làm tăng số lượng tham chiếu của share_ptr. 
```c
Count2
```

```c
    /****************************************************
     * lock(): chuyển weak_ptr sang shared_ptr tại 1 thời điểm
     *          và sau khi kết thúc lệnh lại chuyển về weak_ptr
     * Dùng để đọc giá trị hiện tại 
     *************************************************** */
    cout << "ptr3 " <<*(ptr3.lock()) <<endl;
    cout << "Count " << sptr1.use_count() <<endl;
```
- method lock(_) giúp chuyển từ weak_ptr sang share_ptr tại 1 thời điểm để đọc giá trị hiện tại của đối tượng và rồi hết lệnh thì chuyển lại thành weak_ptr.

```c
    sptr1.reset(); // giải phóng quyền sở hữu của sptr1 đối với đối tượng
    sptr2.reset(); // giải phóng quyền sở hữu của sptr1 đối với đối tượng
    /************************************************************
     * expired() : kiểu boolean dùng để kiểm tra xem đối tượng hiện tại 
     *              có còn quản lý bởi shared_ptr không.
     * return True nếu không có bất kì 1 shared_ptr nào quản lý đối tượng
     * return False nếu vẫn còn có shared_ptr quản lý đối tượng
     *********************************************************** */
    cout << "check " << ptr3.expired() <<endl;
```
- expired() dùng để kiếm tra xem đối tượng hiện tại có còn quản lý bởi share_ptr nào hay không. Nếu reset hết tất cả các share_ptr quản lý đến đối tượng thì sẽ trả về True(1) còn nếu vẫn còn thì là False(0).

***TÓM TẮT***
- Weak pointers là Smart Pointer dùng để theo dõi đối tượng mà share_ptr đang quản lý.
- Nó sẽ không làm tăng số lượng tham chiếu của share_ptr, không truy cập trực tiếp đến đối tượng hiện tại.

# So sánh 3 loại Smart Pointer trong C++

## Điểm chung
- Cả ba loại smart pointer đều giúp quản lý và tự động giải phóng bộ nhớ động (heap) mà không cần gọi thủ công delete.
- Các smart pointer đều là các class template và không phải là con trỏ . Chúng chứa một con trỏ thô bên trong và cung cấp các phương thức để làm việc với đối tượng được quản lý.
- Ngăn chặn lỗi bộ nhớ phổ biến như rò rỉ bộ nhớ (memory leak).

---

## Điểm khác nhau

| Thuộc tính               | `unique_ptr`                                                                               | `shared_ptr`                                                                            | `weak_ptr`                                                                                           |
|--------------------------|-----------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------|
| **Quyền sở hữu**         | Quyền sở hữu độc quyền, chỉ có một `unique_ptr` quản lý đối tượng tại một thời điểm.       | Chia sẻ quyền sở hữu. Nhiều `shared_ptr` có thể cùng quản lý một đối tượng.            | Không có quyền sở hữu, chỉ "theo dõi" đối tượng được quản lý bởi `shared_ptr`.                        |
| **Reference Count**      | Không có reference count.                                                                     | Có reference count, quản lý số lượng `shared_ptr` trỏ đến đối tượng.                  | Không làm tăng reference count, chỉ kiểm tra đối tượng được quản lý có còn tồn tại hay không.             |
| **Chuyển quyền sở hữu**  | Hỗ trợ chuyển quyền sở hữu bằng cách sử dụng `move`.                                      | Không hỗ trợ chuyển quyền sở hữu.                                                           | Không áp dụng (chỉ theo dõi đối tượng)                                                                |                             |
| **Khi nào giải phóng?**  | Đối tượng được giải phóng khi `unique_ptr` bị hủy hoặc gọi `reset()`.                     | Đối tượng được giải phóng khi reference count giảm xuống 0 (không còn `shared_ptr`).  | Đối tượng không bị ảnh hưởng bởi `weak_ptr`, chỉ phụ thuộc vào `shared_ptr`.                    |
| **Chuyển đổi sang raw pointer** | Có thể dùng `.get()` để lấy con trỏ thô.                                              | Có thể dùng `.get()` để lấy con trỏ thô.                                                   | Sử dụng `.lock()` để chuyển sang `shared_ptr` hoặc kiểm tra bằng `.expired()`.                        |
| **Khi nào sử dụng?**     | Khi chỉ cần một smart pointer quản lý đối tượng (quyền sở hữu duy nhất).                       | Khi nhiều thành phần cần chia sẻ quyền sở hữu một đối tượng.                                | Khi cần phá vỡ vòng tham chiếu hoặc kiểm tra đối tượng mà không ảnh hưởng đến vòng đời của nó.            |

