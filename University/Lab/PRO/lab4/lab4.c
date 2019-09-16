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
int full = 1;
int empty = 0;
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
    if (AmountOfElements == 0) {
        return true;
    }

    return false;
}


bool BufferIsFull(int* buffer) {
    if (AmountOfElements == 10) {
        return true;
    }
    return false;
}


void AtomicValuesUse() {
    fprintf(outputFile, "Value of atomic variable int_value2: %d\n", __sync_fetch_and_add(&int_value2, 0));
    fprintf(outputFile, "Value of atomic variable unsigned_value1: %d\n", __sync_add_and_fetch(&unsigned_value1, 0));
    fprintf(outputFile, "Value of atomic variable long_value1: %ld\n", __sync_or_and_fetch(&long_value1, 0));

}


void AtomicValuesModification() {
    __sync_fetch_and_add(&unsigned_value1, 2);
    __sync_add_and_fetch(&long_value1, 4);
    __sync_fetch_and_and(&int_value1, 10);
    __sync_fetch_and_xor(&int_value2, 3);
    __sync_or_and_fetch(&unsigned_value2, 4);
    __sync_nand_and_fetch(&long_value2, 5);
    __sync_bool_compare_and_swap(&ulong_value1, 4, 10);
    __sync_val_compare_and_swap(&ulong_value1, 3, 8);
}


void* thread_function1(void* unused) {
    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 1 is stopped\n");
            break;
        }
        sig21_flag = 3;
        pthread_cond_broadcast(&Sig21);
        fprintf(outputFile, "Thread 1: SIG21 broadcast\n");

        fprintf(outputFile, "Thread 1: Atomic values use\n");
        AtomicValuesUse();

        fprintf(outputFile, "Thread 1: SCR21++\n");
        sem_post(&SCR21);

        sig22_flag = 2;
        pthread_cond_broadcast(&Sig22);
        fprintf(outputFile, "Thread 1: SIG22 broadcast\n");

        fprintf(outputFile, "Thread 1: Atomic values use\n");
        AtomicValuesUse();
    }

    return 0;
}


void* thread_function2(void* unused) {
    int sem_value;
    int element_value;

    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 2 is stopped\n");
            break;
        }

        pthread_mutex_lock(&mutex_sig21);
        while (sig21_flag == 0) {
            fprintf(outputFile, "Thread 2 is waiting for signal 21\n");
            pthread_cond_wait(&Sig21, &mutex_sig21);
        }
        fprintf(outputFile, "Thread 2 get SIG21");
        sig21_flag--;
        pthread_mutex_unlock(&mutex_sig21);

        fprintf(outputFile, "Thread 2: Atomic value use\n");
        AtomicValuesUse();

        fprintf(outputFile, "Thread 2 is waiting SCR21\n");
        sem_wait(&SCR21);
        fprintf(outputFile, "Thread 2 get SCR21\n");

        fprintf(outputFile, "Thread 2 is waiting for SCR1\n");
        sem_wait(&SCR1);
        fprintf(outputFile, "Thread 2 get SCR1\n");
        pthread_mutex_lock(&MCR1);
        sem_getvalue(&SCR1, &sem_value);
        element_value = GetBufferElement(CircleBuffer);
        fprintf(outputFile, "Thread number 2: semaphore = %d - element %d was read\n", sem_value, element_value);
        pthread_mutex_unlock(&MCR1);
    }

    return 0;
}


void* thread_function3(void* unused) {
    int sem_value;
    int element_value;

    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 3 is stopped\n");
            break;
        }

        fprintf(outputFile, "Thread 3 is waiting SCR1\n");
        sem_wait(&SCR1);
        fprintf(outputFile, "Thread 3 get SCR1\n");
        pthread_mutex_lock(&MCR1);
        sem_getvalue(&SCR1, &sem_value);
        element_value = GetBufferElement(CircleBuffer);
        fprintf(outputFile, "Thread number 3: semaphore = %d - element %d was read\n", sem_value, element_value);
        pthread_mutex_unlock(&MCR1);

        pthread_mutex_lock(&mutex_sig22);
        while (sig22_flag == 0) {
            fprintf(outputFile, "Thread 3 is waiting for signal 22\n");
            pthread_cond_wait(&Sig22, &mutex_sig22);
        }
        fprintf(outputFile, "Thread 3 get SIG22\n");
        sig22_flag--;
        pthread_mutex_unlock(&mutex_sig22);
        
        fprintf(outputFile, "Thread 3: Atomic values use\n");
        AtomicValuesUse();
    }

    return 0;
}


