/*
Output:
9 
3 15 
20 
7 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Definition for a node in the queue
struct QueueNode {
    struct TreeNode *node;
    int col;
    int row;
};

// Definition for a node in the hash table (used for map)
struct HashNode {
    int col;
    struct TreeNode *node;
    int row;
    struct HashNode *next;
};

#define HASH_SIZE 2048

// Hash table to store nodes by their column index
struct HashNode *hashTable[HASH_SIZE];

// A utility function to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// A utility function to create a new hash node
struct HashNode* newHashNode(int col, struct TreeNode *node, int row) {
    struct HashNode* hashNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    hashNode->col = col;
    hashNode->node = node;
    hashNode->row = row;
    hashNode->next = NULL;
    return hashNode;
}

// A utility function to create a new queue node
struct QueueNode* newQueueNode(struct TreeNode *node, int col, int row) {
    struct QueueNode* queueNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    queueNode->node = node;
    queueNode->col = col;
    queueNode->row = row;
    return queueNode;
}

// A utility function to compute hash value
unsigned int hash(int col) {
    return (unsigned int)(col + HASH_SIZE / 2) % HASH_SIZE;
}

// Insert node into hash table
void insertHashNode(int col, struct TreeNode *node, int row) {
    unsigned int index = hash(col);
    struct HashNode *newNode = newHashNode(col, node, row);
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct HashNode *current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to perform BFS and populate hash table
void bfs(struct TreeNode *root) {
    if (root == NULL) return;
    struct QueueNode *queue[HASH_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = newQueueNode(root, 0, 0);
    
    while (front < rear) {
        struct QueueNode *current = queue[front++];
        insertHashNode(current->col, current->node, current->row);
        
        if (current->node->left != NULL) {
            queue[rear++] = newQueueNode(current->node->left, current->col - 1, current->row + 1);
        }
        if (current->node->right != NULL) {
            queue[rear++] = newQueueNode(current->node->right, current->col + 1, current->row + 1);
        }
    }
}

// Comparator function for sorting the hash nodes
int compare(const void *a, const void *b) {
    struct HashNode *nodeA = *(struct HashNode**)a;
    struct HashNode *nodeB = *(struct HashNode**)b;
    if (nodeA->col == nodeB->col) {
        if (nodeA->row == nodeB->row) {
            return nodeA->node->val - nodeB->node->val;
        }
        return nodeA->row - nodeB->row;
    }
    return nodeA->col - nodeB->col;
}

// Function to get the vertical order traversal
int** verticalOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    
    // Perform BFS to populate hash table
    bfs(root);
    
    // Collect all hash nodes
    struct HashNode *nodes[HASH_SIZE];
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashNode *current = hashTable[i];
        while (current != NULL) {
            nodes[count++] = current;
            current = current->next;
        }
    }
    
    // Sort the hash nodes
    qsort(nodes, count, sizeof(struct HashNode*), compare);
    
    // Determine the range of columns
    int minCol = 0, maxCol = 0;
    for (int i = 0; i < count; i++) {
        if (nodes[i]->col < minCol) {
            minCol = nodes[i]->col;
        }
        if (nodes[i]->col > maxCol) {
            maxCol = nodes[i]->col;
        }
    }
    
    int range = maxCol - minCol + 1;
    int **result = (int**)malloc(range * sizeof(int*));
    *returnColumnSizes = (int*)malloc(range * sizeof(int));
    for (int i = 0; i < range; i++) {
        (*returnColumnSizes)[i] = 0;
        result[i] = (int*)malloc(count * sizeof(int));
    }
    
    // Populate the result array
    for (int i = 0; i < count; i++) {
        int index = nodes[i]->col - minCol;
        result[index][(*returnColumnSizes)[index]++] = nodes[i]->node->val;
    }
    
    *returnSize = range;
    return result;
}

// Driver code
int main() {
    struct TreeNode* root = newNode(3);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);
    
    int returnSize;
    int* returnColumnSizes;
    int** result = verticalOrder(root, &returnSize, &returnColumnSizes);
    
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

