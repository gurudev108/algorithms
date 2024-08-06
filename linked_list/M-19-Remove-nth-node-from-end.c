/*
Leetcode 19 Remove Nth node from the end 

Approach - Use 2 pointers - first and second.. move first n places away and then 
move them together until first reaches end. 
second's next pointer will be pointing to the node to be deleted. 

*/

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to remove the nth node from the end of the list
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *first = &dummy;
    struct ListNode *second = &dummy;

    // Move first pointer so that the gap between first and second is n nodes apart
    for (int i = 1; i <= n + 1; i++) {
        first = first->next;
    }

    // Move both pointers until first reaches the end
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    // Second's next pointer will be pointing to the node to be deleted
    struct ListNode *toDelete = second->next;
    second->next = toDelete->next;
    free(toDelete);

    return dummy.next;
}

// Helper function to create a new node
struct ListNode* newNode(int val) {
    struct ListNode *node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// Helper function to print the list
void printList(struct ListNode *head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Example usage
int main() {
    // Create a linked list: 1 -> 2 -> 3 -> 4 -> 5
    struct ListNode *head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    printf("Original list: ");
    printList(head);

    int n = 2;
    head = removeNthFromEnd(head, n);

    printf("List after removing %dth node from the end: ", n);
    printList(head);

    return 0;
}
