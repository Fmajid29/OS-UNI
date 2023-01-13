#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int N, M;
int factorial = 1;

void* factorial_thread(void* arg)
{
    int thread_num = *((int*) arg);
    int thread_factorial = 1;
    for (int i = thread_num; i <= N; i += M) {
        thread_factorial *= i;
    }
    printf("Thread %d: %d\n", thread_num + 1, thread_factorial);
    factorial *= thread_factorial;
    pthread_exit(0);
}

int main(int argc, char* argv[])
{
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    pthread_t threads[M];
    int thread_nums[M];
    for (int i = 0; i < M; i++)
    {
        thread_nums[i] = i+1;
        pthread_create(&threads[i], NULL, factorial_thread, &thread_nums[i]);
    }
    for (int i = 0; i < M; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Factorial of %d: %d\n", N, factorial);
    return 0;
}
