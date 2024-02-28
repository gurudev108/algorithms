/*
Notes - Couldn't understand

7.3 Construct all BSTs with n nodes
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

// Function to clone a binary tree.
struct TreeNode* cloneTree(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    struct TreeNode* newNode = createNode(root->val);
    newNode->left = cloneTree(root->left);
    newNode->right = cloneTree(root->right);

    return newNode;
}

// Function to generate all BSTs with n nodes.
struct TreeNode** generateBSTs(int start, int end, int* returnSize) {
    struct TreeNode** result = NULL;

    if (start > end) {
        // Return an array with a single NULL element representing an empty tree.
        result = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
        result[0] = NULL;
        *returnSize = 1;
        return result;
    }

    *returnSize = 0;
    result = (struct TreeNode**)malloc(sizeof(struct TreeNode*));

    for (int i = start; i <= end; ++i) {
        int leftSize, rightSize;
        struct TreeNode** leftTrees = generateBSTs(start, i - 1, &leftSize);
        struct TreeNode** rightTrees = generateBSTs(i + 1, end, &rightSize);

        for (int j = 0; j < leftSize; ++j) {
            for (int k = 0; k < rightSize; ++k) {
                // Create a new tree with i as the root.
                struct TreeNode* root = createNode(i);
                root->left = cloneTree(leftTrees[j]);
                root->right = cloneTree(rightTrees[k]);

                // Add the new tree to the result array.
                result = (struct TreeNode**)realloc(result, (*returnSize + 1) * sizeof(struct TreeNode*));
                result[*returnSize] = root;
                (*returnSize)++;
            }
        }

        free(leftTrees);
        free(rightTrees);
    }

    return result;
}

// Function to perform an in-order traversal of a binary tree (for verification).
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

// Function to free memory allocated for a binary tree.
void freeTree(struct TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // Example usage:
    int n = 5; // Number of nodes

    int returnSize;
    struct TreeNode** result = generateBSTs(1, n, &returnSize);

    printf("All possible BSTs with %d nodes:\n", n);
    for (int i = 0; i < returnSize; ++i) {
        printf("Tree %d: ", i + 1);
        inorderTraversal(result[i]);
        printf("\n");
        freeTree(result[i]);
    }

    free(result);

    return 0;
}

