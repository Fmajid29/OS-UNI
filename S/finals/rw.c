#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

void* inc(){
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 500000; i++)
        counter++;
    pthread_mutex_unlock(&mutex);
    
}

void* dec(){
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < 500000; i++)
        counter--;
    pthread_mutex_unlock(&mutex);

}

int main(){
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1,NULL,&inc,NULL);
    pthread_create(&t2,NULL,&dec,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("%d\n",counter);
    return 0;
}