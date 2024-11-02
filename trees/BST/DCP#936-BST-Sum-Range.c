/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a binary search tree and a range [a, b] (inclusive), return the sum of the elements of the binary search tree within the range.

For example, given the following tree:

    5
   / \
  3   8
 / \ / \
2  4 6  10
and the range [4, 9], return 23 (5 + 4 + 6 + 8).
*/

#include <stdio.h>
#include <stdlib.h>

// Define the structure of the BST node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Recursive function to insert a new node in BST
Node* insert(Node* root, int data) {
    if (root == NULL) return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to calculate the sum of nodes in the given range [a, b]
int rangeSumBST(Node* root, int a, int b) {
    if (root == NULL) return 0;
    
    int sum = 0;
    
    // If the current node is in the range, include it in the sum
    if (root->data >= a && root->data <= b)
        sum += root->data;

    // If root->data > a, then only recurse left
    if (root->data > a)
        sum += rangeSumBST(root->left, a, b);

    // If root->data < b, then only recurse right
    if (root->data < b)
        sum += rangeSumBST(root->right, a, b);

    return sum;
}

int main() {
    // Constructing the example tree
    Node* root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 8);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 6);
    root = insert(root, 10);

    // Define the range [a, b]
    int a = 4, b = 9;

    // Calculate the sum of nodes within the range
    int result = rangeSumBST(root, a, b);
    printf("Sum of nodes in range [%d, %d]: %d\n", a, b, result);

    return 0;
}
