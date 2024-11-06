#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__,'\n')

int sum(int count,...){

    va_list args;
    va_list check;

    va_start(args,count);
    va_copy(check,args);

    int result =count;
    int value;
    while((value = va_arg(check,int)) != '\n'){
        result += va_arg(args,int);
    }
    va_end(args);
    return result;
}

int main(){
    int kq  = sum(4,1,2,0,3,4,20,16,'\n');
    printf("%d",kq);
}