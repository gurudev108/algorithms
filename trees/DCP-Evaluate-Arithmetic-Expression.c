/*
DCP - Evaluate arithmetic tree

*/

#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new TreeNode.
struct TreeNode* createNode(char val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to evaluate an arithmetic expression tree.
int evaluateExpression(struct TreeNode* root) {
    if (root == NULL) {
        fprintf(stderr, "Error: NULL node encountered.\n");
        exit(EXIT_FAILURE);
    }

    // ##IMP## If the node is a leaf (operand), return its value.
    if (root->left == NULL && root->right == NULL) {
        return root->val - '0';
    }

    // Recursively evaluate left and right subtrees.
    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    // Apply the operator.
    switch (root->val) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                fprintf(stderr, "Error: Division by zero.\n");
                exit(EXIT_FAILURE);
            }
            return leftValue / rightValue;
        default:
            fprintf(stderr, "Error: Unknown operator '%c'.\n", root->val);
            exit(EXIT_FAILURE);
    }
}

int main() {
    // Example usage:
    struct TreeNode* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('-');
    root->left->left = createNode('3');
    root->left->right = createNode('2');
    root->right->left = createNode('5');
    root->right->right = createNode('4');

    int result = evaluateExpression(root);

    printf("Result of the arithmetic expression: %d\n", result);

    return 0;
}

