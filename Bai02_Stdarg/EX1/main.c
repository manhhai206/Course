#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__,'\n')

int sum(int count,...){

    va_list args;
    va_start(args,count); //7

    int sum = count; //sum = 7;
    /* Dùng để kiếm tra */
    int value;
    /* Duyệt đến khi nào đến ký tự \n thì ngừng */
    while ((value = va_arg(args,int)) != '\n')
    {
       sum += value;
    }

    va_end(args);
    return sum;

}

int main()
{
    printf("tong = %d\n",tong(1,2,3));
    return 0;
}