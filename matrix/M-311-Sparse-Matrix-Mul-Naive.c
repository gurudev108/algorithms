/*
Sparse Matrix Multiplication
Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x mat2. You may assume that multiplication is always possible.

Approach - Naive without using the sparse feature of the matrix

Output:
Resultant Matrix:
7 0 
-7 3 
*/
#include <stdio.h>
#include <stdlib.h>

int** multiply(int** mat1, int mat1RowSize, int mat1ColSize, int** mat2, int mat2ColSize) {
    int m = mat1RowSize;
    int k = mat1ColSize;
    int n = mat2ColSize;

    // Allocate memory for the result matrix
    int** result = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        result[i] = (int*)calloc(n, sizeof(int));
    }

    // Naive matrix multiplication
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < k; l++) {
                result[i][j] += mat1[i][l] * mat2[l][j];
            }
        }
    }

    return result;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Example matrices - assumed multiplication possible
    int mat1RowSize = 2, mat1ColSize = 3;
    int mat2ColSize = 2;

    int* mat1Data[2] = { (int[]){1, 0, 0}, (int[]){-1, 0, 3} };
    int* mat2Data[3] = { (int[]){7, 0}, (int[]){0, 0}, (int[]){0, 1} };

    // Convert to double pointer for passing
    int** mat1 = mat1Data;
    int** mat2 = mat2Data;

    int** result = multiply(mat1, mat1RowSize, mat1ColSize, mat2, mat2ColSize);

    printf("Resultant Matrix:\n");
    printMatrix(result, mat1RowSize, mat2ColSize);

    // Free allocated memory
    for (int i = 0; i < mat1RowSize; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}

