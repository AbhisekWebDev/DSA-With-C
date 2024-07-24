#include <stdio.h>
#include <stdlib.h>

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

// Function to perform BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    int visited[V] = {0};
    int queue[V];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("\n");
    printf("BFS traversal starting from vertex %d: ", startVertex);
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Function to perform DFS traversal
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[V] = {0};
    printf("DFS traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
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

    // Perform BFS and DFS traversals
    BFS(graph, 0);
    DFS(graph, 0);

    return 0;
}





// To perform Breadth-First Search (BFS) and Depth-First Search (DFS) on a graph,
// we'll add corresponding functions to the existing graph structure. BFS uses a queue
// to explore the graph level by level, while DFS uses a stack (or recursion) to explore as far as possible
// along a branch before backtracking.






// BFS Function:

// The BFS() function initializes a visited array and a queue. It starts by visiting the startVertex,
// marks it as visited, and adds it to the queue.
// It then dequeues a vertex, prints it, and enqueues all its adjacent, unvisited vertices, marking them as visited.
// This process continues until the queue is empty.


// DFS Function:

// The DFS() function uses a helper function DFSUtil() to handle the recursive traversal.
// It starts from the startVertex, marks it as visited, and prints it.
// It then recursively visits all unvisited adjacent vertices.
