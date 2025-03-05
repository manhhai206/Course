#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int left, int right)
{
    int pivot = arr[right];
    int i = left - 1;

    for(int j = left;j<right;j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[j],&arr[i]);
        }
    }

    swap(&arr[i+1],&arr[right]);
    return i+1;
}

void quickSort(int *arr, int left, int right)
{
    if(left<right)
    {
        int pi = partition(arr,left,right);
        quickSort(arr,left,pi-1);
        quickSort(arr,pi+1,right);
    }
}


int main(){

    int arr[] = {1,3,2,5,4,6,9,7};
    int size =  sizeof(arr)/sizeof(arr[0]); 
    quickSort(arr,0,size-1);
    for(int i =0;i<size;i++){
        printf("%d\t",arr[i]);
    }
}