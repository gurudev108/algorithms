/* 
https://leetcode.com/problems/invert-binary-tree/description/
226. Invert Binary Tree
Easy

Daily Coding Problem: Problem #596 [Medium]
Invert a binary tree
For example, given the following tree:

    a
   / \
  b   c
 / \  /
d   e f
should become:

  a
 / \
 c  b
 \  / \
  f e  d
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode* temp = NULL;
    if (root == NULL)
    {
      return NULL;
    }

    // Order of recursive calls and swap doesnt matter - pre/post/in

    temp = root->left;
    root->left = root->right;
    root->right = temp;

    root->left = invertTree(root->left);
    root->right = invertTree(root->right);

    return root;
}

/* Approach 2 - Iterative
TODO 
*/


