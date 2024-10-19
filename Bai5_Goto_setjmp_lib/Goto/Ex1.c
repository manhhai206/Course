#include <stdio.h>

int main()
{
    // int option;

    // menu1: 
    // do
    // {
    //     printf("Menu - 1\n");
    //     printf("1: Tao ra menu thu hai\n");
    //     printf("2: .....\n");
    //     printf("3:............\n");
    //     scanf("%d",&option);
    // }while (option!=1);

    // switch (option)
    // {
    // case 1:
    //     printf("Menu - 2 \n");
    //     printf("0: Quay lai menu 1\n");
    //     printf("1: Ket thuc chuong trinh\n");
    //     printf("2: ...\n");
    //     scanf("%d",&option);

    //     switch (option)
    //     {
    //     case 0:
    //         goto menu1;
    //         break;
        
    //     default:
    //         break;
    //     }
    //     break;
    
    // default:
    //     break;
    // }

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
}