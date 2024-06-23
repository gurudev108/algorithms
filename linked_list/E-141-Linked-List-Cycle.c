/* 
Leetcode Easy 141 Linked List Cycle

Verified on Leetcode - Beats 69% runtime and 97% memory

*/

#include "stdio.h"

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

bool hasCycle(struct ListNode *head)
{
  if (head == NULL)
  {
    return false;
  }
  ListNode* slow = head;
  ListNode* fast = head->next;

  while(slow!=fast)
  {
    if((fast == NULL) || (fast->next == NULL))
    {
      return false;
    }
    slow = slow->next;
    fast = fast->next->next;
  }
  return true;
}
