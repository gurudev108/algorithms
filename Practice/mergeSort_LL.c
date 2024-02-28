#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node* next;
};

typedef struct node Node;

void print_list(Node *head)
{
  printf("\nPrinting Linked List ");
  while(head)
  {
    printf(" %d", head->data);
    head = head->next;
  }
  return;
}

void push(Node **head, int data)
{
  Node *item = (Node*)malloc(sizeof(Node));
  item->data = data;
  if (*head == NULL)
  {
    item->next = NULL;
    *head = item;
  }
  else
  {
    item->next = *head;
    *head = item;
  }
  
}

void midSplit(Node *head, Node* a, Node *b)
{
  Node *slow = head;
  Node *fast = head;
  while(fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  a = head;
  b = slow->next;
  slow->next = NULL; 
} 

void mergeSort(Node **head)
{
  Node *a, *b;
  if (head == NULL)
  {
    return;
  }
  midSplit(*head, &a, &b);
  mergeSort(&a);
  mergeSort(&b);
  SortedMerge(&a, &b);
}

int main()
{
  Node *head = NULL;
  for (int i=0; i<10; i++)
  {
    push(&head, i);
  }

  print_list(head);

  mergeSort(&head);

  print_list(head);
  return 0;
}
  
