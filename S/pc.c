#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int read_index = 0;
int write_index = 0;

void* producer(void* arg) {
    while (true) {
        int item = produce_item();
        buffer[write_index] = item;
        write_index = (write_index + 1) % BUFFER_SIZE;
    }
}

void* consumer(void* arg) {
    while (true) {
        int item = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
        consume_item(item);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}
