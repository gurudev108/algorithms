/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields, it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list; it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to get_pointer and dereference_pointer functions that converts between nodes and memory addresses.

Approach
XOR can be used to store both prev and next, which means when we have to fetch next we can just do XOR(prev, curr->both)

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  struct Node* both;
  int data;
} Node;

Node* XOR(Node* a, Node* b)
{
  return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}
void add (Node** head, int data)
{
  Node* node = (Node*) malloc(sizeof(Node));
  node->data = data;

  if(*head == NULL)
  {
    /* Empty Linked List */
    printf("Empty Linked List\n");
    node->both = NULL;
    *head = node; 
  }
  else
  {
    /* Traverse the list to find the last node */
    Node* prev = NULL;
    Node* curr = *head;
    Node* next;

    while(XOR(prev, curr->both))
    {
      next = XOR(prev, curr->both);
      prev = curr;
      curr = next;
    }
    /* curr points to the last node, and node is added in the end */
    curr->both = XOR(prev, node);
    node->both = curr;
  }
}

Node* get(Node* head, int index)
{
  Node* prev = NULL;
  Node* curr = head;
  Node* next;
  int count = 0;

  while (curr!=NULL && count<index )
  {
    next = XOR(curr->both, prev);
    prev = curr;
    curr = next;
    count++;
  }
  return curr;

}

void print(Node* head)
{
  Node* prev = NULL;
  Node* curr = head;
  Node* next;
  while (XOR(curr->both, prev))
  {
    printf("%d", curr->data);
    next = XOR(curr->both, prev);
    prev = curr;
    curr = next;
  }
}

int main()
{
  Node* head = NULL;
  add(&head, 1);
  add(&head, 2);
  add(&head, 3);
  add(&head, 4);
  printf("Printing List\n");
  print(head);
  
  Node* node = get(head, 1);
  if (node != NULL)
  {
    printf("Node at index 2: %d\n", node->data);
  } 
  else
  {
    printf("Node not found at index 2\n");
  }

  return 0;
}  
  
