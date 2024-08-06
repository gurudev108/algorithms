/*
Implement queue using arrays

10 enqueued to queue
20 enqueued to queue
30 enqueued to queue
40 enqueued to queue
Queue elements: 10 20 30 40 
Front element is 10
Dequeued element is 10
Dequeued element is 20
Queue elements: 30 40 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the queue

// Queue structure
struct Queue {
    int arr[MAX]; // Array to store queue elements
    int front;    // Index of the front element
    int rear;     // Index of the rear element
};

// Function to initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to check if the queue is full
int isFull(struct Queue* queue) {
    return queue->rear == MAX - 1;
}

// Function to enqueue (add) an element to the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue overflow! Cannot enqueue %d\n", value);
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Function to dequeue (remove) an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow! Cannot dequeue\n");
        return -1;
    }
    int value = queue->arr[queue->front];
    if (queue->front == queue->rear) {
        // Queue is now empty
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return value;
}

// Function to peek at the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->arr[queue->front];
}

// Function to print the queue
void printQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    printQueue(&queue);

    printf("Front element is %d\n", peek(&queue));

    printf("Dequeued element is %d\n", dequeue(&queue));
    printf("Dequeued element is %d\n", dequeue(&queue));

    printQueue(&queue);

    return 0;
}
