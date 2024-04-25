/* Verified and submitted on Leetcode */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Return an array of arrays of integers
 * The size of the returned array is *returnSize.
 * The sizes of the arrays in the returned array are returned in *columnSizes array.
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** columnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        *columnSizes = NULL;
        return NULL;
    }

    // Initialize a queue to store the nodes
    struct TreeNode* queue[10000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    // Initialize the result array
    int** result = (int**)malloc(sizeof(int*) * 10000);
    *columnSizes = (int*)malloc(sizeof(int) * 10000);
    *returnSize = 0;

    while (front != rear) {
        int levelSize = rear - front;
        result[*returnSize] = (int*)malloc(sizeof(int) * levelSize);
        (*columnSizes)[*returnSize] = levelSize;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            result[*returnSize][i] = node->val;

            if (node->left) {
                queue[rear++] = node->left;
            }
            if (node->right) {
                queue[rear++] = node->right;
            }
        }

        (*returnSize)++;
    }

    return result;
}

/*
Here's how the code works:
We first check if the root is NULL. If it is, we return NULL and set the returnSize and columnSizes pointers accordingly.
We initialize a queue to store the nodes of the binary tree. We also initialize the result array and the columnSizes array.
We then enter a loop that continues until the queue is empty.
In each iteration of the loop, we process all the nodes at the current level. We first determine the size of the current level, and then allocate memory for the result array and the columnSizes array.
We then iterate through all the nodes at the current level, adding their values to the result array and adding their left and right children to the queue (if they exist).
Finally, we increment the returnSize and return the result array.
The time complexity of this solution is O(n), where n is the number of nodes in the binary tree, since we visit each node exactly once. The space complexity is also O(n), since we need to store all the nodes in the queue and the result array.
*/
