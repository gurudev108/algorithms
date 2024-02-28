/*
write a c program to Check if a binary tree is a mirror image of another binary tree

Approach - 
Based on the symmetric definition, we can use the following rules to check whether two binary trees are a mirror reflection of each other:
The two root nodes have the same value.
The left subtree of one root node is a mirror reflection of the right subtree of the other root node.

To check if a binary tree is a mirror image of another binary tree in C, you can recursively compare the left subtree of one tree with the right subtree of the other tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to check if two binary trees are mirror images of each other.
bool isMirror(struct TreeNode* root1, struct TreeNode* root2) {
    // If both trees are empty, they are mirror images.
    if (root1 == NULL && root2 == NULL) {
        return true;
    }

    // If one tree is empty and the other is not, they are not mirror images.
    if (root1 == NULL || root2 == NULL) {
        return false;
    }

    // Check if the values of the current nodes are equal, and
    // recursively check the left subtree of the first tree with the right subtree of the second tree
    // and the right subtree of the first tree with the left subtree of the second tree.
    return (root1->val == root2->val) &&
           isMirror(root1->left, root2->right) &&
           isMirror(root1->right, root2->left);
}

// Function to check if a binary tree is a mirror image of another binary tree.
bool isSymmetric(struct TreeNode* root) {
    // Call the isMirror function with the root of the tree and itself.
    return isMirror(root, root);
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(2);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right->left = createNode(4);
    root->right->right = createNode(3);

    // Check if the binary tree is a mirror image of itself.
    if (isSymmetric(root)) {
        printf("The binary tree is symmetric.\n");
    } else {
        printf("The binary tree is not symmetric.\n");
    }

    return 0;
}

