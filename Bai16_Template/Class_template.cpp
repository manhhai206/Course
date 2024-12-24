#include <iostream>
#include <string>
using namespace std;

template<typename T1, typename T2>
class Sensor
{
    private:
        T1 value1;
        T2 value2;

    public:
        Sensor(T1 init1, T2 init2): value1(init1), value2(init2){}

        T1 getValue1(){
            return value1;
        }

        T2 getValue2(){
            return value2;
        }

        void display(){
            cout << "Sensor Value 1 :" << getValue1() << endl;
            cout << "Sensor Value 2 :" << getValue2() << endl; 
        }
};

template<typename T, int size>
class Array
{
    T arr[size];

    public:
        void set(int index, T value){
            if(index >= 0 && index < size) arr[index] = value;
        }

        T getElment(int index){
            return arr[index];
        }
};

template<typename T>
T sum(T value){
    return value;
}

template<typename T, typename...Args>
auto sum(T first,Args...args){
    return first + sum(args...);
}

int main(){
    
    Array<int,5> arr;
    arr.set(0,10);
    cout << arr.getElment(0)<<endl;

    Sensor tempSensor("ON",40);
    tempSensor.display();
    cout <<endl;
    Sensor stateSensor("ON",27.5);
    stateSensor.display();
    cout <<endl;

    cout <<sum(1,2,3,4,5)<<endl;
    return 0;
}