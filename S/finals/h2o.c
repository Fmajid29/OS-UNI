#include <pthread.h>
#include <semaphore.h>
sem_t cSem;
sem_t hSem;
sem_t oSem;
sem_t glucoseSem;
int cCount = 0;
int hCount = 0;
int oCount = 0;
void makeGlucose() {
    // code to make glucose
    printf("Glucose formed!\n");
}
void *cReady(void *arg) {
    sem_wait(&cSem);
    cCount++;
    if (cCount >= 6 && hCount >= 12 && oCount >= 6) {
        sem_post(&glucoseSem);
    } else {
        sem_post(&cSem);
    }
}
void *hReady(void *arg) {
    sem_wait(&hSem);
    hCount++;
    if (cCount >= 6 && hCount >= 12 && oCount >= 6) {
        sem_post(&glucoseSem);
    } else {
        sem_post(&hSem);
    }
}
void *oReady(void *arg) {
    sem_wait(&oSem);
    oCount++;
    if (cCount >= 6 && hCount >= 12 && oCount >= 6) {
        sem_post(&glucoseSem);
    } else {
        sem_post(&oSem);
    }
}
int main() {
    sem_init(&cSem, 0, 6);
    sem_init(&hSem, 0, 12);
    sem_init(&oSem, 0, 6);
    sem_init(&glucoseSem, 0, 0);
    pthread_t cThreads[6];
    pthread_t hThreads[12];
    pthread_t oThreads[6];
    for (int i = 0; i < 6; i++) {
        pthread_create(&cThreads[i], NULL, cReady, NULL);
    }
    for (int i = 0; i < 12; i++) {
        pthread_create(&hThreads[i], NULL, hReady, NULL);
    }
    for (int i = 0; i < 6; i++) {
        pthread_create(&oThreads[i], NULL, oReady, NULL);
    }
    sem_wait(&glucoseSem);
    makeGlucose();
    for (int i = 0; i < 6; i++) {
        pthread_join(cThreads[i], NULL);
    }
    for (int i = 0; i < 12; i++) {
        pthread_join(hThreads[i], NULL);
    }
    for (int i = 0; i < 6; i++) {
        pthread_join(oThreads[i], NULL);
    }
    sem_destroy(&cSem);
    sem_destroy(&hSem);
    sem_destroy(&oSem);
    sem_destroy(&glucoseSem);
    return 0;
}