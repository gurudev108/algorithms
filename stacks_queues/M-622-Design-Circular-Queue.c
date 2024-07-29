/* 
Leetcode M 622 Design Circular Queue

Output:
Enqueue 1: 1
Enqueue 2: 1
Enqueue 3: 1
Enqueue 4: 0
Rear: 3
Is Full: 1
Dequeue: 1
Enqueue 4: 1
Rear: 4

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int head;
    int tail;
    int size;
    int capacity;
} MyCircularQueue;

// Function to create a circular queue of given capacity.
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *queue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    queue->data = (int*)malloc(k * sizeof(int));
    queue->head = -1;
    queue->tail = -1;
    queue->size = 0;
    queue->capacity = k;
    return queue;
}

// Function to insert an element into the circular queue. Returns true if successful.
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (obj->size == obj->capacity) {
        return false;
    }
    if (obj->size == 0) {
        obj->head = 0;
        obj->tail = 0;
    } else {
        obj->tail = (obj->tail + 1) % obj->capacity;
    }
    obj->data[obj->tail] = value;
    obj->size++;
    return true;
}

// Function to delete an element from the circular queue. Returns true if successful.
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (obj->size == 0) {
        return false;
    }
    if (obj->size == 1) {
        obj->head = -1;
        obj->tail = -1;
    } else {
        obj->head = (obj->head + 1) % obj->capacity;
    }
    obj->size--;
    return true;
}

// Function to get the front item from the queue. Returns the element or -1 if the queue is empty.
int myCircularQueueFront(MyCircularQueue* obj) {
    if (obj->size == 0) {
        return -1;
    }
    return obj->data[obj->head];
}

// Function to get the last item from the queue. Returns the element or -1 if the queue is empty.
int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj->size == 0) {
        return -1;
    }
    return obj->data[obj->tail];
}

// Function to check if the circular queue is empty.
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->size == 0;
}

// Function to check if the circular queue is full.
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return obj->size == obj->capacity;
}

// Function to free the memory allocated for the circular queue.
void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->data);
    free(obj);
}

int main() {
    MyCircularQueue* queue = myCircularQueueCreate(3);
    printf("Enqueue 1: %d\n", myCircularQueueEnQueue(queue, 1));
    printf("Enqueue 2: %d\n", myCircularQueueEnQueue(queue, 2));
    printf("Enqueue 3: %d\n", myCircularQueueEnQueue(queue, 3));
    printf("Enqueue 4: %d\n", myCircularQueueEnQueue(queue, 4));  // Should be false
    printf("Rear: %d\n", myCircularQueueRear(queue));
    printf("Is Full: %d\n", myCircularQueueIsFull(queue));
    printf("Dequeue: %d\n", myCircularQueueDeQueue(queue));
    printf("Enqueue 4: %d\n", myCircularQueueEnQueue(queue, 4));
    printf("Rear: %d\n", myCircularQueueRear(queue));
    printf("Front: %d\n", myCircularQueueFront(queue));
    myCircularQueueFree(queue);
    return 0;
}