void* thread_function4(void* unused) {
    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 4 is stopped\n");
            break;
        }

        fprintf(outputFile, "Thread 4: Atomic values mod\n");
        AtomicValuesModification();

        pthread_mutex_lock(&mutex_sig21);
        while (sig21_flag == 0) {
            fprintf(outputFile, "Thread 4 is waiting for signal 21\n");
            pthread_cond_wait(&Sig21, &mutex_sig21);
        }
        sig21_flag--;
        pthread_mutex_unlock(&mutex_sig21);
        fprintf(outputFile, "Thread 4: get signal 21\n");

        if (sem_trywait(&SCR21) == 0) {
            fprintf(outputFile, "Thread 4: SCR21 was open\n");
        }

        fprintf(outputFile, "Thread 4: Atomic values mod\n");
        AtomicValuesModification();

        pthread_mutex_lock(&mutex_sig22);
        while (sig22_flag == 0) {
            fprintf(outputFile, "Thread 4 is waiting for signal 22\n");
            pthread_cond_wait(&Sig22, &mutex_sig22);
        }
        sig22_flag--;
        pthread_mutex_unlock(&mutex_sig22);
        fprintf(outputFile, "Thread 4: get signal 22\n");
    }

    return 0;
}


void* thread_function5(void* unused) {
    int sem_value;
    int element_value;

    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty thread 5\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full thread 5\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 5 is stopped\n");
            break;  
        }

        fprintf(outputFile, "Thread 5 is waiting for SCR1\n");
        sem_wait(&SCR1);
        pthread_mutex_lock(&MCR1);
        sem_getvalue(&SCR1, &sem_value);
        element_value = GetBufferElement(CircleBuffer);
        fprintf(outputFile, "Thread number 5: semaphore = %d - element %d was read\n", sem_value, element_value);
        pthread_mutex_unlock(&MCR1);

        pthread_mutex_lock(&mutex_sig21);
        while (sig21_flag == 0) {
                fprintf(outputFile, "Thread 5 is waiting for signal 21\n");
                pthread_cond_wait(&Sig21, &mutex_sig21);
        }
        sig21_flag--;
        pthread_mutex_unlock(&mutex_sig21);
        fprintf(outputFile, "Thread 5 get SIG21\n");

        fprintf(outputFile, "Thread 5: Atomic value use\n");
        AtomicValuesUse();
    }

    return 0;
}


void* thread_function6(void* unused) {
    int sem_value;

    while (1) {
        if (BufferIsEmpty(CircleBuffer)) {
            fprintf(outputFile, "Buffer is empty thread 6\n");
            empty++;
        }
        if (BufferIsFull(CircleBuffer)) { 
            fprintf(outputFile, "Buffer is full thread 6\n");
            full++;
        }
        if (full >= 2 && empty >= 2) {
            fprintf(outputFile, "Thread 6 is stopped\n");
            break;
        }

        pthread_mutex_lock(&MCR1);
        sem_getvalue(&SCR1, &sem_value);
        if (sem_value < N) {
            PutBufferElement(CircleBuffer, sem_value);
            sem_getvalue(&SCR1, &sem_value);
            fprintf(outputFile, "Thread number 6: semaphore = %d - element %d was writed\n", sem_value, sem_value);
            sem_post(&SCR1);
        }
        pthread_mutex_unlock(&MCR1);
    }

    return 0;
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

    char fileName[] = "output.txt";
    outputFile = fopen(fileName, "w");

    sem_init(&SCR1, 0, 0);
    sem_init(&SCR21, 0, 0);

    pthread_create (&thread1, NULL, &thread_function1, NULL);
    pthread_create (&thread2, NULL, &thread_function2, NULL);
    pthread_create (&thread3, NULL, &thread_function3, NULL);
    pthread_create (&thread4, NULL, &thread_function4, NULL);
    pthread_create (&thread5, NULL, &thread_function5, NULL);
    pthread_create (&thread6, NULL, &thread_function6, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);


    fclose(outputFile);
}