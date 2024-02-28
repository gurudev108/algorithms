/* 
543. Diameter of a Binary Tree
*/

#include <stdio.h>
#include <stdlib.h>

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

// Function to find the maximum of two integers.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the height of a binary tree.
int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Return the height of the current node.
    return 1 + max(leftHeight, rightHeight);
}

// Function to calculate the diameter of a binary tree.
int diameterOfBinaryTree(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // Calculate the height of the left and right subtrees.
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Calculate the diameter recursively for the left and right subtrees.
    int leftDiameter = diameterOfBinaryTree(root->left);
    int rightDiameter = diameterOfBinaryTree(root->right);

    // Return the maximum of the following three values:
    // 1. Diameter of the left subtree.
    // 2. Diameter of the right subtree.
    // 3. Longest path between two nodes which goes through the root.
    return max(max(leftDiameter, rightDiameter), leftHeight + rightHeight);
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    int result = diameterOfBinaryTree(root);

    printf("Diameter of the binary tree: %d\n", result);

    return 0;
}

