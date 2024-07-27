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
    // Here, the graph is undirected, so we need to ensure symmetry
    int graph[4][4] = {
        {0, 3, INF, 7},
        {3, 0, 1, INF},
        {INF, 1, 0, 2},
        {7, INF, 2, 0}
    };

    // Run Floyd-Warshall algorithm
    FloydWarshall(graph, V);

    return 0;
}


// The Floyd-Warshall algorithm can be used for undirected graphs.
// In fact, the Floyd-Warshall algorithm is quite versatile and works for both directed and undirected graphs.
// The key aspect is that the graph should be represented as a weighted adjacency matrix,
// where each entry denotes the weight of the edge between two vertices.

// In the case of an undirected graph, you need to ensure that each edge is represented in both directions
// in the adjacency matrix. That is, if there's an edge between vertices u and v, you should have:

// graph[u][v] = weight of the edge
// graph[v][u] = weight of the edge


// Graph Representation:
// The graph matrix represents an undirected graph where each edge is bidirectional.
// For instance, graph[0][1] and graph[1][0] both have the weight of the edge between vertices 0 and 1.


// Initialization:
// The dist matrix is initialized to the same values as the input graph.
// This matrix will store the shortest distances between all pairs of vertices.


// Algorithm Execution:
// The Floyd-Warshall algorithm updates the dist matrix by considering each vertex
// as an intermediate point and checking if a shorter path can be found through that vertex.


// Output:
// The resulting matrix shows the shortest distances between all pairs of vertices.
