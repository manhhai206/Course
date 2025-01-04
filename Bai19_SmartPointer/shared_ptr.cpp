#include <iostream>
#include <memory>

using namespace std;

/*********************************************************
 * shared pointer(shared_ptr) là một smart pointer hỗ trợ chia
 *                          sẽ quyền sở hữu với 1 đối tượng.
 *
 * Nhiều shared_ptr có thể cùng sở hữu 1 đối tượng.
 * Đối tượng chỉ được giải phóng khi không có shared_ptr nào sở hữu nó.
 ******************************************************** */

int main(){

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

    int *rawPtr = sptr1.get();
    cout << "rawPtr: " << *rawPtr << endl;
    /**************************************************
     *  trả về con trỏ thô (int*) trỏ tới vùng mà ptr1 đang quản lý
     ************************************************* */

    *sptr1 = 50;
    cout << "sptr1 " <<*sptr1 <<endl;
    *rawPtr = 100;
    cout << "sptr1 " <<*sptr1 <<endl;


    shared_ptr<int> a = make_shared<int>(50);
    shared_ptr<int> b = make_shared<int>(60);
    a.swap(b);
    cout << "a =  " << *a <<endl;
    cout << "b =  " << *b <<endl;

    a = move(b);
    cout << "a =  " << *a <<endl;

    sptr1.reset(new int(10));
    cout << "sptr1 = " << *sptr1 <<endl;
    cout << "sptr2 = " << *sptr2 <<endl;
    

    return 0;

}