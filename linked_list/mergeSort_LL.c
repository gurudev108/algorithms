// C code for linked list merged sort
#include <stdio.h>
#include <stdlib.h>

/* Link list node */
struct Node {
  int data;
  struct Node* next;
};

/* function prototypes */
struct Node* SortedMerge(struct Node* a, struct Node* b);
void FrontBackSplit(struct Node* source,
          struct Node** frontRef, struct Node** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Node** headRef)
{
  struct Node* head = *headRef;
  struct Node* a;
  struct Node* b;

  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL)) {
    return;
  }

  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b);

  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);

  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct Node* SortedMerge(struct Node* a, struct Node* b)
{
  struct Node* result = NULL;

  /* Base cases */
  if (a == NULL)
    return (b);
  else if (b == NULL)
    return (a);

  printf("\nSortedMerge first:%d second:%d", a->data, b->data);
  /* Pick either a or b, and recur */
  if (a->data <= b->data) {
    result = a;
    result->next = SortedMerge(a->next, b);
  }
  else {
    result = b;
    result->next = SortedMerge(a, b->next);
  }
  return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
  and return the two lists using the reference parameters.
  If the length is odd, the extra node should go in the front list.
  Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct Node* source,
          struct Node** frontRef, struct Node** backRef)
{
  struct Node* fast;
  struct Node* slow;
  slow = source;
  fast = source->next;

  /* Advance 'fast' two nodes, and advance 'slow' one node */
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  /* 'slow' is before the midpoint in the list, so split it in two
  at that point. */
  *frontRef = source;
  *backRef = slow->next;
  slow->next = NULL;
}

/* Function to print nodes in a given linked list */
void printList(struct Node* node)
{
  while (node != NULL) {
    printf("%d ", node->data);
    node = node->next;
  }
}

/* Function to insert a node at the beginning of the linked list */
void push(struct Node** head_ref, int new_data)
{
  /* allocate node */
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

  /* put in the data */
  new_node->data = new_data;

  /* link the old list of the new node */
  new_node->next = (*head_ref);

  /* move the head to point to the new node */
  (*head_ref) = new_node;
}

/* Driver program to test above functions*/
int main()
{
  /* Start with the empty list */
  struct Node* a = NULL;

  /* Let us create a unsorted linked lists to test the functions
Created lists shall be a: 2->3->20->5->10->15 */
  for (int i=0; i<10; i++)
  {
    push(&a, i);
  }

  printf("\nLinked List before sorting: ");
  printList(a);

  /* Sort the above created Linked List */
  MergeSort(&a);

  printf("\nSorted Linked List is: ");
  printList(a);

  return 0;
}

