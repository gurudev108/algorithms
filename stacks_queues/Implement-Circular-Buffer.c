/*
Implement Circular Buffer

Output:
10 enqueued to buffer
20 enqueued to buffer
30 enqueued to buffer
40 enqueued to buffer
50 enqueued to buffer
Buffer elements: 10 20 30 40 50 
Front element is 10
Dequeued element is 10
Dequeued element is 20
Buffer elements: 30 40 50 
60 enqueued to buffer
70 enqueued to buffer
Buffer elements: 30 40 50 60 70 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Define the maximum size of the circular buffer

// Circular buffer structure
struct CircularBuffer {
    int arr[MAX]; // Array to store the buffer elements
    int front;    // Index of the front element
    int rear;     // Index of the rear element
    int size;     // Current size of the buffer
};

// Function to initialize the circular buffer
void initializeBuffer(struct CircularBuffer* buffer) {
    buffer->front = 0;
    buffer->rear = -1;
    buffer->size = 0;
}

// Function to check if the circular buffer is empty
int isEmpty(struct CircularBuffer* buffer) {
    return buffer->size == 0;
}

// Function to check if the circular buffer is full
int isFull(struct CircularBuffer* buffer) {
    return buffer->size == MAX;
}

// Function to add an element to the circular buffer
void enqueue(struct CircularBuffer* buffer, int value) {
    if (isFull(buffer)) {
        printf("Buffer overflow! Cannot enqueue %d\n", value);
        return;
    }
    buffer->rear = (buffer->rear + 1) % MAX;
    buffer->arr[buffer->rear] = value;
    buffer->size++;
    printf("%d enqueued to buffer\n", value);
}

// Function to remove an element from the circular buffer
int dequeue(struct CircularBuffer* buffer) {
    if (isEmpty(buffer)) {
        printf("Buffer underflow! Cannot dequeue\n");
        return -1;
    }
    int value = buffer->arr[buffer->front];
    buffer->front = (buffer->front + 1) % MAX;
    buffer->size--;
    return value;
}

// Function to get the front element of the circular buffer
int peek(struct CircularBuffer* buffer) {
    if (isEmpty(buffer)) {
        printf("Buffer is empty\n");
        return -1;
    }
    return buffer->arr[buffer->front];
}

// Function to print the circular buffer
void printBuffer(struct CircularBuffer* buffer) {
    if (isEmpty(buffer)) {
        printf("Buffer is empty\n");
        return;
    }
    printf("Buffer elements: ");
    int i = buffer->front;
    for (int count = 0; count < buffer->size; count++) {
        printf("%d ", buffer->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    struct CircularBuffer buffer;
    initializeBuffer(&buffer);

    enqueue(&buffer, 10);
    enqueue(&buffer, 20);
    enqueue(&buffer, 30);
    enqueue(&buffer, 40);
    enqueue(&buffer, 50); // Buffer will be full after this

    printBuffer(&buffer);

    printf("Front element is %d\n", peek(&buffer));

    printf("Dequeued element is %d\n", dequeue(&buffer));
    printf("Dequeued element is %d\n", dequeue(&buffer));

    printBuffer(&buffer);

    enqueue(&buffer, 60); // Enqueue after dequeuing
    enqueue(&buffer, 70); // Circular wrap-around

    printBuffer(&buffer);

    return 0;
}

