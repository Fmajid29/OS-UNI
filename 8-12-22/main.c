#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int const SIZE = argc - 1; int arr[SIZE];

    for (int i = 0; i < SIZE; i++){
        arr[i] = atoi(argv[i+1]);
    }

    int p1[2];
    pipe(p1);

    write(p1[1], arr, sizeof(arr));

    pid_t pid = fork();

    if (pid == 0){
        int array[SIZE];
        read(p1[0], array, sizeof(array));
        write(p1[1], array, sizeof(array));
    }
    else{
        wait(0);
        int arr1[SIZE];
        read(p1[0], arr1, sizeof(arr1));
        for (int i = 0; i < SIZE; i++){
            printf("%d\n",arr1[i]);
        }
    }

    return 0;
}