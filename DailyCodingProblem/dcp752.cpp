/*
Print the nodes in a binary tree level-wise.
For example, the following should print 1, 2, 3, 4, 5.

  1
 / \
2   3
   / \
  4   5

*/

#include <iostream>
#include <queue>

using namespace std;

struct node
{
  int data;
  node* left;
  node* right;
};

node* newNode(int data)
{
  auto root = new node;
  root->data = data;
  root->left = NULL;
  root->right = NULL;
  return root;
}

void printLevelOrder(struct node* root)
{
  queue<node*> q;
  if (root)
  {
    q.push(root);
  }
  while(!q.empty())
  {
    auto f = q.front();
    q.pop();

    cout << f->data <<" ";
    if (f->left) q.push(f->left);
    if (f->right) q.push(f->right);

  }
}

int main()
{
  auto root = newNode(1);
  root->left = newNode(2);
  root->right = newNode(3);
  root->right->left = newNode(4);
  root->right->right = newNode(5);

  printLevelOrder(root);

  return 0;

}
