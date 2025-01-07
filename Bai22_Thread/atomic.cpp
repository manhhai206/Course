#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std; 

atomic<int> sharedCounter(0);
mutex mtx;

void incrementTask(int iter)
{
    for(int i=0; i < iter; i++)
    {
        lock_guard<mutex> glock(mtx);
        cout << ++sharedCounter <<endl;

    }
}

int main(){

    thread t1(incrementTask, 20000);
    thread t2(incrementTask, 10000);

    t1.join();
    t2.join();

    cout << "Final result:  " << sharedCounter << endl;

    return 0;
}