/* Questions on Linked List
1. Check loop in a linked list
2. Find the middle of a linked list
3. Find the nth node from the end
4. Merge 2 linked list
5. Print the linked list in reverse order
6. Check if the linked list is pallindrome
7. Sort a linked list
8. Implement a queue using linked list
9. Implement a stack using a linked list
10. Reverse a Linked list
11. Intersection of 2 linked list

Problems
Power Set
*/

#include<stdbool.h> // for bool
#include<stdio.h> // for NULL can also use stddef.h
#include<string.h>
#include<stdlib.h> // for malloc

/* Check whether a singly linked list contains a loop */

typedef struct Node Node;

typedef struct Node {
  int num;
  char name[10];
  Node* next;
} Node;  // Not doing this will give a warning

bool check_loop(Node* head) {
  Node* fast_ptr = head;
  Node* slow_ptr = head;

  while (slow_ptr && fast_ptr && fast_ptr->next) {

    slow_ptr = slow_ptr->next;
    fast_ptr = fast_ptr->next->next;

    if (slow_ptr == fast_ptr) {
      printf("\nLoop found at %p num=%d", fast_ptr, fast_ptr->num);
      return true;
    }
    printf("\nFast Ptr %d %p", fast_ptr->num, fast_ptr);
    printf("\nSlow Ptr %d %p", slow_ptr->num, slow_ptr);
  }
  printf("\nLoop not found - reached end of LL slow_ptr %d fast_ptr %d", slow_ptr->num, fast_ptr->num);
  return false;
}

void reverse(Node **head)
{
  Node *curr = *head;
  Node* prev = NULL;
  Node* next = NULL;
  while (curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *head = prev;
}

void push (Node** head, int num)
{
  Node* item = (Node *)malloc(sizeof(Node));
  // check item NULL error

  item->num = num;
  item->next = *head;

  *head = item;
}

void print (Node* head)
{
  int count = 0;
  while(head)
  {
    printf("\nNode#%d %d", count++, head->num); 
    head = head->next;
  }
}

int main() {
  Node *head = NULL;
  //check_loop_main(); deprecated
  /* IMP - we pass &head because we want the function to update the new head - handler function will need double pointer */
  push(&head, 5);
  push(&head, 4);
  push(&head, 3);
  push(&head, 2);
  push(&head, 1);

  print(head);

/*
  printf("\nChecking loop in LL returns %d", check_loop(head));
  // Add a loop to test check_loop function
  printf("\nAdding a loop");
  head->next->next->next->next->next = head;

  printf("\nChecking loop in LL returns %d", check_loop(head));
*/
  reverse(&head);
  print(head);
  return 0;
}  
  
