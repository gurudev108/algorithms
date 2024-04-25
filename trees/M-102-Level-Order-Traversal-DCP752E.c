#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Structure for a queue node
struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

// Structure for queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new queue node
struct QueueNode* newQueueNode(struct TreeNode* data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}
// Function to create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to enqueue a tree node to the queue
void enqueue(struct Queue* q, struct TreeNode* data) {
    struct QueueNode* temp = newQueueNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Function to dequeue a tree node from the queue
struct TreeNode* dequeue(struct Queue* q) {
    if (q->front == NULL)
        return NULL;
    struct TreeNode* temp = q->front->data;
    struct QueueNode* tempNode = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(tempNode);
    return temp;
}

// Function to perform level order traversal of a binary tree
void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct Queue* q = createQueue();
    enqueue(q, root);

    while (q->front != NULL) {
        struct TreeNode* current = dequeue(q);
        printf("%d ", current->val);

        if (current->left != NULL)
            enqueue(q, current->left);
        if (current->right != NULL)
            enqueue(q, current->right);
    }

    free(q);
}

int main() {
    // Example binary tree
    //struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    // Create the binary tree
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->right->left = createNode(4);
    root->right->right = createNode(5);
/*
    root->val = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->left->left = root->left->right = root->right->left = root->right->right = NULL;
*/
    printf("Level Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    // Free allocated memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

