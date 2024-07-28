#include <stdio.h>

// Function to perform binary search
int binarySearch(int array[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is at the middle
        if (array[mid] == target) {
            return mid; // Return the index if the target is found
        }

        // If the target is greater, ignore the left half
        if (array[mid] < target) {
            left = mid + 1;
        }
        // If the target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    return -1; // Return -1 if the target is not found
}

int main() {
    int array[] = {1, 3, 5, 7, 9, 11, 13}; // Sorted array of integers
    int size = sizeof(array) / sizeof(array[0]);
    int target;

    // Input the target number to search
    printf("Enter the number to search: ");
    scanf("%d", &target);

    // Call the binary search function
    int result = binarySearch(array, size, target);

    // Display the result
    if (result != -1) {
        printf("Number found at index %d.\n", result);
    } else {
        printf("Number not found in the array.\n");
    }

    return 0;
}

// Binary Search Requirement: The array must be sorted for binary search to work correctly.
// If the array is not sorted, the algorithm may not function properly.

// Binary search is more efficient than linear search for large datasets,
// as it reduces the search area by half with each step, resulting in a time complexity of O(log n).
