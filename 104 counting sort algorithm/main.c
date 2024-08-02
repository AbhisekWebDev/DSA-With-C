#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int find_largest_element(int array[], int size) {

    int max_element = array[0];  // Assume the first element is the largest to start

    for (int i = 1; i < size; i++) {  // Start loop from the second element
        if (array[i] > max_element)
            max_element = array[i];
    }
    return max_element;
}

void countingSort(int array[], int size) {

    int k = find_largest_element(array, size);

    // The countArray and sortedArray are now dynamically allocated using malloc
    // to ensure they are properly sized based on k and size.
    int *countArray = (int *)malloc((k + 1) * sizeof(int));
    int *sortedArray = (int *)malloc(size * sizeof(int));

    // Initialize countArray with zeros
    for (int i = 0; i <= k; i++)
        countArray[i] = 0;

    // Store the count of each element in countArray
    for (int i = 0; i < size; i++)
        countArray[array[i]]++;

    // Change countArray so that countArray[i] now contains the actual position of this element in the sorted array
    for (int i = 1; i <= k; i++)
        countArray[i] += countArray[i - 1];

    // Build the sorted array
    for (int i = size - 1; i >= 0; i--)
        sortedArray[--countArray[array[i]]] = array[i];

    // Copy the sorted array back to the original array
    for (int i = 0; i < size; i++)
        array[i] = sortedArray[i];

    // Free dynamically allocated memory
    free(countArray);
    free(sortedArray);
}

int main()
{
    int array[] = {2, 1, 1, 0, 2, 5, 4, 0, 2, 8, 7, 7, 9, 2, 0, 1, 9};

    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array : ");
    printArray(array, size);

    countingSort(array, size);

    printf("Sorted array : ");
    printArray(array, size);

    return 0;
}
