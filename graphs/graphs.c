#include <stdio.h>

#define MAX_NODES 100

// Global variables
int graph[MAX_NODES][MAX_NODES];  // Adjacency matrix representation of the graph
int visited[MAX_NODES];           // Array to keep track of visited nodes
int numNodes;                     // Number of nodes in the graph

// Function to perform Depth First Search
void dfs(int node) {
    printf("%d ", node);  // Print the visited node
    visited[node] = 1;    // Mark the node as visited

    // Visit all the adjacent nodes of the current node
    for (int i = 0; i < numNodes; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);  // Recursive call for unvisited adjacent node
        }
    }
}

/* Function to calculate the degree
Input - Graph G, Vertex V
Output - Degree of the vertex
*/

/* Compute max degree in a Graph */

/* Compute average degree
2X num of edges/num of vertex */

/* Count self loops */

// Function to initialize the graph
void initializeGraph(int n) {
    numNodes = n;

    // Initialize the adjacency matrix and visited array
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph[i][j] = 0;
        }
        visited[i] = 0;
    }
}

int main() {
    int n, m;  // Number of nodes and edges

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &m);

    initializeGraph(n);

    printf("Enter the edges (node1 node2):\n");
    for (int i = 0; i < m; i++) {
        int node1, node2;
        scanf("%d %d", &node1, &node2);
        graph[node1][node2] = 1;
        graph[node2][node1] = 1;  // Uncomment this line for undirected graphs
    }

    int startNode;
    printf("Enter the starting node: ");
    scanf("%d", &startNode);

    printf("Depth First Traversal: ");
    dfs(startNode);

    return 0;
}

