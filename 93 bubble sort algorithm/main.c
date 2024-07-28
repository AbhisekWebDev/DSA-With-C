#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[] = {16,14,5,6,8};

    int size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    int iterations = 0;

    bubbleSort(array, size, &iterations);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Number of iterations: %d\n", iterations);

    return 0;
}

void bubbleSort(int array[], int size, int *iterations){
    for(int i = 0 ; i < size - 1 ; i++){

        int flag = 0;

        for(int j = 0 ; j < size - 1 - i ; j++){
            if(array[j] > array[j + 1]){
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;

                flag = 1;
            }
        }
        (*iterations)++;
        if(flag == 0) break;
    }
}
