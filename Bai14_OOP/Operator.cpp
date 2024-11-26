#include <iostream>
#include <stdbool.h>

using namespace std;

class Phanso
{
    private: 
        int num;
        int den;
    
    public:
        Phanso(int num = 0,int den =1){
            this->num = num;
            this->den = den;
        }

        Phanso operator + (Phanso &other)
        {
            Phanso ketqua;
            ketqua.num = this->num * other.den + this->den * other.num;
            ketqua.den = this->den * other.den;
            return ketqua;
        } 

        Phanso operator * (Phanso &other)
        {
            Phanso ketqua;
            ketqua.num = this->num * other.num;
            ketqua.den = this->den * other.den;
            return ketqua;
        }

        bool operator == (Phanso &other){
            return (this->num == other.num && this->den == other.den);
        }

        void display()
        {
            cout << "Tu so: " << num <<"   Mau so: "<<den<<endl;

        }
};

int main(){

    Phanso p1(1,2);
    Phanso p2(1,2);
    Phanso p4(1,6);
    Phanso p3 = p1+p2+p4;

    p1.display();
    p2.display();
    p3.display();

    if(p1 == p2){
        cout <<"p1 = p2"<<endl;
    }else{
        cout << "p1 != p2"<<endl;
    }
}