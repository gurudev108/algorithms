/* Verified on Leetcode 
Leetcode 112. Path Sum - https://leetcode.com/problems/path-sum/
Difficult {Easy}
Topics {BFS, DFS, Tree, BinaryTree}

Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.
*/

#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node */
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};
 
bool hasPathSum(struct TreeNode* root, int targetSum)
{
  if (root == NULL) {
	return false;
  }

  targetSum -= root->val;

  if ((root->left == NULL) && (root->right == NULL)) {
	return (targetSum == 0);
  }
  else {
	return (hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum));
  }
}


