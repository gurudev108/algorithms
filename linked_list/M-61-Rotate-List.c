/*
61. Rotate List by K places
*/
#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    // Step 1: Find the length of the linked list
    int length = 1;
    struct ListNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    // Step 2: Calculate effective rotation index
    int effectiveK = k % length;
    if (effectiveK == 0) {
        return head; // No rotation needed
    }

    // Step 3: Locate new tail and new head
    struct ListNode* newTail = head;
    for (int i = 0; i < length - effectiveK - 1; ++i) {
        newTail = newTail->next;
    }
    struct ListNode* newHead = newTail->next;

    // Step 4: Break the linked list, set the new head, and connect the new tail to the original head
    newTail->next = NULL;
    tail->next = head;

    // Step 5: Return the new head
    return newHead;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to create a new node with a given value
struct ListNode* newNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// Function to free the memory allocated for the linked list
void freeList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        struct ListNode* next = current->next;
        free(current);
        current = next;
    }
}

// Main function for testing
int main() {
    // Example linked list: 1 -> 2 -> 3 -> 4 -> 5
    struct ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    int k = 2;

    printf("Original Linked List:\n");
    printList(head);

    // Rotate the linked list to the right by k places
    struct ListNode* rotatedHead = rotateRight(head, k);

    printf("\nLinked List after rotating to the right by %d places:\n", k);
    printList(rotatedHead);

    // Free the memory allocated for the linked list
    freeList(rotatedHead);

    return 0;
}

