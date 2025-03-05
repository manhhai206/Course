#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

int sensor_data = 0;
bool check_data = false; // sửa int -> bool để đúng kiểu dữ liệu
mutex mtx;
condition_variable cv;

void sensor_read(void)
{
    while (1)
    {
        delay(2);
        unique_lock<mutex> lock(mtx);
        sensor_data = rand() % 100;
        check_data = true;
        cout << "Read data done!\n";
        lock.unlock();
        cv.notify_one();
    }
}

void process_data(void)
{
    while (1)
    {
        unique_lock<mutex> uniqueLock(mtx);
        cv.wait(uniqueLock, []()->bool { return check_data; }); // Chờ khi check_data == true

        cout << "Data: " << sensor_data << endl;

        check_data = false; // Reset trước khi unlock mutex
        uniqueLock.unlock();
    }
}

int main()
{
    thread task1(sensor_read);
    thread task2(process_data);

    task1.join();
    task2.join();

    return 0;
}
