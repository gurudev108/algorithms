/*

You are given the head of a singly linked list. The list is represented by L0 → L1 → … → Ln - 1 → Ln.
You need to reorder it to L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → ….
You may not modify the values in the list's nodes. Only the nodes themselves may be changed.

Approach:
Find the middle of the linked list using the slow and fast pointer technique.
Reverse the second half of the linked list.
Merge the two halves by alternating nodes from the first and second halves.

Output:
Printing	1 2 3 4 5 

Middle = 3
Printing first half
Printing	1 2 3 

Printing 2nd half data:5
Printing	5 4 

Printing	1 5 2 4 3 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node* next;
} Node;

void printList(Node* head);
void push(Node** head, int data)
{
  Node* newNode = (Node*) malloc(sizeof(Node));
  newNode->data = data;

  if(*head == NULL)
  {
    newNode->next = NULL;
  }
  else
  {
    newNode->next = *head;
  }
  *head = newNode;
}

Node* findMiddle(Node* head)
{
  if ((head == NULL) || (head->next == NULL))
  {
    return head;
  }
  Node* slow = head;
  Node* fast = head;
  while(fast && fast->next)
  {
    fast = (fast->next)->next;
    slow = slow->next;
  }
  return slow;
}

Node* reverseLL(Node* head)
{
  Node* prev = NULL;
  Node* curr = head;
  Node* next = NULL;

  while(curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

void reorderList(Node* head)
{
  // Step 1 - Find middle
  Node* mid = findMiddle(head);
  printf("\nMiddle = %d", mid->data);

  // Step 2 - Reverse 2nd half
  Node* second = reverseLL(mid->next);
  mid->next = NULL; // Split into 2 halves
  Node* first = head;
  printf("\nPrinting first half");
  printList(first);
  printf("\nPrinting 2nd half data:%d", second->data);
  printList(second);
  // Step 3 - Merge the two halves @TODO @REVISE
  while (second != NULL)
  {
    Node* temp1 = first->next;
    Node* temp2 = second->next;

    first->next = second;
    second->next = temp1;

    first = temp1;
    second = temp2;
  }
}

void printList(Node* head)
{
  printf("\nPrinting\t");
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
  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);
  printList(head);
  reorderList(head);
  printList(head);
}
