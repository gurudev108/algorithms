#include <stdio.h>

// Function to print a 2D matrix using pointers
void printMatrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Accessing elements using pointer arithmetic
            printf("%d\t", *(matrix + i * cols + j));
        }
        printf("\n");
    }
}

int main() {
    // Example 2D matrix
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Pass the 2D matrix to the function
    printMatrix((int *)matrix, 3, 4);

    return 0;
}

