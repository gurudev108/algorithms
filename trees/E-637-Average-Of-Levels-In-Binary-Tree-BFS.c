/*
Leetcode 637. Average of Levels in Binary Tree

Approach: BFS

Output:
Averages of levels:
3.00 14.50 11.00 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// A structure to represent a queue node
typedef struct {
    struct TreeNode** nodes;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->nodes = (struct TreeNode**)malloc(capacity * sizeof(struct TreeNode*));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue a node
void enqueue(Queue* queue, struct TreeNode* node) {
    if (queue->size == queue->capacity) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->nodes[queue->rear] = node;
    queue->size++;
}

// Function to dequeue a node
struct TreeNode* dequeue(Queue* queue) {
    struct TreeNode* node = queue->nodes[queue->front];
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

// Function to calculate the average of each level in a binary tree
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int maxNodes = 1000; // Assumed maximum nodes (height 9 gives 2^10 - 1 = 1023 nodes)
    double* result = (double*)malloc(maxNodes * sizeof(double));
    *returnSize = 0;

    Queue* queue = createQueue(maxNodes);
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        int levelSize = queue->size;
        double levelSum = 0.0;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* currentNode = dequeue(queue);
            levelSum += currentNode->val;

            if (currentNode->left != NULL) {
                enqueue(queue, currentNode->left);
            }
            if (currentNode->right != NULL) {
                enqueue(queue, currentNode->right);
            }
        }

        result[*returnSize] = levelSum / levelSize;
        (*returnSize)++;
    }

    freeQueue(queue);
    return result;
}

// Helper function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Example usage
int main() {
    // Creating the binary tree:
    //        3
    //       / \
    //      9  20
    //         / \
    //        15  7
    struct TreeNode* root = createTreeNode(3);
    root->left = createTreeNode(9);
    root->right = createTreeNode(20);
    root->right->left = createTreeNode(15);
    root->right->right = createTreeNode(7);

    int returnSize;
    double* averages = averageOfLevels(root, &returnSize);

    printf("Averages of levels:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%.2f ", averages[i]);
    }
    printf("\n");

    free(averages);
    return 0;
}

