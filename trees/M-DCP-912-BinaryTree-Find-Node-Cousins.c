/*

Good morning! Here's your coding interview problem for today.

This problem was asked by Yext.

Two nodes in a binary tree can be called cousins if they are on the same level of the tree but have different parents. For example, in the following diagram 4 and 6 are cousins.

    1
   / \
  2   3
 / \   \
4   5   6
Given a binary tree and a particular node, find all cousins of that node.

Verified Output:
Cousins of node 4: 6 7 
*/
#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Structure for queue used in BFS
struct Queue {
    struct Node* node;
    int level;
    struct Node* parent;
    struct Queue* next;
};

// Function to create a new queue node
struct Queue* createQueueNode(struct Node* node, int level, struct Node* parent) {
    struct Queue* newQueueNode = (struct Queue*)malloc(sizeof(struct Queue));
    newQueueNode->node = node;
    newQueueNode->level = level;
    newQueueNode->parent = parent;
    newQueueNode->next = NULL;
    return newQueueNode;
}

// Function to enqueue a node into the queue
void enqueue(struct Queue** head, struct Node* node, int level, struct Node* parent) {
    struct Queue* newQueueNode = createQueueNode(node, level, parent);
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
struct Node* dequeue(struct Queue** head, int* level, struct Node** parent) {
    if (*head == NULL) {
        return NULL;
    }
    struct Queue* temp = *head;
    *head = (*head)->next;
    struct Node* node = temp->node;
    *level = temp->level;
    *parent = temp->parent;
    free(temp);
    return node;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* head) {
    return (head == NULL);
}

// Function to find all cousins of a given node
void findCousins(struct Node* root, int target) {
    if (root == NULL) {
        return;
    }

    struct Queue* queue = NULL;
    enqueue(&queue, root, 0, NULL);  // Enqueue the root node
    struct Node* targetParent = NULL;
    int targetLevel = -1;

    // First BFS pass: Find the target node's level and parent
    while (!isQueueEmpty(queue)) {
        int level;
        struct Node* parent;
        struct Node* currentNode = dequeue(&queue, &level, &parent);

        if (currentNode->data == target) {
            targetLevel = level;
            targetParent = parent;
            break;
        }

        // Enqueue the left and right children
        if (currentNode->left != NULL) {
            enqueue(&queue, currentNode->left, level + 1, currentNode);
        }
        if (currentNode->right != NULL) {
            enqueue(&queue, currentNode->right, level + 1, currentNode);
        }
    }

    // If the target node is not found, return
    if (targetLevel == -1) {
        printf("Target node not found in the tree.\n");
        return;
    }

    // Second BFS pass: Find all nodes at the same level as the target but with different parents
    queue = NULL;  // Reset queue for second BFS
    enqueue(&queue, root, 0, NULL);

    printf("Cousins of node %d: ", target);
    int foundCousin = 0;

    while (!isQueueEmpty(queue)) {
        int level;
        struct Node* parent;
        struct Node* currentNode = dequeue(&queue, &level, &parent);

        if (level == targetLevel && parent != targetParent) {
            printf("%d ", currentNode->data);
            foundCousin = 1;
        }

        // Enqueue the left and right children
        if (currentNode->left != NULL) {
            enqueue(&queue, currentNode->left, level + 1, currentNode);
        }
        if (currentNode->right != NULL) {
            enqueue(&queue, currentNode->right, level + 1, currentNode);
        }
    }

    if (!foundCousin) {
        printf("No cousins found.\n");
    }
    printf("\n");
}

int main() {
    // Create the binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Find cousins of a given target node
    int target = 4;  // Example: finding cousins of node 4
    findCousins(root, target);

    return 0;
}

