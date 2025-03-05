#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

atomic<int> sharedCounter(0);
mutex mtx;
void incrementTask(int iter)
{
    for(int i=0;i<iter;i++)
    {   
        unique_lock<mutex> unilock(mtx);
        cout << "HMI" <<endl;
        unilock.unlock();

        unilock.lock();
        cout << "Keyboard" <<endl;
        unilock.unlock();

        unilock.lock();
        cout << "Mouse "<<endl;
        unilock.unlock();
    }
}

int main(){
    thread t1(incrementTask,100);
    thread t2(incrementTask,100);
    thread t3(incrementTask,100);

    t1.join();
    t2.join();
    t3.join();

    cout << "Final Result:  " << sharedCounter << endl;
    return 0;
}