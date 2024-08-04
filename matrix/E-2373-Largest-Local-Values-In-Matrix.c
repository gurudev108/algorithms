/*
Leetcode E 2373. Largest Local Values in a Matrix

You are given an n x n integer matrix grid.
Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:

maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.

Return the generated matrix.

Approach:
The size of the resulting matrix maxLocal is (n - 2) x (n - 2), where n is the size of the original matrix.
For each position (i, j) in maxLocal, the corresponding 3x3 sub-matrix in grid centered at (i+1, j+1) is examined.
The maximum value within this 3x3 sub-matrix is found and stored in maxLocal[i][j].
*/

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

// Function to find the largest local values in a matrix
int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    *returnSize = n - 2;
    int** maxLocal = (int**)malloc((*returnSize) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    
    for (int i = 0; i < *returnSize; i++) {
        maxLocal[i] = (int*)malloc((*returnSize) * sizeof(int));
        (*returnColumnSizes)[i] = *returnSize;
        for (int j = 0; j < *returnSize; j++) {
            int maxValue = grid[i][j];
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    maxValue = max(maxValue, grid[k][l]);
                }
            }
            maxLocal[i][j] = maxValue;
        }
    }
    
    return maxLocal;
}

// Helper function to print a matrix
void printMatrix(int** matrix, int size, int* colSizes) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < colSizes[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Example usage
int main() {
    int grid[5][5] = {
        {9, 9, 8, 1, 2},
        {5, 6, 2, 4, 3},
        {7, 2, 3, 5, 1},
        {6, 6, 3, 8, 7},
        {3, 2, 1, 2, 3}
    };
    int gridSize = 5;
    int gridColSize = 5;

    // Create a pointer array for the grid rows
    int* gridPtr[gridSize];
    for (int i = 0; i < gridSize; i++) {
        gridPtr[i] = grid[i];
    }

    int returnSize;
    int* returnColumnSizes;
    int** result = largestLocal(gridPtr, gridSize, &gridColSize, &returnSize, &returnColumnSizes);
    
    printf("Largest Local Values in a Matrix:\n");
    printMatrix(result, returnSize, returnColumnSizes);

    // Free the allocated memory for the result and column sizes
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}
