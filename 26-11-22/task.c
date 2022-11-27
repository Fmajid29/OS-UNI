#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]){

    int nums[argc] , i;

    for(i = 1 ; i  < argc ; i++){
        nums[i] = atoi(argv[i]);
    }

    pid_t forkId;

    int pipe1[2];

    pipe(pipe1);

    write(pipe1[WRITE] , nums , sizeof(nums));

    forkId = fork();

    if (forkId == 0){
        int getNums[argc];
        read(pipe1[READ] , getNums, sizeof(getNums));
        close(pipe1[READ]);
        printf("child recieved %d", getNums[4]);
        int min = 5;
        write(pipe1[WRITE], min, sizeof(min));
    }
    else{
        wait();
        close(pipe1[WRITE]);
        int min = 5;
        read(pipe1[READ], min, sizeof(min));
        printf("\nparent recieved min: %d", min);
    }
    
    return 0;
}