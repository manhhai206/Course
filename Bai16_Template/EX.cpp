#include <iostream>
using namespace std;

    template<typename T>
    void f(T param){
        cout <<param<<endl;
    }

main(){
    int x = 27;            // x is an int
    const int cx = x;      // cx is a const int
    const int& rx = x;     // rx is a const int reference

    f(x);   // Argument is x, type deduced: T = int, param's type = int
    f(cx);  // Argument is cx, type deduced: T = int, param's type = int
    f(rx);  // Argument is rx, type deduced: T = int, param's type = int


}