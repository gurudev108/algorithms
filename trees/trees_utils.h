// tree_utils.h

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function declarations.
struct TreeNode* createTreeNode(int val);
struct TreeNode* insertIntoBST(struct TreeNode* root, int val);
void inOrderTraversal(struct TreeNode* root);

#endif // TREE_UTILS_H

