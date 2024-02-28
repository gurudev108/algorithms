/*
98. Validate BST
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

// Function to check if a binary tree is a binary search tree.
bool isValidBSTUtil(struct TreeNode* root, long long minVal, long long maxVal) {
    if (root == NULL) {
        return true;
    }

    // Check if the current node's value is within the valid range.
    if (root->val <= minVal || root->val >= maxVal) {
        return false;
    }

    // Recursively check the left and right subtrees with updated min and max values.
    return isValidBSTUtil(root->left, minVal, root->val) &&
           isValidBSTUtil(root->right, root->val, maxVal);
}

bool isValidBST(struct TreeNode* root) {
    // Use long long to handle edge cases where the node values are INT_MAX or INT_MIN.
    return isValidBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(2);
    root->left = createNode(1);
    root->right = createNode(3);

    // Check if the binary tree is a binary search tree.
    if (isValidBST(root)) {
        printf("The binary tree is a binary search tree.\n");
    } else {
        printf("The binary tree is not a binary search tree.\n");
    }

    return 0;
}

