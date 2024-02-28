/*
Accepted
105. Construct binary tree from preorder and inorder traversal
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

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

// Helper function to construct the binary tree from preorder and inorder traversals.
struct TreeNode* buildTreeHelper(int* preorder, int preorderSize, int* inorder, int inorderSize, int* preorderIndex) {
    if (*preorderIndex >= preorderSize || inorderSize == 0) {
        return NULL;
    }

    // Pick the current root from the preorder traversal.
    struct TreeNode* root = createNode(preorder[*preorderIndex]);

    // Find the index of the root in the inorder traversal.
    int rootIndex;
    for (rootIndex = 0; rootIndex < inorderSize; ++rootIndex) {
        if (inorder[rootIndex] == root->val) {
            break;
        }
    }

    // Recursively build the left and right subtrees.
    (*preorderIndex)++;
    root->left = buildTreeHelper(preorder, preorderSize, inorder, rootIndex, preorderIndex);
    root->right = buildTreeHelper(preorder, preorderSize, inorder + rootIndex + 1, inorderSize - rootIndex - 1, preorderIndex);

    return root;
}

// Function to construct the binary tree from preorder and inorder traversals.
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int preorderIndex = 0;
    return buildTreeHelper(preorder, preorderSize, inorder, inorderSize, &preorderIndex);
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
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};

    int preorderSize = sizeof(preorder) / sizeof(preorder[0]);
    int inorderSize = sizeof(inorder) / sizeof(inorder[0]);

    struct TreeNode* root = buildTree(preorder, preorderSize, inorder, inorderSize);

    printf("Inorder Traversal of Constructed Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

