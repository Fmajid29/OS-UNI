#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char* argv[]){

    int const SIZE = argc - 1;
    int arr[SIZE];

    // recieving data from terminal and putting in integer array
    for (int i = 0; i < SIZE; i++){
        arr[i] = atoi(argv[i + 1]);
    }

    int pipe1[2];
    pipe(pipe1);

    // writing int array into the pipe.
    write(pipe1[1], arr, sizeof(arr));

    // creating first child
    pid_t id = fork();

    if (id == 0){
        // doing all the functionality of C1
        int array[SIZE], temp;
        read(pipe1[0], array, sizeof(array));
        
        for (int i = 0; i < SIZE; i++){
            temp = array[i];
            for (int j = 1; j < SIZE; j++){
                if (temp < array[j]){
                    array[j - 1] = array[j];
                    array[j] = temp;
                }
            }
        }

        for (int i = 0; i< SIZE; i++){
            printf("%d \n", array[i]);
        }

        // writing decending sorted array back into the pipe
        write(pipe1[1], array, sizeof(array));
    }
    else{
        wait(0);
        pid_t id1;
        // creating child 2
        id1 = fork();
        if (id1 == 0){
            // doing functionality of C2
            int array1[SIZE];

            // reading sorted array from the pipe passed by C1
            read(pipe1[0], array1, sizeof(array1));
            int secMax[1];
            secMax[0] = array1[1];

            // writing data back into the pipe.
            write(pipe1[1],secMax, sizeof(secMax));
        }
        else{
            wait(0);
            pid_t id2;
            // creating child 3
            id2 = fork();
            if (id2 == 0){

                // doing C3 functionality
                int seM[1];
                read(pipe1[0], seM, sizeof(seM));
                printf("%d \n", seM[0]);
            }
            else{
                wait(0);
            }
        }
    }

    return 0;
}