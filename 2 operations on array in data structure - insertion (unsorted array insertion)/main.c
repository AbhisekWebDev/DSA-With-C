#include <stdio.h>
#include <stdlib.h>

// INSERTION OF AN ELEMENT TO A AN UNSORTED ARRAY

int main()
{
    int a[50], size, num, pos;

    printf("Enter the size of array : ");
    scanf("%d", &size);
    printf("Enter the elements of array : ");

    for(int i = 0 ; i < size ; i++)
        scanf("%d", &a[i]);

    printf("Enter position : ");
    scanf("%d", &pos);

    printf("Enter data : ");
    scanf("%d", &num);

    a[size] = a[pos - 1];
    a[pos - 1] = num;
    size++;

    for(int i = 0 ; i < size ; i++)
        printf("%d", a[i]);

    return 0;
}
