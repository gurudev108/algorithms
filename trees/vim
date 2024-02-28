/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void binaryTreePathsHelper(struct TreeNode* root, char* currentPath, char** result, int* resultSize) {
    if (!root) {
        return;
    }

    // Convert the current node's value to a string
    char val_str[12];  // Assuming a 32-bit integer, so at most 11 digits plus null terminator
    sprintf(val_str, "%d", root->val);

    // If it's a leaf node, add the current path to the result
    if (!root->left && !root->right) {
        int path_length = snprintf(NULL, 0, "%s%s", currentPath, val_str) + 1;  // +1 for null terminator
        char* path = (char*)malloc(path_length);
        sprintf(path, "%s%s", currentPath, val_str);
        result[(*resultSize)++] = path;
        return;
    }

    // If not a leaf node, continue DFS for left and right children
    char* new_path = (char*)malloc(strlen(currentPath) + strlen(val_str) + 3);  // 3 for "->" and null terminator
    sprintf(new_path, "%s%s->", currentPath, val_str);
    binaryTreePathsHelper(root->left, new_path, result, resultSize);
    binaryTreePathsHelper(root->right, new_path, result, resultSize);
    free(new_path);
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    char** result = NULL;
    *returnSize = 0;

    // Allocate space for the result
    result = (char**)malloc(sizeof(char*) * 1000);  // Assuming a maximum of 1000 paths
    binaryTreePathsHelper(root, "", result, returnSize);

    return result;
}
