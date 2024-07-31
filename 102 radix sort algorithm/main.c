#include <stdio.h>

// Function prototypes
void radixSort(int array[], int n);
void countingSort(int array[], int n, int exp);
int getMax(int array[], int n);
void printArray(int array[], int n);

int main() {
    int array[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printArray(array, n);

    radixSort(array, n);

    printf("Sorted array: ");
    printArray(array, n);

    return 0;
}

// Function to get the maximum element in the array
int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

// A function to do counting sort of array[] according to the digit represented by exp
void countingSort(int array[], int n, int exp) {
    int output[n]; // Output array
    int count[10] = {0}; // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++) {
        count[(array[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] contains the actual
    // position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    // Copy the output array to array[], so that array[] now
    // contains sorted numbers according to the current digit
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

// The main function to that sorts array[] of size n using Radix Sort
void radixSort(int array[], int n) {
    // Find the maximum number to know the number of digits
    int max = getMax(array, n);

    // Do counting sort for every digit. Note that instead of passing the digit number,
    // exp is passed. exp is 10^i where i is the current digit number
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(array, n, exp);
    }
}

// Function to print the array
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


// Radix Sort is a non-comparative sorting algorithm that sorts numbers by processing individual digits.
// It works by sorting numbers based on their least significant digit (LSD)
// and moving towards the most significant digit (MSD).
// The counting sort algorithm is often used as a subroutine in radix sort.

// getMax Function:

// Finds the maximum number in the array to determine the number of digits.
// This is important for determining the number of passes needed in the Radix Sort.


// countingSort Function:

// This function sorts the array based on the digit represented by exp (exponent).
// The digit to be sorted is (array[i] / exp) % 10.
// It uses a counting sort approach, first counting the occurrences of each digit,
// then adjusting the counts to position the numbers in the output array, and finally building the output array.


// radixSort Function:

// The main function for Radix Sort. It first finds the maximum number in the array to know the number of digits.
// It then iterates over each digit, starting from the least significant digit (LSD) to the most significant digit (MSD),
// and calls countingSort for each digit position.


// printArray Function: - Prints the elements of the array.
