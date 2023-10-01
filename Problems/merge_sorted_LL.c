/* Problem statement: Given two sorted linked lists, merge them so the resulting linked list is also sorted */

/* Merge 2 sorted linked list */

/* Merge two sorted LL */

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
  int data;
  struct Node* next;
} Node;

/* NEED DOUBLE POINTER ONLY in PUSH */
void push(Node** head, int data)
{
  Node *item = (Node*) malloc(sizeof(Node));
  item->data = data;
  item->next = *head;
  *head = item;
}

void print(Node* head)
{
  printf("\nPrinting List with head=%p", head);
  while(head)
  {
    printf(" %d", head->data);
    head = head->next;
  }
}

/* DOUBLE PTR NOT NEEDED HERE */
Node* mergeSortedList(Node* head1, Node* head2)
{
  Node result;
  Node* tail = &result;

  while(1)
  {
    if(NULL == head1)
    {
      tail->next = head2;
      break;
    }
    else if (NULL == head2)
    {
      tail->next = head1;
      break;
    }

    if(head1->data > head2->data)
    {
      tail->next = head2;
      head2 = head2->next;
      tail = tail->next;
      tail->next = NULL;
      
    }
    else
    {
      tail->next = head1;
      head1 = head1->next;
      tail = tail->next;
      tail->next = NULL;
    }
  }
  // IMP - What to return here - BE AWARE
  return result.next;
}

int main()
{
  Node *head1 = NULL;
  Node *head2 = NULL;
  Node *result = NULL;
  push (&head1, 12);
  push (&head1, 10);
  push (&head1, 8);
  push (&head1, 5);

  print(head1);

  push (&head2, 6);
  push (&head2, 4);
  push (&head2, 1);

  print(head2);

  result = mergeSortedList(head1, head2);

  print(result);


}

