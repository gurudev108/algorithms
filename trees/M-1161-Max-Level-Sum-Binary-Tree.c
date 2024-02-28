/* Accepted - https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/

1161. Max Level Sum of a Binary Tree
Medium

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new TreeNode.
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find the level with the minimum sum in a binary tree.
int maxLevelSum(struct TreeNode* root)
{
  int maxSum = INT_MIN;
  int maxLevel = 0;
  int front = 0, rear = 0;
  int level = 0;
  /* Assuming max list of 1000 levels */
  struct TreeNode** queue = (struct TreeNode**) malloc(sizeof(struct TreeNode*)*10000);

  queue[rear++] = root;

  while(front<rear)
  {
    int levelSize = rear - front; //number of nodes at current level
    int levelSum = 0;
    level++;

    //Process nodes at current level
    for (int i=0; i<levelSize; ++i) //Note ++i
    {
      struct TreeNode* current = queue[front++];
      levelSum += current->val;

      //Enqueue the child of current nodes if it exists
      if (current->left)
      {
        queue[rear++] = current->left;
      }
      if (current->right)
      {
        queue[rear++] = current->right;
      }
    }
    // Update maxSum
    if (levelSum > maxSum)
    {
      maxSum = levelSum;
      maxLevel = level; //IMP Levels are zero based       
    }
    printf("\nfront %d read %d levelSum %d maxSum %d maxLevel %d",
    front, rear, levelSum, maxSum, maxLevel);
  }
  free(queue);
  return maxLevel;

}

int main() {
    // Example usage:
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(8);
    root->right->right->left = createNode(6);
    root->right->right->right = createNode(7);

    int result = maxLevelSum(root);

    if (result != -1) {
        printf("Level with the maximum sum: %d\n", result);
    } else {
        printf("Tree is empty.\n");
    }

    return 0;
}

