/*

Leetcode M 311 Sparse Matrix Mul - Lists of lists

Approach - Lets now work on another optimized solution approach - lists of list. The interviewer's follow-up could be, what if the matrix is too big to store in the memory, but there are only a few non-zero elements. Here, he wants to see how we handle huge space waste. He expects us to store the matrix efficiency and do multiplication using that. Thus, we have to use some data structure to only store the non-zero elements of both matrices.

We will create some buckets where each bucket denotes one row and that bucket contains an array of pairs of (value, column). Zero valued elements will be missing from our data structure. Since the matrices are sparse, we will only store a few elements in our data structure

To efficiently handle sparse matrices, especially when they are too large to fit entirely in memory but contain few non-zero elements, we can use a "lists of lists" approach. In this approach, each row of a matrix is represented by a list of pairs (value, column), where value is the non-zero element and column is the index of the column where this element is located.

Optimized Sparse Matrix Multiplication Using Lists of Lists
We'll represent both matrices in this compact form and perform multiplication using these representations. The idea is to only iterate through non-zero elements, significantly reducing the number of operations compared to a naive approach.

Output:
Resultant Matrix:
7 0 
-7 3 
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a non-zero element with its column index
typedef struct {
    int value;
    int col;
} Element;

// Function to multiply two sparse matrices represented as lists of lists
int** multiplySparseMatrices(Element*** mat1, int mat1Rows, int* mat1Sizes,
                             Element*** mat2, int mat2Cols, int* mat2Sizes) {
    // Allocate memory for the result matrix
    int** result = (int**)malloc(mat1Rows * sizeof(int*));
    for (int i = 0; i < mat1Rows; i++) {
        result[i] = (int*)calloc(mat2Cols, sizeof(int));
    }

    // Perform multiplication using sparse representation
    for (int i = 0; i < mat1Rows; i++) {
        for (int j = 0; j < mat1Sizes[i]; j++) {
            int mat1Value = mat1[i][j]->value;
            int mat1Col = mat1[i][j]->col;

            for (int k = 0; k < mat2Sizes[mat1Col]; k++) {
                int mat2Value = mat2[mat1Col][k]->value;
                int mat2Col = mat2[mat1Col][k]->col;

                result[i][mat2Col] += mat1Value * mat2Value;
            }
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Example sparse matrix mat1: [[1, 0, 0], [-1, 0, 3]]
    int mat1Rows = 2, mat1Cols = 3;
    int mat1Sizes[2] = {1, 2};

    Element* mat1Data1[] = { &(Element){1, 0} };
    Element* mat1Data2[] = { &(Element){-1, 0}, &(Element){3, 2} };

    Element** mat1[] = { mat1Data1, mat1Data2 };

    // Example sparse matrix mat2: [[7, 0], [0, 0], [0, 1]]
    int mat2Rows = 3, mat2Cols = 2;
    int mat2Sizes[3] = {1, 0, 1};

    Element* mat2Data1[] = { &(Element){7, 0} };
    Element* mat2Data3[] = { &(Element){1, 1} };

    Element** mat2[] = { mat2Data1, NULL, mat2Data3 };

    // Multiply the sparse matrices
    int** result = multiplySparseMatrices(mat1, mat1Rows, mat1Sizes, mat2, mat2Cols, mat2Sizes);

    // Print the result matrix
    printf("Resultant Matrix:\n");
    printMatrix(result, mat1Rows, mat2Cols);

    // Free allocated memory
    for (int i = 0; i < mat1Rows; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}

/*
Explanation - 
Data Structure:
We use a struct Element to represent non-zero elements along with their column indices.
mat1 and mat2 are arrays of lists (arrays of Element*) where each list contains the non-zero elements for that row.

Matrix Multiplication:
For each row in mat1, we iterate over its non-zero elements.
For each non-zero element (value, column) in mat1, we find the corresponding row in mat2 (since mat2's rows correspond to columns in mat1 due to the matrix multiplication).
We then iterate over the non-zero elements in the corresponding row of mat2 to accumulate the product in the resulting matrix.

Efficiency:
This method significantly reduces the number of computations by only considering non-zero elements, thus making it efficient for large sparse matrices.
Memory Management:
The result matrix is dynamically allocated, and memory management (allocation and deallocation) is handled appropriately.
This approach ensures that only non-zero elements are stored and processed, making it highly efficient in terms of both time and space for sparse matrices.
*/