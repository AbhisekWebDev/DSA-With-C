#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[] = {1, 9, 7, 3, 8, 2, 4, 6, 5, 0};

    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array : ");

    for (int i = 0 ; i < size ; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    insertionSort(array, size);

    printf("Sorted array : ");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}

void insertionSort(int array[], int size){

    for(int i = 1 ; i < size ; i++){

        int temp = array[i];

        int j = i - 1;

        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = temp;
    }
}
