/*
Implement queue using LL

Output:
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

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Queue structure
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue (add) an element to the queue
void enqueue(struct Queue* queue, int data) {
    struct Node* node = newNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
        printf("%d enqueued to queue\n", data);
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
    printf("%d enqueued to queue\n", data);
}

// Function to dequeue (remove) an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow! Cannot dequeue\n");
        return -1;
    }
    struct Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    // If the queue is now empty, set rear to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Function to peek at the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

// Function to print the queue
void printQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = queue->front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
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

