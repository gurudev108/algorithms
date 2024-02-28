/*
7.2 Convert sorted array to BST
Given a sorted array, convert it into a height-balanced binary search tree.

https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
Easy
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

// Function to convert a sorted array into a height-balanced BST.
struct TreeNode* sortedArrayToBST(int* nums, int start, int end) {
    if (start > end) {
        return NULL;
    }

    // Calculate the middle index.
    int mid = start + (end - start) / 2;

    // Create the root node with the middle element.
    struct TreeNode* root = createNode(nums[mid]);

    // Recursively build the left and right subtrees.
    root->left = sortedArrayToBST(nums, start, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, end);

    return root;
}

// Function to perform an in-order traversal of the constructed tree (for verification).
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

int main() {
    // Example usage:
    int nums[] = {-10, -3, 0, 5, 9};
    int size = sizeof(nums) / sizeof(nums[0]);

    struct TreeNode* root = sortedArrayToBST(nums, 0, size - 1);

    printf("In-order Traversal of Constructed BST: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}


