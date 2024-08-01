#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node* next;
};

typedef struct node Node;

Node* push (Node* head, int data)
{
  Node* item = (Node*) malloc(sizeof(Node));
  item->data = data;
  if (head == NULL)
  {
    head = item;
    item->next = NULL;
  }
  else
  {
    item->next = head;
    head = item;
  }
  return head;

}

// SortedMerge Using Recursion
Node* SortedMerge(Node* first, Node* second)
{
  Node* result = NULL;
  if (first == NULL)
  {
    return second;
  }
  else if (second == NULL)
  {
    return first;
  }
  printf("\nSortedMerge first:%d second:%d", first->data, second->data);
  if (first->data <= second->data)
  {
    result = first;
    result->next = SortedMerge(first->next, second);
  }
  else
  {
    result = second;
    result->next = SortedMerge(first, second->next);
  }
  return result;
}

// This function returns the middle element of the Linked List
void midSplit(Node* head, Node** first, Node** second)
{
  *first = head;
  if (head == NULL)
  {
    return;
  }
  Node* fast = head;
  Node* slow = head;
  while(fast->next && fast->next->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  *second = slow->next;
  slow->next = NULL;

  printf("\nLast element of first LL%d First element of 2nd LL:%d", slow->data, (*second)->data);
}

void print_list(Node* head)
{
  printf("\nPrinting Linked List");
  while(head)
  {
    printf(" %d", head->data);
    head = head->next;
  }
}

void mergeSort(Node** headref)
{
  Node *head = *headref;
  Node *first, *second;
  //Base case 0 or 1 nodes
  if ((head == NULL) || (head->next == NULL))
  {
    //printf("\nmergeSort NULL check return");
    return;
  }
  //printf("\nmergeSort %d", head->data);
  // Split Linked List into 2 halves
  midSplit(head, &first, &second);

  //printf("\nAfter midSplit first%d second%d", first->data, second->data);
  mergeSort(&first);
  mergeSort(&second);

  //printf("\nSortedMerge first%d second%d", first->data, second->data);

  *headref = SortedMerge(first, second);
}

int main()
{
  // Note that *first *second instead of Node* head, first, second
  Node *head = NULL;
  for (int i=0; i<10; i++)
  {
    head = push(head, i);
  }
  print_list(head);
  mergeSort(&head);
  print_list(head);
  return 0;
}
