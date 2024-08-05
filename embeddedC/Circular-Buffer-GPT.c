/*

New data is enqueued at Head
dequeued from tail 
uses size in the circular buffer, can be checked against BUFFER_SIZE to see if its full or not

Output:
Buffer contents: 1 2 3 4 5 
Buffer is full. Cannot enqueue data.
Failed to add data 6.
Dequeued: 1
Dequeued: 2
Buffer contents: 3 4 5 
Buffer contents: 3 4 5 6
*/

#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 5  // Define the size of the buffer

typedef struct {
    int buffer[BUFFER_SIZE]; // The buffer array
    int head;                // Points to the next position to write
    int tail;                // Points to the next position to read
    int size;                // Current number of elements in the buffer
} CircularBuffer;

// Function to initialize the buffer
void initBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
}

// Function to check if the buffer is full
bool isFull(CircularBuffer *cb) {
    return cb->size == BUFFER_SIZE;
}

// Function to check if the buffer is empty
bool isEmpty(CircularBuffer *cb) {
    return cb->size == 0;
}

// Function to add an element to the buffer 
bool enqueue(CircularBuffer *cb, int data) {
    if (isFull(cb)) {
        printf("Buffer is full. Cannot enqueue data.\n");
        return false;
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->size++;
    return true;
}

// Function to remove an element from the buffer
bool dequeue(CircularBuffer *cb, int *data) {
    if (isEmpty(cb)) {
        printf("Buffer is empty. Cannot dequeue data.\n");
        return false;
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->size--;
    return true;
}

// Function to print the buffer elements
void printBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty.\n");
        return;
    }
    printf("Buffer contents: ");
    int count = cb->size;
    int index = cb->tail;
    while (count > 0) {
        printf("%d ", cb->buffer[index]);
        index = (index + 1) % BUFFER_SIZE;
        count--;
    }
    printf("\n");
}

int main() {
    CircularBuffer cb;
    int data;

    initBuffer(&cb);

    enqueue(&cb, 1);
    enqueue(&cb, 2);
    enqueue(&cb, 3);
    enqueue(&cb, 4);
    enqueue(&cb, 5);  // Buffer is now full

    printBuffer(&cb);

    // Attempt to enqueue to a full buffer
    if (!enqueue(&cb, 6)) {
        printf("Failed to add data 6.\n");
    }

    dequeue(&cb, &data);
    printf("Dequeued: %d\n", data);
    dequeue(&cb, &data);
    printf("Dequeued: %d\n", data);

    printBuffer(&cb);

    enqueue(&cb, 6);
    printBuffer(&cb);

    return 0;
}

