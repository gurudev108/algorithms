#include <stdio.h>

// Function to print a matrix
void printMatrix(int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print a matrix using pointers instead of [][]
void printMatrix_1(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", *(matrix + i*cols + j));
        }
        printf("\n");
    }
}


// Function to calculate the transpose of a matrix
void transposeMatrix(int matrix[][3], int rows, int cols, int result[][3]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

int main() {
    // Example matrix
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int rows = 3;
    int cols = 3;

    // Print the original matrix
    printf("Original Matrix:\n");
    printMatrix(matrix, rows, cols);
    printMatrix_1((int*)matrix, rows, cols);

    // Calculate and print the transpose of the matrix
    int result[3][3];
    transposeMatrix(matrix, rows, cols, result);

    printf("\nTranspose Matrix:\n");
    printMatrix(result, cols, rows);

    return 0;
}

