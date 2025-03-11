#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int value) : count(value) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return count > 0; }); // Chờ nếu count = 0
        --count;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

Semaphore sem(2); // Tạo semaphore cho tối đa 2 thread

void limitedResource(int id) {
    sem.acquire();
    std::cout << "Thread " << id << " dang truy cap tai nguyen\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Mô phỏng xử lý
    std::cout << "Thread " << id << " roi khoi tai nguyen\n";
    sem.release();
}

int main() {
    std::thread t1(limitedResource, 1);
    std::thread t2(limitedResource, 2);
    std::thread t3(limitedResource, 3);
    std::thread t4(limitedResource, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
