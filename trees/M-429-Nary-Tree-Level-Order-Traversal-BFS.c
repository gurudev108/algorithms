/*
Leetcode M 429 Nary Tree Level Order Traversal

Approach: BFS

Verified Output:
Level Order Traversal:
1 
3 2 4 
5 6 
*/
#include <stdio.h>
#include <stdlib.h>

// Definition for a Node.
struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

// A structure to represent a queue
typedef struct {
    struct Node** nodes;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->nodes = (struct Node**)malloc(capacity * sizeof(struct Node*));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue a node
void enqueue(Queue* queue, struct Node* node) {
    if (queue->size == queue->capacity) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->nodes[queue->rear] = node;
    queue->size++;
}

// Function to dequeue a node
struct Node* dequeue(Queue* queue) {
    struct Node* node = queue->nodes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return node;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to free the queue
void freeQueue(Queue* queue) {
    free(queue->nodes);
    free(queue);
}

// Function to perform level order traversal of an N-ary tree
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int maxNodes = 10000; // Assumed maximum nodes
    int** result = (int**)malloc(maxNodes * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxNodes * sizeof(int));
    *returnSize = 0;

    Queue* queue = createQueue(maxNodes);
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        int levelSize = queue->size;
        int* currentLevel = (int*)malloc(levelSize * sizeof(int));

        for (int i = 0; i < levelSize; i++) {
            struct Node* currentNode = dequeue(queue);
            currentLevel[i] = currentNode->val;
            for (int j = 0; j < currentNode->numChildren; j++) {
                if (currentNode->children[j] != NULL) {
                    enqueue(queue, currentNode->children[j]);
                }
            }
        }

        result[*returnSize] = currentLevel;
        (*returnColumnSizes)[*returnSize] = levelSize;
        (*returnSize)++;
    }

    freeQueue(queue);
    return result;
}

// Helper function to create a new node
struct Node* createNode(int val, int numChildren) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->numChildren = numChildren;
    newNode->children = (struct Node**)malloc(numChildren * sizeof(struct Node*));
    return newNode;
}

// Example usage
int main() {
    struct Node* root = createNode(1, 3);
    root->children[0] = createNode(3, 2);
    root->children[1] = createNode(2, 0);
    root->children[2] = createNode(4, 0);
    root->children[0]->children[0] = createNode(5, 0);
    root->children[0]->children[1] = createNode(6, 0);

    int returnSize;
    int* returnColumnSizes;
    int** result = levelOrder(root, &returnSize, &returnColumnSizes);

    printf("Level Order Traversal:\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}

