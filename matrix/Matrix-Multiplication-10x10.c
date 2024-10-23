/*
Enter the number of rows and columns for the first matrix: 2
3
Enter the number of rows and columns for the second matrix: 3
4
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
4
5
6
7
8
9
10
11
12
The resultant matrix is:
38 44 50 56 
83 98 113 128 
*/
#include <stdio.h>

// Function to multiply two matrices
void multiplyMatrices(int firstMatrix[][10], int secondMatrix[][10], int resultMatrix[][10], int row1, int col1, int row2, int col2) {
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

    int firstMatrix[10][10], secondMatrix[10][10], resultMatrix[10][10];

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

    return 0;
}

