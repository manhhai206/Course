#include <stdio.h>
#include <stdarg.h>

/**************************************************
 * Hàm này nhận một số nguyên count là số lượng các tham số, 
 * và sau đó là một dãy các tham số kiểu nguyên (int)
 * không xác định.
 ************************************************* */
int sum(int count,...)
{
    /* Khai báo một biến args để lưu trữ danh sách các tham số. */
    va_list args;
    /**********************************************************
     * Khởi tạo args để bắt đầu truy cập vào các tham số biến. 
     * Với tham số đầu tiên là count, cho biết số lượng tham số
     ********************************************************** */
    va_start(args,count); // 5

    int result = 0;
    for(int i=0;i<count;i++)
    {
       /* Dùng để lấy từng tham số (ở đây là kiểu int) từ danh sách tham số.
        * cout = 0      result = 1;
        * cout = 1      result += 2 
        * cout = 2      result += 3;
        */
        result+=va_arg(args,int);
    }
    /* Kết thúc */
    va_end(args);
    return result;
}

int main(){
    int kq = sum(5,1,2,3,4,5);
    printf("%d", kq);
}