#include<stdbool.h>
#include<stdio.h> // for NULL can also use stddef.h
#include<string.h>
#include<stdlib.h> // for malloc

/* Check whether a singly linked list contains a loop */

typedef struct Node Node;

typedef struct Node {
  int num;
  char name[10];
  Node* next;
} Node;

bool check_loop(Node* head) {
  if ((head == NULL) || (head->next == NULL)) {
    return false;
  }
  Node* fast_ptr = head->next;
  Node* slow_ptr = head;

  while (fast_ptr != NULL && fast_ptr->next != NULL) {

    if (slow_ptr == fast_ptr) {
      return true;
    }
    printf("\nFast Ptr %d %s %p", fast_ptr->num, fast_ptr->name, fast_ptr->next);
    printf("\nSlow Ptr %d %s %p", slow_ptr->num, slow_ptr->name, slow_ptr->next);
    slow_ptr = slow_ptr->next;
    fast_ptr = (fast_ptr->next)->next;
  }
  return false;
}

void check_loop_main() {

  bool flag = false;
  Node* node1 = (Node*)malloc(sizeof(Node));
  Node* node2 = (Node*)malloc(sizeof(Node));
  Node* node3 = (Node*)malloc(sizeof(Node));
  Node* node4 = (Node*)malloc(sizeof(Node));
  Node* node5 = (Node*)malloc(sizeof(Node));

  node1->num = 1;
  node2->num = 2;
  node3->num = 3;
  node4->num = 4;
  node5->num = 5;

  strcpy(node1->name, "Ankit");
  strcpy(node2->name, "Abhilasha");
  strcpy(node3->name, "Mylo");
  strcpy(node4->name, "Krunal");
  strcpy(node5->name, "Aadya");

  node1->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;
  node5->next = node2;

  flag = check_loop(node1);
  printf("Result check loop = %d node1:%p %d %s %p", flag, node1, node1->num, node1->name, node1->next);

}

int main() {
  check_loop_main();
  return 0;
}  
  
