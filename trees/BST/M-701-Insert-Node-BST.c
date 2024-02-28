/*
701. Insert into a Binary Search Tree
Verified
Contains both iterative and recursive solutions
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

// Approach 1 Iterative
// Function to insert a value into a BST iteratively.
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    // If the root is NULL, create a new node and return it.
    if (root == NULL) {
        return createNode(val);
    }

    // Use a pointer to traverse the tree.
    struct TreeNode* current = root;

    while (1) {
        // If the value is less than the current node's value, move to the left subtree.
        if (val < current->val) {
            // If the left child is NULL, insert the new node here.
            if (current->left == NULL) {
                current->left = createNode(val);
                break;
            } else {
                // Move to the left child.
                current = current->left;
            }
        } else {
            // If the value is greater than or equal to the current node's value, move to the right subtree.
            // If the right child is NULL, insert the new node here.
            if (current->right == NULL) {
                current->right = createNode(val);
                break;
            } else {
                // Move to the right child.
                current = current->right;
            }
        }
    }

    return root;
}

// Approach 2 - Recursive
/* Recursive implementation */
// Function to insert a value into a BST.
struct TreeNode* insertIntoBST_recursive(struct TreeNode* root, int val) {
    // If the root is NULL, create a new node and return it.
    if (root == NULL) {
        return createNode(val);
    }

    // If the value is less than the root's value, recursively insert into the left subtree.
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    }
    // If the value is greater than the root's value, recursively insert into the right subtree.
    else {
        root->right = insertIntoBST(root->right, val);
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

//Approach 3 - iterative
// Another iterative solution - my own
struct TreeNode* insertIntoBST_iterative(struct TreeNode* root, int val) {
    struct TreeNode* node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    struct TreeNode* head = root;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    if (root == NULL)
    {
      return node;
    }
    while(head)
    {
      printf("%d ", head->val);
      if (head->val == val)
      {
        // no need coz its guaranteed but still for completeness
        printf("item already exists");
        free(node);
        return NULL;
      }
      if(val > head->val)
      {
        /* Insert into right subtree */
        if (head->right)
        {
          head = head->right;
        }
        else
        {
          head->right = node;
          printf("Item added om right");
          return root;
        }
      }
      else
      {
        /* Insert into left subtree */
        if (head->left)
        {
          head = head->left;
        }
        else
        {
          head->left = node;
          printf("Item added on left");
          return root;
        }
      }
    }
    return NULL;
   
}
int main() {
    // Example usage:
    struct TreeNode* root = NULL;
    int values[] = {5, 3, 7, 1, 4, 6, 8};

    // Insert values into the BST iteratively.
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        root = insertIntoBST(root, values[i]);
        //root = insertIntoBST_recursive(root, values[i]);
    }

    // Print the inorder traversal of the resulting BST.
    printf("Inorder Traversal: ");
    inorderTraversal(root);

    return 0;
}

