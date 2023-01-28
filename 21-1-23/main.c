#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t accessMutex, wrt;
int readCount = 0;

void *reader(void *arg)
{
    int f = (int)arg;
    sem_wait(&accessMutex);
    readCount++;
    if(readCount==1)
        sem_wait(&wrt);
    sem_post(&accessMutex);
    printf("Reader %d is reading\n", f);
    sleep(1);
    sem_wait(&accessMutex);
    readCount--;
    if(readCount==0)
        sem_post(&wrt);
    sem_post(&accessMutex);
}

void *writer(void *arg)
{
    int f = (int)arg;
    sem_wait(&wrt);
    printf("Writer %d is writing\n", f);
    sleep(1);
    sem_post(&wrt);
}

int main()
{
    pthread_t rtid[5], wtid[5];
    sem_init(&accessMutex, 0, 1);
    sem_init(&wrt, 0, 1);
    for(int i=0;i<=5;i++)
    {
        pthread_create(&wtid[i], NULL, writer, (void*) i);
        pthread_create(&rtid[i], NULL, reader, (void*) i);
    }
    for(int i=0;i<=5;i++)
    {
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }
    return 0;
}
