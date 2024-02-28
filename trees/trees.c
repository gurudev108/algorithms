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
Min height?
Max height?
Num of leaves
Generic - size(), isEmpty(), elements(), 
Positional - positions(), swapElements(p,q) replaceElement(p,e)
Query - isRoot(), isInternal(), isExternal()
Accessor - root(), parent(p), children(p), leftChild(p), rightChild(p), sibling(p)


Ordered Dictionaries - can be implemented using BST 
Recall dictionary has key value pair (HASHING) Use key to insert, search and delete an element
Ordered dict - element with min key - min(), max(), predecessor(S,k), successor(S,k)
Recall on hashing we only do equality check with keys
Here we expect more - there is some ordering and we can compare keys

Searching in BST - Search(T,11). 2 approaches
- Recursive approach
- Iterative approach
BST (Minimum/Maximum) - TreeMinimum
Successor - Given x, find the next (smallest key greater than key[x] _ TreeSuccessor(x)
Case 1 - right subtree is non empty
Case 2- right subtree of x is empty - lowest ancestor of x whose left child is also an ancestor of x 
*/

#define MAX(a,b) ((a>b)?a:b)

typedef struct Node {
  struct Node* left;
  int data;
  struct Node* right;
} Node;

/* Functions implemented */
int getHeight(Node* head);
Node* createBST(int data);
Node* insert(Node* head, int data);
Node* delete(Node* item); // TODO
void preOrderTraversal(Node* head);
void inOrderTraversal(Node* head);
void postOrderTraversal(Node* head);
void printArithmeticExpression(Node* head); // TODO
Node* search(Node* head, int data);
Node* iterativeSearch(Node* head, int data);
Node* minimum(Node* head);
Node* maximum(Node* head);
Node* successor(Node* head, Node* item);


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

Node* delete(Node* item) {
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
/*
Euler Tour Traversal - draw a line starting from the node on the left and draw the line 
covering everythign on the left, bottom and rise up.
Each node visited three times, 1. on the left, 2. from below, 3. on the right, except
leaf node visited twice
Pre/Post/In order traversals are special cases of Euler tour traversal

Question - Print an arithmetic expression 
         +
      +     /
    x  2   1 3
  x   7
3   +
   2 5
Euler's walk - ((((3x
1. Print "(" before traversing the left subtree
2. Traverse it - Print the value of the node
3. Traverse the right subtree, print ")" after traversing it
*/
void printArithmeticExpression(Node* head) {

}


/*
Building tree from pre and in order 
 Given the preorder and inorder traversal of a binary tree, we can uniquely determine the tree
 Preorder abcdfge
 Inorder cbfdgae

 Compute the post order traversal of the tree
 Flag out an error if the sequences that they could not possibly be a pre/in of a tree
 You could use recursion 

 Also possible with post and in order. Last node visited un post order is the root. This can be
 used to split the inorder traversal to identify the left and right subtrees

Given a pre and post - you can NOT uniquely determine a tree. There could be 
2 trees that could have the same 
 Preorder abc
 Postorder cba 
  a        a
 b          b
  c        c

Special case - if each internal node of a binary tree has atleast 2 children
then tree can be determined from pre and post order
Preorder abcdfge
Post cfgdbea
	a
     b     e

With just the pre order its not possible to uniquely determine coz there 
are many possibilities of trees
*/



/*
TREE-SEARCH(x,k)
*/
Node* search(Node* head, int data) {
  if (head == NULL) {
    printf("\nRecursive Search Item:%d not found", data);
    return NULL;
  }
  if (data == head->data) {
    printf("\nRecursive Search Item:%d found", data);
    return head;
  }
  else if (data > head->data) search(head->right, data);
  else if (data < head->data) search(head->left, data);

  return head; // fix compile warning

}

/*
ITERATIVE-TREE-SEARCH(x,k)
*/
Node* iterativeSearch(Node* head, int data) {
  if (head == NULL) return NULL;
while(head) {
    if(head->data == data) {
      printf("\nIterative Search Item:%d found", data);
      return head;
    } else if (data > head->data) {
      head = head->right;
    } else {
      head = head->left;
    }
  }
  printf("\nIterative Search Item:%d not found", data);
  return NULL;
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
  printf("\nIn Order Tree Traversal");
  inOrderTraversal(head);
  printf("\nPre Order Tree Traversal");
  preOrderTraversal(head);
  printf("\nPost Order Tree Traversal");
  postOrderTraversal(head);

  printf("\nMaximum =%d", (maximum(head))->data);
  printf("\nMinimum =%d", (minimum(head))->data);

  search(head, 20);
  search(head, 16);
  search(head, 22);
  iterativeSearch(head, 20);
  iterativeSearch(head, 16);
  iterativeSearch(head, 22);

  printf("\nHeight of tree = %d", getHeight(head));
  return 0;
}
