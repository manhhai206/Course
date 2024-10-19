 
# Goto - setjmp.h

## Goto

Định nghĩa goto là từ khóa cho phép chương trình nhảy đến 1 lable , và lable phải đặt nội bộ ở trong hàm.Từ khóa goto cung cấp khả năng kiếm soát luồng chạy của chương trình.
```c
#include <stdio.h>

int main()
{
    int option;
    menu1: 
    do
    {
        printf("Menu - 1\n");
        printf("1: Tao ra menu thu hai\n");
        printf("2: .....\n");
        printf("3:............\n");
        scanf("%d",&option);
    }while (option!=1);

    switch (option)
    {
    case 1:
        printf("Menu - 2 \n");
        printf("0: Quay lai menu 1\n");
        printf("1: Ket thuc chuong trinh\n");
        printf("2: ...\n");
        scanf("%d",&option);
        switch (option)
        {
        case 0:
            goto menu1;
            break;
        
        default:
            break;
        }
        break;
    
    default:
        break;
    }  
}
```

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
Nếu không xài goto thì phải xài lệnh break 3 lần trong 3 vòng lặp đươc tạo ra.Nên đó chúng ta sử dụng lệnh để nhảy ra khỏi các vòng lặp.
## setjmp.h

setjmp.h là thư viện cho phép chúng ta nhảy từ hàm này qua hàm khác bằng cách sử dụng 2 hàm chính là :setjmp và longjmp.

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

