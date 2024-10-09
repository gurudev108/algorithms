/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given the root of a binary tree, return a deepest node. For example, in the following tree, return d.

    a
   / \
  b   c
 /
d
*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Structure for queue used in BFS
struct Queue {
    struct Node* node;
    struct Queue* next;
};

// Function to create a new queue node
struct Queue* createQueueNode(struct Node* node) {
    struct Queue* newQueueNode = (struct Queue*)malloc(sizeof(struct Queue));
    newQueueNode->node = node;
    newQueueNode->next = NULL;
    return newQueueNode;
}

// Function to enqueue a node into the queue
void enqueue(struct Queue** head, struct Node* node) {
    struct Queue* newQueueNode = createQueueNode(node);
    if (*head == NULL) {
        *head = newQueueNode;
    } else {
        struct Queue* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newQueueNode;
    }
}

// Function to dequeue a node from the queue
struct Node* dequeue(struct Queue** head) {
    if (*head == NULL) {
        return NULL;
    }
    struct Queue* temp = *head;
    *head = (*head)->next;
    struct Node* node = temp->node;
    free(temp);
    return node;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* head) {
    return (head == NULL);
}

// Function to find the deepest node in the binary tree using BFS
struct Node* findDeepestNode(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    struct Queue* queue = NULL;  // Initialize an empty queue
    enqueue(&queue, root);       // Enqueue the root node
    struct Node* currentNode = NULL;

    while (!isQueueEmpty(queue)) {
        currentNode = dequeue(&queue);  // Dequeue a node

        // Enqueue its children if they exist
        if (currentNode->left != NULL) {
            enqueue(&queue, currentNode->left);
        }
        if (currentNode->right != NULL) {
            enqueue(&queue, currentNode->right);
        }
    }

    // The last node dequeued is the deepest node
    return currentNode;
}

int main() {
    // Create the binary tree
    struct Node* root = createNode('a');
    root->left = createNode('b');
    root->right = createNode('c');
    root->left->left = createNode('d');

    // Find the deepest node
    struct Node* deepestNode = findDeepestNode(root);
    if (deepestNode != NULL) {
        printf("The deepest node is: %c\n", deepestNode->data);
    } else {
        printf("The tree is empty.\n");
    }

    return 0;
}

