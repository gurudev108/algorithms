#include "include/trees.h"
/* Not working on Leetcode

236. Lowest common ancestor of a Binary Tree
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/

To find the lowest common ancestor (LCA) of two given nodes in a binary tree, you can use a recursive approach. 
The LCA is the first common ancestor of the two nodes as you traverse the tree from the root.
In this program, the lowestCommonAncestor function recursively searches for the lowest common ancestor in the left and right subtrees.

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

// Function to find the lowest common ancestor in a BST.
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    // If the root is NULL or matches either of the given nodes, it is the LCA.
    if (root == NULL || root == p || root == q) {
        return root;
    }

    // Recursively search for the LCA in the left and right subtrees.
    struct TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);

    // If both left and right subtrees have a result, the current root is the LCA.
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }

    // If only one subtree has a result, pass that result up the tree.
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(20);
    root->left = createNode(10);
    root->right = createNode(30);
    root->left->left = createNode(5);
    root->left->right = createNode(15);
    root->right->left = createNode(25);
    root->right->right = createNode(35);

    struct TreeNode* node1 = root->left->left;   // Node with value 5
    struct TreeNode* node2 = root->left->right;  // Node with value 15

    struct TreeNode* lca = lowestCommonAncestor(root, node1, node2);

    if (lca != NULL) {
        printf("Lowest Common Ancestor: %d\n", lca->val);
    } else {
        printf("No Lowest Common Ancestor found.\n");
    }

    return 0;
}

