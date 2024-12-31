
# The compilation Process of a C program

Quá trình biên dịch trong ngôn ngữ C liên quan đến quá trình chuyển đổi source code được viết ở ngôn ngữ bậc cao sang ngôn ngữ máy, đảm bảo rằng máy tính có thể hiểu và thực thi

C là ngôn ngữ biên dịch, và chương trình được viết bởi ngôn ngữ C thì phải trải qua quá trình chuyển đổi từ source code sang chương trình thực thi.

Quá trình đó được chia thành 4 giai đoạn:
- **Tiền xử lý (Pre-processing)** 	
- **Biên dịch (Compilation)**
- **Dịch hợp ngữ (Assembly)**
- **Liên kết (Linking)**
 
     ![](https://tapit.vn/wp-content/uploads/2017/07/GCC_CompilationProcess.png)

## Giai đoạn tiền xử lý - Preprocessor
- Thì giai đoạn này sẽ chuyển toàn bộ mã nguồn .c và .h thành .i.
- Xóa bỏ tất cả các chú thích hay comment.
- Chỉ thị tiền xử lý (bắt đầu bằng #) cũng được xử lý.
- Còn lại thì giữ nguyên.

## Giai đoạn biên dịch -  Compiler
- Thì chuyển thì file.i sang file.s
- Phân tích cú pháp (syntax) của mã nguồn high-level-language.
- Chuyển chúng sang dạng mã Assembly là một ngôn ngữ bậc thấp (hợp ngữ) gần với tập lệnh của bộ vi xử lý.

## Giai đoạn dịch hợp ngữ - Assembler
- File.s sang file.o
- Dich chương trình => Sang mã máy 0 và 1
- Một tệp mã máy (.obj) sinh ra trong hệ thống sau đó giúp máy tính hiểu được.

## Giai đoạn liên kết - Linker
- Tổng hợp nhiều file.o khác nhau liên kết lại với nhau.
- Cuối cùng sẽ tạo thành 1 file.exe

