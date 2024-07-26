#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int* visited;
    int* discoveryTime;
    int* low;
    int* parent;
    int time;
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
    graph->visited = (int*) malloc(numVertices * sizeof(int));
    graph->discoveryTime = (int*) malloc(numVertices * sizeof(int));
    graph->low = (int*) malloc(numVertices * sizeof(int));
    graph->parent = (int*) malloc(numVertices * sizeof(int));
    graph->time = 0;

    for (int i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
        graph->visited[i] = 0;
        graph->discoveryTime[i] = -1;
        graph->low[i] = -1;
        graph->parent[i] = -1;
    }

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

// DFS function to find bridges
void bridgeDFS(struct Graph* graph, int u) {
    graph->visited[u] = 1;
    graph->discoveryTime[u] = graph->low[u] = ++graph->time;

    struct Node* currentNode = graph->array[u].head;
    while (currentNode != NULL) {
        int v = currentNode->dest;
        if (!graph->visited[v]) {
            graph->parent[v] = u;
            bridgeDFS(graph, v);

            // Check if the subtree rooted at v has a connection back to one of u's ancestors
            graph->low[u] = (graph->low[u] < graph->low[v]) ? graph->low[u] : graph->low[v];

            // If the lowest vertex reachable from subtree under v is below u in DFS tree, then u-v is a bridge
            if (graph->low[v] > graph->discoveryTime[u])
                printf("Bridge found between vertices %d and %d\n", u, v);
        }
        else if (v != graph->parent[u]) {
            // Update low value of u for parent function calls.
            graph->low[u] = (graph->low[u] < graph->discoveryTime[v]) ? graph->low[u] : graph->discoveryTime[v];
        }
        currentNode = currentNode->next;
    }
}

// Function to find and display all bridges in the graph
void findBridges(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i])
            bridgeDFS(graph, i);
    }
}

int main() {
    int V = 5;  // Number of vertices in the graph
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);

    printf("Graph:\n");
    printGraph(graph);

    printf("\nBridges in the graph:\n");
    findBridges(graph);

    return 0;
}
