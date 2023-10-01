/* INCOMPLETE
Heap sort on Linked List */

#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int item;
  struct Node* next;
};

//struct Node* middle_LL(struct node* head

void heapSort(struct node* head, int len)
{

  for (int i=0; i<len/2; i++)
    head=head->next;
 
  /* Build a heap */
  for 
}

/* Function to print nodes in a given linked list */
void printList(struct Node* node)
{
  while (node != NULL) {
    printf("%d ", node->item);
    node = node->next;
  }
}

/* Function to insert a node at the beginning of the linked list */
void push(struct Node** head_ref, int new_data)
{
  struct Node* node = (struct Node*) malloc(sizeof(struct Node));

  node->item = new_data;

  node->next = *head_ref;

  *head_ref = node; 

}

/* Driver program to test above functions*/
int main()
{
  /* Start with the empty list */
  struct Node* a = NULL;
  int len = 6;

  /* Let us create a unsorted linked lists to test the functions
  Created lists shall be a: 2->3->20->5->10->15 */
  push(&a, 15);
  push(&a, 10);
  push(&a, 5);
  push(&a, 20);
  push(&a, 3);
  push(&a, 2);

  printf("\nLinked List before sorting: ");
  printList(a);

  /* Sort the above created Linked List */
  heapSort(&a, len);

  printf("\nSorted Linked List is: ");
  printList(a);

  return 0;
}
     
