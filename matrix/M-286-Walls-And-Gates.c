/*
Leetcode M 286 Walls and Gates

You are given an m x n grid rooms initialized with these three possible values.

-1 A wall or an obstacle.
0 A gate.
INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

IMP:
**rooms in the definition is implemented as arrays of pointers - int* rooms[4]


Approach #1 (Brute Force) [Time Limit Exceeded]

The brute force approach is simple, we just implement a breadth-first search from each empty room to its nearest gate.

While we are doing the search, we use a 2D array called distance to keep track of the distance from the starting point. It also implicitly tell us whether a position had been visited so it won't be inserted into the queue again

Approach #2 

Instead of searching from an empty room to the gates, how about searching the other way round? In other words, we initiate breadth-first search (BFS) from all gates at the same time. Since BFS guarantees that we search all rooms of distance d before searching rooms of distance d + 1, the distance to an empty room must be the shortest.

Verified Output:
  3  -1   0   1 
  2   2   1  -1 
  1  -1   2  -1 
  0  -1   3   4 
*/
#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    Point* points;
    int size;
    int capacity;
} Queue;

// Function to initialize a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->points = (Point*)malloc(capacity * sizeof(Point));
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue a point
void enqueue(Queue* queue, int row, int col) {
    if (queue->size == queue->capacity) {
        return;
    }
    queue->points[queue->size].row = row;
    queue->points[queue->size].col = col;
    queue->size++;
}

// Function to dequeue a point
Point dequeue(Queue* queue) {
    Point point = queue->points[0];
    for (int i = 1; i < queue->size; i++) {
        queue->points[i - 1] = queue->points[i];
    }
    queue->size--;
    return point;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to release memory allocated for the queue
void freeQueue(Queue* queue) {
    free(queue->points);
    free(queue);
}

// Main function to solve the problem
void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize) {
    if (roomsSize == 0) return;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Queue* queue = createQueue(roomsSize * (*roomsColSize));

    // Enqueue all gates
    for (int i = 0; i < roomsSize; i++) {
        for (int j = 0; j < roomsColSize[i]; j++) {
            if (rooms[i][j] == 0) {
                enqueue(queue, i, j);
            }
        }
    }

    // Perform BFS from each gate
    while (!isEmpty(queue)) {
        Point point = dequeue(queue);
        int row = point.row;
        int col = point.col;

        for (int i = 0; i < 4; i++) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            // Check if the new position is within bounds and is an empty room
            if (newRow >= 0 && newRow < roomsSize && newCol >= 0 && newCol < roomsColSize[newRow] && rooms[newRow][newCol] == INF) {
                rooms[newRow][newCol] = rooms[row][col] + 1;
                enqueue(queue, newRow, newCol);
            }
        }
    }

    freeQueue(queue);
}

// Helper function to print the grid (for testing purposes)
void printRooms(int** rooms, int roomsSize, int* roomsColSize) {
    for (int i = 0; i < roomsSize; i++) {
        for (int j = 0; j < roomsColSize[i]; j++) {
            if (rooms[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%3d ", rooms[i][j]);
            }
        }
        printf("\n");
    }
}

// Example usage
int main() {
    int grid[4][4] = {
        {INF,  -1,  0,  INF},
        {INF, INF, INF,  -1},
        {INF,  -1, INF,  -1},
        {0,    -1, INF, INF}
    };
    int* rooms[4];
    int roomsColSize[4] = {4, 4, 4, 4};
    for (int i = 0; i < 4; i++) {
        rooms[i] = grid[i];
    }

    wallsAndGates(rooms, 4, roomsColSize);

    printRooms(rooms, 4, roomsColSize);

    return 0;
}

