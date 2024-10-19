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
