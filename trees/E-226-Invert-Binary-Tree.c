/* 
https://leetcode.com/problems/invert-binary-tree/description/
226. Invert Binary Tree
Easy

Daily Coding Problem: Problem #596 [Medium]
Invert a binary tree
For example, given the following tree:

    a
   / \
  b   c
 / \  /
d   e f
should become:

  a
 / \
 c  b
 \  / \
  f e  d
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to invert a binary tree.
struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL) return NULL;

    // Swap the left and right children.
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively invert the left and right subtrees.
    invertTree(root->left);
    invertTree(root->right);

    return root;
}

// Helper function to create a new tree node.
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to print the tree in inorder traversal.
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

// Example usage
int main() {
    // Creating an example tree:
    //       4
    //      / \
    //     2   7
    //    / \ / \
    //   1  3 6  9
    struct TreeNode* root = newNode(4);
    root->left = newNode(2);
    root->right = newNode(7);
    root->left->left = newNode(1);
    root->left->right = newNode(3);
    root->right->left = newNode(6);
    root->right->right = newNode(9);

    printf("Original tree inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    invertTree(root);

    printf("Inverted tree inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}



