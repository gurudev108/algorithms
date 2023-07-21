#include <stdio.h>

/* Leetcode - https://leetcode.com/problems/rotate-image/description/
Rotate Image - Medium
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]
Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

Solution 1- We can iterate over each group of four cells and rotate them.

Better Solution using linear algebra idea - 
The most elegant solution for rotating the matrix is to firstly reverse the matrix around the main diagonal, and then reverse it from left to right.
These operations are called transpose and reflect in linear algebra.
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize){

}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().

int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes){
    
int maxLocal[][]
}

*/


// Function to find the largest local values in a matrix
void findLargestLocalValues(int matrix[][3], int rows, int columns) {
    int i, j;
    
    for (i = 1; i < rows - 1; i++) {
        for (j = 1; j < columns - 1; j++) {
            int current = matrix[i][j];
            
            if (current > matrix[i-1][j] &&
                current > matrix[i+1][j] &&
                current > matrix[i][j-1] &&
                current > matrix[i][j+1]) {
                printf("Largest local value found at position (%d, %d): %d\n", i, j, current);
            }
        }
    }
}

int main() {
    int matrix[3][3] = {
        {25, 10, 3},
        {7, 20, 12},
        {15, 4, 8}
    };
    
    findLargestLocalValues(matrix, 3, 3);
    
    return 0;
}

