#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{

    execlp("ls", "ls", "-a", NULL);
    printf("executed\n");
    // pid_t a,b,c,d,e,f,g,h,i;

    // b = fork();

    // if(b == 0)
    // {
    //     e=fork();
    //     if(e==0)
    //     {
    //         h=fork();
    //         if(h==0)
    //         {
    //             printf("%d =H\n",getpid());
    //         }
    //         else
    //         {
    //             i=fork();
    //             if(i==0)
    //             {
    //                 printf("%d =I\n",getpid());
    //             }
    //             else
    //             {
    //                 printf("%d =E\n",getpid());
    //             }
    //         }
    //     }
    //     else
    //     {
    //         f=fork();
    //         if(f==0)
    //         {
    //             printf("%d =F\n",getpid());
    //         }
    //         else
    //         {
    //             printf("%d =B\n",getpid());
    //         }
    //     }
    // }
    // else
    // {
    //     c = fork();
    //     if(c==0)
    //     {
    //         g=fork();
    //         if(g==0)
    //         {
    //             printf("%d =G\n",getpid());
    //         }
    //         else
    //         {
    //             printf("%d =C\n",getpid());
    //         }
    //     }
    //     else
    //     {
    //         d=fork();
    //         if(d==0)
    //         {
    //             printf("%d =D\n",getpid());
    //         }
    //         else
    //         {
    //             printf("%d =A\n",getpid());
    //         }
    //     }
    // }
    return 0;
}