#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    int p1[2];
    pipe(p1);
    pid_t pid;
    pid = fork();

    if (pid == 0){
        close(p1[0]);
        dup2(p1[1], 1);
        close(p1[1]);
        execlp("ls","ls","-r",NULL);
    }
    else{
        wait(0);
        int f = open("input.txt", O_WRONLY | O_APPEND);
        char buffer[1000] = {""};
        close(p1[1]);
        dup2(f,1);
        while(read(p1[0],buffer,sizeof(buffer)) != 0){
            printf("%s", buffer);
        }
        close(p1[0]);
    }

    return 0;
}