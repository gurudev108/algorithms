/*
Lowest Common Ancestor BST - recursive. Also see Iterative using parent pointers.

Approach
Problem Statement Recap
Given a binary tree and two nodes p and q, find their LCA. The LCA of two nodes p and q in a binary tree is defined as the lowest node that has both p and q as descendants (a node can be a descendant of itself).

Approach
Recursive Traversal:
We recursively traverse the tree.
If we find either p or q, we return that node to the caller.
If both left and right subtrees return a non-null node, then the current node is the LCA.
If only one of the subtrees returns a non-null node, propagate the non-null return value upwards.
Base Case:
If the current node is NULL, return NULL.
If the current node matches either p or q, return the current node.
Recursive Case:
Recursively search in the left and right subtrees.
If both searches return non-null values, the current node is the LCA.

Output:
LCA of nodes 5 and 4 is: 5
*/

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Helper function to create a new tree node
TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the Lowest Common Ancestor
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base case
    if (root == NULL || root == p || root == q) {
        return root;
    }

    // Recursively search in the left and right subtrees
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // If both left and right are non-null, root is the LCA
    if (left != NULL && right != NULL) {
        return root;
    }

    // Otherwise, return the non-null child
    return (left != NULL) ? left : right;
}

// Main function to demonstrate the LCA function
int main() {
    // Constructing the binary tree
    //        3
    //       / \
    //      5   1
    //     / \ / \
    //    6  2 0  8
    //      / \
    //     7   4
    TreeNode* root = newNode(3);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(6);
    root->left->right = newNode(2);
    root->right->left = newNode(0);
    root->right->right = newNode(8);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(4);

    TreeNode* p = root->left;         // Node 5
    TreeNode* q = root->left->right->right; // Node 4

    TreeNode* lca = lowestCommonAncestor(root, p, q);
    if (lca != NULL) {
        printf("LCA of nodes %d and %d is: %d\n", p->val, q->val, lca->val);
    } else {
        printf("LCA not found.\n");
    }

    return 0;
}

