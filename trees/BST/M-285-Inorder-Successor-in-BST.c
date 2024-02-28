/*
285. Inorder Successor in BST

Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST. 
If the given node has no in-order successor in the tree, return null.

The successor of a node p is the node with the smallest key greater than p.val.

Approach1 - Iterative
Case 1- If right child exists this is easy and we can just find the minimum element in the right subtree of p 
which is the left most child. 
Case 2- Otherwise we need to find the parent of p who is the left child of its parent (successor). 

Approach2 - Iterative with parent pointer
With parent pointer Case 2 becomes easy and we can just traverse up using the parent pointer. The parent pointer is used to travel up until a node is found which is the left child of its parent. The parent of such a node is the successor.

Approach3 - Recursive without parent pointer
The idea is to search for the given node in the tree and update the successor to the current node before visiting its left subtree. If the node is found in the BST, we return the node with the minimum key in its right subtree. If the right subtree of the node doesn't exist, then the in-order successor is one of its ancestors, which has already been updated while searching for the given key.

*/

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}BSTNode;

// Function to find the minimum value node in a BST
struct TreeNode *findMin(struct TreeNode *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Approach 1 
// Function to find the inorder successor of a node in a BST
struct TreeNode *inorderSuccessor(struct TreeNode *root, struct TreeNode *target) {
    // If the right subtree of the target node is not null,
    // then the inorder successor is the leftmost node in the right subtree.
    if (target->right != NULL) {
        return findMin(target->right);
    }

    // If the right subtree is null, then the inorder successor is the lowest
    // ancestor of the target node whose left child is also an ancestor of the target.
    struct TreeNode *successor = NULL;
    while (root != NULL) {
        if (target->val < root->val) {
            successor = root;
            root = root->left;
        } else if (target->val > root->val) {
            root = root->right;
        } else {
            break; // Target node found, exit the loop
        }
    }

    return successor;
}

//Approach 2- Using parent pointer
BSTNode* inorderSuccessor(BSTNode* root, BSTNode* target) 
{
    if (target->right != NULL)
        return findMin(target->right);

    BSTNode* prev = target->parent;
    while (target != NULL && target == prev->right) 
    {
        target = prev;
        prev = prev->parent;
    }
    return prev;
}

//Approach 3 - Recursive without parent pointer
// Not verified but should be good
// https://www.enjoyalgorithms.com/blog/inorder-successor-in-binary-search-tree
BSTNode* inorderSuccessor(BSTNode* root, BSTNode* succ, BSTNode* x) 
{
    if (root == NULL)
        return succ;

    if (x->key == root->key) 
    {
        if (x->right != nullptr)
            return bstMinimum(x->right);
    } 
    else if (x->key < root->key) 
    {
        succ = root;
        return inorderSuccessor(root->left, succ, x);
    } 
    else
        return inorderSuccessor(root->right, succ, x);

    return succ;
}
