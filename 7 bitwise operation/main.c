#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 5, b = 4;

    printf("%d \n", a & b);

    printf("%d \n", a | b);

    printf("%d \n", ~a);

    printf("%d \n", ~b);

    printf("%d \n",  a ^ b);

    printf("%d \n",  a << 2);

    printf("%d \n",  b >> 2);

    return 0;
}
