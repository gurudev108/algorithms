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

// Function to print all nodes at a given level in a binary tree.
void printNodesAtLevel(struct TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    // If the current level is 1, print the value of the node.
    if (level == 1) {
        printf("%d ", root->val);
    }
    // If the current level is greater than 1, recursively print nodes at the left and right subtrees.
    else if (level > 1) {
        printNodesAtLevel(root->left, level - 1);
        printNodesAtLevel(root->right, level - 1);
    }
}

// Function to calculate the height of a binary tree.
int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Return the height of the current node.
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

// Function to print all nodes at a given level in a binary tree.
void printNodesAtGivenLevel(struct TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }

    int treeHeight = height(root);

    // Validate the given level.
    if (level < 1 || level > treeHeight) {
        printf("Invalid level\n");
        return;
    }

    // Call the recursive function to print nodes at the given level.
    printNodesAtLevel(root, level);
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int levelToPrint = 2;

    printf("Nodes at level %d: ", levelToPrint);
    printNodesAtGivenLevel(root, levelToPrint);

    return 0;
}

