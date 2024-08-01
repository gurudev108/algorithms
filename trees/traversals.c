#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Definition for the queue node.
struct QueueNode {
    struct TreeNode *treeNode;
    struct QueueNode *next;
};

// Function to create a new tree node.
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new queue node.
struct QueueNode* createQueueNode(struct TreeNode *treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

// Function to enqueue a queue node.
void enqueue(struct QueueNode **front, struct QueueNode **rear, struct TreeNode *treeNode) {
    struct QueueNode* newNode = createQueueNode(treeNode);
    if (*rear) {
        (*rear)->next = newNode;
        *rear = newNode;
    } else {
        *front = *rear = newNode;
    }
}

// Function to dequeue a queue node.
struct TreeNode* dequeue(struct QueueNode **front) {
    if (!(*front)) return NULL;
    struct QueueNode* temp = *front;
    struct TreeNode* treeNode = temp->treeNode;
    *front = (*front)->next;
    free(temp);
    return treeNode;
}

// Function to perform BFS on the binary tree.
void bfs(struct TreeNode* root) {
    if (!root) return;

    struct QueueNode *front = NULL, *rear = NULL;
    enqueue(&front, &rear, root);

    while (front) {
        struct TreeNode* currentNode = dequeue(&front);
        printf("%d ", currentNode->val);

        if (currentNode->left) enqueue(&front, &rear, currentNode->left);
        if (currentNode->right) enqueue(&front, &rear, currentNode->right);
    }
}

// Example usage
int main() {
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("BFS traversal of the binary tree:\n");
    bfs(root);

    // Cleanup code should be added here to free allocated memory

    return 0;
}

