/*

Leetcode M 200 Number of Islands

*/

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// Define a structure for the queue used in BFS
typedef struct {
    int x, y;
} Point;

typedef struct {
    Point* points;
    int front, rear, size, capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->points = (Point*)malloc(queue->capacity * sizeof(Point));
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

// Function to enqueue a point
void enqueue(Queue* queue, Point point) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->points[queue->rear] = point;
    queue->size++;
}

// Function to dequeue a point
Point dequeue(Queue* queue) {
    Point point = queue->points[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return point;
}

// Function to perform Breadth-First Search (BFS)
void bfs(char** grid, int gridSize, int* gridColSize, int x, int y) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Queue* queue = createQueue(gridSize * gridColSize[0]);
    
    enqueue(queue, (Point){x, y});
    grid[x][y] = '2'; // Mark as visited
    
    while (!isEmpty(queue)) {
        Point p = dequeue(queue);
        
        for (int i = 0; i < 4; i++) {
            int newX = p.x + directions[i][0];
            int newY = p.y + directions[i][1];
            
            // Check boundaries and if the cell is land
            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridColSize[newX] && grid[newX][newY] == '1') {
                grid[newX][newY] = '2'; // Mark as visited
                enqueue(queue, (Point){newX, newY});
            }
        }
    }
    
    free(queue->points);
    free(queue);
}

// Function to count the number of islands using BFS
int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (gridSize == 0 || gridColSize == NULL) return 0;

    int num_islands = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == '1') {
                // Start a BFS when we find an unvisited land
                num_islands++;
                bfs(grid, gridSize, gridColSize, i, j);
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

