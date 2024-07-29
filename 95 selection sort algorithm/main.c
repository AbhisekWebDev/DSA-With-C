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

    selectionSort(array, size);

    printf("Sorted array : ");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}

void selectionSort(int array[], int size){

    for(int i = 0 ; i < size ; i++){

        int min = i;

        for(int j = i + 1 ; j < size ; j++){

            if(array[j] < array[min])
                min = j;
        }

        if(min != i)
            swap(&array[i], &array[min]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
