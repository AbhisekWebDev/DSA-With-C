#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void quickSort(int array[], int lb, int ub);
int partition(int array[], int lb, int ub);
void swap(int *a, int *b);

int main() {
    int array[] = {1, 9, 7, 3, 8, 2, 4, 6, 5, 0};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    quickSort(array, 0, size - 1);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

void quickSort(int array[], int lb, int ub) {
    if (lb < ub) {
        int location = partition(array, lb, ub);
        quickSort(array, lb, location - 1);
        quickSort(array, location + 1, ub);
    }
}

int partition(int array[], int lb, int ub) {
    int pivot = array[lb];
    int start = lb;
    int end = ub;

    while (start < end) {
        while (array[start] <= pivot && start < ub)
            start++;
        while (array[end] > pivot)
            end--;
        if (start < end)
            swap(&array[start], &array[end]);
    }
    swap(&array[lb], &array[end]);
    return end;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
