#include <stdio.h>
#include <pthread.h>

int readers = 0; // number of readers currently in the critical section
int writers = 0; 
pthread_mutex_t lock;
pthread_cond_t cond;

void* reader(void* arg) {
    pthread_mutex_lock(&lock);
    while (writers > 0) {
        pthread_cond_wait(&cond, &lock);
    }
    readers++;
    pthread_mutex_unlock(&lock);

    // critical section - read data
    printf("Reader is reading\n");

    pthread_mutex_lock(&lock);
    readers--;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

void* writer(void* arg) {
    pthread_mutex_lock(&lock);
    while (readers > 0 || writers > 0) {
        pthread_cond_wait(&cond, &lock);
    }
    writers++;
    pthread_mutex_unlock(&lock);

    // critical section - write data
    printf("Writer is writing\n");

    pthread_mutex_lock(&lock);
    writers--;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);
    pthread_create(&r3, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&w2, NULL, writer, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}