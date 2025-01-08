 
# Goto - setjmp.h

## Goto
- Định nghĩa goto là từ khóa cho phép chương trình nhảy đến 1 lable.
- Lable phải đặt nội bộ ở trong hàm.Từ khóa goto cung cấp khả năng kiếm soát luồng chạy của chương trình.
- Ví dụ:
    ```c
    int main() {
        int i = 0;

        // Đặt nhãn
        start:
            if (i >= 5) {
                goto end;  // Chuyển control đến nhãn "end"
            }

            printf("%d ", i);
            i++;

            goto start;  // Chuyển control đến nhãn "start"

        // Nhãn "end"
        end:
            printf("\n");

        return 0;
    }
    ```
    - Khi i chưa thỏa điều kiện `>=5` thì bỏ qua if đầu tiên thực thi các lệnh bên dưới.
    - Khi thỏa điều kiện thực hiện lệnh `goto end` thì lập tức nhảy đến lable `end`.

- Goto thường được sử dụng trong các vấn đề như thoát khỏi vòng lặp
    ```c
        int i,j;
        while(1){
            for(i=0;i<5;i++){
                for(j=0;j<5;j++){
                    if(i==2 && j==3)
                    {
                        printf("Thoat chuong trinh\n");
                        goto thoat;
                    }
                }
            }
        }
        thoat:
        return 0;
    ```
    - Nếu không xài goto thì phải xài lệnh break 3 lần trong 3 vòng lặp đươc tạo ra.Nên đó chúng ta sử dụng lệnh để nhảy ra khỏi các vòng lặp.

## setjmp.h
setjmp.h là thư viện cho phép chúng ta nhảy từ hàm này qua hàm khác bằng cách sử dụng 2 hàm chính là :setjmp và longjmp.
- Là một biến kiểu jmp_buf dùng để lưu trữ trạng thái của chương trình tại thời điểm gọi hàm setjmp.
- Hàm longjmp được gọi để nhảy ngược lại trạng thái đã được lưu bởi setjmp.
- Ví dụ 1:
    ```c
    #include "stdio.h"
    #include "setjmp.h"

    jmp_buf buf;

    int main(){
        int exception = setjmp(buf);
        
        if(exception == 0 )
        {
            printf("exception = %d\n",exception);
        }
        else if(exception == 3)
        {
            printf("exception = %d\n",exception);
        }

        longjmp(buf,3);
        return 0;
    }
    ```
- Ví dụ 2:

    ```c
    #include "stdio.h"
    #include "setjmp.h"

    jmp_buf buf;

    double divide(int a,int b)
    {
        if( a == 0 && b == 0){
            longjmp(buf,1);   
        }
        else if(a != 0  && b == 0){
            longjmp(buf,2);
        }
        return (double)(a/b);
    }

    int main(){
        int exception;

        if((exception = setjmp(buf)) == 0 )
        {
            double kq = divide(8,0);
            printf("exception = %f\n",kq);
        }
        else if(exception == 1)
        {
            printf("exception khong ton tai\n");
        }
        else if(exception == 2)
        {
            printf("Chia cho 0\n");
        }

        return 0;
    }
    ```

- Ví dụ 3:

    ```c
    #include "stdio.h"
    #include "setjmp.h"

    jmp_buf buf;
    int exception;

    #define TRY if((exception = setjmp(buf)) == 0 )
    #define CATCH(x) else if(exception == x)
    #define THROW(x) longjmp(buf,x)

    double divide(int a,int b)
    {
        if( a == 0 && b == 0){
            THROW(1);   
        }
        else if(a != 0  && b == 0){
            THROW(2);
        }
        return (double)(a/b);
    }

    int main(){

        TRY
        {
            double kq = divide(5,0);
            printf("Ket qua = %f\n",kq);
        }
        CATCH(1)
        {
            printf(" khong ton tai\n");
        }
        CATCH(2)
        {
            printf("Chia cho 0\n");
        }

        return 0;
    }
    ```

