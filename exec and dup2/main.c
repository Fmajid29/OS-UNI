#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int p1[2];
    pipe(p1);
    pid_t id1 = fork();

    if (id1 > 0){
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);
        execlp("ps", "ps", NULL);
    }
    else if (id1 == 0){
        close(p1[1]);
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);
        execlp("sed", "sed", "1d", NULL);

        int p2[2];
        pipe(p2);
        pid_t id2 = fork();

        if (id2 > 0){
            close(p2[0]);
            dup2(p2[1], STDOUT_FILENO);
            close(p2[1]);
            execlp("sed", "sed", "1d", NULL);
        }
        else if (id2 == 0){
            close(p2[1]);
            dup2(p2[0], STDIN_FILENO);
            close(p2[0]);
            execlp("wc", "wc", "-l", NULL);
        }
    }

    return 0;
}