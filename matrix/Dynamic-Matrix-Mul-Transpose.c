/*
Matrix multiplication without assuming max size using pointers

Approach
Use row to dynamically allocate, every row has a pointer that points to a row in the matrix.
Example - 
int **firstMatrix = (int **)malloc(row1 * sizeof(int *));

Output:

Enter the number of rows and columns for the first matrix: 2
3
Enter the number of rows and columns for the second matrix: 3
1
Enter elements of the first matrix:
1
2
3
4
5
6
Enter elements of the second matrix:
1
2
3
The resultant matrix is:
14 
32 
The transposed matrix is:
1 4 
2 5 
3 6 

*/

#include <stdio.h>
#include <stdlib.h>

// Function to multiply two matrices
void multiplyMatrices(int **firstMatrix, int **secondMatrix, int **resultMatrix, int row1, int col1, int row2, int col2) {
    // Initializing elements of result matrix to 0
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            resultMatrix[i][j] = 0;
        }
    }

    // Multiplying firstMatrix and secondMatrix, and storing result in resultMatrix
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            for (int k = 0; k < col1; ++k) {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

// For Transpose
void transposeMatrix(int **matrix, int **transposedMatrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposedMatrix[j][i] = matrix[i][j];  // Transpose element
        }
    }
}

int main() {
    int row1, col1, row2, col2;
    
    // Input for dimensions of the matrices
    printf("Enter the number of rows and columns for the first matrix: ");
    scanf("%d %d", &row1, &col1);

    printf("Enter the number of rows and columns for the second matrix: ");
    scanf("%d %d", &row2, &col2);

    // Check if matrices can be multiplied
    if (col1 != row2) {
        printf("Matrix multiplication is not possible. The number of columns of the first matrix must equal the number of rows of the second matrix.\n");
        return -1;
    }

    // Dynamically allocate memory for the matrices
    int **firstMatrix = (int **)malloc(row1 * sizeof(int *));
    int **secondMatrix = (int **)malloc(row2 * sizeof(int *));
    int **resultMatrix = (int **)malloc(row1 * sizeof(int *));
    // For Transpose
    int **transposedMatrix = (int **)malloc(col1 * sizeof(int *));  // For transpose of first matrix
    
    for (int i = 0; i < row1; i++) {
        firstMatrix[i] = (int *)malloc(col1 * sizeof(int));
    }

    for (int i = 0; i < row2; i++) {
        secondMatrix[i] = (int *)malloc(col2 * sizeof(int));
    }

    for (int i = 0; i < row1; i++) {
        resultMatrix[i] = (int *)malloc(col2 * sizeof(int));
    }

    // For Transpose
    for (int i = 0; i < col1; i++) {
        transposedMatrix[i] = (int *)malloc(row1 * sizeof(int));
    }

    // Input for first matrix
    printf("Enter elements of the first matrix:\n");
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            scanf("%d", &firstMatrix[i][j]);
        }
    }

    // Input for second matrix
    printf("Enter elements of the second matrix:\n");
    for (int i = 0; i < row2; ++i) {
        for (int j = 0; j < col2; ++j) {
            scanf("%d", &secondMatrix[i][j]);
        }
    }

    // Function call to multiply the matrices
    multiplyMatrices(firstMatrix, secondMatrix, resultMatrix, row1, col1, row2, col2);

    // Output the result matrix
    printf("The resultant matrix is:\n");
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col2; ++j) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    // For Transpose
    transposeMatrix(firstMatrix, transposedMatrix, row1, col1);

    // For Transpose - Output the transposed matrix
    printf("The transposed matrix is:\n");
    for (int i = 0; i < col1; ++i) {
        for (int j = 0; j < row1; ++j) {
            printf("%d ", transposedMatrix[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < row1; i++) {
        free(firstMatrix[i]);
        free(resultMatrix[i]);
    }
    
    for (int i = 0; i < row2; i++) {
        free(secondMatrix[i]);
    }

    // For Transpose
    for (int i = 0; i < col1; i++) {
        free(transposedMatrix[i]);
    }

    free(firstMatrix);
    free(secondMatrix);
    free(resultMatrix);
    // For Transpose
    free(transposedMatrix);

    return 0;
}

