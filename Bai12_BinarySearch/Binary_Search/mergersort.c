#include <stdio.h>
#include <stdlib.h>

void merger(int *arr, int left, int mid, int righ)
{

    int leng_left = mid - left + 1; //Độ dài dãy bên trái
    int leng_righ = righ - mid; //Độ dài dãy bên phải

    // Tạo mảng tạm thời
    int a_left[leng_left];
    int a_righ[leng_righ];

    //Copy từng giá trị vào mảng a_left
    for(int i = 0; i < leng_left; i++)
        a_left[i] = arr[left + i];
    //Copy từng giá trị vào mảng a_left
    for(int i = 0; i < leng_righ; i++)
        a_righ[i] = arr[mid + 1 + i]; 

    // Gộp hai mảng con theo quy tắc phần tử nhỏ hơn đưa vào trước
    int i = 0, j = 0, k = left;
    while (i < leng_left && j < leng_righ) 
    {
        if (a_left[i] <= a_righ[j]) {
            arr[k] = a_left[i];
            i++;
        } else {
            arr[k] = a_righ[j];
            j++;
        }
        k++;
    }

    // Copy các phần tử còn lại của mảng bên trái (nếu có)
    while (i < leng_left) {
        arr[k] = a_left[i];
        i++;
        k++;
    }

    // Copy các phần tử còn lại của mảng bên phải (nếu có)
    while (j < leng_righ) {
        arr[k] = a_righ[j];
        j++;
        k++;
    }
}

void mergerSort(int *arr, int left, int righ)
{
    if (left < righ)
    {
        int mid = left + (righ - left) / 2;
        // Gọi đệ quy sắp xếp từng phần bên trái và bên phải
        mergerSort(arr, left, mid);
        mergerSort(arr, mid + 1, righ);
        // Gộp hai phần đã sắp xếp lại với nhau
        merger(arr, left, mid, righ);
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

    mergerSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);

    return 0;
}
