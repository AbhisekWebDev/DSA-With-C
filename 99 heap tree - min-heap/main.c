#include <stdio.h>

// Function prototypes
void minHeapify(int array[], int n, int i);
void heapSort(int array[], int n);
void printArray(int array[], int n);

int main() {
    int array[] = {1, 9, 7, 3, 8, 2, 4, 6, 5, 0};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printArray(array, size);

    heapSort(array, size);

    printf("Sorted array (Min-Heap): ");
    printArray(array, size);

    return 0;
}

// Function to heapify a subtree rooted with node i
// n is the size of the heap
void minHeapify(int array[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    // If left child is smaller than root
    if (left < n && array[left] < array[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && array[right] < array[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        // Swap the root with the smallest
        int temp = array[i];
        array[i] = array[smallest];
        array[smallest] = temp;

        // Recursively heapify the affected sub-tree
        minHeapify(array, n, smallest);
    }
}

// Main function to do heap sort
void heapSort(int array[], int n) {
    // Build min-heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(array, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Call min heapify on the reduced heap
        minHeapify(array, i, 0);
    }
}

// Function to print the array
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}
