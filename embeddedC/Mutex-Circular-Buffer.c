/*
Output:

Buffer: 10 20 30 26 64029959 
Head: 0, Tail: 3, Count: 3
Dequeued: 10
Buffer: 10 20 30 26 64029959 
Head: 1, Tail: 3, Count: 2
Buffer: 60 20 30 40 50 
Head: 1, Tail: 1, Count: 5
*/

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define BUFFER_SIZE 5  // Size of the circular buffer

// Circular buffer structure
typedef struct {
    int buffer[BUFFER_SIZE];
    int head;    // Points to the start of the buffer (next item to dequeue)
    int tail;    // Points to the end of the buffer (next empty slot for enqueue)
    int count;   // Number of elements currently in the buffer
    pthread_mutex_t lock;  // Mutex for thread safety
} CircularBuffer;

// Initialize the circular buffer
void initBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
    pthread_mutex_init(&(cb->lock), NULL);
}

// Check if the buffer is full
bool isFull(CircularBuffer *cb) {
    return cb->count == BUFFER_SIZE;
}

// Check if the buffer is empty
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// Add an item to the circular buffer (enqueue)
bool enqueue(CircularBuffer *cb, int item) {
    pthread_mutex_lock(&(cb->lock));  // Acquire the lock
    if (isFull(cb)) {
        printf("Buffer is full! Cannot enqueue.\n");
        pthread_mutex_unlock(&(cb->lock));  // Release the lock
        return false;
    }
    cb->buffer[cb->tail] = item;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count++;
    pthread_mutex_unlock(&(cb->lock));  // Release the lock
    return true;
}

// Remove an item from the circular buffer (dequeue)
bool dequeue(CircularBuffer *cb, int *item) {
    pthread_mutex_lock(&(cb->lock));  // Acquire the lock
    if (isEmpty(cb)) {
        printf("Buffer is empty! Cannot dequeue.\n");
        pthread_mutex_unlock(&(cb->lock));  // Release the lock
        return false;
    }
    *item = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count--;
    pthread_mutex_unlock(&(cb->lock));  // Release the lock
    return true;
}

// Print the current state of the circular buffer
void printBuffer(CircularBuffer *cb) {
    pthread_mutex_lock(&(cb->lock));  // Acquire the lock
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", cb->buffer[i]);
    }
    printf("\nHead: %d, Tail: %d, Count: %d\n", cb->head, cb->tail, cb->count);
    pthread_mutex_unlock(&(cb->lock));  // Release the lock
}

// Example usage
int main() {
    CircularBuffer cb;
    initBuffer(&cb);
    
    // Enqueue elements into the buffer
    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);
    printBuffer(&cb);
    
    // Dequeue an element from the buffer
    int item;
    dequeue(&cb, &item);
    printf("Dequeued: %d\n", item);
    printBuffer(&cb);
    
    // Enqueue more elements
    enqueue(&cb, 40);
    enqueue(&cb, 50);
    enqueue(&cb, 60);  // This will wrap around
    printBuffer(&cb);
    
    return 0;
}

