#include <iostream>
#include <memory>

using namespace std;

/***************************************************************
 * weak_ptr: được sử dụng để theo dõi 1 đối tương đang được quản lý
 *          bởi shared_ptr.
 * Sẽ không làm tăng bộ đếm tham chiếu của shared_ptr, không truy cập
 * trực tiếp đến đối tượng mà nó theo dõi.
 *************************************************************** */

int main(){

    shared_ptr<int> sptr1 = make_shared<int>(20);
    shared_ptr<int> sptr2 = sptr1;

    //Tạo 1 weak pointer trỏ tới đối tượng mà shared pointer đang quản lý
    weak_ptr<int> ptr3 = sptr1;
    
    cout << "Count" << sptr1.use_count() <<endl;

    /****************************************************
     * lock(): chuyển weak_ptr sang shared_ptr tại 1 thời điểm
     *          và sau khi kết thúc lệnh lại chuyển về weak_ptr
     * Dùng để đọc giá trị hiện tại 
     *************************************************** */
    cout << "ptr3 " <<*(ptr3.lock()) <<endl;
    cout << "Count " << sptr1.use_count() <<endl;

    sptr1.reset(); // giải phóng quyền sở hữu của sptr1 đối với đối tượng
    sptr2.reset(); // giải phóng quyền sở hữu của sptr1 đối với đối tượng
    /************************************************************
     * expired() : kiểu boolean dùng để kiểm tra xem đối tượng hiện tại 
     *              có còn quản lý bởi shared_ptr không.
     * return True nếu không có bất kì 1 shared_ptr nào quản lý đối tượng
     * return False nếu vẫn còn có shared_ptr quản lý đối tượng
     *********************************************************** */
    cout << "check " << ptr3.expired() <<endl;
 }