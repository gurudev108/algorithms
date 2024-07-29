/*
Leetcode M 200 Number of Islands

Approach - DFS

Verified Output:
Number of islands: 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform Depth-First Search (DFS)
void dfs(char** grid, int gridSize, int* gridColSize, int i, int j) {
    // Check if the current cell is out of bounds or not an island
    if (i < 0 || j < 0 || i >= gridSize || j >= gridColSize[i] || grid[i][j] != '1') {
        return;
    }

    // Mark the current cell as visited
    grid[i][j] = '2';

    // Visit all adjacent cells (up, down, left, right)
    dfs(grid, gridSize, gridColSize, i + 1, j);
    dfs(grid, gridSize, gridColSize, i - 1, j);
    dfs(grid, gridSize, gridColSize, i, j + 1);
    dfs(grid, gridSize, gridColSize, i, j - 1);
}

// Function to count the number of islands
int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0 || gridColSize == NULL) return 0;

    int num_islands = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '1') {
                // Start a DFS when we find an unvisited land
                num_islands++;
                dfs(grid, gridSize, gridColSize, i, j);
            }
        }
    }

    return num_islands;
}

// Helper function to create a grid for testing
char** createGrid(char* data[], int rows, int cols) {
    char** grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (char*)malloc((cols + 1) * sizeof(char));
        strcpy(grid[i], data[i]);
    }
    return grid;
}

// Helper function to free the grid memory
void freeGrid(char** grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

// Main function to test the solution
int main() {
    char* data[] = {
        "11110",
        "11010",
        "11000",
        "00010"
    };
    int gridSize = 4;
    int gridColSize[] = {5, 5, 5, 5};
    
    char** grid = createGrid(data, gridSize, gridColSize[0]);

    int result = numIslands(grid, gridSize, gridColSize);
    printf("Number of islands: %d\n", result);

    freeGrid(grid, gridSize);

    return 0;
}


