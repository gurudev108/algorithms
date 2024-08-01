/*

This program defines a binary tree structure using a TreeNode structure. It creates the binary tree as described in the example and then prints the nodes of the tree level-wise using breadth-first search (BFS) traversal. The printLevelOrder function implements BFS using a queue data structure to process nodes level by level. Finally, the main function creates the binary tree and calls printLevelOrder to print the nodes level-wise.

Just 1 struct TreeNode and queue[1000]

Verified Output:
Nodes in the binary tree level-wise: 1 2 3 4 5 
*/

#include <stdio.h>
#include <stdlib.h>

// Define a structure for the binary tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to print the nodes of the binary tree level-wise
void printLevelOrder(TreeNode* root) {
    // Check if the tree is empty
    if (root == NULL)
        return;

    // Create a queue to store the nodes of the current level
    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // Traverse the tree level by level
    while (front < rear) {
        TreeNode* current = queue[front++];

        // Print the data of the current node
        printf("%d ", current->data);

        // Enqueue the left child if it exists
        if (current->left != NULL)
            queue[rear++] = current->left;

        // Enqueue the right child if it exists
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

int main() {
    // Create the binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->right->left = createNode(4);
    root->right->right = createNode(5);

    // Print the nodes of the binary tree level-wise
    printf("Nodes in the binary tree level-wise: ");
    printLevelOrder(root);
    printf("\n");

    return 0;
}

