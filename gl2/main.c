#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h> 

#define MAX 10

int arr[MAX]; 
int sum1, sum2; 

void* ascending_sort(void* arg) 
{ 
    int temp; 

    for (int i = 0; i < MAX; i++) { 
        for (int j = i + 1; j < MAX; j++) { 
            if (arr[i] > arr[j]) { 
                temp = arr[i]; 
                arr[i] = arr[j];
                arr[j] = temp; 
            } 
        } 
    } 

    if (arr[0] < arr[MAX - 1])
        sum1 = arr[0] + arr[MAX - 1];

    return 0; 
} 

void* descending_sort(void* arg) 
{ 
    int temp; 

    for (int i = 0; i < MAX; i++) { 
        for (int j = i + 1; j < MAX; j++) { 
            if (arr[i] < arr[j]) { 
                temp = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = temp; 
            } 
        } 
    } 

    if (arr[0] > arr[MAX - 1])
        sum2 = arr[0] + arr[MAX - 1]; 

    return 0; 
} 

int main(int argc, char* argv[]) 
{ 
    arr[0] = 34;
    arr[1] = 12;
    arr[2] = 1;
    arr[3] = 16;
    arr[4] = 22;
    arr[5] = 98;
    arr[6] = 11;
    arr[7] = 57;
    arr[8] = 36;
    arr[9] = 27;

    pthread_t thread1, thread2; 


    pthread_create(&thread1, NULL, ascending_sort, NULL); 
    pthread_create(&thread2, NULL, descending_sort, NULL); 


    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 


    if (sum1 == sum2) 
        printf("Correctly sorted\n"); 
    else
        printf("Error in sorting\n"); 

    return 0; 
} 
