#include <stdio.h>
#include <stdlib.h>

int f1(int a) {return 5 * a;}
int f2(int b) {return b - 2;}
int f3(int *c) {return f2(f1(*c));}

int main()
{
//
//    01011
//    10110
//    00010
//    printf("%d %d\n", (11 && 22), (11 & 22));

//    int a=0,b=1,c=2;
//    printf("%d %d %d \n", f1(b), f2(c), f3(&a));

    // alocare
    int r = 5, c = 7;
    int i, j;
    int **a = malloc(4 * sizeof(int*));
    a[0] = malloc(r * c * sizeof(int));

    for(i = 1; i < r; i++)
        a[i] = a[0] + i * c;
    // sfarsit alocare

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            a[i][j] = j;
    }

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    return 0;
}
