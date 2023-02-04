#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t barber;
sem_t customer;
sem_t mutex;
int waiting = 0;

void *Barber(void *arg) {
    while(1){
    sem_wait(&customer);
    sem_wait(&mutex);
    waiting--;
    sem_post(&mutex);

    printf("Barber is cutting hair\n");
    sleep(1);
    sem_post(&barber);
    if (waiting == 0){
        printf("Barber is sleeping\n");
       // break;
    }
    
    }
   
}

void *Customer(void *arg) {
    sem_wait(&mutex);
    if(waiting < N) {
        waiting++;
        printf("Customer entered\n");
        sem_post(&customer);
        sem_post(&mutex);
        sem_wait(&barber);
    }
    else {
        sem_post(&mutex);
        printf("No chairs available, customer leaving\n");
    }
}

int main() {
    sem_init(&barber, 0, 0);
    sem_init(&customer, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t bthread, cthread[10];

    pthread_create(&bthread, NULL, Barber, NULL);
    for (int i = 0; i < 10; i++)
        pthread_create(&cthread, NULL, Customer, NULL);

    
    for (int i = 0; i < 10; i++){
        pthread_join(bthread, NULL);
        pthread_join(cthread, NULL);
    }

    return 0;
}
