#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_FORKS 4

sem_t forks[NUM_FORKS];

void *philosopher(void *num) {
    int i = *((int *)num);
    int left = i;
    int right = (i + 1) % NUM_FORKS;

    while (1) {
        printf("Philosopher %d is thinking.\n", i);
        sleep(1);
        printf("Philosopher %d is hungry.\n", i);

        sem_wait(&forks[left]);
        printf("Philosopher %d took fork %d.\n", i, left);

        sem_wait(&forks[right]);
        printf("Philosopher %d took fork %d.\n", i, right);

        printf("Philosopher %d is eating.\n", i);
        sleep(1);

        sem_post(&forks[left]);
        printf("Philosopher %d put down fork %d.\n", i, left);

        sem_post(&forks[right]);
        printf("Philosopher %d put down fork %d.\n", i, right);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_FORKS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
