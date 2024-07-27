#include <stdio.h>
#include <limits.h>

#define V 5 // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest distance from the source to each vertex
void printSolution(int dist[]) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t\t%d\n", i, dist[i]);
    }
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Output array. dist[i] holds the shortest distance from src to i
    int visited[V]; // visited[i] will be 1 if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and visited[] as 0
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if:
            // - it is not in visited
            // - there is an edge from u to v
            // - total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist);
}

int main() {
    // Define the graph as an adjacency matrix
    int graph[V][V] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    int source = 0; // Starting vertex (source)

    // Call Dijkstra's algorithm
    dijkstra(graph, source);

    return 0;
}



// Dijkstra's algorithm is a popular method for finding the shortest path between nodes in a graph,
// particularly useful for graphs with non-negative weights.
// This program uses an adjacency matrix to represent the graph and finds the shortest path from a source vertex
// to all other vertices.


// Graph Representation:
// The graph is represented as an adjacency matrix,
// where graph[i][j] holds the weight of the edge from vertex i to vertex j. If there is no edge, the value is 0.


// Initialization: Two arrays are used:
// dist[]: This holds the shortest distance from the source to each vertex.
// It is initialized with INT_MAX (representing infinity) except for the source vertex, which is set to 0.

// visited[]: This keeps track of the vertices included in the shortest path tree, initialized to 0 (false).


// Algorithm Steps:
// The algorithm picks the vertex with the minimum distance that hasn't been processed yet (minDistance function).
// It then updates the distance of the adjacent vertices of the picked vertex.
// This process repeats until all vertices are processed.


// Output: The shortest distances from the source vertex to each other vertex are printed.
