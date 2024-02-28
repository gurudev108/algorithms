/*
Get tree level with minimum sum
Given a binary tree, return the level of the tree that has the minimum sum. The level
of a node is defined as the number of connections required to get to the root, with
the root having level zero.

To find the level of a binary tree with the minimum sum, you can perform a level-order traversal (BFS) of the tree while keeping track of the sum at each level. At each level, calculate the sum of values and update the minimum level accordingly
This program defines a minSumLevel function to find the level with the minimum sum in a binary tree using level-order traversal

*/

#include <stdio.h>
#include <stdlib.h>
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

// Function to find the level with the minimum sum in a binary tree.
int minSumLevel(struct TreeNode* root) {
    if (root == NULL) {
        return -1; // No levels in an empty tree.
    }

    int minLevel = 0; // Initialize the minimum level to zero.
    int minSum = INT_MAX; // Initialize the minimum sum to the maximum possible value.

    // Initialize variables for BFS.
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1000);
    int front = 0, rear = 0;

    // Enqueue the root.
    queue[rear++] = root;

    // Start level order traversal.
    while (front < rear) {
        int levelSize = rear - front; // Number of nodes at the current level.
        int levelSum = 0; // Sum of values at the current level.

        // Process nodes at the current level.
        for (int i = 0; i < levelSize; ++i) {
            struct TreeNode* current = queue[front++];
            levelSum += current->val;

            // Enqueue the left and right children if they exist.
            if (current->left != NULL) {
                queue[rear++] = current->left;
            }
            if (current->right != NULL) {
                queue[rear++] = current->right;
            }
        }

        // Update minimum level and sum if needed.
        if (levelSum < minSum) {
            minSum = levelSum;
            minLevel = front - 1; // Levels are zero-based, so use (front - 1) as the minimum level.
        }
    }

    free(queue); // Free the memory allocated for the queue.

    return minLevel;
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(10);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(8);
    root->right->right->left = createNode(6);
    root->right->right->right = createNode(7);

    int result = minSumLevel(root);

    if (result != -1) {
        printf("Level with the minimum sum: %d\n", result);
    } else {
        printf("Tree is empty.\n");
    }

    return 0;
}

