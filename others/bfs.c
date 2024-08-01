/*
Practicing BFS implemented as a Queue - other option is Recursion
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

struct QueueNode {
  struct TreeNode* data;
  struct QueueNode* next;
};

struct Queue {
  struct QueueNode* front;
  struct QueueNode* rear;
};

struct TreeNode* createNode(int val)
{
  struct TreeNode* node = (struct TreeNode*) malloc(sizeof(struct TreeNode));
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;  
}

struct Queue* createQueue()
{
  struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
  if (q!= NULL) {
    q->front = NULL;
    q->rear = NULL;
  } else {
    printf("Error creating Queue");
  }
  return q;
}

void enqueue(struct Queue* q, struct TreeNode* node)
{

  //printf("enqueue start %d front %p rear %p\n", node->val, q->front, q->rear);
  struct QueueNode *tmp = (struct QueueNode*) malloc(sizeof(struct QueueNode));
  tmp->data = node;
  tmp->next = NULL;
  if ((q->rear == NULL) || (q->front == NULL)) {
    q->front = q->rear = tmp;
  } else {
    q->rear->next = tmp;
    q->rear = tmp;
  }

  //printf("enqueue end %d front %p rear %p\n", node->val, q->front, q->rear);
}

struct TreeNode* dequeue(struct Queue* q)
{

  //printf("dequeue start %d front %p rear %p\n", q->front->data->val, q->front, q->rear);
  if((q->rear == NULL) || (q->front == NULL))
    return NULL;

  struct QueueNode* tmp = q->front;
  struct TreeNode* node = tmp->data;

  q->front = tmp->next;
  free(tmp);

  return node;
}

void bfs(struct TreeNode* root)
{
  if(root == NULL)
    return;

  struct Queue* q = createQueue();
  enqueue(q, root);

  while(q->front)
  {
    struct TreeNode* current = dequeue(q);
    printf("%d ", current->val);

    if(current->left)
      enqueue(q, current->left);

    if(current->right)
      enqueue(q, current->right);
    
  }
  free(q);
}

int main()
{
  struct TreeNode* root = createNode(1);
  root->left = createNode(2);
  root->right = createNode(3);
  root->left->left = createNode(4);
  root->left->right = createNode(5);
  root->right->left = createNode(6);
  root->right->right = createNode(7);

  bfs(root);
  
  return 0;
}
