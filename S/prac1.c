#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<pthread.h>

unsigned int count;
int lock = 0;
void* increment (void* ptr)
{
    while (lock == 1); // lock = 0
    
    lock = 1;
    for(unsigned int i=0;i<500000;i++)
        count++;
    lock = 0;
}
void* decrement (void* ptr)
{
 while (lock == 1); // ;lock == 1
 lock = 1;
for(unsigned int i=0;i<500000;i++)
    count--;
lock = 0;
}
int main()
{
count = 3;
printf("\nInitial value of Count is %d ",count);
pthread_t pid1,pid2;
pthread_create(&pid1,NULL,&increment,NULL);
pthread_create(&pid2,NULL,&decrement,NULL);
pthread_join(pid1,NULL);
pthread_join(pid2,NULL);
printf("\nFinal value of Count is %d ",count);
printf("\nIs it correct? \n");
return 0;
}