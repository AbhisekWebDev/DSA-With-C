#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[3][3] = {6,2,5,0,1,3,4,9,8};
    int *p;

    p = &a[0][0];
    p = a[0];

    printf("%p \n", p);
    printf("%p \n", a);
    printf("%p \n", a[0][0]);
    printf("%p \n", a[0]);
    printf("%p \n", &a);
    printf("%p \n", *a);
    printf("%p \n", a+1);
    printf("%p \n", &a[1]);
    printf("%p \n", *(a+1));
    printf("%p \n", a[1][2]);
    printf("%p \n", *(a+1)+2);
    printf("%p \n", *(*(a+1)+2));
    printf("%p \n", &a[1]);
    printf("%p \n", a[1]);
    printf("%p \n", a[1][0]);
    printf("%p \n", &a[1][0]);

    printf("%d \n", p);
    printf("%d \n", a);
    printf("%d \n", a[0][0]);
    printf("%d \n", a[0]);
    printf("%d \n", &a);
    printf("%d \n", *a);
    printf("%d \n", a+1);
    printf("%d \n", &a[1]);
    printf("%d \n", *(a+1));
    printf("%d \n", a[1][2]);
    printf("%d \n", *(a+1)+2);
    printf("%d \n", *(*(a+1)+2));
    printf("%d \n", &a[1]);
    printf("%d \n", a[1]);
    printf("%d \n", a[1][0]);
    printf("%d", &a[1][0]);

    return 0;
}
