#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* arr, int l, int r, int x)
{
    if(l <= r)
    {
        int mid = l + (r - l) / 2;

        if(arr[mid] == x) return mid;

        if(arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        return binarySearch(arr, mid+1, r ,x);
    }

    return -1;
}


int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    int pos = binarySearch(arr,0,9,8);

    printf("%d %d",pos, arr[pos]);

    return 0;
}