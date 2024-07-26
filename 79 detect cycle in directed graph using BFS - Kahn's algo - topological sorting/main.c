#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the adjacency list
struct Node {
    int dest;
    struct Node* next;
};

// Define the structure for the adjacency list
struct AdjList {
    struct Node* head;
};

// Define the structure for the graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Create a new node in the adjacency list
struct Node* newAdjListNode(int dest) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*) malloc(numVertices * sizeof(struct AdjList));

    for (int i = 0; i < numVertices; i++)
        graph->array[i].head = NULL;

    return graph;
}

// Add an edge to the directed graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Utility function to print the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        struct Node* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Function to detect a cycle in the graph using BFS (Kahn's algorithm)
int isCyclic(struct Graph* graph) {
    int* inDegree = (int*) malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++)
        inDegree[i] = 0;

    // Calculate in-degrees of all vertices
    for (int u = 0; u < graph->numVertices; u++) {
        struct Node* currentNode = graph->array[u].head;
        while (currentNode != NULL) {
            inDegree[currentNode->dest]++;
            currentNode = currentNode->next;
        }
    }

    // Enqueue all vertices with in-degree 0
    int* queue = (int*) malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (inDegree[i] == 0)
            queue[rear++] = i;
    }

    int count = 0; // Count of visited vertices
    while (front < rear) {
        int u = queue[front++];

        struct Node* currentNode = graph->array[u].head;
        while (currentNode != NULL) {
            if (--inDegree[currentNode->dest] == 0)
                queue[rear++] = currentNode->dest;

            currentNode = currentNode->next;
        }
        count++;
    }

    free(queue);
    free(inDegree);

    // If count does not equal the number of vertices, there is a cycle
    return (count != graph->numVertices);
}

int main() {
    int V = 4;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Graph:\n");
    printGraph(graph);

    if (isCyclic(graph))
        printf("\nGraph contains cycle\n");
    else
        printf("\nGraph doesn't contain cycle\n");

    return 0;
}


// To detect a cycle in a directed graph using Breadth-First Search (BFS),
// we can use the concept of Kahn's algorithm for topological sorting.
// This algorithm works by repeatedly removing vertices with no incoming edges (in-degree 0).
// If we can't remove all vertices (i.e., some vertices remain with non-zero in-degrees), the graph contains a cycle.
