#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to find the subset of an element i (uses path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to do union of two subsets (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare two edges according to their weights
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Function to construct and display the MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0; // Initial count of edges in the result
    int i = 0; // Initial index for sorted edges

    // Step 1: Sort all edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle.
        struct Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn't cause a cycle, include it in the result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Display the MST
    printf("Edges in the constructed MST:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

// Main function to demonstrate the MST
int main() {
    int V = 4; // Number of vertices in the graph
    int E = 5; // Number of edges in the graph
    struct Graph* graph = createGraph(V, E);

    // Add edges
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    // Find and display the MST
    KruskalMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}





// Kruskal's algorithm, which is a common algorithm for finding the MST of a connected, undirected graph.
// Kruskal's algorithm sorts all the edges in non-decreasing order of their weight and adds them to the MST
// if they don't form a cycle. The algorithm uses a disjoint-set data structure to keep track of the vertices
// that are already included in the MST.


// Structures:

// Edge: Represents an edge with source (src), destination (dest), and weight (weight).

// Graph: Represents the graph with an array of edges, number of vertices (V), and number of edges (E).

// Subset: Used in the union-find algorithm to detect cycles.


// Graph Creation:
// createGraph: Initializes a graph with V vertices and E edges.


// Union-Find Operations:
//find: Finds the representative of the subset to which an element belongs, with path compression.


// Union: Unites two subsets into a single subset using union by rank.


// Kruskal's Algorithm:

// KruskalMST: Implements Kruskal's algorithm to find the MST. It sorts all edges in non-decreasing order
// of their weight, then iteratively adds the smallest edge to the MST if it doesn't form a cycle.
// The function prints the edges included in the MST.


// Main Function:

// Initializes the graph with 4 vertices and 5 edges.
// Adds the edges with their weights.
// Calls KruskalMST to find and display the MST.
