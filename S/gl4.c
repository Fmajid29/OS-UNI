#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 3

int n;
int *numbers;

void* factorial(void* arg)
{
    int start = *((int*)arg);
    int end = start + n/3;

    for (int i = start; i < end; i++)
    {
        int fact = 1;
        for (int j = 1; j <= numbers[i]; j++)
        {
            fact *= j;
        }
        printf("Factorial of %d: %d\n", numbers[i], fact);
    }
    return NULL;
}

void* prime(void* arg)
{
    int start = *((int*)arg);
    int end = start + n/3;

    for (int i = start; i < end; i++)
    {
        int isPrime = 1;
        for (int j = 2; j <= numbers[i] / 2; j++)
        {
            if (numbers[i] % j == 0)
            {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
        {
            printf("prime: %d\n", numbers[i]);
        }
    }
    return NULL;
}

void* power(void* arg)
{
    int start = *((int*)arg);
    int end = start + n/3;

    for (int i = start; i < end; i++)
    {
        int result = 1;
        for (int i = 0; i < numbers[i]; i++)
        {
            result *= 2;
        }
        printf("2 power %d is: %d\n", numbers[i], result);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    n = argc - 1;
    numbers = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t threads[MAX_THREADS];
    int thread_args[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++)
    {
        thread_args[i] = i * (n/3);

        if (i == 0)
        {
            printf("Thread %d loading...\n", i+1);
            pthread_create(&threads[i], NULL, factorial, &thread_args[i]);
            sleep(1);
        }
        else if (i == 1)
        {
            printf("Thread %d loading...\n", i+1);
            pthread_create(&threads[i], NULL, prime, &thread_args[i]);
            sleep(1);
        }
        else if (i == 2)
        {
            printf("Thread %d loading...\n", i+1);
            pthread_create(&threads[i], NULL, power, &thread_args[i]);
            sleep(1);
        }
    }

    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

return 0;
}
