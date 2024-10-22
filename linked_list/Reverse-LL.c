/*
1. Reverse a Linked List
2. Reverse a Doubly Linked List
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node* next;

  #ifdef DOUBLY_LL
  struct Node* prev;
  #endif
} Node;

void reverse(Node **head)
{
  Node *prev = NULL;
  Node *curr = *head;
  Node *next = NULL;
  while(curr)
  {
    next = curr->next;
    curr->next = prev;
    #ifdef DOUBLY_LL
    curr->prev = next;
    #endif
    prev = curr;
    curr = next;
  }
  *head = prev;
}

void push(Node **head, int data)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  if (*head == NULL)
  {
    *head = node;
    node->next = NULL;
    #ifdef DOUBLY_LL
    node->prev = NULL;
    #endif
  }
  else
  {
    Node* tmp = *head;
    *head = node;
    node->next = tmp;
    #ifdef DOUBLY_LL
    node->prev = NULL;
    #endif
  }
}

void print(Node *head)
{
  printf("Printing \t");
  while(head)
  {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

int main()
{
  Node* head = NULL;
  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 4);
  push(&head, 5);

  print(head);

  reverse(&head);

  print(head);
  return 0;
}
