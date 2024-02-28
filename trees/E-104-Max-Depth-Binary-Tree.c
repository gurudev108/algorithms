/*
https://leetcode.com/problems/maximum-depth-of-binary-tree/
104. Max Depth of a Binary Tree
Easy
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 #define MAX(a,b) ((a>b)?a:b)

int maxDepth(struct TreeNode* root) {
    if (root == NULL)
    {
      return 0;
    }
    int lh = maxDepth (root->left);
    int rh = maxDepth (root->right);
    return MAX(lh, rh) + 1;

}
