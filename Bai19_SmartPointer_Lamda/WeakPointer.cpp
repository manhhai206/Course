#include <iostream>
#include <memory>

using namespace std;

class HinhChuNhat {
private:
    int ChieuDai;
    int ChieuRong;

public:
    HinhChuNhat(int dai, int rong){
        ChieuDai = dai;
        ChieuRong = rong;
        cout << "Constructor called. "  << endl;
    }

    void tinhDienTich() {
        cout << "Dien tich: " << ChieuDai * ChieuRong << endl;
    }

    ~HinhChuNhat() {
        cout << "Destructor called " << endl;
    }


};

int main() {

    shared_ptr <HinhChuNhat> ptr1 (new HinhChuNhat(40,10));
    shared_ptr <HinhChuNhat> ptr3(ptr1);
    weak_ptr <HinhChuNhat> ptr2;
    ptr2 = ptr1;
   
    ptr1.reset();
    ptr3.reset();
 
    if (auto ptr_lock = ptr2.lock())
    {
        ptr_lock->tinhDienTich();
    }
    else
    {
        cout << "Object has been deallocated" << endl;
    }
   

    cout << "Count: " <<ptr2.use_count() << endl;
    

    return 0;
}
