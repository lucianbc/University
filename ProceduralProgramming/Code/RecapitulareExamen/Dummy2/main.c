#include <stdio.h>
#include <stdlib.h>

void interschimba(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int* citire(int n)
{
    int* v = malloc(n * sizeof(int));
    int i;
    for(i = 0; i < n; i++)
        scanf("%d", v + i);
    return v;
}

void scrie(int* v, int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int gasesteMint(int* v, int i, int j)
{
    int pozMin = i, p;

    for(p = i + 1; p <= j; p++)
        if(v[p] < v[pozMin])
        {
            pozMin = p;
        }
    return pozMin;
}

void sortare(int* v, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int poz = gasesteMint(v, i, n - 1);
        if(poz != i)
        {
            v[poz] = v[poz] + v[i];
            v[i] = v[poz] - v[i];
            v[poz] = v[poz] - v[i];
        }
    }
}

int comp(const void *a, const void *b)
{
    return *(int*)a == *(int*)b;
}

void* cautare(const void* x, const void* t, int n, int d, int (*cmpValori)(const void*, const void*))
{
    char* crt = t;
    int i;
    for(i = 0; i < n; i++)
    {
        if(cmpValori(x, t + i * d))
            return t + i * d;
    }
    return NULL;
}

int main()
{
    int n;

    scanf("%d", &n);

    int* a = citire(n);

    sortare(a, n);

    scrie(a, n);

    void* ap = cautare(&n, a, n, sizeof(int), comp);

    printf("%p\n", ap);

    return 0;
}
