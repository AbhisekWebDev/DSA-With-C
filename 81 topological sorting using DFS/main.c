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

// Utility function to add a node to the stack
void push(int stack[], int* top, int value) {
    stack[++(*top)] = value;
}

// DFS utility function for topological sorting
void topologicalSortUtil(struct Graph* graph, int v, int visited[], int stack[], int* top) {
    visited[v] = 1;

    struct Node* currentNode = graph->array[v].head;
    while (currentNode != NULL) {
        int connectedVertex = currentNode->dest;
        if (!visited[connectedVertex])
            topologicalSortUtil(graph, connectedVertex, visited, stack, top);

        currentNode = currentNode->next;
    }

    push(stack, top, v);
}

// Function to perform topological sort
void topologicalSort(struct Graph* graph) {
    int* visited = (int*) malloc(graph->numVertices * sizeof(int));
    int* stack = (int*) malloc(graph->numVertices * sizeof(int));
    int top = -1;

    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i])
            topologicalSortUtil(graph, i, visited, stack, &top);
    }

    printf("\nTopological Sort:\n");
    while (top != -1)
        printf("%d ", stack[top--]);

    free(visited);
    free(stack);
}

int main() {
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Graph:\n");
    printGraph(graph);

    topologicalSort(graph);

    return 0;
}




// Topological sorting is an ordering of the vertices in a directed acyclic graph (DAG) such that
// for every directed edge u→v, vertex u comes before v.

//It's commonly used in scenarios like task scheduling, where some tasks must be performed before others.
