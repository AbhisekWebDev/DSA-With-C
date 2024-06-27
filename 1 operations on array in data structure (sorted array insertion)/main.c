#include <stdio.h>
#include <stdlib.h>

// INSERTION OF AN ELEMENT TO A SPECIFIC POSITION

int main()
{
    int a[50], size, num, pos;

    printf("Enter the size of array");
    scanf("%d", &size);
    printf("Enter the elements of array");

    for(int i = 0 ; i < size ; i++)
        scanf("%d", &a[i]);

    printf("Enter data");
    scanf("%d", &num);

    printf("Enter position");
    scanf("%d", &pos);

    for(int i = size - 1 ; i >= pos - 1 ; i--)
        a[i + 1] = a[i];

    a[pos - 1] = num;
    size++;

    for(int i = 0 ; i < size ; i++)
        printf("%d", a[i]);

    return 0;
}
