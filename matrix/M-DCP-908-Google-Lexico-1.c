#include <stdio.h>
#include <string.h>

// Function to find the minimum number of columns to be removed
int minColumnsToRemove(char matrix[][100], int rows, int cols) {
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
    // Example 1
    char matrix1[3][100] = {
        "cba",
        "daf",
        "ghi"
    };
    int rows1 = 3;
    int cols1 = strlen(matrix1[0]);
    printf("Example 1: Minimum columns to remove: %d\n", minColumnsToRemove(matrix1, rows1, cols1));

    // Example 2
    char matrix2[1][100] = {
        "abcdef"
    };
    int rows2 = 1;
    int cols2 = strlen(matrix2[0]);
    printf("Example 2: Minimum columns to remove: %d\n", minColumnsToRemove(matrix2, rows2, cols2));

    // Example 3
    char matrix3[3][100] = {
        "zyx",
        "wvu",
        "tsr"
    };
    int rows3 = 3;
    int cols3 = strlen(matrix3[0]);
    printf("Example 3: Minimum columns to remove: %d\n", minColumnsToRemove(matrix3, rows3, cols3));

    return 0;
}

