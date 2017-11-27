#include <stdio.h>
#include <stdlib.h>

int** superior(int h)
{
    int** hv = malloc(h * sizeof(int*));

    for(int i = 0; i < h; i++)
    {
        hv[i] = malloc((h - i)*sizeof(int));
        //printf("%d\n", h - i);
        for(int j = 0; j < h - i; j++)
            hv[i][j] = j;
    }
    return hv;
}

void afisareSueprior(int** a, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
            printf("  ");
        for(int j = 0; j < n - i; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int main()
{
    int** m = superior(5);

    afisareSueprior(m, 5);

    return 0;
}
