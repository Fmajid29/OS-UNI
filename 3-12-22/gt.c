#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int findSum(int* arr, int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += arr[i];
    }
    return sum;
}

int main(int argc, char* argv[]){

    int const  SIZE = argc - 1;
    int arr[SIZE];
    int rez[1];
    
    for (int i = 0; i < SIZE; i++){
       arr[i] = atoi(argv[i + 1]);
    }

    int pipe1[2];
    pipe(pipe1);

    write(pipe1[1], arr, sizeof(arr));
    pid_t id = fork();

    if (id == 0){
        int array[SIZE];
        // close(pipe1[1]);
        read(pipe1[0], array, sizeof(array));

        int arr1[SIZE / 2], arr2[SIZE / 2];
        
        
        int i;
        for (i = 0; i < SIZE/2; i++){
            arr1[i] = array[i];
        }
        for (int j = 0; j < SIZE / 2; j++){
            arr2[j] = array[j + i];
        }

        int sum1 = findSum(arr1, SIZE/2);

        pid_t id1;
        int pipe2[2];
        pipe(pipe2);
        write(pipe2[1], arr2, sizeof(arr2));
        id1 = fork();


        if (id1 == 0){
            int array1[SIZE / 2];
            read(pipe2[0], array1, sizeof(array1));
            int sum2[1];
            sum2[0] = findSum(array1, SIZE/2);

            write(pipe2[1], sum2, sizeof(sum2));
        }
        else{
            wait(0);
            int sum2[1];
            read(pipe2[0], sum2, 1);
            int rez[1]; 
            rez[0]= sum2[0] - sum1;
            printf("%d", rez[0]);

            write(pipe1[1], rez, sizeof(rez));
        }
    }
    else{
        wait(0);
        int result[1];
        read(pipe1[0], result, sizeof(result));
        printf("%d", rez[0]);
    }


    return 0;
}