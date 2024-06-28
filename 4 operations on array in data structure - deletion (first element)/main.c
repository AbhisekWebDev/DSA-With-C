#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[50], size, num, pos;

    printf("Enter the size of array : ");
    scanf("%d", &size);

    if(size > 50)
        printf("Invalid size");
    else {
    printf("Enter the elements of array : ");

    for(int i = 0 ; i < size ; i++)
        scanf("%d", &a[i]);

    printf("Enter position you want to delete : ");
    scanf("%d", &pos);

    if(pos < 0 || pos > size)
        printf("Invalid position");
    else {
        for(int i = 0 ; i < size -1 ; i++)
            a[i] = a[i + 1];

        size--;
    }
    }

    for(int i = 0 ; i < size ; i++)
        printf("%d", a[i]);

    return 0;
}
