#include <iostream>
#include "lcd1.hpp"
#include "lcd2.hpp"

using namespace std;

namespace std{
    struct 
    {
        int x;
        int y;
    } Point;
    
    void Display(){
        cout << "x = "<<Point.x <<endl;
        cout << "y = "<<Point.y <<endl;
    }
}

namespace A{
    char *name = (char*)"Trung 20";

    void display(){
        cout << "Name: " << name << endl;
    }

    namespace C {
        char *name2 = (char*)"Hai 22";
    }
}

namespace B{
    char *name = (char*)"Tuan 21";

    void display(){
        cout << "Name: " << name << endl;
    }
}

using namespace A;

int main(int argc, char const *argv[])
{
    cout << "Name: " << C::name2 << endl;
    display();
    cout <<endl;

    cout << "Name: " << B::name << endl;
    B::display();
    cout <<endl;

    std::Point.x = 5;
    std::Point.y = 10;
    std::Display();
    cout <<endl;

    LCD::lcd;
    LCD::temp;
    LCD::text;
    
    return 0;
}
