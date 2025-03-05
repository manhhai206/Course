#include <stdio.h>
#include <stdlib.h>

void merge(int *arr,int left, int middle, int right)
{
    int leng_left = middle - left + 1;
    int leng_right =  right - middle;

    int a_right[leng_right];
    int a_left[leng_left];

    for(int i = 0; i< leng_left;i++)
    {
        a_left[i] = arr[left + i];
    }

    for(int i = 0; i< leng_right;i++)
    {
        a_right[i] = arr[middle + 1 + i];
    }

    int i=0, j=0, k = left;

    while(i<leng_left && j <leng_right){
        if(a_left[i] < a_right[j]){
            arr[k] = a_left[i];
            i++;
        } else {
            arr[k] = a_right[j];
            j++;
        }
        k++;
    }
    
    while(i<leng_left){
        arr[k] =  a_left[i];
        i++;
        k++;
    }

    while(j<leng_right){
        arr[k] =  a_right[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left,int right)
{
    if(left <right)
    {
        int mid = left+(right-left) /2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);

        //Tron 2 mang lai
        merge(arr,left,mid,right);

    }
}

// Hàm in mảng
void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);

    return 0;
}
