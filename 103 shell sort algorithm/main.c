#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int size);
void shellSort(int array[], int size);
void swap(int *a, int *b);

int main()
{
    printf("Shell sort : \n");

    int array[] = {9, 2, 7, 8, 3, 1, 4, 6, 5, 0};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printArray(array, size);

    shellSort(array, size);

    printf("Sorted array: ");
    printArray(array, size);

    return 0;
}

void printArray(int array[], int size){
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    printf("\n");
}

void shellSort(int array[], int size){
    for (int gap = size / 2; gap > 0; gap /= 2){
        for (int j = gap; j < size; j++){
            for (int i = j - gap; i >= 0; i -= gap){
                if (array[i + gap] >= array[i])break;
                swap(&array[i + gap], &array[i]);
            }
        }
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
