/*
Leetcode 21. Merge Two Sorted List

Approach:
1. Create a dummy node and assign current to point at it. Merged List will 
continue after dummy, please return dummy.next
2. Iterate through the list until one of them becomes empty - while (list1 && list2)
3. Append remaining node

List 1 = 1>3>5
List 2 = 2>4>6
Output:
Merged List:
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
Free Merged List:
Free Done:
*/

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list
typedef struct Node {
    int val;
    struct Node* next;
} Node;

// Function to merge two sorted linked lists
Node* mergeTwoLists(Node* list1, Node* list2) {
    /* ###IMP STEP#### */
    // Create a dummy node to simplify handling of the merged list
    Node dummy;
    Node* current = &dummy;

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
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to create a new node with a given value
Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    return node;
}

// Function to free the memory allocated for the linked list
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    // Example linked lists: 1->3->5 and 2->4->6
    Node* list1 = newNode(1);
    list1->next = newNode(3);
    list1->next->next = newNode(5);

    Node* list2 = newNode(2);
    list2->next = newNode(4);
    list2->next->next = newNode(6);

    // Merge the two sorted linked lists
    Node* mergedList = mergeTwoLists(list1, list2);

    // Print the merged list
    printf("Merged List:\n");
    printList(mergedList);

    // Free the memory allocated for the linked lists
    printf("Free Merged List:\n");
    freeList(mergedList);
 
    return 0;
}

