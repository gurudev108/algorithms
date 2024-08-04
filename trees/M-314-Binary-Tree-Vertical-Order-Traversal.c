/*
Leetcode Medium 314 Binary Tree Vertical Order Traversal

Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Approach:

The problem can be solved using a level-order traversal (BFS) with a slight modification. The idea is to keep track of the horizontal distance (column) from the root node for each node. Here's a step-by-step approach:

1. **Data Structure**:
   - Use a queue to facilitate level-order traversal.
   - Use a dictionary (or map) to store nodes based on their column index.

2. **Initialization**:
   - Start with the root node at column 0.
   - Initialize the queue with the root node and its column index (0).

3. **Traversal**:
   - While the queue is not empty, process nodes in a BFS manner.
   - For each node, append its value to the list corresponding to its column index in the dictionary.
   - Add the node's left child to the queue with the column index decremented by 1.
   - Add the node's right child to the queue with the column index incremented by 1.

4. **Result Compilation**:
   - Extract and sort the keys (column indices) from the dictionary.
   - Collect the values from the dictionary based on the sorted keys.


*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Definition for the queue node.
struct QueueNode {
    struct TreeNode *node;
    int column;
    struct QueueNode *next;
};

// Definition for the dictionary node.
struct DictNode {
    int column;
    int *values;
    int size;
    int capacity;
    struct DictNode *next;
};

// Function to create a new tree node.
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new queue node.
struct QueueNode* createQueueNode(struct TreeNode *node, int column) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->node = node;
    newNode->column = column;
    newNode->next = NULL;
    return newNode;
}

// Function to enqueue a queue node.
void enqueue(struct QueueNode **front, struct QueueNode **rear, struct TreeNode *node, int column) {
    struct QueueNode* newNode = createQueueNode(node, column);
    if (*rear) {
        (*rear)->next = newNode;
        *rear = newNode;
    } else {
        *front = *rear = newNode;
    }
}

// Function to dequeue a queue node.
struct QueueNode* dequeue(struct QueueNode **front) {
    if (!(*front)) return NULL;
    struct QueueNode* temp = *front;
    *front = (*front)->next;
    //free(temp);
    return temp;
}

// Function to create a new dictionary node.
struct DictNode* createDictNode(int column) {
    struct DictNode* newNode = (struct DictNode*)malloc(sizeof(struct DictNode));
    newNode->column = column;
    newNode->values = (int*)malloc(10 * sizeof(int));
    newNode->size = 0;
    newNode->capacity = 10;
    newNode->next = NULL;
    return newNode;
}

// Function to add value to the dictionary node.
void addToDictNode(struct DictNode *dictNode, int val) {
    if (dictNode->size == dictNode->capacity) {
        dictNode->capacity *= 2;
        dictNode->values = (int*)realloc(dictNode->values, dictNode->capacity * sizeof(int));
    }
    dictNode->values[dictNode->size++] = val;
}

// Function to add or update dictionary.
void addToDict(struct DictNode **dict, int column, int val) {
    struct DictNode *current = *dict;
    struct DictNode *prev = NULL;
    while (current && current->column < column) {
        prev = current;
        current = current->next;
    }
    if (current && current->column == column) {
        addToDictNode(current, val);
    } else {
        struct DictNode *newNode = createDictNode(column);
        addToDictNode(newNode, val);
        newNode->next = current;
        if (prev) {
            prev->next = newNode;
        } else {
            *dict = newNode;
        }
    }
}

// Function to perform the vertical order traversal.
int** verticalOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        *columnSizes = NULL;
        return NULL;
    }

    struct QueueNode *front = NULL, *rear = NULL;
    struct DictNode *dict = NULL;
    int minColumn = INT_MAX, maxColumn = INT_MIN;

    enqueue(&front, &rear, root, 0);

    while (front) {
        struct QueueNode *queueNode = dequeue(&front);
        struct TreeNode *currentNode = queueNode->node;
        int column = queueNode->column;

        free(queueNode);

        addToDict(&dict, column, currentNode->val);
        if (column < minColumn) minColumn = column;
        if (column > maxColumn) maxColumn = column;

        if (currentNode->left) enqueue(&front, &rear, currentNode->left, column - 1);
        if (currentNode->right) enqueue(&front, &rear, currentNode->right, column + 1);
    }

    int numColumns = maxColumn - minColumn + 1;
    *returnSize = numColumns;
    *columnSizes = (int*)malloc(numColumns * sizeof(int));
    int **result = (int**)malloc(numColumns * sizeof(int*));

    for (int i = 0; i < numColumns; ++i) {
        struct DictNode *current = dict;
        while (current && current->column != minColumn + i) {
            current = current->next;
        }
        if (current) {
            (*columnSizes)[i] = current->size;
            result[i] = current->values;
        }
    }

    return result;
}

// Example usage
int main() {
    struct TreeNode* root = createTreeNode(3);
    root->left = createTreeNode(9);
    root->right = createTreeNode(20);
    root->right->left = createTreeNode(15);
    root->right->right = createTreeNode(7);

    int* columnSizes;
    int returnSize;
    int** result = verticalOrder(root, &columnSizes, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        for (int j = 0; j < columnSizes[i]; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Cleanup code should be added here to free allocated memory

    return 0;
}

/*
 Complexity Analysis

- **Time Complexity**: O(N), where N is the number of nodes in the tree. Each node is visited exactly once.
- **Space Complexity**: O(N), for the queue and the dictionary. The queue can hold up to N/2 nodes in the worst case (all leaf nodes), and the dictionary holds the nodes grouped by columns. 

This approach ensures a level-order traversal while keeping track of the horizontal distance, allowing us to gather nodes in vertical order.i
*/
