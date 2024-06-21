/*
Leetcode Easy - Reverse a Linked List

Output
push: head=0x0x0 data=5
push: head=0x0x600002e88030 data=4
push: head=0x0x600002e88040 data=3
push: head=0x0x600002e88050 data=2
push: head=0x0x600002e88060 data=1
Print LL head:0x0x600002e88070 1  2  3  4  5 
Print LL head:0x0x600002e88030 5  4  3  2  1 % 
*/

#include "stdio.h"
#include "stdlib.h"

typedef struct ListNode {
  int data;
  struct ListNode* next;
} ListNode;

ListNode* push(ListNode *head, int data)
{
  printf("\npush: head=0x%p data=%d", head, data);
  ListNode* curr = (ListNode*) malloc (sizeof(ListNode));

  if (curr == NULL)
  {
    printf("\nError - Node not added - low memory");
    return NULL;
  }
  curr->data = data;
  curr->next = head;

  head = curr;
  return head;
}

void print(ListNode *head)
{
  ListNode* curr = head;
  printf("\nPrint LL head:0x%p", head);
  while (curr)
  {
    printf(" %d ", curr->data);
    curr = curr->next;
  }
}
ListNode* reverse (ListNode *head)
{
  ListNode *prev = NULL;
  ListNode *curr = head;
  ListNode *next = NULL;

  /* NO need to do any checks 
  if (head == NULL)
  {
    printf("\nEmpty LL");
    return NULL;
  }
  next = curr->next;

  if (next == NULL)
  {
    printf("\nOnly 1 node");
    return curr;
  }
  */

  //@IMP - While loop on curr
  while(curr!=NULL)
  {
    next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }

  head = prev;

  return head;
}


int main()
{
  ListNode *head = NULL;
  head = push (head, 5);
  head = push (head, 4);
  head = push (head, 3);
  head = push (head, 2);
  head = push (head, 1);
  print(head);

  head = reverse(head);
  print(head);

  return 0;
}
