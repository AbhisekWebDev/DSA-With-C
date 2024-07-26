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

// Structure to store the vertex and its parent in the queue
struct QueueNode {
    int vertex;
    int parent;
};

// Function to detect a cycle in the graph using BFS
int isCyclic(struct Graph* graph) {
    int* visited = (int*) malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            struct QueueNode* queue = (struct QueueNode*) malloc(graph->numVertices * sizeof(struct QueueNode));
            int front = 0, rear = 0;

            visited[i] = 1;
            queue[rear].vertex = i;
            queue[rear].parent = -1;
            rear++;

            while (front < rear) {
                int u = queue[front].vertex;
                int parent = queue[front].parent;
                front++;

                struct Node* currentNode = graph->array[u].head;
                while (currentNode != NULL) {
                    int v = currentNode->dest;

                    if (!visited[v]) {
                        visited[v] = 1;
                        queue[rear].vertex = v;
                        queue[rear].parent = u;
                        rear++;
                    } else if (v != parent) {
                        free(queue);
                        free(visited);
                        return 1; // Cycle detected
                    }

                    currentNode = currentNode->next;
                }
            }

            free(queue);
        }
    }

    free(visited);
    return 0; // No cycle detected
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
