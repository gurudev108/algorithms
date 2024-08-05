/*

Output:
Reader 1 is reading the shared buffer:
0 0 0 0 0 0 0 0 0 0 
Reader 2 is reading the shared buffer:
0 0 0 0 0 0 0 0 0 0 
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Reader 1 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Reader 2 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Reader 1 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Reader 2 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Reader 2 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Reader 1 is reading the shared buffer:
2 2 2 2 2 2 2 2 2 2 
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Writer 1 is writing to the shared buffer.
Writer 2 is writing to the shared buffer.
Writer 1 is writing to the shared buffer.
Reader 1 is reading the shared buffer:
1 1 1 1 1 1 1 1 1 1 

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readerQ = PTHREAD_COND_INITIALIZER;
pthread_cond_t writerQ = PTHREAD_COND_INITIALIZER;

int readers = 0;
int writers = 0;
int active_writers = 0;
int shared_buffer[10] = {0}; // Shared data that will be read and written by threads

void* reader(void* arg) {
    int id = *((int*)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if there are active or waiting writers
        while (writers > 0 || active_writers > 0) {
            pthread_cond_wait(&readerQ, &mutex);
        }

        readers++;
        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader %d is reading the shared buffer:\n", id);
        for (int i = 0; i < 10; i++) {
            printf("%d ", shared_buffer[i]);
        }
        printf("\n");
        sleep(1); // Simulate reading

        pthread_mutex_lock(&mutex);
        readers--;
        if (readers == 0 && writers > 0) {
            pthread_cond_signal(&writerQ);
        }
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate time between reads
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        writers++;
        // Wait if there are active readers or writers
        while (active_writers > 0 || readers > 0) {
            pthread_cond_wait(&writerQ, &mutex);
        }

        writers--;
        active_writers++;
        pthread_mutex_unlock(&mutex);

        // Writing section
        for (int i = 0; i < 10; i++) {
            shared_buffer[i] = id; // Simulate writing by setting all elements to writer's id
        }
        printf("Writer %d is writing to the shared buffer.\n", id);
        sleep(1); // Simulate writing

        pthread_mutex_lock(&mutex);
        active_writers--;
        if (writers > 0) {
            pthread_cond_signal(&writerQ);
        } else {
            pthread_cond_broadcast(&readerQ);
        }
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate time between writes
    }

    return NULL;
}

int main() {
    pthread_t readers[2], writers[2];

    // Create reader threads
    for (int i = 0; i < 2; i++) {
        int* id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, (void*)id);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        int* id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, (void*)id);
    }

    // Join threads (not really needed in this case, as the main thread will run indefinitely)
    for (int i = 0; i < 2; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    return 0;
}

