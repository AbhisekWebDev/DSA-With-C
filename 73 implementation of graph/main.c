#include <stdio.h>
#include <stdlib.h>

// EXPLAINATIONS DOWN BELOW

// Define the number of vertices
#define V 5

// Structure to represent an adjacency list node
struct AdjListNode {
    int dest; // Destination vertex
    struct AdjListNode* next; // Pointer to the next adjacent node
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head; // Pointer to the head of the list
};

// Structure to represent a graph
struct Graph {
    struct AdjList* array; // Array of adjacency lists
    int adjMatrix[V][V]; // Adjacency matrix
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add to the adjacency list
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;

    // Add to the adjacency matrix
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Function to print the adjacency list representation of the graph
void printAdjList(struct Graph* graph) {
    for (int v = 0; v < V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Function to print the adjacency matrix representation of the graph
void printAdjMatrix(struct Graph* graph) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Main function to demonstrate the graph
int main() {
    struct Graph* graph = createGraph();
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the adjacency list representation of the graph
    printAdjList(graph);

    // Print the adjacency matrix representation of the graph
    printAdjMatrix(graph);

    return 0;
}




// create a simple program that represents an undirected graph using an adjacency list.
// An adjacency list is a common way to represent a graph where each vertex has a list of adjacent vertices.

// Steps to Implement the Graph

// Define the Structure of the Graph:
// A Graph structure containing an array of AdjList pointers.
// An AdjList structure containing a linked list of AdjListNode.
// An AdjListNode structure representing the nodes in the linked list.

// Create the Graph:
// Initialize the graph with a specific number of vertices.
// Allocate memory for the adjacency list and initialize each list as empty.

// Add Edges:
// Define a function to add edges between two vertices.

// Display the Graph:
// Define a function to display the graph as an adjacency list.






// Structures:

// AdjListNode: Represents a node in the adjacency list. Contains dest (the destination vertex)
// and next (pointer to the next node).

// AdjList: Contains a pointer to the head of an adjacency list.

// Graph: Contains the number of vertices V and an array of AdjList to represent the adjacency list of each vertex.


// Functions:

// newAdjListNode(int dest): Creates a new adjacency list node.

// createGraph(int V): Allocates memory for a graph with V vertices and initializes the adjacency lists.

// addEdge(struct Graph* graph, int src, int dest): Adds an undirected edge between src and dest.

// printGraph(struct Graph* graph): Prints the adjacency list representation of the graph.





// Adjacency matrix

// To represent a graph, both adjacency list and adjacency matrix methods are commonly used.
// The adjacency matrix is a 2D array where each cell at row i
// and column j indicates whether there is an edge between vertices i and j.

// Adjacency Matrix in the Graph Structure:
// The Graph structure now includes an adjMatrix[V][V] to store the adjacency matrix.

// Initialization of Adjacency Matrix:
// In the createGraph() function, the adjacency matrix is initialized to 0,
// indicating no edges between any vertices initially.

// Adding Edges:
// In the addEdge() function, the adjacency matrix is updated whenever an edge is added.
// For an undirected graph, graph->adjMatrix[src][dest] and graph->adjMatrix[dest][src] are both set to 1.

// Printing the Adjacency Matrix:
// The printAdjMatrix() function iterates over the matrix and prints its values,
// showing the connections between vertices.
