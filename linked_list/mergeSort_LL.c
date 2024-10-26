/* 
C code for linked list merged sort

Approach: Divide and Conquer approach - Recursion
Base case
Split the list into 2 halves 
Merge Sort both the halves (Recursion)
Merge the sorted list
Explanation of the Code
ListNode Structure: Defines the structure of a node in the linked list.
splitList: This function splits the linked list into two halves using the slow and fast pointer approach.
mergeLists: This function merges two sorted linked lists.
mergeSort: This is the main function that implements merge sort on the linked list.
printList: Utility function to print the linked list.
newNode: Utility function to create a new linked list node.
main: Creates a sample linked list, sorts it, and prints both the original and sorted linked list.

Output: 
Linked List before sorting: 9 3 8 4 2 0 8 3 9 7 
SortedMerge first:9 second:3
SortedMerge first:3 second:8
SortedMerge first:9 second:8
SortedMerge first:4 second:2
SortedMerge first:3 second:2
SortedMerge first:3 second:4
SortedMerge first:8 second:4
SortedMerge first:0 second:8
SortedMerge first:0 second:3
SortedMerge first:8 second:3
SortedMerge first:9 second:7
SortedMerge first:0 second:7
SortedMerge first:3 second:7
SortedMerge first:8 second:7
SortedMerge first:8 second:9
SortedMerge first:2 second:0
SortedMerge first:2 second:3
SortedMerge first:3 second:3
SortedMerge first:4 second:3
SortedMerge first:4 second:7
SortedMerge first:8 second:7
SortedMerge first:8 second:8
SortedMerge first:9 second:8
SortedMerge first:9 second:9
Sorted Linked List is: 0 2 3 3 4 7 8 8 9 9 
*/
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
    push(&a, rand()%10);
  }

  printf("\nLinked List before sorting: ");
  printList(a);

  /* Sort the above created Linked List */
  MergeSort(&a);

  printf("\nSorted Linked List is: ");
  printList(a);

  return 0;
}

/*

Approaches to Solve the Problem
Merge Sort:
Overview: Merge sort is a divide-and-conquer algorithm that recursively splits the list into halves, sorts each half, and then merges them back together.
Complexity: It runs in O(nlogn)
O(nlogn) time and can be implemented in constant space (if we consider the space for the recursive stack as not being additional, which is debatable).
Implementation: It is well-suited for linked lists because merging two linked lists can be done in linear time without extra space.
Quick Sort:
Overview: Quick sort selects a pivot element, partitions the linked list around the pivot, and then recursively sorts the partitions.
Complexity: While it can average O(nlogn)
O(nlogn), its worst-case time complexity is O(n2) if the pivot is poorly chosen.
Space Complexity: It typically requires O(n) space for the recursive calls, making it unsuitable for this problem.
Heap Sort:
Overview: Heap sort involves building a heap from the linked list and then repeatedly extracting the maximum element.
Complexity: It has a time complexity of O(nlogn), but it requires O(n) space for the heap.
Space Complexity: This approach doesn't meet the requirement of constant space.
Insertion Sort:
Overview: While insertion sort is O(n2) in the average and worst cases, it can be efficient for small or partially sorted lists.
Complexity: It doesn’t meet the O(nlogn) requirement, so it's not suitable here.
Best Approach
Merge Sort is the best approach for this problem because:
It can be implemented in O(nlogn) time.
It can be adapted to work with linked lists efficiently without needing additional space for data structures, aside from a few pointers.

*/