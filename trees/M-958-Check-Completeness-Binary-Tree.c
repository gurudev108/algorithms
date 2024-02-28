/*
958. Check completeness of a binary tree

This program defines an isCompleteTree function to check if a binary tree is complete. It uses a level-order traversal (BFS) with a queue to visit 
each node in the tree.

Approach - BFS level order traversal which uses queue
By analyzing the definition, we can see that a binary tree is complete if there is no node to the right of the first null node and no node at a 
greater level than the first null node.

It means that if we traverse the tree level by level from left to right and we come across a null node, all subsequent nodes in this traversal 
should be null as well (should not exist). 
The level-order traversal array of a complete binary tree will never have a null node in between non-null nodes.

Breadth-first search (BFS) traversal can be used to perform level-wise traversal. BFS is an algorithm for traversing or searching a graph. 
It traverses in a level-wise manner, i.e., all the nodes at the present level (say l) are explored before moving on to the nodes at the next 
level (l + 1), where a level's number is the distance from a starting node. BFS is implemented with a queue.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new TreeNode.
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to check if a binary tree is complete.
bool isCompleteTree(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }

    // Initialize a flag to mark the completion of the tree.
    bool reachedEnd = false;

    // Create a queue for level order traversal.
    struct TreeNode* queue[1000];
    int front = 0, rear = 0;

    // Enqueue the root.
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* current = queue[front++];

        // If we have encountered a null node, set the flag to true.
        if (current == NULL) {
            reachedEnd = true;
        } else {
            // If we have encountered a non-null node after a null node, the tree is not complete.
            if (reachedEnd) {
                return false;
            }

            // Enqueue the left and right children.
            queue[rear++] = current->left;
            queue[rear++] = current->right;
        }
    }

    return true;
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    // Check if the binary tree is complete.
    if (isCompleteTree(root)) {
        printf("The binary tree is complete.\n");
    } else {
        printf("The binary tree is not complete.\n");
    }

    return 0;
}

