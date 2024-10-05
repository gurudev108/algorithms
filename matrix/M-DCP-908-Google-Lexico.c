/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

You are given an N by M 2D matrix of lowercase letters. Determine the minimum number of columns that can be removed to ensure that each row is ordered from top to bottom lexicographically. That is, the letter at each column is lexicographically later as you go down each row. It does not matter whether each row itself is ordered lexicographically.

For example, given the following table:

cba
daf
ghi
This is not ordered because of the a in the center. We can remove the second column to make it ordered:

ca
df
gi
So your function should return 1, since we only needed to remove 1 column.

As another example, given the following table:

abcdef
Your function should return 0, since the rows are already ordered (there's only one row).

As another example, given the following table:

zyx
wvu
tsr
Your function should return 3, since we would need to remove all the columns to order it.
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Function to find the minimum number of columns to remove
uint8_t min_deletion_size(char matrix[MAX_ROWS][MAX_COLS], uint8_t rows, uint8_t cols) {
    uint8_t remove_count = 0;

    // Iterate through each column
    for (uint8_t col = 0; col < cols; col++) {
        // Check if this column is lexicographically ordered
        bool ordered = true;
        for (uint8_t row = 1; row < rows; row++) {
            if (matrix[row][col] < matrix[row - 1][col]) {
                // If any character is out of order, mark the column to be removed
                ordered = false;
                break;
            }
        }
        if (!ordered) {
            remove_count++;
        }
    }

    return remove_count;
}

int main() {
    // Example 1
    char matrix1[MAX_ROWS][MAX_COLS] = {
        {'c', 'b', 'a'},
        {'d', 'a', 'f'},
        {'g', 'h', 'i'}
    };
    uint8_t rows1 = 3;
    uint8_t cols1 = 3;
    printf("Columns to remove: %d\n", min_deletion_size(matrix1, rows1, cols1));  // Output: 1

    // Example 2
    char matrix2[MAX_ROWS][MAX_COLS] = {
        {'a', 'b', 'c', 'd', 'e', 'f'}
    };
    uint8_t rows2 = 1;
    uint8_t cols2 = 6;
    printf("Columns to remove: %d\n", min_deletion_size(matrix2, rows2, cols2));  // Output: 0

    // Example 3
    char matrix3[MAX_ROWS][MAX_COLS] = {
        {'z', 'y', 'x'},
        {'w', 'v', 'u'},
        {'t', 's', 'r'}
    };
    uint8_t rows3 = 3;
    uint8_t cols3 = 3;
    printf("Columns to remove: %d\n", min_deletion_size(matrix3, rows3, cols3));  // Output: 3

    return 0;
}

