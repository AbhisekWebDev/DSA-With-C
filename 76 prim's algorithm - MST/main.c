#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Number of vertices in the graph
#define V 5

// Function to find the vertex with the minimum key value that is not yet included in the MST
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], minIndex = v;

    return minIndex;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and display the MST using Prim's algorithm
void primMST(int graph[V][V]) {
    int parent[V]; // Array to store the constructed MST
    int key[V];    // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include the first 1st vertex in MST.
    key[0] = 0;      // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always the root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        for (int v = 0; v < V; v++)
            // graph[u][v] is non-zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Print the constructed MST
    printMST(parent, graph);
}

// Main function to demonstrate the MST using Prim's algorithm
int main() {
    /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Find and display the MST using Prim's algorithm
    primMST(graph);

    return 0;
}





// Prim's algorithm builds the MST by starting with an arbitrary vertex and growing the tree one edge at a time,
// always choosing the minimum weight edge that connects a vertex in the MST to a vertex outside it.



// Graph Representation:

// The graph is represented using an adjacency matrix, where graph[i][j] holds the weight of the edge
// between vertices i and j. A value of 0 indicates no edge between the vertices.


// Helper Functions:

// minKey: This function finds the vertex with the smallest key value that hasn't been included in the MST yet.
// It is used to pick the next vertex to include in the MST.

// printMST: This function prints the edges of the MST and their corresponding weights.


// Prim's Algorithm:

// primMST: This function implements Prim's algorithm. It initializes all vertices' keys as infinite
// and marks all vertices as not being part of the MST. It starts from the first vertex and always picks
// the minimum weight edge that connects a vertex in the MST with a vertex outside the MST.
// This process continues until all vertices are included in the MST.


// Main Function:
// The main function initializes a graph with 5 vertices and 7 edges.
// It then calls the primMST function to find and display the MST.
