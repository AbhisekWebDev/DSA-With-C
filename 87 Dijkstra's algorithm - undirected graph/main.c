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

// Function to implement Dijkstra's algorithm for an undirected graph
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
    // Define the undirected graph as an adjacency matrix
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int source = 0; // Starting vertex (source)

    // Call Dijkstra's algorithm
    dijkstra(graph, source);

    return 0;
}



// Dijkstra's algorithm for an undirected graph, we can still use an adjacency matrix.
// However, we need to ensure that the matrix is symmetric; that is,
// if there is an edge between vertex i and vertex j, then both graph[i][j] and graph[j][i]
// should have the same non-zero value. This symmetry ensures that the graph is undirected,
// meaning the relationship between nodes goes both ways.


// Graph Representation:
// The graph is represented as an undirected graph using an adjacency matrix where graph[i][j] = graph[j][i].
// For example, if there is an edge between vertex 0 and vertex 1 with a weight of 2,
// then both graph[0][1] and graph[1][0] are set to 2.


// Algorithm Steps:
// The algorithm proceeds similarly to the directed graph case.
// The main difference is in the graph representation, as the adjacency matrix now represents an undirected graph.


// Output: The shortest distances from the source vertex to each other vertex are printed.
