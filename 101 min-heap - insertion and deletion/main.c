#include <stdio.h>

// Function prototypes
void insert(int heap[], int *n, int value);
void deleteRoot(int heap[], int *n);
void minHeapify(int heap[], int n, int i);
void printHeap(int heap[], int n);

int main() {
    int heap[100]; // Array representation of the heap
    int size = 0; // Current size of the heap

    // Inserting elements into the heap
    insert(heap, &size, 10);
    insert(heap, &size, 20);
    insert(heap, &size, 5);
    insert(heap, &size, 30);
    insert(heap, &size, 2);

    printf("Min-Heap array after insertion: ");
    printHeap(heap, size);

    // Deleting the root element from the heap
    deleteRoot(heap, &size);

    printf("Min-Heap array after deletion: ");
    printHeap(heap, size);

    return 0;
}

// Function to insert an element into the min-heap
void insert(int heap[], int *n, int value) {
    // Insert the new value at the end
    heap[*n] = value;
    (*n)++;

    // Heapify the new element up to maintain the min-heap property
    int i = *n - 1;
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Function to delete the root element from the min-heap
void deleteRoot(int heap[], int *n) {
    if (*n <= 0)
        return;

    // Move the last element to the root and reduce the size of the heap
    heap[0] = heap[*n - 1];
    (*n)--;

    // Heapify down to maintain the min-heap property
    minHeapify(heap, *n, 0);
}

// Function to heapify a subtree rooted with node i
void minHeapify(int heap[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    // If left child is smaller than root
    if (left < n && heap[left] < heap[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    // If smallest is not root *swapping*
    if (smallest != i) {
        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        // Recursively heapify the affected sub-tree
        minHeapify(heap, n, smallest);
    }
}

// Function to print the heap
void printHeap(int heap[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", heap[i]);
    printf("\n");
}
