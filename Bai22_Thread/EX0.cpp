#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void delay(uint32_t time)
{
    this_thread::sleep_for(chrono::seconds(time));
}

void task1(uint32_t time)
{
    int i = 0;
    for(int j = 0 ;j<8;j++)
    {
        cout << "task 1, i = " << i++ << endl;
        delay(time);
    }
}

void task2(uint32_t time, string str)
{
    int i = 0;
    for(int j = 0 ;j<8;j++)
    {
        cout << "task 2, i = " << i++ << endl;
        delay(time);
    }
}

int main() {

    thread t1(task1,1);    
    thread t2(task2,2,"Hello");

    t1.detach();
    t2.detach();

    for(int i = 0 ;i<5;i++){
        cout << "This is main\n";
        delay(1);
    }

    // t1.join();
    // t2.join();

    return 0;
}