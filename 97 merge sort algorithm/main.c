#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void mergeSort(int array[], int left, int right);
void merge(int array[], int left, int mid, int right);

int main() {
    int array[] = {1, 9, 7, 3, 8, 2, 4, 6, 5, 0};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    mergeSort(array, 0, size - 1);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

// Function to perform merge sort on the array
void mergeSort(int array[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        // Merge the sorted halves
        merge(array, left, mid, right);
    }
}

// Function to merge two halves of the array
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

