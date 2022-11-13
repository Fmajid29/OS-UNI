#include <stdio.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}


int main(){
    int arr[20] = { 1,2,3,4,5,6,7,8,69,43,85,2,-99,14,73,56,78,12,36,87 };
    int sorted[20];
    int sortedSize = 0;

    for (int i = 0; i< 20; i++){
        if (arr[i] == -99)
            break;
        else{
            sorted[i] = arr[i];
            sortedSize++;
        }
    }

    bubbleSort(sorted,sortedSize);

    printf("\nOriginal Sorted \n");
    for (int i = 0; i< sortedSize; i++){
        printf("%d          %d\n", arr[i],sorted[i]);
    }

    return 0;
}