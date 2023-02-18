#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_counter = 0;

void *increment_counter(void *thread_id) {
    int id = *(int*)thread_id;
    printf("Thread %d starting\n", id);

    // Acquire mutex lock
    pthread_mutex_lock(&mutex);

    // Critical section
    shared_counter++;
    printf("Thread %d incremented counter, counter is now %d\n", id, shared_counter);

    // Release mutex lock
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

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
