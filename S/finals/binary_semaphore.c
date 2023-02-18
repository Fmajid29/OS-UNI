#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t binary_semaphore;
int shared_counter = 0;

void *increment_counter(void *thread_id) {
    int id = *(int*)thread_id;
    printf("Thread %d starting\n", id);

    // Wait for the semaphore to be available
    sem_wait(&binary_semaphore); //--1

    // Critical section
    shared_counter++;
    printf("Thread %d incremented counter, counter is now %d\n", id, shared_counter);

    // Release the semaphore
    sem_post(&binary_semaphore); //++1

}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the binary semaphore with an initial value of 1 (available)
    sem_init(&binary_semaphore, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of counter: %d\n", shared_counter);
    return 0;
}
