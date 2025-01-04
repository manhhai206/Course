#include <iostream>
#include <string>

using namespace std;

class Car {
public:
    string Model;
    int Date;

public:
    Car(string m, int d) : Model(m), Date(d) {}

    virtual void Display(){
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl; 
    }
};

class Toyota : public Car {
private:
    string Engine;

public:
    Toyota(string m, int d, string e) : Car(m, d), Engine(e) {}

    void Display() override {
        cout << "Brand Toyota:\n";
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl;
        cout << "Engine: " << Engine << endl;
    }
};

class Honda : public Car {
private:    
    string Engine;

public:
    Honda(string m, int d, string e) : Car(m, d), Engine(e) {}

    void Display() override {
        cout << "Brand Honda:\n";
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl;
        cout << "Engine: " << Engine << endl;
    }
};

class Vinfast : public Car {
private:
    string Country;

public:
    Vinfast(string m, int d, string c) : Car(m, d), Country(c) {}


    void Display() override {
        cout << "Brand Vinfast:\n";
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl;
        cout << "Country: " << Country << endl;
    }
};

int main() {

    Car *myCar;

    Toyota toyotaCar("Camry", 2023, "Hybrid");
    /*************************************************
     * Một đối tượng gọi 1 method ra thì gọi method ở
     * class nào dựa vào đối tương trỏ đến chứ không
     * phải đối tượng nó tạo ra
     * 
     ***********************************************/
    myCar = &toyotaCar;

    myCar->Display();

    return 0;
}
