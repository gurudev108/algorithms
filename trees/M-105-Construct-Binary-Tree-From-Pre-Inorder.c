/*
Leetcode 105. Construct binary tree from PreOrder and Inorder traversal

Approach - Recursion

1. Create a helper function for recursion
2. First element in the preorder is the root node.
   2.1 Find the index of this root node in the inorder 
   2.2 Left tree = start to index of the root node
   2.3 Right tree = index + 1 to end
3. Return root

Verified Output:
9 3 15 20 7 
*/
 
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Helper function to find the index of a value in the inorder array
int findIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive helper function to build the tree
struct TreeNode* buildTreeHelper(int* preorder, int preorderStart, int preorderEnd, int* inorder, int inorderStart, int inorderEnd) {
    if (preorderStart > preorderEnd || inorderStart > inorderEnd) {
        return NULL;
    }
    
    // The first element in preorder is the root node
    int rootValue = preorder[preorderStart];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootValue;
    root->left = NULL;
    root->right = NULL;
    
    // Find the index of the root in the inorder array
    int rootIndex = findIndex(inorder, inorderStart, inorderEnd, rootValue);
    
    // Calculate the number of elements in the left subtree
    int leftSubtreeSize = rootIndex - inorderStart;
    
    // Recursively build the left and right subtrees
    root->left = buildTreeHelper(preorder, preorderStart + 1, preorderStart + leftSubtreeSize, inorder, inorderStart, rootIndex - 1);
    root->right = buildTreeHelper(preorder, preorderStart + leftSubtreeSize + 1, preorderEnd, inorder, rootIndex + 1, inorderEnd);
    
    return root;
}

// Main function to build the tree
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    return buildTreeHelper(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1);
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
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};
    int size = sizeof(preorder) / sizeof(preorder[0]);
    
    struct TreeNode* root = buildTree(preorder, size, inorder, size);
    
    // Print the tree in inorder traversal to verify the result
    printInorder(root);
    
    // Free the allocated memory
    freeTree(root);
    
    return 0;
}

