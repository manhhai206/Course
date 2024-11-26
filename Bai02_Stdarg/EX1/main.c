#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__,'\n')

int sum(int count,...){

    va_list args;
    va_start(args,count);

    int sum = count;
    int value;

    while ((value = va_arg(args,int)) != '\n')
    {
       sum += value;
    }

    va_end(args);
    return sum;

}

int main()
{
    printf("tong = %d\n",tong(1,2,3,0,5));
    return 0;
}