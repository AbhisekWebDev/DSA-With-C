#include <stdio.h>
#include <limits.h>

#define INF INT_MAX // Define INF as a large value

// Function to print the solution
void printSolution(int dist[][4], int V) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// The Floyd-Warshall algorithm
void FloydWarshall(int graph[][4], int V) {
    int dist[V][V];

    // Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Add all vertices one by one to the set of intermediate vertices.
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist, V);
}

int main() {
    // Number of vertices in the graph
    int V = 4;

    // Create a graph represented as an adjacency matrix
    int graph[4][4] = {
        {0, 3, INF, INF},
        {2, 0, INF, INF},
        {INF, 7, 0, 1},
        {6, INF, INF, 0}
    };

    // Run Floyd-Warshall algorithm
    FloydWarshall(graph, V);

    return 0;
}



// The Floyd-Warshall algorithm is a classic algorithm used to find the shortest paths between all pairs of vertices
// in a weighted graph. It's particularly useful for graphs where you need to find the shortest path between
// every pair of nodes, not just from a single source to all other nodes.


// Initialization:

// INF is used to represent infinity (no direct path between nodes).
// graph is a 2D array that represents the adjacency matrix of the graph,
// where graph[i][j] holds the weight of the edge from vertex i to vertex j. If there is no direct edge, it is set to INF.


// Floyd-Warshall Algorithm:
// Step 1: Initialize the dist matrix with the values from the input graph.
// Step 2: For each vertex k, update the shortest path between all pairs of vertices i and j using k
        // as an intermediate vertex.
// Step 3: Print the resulting distance matrix.


// Print Solution:
// A matrix of shortest distances is printed, where INF represents no path between the vertices.
