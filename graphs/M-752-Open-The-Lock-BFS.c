/*
Leetcode M 752. Open the lock

Approach - BFS since shortest route to target. 

Output:
Minimum turns to open the lock: 6
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 10000

typedef struct {
    char code[5];
    int steps;
} Node;

typedef struct {
    Node* nodes;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->nodes = (Node*)malloc(capacity * sizeof(Node));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue a node
void enqueue(Queue* queue, const char* code, int steps) {
    if (queue->size == queue->capacity) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    strcpy(queue->nodes[queue->rear].code, code);
    queue->nodes[queue->rear].steps = steps;
    queue->size++;
}

// Function to dequeue a node
Node dequeue(Queue* queue) {
    Node node = queue->nodes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return node;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to free the queue
void freeQueue(Queue* queue) {
    free(queue->nodes);
    free(queue);
}

// Function to increment a digit in the lock
void increment(char* code, int i) {
    code[i] = (code[i] - '0' + 1) % 10 + '0';
}

// Function to decrement a digit in the lock
void decrement(char* code, int i) {
    code[i] = (code[i] - '0' - 1 + 10) % 10 + '0';
}

// Function to determine the minimum number of moves to open the lock
int openLock(char** deadends, int deadendsSize, char* target) {
    char start[] = "0000";
    bool visited[MAX_SIZE] = { false };
    
    for (int i = 0; i < deadendsSize; i++) {
        int index = (deadends[i][0] - '0') * 1000 + 
                    (deadends[i][1] - '0') * 100 + 
                    (deadends[i][2] - '0') * 10 + 
                    (deadends[i][3] - '0');
        visited[index] = true;
    }
    
    if (visited[0]) {
        return -1; // Start is a deadend
    }

    Queue* queue = createQueue(MAX_SIZE);
    enqueue(queue, start, 0);
    visited[0] = true;

    while (!isQueueEmpty(queue)) {
        Node node = dequeue(queue);
        if (strcmp(node.code, target) == 0) {
            freeQueue(queue);
            return node.steps;
        }
        
        for (int i = 0; i < 4; i++) {
            char original = node.code[i];

            increment(node.code, i);
            int index = (node.code[0] - '0') * 1000 +
                        (node.code[1] - '0') * 100 +
                        (node.code[2] - '0') * 10 +
                        (node.code[3] - '0');
            if (!visited[index]) {
                enqueue(queue, node.code, node.steps + 1);
                visited[index] = true;
            }
            node.code[i] = original;

            decrement(node.code, i);
            index = (node.code[0] - '0') * 1000 +
                    (node.code[1] - '0') * 100 +
                    (node.code[2] - '0') * 10 +
                    (node.code[3] - '0');
            if (!visited[index]) {
                enqueue(queue, node.code, node.steps + 1);
                visited[index] = true;
            }
            node.code[i] = original;
        }
    }

    freeQueue(queue);
    return -1;
}

// Example usage
int main() {
    char* deadends[] = {"0201", "0101", "0102", "1212", "2002"};
    int deadendsSize = 5;
    char target[] = "0202";
    int result = openLock(deadends, deadendsSize, target);
    printf("Minimum turns to open the lock: %d\n", result);
    return 0;
}

