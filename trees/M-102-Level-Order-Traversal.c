/* 
This program uses a queue-based approach to perform a level-order traversal of 
the binary tree iteratively. It iterates through each level of the tree, 
enqueueing each node's children and dequeuing and printing each node's value. 
*/

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Definition for a queue node
struct QueueNode {
    struct TreeNode* treeNode;
    struct QueueNode* next;
};

// Definition for a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new queue node
struct QueueNode* newQueueNode(struct TreeNode* treeNode) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = treeNode;
    temp->next = NULL;
    return temp;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Function to enqueue a treeNode to the queue
void enQueue(struct Queue* q, struct TreeNode* treeNode) {
    struct QueueNode* temp = newQueueNode(treeNode);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

// Function to dequeue a treeNode from the queue
struct TreeNode* deQueue(struct Queue* q) {
    if (q->front == NULL)
        return NULL;

    struct TreeNode* temp = q->front->treeNode;
    struct QueueNode* tempQueueNode = q->front;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(tempQueueNode);
    return temp;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

// Function to perform level order traversal of the binary tree
void levelOrder(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct Queue* q = createQueue();
    enQueue(q, root);

    while (!isEmpty(q)) {
        int levelSize = q->rear - q->front + 1; // Current level size

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = deQueue(q);
            printf("%d ", node->val);

            if (node->left != NULL)
                enQueue(q, node->left);

            if (node->right != NULL)
                enQueue(q, node->right);
        }
    }

    // Freeing memory
    free(q->front);
    free(q->rear);
    free(q);
}

// Function to create a new binary tree node
struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(!node) printf("malloc failed");
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    printf("newTreeNode returning");
    return node;
}

int main() {
    // Example usage
    printf("Start\n");
    struct TreeNode* root = newTreeNode(3);
    printf("\nRoot created");
    root->left = newTreeNode(9);
    root->right = newTreeNode(20);
    root->right->left = newTreeNode(15);
    root->right->right = newTreeNode(7);

    printf("Level Order Traversal: ");
    levelOrder(root);
    printf("\n");

    // Freeing memory
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

