#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the minimum number of columns to be removed
int minColumnsToRemove(char **matrix, int rows, int cols) {
    int columnsToRemove = 0;

    // Iterate over each column
    for (int col = 0; col < cols; col++) {
        // Check if the column is lexicographically ordered
        for (int row = 1; row < rows; row++) {
            if (matrix[row][col] < matrix[row - 1][col]) {
                columnsToRemove++;
                break; // No need to check this column further, it's not ordered
            }
        }
    }

    return columnsToRemove;
}

int main() {
    int rows, cols;

    // Take the number of rows and columns as input
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Dynamically allocate memory for the matrix
    char **matrix = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (char *)malloc((cols + 1) * sizeof(char)); // +1 for null terminator
    }

    // Input the matrix from the user
    printf("Enter the matrix rows (one row per line):\n");
    for (int i = 0; i < rows; i++) {
        scanf("%s", matrix[i]);
    }

    // Find the minimum number of columns to remove
    int result = minColumnsToRemove(matrix, rows, cols);
    printf("Minimum columns to remove: %d\n", result);

    // Free dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

