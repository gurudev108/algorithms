/* 
36. Valid Sudoku 
*/
#include <stdio.h>
#include <stdbool.h>

// Function to check if a given row contains all digits from 1 to 9
bool isRowPerfect(char** board, int row) {
    /* ###IMP### rest elements are implicity false */
    bool used[10] = {false};

    for (int col = 0; col < 9; ++col) {
        char currentChar = board[row][col];
        if (currentChar != '.' && (currentChar < '1' || currentChar > '9' || used[currentChar - '0'])) {
            return false;
        }
        if (currentChar != '.') {
            used[currentChar - '0'] = true;
        }
    }

    return true;
}

// Function to check if a given column contains all digits from 1 to 9
bool isColPerfect(char** board, int col) {
    bool used[10] = {false};

    for (int row = 0; row < 9; ++row) {
        char currentChar = board[row][col];
        if (currentChar != '.' && (currentChar < '1' || currentChar > '9' || used[currentChar - '0'])) {
            return false;
        }
        if (currentChar != '.') {
            used[currentChar - '0'] = true;
        }
    }

    return true;
}

// Function to check if a given 3x3 subgrid contains all digits from 1 to 9
bool isSubgridPerfect(char** board, int startRow, int startCol) {
    bool used[10] = {false};

    for (int row = startRow; row < startRow + 3; ++row) {
        for (int col = startCol; col < startCol + 3; ++col) {
            char currentChar = board[row][col];
            if (currentChar != '.' && (currentChar < '1' || currentChar > '9' || used[currentChar - '0'])) {
                return false;
            }
            if (currentChar != '.') {
                used[currentChar - '0'] = true;
            }
        }
    }

    return true;
}

// Function to check if the Sudoku board is valid
bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // Check each row, column, and subgrid
    for (int i = 0; i < 9; ++i) {
        if (!isRowPerfect(board, i) || !isColPerfect(board, i)) {
            return false;
        }
    }

    // Check each 3x3 subgrid
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            if (!isSubgridPerfect(board, startRow, startCol)) {
                return false;
            }
        }
    }

    return true;
}

// Main function for testing
int main() {
    // Example valid Sudoku board
    char* validSudoku[] = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };

    int boardSize = 9;
    int boardColSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    // Check if it's a valid Sudoku
    if (isValidSudoku(validSudoku, boardSize, boardColSize)) {
        printf("The Sudoku board is valid.\n");
    } else {
        printf("The Sudoku board is not valid.\n");
    }

    return 0;
}

