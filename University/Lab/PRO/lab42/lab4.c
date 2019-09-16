#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#include "time.h"
#include "stdbool.h"


#define N 10


pthread_t thread1;
pthread_t thread2;
pthread_t thread3;
pthread_t thread4;
pthread_t thread5;
pthread_t thread6;

pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_sig21 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_sig22 = PTHREAD_MUTEX_INITIALIZER;

int sig21_flag = 0;
int sig22_flag = 0;

pthread_cond_t Sig21 = PTHREAD_COND_INITIALIZER;
pthread_cond_t Sig22 = PTHREAD_COND_INITIALIZER;

sem_t SCR1;
sem_t SCR21;

int int_value1 = 1;
int int_value2 = 2;
unsigned unsigned_value1 = 3;
unsigned unsigned_value2 = 4;
long long_value1 = 5;
long long_value2 = 6;
unsigned long ulong_value1 = 7;
unsigned long ulong_value2 = 8;


int CircleBuffer[N];
int NextIn = 0;
int NextOut = 0;
int AmountOfElements = 0;
int getted = 0;
int putted = 0;
int full = 0;
int empty = -1;
FILE* outputFile;


int GetBufferElement(int* buffer) {
        int value = buffer[NextOut];
        buffer[NextOut] = -1;
        AmountOfElements--;
        NextOut = (NextOut + 1) % N;
        
        return value;
}


void PutBufferElement(int* buffer, const int value) {
    buffer[NextIn] = value;
    AmountOfElements++;
    NextIn = (NextIn + 1) % N;
}


bool BufferIsEmpty(int* buffer) {
    for (int i = 0; i < N; i++){
        if (buffer[i] != -1)
            return false;
    }

    return true;
}


bool BufferIsFull(int* buffer) {
    for (int i = 0; i < N; i++) {
        if (buffer[i] == -1)
            return false;
    }

    return true;
}


void* thread_function6(void* unused) {
    int sem_value;

    while (1) {
        pthread_mutex_lock(&MCR1);
        sem_getvalue(&SCR1, &sem_value);
        if (AmountOfElements < N) {
            PutBufferElement(CircleBuffer, sem_value);
            sem_getvalue(&SCR1, &sem_value);
            fprintf(outputFile, "Thread number 6: semaphore = %d - element %d was writed\n", sem_value, sem_value);
            sem_post(&SCR1);
        }
        pthread_mutex_unlock(&MCR1);
    }
}


int main()
{
    for (int i = 0; i < N; i++) {
        CircleBuffer[i] = -1;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", CircleBuffer[i]);
    }
    printf("\n");
    printf("%d\n", AmountOfElements);

    char fileName[] = "output.txt";
    outputFile = fopen(fileName, "w");

    sem_init(&SCR1, 0, 0);
    sem_init(&SCR21, 0, 0);

    // pthread_create (&thread1, NULL, &thread_function1, NULL);
    // pthread_create (&thread2, NULL, &thread_function2, NULL);
    // pthread_create (&thread3, NULL, &thread_function3, NULL);
    // pthread_create (&thread4, NULL, &thread_function4, NULL);
    // pthread_create (&thread5, NULL, &thread_function5, NULL);
    pthread_create (&thread6, NULL, &thread_function6, NULL);

    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);
    // pthread_join(thread3, NULL);
    // pthread_join(thread4, NULL);
    // pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);


    fclose(outputFile);
}