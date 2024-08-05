/*

Lowest common ancestor - Iterative using parent pointer

Approach:
Key Steps
Parent Pointers Initialization:
Perform a level-order traversal (BFS) of the tree to populate the parent pointers for each node.
Find Ancestors:
For both nodes p and q, find their ancestors and store them in separate sets.
Find the LCA:
Start from one of the nodes and move up using the parent pointers until an ancestor is found in the set of ancestors of the other node.

Output:
LCA of nodes 5 and 4 is: 5

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Definition for a stack to keep track of tree nodes and parent pointers
typedef struct Stack {
    TreeNode *node;
    TreeNode *parent;
    struct Stack *next;
} Stack;

// Function to create a new tree node
TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to push a node and its parent onto the stack
void push(Stack **stack, TreeNode *node, TreeNode *parent) {
    Stack *newNode = (Stack*)malloc(sizeof(Stack));
    newNode->node = node;
    newNode->parent = parent;
    newNode->next = *stack;
    *stack = newNode;
}

// Function to pop a node and its parent from the stack
void pop(Stack **stack, TreeNode **node, TreeNode **parent) {
    if (*stack == NULL) {
        *node = NULL;
        *parent = NULL;
        return;
    }
    *node = (*stack)->node;
    *parent = (*stack)->parent;
    Stack *temp = *stack;
    *stack = (*stack)->next;
    free(temp);
}

// Function to find the LCA using parent pointers
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Dictionary-like structure to store parent pointers
    TreeNode* parent[1000] = {NULL};

    // Stack for BFS
    Stack *stack = NULL;
    push(&stack, root, NULL);

    // Set parent pointers using BFS
    while (stack) {
        TreeNode *node, *nodeParent;
        pop(&stack, &node, &nodeParent);
        if (node) {
            parent[node->val] = nodeParent;
            if (node->left) {
                push(&stack, node->left, node);
            }
            if (node->right) {
                push(&stack, node->right, node);
            }
        }
    }

    // Track ancestors of p
    TreeNode *ancestorsP[1000] = {NULL};
    int indexP = 0;
    while (p) {
        ancestorsP[indexP++] = p;
        p = parent[p->val];
    }

    // Track ancestors of q and find LCA
    while (q) {
        // Check if q is in the ancestors of p
        for (int i = 0; i < indexP; i++) {
            if (q == ancestorsP[i]) {
                return q;
            }
        }
        q = parent[q->val];
    }

    return NULL; // If no LCA is found
}

// Main function to demonstrate the LCA function
int main() {
    // Constructing the binary tree
    //        3
    //       / \
    //      5   1
    //     / \ / \
    //    6  2 0  8
    //      / \
    //     7   4
    TreeNode* root = newNode(3);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(6);
    root->left->right = newNode(2);
    root->right->left = newNode(0);
    root->right->right = newNode(8);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(4);

    TreeNode* p = root->left;         // Node 5
    TreeNode* q = root->left->right->right; // Node 4

    TreeNode* lca = lowestCommonAncestor(root, p, q);
    if (lca != NULL) {
        printf("LCA of nodes %d and %d is: %d\n", p->val, q->val, lca->val);
    } else {
        printf("LCA not found.\n");
    }

    return 0;
}

/*
Explanation
Explanation
TreeNode Structure:
Represents a node in the binary tree with an integer value val and pointers to the left and right children.
Stack Structure:
A simple stack implementation is used to perform BFS and store nodes along with their parents.
newNode Function:
Creates a new tree node with the specified value.
push and pop Functions:
Used to manage the stack operations.
lowestCommonAncestor Function:
Initializes parent pointers using BFS.
Finds and stores ancestors of p and checks for common ancestors with q.
main Function:
Constructs a sample binary tree, specifies two nodes p and q, and finds their LCA using the iterative approach.
This implementation is suitable for scenarios where modifying the tree structure to include parent pointers directly is not possible. It provides an efficient way to find the LCA using additional data structures.
*/