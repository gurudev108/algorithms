/* DCP

250. Count Univalue subtrees
Medium

Given the root of a binary tree, return the number of uni-value 
subtrees
.
A uni-value subtree means all nodes of the subtree have the same value.

Example 1:
Input: root = [5,1,5,5,5,null,5]
Output: 4

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// Helper function to check if a subtree is a uni-value subtree.
bool isUniValueSubtree(struct TreeNode* root, int* count) {
    if (root == NULL) {
        return true;
    }

    bool leftUni = isUniValueSubtree(root->left, count);
    bool rightUni = isUniValueSubtree(root->right, count);

    if (leftUni && rightUni) {
        // If both left and right subtrees are uni-value and
        // the current node's value matches its children's values (if any),
        // then the current subtree is a uni-value subtree.
        if ((root->left == NULL || root->left->val == root->val) &&
            (root->right == NULL || root->right->val == root->val)) {
            (*count)++;
            return true;
        }
    }

    return false;
}

// Function to count the number of uni-value subtrees in a binary tree.
int countUnivalSubtrees(struct TreeNode* root) {
    int count = 0;
    isUniValueSubtree(root, &count);
    return count;
}
