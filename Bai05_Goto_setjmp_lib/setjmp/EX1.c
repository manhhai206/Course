#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;

/* Lưu trạng thái chương trình tại vị trí hiện tại. Trả về 0 khi được gọi lần đầu. */
#define TRY if((exception = setjmp(buf)) == 0 )

#define CATCH(x) else if(exception == x)

/* Quay lại vị trí gọi setjmp(env) và trả về giá trị x */
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
