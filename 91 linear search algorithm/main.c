#include <stdio.h>

// Function to perform linear search
int linearSearch(int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i; // Return the index if the target is found
        }
    }
    return -1; // Return -1 if the target is not found
}

int main() {
    int array[] = {4, 2, 7, 1, 9, 3}; // Array of integers
    int size = sizeof(array) / sizeof(array[0]); // Calculate the size of the array
    int target;

    // Input the target number to search
    printf("Enter the number to search: ");
    scanf("%d", &target);

    // Call the linear search function
    int result = linearSearch(array, size, target);

    // Display the result
    if (result != -1) {
        printf("Number found at index %d.\n", result);
    } else {
        printf("Number not found in the array.\n");
    }

    return 0;
}

// linear search works on sorted array as well as unsorted array
