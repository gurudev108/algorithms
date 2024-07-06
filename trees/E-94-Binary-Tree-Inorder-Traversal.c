/*
Leetcode 94. Binary Tree Inorder Traversal

Verified output:
BST created with data=10 at address=0x600003efd1e0
Item:2 added at 0x600003efd200
Item:4 added at 0x600003efd220
Item:6 added at 0x600003efd240
Item:8 added at 0x600003efd260
Item:12 added at 0x600003efd280
Item:14 added at 0x600003efd2a0
Item:16 added at 0x600003efd2c0
Item:18 added at 0x600003efd2e0
Item:15 added at 0x600003efd300
In Order Tree Traversal 2 4 6 8 10 12 14 15 16 18
Pre Order Tree Traversal 10 2 4 6 8 12 14 16 15 18
Post Order Tree Traversal 8 6 4 2 15 18 16 14 12 10
Height of tree = 5%  
*/

#include<stddef.h> // for NULL
#include<stdlib.h> // for malloc
#include<stdio.h> // for printf
/* 
Example of Binary Tree
** Arithmetic expressions ((4*3)/2+4/3) ** 
** Disk usage du command in Linux - postOrder traversal add left + right + visit node v**

Complete binary tree - if at ith level there are 2^i nodes (full)
In a tree of height h, leaves are at level h, num of leaves is 2^h
num of internal nodes = 2^h - 1, total num of nodes = 2^(h+1) - 1
*/

#define MAX(a,b) ((a>b)?a:b)

typedef struct Node {
  struct Node* left;
  int data;
  struct Node* right;
} Node;

int getHeight(Node* head)
{
  if (head == NULL)
  {
    return 0;
  }
  else
  {
    int l_height = getHeight(head->left);
    int r_height = getHeight(head->right);
    return MAX(l_height, r_height) + 1;
  }
}
Node* createBST(int data) {
  Node* head = (Node*)malloc(sizeof(Node));
  if (head == NULL) {
    printf("\nNo memory");
    return NULL;
  }
  head->data = data;
  head->left = NULL;
  head->right = NULL;
  printf("\nBST created with data=%d at address=%p", data, head);
  return head;
}

Node* insert(Node* head, int data) {

  if (head == NULL) return NULL;
  Node* item = (Node*) malloc(sizeof(Node));
  while (head) {
    if (data == head->data) {
      printf("\nItem already exists - returning without adding");
      free(item);
      return NULL;
    }
    if (data > head->data) {
      if (head->right) {
        head = head->right;
      } else {
        head->right = item;
        (head->right)->data = data;
        printf("\nItem:%d added at %p", data, head->right);
        return item;
      }
    }
    else if (data < head->data) {
      if (head->left) {
        head = head->left;
      } else {
        head->left = item;
        (head->left)->data = data;
        printf("\nItem:%d added at %p", data, head->left);
        return item;
      }
    }  
  }
  return item;
}

/*
Tree Traversal - Pre Post Inorder
preOrder(v)  - Visit node v. For each child w of v do recursively perform preOrder(v)

postOrder(v) - for each child w of v do recursively peform postOrder(v), then visit node v 
  Usage - Evaluating arithmetic expression, operator is evaluated when we visit the node

*/
void preOrderTraversal(Node* head) {
  if (head == NULL) return;
  else {
    printf(" %d", head->data); // visit node v
    preOrderTraversal(head->left);
    preOrderTraversal(head->right);
  }
}

void inOrderTraversal(Node* head) {
  if (head == NULL) return;
  else {
    inOrderTraversal(head->left);
    printf(" %d", head->data);
    inOrderTraversal(head->right);
  }
}

void postOrderTraversal(Node* head) {
  if (head == NULL) return;
  else {
    postOrderTraversal(head->left);
    postOrderTraversal(head->right);
    printf(" %d", head->data);
  }
}

int main() {

  Node *head = createBST(10);

  insert(head, 2);
  insert(head, 4);
  insert(head, 6);
  insert(head, 8);
  insert(head, 12);
  insert(head, 14);
  insert(head, 16);
  insert(head, 18);
  insert(head, 15);
  printf("\nIn Order Tree Traversal");
  inOrderTraversal(head);
  printf("\nPre Order Tree Traversal");
  preOrderTraversal(head);
  printf("\nPost Order Tree Traversal");
  postOrderTraversal(head);

  printf("\nHeight of tree = %d", getHeight(head));
  return 0;
}
