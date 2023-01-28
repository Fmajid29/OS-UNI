#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, readerQueue;
int data = 0, readcount = 0, readerQueueSize = 0;

void* reader(void* arg)
{
    int f;
    f = ((int)arg);
    sem_wait(&readerQueue);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    printf("Data read by the reader %d is %d\n", f, data);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
}

void* writer(void* arg)
{
    int f;
    f = ((int) arg);
    sem_wait(&wrt);
    data++;
    printf("Data writen by the writer %d is %d\n", f, data);
    sem_post(&readerQueue);
    sem_post(&wrt);

    
}

int main()
{
    int i, b; 
    pthread_t rtid[8], wtid[3];
    sem_init(&wrt, 0, 1);
    sem_init(&readerQueue, 0, 5);
    for (i = 0; i < 8; i++)
    {
        pthread_create(&rtid[i], NULL, reader, (void *)i);
    }
    for (i = 0; i < 3; i++)
    {
        pthread_create(&wtid[i], NULL, writer, (void *)i);
    }
    for (i = 0; i < 8; i++)
    {
        if (i < 3)
            pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
        
    }
    return 0;
}
