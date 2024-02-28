/*
450. Delete a Node in BST
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

// Function to find the minimum value node in a BST.
struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node with a given value from a BST.
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    // If the root is NULL, the key is not present.
    if (root == NULL) {
        return root;
    }

    // If the key is smaller than the root's key, it lies in the left subtree.
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    // If the key is larger than the root's key, it lies in the right subtree.
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    // If the key is equal to the root's key, this is the node to be deleted.
    else {
        // Case 1- Node with only one child or no child.
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2- Node with two children: Get the inorder successor (smallest in the right subtree).
        struct TreeNode* temp = findMin(root->right);

        // Copy the inorder successor's value to this node.
        root->val = temp->val;

        // ##IMP##  - Delete the inorder successor.
        root->right = deleteNode(root->right, temp->val);
    }

    return root;
}

// Function to print the inorder traversal of a BST (for testing purposes).
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

int main() {
    // Example usage:
    struct TreeNode* root = NULL;
    int values[] = {5, 3, 7, 1, 4, 6, 8};

    // Insert values into the BST.
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        root = insertIntoBST(root, values[i]);
    }

    // Print the inorder traversal of the original BST.
    printf("Inorder Traversal (Original): ");
    inorderTraversal(root);
    printf("\n");

    // Delete a node (e.g., node with value 3) from the BST.
    root = deleteNode(root, 3);

    // Print the inorder traversal of the modified BST.
    printf("Inorder Traversal (Modified): ");
    inorderTraversal(root);

    return 0;
}

