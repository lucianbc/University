#include <stdio.h>
#include <stdlib.h>

int NR_LINIE, NR_COLOANA;
int TO_WRITE = 1;

void scrieLinie(int[][100], int, int, int);
void scrieColoana(int[][100], int, int, int);

void scrieLinie(int a[][100], int l, int c, int s)
{
    if(NR_LINIE == 0)
        return;

    int i;
    for(i = 0; i < NR_COLOANA; i++)
    {
         a[l][c + s * i] = TO_WRITE;
         TO_WRITE++;
    }

    NR_LINIE--;

    scrieColoana(a, l + s, c + s * (i - 1), s);
}

void scrieColoana(int a[][100], int l, int c, int s)
{
    if(NR_COLOANA == 0)
        return;

    int i;
    for(i = 0; i < NR_LINIE; i++)
    {
        a[l + s * i][c] = TO_WRITE;
        TO_WRITE++;
    }

    NR_COLOANA--;

    scrieLinie(a, l + s * (i - 1), c - s, -s);
}

void afisare(int a[][100], int n, int m)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int main()
{
    int a[100][100];
    int n = 5;
    NR_LINIE = NR_COLOANA = n;

    scrieLinie(a, 0, 0, 1);

    afisare(a, n, n);

    return 0;
}
