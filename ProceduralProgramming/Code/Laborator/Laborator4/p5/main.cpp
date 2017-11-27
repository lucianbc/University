#include <iostream>
#include <stdio.h>

using namespace std;

void citire(int a[][100], int* n, int* m)
{
    // n linii, m coloane
    FILE* inputFile = fopen("inputFile.txt", "r");
    fscanf(inputFile, "%d", n);
    fscanf(inputFile, "%d", m);

    int i, j;

    for(i = 0; i < *n; i++)
        for(j = 0; j < *m; j++)
            fscanf(inputFile, "%d", &a[i][j]);
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

void afisareLinie(int[][100], int, int, int);
void afisareColoana(int[][100], int, int, int);

int NR_LINIE, NR_COLOANA;

void afisareLinie(int a[][100], int l, int c, int s)
{
    if(NR_LINIE == 0)
        return;

    int i;
    for(i = 0; i < NR_COLOANA; i++)
        printf("%d ", a[l][c + s * i]);

    NR_LINIE--;

    afisareColoana(a, l + s, c + s * (i - 1), s);
}

void afisareColoana(int a[][100], int l, int c, int s)
{
    if(NR_COLOANA == 0)
        return;

    int i;
    for(i = 0; i < NR_LINIE; i++)
        printf("%d ", a[l + s * i][c]);

    NR_COLOANA--;

    afisareLinie(a, l + s * (i - 1), c - s, -s);
}

int main()
{
    int n, m;
    int a[100][100];

    citire(a, &n, &m);

    NR_LINIE = n, NR_COLOANA = m;

    afisareLinie(a, 0, 0, 1);

    return 0;
}
