#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeblock;
int data = 0, rcount = 0, wcount = 0;

void *reader(void *arg)
{
    sem_wait(&mutex);
    rcount++;
    if(rcount==1 && wcount >= rcount)
    {
        sem_wait(&writeblock);
    }
    sem_post(&mutex);
    printf("Data read\n");
    sem_wait(&mutex);
    rcount--;
    if(rcount==0)
    {
        sem_post(&writeblock);
    }
        sem_post(&mutex);
}

void *writer(void *arg)
{
    sem_wait(&writeblock);
    wcount++;
    data++;
    printf("Data writen\n");
    sem_post(&writeblock);
}

int main()
{
    int i,b;
    pthread_t rtid[5],wtid[7];
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);

    for(i=0;i< 7;i++)
    {
        if (i < 5)
            pthread_create(&rtid[i],NULL,reader,NULL);
        pthread_create(&wtid[i],NULL,writer,NULL);
    }

    for(i=0;i<=2;i++)
    {
        pthread_join(wtid[i],NULL);
        pthread_join(rtid[i],NULL);
    }

    return 0;
}