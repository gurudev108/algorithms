/*
Reverse Doubly Linked List

Output:
Original list: 1 2 3 4 5 
Reversed list: 5 4 3 2 1 
*/
#include <stdio.h>
#include <stdlib.h>

// Definition for doubly-linked list node
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

// Function to reverse a doubly linked list
struct Node* reverse(struct Node* head) {
    struct Node *temp = NULL;
    struct Node *current = head;

    // Swap next and prev for all nodes of the doubly linked list
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Before changing the head, check for the cases like empty list and list with only one node
    if (temp != NULL) {
        head = temp->prev;
    }

    return head;
}

// Function to insert a node at the end of the doubly linked list
void append(struct Node** head_ref, int new_data) {
    // Allocate memory for new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref;  // Used to traverse the list

    // Put in the data
    new_node->data = new_data;

    // This new node is going to be the last node, so make next of it as NULL
    new_node->next = NULL;

    // If the Linked List is empty, then make the new node as head
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    // Else traverse till the last node
    while (last->next != NULL) {
        last = last->next;
    }

    // Change the next of last node
    last->next = new_node;

    // Make last node as previous of new node
    new_node->prev = last;

    return;
}

// Function to print the doubly linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    /* Start with the empty list */
    struct Node* head = NULL;

    // Create a doubly linked list 1->2->3->4->5
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    printf("Original list: ");
    printList(head);

    // Reverse the doubly linked list
    head = reverse(head);

    printf("Reversed list: ");
    printList(head);

    return 0;
}

