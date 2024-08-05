/*
Reader Writer Problem - The reader-writer problem is a classic synchronization problem where a shared resource can be read by multiple readers simultaneously but only written by a single writer at a time. When giving preference to writers, a writer should be allowed to write as soon as it becomes available, preventing any new readers from starting to read if a writer is waiting.

Approach - Use Cond Var as it allows more than 1 producer/consumer

Improved writer - active writer. 
Output:
Reader 1 is reading.
Reader 2 is reading.
Writer 1 is writing.
Writer 2 is writing.
Writer 1 is writing.
Writer 2 is writing.
Writer 1 is writing.
Writer 2 is writing.
Reader 1 is reading.
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
        printf("Reader %d is reading.\n", id);
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
        printf("Writer %d is writing.\n", id);
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
/*
Explanation
Data Structures:
pthread_mutex_t mutex: A mutex to protect shared data and ensure mutual exclusion.
pthread_cond_t readerQ and pthread_cond_t writerQ: Condition variables to manage waiting readers and writers.
int readers: The count of active readers.
int writers: The count of waiting writers.
int active_writers: The count of active writers (either 0 or 1).
Reader Thread (reader):
Acquires the lock and waits if there are any active or waiting writers.
Increments the readers count and releases the lock.
Reads the data and then decrements the readers count.
Signals waiting writers if it was the last reader.
Writer Thread (writer):
Acquires the lock and increments the writers count.
Waits if there are any active readers or writers.
Decrements the writers count and sets active_writers to 1.
Writes the data and then resets active_writers to 0.
Signals waiting writers if there are any, otherwise signals all waiting readers.
Main Function (main):
Creates two reader threads and two writer threads.
Allocates a unique ID for each thread to distinguish between them.
Key Points
Writer Priority: The program ensures that waiting writers are given priority over new readers. Once a writer is waiting, new readers are not allowed to start reading.
Condition Variables: readerQ and writerQ are used to signal threads when they can proceed.
Resource Access: Multiple readers can access the resource simultaneously, but writers get exclusive access.
*/
