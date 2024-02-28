/*
https://leetcode.com/problems/transpose-matrix/

867. Transpose Matrix
Easy
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    // Check for empty matrix
    if (matrixSize == 0 || *matrixColSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Determine dimensions of the transposed matrix
    int rows = *matrixColSize;
    int cols = matrixSize;

    // Allocate memory for the transposed matrix
    int** result = (int**)malloc(rows * sizeof(int*));
    // DOUBT - should this be rows or columns?
    *returnColumnSizes = (int*)malloc(rows * sizeof(int));

    for (int i = 0; i < rows; i++) {
        result[i] = (int*)malloc(cols * sizeof(int));
        (*returnColumnSizes)[i] = cols;
    }

    // Transpose the matrix
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < *matrixColSize; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    *returnSize = rows;
    return result;
}
