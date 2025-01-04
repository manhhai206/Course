#include <iostream>

using namespace std;

class Test
{
    public:
        int value;

        Test(int val = 10) : value(val) {}

        void display() const
        {
            cout << "Test value: " << value << endl;
        }
};

/**
 * @brief   Lớp UniquePointer quản lý một con trỏ duy nhất và tự động giải phóng vùng nhớ.
 * @tparam  T   Kiểu dữ liệu của đối tượng được quản lý.
 */
template <typename T>
class UniquePointer
{
    private:
        T *ptr; /**< Con trỏ thô đến đối tượng được quản lý. */
       

    public:
        /**
         * @brief   Constructor khởi tạo con trỏ UniquePointer.
         * @param   p   Con trỏ thô đến đối tượng. Giá trị mặc định là nullptr.
         */
        UniquePointer(T *p = nullptr): ptr(p){}


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
        /*
         * &uptr = 0xf4 (stack)
         */


        /**
         * @brief   Xóa bỏ khả năng sao chép đối tượng UniquePointer.
         */
        UniquePointer(const UniquePointer&) = delete;


        /**
         * @brief   Xóa bỏ khả năng gán bằng copy đối tượng UniquePointer.
         * @return  Trả về tham chiếu đến đối tượng UniquePointer hiện tại.
         */
        UniquePointer& operator = (const UniquePointer&) = delete;


        /**
         * @brief   Toán tử dereference để truy cập đối tượng được quản lý.
         * @return  Tham chiếu đến đối tượng được quản lý.
         */
        T& operator * () const
        {
            return *ptr;    // *0x01 = 10
        }


        /**
         * @brief   Toán tử để truy cập các thành phần của đối tượng.
         * @return  Con trỏ đến đối tượng được quản lý.
         */
        T* operator -> () const
        {
            return ptr;
        }


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

       
        /**
         * @brief   Giải phóng đối tượng hiện tại và quản lý đối tượng mới.
         * @param   p   Con trỏ thô đến đối tượng mới. Mặc định là nullptr.
         */
        void reset(T* p = nullptr)
        {
            if (ptr)
            {
                delete ptr;
            }
            ptr = p;
        }


        /**
         * @brief   Move constructor chuyển nhượng quyền sở hữu con trỏ.
         * @param   other   Đối tượng 'UniquePointer' cần chuyển nhượng quyền sở hữu.
         */
        UniquePointer(UniquePointer &&other) : ptr(other.ptr)
        {
            other.ptr = nullptr;
        }


        /**
         * @brief   Toán tử gán chuyển nhượng quyền sở hữu.
         * @param   other   Đối tượng 'UniquePointer' cần chuyển nhượng quyền sở hữu.
         */
        UniquePointer& operator = (UniquePointer &&other)
        {
            if (this != &other)
            {
                // giải phóng tài nguyên hiện tại
                if (ptr)
                {
                    delete ptr;
                }

                // chuyển quyền sở hữu
                ptr = other.ptr;
                other.ptr = nullptr;
            }

            return *this;
        }
};

int main(int argc, char const *argv[])
{
    // UniquePointer<Test> uptr1 = new Test(10);
    // UniquePointer<Test> uptr1(new Test(10));
    // uptr1->display();


    UniquePointer<int> uptr(new int(10));   // 0x01: 10

    // UniquePointer<int> uptr2 = move(uptr);

    // uptr2 = uptr;

    /* truy cập và in giá trị */
    cout << "value: " << *uptr << endl; // *ptr


    /* lấy giá trị con trỏ thô */
    int* rawPtr = uptr.get(); // 0x01
    cout << "giá trị con trỏ thô: " << *rawPtr << endl;
    delete rawPtr;


    /* chuyển quyền sở hữu đối tượng kiểu int cho con trỏ thô mới */
    // int* rawPtr1 = uptr.release();  // 0x01
    // delete rawPtr1;


    /* thu hồi đối tượng cũ và bắt đầu quản lý đối tượng mới */
    uptr.reset(new int(20));    // 0xa1: 20
    cout << "new value: " << *uptr << endl;


    // /* thu hồi vùng nhớ chứa 20, uptr không quản lý vùng nhớ nào */
    // uptr.reset();

    /* sử dụng move semantic để chuyển quyền sở hữu */
    UniquePointer<int> uptr2 = move(uptr);
    if (uptr.get() == NULL){
        cout << "uptr đã chuyển quyền sở hữu\n";
    } else {
        cout << "uptr vẫn còn quyền sở hữu\n";
    }

    cout << "uptr2 đang quản lý đối tượng kiểu int có giá trị là: " << *uptr2 << endl;

    /* sử dụng move assignment operator để chuyển quyền sở hữu */
    UniquePointer<int> uptr3;
    uptr3 = move(uptr2);
    cout << "uptr3 đang quản lý đối tượng kiểu int có giá trị là: " << *uptr3 << endl;

    /* khi kết thúc chương trình, bộ nhớ sẽ được tự động giải phóng */
    return 0;
}

