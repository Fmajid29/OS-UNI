#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int passengers 70;

sem_t busses;

void* depart(){
    if (riders == 0)
        printf("no riders avai");
    else
    printf("buss is full and departing");
}


void *board{
    sem_post(busses)
    depart();
}

void *increment_counter(void *thread_id) {
    int id = *(int*)thread_id;
    printf("Thread %d starting\n", id);

    // Wait for the semaphore to be available
    sem_wait(&counting_semaphore);

    // Critical section
    if (passengers > 0)
    shared_counter--;


    if(passengers == 0){
        depart();
    }
    printf("Thread %d incremented counter, counter is now %d\n", id, shared_counter);

    // Release the semaphore
    sem_post(&counting_semaphore);

}


int main() {
    pthread_t threads[riders];
    int thread_ids[riders];

    // Initialize the counting semaphore with an initial value of 2
    sem_init(&busses, 0, 3);

    // Create threads
    for (int i = 0; i < riders; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < riders; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of counter: %d\n", shared_counter);
    return 0;
}
