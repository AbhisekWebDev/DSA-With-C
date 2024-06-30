#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[] = {6, 2, 1, 5, 3};
    int b = 10;
    int *p = &b;

    printf("%d \n", b);
    printf("%d \n", *p);
    printf("%p \n", &b);
    printf("%p \n", p);
    printf("%p \n", a);

    int *q = a;
    q++;

    printf("%p \n", &a);
    printf("%p \n", &q);

    printf("%d \n", a[2]);
    printf("%d \n", *(a+2));
    printf("%d \n", *(q+1));

    printf("%d \n", 2[a]);
    printf("%d \n", 2[q]);

    printf("%d \n", *(q+1));
    printf("%d \n", *(2+q));
    printf("%d \n", 3[q]);

    printf("%p \n", a+1);
    printf("%p \n", &a+1);

    printf("%p \n", &a[0] + 1);
    printf("%d \n", *a);
    printf("%d \n", *a + 1);

    printf("%d \n", q+3);

    printf("Looping \n");

    int i;
    for(i = 0 ; i < 5 ; i++){
        printf("%d", a[i]);
    }

    printf("\n");

    for(i = 0 ; i < 5 ; i++){
        printf("%d", *(q+i));
    }

    printf("\n");

    for(i = 0 ; i < 5 ; i++){
        printf("%d", *(a+i));
    }

    printf("\n");

    for(i = 0 ; i < 5 ; i++){
        printf("%d", i[a]);
    }

    return 0;
}
