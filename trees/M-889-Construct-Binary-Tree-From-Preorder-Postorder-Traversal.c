/*

Leetcode Medium 889. Construct Binary Tree from Preorder and Postorder Traversal

Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.

If there exist multiple answers, you can return any of them.

Output: 
4 2 5 1 6 3 7

Verified on Leetcode 50-10

*/
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Helper function to find the index of a value in the postorder array
int findIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive helper function to build the tree
struct TreeNode* buildTreeHelper(int* preorder, int preorderStart, int preorderEnd, int* postorder, int postorderStart, int postorderEnd) {
    if (preorderStart > preorderEnd || postorderStart > postorderEnd) {
        return NULL;
    }
    
    // The first element in preorder is the root node
    int rootValue = preorder[preorderStart];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootValue;
    root->left = NULL;
    root->right = NULL;
    
    // If there's only one element, it's a leaf node
    if (preorderStart == preorderEnd) {
        return root;
    }
    
    // Find the index of the left child in the postorder array
    int leftChildValue = preorder[preorderStart + 1];
    int leftChildIndex = findIndex(postorder, postorderStart, postorderEnd - 1, leftChildValue);
    
    // Calculate the number of elements in the left subtree
    int leftSubtreeSize = leftChildIndex - postorderStart + 1;
    
    // Recursively build the left and right subtrees
    root->left = buildTreeHelper(preorder, preorderStart + 1, preorderStart + leftSubtreeSize, postorder, postorderStart, leftChildIndex);
    root->right = buildTreeHelper(preorder, preorderStart + leftSubtreeSize + 1, preorderEnd, postorder, leftChildIndex + 1, postorderEnd - 1);
    
    return root;
}

// Main function to build the tree
struct TreeNode* buildTree(int* preorder, int preorderSize, int* postorder, int postorderSize) {
    return buildTreeHelper(preorder, 0, preorderSize - 1, postorder, 0, postorderSize - 1);
}

// Helper function to print the tree in inorder traversal (for testing)
void printInorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printInorder(root->left);
    printf("%d ", root->val);
    printInorder(root->right);
}

// Helper function to free the allocated memory (for testing)
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int size = sizeof(preorder) / sizeof(preorder[0]);
    
    struct TreeNode* root = buildTree(preorder, size, postorder, size);
    
    // Print the tree in inorder traversal to verify the result
    printInorder(root);
    
    // Free the allocated memory
    freeTree(root);
    
    return 0;
}

