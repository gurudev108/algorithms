/*
Sparse Matrix Multiplication
Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of 
mat1 x mat2. You may assume that multiplication is always possible.

Approach - In the optimized solution, we leverage the sparsity of the matrices. 
We only multiply non-zero elements of mat1 with corresponding non-zero elements of mat2. 
This reduces the number of multiplications and additions significantly.

Output:
Resultant Matrix:
7 0 
-7 3 
*/

#include <stdio.h>
#include <stdlib.h>

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** sparseMultiply(int** mat1, int mat1RowSize, int mat1ColSize, int** mat2, int mat2ColSize) {
    int m = mat1RowSize;
    int k = mat1ColSize;
    int n = mat2ColSize;

    // Allocate memory for the result matrix
    int** result = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        result[i] = (int*)calloc(n, sizeof(int));
    }

    // Optimized matrix multiplication
    for (int i = 0; i < m; i++) {
        for (int l = 0; l < k; l++) {
            if (mat1[i][l] != 0) { // Only consider non-zero elements of mat1
                for (int j = 0; j < n; j++) {
                    if (mat2[l][j] != 0) { // Only consider non-zero elements of mat2
                        result[i][j] += mat1[i][l] * mat2[l][j];
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    // Example matrices
    int mat1RowSize = 2, mat1ColSize = 3;
    int mat2ColSize = 2;

    int* mat1Data[2] = { (int[]){1, 0, 0}, (int[]){-1, 0, 3} };
    int* mat2Data[3] = { (int[]){7, 0}, (int[]){0, 0}, (int[]){0, 1} };

    // Convert to double pointer for passing
    int** mat1 = mat1Data;
    int** mat2 = mat2Data;

    int** result = sparseMultiply(mat1, mat1RowSize, mat1ColSize, mat2, mat2ColSize);

    printf("Resultant Matrix:\n");
    printMatrix(result, mat1RowSize, mat2ColSize);

    // Free allocated memory
    for (int i = 0; i < mat1RowSize; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}

