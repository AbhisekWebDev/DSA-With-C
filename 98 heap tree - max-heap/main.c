#include <stdio.h>

// Function prototypes
void heapify(int array[], int n, int i);
void heapSort(int array[], int n);
void printArray(int array[], int n);

int main() {
    int array[] = {1, 9, 7, 3, 8, 2, 4, 6, 5, 0};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printArray(array, size);

    heapSort(array, size);

    printf("Sorted array (Max-Heap): ");
    printArray(array, size);

    return 0;
}

// Function to heapify a subtree rooted with node i
// n is the size of the heap
void heapify(int array[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child index
    int right = 2 * i + 2; // right child index

    // If left child is larger than root
    if (left < n && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        // Swap the root with the largest
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(array, n, largest);
    }
}

// Main function to do heap sort
void heapSort(int array[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Call max heapify on the reduced heap
        heapify(array, i, 0);
    }
}

// Function to print the array
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}
