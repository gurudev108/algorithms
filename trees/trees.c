/* 
Leetcode 285 Inorder Successor in BST

*/

#include<stddef.h> // for NULL
#include<stdlib.h> // for malloc
#include<stdio.h> // for printf

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
TREE-MINIMUM(x)
*/
Node* minimum(Node* head) {
  if (head == NULL) return NULL;
  while(head->left) {
    head = head->left;
  }
  return head;
}

/*
TREE-MAXIMUM(x)
*/
Node* maximum(Node* head) {
  if (head == NULL) return NULL;

  while(head->right) {
    head = head->right;
  }
  return head;
}

/*
TREE-SUCCESSOR(x) - node with the smallest key greater than key[x]
  if(right[x] != NULL) return TreeMinimum(right[x])
  while (x = right[parent[x])
    x = parent[x]
  return parent[x]  
*/
Node* successor(Node* head, Node* item) {
  Node* result = NULL;
  if (head == NULL) return NULL;
  // Case 1 - Right child is not NULL, then successor is the leftmost node in the right subtree
  if (item->right) return minimum(item->right);
  // Case 2 - No right child, find the lowest ancestor of item whose left child is also an ancestor of item
  while (head) {
    if (head->data == item->data) {
      printf("\nSuccessor found");
      return result;
    }
    if (item->data > head->data) {
      head = head->right;
    } else if (item->data < head->data) {
      result = head;
      head = head->left;
    }
  } 
  return result; // fix compile warning
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
  printf("\nSuccessor is :%d", successor(head, 8));
  successor(head, 8);

  return 0;
}
