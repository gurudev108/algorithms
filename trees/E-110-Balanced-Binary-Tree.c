/* Verified on leetcode
https://leetcode.com/problems/balanced-binary-tree/description/
110. Balanced Binary Tree
Easy
Given a binary tree, determine if its height balanced
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 #include <math.h>
 #define MAX(a,b) ((a>b)?a:b)
int height(struct TreeNode* head)
{
  if (head == NULL)
  {
    return 0;
  }
  int lh = height(head->left);
  int rh = height(head->right);
  return MAX(lh,rh)+1;
}

bool isBalanced(struct TreeNode* root) {
  if (root == NULL) return true;
  int lh = height(root->left);
  int rh = height(root->right);
  // Forgot to add the recursive conditions of left and right tree being balanced
  if ((abs(lh-rh)<=1) && isBalanced(root->left) && isBalanced(root->right))
  {
    return true;
  }
  else
  {
    return false;
  }
    
}
