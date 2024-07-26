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

// Add an edge to the undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
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

// Utility function for DFS traversal
int isCyclicUtil(struct Graph* graph, int v, int visited[], int parent) {
    visited[v] = 1;

    struct Node* currentNode = graph->array[v].head;
    while (currentNode != NULL) {
        int connectedVertex = currentNode->dest;

        if (!visited[connectedVertex]) {
            if (isCyclicUtil(graph, connectedVertex, visited, v))
                return 1;
        }
        else if (connectedVertex != parent) {
            return 1;
        }

        currentNode = currentNode->next;
    }
    return 0;
}

// Function to detect a cycle in the graph
int isCyclic(struct Graph* graph) {
    int* visited = (int*) malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = 0;

    for (int u = 0; u < graph->numVertices; u++) {
        if (!visited[u] && isCyclicUtil(graph, u, visited, -1))
            return 1;
    }

    free(visited);
    return 0;
}

int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 1);

    printf("Graph:\n");
    printGraph(graph);

    if (isCyclic(graph))
        printf("\nGraph contains cycle\n");
    else
        printf("\nGraph doesn't contain cycle\n");

    return 0;
}
