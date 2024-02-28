/*
7.1 Find floor and ceiling
Given a binary search tree, find the floor and ceiling of a given integer. The floor is
the highest element in the tree less than or equal to an integer, while the ceiling is
the lowest element in the tree greater than or equal to an integer.
If either value does not exist, return None.
*/
#include <stdio.h>
#include <stdlib.h>

// Definition for a binary search tree (BST) node.
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

// Function to find the floor and ceiling in a BST.
void findFloorCeiling(struct TreeNode* root, int target, int* floor, int* ceiling) {
    while (root != NULL) {
        if (root->val == target) {
            *floor = target;
            *ceiling = target;
            return;
        } else if (root->val > target) {
            // Current node is greater than the target, update ceiling and move to the left subtree.
            *ceiling = root->val;
            root = root->left;
        } else {
            // Current node is less than the target, update floor and move to the right subtree.
            *floor = root->val;
            root = root->right;
        }
    }
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(8);
    root->left = createNode(4);
    root->right = createNode(12);
    root->left->left = createNode(2);
    root->left->right = createNode(6);
    root->right->left = createNode(10);
    root->right->right = createNode(14);

    int target = 5;
    int floorValue = -1; // Initialize with a value that indicates none.
    int ceilingValue = -1; // Initialize with a value that indicates none.

    findFloorCeiling(root, target, &floorValue, &ceilingValue);

    if (floorValue != -1) {
        printf("Floor of %d: %d\n", target, floorValue);
    } else {
        printf("No floor found for %d.\n", target);
    }

    if (ceilingValue != -1) {
        printf("Ceiling of %d: %d\n", target, ceilingValue);
    } else {
        printf("No ceiling found for %d.\n", target);
    }

    return 0;
}

