#include <iostream>
#include <memory>

using namespace std;
 
class SpeedSensor
{
    private:
        int data;
    
    public:
        SpeedSensor(int value) : data(value){
            cout << "Contructor called, data = " << data << endl;
        }

        ~SpeedSensor(){
            cout << "Destructor called\n";
        }

        void ReadData(){
            cout << "Reading speed data ...\n";
        }

        void setData(int value){
            data = value;
        }

        void display(){
            cout << "Data " << data << endl;
        }
};

int main(){

    /****************************************************
     * make_unique cho phép khởi tạo đối tượng cho uptr.
     * trả về đối tượng được cấp phát động (lưu tại heap)
     * đối tượng được unique_ptr quản lý
     *************************************************** */
    unique_ptr<SpeedSensor> uptr = make_unique<SpeedSensor>(10);
    /**
     * object SpeedSensor: 0x01
     * ptr: 0x01
     * */
    uptr->setData(50);
    uptr->ReadData();
    uptr->display();
    (*uptr).display();

    /**********************************************
     * release() tách quyền sở hữu
     * đối tượng của uptr gán bằng Null
     * return về con trỏ thôi
     *********************************************** */
    cout <<"Release\n";
    SpeedSensor *rawPtr = uptr.release();
    rawPtr->display();
    delete rawPtr;
    
    /*************************************************
     * get() trả về con trỏ thô nhưng còn vẫn quyền sở hữu
     * return về con trỏ thôi
     ************************************************* */
    cout <<"Get\n";
    SpeedSensor *rawPtr = uptr.get();
    rawPtr->setData(100);
    rawPtr->display();
    delete rawPtr;

    /*************************************************
     * reset() thu hồi đối tượng và có thể quản lý
     *         đối tượng mới
     ************************************************* */
    cout <<"Reset\n";
    uptr.reset(new SpeedSensor(20));
    uptr->display();

    /*************************************************
     * move() chuyển quyền sở hữu
     ************************************************* */
    unique_ptr<SpeedSensor> uptr2 = move(uptr);\
    //uptr->display();
    uptr2->display();


    return 0;
}