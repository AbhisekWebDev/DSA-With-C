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

// Function to perform topological sorting using BFS (Kahn's Algorithm)
void topologicalSort(struct Graph* graph) {
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
    int* topologicalOrder = (int*) malloc(graph->numVertices * sizeof(int));

    // Process vertices in the queue
    while (front < rear) {
        int u = queue[front++];
        topologicalOrder[count++] = u;

        struct Node* currentNode = graph->array[u].head;
        while (currentNode != NULL) {
            if (--inDegree[currentNode->dest] == 0)
                queue[rear++] = currentNode->dest;

            currentNode = currentNode->next;
        }
    }

    // Check if there was a cycle (count should be equal to the number of vertices)
    if (count != graph->numVertices) {
        printf("There exists a cycle in the graph\n");
    } else {
        printf("\nTopological Sort:\n");
        for (int i = 0; i < count; i++)
            printf("%d ", topologicalOrder[i]);
        printf("\n");
    }

    free(inDegree);
    free(queue);
    free(topologicalOrder);
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
