#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

// Function to check if a given row contains all digits from 1 to 9
bool isRowPerfect(int matrix[SIZE][SIZE], int row) {
    bool used[SIZE + 1] = {false};

    for (int col = 0; col < SIZE; ++col) {
        if (matrix[row][col] < 1 || matrix[row][col] > SIZE || used[matrix[row][col]]) {
            return false;
        }
        used[matrix[row][col]] = true;
    }

    return true;
}

// Function to check if a given column contains all digits from 1 to 9
bool isColPerfect(int matrix[SIZE][SIZE], int col) {
    bool used[SIZE + 1] = {false};

    for (int row = 0; row < SIZE; ++row) {
        if (matrix[row][col] < 1 || matrix[row][col] > SIZE || used[matrix[row][col]]) {
            return false;
        }
        used[matrix[row][col]] = true;
    }

    return true;
}

// Function to check if a given 3x3 subgrid contains all digits from 1 to 9
bool isSubgridPerfect(int matrix[SIZE][SIZE], int startRow, int startCol) {
    bool used[SIZE + 1] = {false};

    for (int row = startRow; row < startRow + 3; ++row) {
        for (int col = startCol; col < startCol + 3; ++col) {
            if (matrix[row][col] < 1 || matrix[row][col] > SIZE || used[matrix[row][col]]) {
                return false;
            }
            used[matrix[row][col]] = true;
        }
    }

    return true;
}

// Function to check if the matrix is a perfect sudoku
bool isPerfectSudoku(int matrix[SIZE][SIZE]) {
    // Check each row, column, and subgrid
    for (int i = 0; i < SIZE; ++i) {
        if (!isRowPerfect(matrix, i) || !isColPerfect(matrix, i)) {
            return false;
        }
    }

    // Check each 3x3 subgrid
    for (int startRow = 0; startRow < SIZE; startRow += 3) {
        for (int startCol = 0; startCol < SIZE; startCol += 3) {
            if (!isSubgridPerfect(matrix, startRow, startCol)) {
                return false;
            }
        }
    }

    return true;
}

// Main function for testing
int main() {
    // Example perfect sudoku matrix
    int perfectSudoku[SIZE][SIZE] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    // Check if it's a perfect sudoku
    if (isPerfectSudoku(perfectSudoku)) {
        printf("The matrix is a perfect sudoku.\n");
    } else {
        printf("The matrix is not a perfect sudoku.\n");
    }

    return 0;
}

