/*

Same as DCP#936

Leetcode E 938 Range sum of BST
Given the root node of a binary search tree and two integers low and high, 
return the sum of values of all nodes with a value in the inclusive range [low, high].

Approach:
1. Recursive
2. Iterative using stack

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new TreeNode.
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Stack implementation
struct Stack {
    struct TreeNode** data;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (struct TreeNode**)malloc(stack->capacity * sizeof(struct TreeNode*));
    return stack;
}

bool isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct TreeNode* node) {
    stack->data[++stack->top] = node;
}

struct TreeNode* pop(struct Stack* stack) {
    return stack->data[stack->top--];
}

int rangeSumBSTIterative(struct TreeNode* root, int low, int high) {
    if (root == NULL) return 0;

    int sum = 0;
    struct Stack* stack = createStack(1000);
    push(stack, root);

    while (!isStackEmpty(stack)) {
        struct TreeNode* node = pop(stack);

        if (node->val >= low && node->val <= high) {
            sum += node->val;
        }

        if (node->left && node->val > low) {
            push(stack, node->left);
        }

        if (node->right && node->val < high) {
            push(stack, node->right);
        }
    }

    free(stack->data);
    free(stack);
    return sum;
}


int rangeSumBSTRecursive(struct TreeNode* root, int low, int high) {
    if (root == NULL) return 0;

    if (root->val < low) {
        return rangeSumBSTRecursive(root->right, low, high);
    } else if (root->val > high) {
        return rangeSumBSTRecursive(root->left, low, high);
    } else {
        return root->val + rangeSumBSTRecursive(root->left, low, high) + rangeSumBSTRecursive(root->right, low, high);
    }
}

int main() {
    // Create a sample BST:
    //        5
    //       /  \
    //      3   8
    //     / \ / \
    //    2  4 6  10
    struct TreeNode *root = createTreeNode(5);
    root->left = createTreeNode(3);
    root->right = createTreeNode(8);
    root->left->left = createTreeNode(2);
    root->left->right = createTreeNode(4);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(10);

    int low = 4, high = 9;
    
    // Compute and print the range sum.
    int result_recursive = rangeSumBSTRecursive(root, low, high);
    int result_iterative = rangeSumBSTIterative(root, low, high);
    printf("Range Sum of BST for range [%d, %d]: recursive %d iterative %d \n", low, high, result_recursive, result_iterative);
    
    return 0;
}

