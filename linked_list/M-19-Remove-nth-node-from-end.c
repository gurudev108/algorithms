/*
https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int num;
     struct Node *next;
};

typedef struct Node Node;

Node* removeNthFromEnd(Node* head, int n)
{
    Node* first = head
    for(int i=0; i<n; i++)
    {
      
    return head;
}

void print (Node* head)
{
  int count = 0;
  printf("\nhead = 0x%p", head);
  while(head)
  {
    printf("->%d", head->num); 
    head = head->next;
  }
}

void push (Node** head, int num)
{
  Node* item = (Node *)malloc(sizeof(Node));
  // check item NULL error

  item->num = num;
  item->next = *head;

  *head = item;
}

int main() {
  Node *head = NULL;
  int insert = 0;
  /* IMP - we pass &head because we want the function to update the new head - handler function will need double pointer */
  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  print(head);

  removeNthFromEnd(head, 2);

  print(head); 
  return 0;
}  
