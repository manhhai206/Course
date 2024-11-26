#include <iostream>

using namespace std;

class HinhChuNhat {

    public:
        double chieudai;
        double chieurong;
        static int var;

        static void display(){
            cout << "static method : " <<endl;
            var = 20;
        }
};

int HinhChuNhat::var;

int main(){
    HinhChuNhat hcn1;
    HinhChuNhat::display();
    cout <<"var = " <<HinhChuNhat::var <<endl;
}