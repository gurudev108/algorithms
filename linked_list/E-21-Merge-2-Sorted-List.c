/*
21. Merge Two Sorted List
*/

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to merge two sorted linked lists
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    /* ###IMP STEP#### */
    // Create a dummy node to simplify handling of the merged list
    struct ListNode dummy;
    struct ListNode* current = &dummy;

    // Iterate through the lists until one of them becomes empty
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            // Append the current node from list1 to the merged list
            current->next = list1;
            list1 = list1->next;
        } else {
            // Append the current node from list2 to the merged list
            current->next = list2;
            list2 = list2->next;
        }

        // Move to the next node in the merged list
        current = current->next;
    }

    // If either list1 or list2 is not empty, append the remaining nodes
    if (list1 != NULL) {
        current->next = list1;
    } else {
        current->next = list2;
    }

    // Return the head of the merged list (skip the dummy node)
    return dummy.next;
}

// Function to print a linked list
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

int main() {
    // Example linked lists: 1->3->5 and 2->4->6
    struct ListNode* list1 = newNode(1);
    list1->next = newNode(3);
    list1->next->next = newNode(5);

    struct ListNode* list2 = newNode(2);
    list2->next = newNode(4);
    list2->next->next = newNode(6);

    // Merge the two sorted linked lists
    struct ListNode* mergedList = mergeTwoLists(list1, list2);

    // Print the merged list
    printf("Merged List:\n");
    printList(mergedList);

    // Free the memory allocated for the linked lists
    freeList(list1);
    freeList(list2);
    freeList(mergedList);

    return 0;
}

