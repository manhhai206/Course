# Process (Tiến trình)

- 1 chương trình đang chạy trên hệ thống( ứng dụng đang chạy: ví dụ: App đang sử dụng được tính là process).
- có địa chỉ bộ nhớ riêng.
- có thể tương tác với phần cứng bên dưới (bàn phím, chuột...)
- 1 process có thể chứa nhiều thread(luồng)
- các process có thể giao tiếp được với nhau thông qua IPC
    + IPC signal
    + IPC semaphone
    + IPC pipe
    ....

# Thread( Luồng)
- Là 1 đơn vị thuộc process
- các luồng trong cùng process thì chia sẽ cùng bộ nhớ

## Tạo và khởi chạy luồng
- Cú pháp:
    + std::thread thread_id(function,args...)
    + std::thread: class dùng để tạo, khởi chạy các luồng
    + function : hàm hoặc lamda mà luồng sẽ thực thi
    + args...: dánh sách tham số truyền vào function
- mỗi luồng chỉ thực thi 1 hàm( lamda) duy nhất
- luồng chính(main) kết thúc thì các luồng phụ cũng kết thúc theo

## Quản lý luồng

### join()
- khi 1 method join(), luồng chính phải chờ cho đến khi luồng được gọi kết thúc rồi mới thực thi.

```c
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

    //Sau khi luồng phụ thực thi hết rồi mới chạy luồng chính
    for(int i = 0 ;i<5;i++){
        cout << "This is main\n";
        delay(1);
    }

    //Luồng được gọi join sẽ được thực thi trước
    t1.join();
    t2.join();
    
    return 0;
}
```


### detach()
- Khi 1 luồng gọi method detach(), nó sẽ tách khỏi luồng chính và chạy độc lập.
- nếu 1 luồng chính kết thúc trước khi luồng phụ hoàn thành, chương trình sẽ dừng lại và các luồng phụ bị hủy bỏ.
- 1 luồng không thể gọi detach() sau khi nó kết thúc (gọi join()) và luồng chính kết thúc trước luồng gọi detach()
- Khi nào nên sử dụng join, detach:
    + Sử dụng join() khi luồng thực hiện 1 công việc quan trọng mà kết quả nó ảnh hưởng tới luồng chính
    + Sử dụng detach khi công việc của các luồng phụ không ảnh hưởng đên luồng chính

### joinable()
- Kiểm tra xem 1 luồng đã kết thúc chưa hoặc đã gọi method join chưa.

- Nếu luồng chưa kết thúc hoặc chưa gọi join thì trả về "true", thì con lại là trả về "false"

## Đồng bộ luồng

### Mutex

- std::mutex được sử dụng đẻ khóa tài nguyên chung, đảm bảo rằng chỉ có 1 luồng duy nhất có thể truy cập tài nguyên tại 1 thời điểm
- tài nguyên ở đây có thể là các ngoại vi( bàn phím, camera, màn hình ...)
- Mutex có 2 trạng thái chính:
    + Lock:
        + Khi có 1 luồng giữ (lock) mutex,trạng thái mutex là locked. Điều này có nghĩa là hiện mutex đang được sở hữu 1 luồng và không luồng nào truy cập tài nguyên được bảo vệ bởi mutex cho đến kgi luồng giữ mutex được unlock.
        + Nếu 1 luồng khác cố gắng lock mutex khi nó đang ở trạng thái locked, luồng đó sẽ bị block cho đến khi được unlock.
    + Unlock: 
        + Khi mà mutex không còn bất kì luồng nào giữ (lock), trạng thái cuuar mutex là unlocked.
        + Trong trạng thái này, bất kì luồng nào cũng có thể lock mutex và trở thành luồng sở hữu nó.
        + Sau  khi 1 luồng sở hữu mutex, trạng thái chuyển thành locked và các luồng phải chờ.
```c
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
        mtx.lock();
        cout << ++sharedCounter << endl;
        mtx.unlock();
    }
}

int main(){
    thread t1(incrementTask,200);
    thread t2(incrementTask,100);

    t1.join();
    t2.join();

    cout << "Final Result:  " << sharedCounter << endl;
    return 0;
}
```
### lock_guard

- std::lock_guard quản lý công việc và mở khóa, giúp lỗi lập trình như quên unlock 
- Tự động khóa mutex khi đối tượng được tạo
- Tự động mở khóa khi đối tượng bị hủy
```c
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
        lock_guard<mutex> glock(mtx);
        cout << ++sharedCounter << endl;
    }
}

int main(){
    thread t1(incrementTask,200);
    thread t2(incrementTask,100);

    t1.join();
    t2.join();

    cout << "Final Result:  " << sharedCounter << endl;
    return 0;
}
```
### unique_lock()

- std:: unique_lock linh hoạt hơn std:lock_guard cung cấp 2 cơ chế: khóa/mở khóa tự động hoặc thủ công nhiều lần trong phạm vi hoặc kiểm soát thời gian khóa.
```c
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
```
### Atomic

- std::atomic là 1 struct template

- std::atomic được thiết kế để thực hiện các thao tác trên các biến toàn cục(chứa dữ liệu) mà cac thao tác này không bị gián đoạn bởi các luồng khác.
```c
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> sharedCounter(0);

void incrementTask(int iter)
{
    for(int i=0;i<iter;i++)
    {
        cout << ++sharedCounter << endl;
    }
}

int main(){
    thread t1(incrementTask,2000);
    thread t2(incrementTask,1000);

    t1.join();
    t2.join();

    cout << "Final Result:  " << sharedCounter << endl;
    return 0;
}
```
### Condition Variabble
- std::condition_variable là 1 cơ chế giao tiếp và đồng bộ giữa 2 hoặc nhiều luồng, cho phép luồng chờ cho đến khi 1 điều kiện cụ thể  được đáp ứng, và 1 luồng khác có thể thông báo khi điều kiện được thỏa mãn.

- wait(): cho phép 1 luồng chờ đến khi có 1 điều kiện cụ thể được thỏa mãn.
- notify_one(): gửi thông báo tới 1 luồng đang chờ.
- notify_all(): gửi thông báo cho nhiều luồng đang chờ.

