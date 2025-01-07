
# Process (Tiến trình)

- 1 chương trình đang chạy trên hệ thống
- có địa chỉ bộ nhớ riêng
- có thể tương tác với phần cứng bên dưới (bàn phím, chuột...)
- 1 process có thể chứa nhiều thread(luồng)
- các process có thể giao tiếp được với nhau thông qua IPC
    + IPC signal
    + IPC semaphone
    + IPC pipe
    ....

# Thread( Luồng)
- Là 1 đơn vị thuộc process
- các luồng trong cùng process thì chia sẽ cugf bộ nhớ

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
- khi 1 method join(), luồng chính phải chờ cho đến khi luồng được gọi kết thúc rồi mới thực thi

### detach()
- Khi 1 luồng gọi method detach(), nó sẽ tách khỏi luồng chính và chạy độc lập.
- nếu 1 luồng chính kết thúc trước khi luồng phụ hoàn thành, chương trình sẽ dừng lại và các luồng phụ bị hủy bỏ.
- 1 luồng không thể gọi detach() sau khi nó kết thúc (gọi join()) và luồng chính kết thúc trước luồng gọi detach()
- Khi nào nên  sử dụng join, detach:
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

### lock_guard

- std::lock_guard quản lý công việc và mở khóa, giúp lỗi lập trình như quên unlock 
- Tự động khóa mutex khi đối tượng được tạo
- Tự động mở khóa khi đối tượng bị hủy

### unique_lock()

- std:: unique_lock linh hoạt hơn std:lock_guard cung cấp 2 cơ chế: khóa/mở khóa tự động hoặc thủ công nhiều lần trong phạm vi hoặc kiểm soát thời gian khóa.

### Atomic

- std::atomic là 1 struct template
- std::atomic được thiết kế để thực hiện các thao tác trên các biến toàn cục(chứa dữ liệu) mà cac thao tác này không bị gián đoạn bởi các luồng khác.

### Condition Variabble



## Luồng bất đồng bộ